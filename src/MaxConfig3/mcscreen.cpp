#include "mcscreen.h"
#include "ui_mcscreen.h"
#include "Core/icore.h"
#include <QButtonGroup>
#include <LAPIControl>
#include <QThread>
#include <LBL_Advanved/Advancedsetting>
#include <HDMIChip/mcnt68400advsetting.h>
#include <HDMIChip/mcms9570advsetting.h>
#include <CustomWidget/mcelevatedclass.h>

#include "ConnectionControl/connectionView.h"
#include "ConnectionControl/connectionScene.h"

MCScreen::MCScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mcScreen)
{
    ui->setupUi(this);

    gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadVideoSourceBrightness(), this);
    gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_SCReadBrightness(), this);
    gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadVideoSourceColortemperature(), this);

    // 连接信号槽（相互改变）
    connect(ui->hSliderBrightness, SIGNAL(sliderMoved(int)), ui->spinBoxBrightness, SLOT(setValue(int)));
    connect(ui->hSliderBrightness, QOverload<int>::of(&QSlider::valueChanged), [=](int d){
        ui->spinBoxBrightness->blockSignals(true);
        ui->spinBoxBrightness->setValue(d);
        ui->spinBoxBrightness->blockSignals(false);
        if(!ui->hSliderBrightness->isSliderDown()){
            LAPI::WriteBrightness(d);
        }
    });

    connect(ui->spinBoxBrightness, QOverload<int>::of(&QSpinBox::valueChanged), [=](int d){
        ui->hSliderBrightness->blockSignals(true);
        ui->hSliderBrightness->setValue(d);
        ui->hSliderBrightness->blockSignals(false);
        LAPI::WriteBrightness(d,true);
    });
    connect(ui->hSliderBrightness, &QSlider::sliderReleased, [=]() {
        LAPI::WriteBrightness(ui->spinBoxBrightness->value()); });
        
    BindingSliderAndSpinBox* colorR = new BindingSliderAndSpinBox(ui->hSliderColorR,ui->spinBoxColorR,this);
    connect(colorR, &BindingSliderAndSpinBox::sig_singleShotValueChange, [=](int value)
         { LAPI::WriteHDMIRGBGain(value); });

    BindingSliderAndSpinBox* colorG = new BindingSliderAndSpinBox(ui->hSliderColorG,ui->spinBoxColorG,this);
    connect(colorG, &BindingSliderAndSpinBox::sig_singleShotValueChange, [=](int value)
         { LAPI::WriteHDMIRGBGain(-1,value); });

    BindingSliderAndSpinBox* colorB = new BindingSliderAndSpinBox(ui->hSliderColorB,ui->spinBoxColorB,this);
    connect(colorB, &BindingSliderAndSpinBox::sig_singleShotValueChange, [=](int value)
         { LAPI::WriteHDMIRGBGain(-1,-1,value); });

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

     //advancedsetting = new AdvancedSetting(this);

    // Test Hide , There is currently no functionality
    ui->radioBtnCCT->setVisible(false);
    on_radioBtnCCT_toggled(false);
    //ui->radioBtnRGB->hide();
    on_radioBtnRGB_toggled(false);

    ui->radioButton->hide();
    ui->radioButton_2->hide();
    ui->radioButton_3->hide();
    ui->radioButton_4->hide();
    //ui->labelLoadSignal->hide();
    //ui->labelLoadSignalDisplay->hide();
}

MCScreen::~MCScreen()
{
    delete ui;
    if(m_nt68400advSetDlg){
        m_nt68400advSetDlg->close();
        delete m_nt68400advSetDlg;
        m_nt68400advSetDlg=nullptr;
    }
    if(m_ms9570advSetDlg){
        m_ms9570advSetDlg->close();
        delete m_ms9570advSetDlg;
        m_ms9570advSetDlg=nullptr;
    }
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
    bool bshow=LAPI::HasNT68400();
    ui->radioBtnAndroid->setVisible(bshow);
    ui->radioBtnDP->setVisible(bshow);
    ui->radioBtnPC->setVisible(bshow);
}

void MCScreen::updateScreen()
{
    LAPI::ReadBrightness();
    LAPI::ReadHDMIInputSource(true);
    onParseReadVideoSource(LAPI::GetHDMIInputSource());
    LAPI::ReadHDMIImageColorTtemperature(true);
    LAPI::ReadHDMIInputSignalInfo(true);
    ui->labelInputSignalDisplay->setText(LAPI::GetHDMIInputSignalInfo());
    LAPI::ReadHDIMIDisplayArea(LAPI::UI::EHDMIChannel::EHC_All);
    QSize displayArea = LAPI::GetHDIMIDisplayArea();
    if(!displayArea.isEmpty()){
        ui->labelLoadSignalDisplay->setText(QString("%1X%2").arg(displayArea.width()).arg(displayArea.height()));
    }
    if(LAPI::ER_Success == LAPI::ReadHDMIRGBGain(true)){
        QList<quint8> colorGain = LAPI::GetHDMIRGBGain();
        if(colorGain.count()==3){
            ui->hSliderColorR->setValue(colorGain.at(0));
            ui->hSliderColorG->setValue(colorGain.at(1));
            ui->hSliderColorB->setValue(colorGain.at(2));
        }
    }
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
    {
        if(!ui->radioBtnCCT->isChecked()||!ui->radioBtnRGB->isChecked()){
            ui->radioBtnRGB->setChecked(true);
        }
    }
        break;
    default:{
        on_radioBtnCCT_toggled(false);
        on_radioBtnRGB_toggled(false);
    }
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
    ConnectionFrame::instance()->setCurrentMode(ConnectionDiagramScene::Mode::NONE);
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

void MCScreen::on_radioBtnCCT_toggled(bool checked)
{
    ui->hSliderColorTemp->setVisible(checked);
    ui->labelWarm->setVisible(checked);
    ui->labelDefault->setVisible(checked);
    ui->labelCool->setVisible(checked);
    if(checked){
        LAPI::WriteHDMIImageColorTtemperature(LAPI::UI::ECT_User);
    }
}

void MCScreen::on_radioBtnRGB_toggled(bool checked)
{
    ui->frameColorRGB->setVisible(checked);
}

void MCScreen::on_radioBtnRGB_clicked()
{
    LAPI::WriteHDMIImageColorTtemperature(LAPI::UI::ECT_User,true);
}

void MCScreen::on_btnModuleParam_clicked()
{
    if(!advancedsetting){
        advancedsetting = new AdvancedSetting(this);
    }
    advancedsetting->raise();
    advancedsetting->show();
}

void MCScreen::on_btnVideoSetting_clicked()
{
    if(LAPI::HasNT68400()){
        if(nullptr==m_nt68400advSetDlg){
            m_nt68400advSetDlg=new MCNT68400AdvSetting();
            Core::ICore::showCenter(m_nt68400advSetDlg);
        }
        else{
            Core::ICore::showRaise(m_nt68400advSetDlg);
        }
    }
    else{
        if(nullptr==m_ms9570advSetDlg){
            m_ms9570advSetDlg=new MCMS9570AdvSetting();
            Core::ICore::showCenter(m_ms9570advSetDlg);
        }
        else{
            Core::ICore::showRaise(m_ms9570advSetDlg);
        }
    }
}


