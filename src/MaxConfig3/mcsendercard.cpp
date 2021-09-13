#include "mcsendercard.h"
#include "ui_mcsendercard.h"
#include "Core/icore.h"

#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif

MCSenderCard::MCSenderCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MCSenderCard)
{
    ui->setupUi(this);
	QRegExp regx("[A-Fa-f0-9]{8}");
	ui->lineEditRegAddr->setValidator(new QRegExpValidator(regx, ui->lineEditRegAddr));
	ui->spinBoxRegLength->setRange(1, 0xFFFF);

	ui->spinBoxZoomWidht->setRange(0, 0xFFFF);
	ui->spinBoxZoomHeight->setRange(0, 0xFFFF); 
	showZoomModeDetails(false);
}

MCSenderCard::~MCSenderCard()
{
    delete ui;
}

bool MCSenderCard::event(QEvent * e)
{
	if (e->type() == LBLPackageEvent::s_disPatcherPackage_eventType)
	{
		LBLPackageEvent *tempE = static_cast<LBLPackageEvent*>(e);
		switch (tempE->cmdNum() - 1)
		{
		case LBLInteCtrlPackage::ECommand::EC_Read_RCFPGARegister:
		{
			//onParseReadRCFPGARegister(tempE->package().data());
		}
		break;
		default:
			break;
		}
	}
	return QWidget::event(e);
}


void MCSenderCard::cleanSenderCardWidget()
{
	ui->btnSwitch3_0Sys->setSwitchStatus(false);
	ui->btnSwitchBlackScreen->setSwitchStatus(false);
	ui->btnSwitchLockScreen->setSwitchStatus(false);
	ui->btnSwitchErrorBitRateClean->setSwitchStatus(false);
	ui->btnSwitchCorrect->setSwitchStatus(false);
	ui->btnSwitchSCS->setSwitchStatus(false);
	ui->btnSwitch24BitGamma->setSwitchStatus(false);
	ui->btnSwitchZoomMode->setSwitchStatus(false);
}

void MCSenderCard::updateSenderCard()
{
	if (LAPI::EResult::ER_Success == LAPI::ReadHDMIByPassStatus()) {
		ui->btnSwitchBypass->setSwitchStatus(LAPI::GetHDMIByPassStatus());
	}
	if (!LAPI::ReadSCProtocolType().isEmpty()) {
		ui->btnSwitch3_0Sys->setSwitchStatus(LAPI::GetSCProtocolType());
	}
	if (!LAPI::ReadSCScreenBlack().isEmpty()) {
		ui->btnSwitchBlackScreen->setSwitchStatus(LAPI::GetSCScreenBlack());
	}
	if (!LAPI::ReadSCScreenLock().isEmpty()) {
		ui->btnSwitchLockScreen->setSwitchStatus(LAPI::GetSCScreenLock());
	}
	if (!LAPI::ReadSCErrorBitRateStatisticalSwitch().isEmpty()) {
		ui->btnSwitchErrorBitRateClean->setSwitchStatus(LAPI::GetSCErrorBitRateStatisticalSwitch());
	}
	if (!LAPI::ReadSCCorrectionSwitch().isEmpty()) {
		ui->btnSwitchCorrect->setSwitchStatus(LAPI::GetSCCorrectionSwitch());
	}
	if (!LAPI::ReadSCSpreadSpectrumSwitch().isEmpty()) {
		ui->btnSwitchSCS->setSwitchStatus(LAPI::GetSCSpreadSpectrumSwitch());
	}
	if (!LAPI::ReadSC24BitGammaSwitch().isEmpty()) {
		ui->btnSwitch24BitGamma->setSwitchStatus(LAPI::GetSC24BitGammaSwitch());
	}
	if (!LAPI::ReadSCZoomMode().isEmpty()) {
		ui->btnSwitchZoomMode->setSwitchStatus(LAPI::GetSCZoomMode());
		showZoomModeDetails(ui->btnSwitchZoomMode->isChecked());
		if (ui->btnSwitchZoomMode->isChecked()) {
			if (!LAPI::ReadSCZoomSize().isEmpty()) {
				QSize size = LAPI::GetSCZoomSize();
				ui->spinBoxZoomWidht->setValue(size.width());
				ui->spinBoxZoomHeight->setValue(size.height());
			}
		}
	}
}

void MCSenderCard::showZoomModeDetails(bool b)
{
	ui->btnZoomSizeSend->setVisible(b);
	ui->label->setVisible(b);
	ui->spinBoxZoomWidht->setVisible(b);
	ui->label_2->setVisible(b);
	ui->spinBoxZoomHeight->setVisible(b);
}

void MCSenderCard::slot_ConnectItem()
{
	cleanSenderCardWidget();
	updateSenderCard();
}

void MCSenderCard::slot_EnterNavigatPage()
{
	updateSenderCard();
}

