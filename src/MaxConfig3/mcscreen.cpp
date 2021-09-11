#include "mcscreen.h"
#include "ui_mcscreen.h"
#include <QButtonGroup>
#include <LAPIControl>
#include <QThread>
//#include <LBL_Advanved/Advancedsetting>
MCScreen::MCScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mcScreen)
{
    ui->setupUi(this);

    gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadVideoSourceBrightness(), this);
    gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_SCReadBrightness(), this);
    gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadVideoSourceColortemperature(), this);

    // 连接信号槽（相互改变）
    connect(ui->spinBoxBrightness, SIGNAL(valueChanged(int)), ui->hSliderBrightness, SLOT(setValue(int)));
    connect(ui->spinBoxBrightness, SIGNAL(valueChanged(int)), this, SLOT(slot_BrightnessValueChanged(int)));
    connect(ui->hSliderBrightness, &QSlider::sliderReleased, [=]() {
        LAPI::WriteBrightness(ui->hSliderBrightness->value()); });
    connect(ui->hSliderBrightness, SIGNAL(valueChanged(int)), ui->spinBoxBrightness, SLOT(setValue(int)));
    //connect(ui->hSliderBrightness, SIGNAL(valueChanged(int)), this, SLOT(slot_BrightnessValueChanged(int)));

    QButtonGroup* pButtonGroup = new QButtonGroup(this);
    pButtonGroup->setExclusive(true);
    pButtonGroup->addButton(ui->radioBtnAndroid);
    pButtonGroup->addButton(ui->radioBtnPC);
    pButtonGroup->addButton(ui->radioBtnHDMI1);
    pButtonGroup->addButton(ui->radioBtnHDMI2);
    pButtonGroup->addButton(ui->radioBtnHDMI3);
    pButtonGroup->addButton(ui->radioBtnDP);
    pButtonGroup->addButton(ui->radioBtnHide);
    ui->radioBtnHide->setVisible(false);

    QButtonGroup*pButtonGroup1 = new QButtonGroup(this);
    pButtonGroup1->setExclusive(true);
    pButtonGroup1->addButton(ui->radioBtnWarm);
    pButtonGroup1->addButton(ui->radioBtnNormal);
    pButtonGroup1->addButton(ui->radioBtnCool);
    pButtonGroup1->addButton(ui->radioBtnCCT);
    pButtonGroup1->addButton(ui->radioBtnRGB);
    pButtonGroup1->addButton(ui->radioButtonHide2);
    ui->radioButtonHide2->setVisible(false);
}

MCScreen::~MCScreen()
{
    delete ui;
    gDispatcher->unregisterDispatcherPackage(LBLPackageInteCtrl_ReadVideoSourceBrightness(), this);
    gDispatcher->unregisterDispatcherPackage(LBLPackageInteCtrl_SCReadBrightness(), this);
    gDispatcher->unregisterDispatcherPackage(LBLPackageInteCtrl_ReadVideoSourceColortemperature(), this);
}

