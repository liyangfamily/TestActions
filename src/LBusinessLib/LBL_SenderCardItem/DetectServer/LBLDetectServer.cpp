/*********************************************************************************************************
** This file is part of the LBL_SenderCardItem module of the LBL Toolkit.
*********************************************************************************************************/

/*!
\class LBLDetectServer

\inmodule LBL_SenderCardItem

\brief The class is the service responsible for detecting all online senderCard.
it will detect all network and serial deveices and send the card status detection command.

\code

\endcode

\note:

*/

#include "LBLDetectServer.h" 

#include <LBL_CommunicatEngine/LBLPackageDispatcher>
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_CommunicatEngined.lib")
#else
#pragma comment(lib,"LBL_CommunicatEngine.lib")
#endif // QT_DEBUG
#endif

#include <QSerialPortInfo>
#include <QNetworkInterface>

int LBLDetectServer::m_detectCount;

LBLDetectServer::LBLDetectServer(QObject *parent)
	: QObject(parent)
{
	connect(this, QOverload<const QString&, quint16>::of(&LBLDetectServer::sig_ConnectToUDP),
		gCluster, QOverload<const QString&, quint16>::of(&LBLCluster::slot_ConnectToUDP));
	connect(this, QOverload<QString>::of(&LBLDetectServer::sig_ConnectToCOM),
		gCluster, QOverload<QString>::of(&LBLCluster::slot_ConnectToCOM));

	gDispatcher->registerTransitObject(this);

	connect(&m_singleDetectTimer, &QTimer::timeout, this, &LBLDetectServer::slot_detectTimeOut);
	connect(&m_detectServerTimer, &QTimer::timeout, [this]() {
		this->slot_startDetectServer(); });
	connect(gCluster, QOverload<QObject*, QSerialPort::SerialPortError>::of(&LBLCluster::sig_SocketError),
        [=](QObject * objSocket) {
		emit sig_DisconnectFromCOM(objSocket); });
	connect(&m_checkHeartBeatingTimer, &QTimer::timeout, gCluster, &LBLCluster::slot_KickDeadClients);

	m_manager.registerPackage(LBLPackageInteCtrl_DetectInfo(), std::bind(&LBLDetectServer::onParsingInteCtrlDetectInfo, this, std::placeholders::_1));
}

LBLDetectServer::~LBLDetectServer()
{
	gDispatcher->unregisterTransitObject(this);
}

const QList<SDetectItemInfo>& LBLDetectServer::getDetectInfoList()
{
	QMutexLocker locker(&m_mutex_protect);
	return m_detectList;
}

bool LBLDetectServer::slot_startDetectServer(quint16 detectIntervalTime/* = 1 * 1000*/, quint16 everyDetectIntervalTime/* = 30 * 1000*/, quint16 everyDetectCount/* = 2*/)
{
	QMutexLocker locker(&m_mutex_protect);
	if (!m_singleDetectTimer.isActive())
	{
		m_detectIntervalTime = detectIntervalTime;
		m_everyDetectIntervalTime = everyDetectIntervalTime;
		m_detectCount = everyDetectCount;
		qDebug() << ">>>>>>>>>>>>>>>>>>Start Detect SenderCard.";
		m_detectCount = 0;
		m_detectList.clear();
		prepareNetDevice();
		prepareComDevice();
        m_singleDetectTimer.start(detectIntervalTime);
		m_detectServerTimer.stop();
        emit sig_StartDetect();
		return true;
	}
	return false;
}

void LBLDetectServer::slot_stopDetectServer()
{
	QMutexLocker locker(&m_mutex_protect);
	if (m_singleDetectTimer.isActive())
	{
		m_singleDetectTimer.stop();
	}
	if (m_detectServerTimer.isActive())
	{
		m_detectServerTimer.stop();
	}
    //qDebug() << "<<<<<<<<<<<<<<<<<<<Stop Detect SenderCard.";
}

bool LBLDetectServer::event(QEvent * e)
{
	if (e->type() == LBLPackageEvent::s_transitPackage_eventType)
	{
		LBLPackageEvent *tempE = static_cast<LBLPackageEvent*>(e);

		slot_ParsingDataFrame(tempE->package().socketObj(), tempE->package());
	}
	return QObject::event(e);
}

void LBLDetectServer::checkHeartBeating(int msec)
{
	QMutexLocker locker(&m_mutex_protect);
	m_checkHeartBeatingTimer.stop();
	m_checkHeartBeatingTimer.start(msec);
}

void LBLDetectServer::prepareComDevice()
{
	QStringList portDescriptionList;
	portDescriptionList.append("Silicon Labs CP210x USB to UART Bridge");
	portDescriptionList.append("Prolific PL2303GC USB Serial COM Port");
	portDescriptionList.append("Prolific USB-to-Serial Comm Port");
#ifdef Q_OS_MACOS
    portDescriptionList.append("USB-Serial Controller ");
#endif

	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
		if (portDescriptionList.contains(info.description()))
		{
			qDebug() << " Find serialPortName:" << info.portName();
			emit sig_ConnectToCOM(info.portName());
		}
	}
}

