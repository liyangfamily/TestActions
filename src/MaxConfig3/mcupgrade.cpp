#include "mcupgrade.h"
#include "ui_mcupgrade.h"
#include <QStyledItemDelegate>
#include <QFileDialog>
#include "app.h"

MCUpgrade::MCUpgrade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MCUpgrade)
{
    ui->setupUi(this);

	gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadMCUAppVersion(), this);
	gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadMCUBootVersion(), this);
	gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadAndroidVersionNum(), this);
	gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadSCFPGARegister(), this);
	gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_Penetrate(), this);

	QStringList upgradeType;
	upgradeType << "SenderCard-MCU" << "SenderCard-FPGA" << "ReceiveCard-FPGA" << "HDMI Decoding Chip" << "16BitGamma" << "16BitGamma_512Byte";
	ui->comboBoxUpgradeType->addItems(upgradeType);

	QStyledItemDelegate *delegate = new QStyledItemDelegate(ui->comboBoxUpgradeType);
	ui->comboBoxUpgradeType->setItemDelegate(delegate);
	 
	connect(ui->comboBoxUpgradeType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_upgradeTypeChanged(int)));

	connect(&m_upgradeWatcher, &QFutureWatcher<quint16>::finished,
		this, &MCUpgrade::onUpgradeFinished);

	connect(&m_upgradeWatcher, &QFutureWatcherBase::progressValueChanged,
		this, &MCUpgrade::updateUpgardeProgressBar);
	connect(&m_upgradeWatcher, &QFutureWatcherBase::progressTextChanged,
		this, &MCUpgrade::updateUpgardeProgressBar);
}

MCUpgrade::~MCUpgrade()
{
    delete ui;

	gDispatcher->unregisterDispatcherPackage(LBLPackageInteCtrl_ReadMCUAppVersion(), this);
	gDispatcher->unregisterDispatcherPackage(LBLPackageInteCtrl_ReadMCUBootVersion(), this);
	gDispatcher->unregisterDispatcherPackage(LBLPackageInteCtrl_ReadAndroidVersionNum(), this);
	gDispatcher->unregisterDispatcherPackage(LBLPackageInteCtrl_ReadSCFPGARegister(), this);
}

bool MCUpgrade::event(QEvent *e)
{
	if (e->type() == LBLPackageEvent::s_disPatcherPackage_eventType)
	{
		LBLPackageEvent *tempE = static_cast<LBLPackageEvent*>(e);
		switch (tempE->cmdNum() - 1)
		{
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
		case LBLInteCtrlPackage::ECommand::EC_NULL_Penetrate:
		{
			if (tempE->sourceDevice() == LBLPackage::EDeviceType::EDT_Android) {
				onParseNT68400Data(tempE->package().data());
			}
		}
		break;
		default:
			break;
		}
	}
	return QWidget::event(e);
}

void MCUpgrade::cleanUpgradeWidget()
{
	ui->labelMCUVer->clear();
	ui->labelAndroidVer->clear();
	ui->labelSCFPGAVer->clear();
	ui->labelFilePathInfo->clear();
	ui->progressBarUpgrade->setValue(0);
	ui->progressBarUpgrade->setFormat(tr("0%"));
}

void MCUpgrade::updateUpgrade()
{
	LAPI::ReadMCUAppVersion();
	LAPI::ReadMCUBootVersion();
	LAPI::ReadSCFPGAVersion();
	LAPI::ReadAndroidVersion(); 
	LAPI::ReadHDMIVersion(true);
	QString nt68400Version = LAPI::GetHDMIVersion();
	ui->labelHDMIVer->setText(nt68400Version);
	if (LAPI::IsUpgrading()) {
		m_upgradeWatcher.blockSignals(false);
		m_upgradeWatcher.setFuture(LAPI::UpgradeFuture());
		ui->btnUpgrade->setText(tr("Cancel"));
	}
	else {
		m_upgradeWatcher.blockSignals(true);
		m_upgradeWatcher.setFuture(QFuture<quint16>());
		ui->btnUpgrade->setText(tr("Upgrade"));
	}
}

quint16 MCUpgrade::onParseReadMCUAppVersion(const QByteArray& data)
{
	LBLPackageInteCtrl_ReadMCUAppVersion pack(data);
	ui->labelMCUVer->setText(tr("%1").arg(pack.getVersion()));
	return LBLPackage::EOR_Success;
}

quint16 MCUpgrade::onParseReadMCUBootVersion(const QByteArray& data)
{
	LBLPackageInteCtrl_ReadMCUBootVersion pack(data);
	//ui->textEdit->append(tr("MCU Boot：%1\n").arg(pack.getVersion()));
	return LBLPackage::EOR_Success;
}

