#include "LBL_NetEngine_COMTransThread.h"
#include <QThread>

LBL_NetEngine_COMTransThread::LBL_NetEngine_COMTransThread(LBL_NetEngine * pThreadEngine, int nPayLoad, QObject * parent)
	: LBL_NetEngine_TransThread(pThreadEngine, nPayLoad, parent)
{
	m_communicatType = ECommunicatType::ECT_COM;
}

LBL_NetEngine_COMTransThread::~LBL_NetEngine_COMTransThread()
{
	qDebug() << __FUNCTION__;
}

void LBL_NetEngine_COMTransThread::closeSocket(QObject * objSocket)
{
	QSerialPort* pSerialPort = qobject_cast<QSerialPort*>(objSocket);
	if (pSerialPort)
	{
		disconnect(pSerialPort, &QSerialPort::readyRead, this, &LBL_NetEngine_COMTransThread::slot_New_Data_Recieved);
		void (LBL_NetEngine_COMTransThread:: * displayError)(QSerialPort::SerialPortError) = &LBL_NetEngine_COMTransThread::slot_DisplayError;
		disconnect(pSerialPort, &QSerialPort::errorOccurred, this, displayError);
		disconnect(pSerialPort, &QSerialPort::bytesWritten, this, &LBL_NetEngine_COMTransThread::slot_Some_Data_Sended);

		m_buffer_sending.erase(pSerialPort);
		m_buffer_sending_offset.erase(pSerialPort);
		m_mutex_protect.lock();
		m_clientList.remove(pSerialPort);
		m_mutex_protect.unlock();
		pSerialPort->clear();
		pSerialPort->close();
		emit sig_SocketClosed(pSerialPort);
		emit sig_Message(pSerialPort, "Info>" + QString(tr("Client Closed.")));
		qDebug() << tr("(%1)..Closed.").arg((quint64)pSerialPort);
		push_to_rabbish_can(pSerialPort);
	}
}

void LBL_NetEngine_COMTransThread::slot_EstablishCOMConnection(LBL_NetEngine_TransThread* threadid, QString comName)
{
	if (threadid != this)
		return;
	QSerialPort* serial_client = nullptr;
	serial_client = new QSerialPort(this);

	if (serial_client)
	{
		serial_client->setBaudRate(QSerialPort::Baud115200);//设置波特率和读写方向
		serial_client->setDataBits(QSerialPort::Data8);		//数据位为8位
		serial_client->setFlowControl(QSerialPort::NoFlowControl);//无流控制
		serial_client->setParity(QSerialPort::NoParity);	//无校验位
		serial_client->setStopBits(QSerialPort::OneStop); //一位停止位
		if (serial_client->isOpen())
		{
			serial_client->clear();
			serial_client->close();
		}
		serial_client->setPortName(comName);
		if (!serial_client->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
		{
			qDebug() << tr("SerialPort Open Faild.") << tr(" SerialName:") << comName;
			push_to_rabbish_can(serial_client);
			return;
		}

		connect(serial_client, &QSerialPort::readyRead, this, &LBL_NetEngine_COMTransThread::slot_New_Data_Recieved/*, Qt::QueuedConnection*/);
		void (LBL_NetEngine_COMTransThread:: * displayError)(QSerialPort::SerialPortError) = &LBL_NetEngine_COMTransThread::slot_DisplayError;
		connect(serial_client, &QSerialPort::errorOccurred, this, displayError, Qt::QueuedConnection);
		connect(serial_client, &QSerialPort::bytesWritten, this, &LBL_NetEngine_COMTransThread::slot_Some_Data_Sended, Qt::QueuedConnection);

		m_mutex_protect.lock();
		m_clientList.insert(serial_client);
		m_mutex_protect.unlock();
		emit sig_NewCOMConnectionEstablish(serial_client, comName);
	}
	else
		Q_ASSERT(false);
}

void LBL_NetEngine_COMTransThread::slot_SendData(QObject * objSocket, LBLEnginePackage package)
{
	m_mutex_protect.lock();
	if (m_clientList.contains(objSocket) == false)
	{
		m_mutex_protect.unlock();
		return;
	}
	m_mutex_protect.unlock();
	QSerialPort * pSocket = qobject_cast<QSerialPort*>(objSocket);
	if (pSocket)
	{
		if (package.type() != m_communicatType || package.data().size() == 0)
		{
			qDebug() << "LBL_NetEngine_COMTransThread::slot_SendData------packageType can't matched or data is empty.";
			return;
		}
		QList<LBLEnginePackage> & list_sock_data = m_buffer_sending[pSocket];
		QList<qint64> & list_offset = m_buffer_sending_offset[pSocket];
		if (list_sock_data.empty() == true)
		{
			qint64 bytesWritten = pSocket->write(package.data().constData(),
				qMin(package.data().size(), m_nPayLoad));
			qDebug() << tr("Serial Port Send. Name:") << pSocket->portName() << tr(" Length:") << bytesWritten;
			if (bytesWritten < package.data().size())
			{
				list_sock_data.push_back(package);
				list_offset.push_back(bytesWritten);
			}
		}
		else
		{
			list_sock_data.push_back(package);
			list_offset.push_back(0);
		}
	}
}

void LBL_NetEngine_COMTransThread::slot_New_Data_Recieved()
{
	QSerialPort* pSocket = qobject_cast<QSerialPort*>(sender());
	if (pSocket)
	{
		LBLEnginePackage comPack(pSocket, m_communicatType, EPackageFromType::EPFT_Receive);
		int avilableCount = pSocket->bytesAvailable();
		if (avilableCount > 0)
		{
			QByteArray recFromData;
			recFromData = pSocket->readAll();
			comPack.setData(recFromData);
			comPack.setComName(pSocket->portName());
			if (comPack.data().isEmpty())
			{
				return;
			}
			else
			{
				emit sig_Data_Received(pSocket, comPack);
			}
		}
	}
}

void LBL_NetEngine_COMTransThread::slot_Some_Data_Sended(qint64 wsended)
{
	QSerialPort* pSocket = qobject_cast<QSerialPort*>(sender());
	if (pSocket)
	{
		QList<LBLEnginePackage> & list_sock_data = m_buffer_sending[pSocket];
		QList<qint64> & list_offset = m_buffer_sending_offset[pSocket];

		emit sig_Data_Sended(pSocket, wsended);
		while (list_sock_data.empty() == false)
		{
			LBLEnginePackage & arraySending = *list_sock_data.begin();
			if (arraySending.type() != m_communicatType || arraySending.data().size() == 0)
			{
				continue;
			}
			qint64 & currentOffset = *list_offset.begin();
			qint64 nTotalBytes = arraySending.data().size();
			Q_ASSERT(nTotalBytes >= currentOffset);
			qint64 nBytesWritten = pSocket->write(arraySending.data().constData() + currentOffset,
				qMin((int)(nTotalBytes - currentOffset), m_nPayLoad));
			currentOffset += nBytesWritten;
			if (currentOffset >= nTotalBytes)
			{
				list_offset.pop_front();
				list_sock_data.pop_front();
			}
			else
				break;
		}
	}
}

void LBL_NetEngine_COMTransThread::slot_DisplayError(QSerialPort::SerialPortError serialError)
{
	QSerialPort* pSocket = qobject_cast<QSerialPort*>(sender());
	if (pSocket)
	{
		qDebug() << pSocket->portName() << tr("(%1)..Error :%2.").arg((quint64)pSocket).arg(pSocket->errorString());
		emit sig_SocketError(pSocket, serialError);

		closeSocket(pSocket);
	}
}