void LBLDetectServer::prepareNetDevice()
{
	/*emit sig_ConnectToUDP(QHostAddress("172.19.150.20"), 8600);
	return;*/
	QList<QNetworkInterface> _interfaceList = QNetworkInterface::allInterfaces();
	foreach(QNetworkInterface _interface, _interfaceList) {
		QString str = _interface.humanReadableName();
		if (_interface.flags().testFlag(QNetworkInterface::IsUp)
			&& _interface.flags().testFlag(QNetworkInterface::IsRunning)
			&& _interface.flags().testFlag(QNetworkInterface::CanBroadcast)
			&& _interface.flags().testFlag(QNetworkInterface::CanMulticast)
			&& !_interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
			QList<QNetworkAddressEntry> _entryList = _interface.addressEntries();
			foreach(QNetworkAddressEntry _entry, _entryList) {
				if (_entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
					QString tempIP = _entry.ip().toString();

					qDebug() << " Find UdpPortIP:" << tempIP;
					emit sig_ConnectToUDP(_entry.ip().toString(), 8600);
				}
			}
		}
	}
}

quint16 LBLDetectServer::onParsingInteCtrlDetectInfo(const QByteArray& data)
{
	LBLPackageInteCtrl_DetectInfo package(data);
	m_curDetectInfo.senderCardStatus = (ESenderCardStatus)package.getStatus();
	m_curDetectInfo.senderCardClass = (ESenderCardClass)package.getSenderCardClass();
	m_curDetectInfo.productType = (EProductType)package.getProductType();
	m_curDetectInfo.uuidType = package.getUuidType();
	m_curDetectInfo.uuid = package.getUuid();
	m_curDetectInfo.senderCardIndex = package.getSenderCardIndex();
	m_curDetectInfo.sourceDeviceType = package.getSourceDevice();
	return LBLPackage::EOR_Success;
}

void LBLDetectServer::slot_ParsingDataFrame(QObject* objSocket, LBLEnginePackage pack)
{
	if (nullptr == objSocket || pack.isEmpty())
	{
		qDebug() << "LBLDetectServer::slot_ParsingDataFrame Can't ParsingPackage.";
		return;
	}
	
	m_curDetectInfo.clear();
	m_curDetectInfo.detectType = EDeviceDetectType::EDDT_AUTO;
	m_curDetectInfo.socketObj = objSocket;
	m_curDetectInfo.hostName = pack.hostName();
	switch (pack.type())
	{
    case ECT_NULL:
		qDebug() << "LBLDetectServer::slot_ParsingDataFrame------package type Error.";
		break;
	case ECT_UDP:
	{
		m_curDetectInfo.communType =ECommunicatType::ECT_UDP;
		m_curDetectInfo.netInfo.ipAddr = pack.hostAddress();
		m_curDetectInfo.netInfo.port = pack.hostPort();

	}
	break;
	case ECT_TCP:
	{
		m_curDetectInfo.communType = ECommunicatType::ECT_TCP;
		m_curDetectInfo.netInfo.ipAddr = pack.hostAddress();
		m_curDetectInfo.netInfo.port = pack.hostPort();
		
	}
		break;
	case ECT_COM:
	{
		m_curDetectInfo.communType = ECommunicatType::ECT_COM;
		m_curDetectInfo.comInfo.comName = pack.comName();
	}
		break;
	default:
		break;
	}
	LBLPackage tempPackage(pack.data());
	if (m_manager.handle(tempPackage))
	{
		if (m_curDetectInfo.senderCardStatus != ESenderCardStatus::ESS_Online)
		{
			qDebug() << "LBLDetectServer::slot_ParsingDataFrame SenderCardStatus Problem.";
            //return;
		}
		if (!m_detectList.contains(m_curDetectInfo))
		{
			m_detectList.append(m_curDetectInfo);
		}
	}
}

void LBLDetectServer::slot_detectTimeOut()
{
	if (m_detectCount < m_targetDetectCount)
	{
		if (0!=m_detectCount) {
			emit sig_SingleDetectComplite(); //此策略主要为了解决探卡信息需要额外的设备名和UUID，单次探完就去更新信息，这样子可以在探卡完成时显示所有信息。
		}
		gCluster->slot_SendHelloPackage();
		m_singleDetectTimer.start(m_detectIntervalTime);
		m_detectCount++;
	}
	else
	{
		m_detectCount = 0;
		if (m_singleDetectTimer.isActive())
		{
			m_singleDetectTimer.stop();
		}
		if (!m_detectServerTimer.isActive())
		{
			m_detectServerTimer.start(m_everyDetectIntervalTime);
		}
		emit sig_DetectComplite();
		//checkHeartBeating();
        qDebug() << "<<<<<<<<<<<<<<<<<<Detect Size: " << m_detectList.size();
		//探卡完成
	}
}
