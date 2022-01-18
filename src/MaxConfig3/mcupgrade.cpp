#include "mcupgrade.h"
#include "ui_mcupgrade.h"
#include <QStyledItemDelegate>
#include <QFileDialog>
#include "app.h"

#include "ConnectionControl/connectionView.h"
#include "ConnectionControl/connectionScene.h"

#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif

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

    ui->comboBoxUpgradeType->addItem(tr("SenderCard-MCU"),LBLFileTransferPackage::EFileType::EFT_SenderMCU);
    ui->comboBoxUpgradeType->addItem(tr("SenderCard-FPGA"),LBLFileTransferPackage::EFileType::EFT_SenderFPGA);
    ui->comboBoxUpgradeType->addItem(tr("ReceiveCard-MCU"),LBLFileTransferPackage::EFileType::EFT_ReciverMCU);
    ui->comboBoxUpgradeType->addItem(tr("ReceiveCard-FPGA"),LBLFileTransferPackage::EFileType::EFT_ReciverFPGA);
    ui->comboBoxUpgradeType->addItem(tr("HDMI Decoding Chip"),LBLFileTransferPackage::EFileType::EFT_SenderMonitor);
    ui->comboBoxUpgradeType->addItem(tr("16BitGamma"),LBLFileTransferPackage::EFileType::EFT_GammaFile);
    ui->comboBoxUpgradeType->addItem(tr("16BitGamma_512Byte"),LBLFileTransferPackage::EFileType::EFT_GammaFile_512B);

	QStyledItemDelegate *delegate = new QStyledItemDelegate(ui->comboBoxUpgradeType);
	ui->comboBoxUpgradeType->setItemDelegate(delegate);
	 
	connect(ui->comboBoxUpgradeType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_upgradeTypeChanged(int)));
    ui->comboBoxUpgradeType->setCurrentIndex(0);
    slot_upgradeTypeChanged(0);

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
    if(ui->progressBarUpgrade->hasError()){
        ui->progressBarUpgrade->setHasError(false);
    }
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
    ui->labelMCUVer->setToolTip(tr("%1").arg(pack.getVersion()));
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
    memcpy(&len, replyData.constData(), 2);
    QString name(replyData.mid(2, len));
    ui->labelAndroidVer->setText(tr("%1").arg(name));
    ui->labelAndroidVer->setToolTip(tr("%1").arg(name));
    return quint16(LBLPackage::EOR_Success);
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
        return quint16(LBLPackage::EOR_Success);
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
    ConnectionFrame::instance()->setCurrentMode(ConnectionDiagramScene::Mode::NONE);
	updateUpgrade();
}

void MCUpgrade::on_btnSelectFile_clicked()
{
	LBLUIHelper::appRunTimeDataLocation();
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Select File"),
		App::lastOpenPath,
        Utils::FileFilter::UPGRADE_FILTER);
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
    m_upgradeType = ui->comboBoxUpgradeType->currentData().toInt();
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
        if(ui->progressBarUpgrade->hasError()){
            ui->progressBarUpgrade->setHasError(false);
        }
		ui->progressBarUpgrade->setFormat(tr("%1 ,Progress：%2%").arg(m_upgradeWatcher.progressText()).arg(m_upgradeWatcher.progressValue()));
	}
	else {
        if(m_upgradeWatcher.result()!=LAPI::EResult::ER_FILE_UpgradeStatus_Success){
            ui->progressBarUpgrade->setHasError(true);
        }
		ui->progressBarUpgrade->setFormat(m_upgradeWatcher.progressText());
	}
}