quint16 MCUpgrade::onParseReadAndroidVersion(const QByteArray& data)
{
	LBLPackageInteCtrl_ReadAndroidVersionNum pack(data);
	QByteArray replyData = pack.getReplyData();
	quint16 len = 0;
	memcpy_s(&len, 2, replyData.constData(), 2);
	QString name(replyData.mid(2, len));
	ui->labelAndroidVer->setText(tr("%1").arg(name));
	return LBLPackage::EOR_Success;
}

quint16 MCUpgrade::onParseReadSCFPGARegister(const QByteArray& data)
{
	LBLPackageInteCtrl_ReadSCFPGARegister pack(data);
	QByteArray packData = pack.getReplyData();
	switch (pack.getAddress())
	{
	case LBL::SC::ENormalSettingRegAddrs::ENSRA_FPGABigVersion:
	{
		QString version;
		version = LAPI::GetSCFPGAVersion();
		ui->labelSCFPGAVer->setText(tr("%1").arg(version));
		return LBLPackage::EOR_Success;
	}
	break;
	default:
		break;
	}
	return 0;
}

quint16 MCUpgrade::onParseNT68400Data(const QByteArray& data)
{
	LBLPackageInteCtrl_Penetrate pack(data);
	QByteArray packData = pack.getReplyData();
	QString nt68400Version = LAPI::GetHDMIVersion();
	//ui->labelHDMIVer->setText(nt68400Version);
	return 0;
}

void MCUpgrade::slot_ConnectItem()
{
	cleanUpgradeWidget();
	updateUpgrade();
}

void MCUpgrade::slot_EnterNavigatPage()
{
	updateUpgrade();
}

void MCUpgrade::on_btnSelectFile_clicked()
{
	LBLUIHelper::appRunTimeDataLocation();
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Select File"),
		App::lastOpenPath,
		tr("Upgrade File(*.bin)"));
	if (!fileName.isEmpty()) {
	//QString fileName = App::lastOpenPath;
		ui->labelFilePathInfo->setText(fileName);
		App::lastOpenPath = fileName;
		App::writeConfig();
	}
	return;
}

void MCUpgrade::on_btnUpgrade_clicked()
{
	if (ui->btnUpgrade->text() == tr("Upgrade")) {
		QString fileName = ui->labelFilePathInfo->text();
		if (!fileName.isEmpty()) {
			if (LAPI::EResult::ER_Success == LAPI::UpgradeFile(m_upgradeType, fileName)) {
				m_upgradeWatcher.blockSignals(false);
				m_upgradeWatcher.setFuture(LAPI::UpgradeFuture());
				ui->btnUpgrade->setText(tr("Cancel"));
			}
		}
	}
	else{
		LAPI::CancelUpgrade();
		ui->btnUpgrade->setText(tr("Canceling..."));
		ui->btnUpgrade->setEnabled(false);
	}
}

void MCUpgrade::on_btnClearFilePath_clicked()
{
	ui->labelFilePathInfo->clear();
}

void MCUpgrade::slot_upgradeTypeChanged(int index)
{
	switch (index)
	{
	case 0:
		m_upgradeType = LBLFileTransferPackage::EFileType::EFT_SenderMCU;
		break;
	case 1:
		m_upgradeType = LBLFileTransferPackage::EFileType::EFT_SenderFPGA;
		break;
	case 2:
		m_upgradeType = LBLFileTransferPackage::EFileType::EFT_ReciverFPGA;
		break;
	case 3:
		m_upgradeType = LBLFileTransferPackage::EFileType::EFT_SenderMonitor;
		break;
	case 4:
		m_upgradeType = LBLFileTransferPackage::EFileType::EFT_GammaFile;
		break;
	case 5:
		m_upgradeType = LBLFileTransferPackage::EFileType::EFT_GammaFile_512B;
		break;
	default:
		break;
	}
}

void MCUpgrade::onUpgradeFinished()
{
	ui->btnUpgrade->setText(tr("Upgrade"));
	ui->btnUpgrade->setEnabled(true);
	m_upgradeWatcher.blockSignals(true);
}

void MCUpgrade::updateUpgardeProgressBar()
{
	ui->progressBarUpgrade->setValue(m_upgradeWatcher.progressValue());
	if (m_upgradeWatcher.isRunning()) {
		ui->progressBarUpgrade->setFormat(tr("%1 ,Progress：%2%").arg(m_upgradeWatcher.progressText()).arg(m_upgradeWatcher.progressValue()));
	}
	else {
		ui->progressBarUpgrade->setFormat(m_upgradeWatcher.progressText());
	}
}
