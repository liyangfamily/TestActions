#include "frmudpclient.h"
#include "ui_frmudpclient.h"
#include "quiwidget.h"
#include <string>
//#include <LBLCluster>
////#include <LBLInteCtrlPackage>
//#ifdef QT_DEBUG
//#pragma comment(lib,"LBL_CommunicatEngined.lib")
//#else
//#pragma comment(lib,"LBL_CommunicatEngine.lib")
//#endif // QT_DEBUG
//
//#include <LBLSCItemManager>
//#ifdef QT_DEBUG
//#pragma comment(lib,"LBL_SenderCardItemd.lib")
//#else
//#pragma comment(lib,"LBL_SenderCardItem.lib")
//#endif // QT_DEBUG
#include "progressmanager/progressmanager_p.h"
#include "progressmanager/progressview.h"
#include <QFutureInterface.h>
using namespace Core;
using namespace Core::Internal;
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LAPI_Controld.lib")
#else
#pragma comment(lib,"LAPI_Control.lib")
#endif // QT_DEBUG
#endif
frmUdpClient::frmUdpClient(QWidget *parent) : QWidget(parent), ui(new Ui::frmUdpClient)
{
	ui->setupUi(this);
	this->initForm();
	this->initConfig();
	quint16 m_test = 0xC205;
	QByteArray temp;
	temp.append((char *)&m_test, sizeof(quint16));

	connect(gCluster, &LBLCluster::sig_SendedDataSteam, this, &frmUdpClient::slot_SendData);
	connect(gCluster, &LBLCluster::sig_ParsingInteCtrlDataFrame, this, &frmUdpClient::slot_ReceiveData);
	connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_DetectComplit, this, &frmUdpClient::slot_DetectComplit);
	connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_SenderCardOnline, this, &frmUdpClient::slot_SenderCardOnline);
	connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_SenderCardOffline, this, &frmUdpClient::slot_SenderCardOffline);

	connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, this, &frmUdpClient::slotTableCellDoubleClicked);
	connect(ui->horizontalSlider, &QSlider::valueChanged, this, &frmUdpClient::slot_SliderValueChanged);
	gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadVideoSourceBrightness(), this);
	gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_SCReadBrightness(), this);
	gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadMCUAppVersion(), this);
	gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadMCUBootVersion(), this);
	gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadAndroidVersionNum(), this);
	gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadSCFPGARegister(), this);

	m_cb1 = std::bind(&frmUdpClient::test, this, std::placeholders::_1, std::placeholders::_2);

	initTable();

	m_pWatcher = new QFutureWatcher<void>(this);
	connect(m_pWatcher, SIGNAL(progressRangeChanged(int, int)), this, SLOT(rangeChanged(int, int)));
	connect(m_pWatcher, &QFutureWatcher<int>::progressValueChanged, [](int nVal) {
		qDebug() << "111111 => " << QThread::currentThreadId() << QThread::currentThread() << " " << nVal << endl;
	});
	connect(m_pWatcher, SIGNAL(finished()), this, SLOT(finished()));

	/*connect(&m_timer, &QTimer::timeout, [=]() {
		qDebug() << "watcher => " << QThread::currentThreadId() << QThread::currentThread() << " " << progress << endl; });*/
	connect(&m_timer, &QTimer::timeout, this, &frmUdpClient::timeout);
	ui->progressBar->setValue(0);
	ui->progressBar->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);  // 对齐方式  
	QStringList upgradeType;
	upgradeType << "发送卡MCU" << "发送卡FPGA" << "NT68400";
	ui->comboBox->addItems(upgradeType);

	connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_upgradeTypeChanged(int)));

	/*m_progressManager = new ProgressManagerPrivate;
	m_progressManager->progressView()->setParent(this);
	m_progressManager->init();*/
}