void MCSenderCard::on_btnTestNormal_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_Normal);
	Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnTestRed_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_Red);
	Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnTestGreen_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_Green);
	Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnTestBlue_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_Blue);
	Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnTestWhite_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_White);
	Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnTestBlack_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_Black);
	Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnSwitchBypass_clicked()
{
	LAPI::EResult ret = LAPI::WriteHDMIByPassStatus(ui->btnSwitchBypass->isChecked());
	Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnRegRead_clicked()
{
	ui->textBrowserReg->clear();
	quint32 addr = ui->lineEditRegAddr->text().toUInt(nullptr, 16);
	quint16 length = ui->spinBoxRegLength->value();
	QByteArray reData = LAPI::ReadSCFPGARegister(addr, length);
	QString buffer;
	buffer = LBLUIHelper::byteArrayToHexStr(reData);
	ui->textBrowserReg->append(buffer);
	Core::ICore::showMessageLAPIResult(reData.isEmpty() ? LAPI::EResult::ER_Fail : LAPI::EResult::ER_Success);
}

void MCSenderCard::on_btnRegWrite_clicked()
{
	quint32 addr = ui->lineEditRegAddr->text().toUInt(nullptr, 16);
	quint16 length = ui->spinBoxRegLength->value();
	QByteArray buffer;
	//buffer.resize(length);
	buffer.fill(0, length);
	QByteArray text = LBLUIHelper::hexStrToByteArray(ui->textBrowserReg->toPlainText());
	buffer.replace(0, length > text.size() ? text.size() : length, text);
	LAPI::EResult ret = LAPI::WriteSCFPGARegister(addr, buffer);
	/*if (LAPI::EResult::ER_Success != LAPI::WriteSCFPGARegister(addr, buffer)) {
        QMessageBox::information(NULL, tr("Tip"), \
            tr("Register write failed."), QMessageBox::Yes, QMessageBox::Yes);
	}*/
	Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnSwitch3_0Sys_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCProtocolType(ui->btnSwitch3_0Sys->isChecked());
	if (ret != LAPI::EResult::ER_Success) {
		ui->btnSwitch3_0Sys->setSwitchStatus(!ui->btnSwitch3_0Sys->isChecked());
	}
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnSwitchBlackScreen_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCScreenBlack(ui->btnSwitchBlackScreen->isChecked());
	if (ret != LAPI::EResult::ER_Success) {
		ui->btnSwitchBlackScreen->setSwitchStatus(!ui->btnSwitchBlackScreen->isChecked());
    }
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnSwitchLockScreen_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCScreenLock(ui->btnSwitchLockScreen->isChecked());
	if (ret != LAPI::EResult::ER_Success) {
		ui->btnSwitchLockScreen->setSwitchStatus(!ui->btnSwitchLockScreen->isChecked());
    }
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnSwitchErrorBitRateClean_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCErrorBitRateStatisticalSwitch(ui->btnSwitchErrorBitRateClean->isChecked());
	if (ret != LAPI::EResult::ER_Success) {
		ui->btnSwitchErrorBitRateClean->setSwitchStatus(!ui->btnSwitchErrorBitRateClean->isChecked());
    }
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnSwitchCorrect_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCCorrectionSwitch(ui->btnSwitchCorrect->isChecked());
	if (ret != LAPI::EResult::ER_Success) {
		ui->btnSwitchCorrect->setSwitchStatus(!ui->btnSwitchCorrect->isChecked());
    }
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnSwitchSCS_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCSpreadSpectrumSwitch(ui->btnSwitchSCS->isChecked());
	if (ret != LAPI::EResult::ER_Success) {
		ui->btnSwitchSCS->setSwitchStatus(!ui->btnSwitchSCS->isChecked());
    }
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnSwitch24BitGamma_clicked()
{
	LAPI::EResult ret = LAPI::WriteSC24BitGammaSwitch(ui->btnSwitch24BitGamma->isChecked());
	if (ret != LAPI::EResult::ER_Success) {
		ui->btnSwitch24BitGamma->setSwitchStatus(!ui->btnSwitch24BitGamma->isChecked());
    }
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnSwitchZoomMode_clicked()
{
	showZoomModeDetails(ui->btnSwitchZoomMode->isChecked());
	LAPI::EResult ret = LAPI::WriteSCZoomMode(ui->btnSwitchZoomMode->isChecked());
	if (ret != LAPI::EResult::ER_Success) {
		ui->btnSwitchZoomMode->setSwitchStatus(!ui->btnSwitchZoomMode->isChecked());
    }
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnZoomSizeSend_clicked()
{
	LAPI::EResult ret = LAPI::WriteSCZoomSize(QSize(ui->spinBoxZoomWidht->value(), ui->spinBoxZoomHeight->value()));
	Core::ICore::showMessageLAPIResult(ret);
}
