#include "mcms9570advsetting.h"
#include "ui_mcms9570advsetting.h"

#include <LAPI_Control/LAPIControl>
#include "Core/icore.h"

#include <QMessageBox>
#include <QButtonGroup>

MCMS9570AdvSetting::MCMS9570AdvSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MCMS9570AdvSetting)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    initUI();
}

MCMS9570AdvSetting::~MCMS9570AdvSetting()
{
    delete ui;
}

void MCMS9570AdvSetting::initUI()
{
    connect(ui->hSliderContrast, SIGNAL(valueChanged(int)), ui->spinBoxContrast, SLOT(setValue(int)));
    connect(ui->spinBoxContrast, QOverload<int>::of(&QSpinBox::valueChanged), [=](int d){
        ui->hSliderContrast->setValue(d);
        LAPI::WriteHDMIImageContrast(d);
    });

    connect(ui->hSliderVolume, SIGNAL(valueChanged(int)), ui->spinBoxVolume, SLOT(setValue(int)));
    connect(ui->spinBoxVolume, QOverload<int>::of(&QSpinBox::valueChanged), [=](int d){
        ui->hSliderVolume->setValue(d);
        LAPI::WriteHDIMIAudioVolume(d,LAPI::UI::EHDMIChannel::EHC_All,false);
    });

    ui->radioBtnCustomResolution->setChecked(true);
    on_radioBtnCustomResolution_clicked();
    ui->radioBtnBoxSeries->setEnabled(false);

    ui->comboBoxPresetResolutuion->addItem("2560*1440",QSize(2560,1440));
    ui->comboBoxPresetResolutuion->addItem("1920*1080",QSize(1920,1080));
    ui->comboBoxPresetResolutuion->addItem("1600*900",QSize(1600,900));
    ui->comboBoxPresetResolutuion->addItem("1280*720",QSize(1280,720));

    ui->spinBoxWidth->setRange(1,0xFFFF);
    ui->spinBoxHeight->setRange(1,0xFFFF);

    on_btnRefresh_clicked();
}

void MCMS9570AdvSetting::updateUISettings()
{
    blockingControlSignals(true);
    updateOtherSettings();
    blockingControlSignals(false);
}

void MCMS9570AdvSetting::updateOtherSettings()
{
    ui->hSliderContrast->setValue(LAPI::GetHDMIImageContrast());
    ui->spinBoxContrast->setValue(LAPI::GetHDMIImageContrast());
    ui->hSliderVolume->setValue(LAPI::GetHDIMIAudioVolume());
    ui->spinBoxVolume->setValue(LAPI::GetHDIMIAudioVolume());

    ui->radioBtnCustomResolution->setChecked(true);
    on_radioBtnCustomResolution_clicked();
    QSize displayArea=LAPI::GetHDIMIDisplayArea();
    ui->spinBoxWidth->setValue(displayArea.width());
    ui->spinBoxHeight->setValue(displayArea.height());
}

void MCMS9570AdvSetting::blockingControlSignals(bool b)
{
    ui->hSliderContrast->blockSignals(b);
    ui->hSliderVolume->blockSignals(b);
    ui->spinBoxContrast->blockSignals(b);
    ui->spinBoxVolume->blockSignals(b);

    ui->radioBtnPresetResolution->blockSignals(b);
    ui->radioBtnBoxSeries->blockSignals(b);
    ui->radioBtnCustomResolution->blockSignals(b);

    ui->comboBoxPresetResolutuion->blockSignals(b);
    ui->comboBoxBoxSeries->blockSignals(b);
    ui->spinBoxRow->blockSignals(b);
    ui->spinBoxColumn->blockSignals(b);
    ui->spinBoxWidth->blockSignals(b);
    ui->spinBoxHeight->blockSignals(b);
}

void MCMS9570AdvSetting::on_radioBtnPresetResolution_clicked()
{
    ui->framePreSetResolution->setVisible(true);
    ui->frameBoxSeries->setVisible(false);
    ui->frameCustResolution->setVisible(false);
}

void MCMS9570AdvSetting::on_radioBtnBoxSeries_clicked()
{
    ui->framePreSetResolution->setVisible(false);
    ui->frameBoxSeries->setVisible(true);
    ui->frameCustResolution->setVisible(false);
}

void MCMS9570AdvSetting::on_radioBtnCustomResolution_clicked()
{
    ui->framePreSetResolution->setVisible(false);
    ui->frameBoxSeries->setVisible(false);
    ui->frameCustResolution->setVisible(true);
}

void MCMS9570AdvSetting::on_btnResolutionSave_clicked()
{
    if(ui->radioBtnPresetResolution->isChecked()){
        LAPI::EResult ret = LAPI::WriteHDIMIDisplayArea(ui->comboBoxPresetResolutuion->currentData().toSize(),LAPI::UI::EHDMIChannel::EHC_All,false);
        Core::ICore::showMessageLAPIResult(ret);
        return;
    }
    if(ui->radioBtnCustomResolution->isChecked()){
        LAPI::EResult ret = LAPI::WriteHDIMIDisplayArea(QSize(ui->spinBoxWidth->value(),ui->spinBoxHeight->value()),\
                                                        LAPI::UI::EHDMIChannel::EHC_All,false);
        Core::ICore::showMessageLAPIResult(ret);
        return;
    }
}

void MCMS9570AdvSetting::on_btnReset_clicked()
{
    int opt =QMessageBox::question(NULL, tr("Question"), \
                                      tr("Are you sure to reset?"), QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    if(opt==QMessageBox::Yes){
        LAPI::EResult ret = LAPI::ResetHDMISetting();
        Core::ICore::showMessageLAPIResult(ret);
    }
}

void MCMS9570AdvSetting::on_btnRefresh_clicked()
{
    ui->btnRefresh->setEnabled(false);
    //同步
    LAPI::ReadHDMIImageContrast(true);
    LAPI::ReadHDIMIAudioVolume(LAPI::UI::EHDMIChannel::EHC_All);

    LAPI::ReadHDIMIDisplayArea(LAPI::UI::EHDMIChannel::EHC_All);

    updateUISettings();
    ui->btnRefresh->setEnabled(true);
}

void MCMS9570AdvSetting::on_btnSetEDID_clicked()
{
    QByteArray EDIDData = LAPI::GetEDIDData();
    if(EDIDData.length() != 256)
    {
         Core::ICore::showMessageLAPIResult(LAPI::EResult::ER_INTECTRL_Fail_NoReason);
         return;
    }
    int Width = ui->spinBoxWidth->value();
    int Height = ui->spinBoxHeight->value();

    EDIDData[56] = Width & 0xFF;
    EDIDData[58] = EDIDData[58] | (Width << 4);

    EDIDData[59] = Height & 0xFF;
    EDIDData[61] = EDIDData[58] | (Height << 4);

    //checksum
    uchar checksum = 0;
    for (int i =0; i<127; ++i)
    {
        checksum += EDIDData[i];
    }
    EDIDData[127] = (uchar)(256 - checksum);

//    quint8* aaa = new quint8[256];
//    for (int i=0;i<256;i++)
//    {
//        aaa[i] = EDIDData[i];
//    }

    quint8 data[256]{0};
    memcpy(data,EDIDData,256);

    quint8 result = 0;
    for(int i = 0;i <16;i++)
    {
        result = LAPI::writeHDMIEDID(i,data+(i+16),16);
        if (LAPI::EResult::ER_Success != (quint16)result)
        {
            break;
        }
    }

    Core::ICore::showMessageLAPIResult((LAPI::EResult)result);

}