bool MCScreen::event(QEvent *e)
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
        case LBLInteCtrlPackage::ECommand::EC_Read_VideoSourceColortemperature:
        {
            onParseSourceColortemperature(tempE->package().data());
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

void MCScreen::cleanScreenWidget()
{
    ui->radioBtnHide->setChecked(true);
    ui->radioButtonHide2->setChecked(true);
    ui->labelInputSignalDisplay->clear();
    ui->labelLoadSignalDisplay->clear();
}

void MCScreen::updateScreen()
{
    LAPI::ReadBrightness();
    LAPI::ReadHDMIInputSource(true);
    onParseReadVideoSource(LAPI::GetHDMIInputSource());
    LAPI::ReadHDMIImageColorTtemperature();
    LAPI::ReadHDMIInputSignalInfo(true);
    ui->labelInputSignalDisplay->setText(LAPI::GetHDMIInputSignalInfo());
}

quint16 MCScreen::onParseReadBrightness(const QByteArray & data)
{
    LBLPackageInteCtrl_ReadVideoSourceBrightness pack(data);
    ui->hSliderBrightness->setValue(pack.getBrightness());
    return LBLPackage::EOR_Success;
}

quint16 MCScreen::onParseReadVideoSource(quint8 source)
{
    switch (source) {
    case LAPI::UI::EIS_Android:
        ui->radioBtnAndroid->setChecked(true);
        break;
    case LAPI::UI::EIS_PC:
        ui->radioBtnPC->setChecked(true);
        break;
    case LAPI::UI::EIS_HDMI1:
        ui->radioBtnHDMI1->setChecked(true);
        break;
    case LAPI::UI::EIS_HDMI2:
        ui->radioBtnHDMI2->setChecked(true);
        break;
    case LAPI::UI::EIS_HDMI3:
        ui->radioBtnHDMI3->setChecked(true);
        break;
    case LAPI::UI::EIS_DP:
        ui->radioBtnDP->setChecked(true);
        break;
    default:
        break;
    }
    return LBLPackage::EOR_Success;
}

quint16 MCScreen::onParseSourceColortemperature(const QByteArray & data)
{
    LBLPackageInteCtrl_ReadVideoSourceColortemperature pack(data);
    LAPI::UI::EColorTemperature colortemperature = (LAPI::UI::EColorTemperature)pack.getColortemperature();
    switch (colortemperature)
    {
    case LAPI::UI::ECT_Warm:
        ui->radioBtnWarm->setChecked(true);
        break;
    case LAPI::UI::ECT_Standard:
        ui->radioBtnNormal->setChecked(true);
        break;
    case LAPI::UI::ECT_Cool:
        ui->radioBtnCool->setChecked(true);
        break;
    case LAPI::UI::ECT_User:
        ui->radioBtnCCT->setChecked(true);
        break;
    default:
        break;
    }
    return LBLPackage::EOR_Success;
}

quint16 MCScreen::onParseReadMCUAppVersion(const QByteArray & data)
{
    LBLPackageInteCtrl_ReadMCUAppVersion pack(data);
    //ui->textEdit->append(tr("MCU App：%1\n").arg(pack.getVersion()));
    return LBLPackage::EOR_Success;
}

quint16 MCScreen::onParseReadMCUBootVersion(const QByteArray & data)
{
    LBLPackageInteCtrl_ReadMCUBootVersion pack(data);
    //ui->textEdit->append(tr("MCU Boot：%1\n").arg(pack.getVersion()));
    return LBLPackage::EOR_Success;
}

quint16 MCScreen::onParseReadAndroidVersion(const QByteArray & data)
{
    LBLPackageInteCtrl_ReadAndroidVersionNum pack(data);
    QByteArray replyData = pack.getReplyData();
    quint16 len = 0;
    memcpy(&len, replyData.constData(), 2);
    QString name(replyData.mid(2, len));
    //ui->textEdit->append(tr("Android版本：%1\n").arg(name));
    return LBLPackage::EOR_Success;
}

quint16 MCScreen::onParseReadSCFPGARegister(const QByteArray & data)
{
    LBLPackageInteCtrl_ReadSCFPGARegister pack(data);
    QByteArray packData = pack.getReplyData();
    switch (pack.getAddress())
    {
    case LBL::SC::ENormalSettingRegAddrs::ENSRA_FPGABigVersion:
    {
        QString version;
        version = LAPI::GetSCFPGAVersion();
        //ui->textEdit->append(tr("FPGA Version：%1\n").arg(version));
        return LBLPackage::EOR_Success;
    }
    break;
    default:
        break;
    }
    return 0;
}

void MCScreen::slot_ConnectItem()
{
    cleanScreenWidget();
    updateScreen();
}

void MCScreen::slot_EnterNavigatPage()
{
    updateScreen();
}

void MCScreen::slot_BrightnessValueChanged(int value)
{
    LAPI::WriteBrightness(value, true);
}

void MCScreen::on_radioBtnHDMI1_clicked()
{
    LAPI::WriteHDMIInputSource(LAPI::UI::EIS_HDMI1);
}

void MCScreen::on_radioBtnHDMI2_clicked()
{
    LAPI::WriteHDMIInputSource(LAPI::UI::EIS_HDMI2);
}

void MCScreen::on_radioBtnHDMI3_clicked()
{
    LAPI::WriteHDMIInputSource(LAPI::UI::EIS_HDMI3);
}

void MCScreen::on_radioBtnAndroid_clicked()
{
    LAPI::WriteHDMIInputSource(LAPI::UI::EIS_Android);
}

void MCScreen::on_radioBtnPC_clicked()
{
    LAPI::WriteHDMIInputSource(LAPI::UI::EIS_PC);
}

void MCScreen::on_radioBtnDP_clicked()
{
    LAPI::WriteHDMIInputSource(LAPI::UI::EIS_DP);
}

void MCScreen::on_radioBtnWarm_clicked()
{
    LAPI::WriteHDMIImageColorTtemperature(LAPI::UI::ECT_Warm);
}

void MCScreen::on_radioBtnNormal_clicked()
{
    LAPI::WriteHDMIImageColorTtemperature(LAPI::UI::ECT_Standard);
}

void MCScreen::on_radioBtnCool_clicked()
{
    LAPI::WriteHDMIImageColorTtemperature(LAPI::UI::ECT_Cool);
}

void MCScreen::on_radioBtnCCT_clicked()
{
    LAPI::WriteHDMIImageColorTtemperature(LAPI::UI::ECT_User);
}

void MCScreen::on_btnModuleParam_clicked()
{
    //AdvancedSetting *advancedsetting = new AdvancedSetting();
    //advancedsetting->show();
}


