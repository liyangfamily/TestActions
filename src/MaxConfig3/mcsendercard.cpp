#include "mcsendercard.h"
#include "ui_mcsendercard.h"
#include "Core/icore.h"

#include "ConnectionControl/connectionView.h"
#include "ConnectionControl/connectionScene.h"

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

    ui->comboBoxNT68400Resolutions->addItem("3840 * 2160",0);
    ui->comboBoxNT68400Resolutions->addItem("1920 * 1080",1);
    connect(ui->comboBoxNT68400Resolutions,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int d){
        slot_comboBoxNT68400Resolutions_IndexChanged(d);
    });

    ui->spinBoxZoomWidht->setRange(0, 0xFFFF);
    ui->spinBoxZoomHeight->setRange(0, 0xFFFF);
    showZoomModeDetails(false);
    ui->groupBox->hide(); //Hide Zoom mode
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
    ui->btn10bitSource->setSwitchStatus(false);
    ui->btnLowDelay->setSwitchStatus(false);
    ui->btnSwitchZoomMode->setSwitchStatus(false);
}

void MCSenderCard::updateSenderCard()
{
    if (!LAPI::ReadSCSelfTestMode().isEmpty()) {
        LAPI::UI::EPictureTestMode mode= LAPI::GetSCSelfTestMode();
        setSenderCardTestMode(mode);
    }
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
    if (!LAPI::ReadSC10BitSource().isEmpty()) {
        ui->btn10bitSource->setSwitchStatus(LAPI::GetSC10BitSource());
    }
    if (!LAPI::ReadSCLowDelay().isEmpty()) {
        ui->btnLowDelay->setSwitchStatus(LAPI::GetSCLowDelay());
    }
    if (!LAPI::ReadSCNT68400Resolution().isEmpty()) {
        ui->comboBoxNT68400Resolutions->setCurrentIndex(LAPI::GetSCNT68400Resolution());
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

void MCSenderCard::setSenderCardTestMode(LAPI::UI::EPictureTestMode mode)
{
    switch(mode)
    {
    case LAPI::UI::EPictureTestMode::EPTM_Red:
        ui->btnTestRed->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_Green:
        ui->btnTestGreen->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_Blue:
        ui->btnTestBlue->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_White:
        ui->btnTestWhite->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_Yellow:
        break;
    case LAPI::UI::EPictureTestMode::EPTM_Purple:
        break;
    case LAPI::UI::EPictureTestMode::EPTM_Cyan:
        break;
    case LAPI::UI::EPictureTestMode::EPTM_Black:
        ui->btnTestBlack->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_LeftSlash:
        ui->btnTestLeftSlash->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_RightSlash:
        ui->btnTestRightSlash->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_HorizontalSlash:
        ui->btnTestHorizontalSlash->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_VerticalSlash:
        ui->btnTestVerticalSlash->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_GradientRed:
        ui->btnTestGradientRed->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_GradientGreen:
        ui->btnTestGradientGreen->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_GradientBlue:
        ui->btnTestGradientBlue->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_GradientWhite:
        ui->btnTestGradientWhite->setChecked(true);
        break;
    case LAPI::UI::EPictureTestMode::EPTM_Normal:
        ui->btnTestNormal->setChecked(true);
        break;
    default:
        break;
    }
}

void MCSenderCard::slot_ConnectItem()
{
    cleanSenderCardWidget();
    updateSenderCard();
}

void MCSenderCard::slot_EnterNavigatPage()
{
    ConnectionFrame::instance()->setCurrentMode(ConnectionDiagramScene::Mode::NONE);
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

void MCSenderCard::on_btnTestLeftSlash_clicked()
{
    LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_LeftSlash);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnTestRightSlash_clicked()
{
    LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_RightSlash);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnTestHorizontalSlash_clicked()
{
    LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_HorizontalSlash);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnTestVerticalSlash_clicked()
{
    LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_VerticalSlash);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnTestGradientRed_clicked()
{
    LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_GradientRed);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnTestGradientGreen_clicked()
{
    LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_GradientGreen);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnTestGradientBlue_clicked()
{
    LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_GradientBlue);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnTestGradientWhite_clicked()
{
    LAPI::EResult ret = LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_GradientWhite);
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
    QByteArray text = LBLUIHelper::hexStrToByteArray(ui->textBrowserReg->toPlainText().simplified());
    buffer.replace(0, length > text.size() ? text.size() : length, text);
    LAPI::EResult ret = LAPI::WriteSCFPGARegister(addr, buffer);
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

void MCSenderCard::on_btn10bitSource_clicked()
{
    LAPI::EResult ret = LAPI::WriteSC10BitSource(ui->btn10bitSource->isChecked());
    if (ret != LAPI::EResult::ER_Success) {
        ui->btn10bitSource->setSwitchStatus(!ui->btn10bitSource->isChecked());
    }
    Core::ICore::showMessageLAPIResult(ret);
}

void MCSenderCard::on_btnLowDelay_clicked()
{
    LAPI::EResult ret = LAPI::WriteSCLowDelay(ui->btnLowDelay->isChecked());
    if (ret != LAPI::EResult::ER_Success) {
        ui->btnLowDelay->setSwitchStatus(!ui->btnLowDelay->isChecked());
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

void MCSenderCard::slot_comboBoxNT68400Resolutions_IndexChanged(int d)
{
    LAPI::WriteSCNT68400Resolution(ui->comboBoxNT68400Resolutions->currentData().toUInt());
}

void MCSenderCard::on_CutoutSetpushButton_clicked()
{
    int addr = 0x2A;
    QByteArray buffer;
    buffer.fill(0, 4);
    buffer[0] = (uchar)(ui->CutoutWidthspinBox->value() & 0xFF);
    buffer[1] = (uchar)((ui->CutoutWidthspinBox->value() >> 8) & 0xFF);
    buffer[2] = (uchar)(ui->CutoutHeightspinBox->value() % 0xFF);
    buffer[3] = (uchar)((ui->CutoutHeightspinBox->value() >> 8) & 0xFF);
    LAPI::EResult ret = LAPI::WriteSCFPGARegister(addr, buffer);
    Core::ICore::showMessageLAPIResult(ret);
}