frmUdpClient::~frmUdpClient()
{
    delete ui;
	LAPI::ReadyExit();
	int maxWait = 0;
	while (!LAPI::CanExit())
	{
		QCoreApplication::processEvents();
		QThread::currentThread()->msleep(200);
		maxWait++;
		if (maxWait >= 150)
		{
			if (QMessageBox::information(0, tr("Confire Exit"),
				tr("There are still some clients alive in the server. continue waiting?"),
				QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
				maxWait = 0;
			else
				break;
		}
	}
}


void frmUdpClient::test(QObject* objSocket, LBLEnginePackage pack)
{
    Q_UNUSED(objSocket)
    Q_UNUSED(pack)
	ui->txtMain->clear();
	ui->txtMain->append("");
}

void frmUdpClient::test1()
{
	for (int i = 0; i < 50; ++i)
	{
		LAPI::WriteBrightness(50, false);
		progress += 2;
		//qDebug() << "test1 => " << QThread::currentThreadId() << QThread::currentThread() << " " << i << endl;
		QThread::msleep(1000);
	}
}

void frmUdpClient::initTable()
{
	QStringList headerText;
	headerText << "设备名" << "状态" << "连接方式" << "连接信息" << "Uuid"<<"internalUuid";  //表头标题用QStringList来表示
	ui->tableWidget->setColumnCount(headerText.count());//列数设置为与 headerText的行数相等
	ui->tableWidget->setHorizontalHeaderLabels(headerText); 
	ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	//ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui->tableWidget->horizontalHeader()->setHighlightSections(false);// 去掉选中表格时，列头的文字高亮
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //选择整行
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget->setColumnHidden(5, true);
}

void frmUdpClient::setTableData(const QList<LBL::SCItem::LBLAbstractSCItem*>& scItemList)
{
	if (ui->tableWidget->rowCount())
	{
		ui->tableWidget->clearContents();
		ui->tableWidget->setRowCount(0);
	}
	int rowCount = scItemList.size();
	if (!rowCount)
		return;
	//initTable();
	ui->tableWidget->setRowCount(rowCount);
	for (int i = 0; i < rowCount; ++i)
	{
		QTableWidgetItem* tableItem = nullptr;
		LBL::SCItem::LBLAbstractSCItem* scItem = scItemList.at(i);
		ui->tableWidget->setRowHeight(i, 36);

		//设备名
		tableItem = new QTableWidgetItem(scItem->senderCardTag());
		ui->tableWidget->setItem(i, 0, tableItem);
		tableItem->setTextAlignment(Qt::AlignCenter);
		//状态
		QString scItemStatus = scItem->senderCardStatus() == ESenderCardStatus::ESS_Online ? "在线" : "离线";
		tableItem = new QTableWidgetItem(scItemStatus);
		ui->tableWidget->setItem(i, 1, tableItem);
		tableItem->setTextAlignment(Qt::AlignCenter);
		tableItem->setTextColor(scItem->senderCardStatus() == ESenderCardStatus::ESS_Online ? QColor("green") : QColor("red"));
		//连接方式
		QString scItemCommunicatType;
		switch (scItem->communType())
		{
		case ECT_UDP:
			scItemCommunicatType = "UDP";
			break;
		case ECT_TCP:
			scItemCommunicatType = "TCP";
			break;
		case ECT_COM:
			scItemCommunicatType = "COM";
			break;
		default:
			break;
		}
		tableItem = new QTableWidgetItem(scItemCommunicatType);
		ui->tableWidget->setItem(i, 2, tableItem);
		tableItem->setTextAlignment(Qt::AlignCenter);
		//连接信息
		tableItem = new QTableWidgetItem(scItem->hostName());
		ui->tableWidget->setItem(i, 3, tableItem);
		tableItem->setTextAlignment(Qt::AlignCenter);
		//uuid
		tableItem = new QTableWidgetItem(scItem->itemUuid().toString(QUuid::WithoutBraces));
		ui->tableWidget->setItem(i, 4, tableItem);
		tableItem->setTextAlignment(Qt::AlignCenter);
		//uuid
		tableItem = new QTableWidgetItem(scItem->internalUuid().toString(QUuid::WithBraces));
		ui->tableWidget->setItem(i, 5, tableItem);
		tableItem->setTextAlignment(Qt::AlignCenter);
	}
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

bool frmUdpClient::event(QEvent * e)
{
	if (e->type() == LBLPackageEvent::s_disPatcherPackage_eventType)
	{
		LBLPackageEvent *tempE = static_cast<LBLPackageEvent*>(e);
		switch (tempE->cmdNum() - 1)
		{
		case LBLInteCtrlPackage::ECommand::EC_Read_VideoSourceBrightness:
		case LBLInteCtrlPackage::ECommand::EC_Read_SCBrightness:
		{
			onParseReadBrightness(tempE->package().data());
		}
		break;
		case LBLInteCtrlPackage::ECommand::EC_Read_MCUAppVersion:
		{
			onParseReadMCUAppVersion(tempE->package().data());
		}
		break;
		case LBLInteCtrlPackage::ECommand::EC_Read_MCUBootVersion:
		{
			onParseReadMCUBootVersion(tempE->package().data());
		}
		break;
		case LBLInteCtrlPackage::ECommand::EC_Read_SCFPGARegister:
		{
			onParseReadSCFPGARegister(tempE->package().data());
		}
		break;
		case LBLInteCtrlPackage::ECommand::EC_Read_AndroidVersion:
		{
			onParseReadAndroidVersion(tempE->package().data());
		}
		break;
		default:
			break;
		}
	}
	return QWidget::event(e);
}

void frmUdpClient::initForm()
{
    /*udpSocket = new QUdpSocket(this);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readData()));*/

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_btnSend_clicked()));

    ui->cboxInterval->addItems(App::Intervals);
    ui->cboxData->addItems(App::Datas);
}

void frmUdpClient::initConfig()
{
    ui->ckHexSend->setChecked(App::HexSendUdpClient);
    connect(ui->ckHexSend, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

    ui->ckHexReceive->setChecked(App::HexReceiveUdpClient);
    connect(ui->ckHexReceive, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

    ui->ckAscii->setChecked(App::AsciiUdpClient);
    connect(ui->ckAscii, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

    ui->ckDebug->setChecked(App::DebugUdpClient);
    connect(ui->ckDebug, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

    ui->ckAutoSend->setChecked(App::AutoSendUdpClient);
    connect(ui->ckAutoSend, SIGNAL(stateChanged(int)), this, SLOT(saveConfig()));

    ui->cboxInterval->setCurrentIndex(ui->cboxInterval->findText(QString::number(App::IntervalUdpClient)));
    connect(ui->cboxInterval, SIGNAL(currentIndexChanged(int)), this, SLOT(saveConfig()));

    ui->txtServerIP->setText(App::UdpServerIP);
    connect(ui->txtServerIP, SIGNAL(textChanged(QString)), this, SLOT(saveConfig()));

    ui->txtServerPort->setText(QString::number(App::UdpServerPort));
    connect(ui->txtServerPort, SIGNAL(textChanged(QString)), this, SLOT(saveConfig()));

    this->changeTimer();
}

void frmUdpClient::saveConfig()
{
    App::HexSendUdpClient = ui->ckHexSend->isChecked();
    App::HexReceiveUdpClient = ui->ckHexReceive->isChecked();
    App::AsciiUdpClient = ui->ckAscii->isChecked();
    App::DebugUdpClient = ui->ckDebug->isChecked();
    App::AutoSendUdpClient = ui->ckAutoSend->isChecked();
    App::IntervalUdpClient = ui->cboxInterval->currentText().toInt();
    App::UdpServerIP = ui->txtServerIP->text().trimmed();
    App::UdpServerPort = ui->txtServerPort->text().trimmed().toInt();
    App::writeConfig();
   // if(nullptr!= udpSocket)
    {
		/*emit sig_ConnectTo(QHostAddress::AnyIPv4, App::UdpServerPort);*/
        //udpSocket->bind(QHostAddress::AnyIPv4, App::UdpServerPort);
    }
    this->changeTimer();
}

void frmUdpClient::changeTimer()
{
    timer->setInterval(App::IntervalUdpClient);
    if (App::AutoSendUdpClient) {
        if (!timer->isActive()) {
            timer->start();
        }
    } else {
        if (timer->isActive()) {
            timer->stop();
        }
    }
}

void frmUdpClient::append(int type, const QString &data, bool clear)
{
    static int currentCount = 0;
    static int maxCount = 100;

    if (clear) {
        ui->txtMain->clear();
        currentCount = 0;
        return;
    }

    if (currentCount >= maxCount) {
        ui->txtMain->clear();
        currentCount = 0;
    }

    if (ui->ckShow->isChecked()) {
        return;
    }

    //过滤回车换行符
    QString strData = data;
    strData = strData.replace("\r", "");
    strData = strData.replace("\n", "");

    //不同类型不同颜色显示
    QString strType;
    if (type == 0) {
        strType = "发送";
        ui->txtMain->setTextColor(QColor("darkgreen"));
    } else {
        strType = "接收";
        ui->txtMain->setTextColor(QColor("red"));
    }

    strData = QString("时间[%1] %2: %3").arg(TIMEMS).arg(strType).arg(strData);
    ui->txtMain->append(strData);
    currentCount++;
}

void frmUdpClient::readData()
{
   /* QHostAddress host;
    quint16 port;
    QByteArray data;
    QString buffer;

    while (udpSocket->hasPendingDatagrams()) {
        data.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(data.data(), data.size(), &host, &port);

        if (App::HexReceiveUdpClient) {
            buffer = QUIHelper::byteArrayToHexStr(data);
        } else if (App::AsciiUdpClient) {
            buffer = QUIHelper::byteArrayToAsciiStr(data);
        } else {
            buffer = QString(data);
        }

        QString ip = host.toString();
        ip = ip.replace("::ffff:", "");
        if (ip.isEmpty()) {
            continue;
        }

        QString str = QString("[%1:%2] %3").arg(ip).arg(port).arg(buffer);
        append(1, str);

        if (App::DebugUdpClient) {
            int count = App::Keys.count();
            for (int i = 0; i < count; i++) {
                if (App::Keys.at(i) == buffer) {
                    sendData(ip, port, App::Values.at(i));
                    break;
                }
            }
        }
    }*/
}

void frmUdpClient::sendData(const QString &ip, int port, const QString &data)
{
    Q_UNUSED(ip)
    Q_UNUSED(port)
	/*if (nullptr == udpSocket)
	{
		qDebug() << ("No Connection.");
		return;
	}*/
    QByteArray buffer;
    if (App::HexSendUdpClient) {
        buffer = QUIHelper::hexStrToByteArray(data);
    } else if (App::AsciiUdpClient) {
        buffer = QUIHelper::asciiStrToByteArray(data);
    } else {
        buffer = data.toLatin1();
    }

	/*LBL_Protocol_Package_IntegratedCtrl package;
	package.packageHeader.targetDeviceType = LBL_Protocol_Package_IntegratedCtrl::EDeviceType::EDT_Android;
	package.packageHeader.cmd = LBL_Protocol_Package_IntegratedCtrl::ECommand::EC_Write_QueryOnlineStatus;
	QByteArray writeData = package.toByteArray();

	SPackage pack(udpSocket, EPackageType::EPT_UDP);
	pack.setUdpInfo(QHostAddress(ip), port);
	pack.setData(writeData);

	emit sig_SendeData(udpSocket, pack);

	QString str = QString("[%1:%2] %3").arg(ip).arg(port).arg(QUIHelper::byteArrayToHexStr(writeData));

	LBL_Protocol_Package_IntegratedCtrl package2;
	package2.fromByteArray(writeData);*/
	/*gSCItemMgr->startCheckHeartBeating();*/
    //append(0, str);
}

void frmUdpClient::slot_NewConnectionEstablish(QObject * objSocket, const QHostAddress & addr, quint16 port)
{
    Q_UNUSED(addr)
    Q_UNUSED(port)
	if (nullptr == objSocket)
	{
		return;
	}
	udpSocket = objSocket;
}

void frmUdpClient::slot_ReceiveData(QObject * objSocket, LBLEnginePackage pack)
{
    Q_UNUSED(objSocket)
	//m_cb1(objSocket, pack);
	QString buffer;
	if (App::HexReceiveUdpClient) {
		buffer = QUIHelper::byteArrayToHexStr(pack.data());
	}
	else if (App::AsciiUdpClient) {
		buffer = QUIHelper::byteArrayToAsciiStr(pack.data());
	}
	else {
		buffer = QString(pack.data());
	}
	QString ip;
	ip = pack.hostName();
	ip = ip.replace("::ffff:", "");
	if (ip.isEmpty()) {
		return;
	}
	QString str = QString("[%1] %2").arg(ip).arg(buffer);
	append(1, str);

}


void frmUdpClient::slot_SendData(QObject* objSocket, LBLEnginePackage pack)
{
    Q_UNUSED(objSocket)
	QString buffer;
	if (App::HexReceiveUdpClient) {
		buffer = QUIHelper::byteArrayToHexStr(pack.data());
	}
	else if (App::AsciiUdpClient) {
		buffer = QUIHelper::byteArrayToAsciiStr(pack.data());
	}
	else {
		buffer = QString(pack.data());
	}
	QString ip;
	ip = pack.hostName();
	ip = ip.replace("::ffff:", "");
	if (ip.isEmpty()) {
		return;
	}
	QString str = QString("[%1] %2").arg(ip).arg(buffer);
	append(0, str);
}

void frmUdpClient::slot_SocketAbort(QObject* objSocket)
{
	if (objSocket == udpSocket)
	{
		qDebug() << ("disConnected.");
		udpSocket = nullptr;
	}
}

void frmUdpClient::slot_SenderCardOnline(SDetectItemInfo info)
{
	qDebug() << "++++++++++slot_SenderCardOnline::" << info.hostName;
}

void frmUdpClient::slot_SenderCardOffline(SDetectItemInfo info)
{
	qDebug() << "----------slot_SenderCardOffline::" << info.hostName;
}

void frmUdpClient::slot_DetectComplit()
{
	QList<LBL::SCItem::LBLAbstractSCItem*> itemList;
	itemList = LAPI::GetAllItemList();
	setTableData(itemList);
	return;
}

void frmUdpClient::slotTableCellDoubleClicked(int row, int column)
{
    Q_UNUSED(column)
	QString  internalUuidStr = ui->tableWidget->item(row, 5)->text();
	QUuid internalUuid = QUuid::fromString(internalUuidStr);
	LAPI::SetUsingItemByInternalUuid(internalUuid);
}

quint16 frmUdpClient::onParseReadBrightness(const QByteArray & data)
{
	LBLPackageInteCtrl_ReadVideoSourceBrightness pack(data);
	ui->horizontalSlider->setValue(pack.getBrightness());
	return LBLPackage::EOR_Success;
}

quint16 frmUdpClient::onParseReadMCUAppVersion(const QByteArray & data)
{
	LBLPackageInteCtrl_ReadMCUAppVersion pack(data);
	ui->textEdit->append(QString::fromLocal8Bit("MCU App：%1\n").arg(pack.getVersion()));
	return LBLPackage::EOR_Success;
}

quint16 frmUdpClient::onParseReadMCUBootVersion(const QByteArray & data)
{
	LBLPackageInteCtrl_ReadMCUBootVersion pack(data);
	ui->textEdit->append(QString::fromLocal8Bit("MCU Boot：%1\n").arg(pack.getVersion()));
	return LBLPackage::EOR_Success;
}

quint16 frmUdpClient::onParseReadAndroidVersion(const QByteArray & data)
{
	LBLPackageInteCtrl_ReadAndroidVersionNum pack(data);
	QByteArray replyData = pack.getReplyData();
	quint16 len = 0;
	memcpy_s(&len, 2, replyData.constData(), 2);
	QString name(replyData.mid(2, len));
	ui->textEdit->append(QString::fromLocal8Bit("Android版本：%1\n").arg(name));
	return LBLPackage::EOR_Success;
}

quint16 frmUdpClient::onParseReadSCFPGARegister(const QByteArray & data)
{
    LBLPackageInteCtrl_ReadSCFPGARegister pack(data);
	QByteArray packData = pack.getReplyData();
	switch (pack.getAddress())
	{
	case LBL::SC::ENormalSettingRegAddrs::ENSRA_FPGABigVersion:
	{
		QString version;
		version = LAPI::GetSCFPGAVersion();
		ui->textEdit->append(QString::fromLocal8Bit("FPGA Version：%1\n").arg(version));
		return LBLPackage::EOR_Success;
	}
	break;
	default:
		break;
	}
	return 0;
}

void frmUdpClient::rangeChanged(int a, int b)
{
    Q_UNUSED(a)
    Q_UNUSED(b)
}

void frmUdpClient::valueChanged(int a)
{
	qDebug() << "value" << a;
}

void frmUdpClient::finished()
{
}

void frmUdpClient::timeout()
{
	if (!LAPI::IsUpgradeFinished())
	{
		//qDebug() << "watcher => Progeress:" << LAPI::upgradeProgress() << " " << "Status:" << QString::number(LAPI::upgradeStatus(), 16) << endl;
		QString statusStr;
		switch (LAPI::UpgradeStatus())
		{
		case LBLFileTransferPackage::EUS_NULL:
			break;
		case LBLFileTransferPackage::EUS_Erase:
			statusStr = QString::fromLocal8Bit("擦除中...");
			break;
		case LBLFileTransferPackage::EUS_Upgaradeing:
			statusStr = QString::fromLocal8Bit("升级中...");
			break;
		case LBLFileTransferPackage::EUS_Rebooting:
			statusStr = QString::fromLocal8Bit("重启中...");
			break;
		case LBLFileTransferPackage::EUS_UpgaradeSucess:
			statusStr = QString::fromLocal8Bit("升级成功");
			break;
		case LBLFileTransferPackage::EUS_UpgaradeFaild:
			statusStr = QString::fromLocal8Bit("升级失败");
			break;
		case LBLFileTransferPackage::EUS_ConnectionBeingEstablished:
			statusStr = QString::fromLocal8Bit("建立连接中...");
			break;
		case LBLFileTransferPackage::EUS_TransferringData:
			statusStr = QString::fromLocal8Bit("数据传输中...");
			break;
		case LBLFileTransferPackage::EUS_Waitting:
			statusStr = QString::fromLocal8Bit("等待中...");
			break;
		default:
			break;
		}
		int value = LAPI::UpgradeProgress();
		ui->progressBar->setValue(value);
		ui->progressBar->setFormat(QString::fromLocal8Bit("%1 , 当前进度为：%2%").arg(statusStr).arg(value));
	}
	else
	{
		if (LAPI::EResult::ER_FILE_UpgradeStatus_Success == LAPI::UpgradeResult())
		{
			ui->progressBar->setValue(100);
			ui->progressBar->setFormat(QString::fromLocal8Bit("升级成功")); 
			
		}
		else
		{
			ui->progressBar->setFormat(QString::fromLocal8Bit("升级失败, 错误代码: 0x%1").arg(QString::number(LAPI::UpgradeResult(), 16)).toUpper());
		}
		m_timer.stop();
		//qDebug() << "watcher => Result:" << QString::number(LAPI::upgradeResult(), 16) << endl;
	}
}

void frmUdpClient::slot_upgradeTypeChanged(int index)
{
	switch (index)
	{
	case 0:
		m_upgradeType= LBLFileTransferPackage::EFileType::EFT_SenderMCU;
		break;
	case 1:
		m_upgradeType = LBLFileTransferPackage::EFileType::EFT_SenderFPGA;
		break;
	case 2:
		m_upgradeType = LBLFileTransferPackage::EFileType::EFT_SenderMonitor;
		break;
	default:
		break;
	}
}

void frmUdpClient::slot_SliderValueChanged(int value)
{
    LAPI::WriteBrightness(value);
}

void frmUdpClient::on_btnOpen_clicked()
{
	/*LBLSyncWaiter waiter(this, SIGNAL(sig_test(quint16, quint16)), 0x16, 0x15);
	waiter.wait(20000);
	int i = 0;
	return;*/
//	QString str1 = ui->labServerIP->text();
	QTextCodec *utf8 = QTextCodec::codecForLocale();
	QByteArray name = utf8->name();
	QString qstr("远程地址");
    std::string str = qstr.toLocal8Bit().data();
	std::string str1 = qstr.toStdString();
	QString testStr = QString::fromStdString(str1);
	std::wstring str2 = qstr.toStdWString();
	//emit sig_ConnectTo(QHostAddress::AnyIPv4, App::UdpServerPort);
	LAPI::StartDetectServer();
}


void frmUdpClient::on_btnClose_clicked()
{
	m_pWatcher->cancel();
	m_pWatcher->waitForFinished();
	/*gSCItemMgr->test();
	return;*/
	/*emit sig_test(0x16, 0x15);
	return;*/
	/*if (nullptr == udpSocket)
	{
		qDebug() << ("No Connection.");
		return;
	}*/
	//qCluster->slot_Disconnect(udpSocket);
	//qCluster->netEngine()->disconnectAll();
	LAPI::StoptDetectServer();
}

void frmUdpClient::on_btnSave_clicked()
{
	QString data = ui->txtMain->toPlainText();
	if (data.length() <= 0) {
		return;
	}

	QString fileName = QString("%1/%2.txt").arg(QUIHelper::appPath()).arg(STRDATETIME);
	QFile file(fileName);
	if (file.open(QFile::WriteOnly | QFile::Text)) {
		file.write(data.toUtf8());
		file.close();
	}

	on_btnClear_clicked();
}

void frmUdpClient::on_btnClear_clicked()
{
    append(0, "", true);
}

void frmUdpClient::on_btnSend_clicked()
{
    QString data = ui->cboxData->currentText();
    if (data.length() <= 0) {
        return;
    }
	data.remove(QRegExp("\\s"));
    sendData(App::UdpServerIP, App::UdpServerPort, data);
}

void frmUdpClient::on_pushButton_clicked()
{
	LAPI::ReadBrightness();
}

void frmUdpClient::on_pushButton_2_clicked()
{
	QHBoxLayout* hLayout = new QHBoxLayout(this);
	hLayout->setContentsMargins(0, 0, 0, 2);
	hLayout->setSpacing(0);
	hLayout->addWidget(m_progressManager->statusBarWidget());
	ui->widget_3->setLayout(hLayout);

	QFutureInterface<void>* m_fakeFutureInterface = new QFutureInterface<void>(QFutureInterfaceBase::Running);
	QFuture<void> future = m_fakeFutureInterface->future();
	m_fakeFutureInterface->setProgressRange(0, 100);
	m_fakeFutureInterface->setProgressValue(50);
	//m_futureWatcher.setFuture(future);
	const Core::FutureProgress *progress = Core::ProgressManager::addTask(
		future, QObject::tr("Cppcheck"), "AutoTest.Task.Index");
	
	//ProgressManager::instance()->cancelTasks(Utils::Id());
	/*ProgressBar* summaryProgressBar = new ProgressBar();
	summaryProgressBar->setMinimumWidth(70);
	summaryProgressBar->setTitleVisible(true);
	summaryProgressBar->setSeparatorVisible(true);
	summaryProgressBar->setCancelEnabled(true);
	summaryProgressBar->setRange(0, 100);
	summaryProgressBar->setValue(50);
	summaryProgressBar->show();
	summaryProgressBar->setError(false);
	summaryProgressBar->setFinished(true);*/
	return;
	LBLUIHelper::appRunTimeDataLocation();
	QString fileName1 = QFileDialog::getOpenFileName(this,
		tr("文件选择"),
		App::lastOpenPath,
		tr("bin文件(*.bin)"));
	if (!fileName1.isEmpty()) {
		App::lastOpenPath = fileName1;
		App::writeConfig();
        m_timer.start(500);
        LAPI::UpgradeFile(m_upgradeType, fileName1);

//		QFile file(fileName1);
//		if (!file.open(QIODevice::ReadOnly))
//			return;
//		QByteArray data = file.readAll();
//		LBLConnection connection;
//		connection.parseConnectionData(data);
//		file.close();

//		QString filePath = QFileDialog::getSaveFileName(nullptr,
//			tr("文件保存"),
//			App::lastOpenPath,
//			tr("bin文件(*.bin)"));
//		if (filePath.isEmpty())
//			return;
//		QFile file1(filePath);
//		if (!file1.open(QIODevice::WriteOnly))
//			return;
//		file1.write(
//			connection.buildConnectionDataV0());
//		file1.close();
	}
	return;
}

void frmUdpClient::on_pushButton_3_clicked()
{
	LAPI::CancelUpgrade();
	return;
}

void frmUdpClient::on_pushButton_4_clicked()
{
	ui->textEdit->clear();
	LAPI::ReadMCUAppVersion();
	LAPI::ReadMCUBootVersion();
	LAPI::ReadSCFPGAVersion();
	LAPI::ReadAndroidVersion();
	/*LAPI::ReadConnection();
	LBLConnection* connection = LAPI::GetConnection();
    if(connection)
        connection->getPort(0).index();*/
	/*LAPI::readSCFPGAEthLoad(true);
	QList<LBL::SC::LBLSPortArea> portAreaList = LAPI::getSCFPGAEthLoad();
    LAPI::writeSCFPGAEthLoad(portAreaList);*/
}

