#include "iccfd435asetting.h"
#include "ui_iccfd435asetting.h"
#include "advancedsetting.h"
#include "icadvancedsetting.h"

ICCFD435ASetting::ICCFD435ASetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ICCFD435ASetting)
{
    ui->setupUi(this);

    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag                  |= Qt::WindowMinimizeButtonHint;
    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    setWindowFlags(windowFlag);

    InitForm();
    LoadForm();
}
#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif
ICCFD435ASetting::~ICCFD435ASetting()
{
    delete ui;
}

void ICCFD435ASetting::InitForm()
{

    int i=0;
    for (i=0;i<4;i++)
    {
        ui->LowGrayscaleRcomboBox->addItem(QString::number(i));
        ui->LowGrayscaleGcomboBox->addItem(QString::number(i));
        ui->LowGrayscaleBcomboBox->addItem(QString::number(i));

        ui->CouplingStrengthAdjRcomboBox->addItem(QString::number(i + 1));
        ui->CouplingStrengthAdjGcomboBox->addItem(QString::number(i + 1));
        ui->CouplingStrengthAdjBcomboBox->addItem(QString::number(i + 1));

        ui->CouplingRangeAdjRcomboBox->addItem(QString::number(i + 1));
        ui->CouplingRangeAdjGcomboBox->addItem(QString::number(i + 1));
        ui->CouplingRangeAdjBcomboBox->addItem(QString::number(i + 1));

        ui->PreDriveTimeRcomboBox->addItem(QString::number(i+1));
        ui->PreDriveTimeGcomboBox->addItem(QString::number(i+1));
        ui->PreDriveTimeBcomboBox->addItem(QString::number(i+1));

        ui->CurrentGearRcomboBox->addItem(QString::number(i+1));
        ui->CurrentGearGcomboBox->addItem(QString::number(i+1));
        ui->CurrentGearBcomboBox->addItem(QString::number(i+1));

    }
    for (i=0;i<8;i++)
    {
        ui->ColBlankAdjRcomboBox->addItem(QString::number(i));
        ui->ColBlankAdjGcomboBox->addItem(QString::number(i));
        ui->ColBlankAdjBcomboBox->addItem(QString::number(i));
    }
    for (i=0;i<2 ;i++ )
    {
        ui->PreDriveModeRcomboBox->addItem(QString::number(i+1));
        ui->PreDriveModeGcomboBox->addItem(QString::number(i+1));
        ui->PreDriveModeBcomboBox->addItem(QString::number(i+1));



        ui->OpenTestPointAdjRcomboBox->addItem(QString::number(i+1));
        ui->OpenTestPointAdjGcomboBox->addItem(QString::number(i+1));
        ui->OpenTestPointAdjBcomboBox->addItem(QString::number(i+1));

        ui->ScanModeRcomboBox->addItem(QString::number(i+1));
        ui->ScanModeGcomboBox->addItem(QString::number(i+1));
        ui->ScanModeBcomboBox->addItem(QString::number(i+1));
    }
    for (i=0;i<32;i++)
    {
        ui->LowGrayStrengthRcomboBox->addItem(QString::number(i+1));
        ui->LowGrayStrengthGcomboBox->addItem(QString::number(i+1));
        ui->LowGrayStrengthBcomboBox->addItem(QString::number(i+1));
    }

    QStringList items;
    items<<tr("短");
    items<<tr("长");
    ui->ColumnBlankTimeRcomboBox->addItems(items);
    ui->ColumnBlankTimeGcomboBox->addItems(items);
    ui->ColumnBlankTimeBcomboBox->addItems(items);

    items.clear();
    items<<tr("时钟下降沿输出");
    items<<tr("时钟上升沿输出");
    ui->DataOutputRcomboBox->addItems(items);
    ui->DataOutputGcomboBox->addItems(items);
    ui->DataOutputBcomboBox->addItems(items);

    items.clear();
    items<<tr("模式1");
    items<<tr("模式2");
    ui->WakeupSettingRcomboBox->addItems(items);
    ui->WakeupSettingGcomboBox->addItems(items);
    ui->WakeupSettingBcomboBox->addItems(items);

    items.clear();
    items<<"0.2V";
    items<<"0.6V";
    items<<"1.0V";
    items<<"1.6V";
    ui->OpenCircuitDetectionThresholdRcomboBox->addItems(items);
    ui->OpenCircuitDetectionThresholdGcomboBox->addItems(items);
    ui->OpenCircuitDetectionThresholdBcomboBox->addItems(items);

    items.clear();
    items<<"0.5V";
    items<<"0.4V";
    items<<"0.3V";
    items<<"0.2V";
    ui->ConstantCurrentPointRcomboBox->addItems(items);
    ui->ConstantCurrentPointGcomboBox->addItems(items);
    ui->ConstantCurrentPointBcomboBox->addItems(items);

    items.clear();
    items<<tr("慢");
    items<<tr("快");
    ui->OutputResponseRcomboBox->addItems(items);
    ui->OutputResponseGcomboBox->addItems(items);
    ui->OutputResponseBcomboBox->addItems(items);

    items.clear();
    items<<tr("65536级");
    items<<tr("32768级");
    items<<tr("16384级");
    items<<tr("8192级");
    ui->PWMGraySettingRcomboBox->addItems(items);
    ui->PWMGraySettingGcomboBox->addItems(items);
    ui->PWMGraySettingBcomboBox->addItems(items);

    items.clear();
    items<<tr("4行");
    items<<tr("2行");
    ui->LowGrayOptimizationModeRcomboBox->addItems(items);
    ui->LowGrayOptimizationModeGcomboBox->addItems(items);
    ui->LowGrayOptimizationModeBcomboBox->addItems(items);



    items.clear();
    items<<"24";
    items<<"32";
    items<<"8";
    items<<"16";
    ui->OutPutPowerTubeRcomboBox->addItems(items);
    ui->OutPutPowerTubeGcomboBox->addItems(items);
    ui->OutPutPowerTubeBcomboBox->addItems(items);





}

int ICCFD435ASetting::GetLowGrayscale(unsigned char value)
{
    switch (value & 0x60)
    {
    case 0x00:
        return 0;
    case 0x20:
        return 1;
    case 0x40:
        return 2;
    case 0x60:
        return 3;
    default:
        return 0;
    }
}
int ICCFD435ASetting::GetColBlankAdj(unsigned char value)
{

    switch((value >> 5) & 0x07)
    {
    case 0x00:
        return 0;
    case 0x04:
        return 1;
    case 0x02:
        return 2;
    case 0x06:
        return 3;
    case 0x01:
        return 4;
    case 0x05:
        return 5;
    case 0x03:
        return 6;
    case 0x07:
        return 7;
    default:
        return 0;
    }
}
bool ICCFD435ASetting::GetColBlankEnhance(unsigned char value)
{
    if ((value & 0x10) == 0x10)
    {
        return false;
    }
    else
    {
        return true;
    }
}
int ICCFD435ASetting::GetColumnBlankTime(unsigned char value)
{
    return (value & 0x01);
}
int ICCFD435ASetting::GetCouplingStrengthAdj(unsigned char value)
{
    return (value >> 2) & 0x03;
}
int ICCFD435ASetting::GetCouplingRangeAdj(unsigned char value)
{
    return (value >> 5) & 0x03;
}
bool ICCFD435ASetting::GetCouplingOptimization(unsigned char value)
{
    if ((value & 0x01) == 0x01)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool ICCFD435ASetting::GetPreDriveEnablement(unsigned char value)
{
    if ((value & 0x10) == 0x10)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int ICCFD435ASetting::GetPreDriveMode(unsigned char value)
{
    return ((value >> 4) & 0x01);
}
int ICCFD435ASetting::GetPreDriveTime(unsigned char value)
{
    return ((value >> 2) & 0x03);
}
int ICCFD435ASetting::GetLowGrayStrength(unsigned char valuelow,unsigned char valuehigh)
{
    int value = valuelow + valuehigh * 256;
    int value1 = ((value >> 7) & 0x1F);
    return (32 - (value1 + 1));
}
int ICCFD435ASetting::GetLowGrayTime(unsigned char value)
{
    return (value >> 7) & 0x01;
}
bool ICCFD435ASetting::GetDynamicEnergySaving(unsigned char value)
{
    if (((value >> 1) & 0x01) == 0x01)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int ICCFD435ASetting::GetWakeupSetting(unsigned char value)
{
    return ((value) & 0x01);
}
int ICCFD435ASetting::GetOpenCircuitDetectionThreshold(unsigned char value)
{
    return (value & 0x03);
}
int ICCFD435ASetting::GetOpenTestPointAdj(unsigned char value)
{
    return ((value >> 1) & 0x01);
}
bool ICCFD435ASetting::GetOpenCircuitProtcetEnable(unsigned char value)
{
    if ((value & 0x02) == 0x02)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool ICCFD435ASetting::GetOpenCircuitDynamicDetec(unsigned char value)
{
    if (((value >> 6) & 0x01) == 0x01)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int ICCFD435ASetting::GetScanMode(unsigned char value)
{
    return (value & 0x01);
}
bool ICCFD435ASetting::GetGclkDoubleAlong(unsigned char value)
{
    if ((value & 0x04) == 0x04)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int ICCFD435ASetting::GetConstantCurrentPoint(unsigned char value)
{
    switch ((value >> 3) & 0x03)
    {
    case 0x00:
        return 0;
    case 0x02:
        return 1;
    case 0x01:
        return 2;
    case 0x03:
        return 3;
    default:
        return 0;
    }
}
int ICCFD435ASetting::GetOutputResponse(unsigned char value)
{
    return ((value >> 7) & 0x01);
}
int ICCFD435ASetting::GetPWMGraySetting(unsigned char value)
{
    return ((value >> 2) & 0x03);
}
bool ICCFD435ASetting::GetLowGrayDisplayOptimization(unsigned char value)
{
    if (((value >> 5) & 0x01) == 0x01)
    {
        return false;
    }
    else
    {
        return true;
    }
}
int ICCFD435ASetting::GetLowGrayOptimizationMode(unsigned char value)
{
    return ((value >> 1) & 0x01);
}
int ICCFD435ASetting::GetCurrentGear(unsigned char value)
{
    return ((value >> 4) & 0x03);
}
int ICCFD435ASetting::GetCurrentGray(unsigned char value)
{
    return ((value >> 5) & 0x01);
}
int ICCFD435ASetting::GetCurrentGraySetting(unsigned char value)
{
    return ((value >> 6) & 0x03);
}






void ICCFD435ASetting::LoadForm()
{
    ui->LowGrayscaleRcomboBox->setCurrentIndex(GetLowGrayscale((uchar)ICPara[257]));
    ui->LowGrayscaleGcomboBox->setCurrentIndex(GetLowGrayscale((uchar)ICPara[259]));
    ui->LowGrayscaleBcomboBox->setCurrentIndex(GetLowGrayscale((uchar)ICPara[261]));

    ui->ColBlankAdjRcomboBox->setCurrentIndex(GetColBlankAdj((uchar)ICPara[263]));
    ui->ColBlankAdjGcomboBox->setCurrentIndex(GetColBlankAdj((uchar)ICPara[265]));
    ui->ColBlankAdjBcomboBox->setCurrentIndex(GetColBlankAdj((uchar)ICPara[267]));

    ui->ColBlankEnhanceRcheckBox->setChecked(GetColBlankEnhance((uchar)ICPara[263]));
    ui->ColBlankEnhanceGcheckBox->setChecked(GetColBlankEnhance((uchar)ICPara[265]));
    ui->ColBlankEnhanceBcheckBox->setChecked(GetColBlankEnhance((uchar)ICPara[267]));

    ui->ColumnBlankTimeRcomboBox->setCurrentIndex(GetColumnBlankTime((uchar)ICPara[268]));
    ui->ColumnBlankTimeGcomboBox->setCurrentIndex(GetColumnBlankTime((uchar)ICPara[270]));
    ui->ColumnBlankTimeBcomboBox->setCurrentIndex(GetColumnBlankTime((uchar)ICPara[272]));

    ui->CouplingStrengthAdjRcomboBox->setCurrentIndex(GetCouplingStrengthAdj((uchar)ICPara[263]));
    ui->CouplingStrengthAdjGcomboBox->setCurrentIndex(GetCouplingStrengthAdj((uchar)ICPara[265]));
    ui->CouplingStrengthAdjBcomboBox->setCurrentIndex(GetCouplingStrengthAdj((uchar)ICPara[267]));

    ui->CouplingRangeAdjRcomboBox->setCurrentIndex(GetCouplingRangeAdj((uchar)ICPara[262]));
    ui->CouplingRangeAdjGcomboBox->setCurrentIndex(GetCouplingRangeAdj((uchar)ICPara[264]));
    ui->CouplingRangeAdjBcomboBox->setCurrentIndex(GetCouplingRangeAdj((uchar)ICPara[266]));

    ui->CouplingOptimizationRcheckBox->setChecked(GetCouplingOptimization((uchar)ICPara[263]));
    ui->CouplingOptimizationGcheckBox->setChecked(GetCouplingOptimization((uchar)ICPara[265]));
    ui->CouplingOptimizationBcheckBox->setChecked(GetCouplingOptimization((uchar)ICPara[267]));

    ui->PreDriveEnablementRcheckBox->setChecked(GetPreDriveEnablement((uchar)ICPara[262]));
    ui->PreDriveEnablementGcheckBox->setChecked(GetPreDriveEnablement((uchar)ICPara[264]));
    ui->PreDriveEnablementBcheckBox->setChecked(GetPreDriveEnablement((uchar)ICPara[266]));

    ui->PreDriveModeRcomboBox->setCurrentIndex(GetPreDriveMode((uchar)ICPara[275]));
    ui->PreDriveModeGcomboBox->setCurrentIndex(GetPreDriveMode((uchar)ICPara[277]));
    ui->PreDriveModeBcomboBox->setCurrentIndex(GetPreDriveMode((uchar)ICPara[279]));

    ui->PreDriveTimeRcomboBox->setCurrentIndex(GetPreDriveTime((uchar)ICPara[275]));
    ui->PreDriveTimeGcomboBox->setCurrentIndex(GetPreDriveTime((uchar)ICPara[277]));
    ui->PreDriveTimeBcomboBox->setCurrentIndex(GetPreDriveTime((uchar)ICPara[279]));

    ui->LowGrayStrengthRcomboBox->setCurrentIndex(GetLowGrayStrength((uchar)ICPara[268],(uchar)ICPara[269]));
    ui->LowGrayStrengthGcomboBox->setCurrentIndex(GetLowGrayStrength((uchar)ICPara[270],(uchar)ICPara[271]));
    ui->LowGrayStrengthBcomboBox->setCurrentIndex(GetLowGrayStrength((uchar)ICPara[272],(uchar)ICPara[273]));

    ui->DataOutputRcomboBox->setCurrentIndex(GetLowGrayTime((uchar)ICPara[262]));
    ui->DataOutputGcomboBox->setCurrentIndex(GetLowGrayTime((uchar)ICPara[264]));
    ui->DataOutputBcomboBox->setCurrentIndex(GetLowGrayTime((uchar)ICPara[266]));

    ui->DynamicEnergySavingRcheckBox->setChecked(GetDynamicEnergySaving((uchar)ICPara[268]));
    ui->DynamicEnergySavingGcheckBox->setChecked(GetDynamicEnergySaving((uchar)ICPara[270]));
    ui->DynamicEnergySavingBcheckBox->setChecked(GetDynamicEnergySaving((uchar)ICPara[272]));

    ui->WakeupSettingRcomboBox->setCurrentIndex(GetWakeupSetting((uchar)ICPara[274]));
    ui->WakeupSettingGcomboBox->setCurrentIndex(GetWakeupSetting((uchar)ICPara[276]));
    ui->WakeupSettingBcomboBox->setCurrentIndex(GetWakeupSetting((uchar)ICPara[278]));

    ui->OpenCircuitDetectionThresholdRcomboBox->setCurrentIndex(GetOpenCircuitDetectionThreshold((uchar)ICPara[275]));
    ui->OpenCircuitDetectionThresholdGcomboBox->setCurrentIndex(GetOpenCircuitDetectionThreshold((uchar)ICPara[277]));
    ui->OpenCircuitDetectionThresholdBcomboBox->setCurrentIndex(GetOpenCircuitDetectionThreshold((uchar)ICPara[279]));

    ui->OpenTestPointAdjRcomboBox->setCurrentIndex(GetOpenTestPointAdj((uchar)ICPara[263]));
    ui->OpenTestPointAdjGcomboBox->setCurrentIndex(GetOpenTestPointAdj((uchar)ICPara[265]));
    ui->OpenTestPointAdjBcomboBox->setCurrentIndex(GetOpenTestPointAdj((uchar)ICPara[267]));

    ui->OpenCircuitProtcetEnableRcheckBox->setChecked(GetOpenCircuitProtcetEnable((uchar)ICPara[262]));
    ui->OpenCircuitProtcetEnableGcheckBox->setChecked(GetOpenCircuitProtcetEnable((uchar)ICPara[264]));
    ui->OpenCircuitProtcetEnableBcheckBox->setChecked(GetOpenCircuitProtcetEnable((uchar)ICPara[266]));

    ui->OpenCircuitDynamicDetecRcheckBox->setChecked(GetOpenCircuitDynamicDetec((uchar)ICPara[268]));
    ui->OpenCircuitDynamicDetecGcheckBox->setChecked(GetOpenCircuitDynamicDetec((uchar)ICPara[270]));
    ui->OpenCircuitDynamicDetecBcheckBox->setChecked(GetOpenCircuitDynamicDetec((uchar)ICPara[272]));

    ui->ScanModeRcomboBox->setCurrentIndex(GetScanMode((uchar)ICPara[262]));
    ui->ScanModeGcomboBox->setCurrentIndex(GetScanMode((uchar)ICPara[264]));
    ui->ScanModeBcomboBox->setCurrentIndex(GetScanMode((uchar)ICPara[266]));

    ui->GclkDoubleAlongRcheckBox->setChecked(GetGclkDoubleAlong((uchar)ICPara[268]));
    ui->GclkDoubleAlongGcheckBox->setChecked(GetGclkDoubleAlong((uchar)ICPara[270]));
    ui->GclkDoubleAlongBcheckBox->setChecked(GetGclkDoubleAlong((uchar)ICPara[272]));

    ui->ConstantCurrentPointRcomboBox->setCurrentIndex(GetConstantCurrentPoint((uchar)ICPara[268]));
    ui->ConstantCurrentPointGcomboBox->setCurrentIndex(GetConstantCurrentPoint((uchar)ICPara[270]));
    ui->ConstantCurrentPointBcomboBox->setCurrentIndex(GetConstantCurrentPoint((uchar)ICPara[272]));

    ui->OutputResponseRcomboBox->setCurrentIndex(GetOutputResponse((uchar)ICPara[275]));
    ui->OutputResponseGcomboBox->setCurrentIndex(GetOutputResponse((uchar)ICPara[277]));
    ui->OutputResponseBcomboBox->setCurrentIndex(GetOutputResponse((uchar)ICPara[279]));

    ui->PWMGraySettingRcomboBox->setCurrentIndex(GetPWMGraySetting((uchar)ICPara[262]));
    ui->PWMGraySettingGcomboBox->setCurrentIndex(GetPWMGraySetting((uchar)ICPara[264]));
    ui->PWMGraySettingBcomboBox->setCurrentIndex(GetPWMGraySetting((uchar)ICPara[266]));

    ui->LowGrayDisplayOptimizationRcheckBox->setChecked(GetLowGrayDisplayOptimization((uchar)ICPara[268]));
    ui->LowGrayDisplayOptimizationGcheckBox->setChecked(GetLowGrayDisplayOptimization((uchar)ICPara[270]));
    ui->LowGrayDisplayOptimizationBcheckBox->setChecked(GetLowGrayDisplayOptimization((uchar)ICPara[272]));

    ui->LowGrayOptimizationModeRcomboBox->setCurrentIndex(GetLowGrayOptimizationMode((uchar)ICPara[274]));
    ui->LowGrayOptimizationModeGcomboBox->setCurrentIndex(GetLowGrayOptimizationMode((uchar)ICPara[276]));
    ui->LowGrayOptimizationModeBcomboBox->setCurrentIndex(GetLowGrayOptimizationMode((uchar)ICPara[278]));

    ui->CurrentGearRcomboBox->setCurrentIndex(GetCurrentGear((uchar)ICPara[269]));
    ui->CurrentGearGcomboBox->setCurrentIndex(GetCurrentGear((uchar)ICPara[271]));
    ui->CurrentGearBcomboBox->setCurrentIndex(GetCurrentGear((uchar)ICPara[273]));


    ui->OutPutPowerTubeRcomboBox->setCurrentIndex(GetCurrentGraySetting((uchar)ICPara[274]));
    ui->OutPutPowerTubeGcomboBox->setCurrentIndex(GetCurrentGraySetting((uchar)ICPara[276]));
    ui->OutPutPowerTubeBcomboBox->setCurrentIndex(GetCurrentGraySetting((uchar)ICPara[278]));

}








/// <summary>
/// 设置对应寄存器的值
/// </summary>
/// <param name="Num"></param> 第几个寄存器 1-4
/// <param name="RGB"></param> 值为0,1,2为R,G,B
/// <param name="hl"></param> 高位还是地位，地位为0，,高位为1
/// <param name="value1"></param> 清0的值
/// <param name="value2"></param> 置1的值
void ICCFD435ASetting::SetRegValue(int Num, int RGB, int hl, unsigned char value1, unsigned char value2)
{
    unsigned char value = (uchar)ICPara[0x100 + (Num - 1) * 6 + RGB * 2 + hl];

    value &= value1;
    value |= value2;

    ICPara[0x100 + (Num - 1) * 6 + RGB * 2 + hl] = value;
}
void ICCFD435ASetting::SetLowGrayscale(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(1, RGB, 1, 0x9F, 0x00);
        break;
    case 1:
        SetRegValue(1, RGB, 1, 0x9F, 0x20);
        break;
    case 2:
        SetRegValue(1, RGB, 1, 0x9F, 0x40);
        break;
    case 3:
        SetRegValue(1, RGB, 1, 0x9F, 0x60);
        break;
    }
}
void ICCFD435ASetting::SetColBlankAdj(int index, int RGB)
{
    switch(index)
    {
    case 0:
        SetRegValue(2, RGB, 1, 0x1F, 0x00);
        break;
    case 1:
        SetRegValue(2, RGB, 1, 0x1F, 0x80);
        break;
    case 2:
        SetRegValue(2, RGB, 1, 0x1F, 0x40);
        break;
    case 3:
        SetRegValue(2, RGB, 1, 0x1F, 0xC0);
        break;
    case 4:
        SetRegValue(2, RGB, 1, 0x1F, 0x20);
        break;
    case 5:
        SetRegValue(2, RGB, 1, 0x1F, 0xA0);
        break;
    case 6:
        SetRegValue(2, RGB, 1, 0x1F, 0x60);
        break;
    case 7:
        SetRegValue(2, RGB, 1, 0x1F, 0xE0);
        break;
    }
}
void ICCFD435ASetting::SetColBlankEnhance(bool check,int RGB)
{
    if (check)
    {
        SetRegValue(2, RGB, 1, 0xEF, 0x00);
    }
    else
    {
        SetRegValue(2, RGB, 1, 0xEF, 0x10);
    }
}
void ICCFD435ASetting::SetColumnBlankTime(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(3, RGB, 0, 0xFE, 0x00);
        break;
    case 1:
        SetRegValue(3, RGB, 0, 0xFE, 0x01);
        break;
    default:
        break;
    }
}
void ICCFD435ASetting::SetCouplingStrengthAdj(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(2, RGB, 1, 0xF3, 0x00);
        break;
    case 1:
        SetRegValue(2, RGB, 1, 0xF3, 0x04);
        break;
    case 2:
        SetRegValue(2, RGB, 1, 0xF3, 0x08);
        break;
    case 3:
        SetRegValue(2, RGB, 1, 0xF3, 0x0C);
        break;
    }
}
void ICCFD435ASetting::SetCouplingRangeAdj(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(2, RGB, 0, 0x9F, 0x00);
        break;
    case 1:
        SetRegValue(2, RGB, 0, 0x9F, 0x20);
        break;
    case 2:
        SetRegValue(2, RGB, 0, 0x9F, 0x40);
        break;
    case 3:
        SetRegValue(2, RGB, 0, 0x9F, 0x60);
        break;
    }
}
void ICCFD435ASetting::SetCouplingOptimization(bool check, int RGB)
{
    if (check)
    {
        SetRegValue(2, RGB, 1, 0xFE, 0x01);
    }
    else
    {
        SetRegValue(2, RGB, 1, 0xFE, 0x00);
    }
}
void ICCFD435ASetting::SetPreDriveEnablement(bool check, int RGB)
{
    if (check)
    {
        SetRegValue(2, RGB, 0, 0xEF, 0x10);
    }
    else
    {
        SetRegValue(2, RGB, 0, 0xEF, 0x00);
    }
}
void ICCFD435ASetting::SetPreDriveMode(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(4, RGB, 1, 0xEF, 0x00);
        break;
    case 1:
        SetRegValue(4, RGB, 1, 0xEF, 0x10);
        break;
    default:
        break;
    }
}
void ICCFD435ASetting::SetPreDriveTime(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(4, RGB, 1, 0xF3, 0x00);
        break;
    case 1:
        SetRegValue(4, RGB, 1, 0xF3, 0x04);
        break;
    case 2:
        SetRegValue(4, RGB, 1, 0xF3, 0x08);
        break;
    case 3:
        SetRegValue(4, RGB, 1, 0xF3, 0x0C);
        break;
    }
}
void ICCFD435ASetting::SetLowGrayStrength(int index, int RGB)
{
    int value = (uchar)ICPara[0x10C + RGB * 2 + 0] + (uchar)ICPara[0x10C + RGB * 2 + 1] * 256;

    value &= 0xF07F;
    value |= ((32 - (index + 1)) << 7);

    ICPara[0x10C + RGB * 2 + 0] = (unsigned char)(value & 0xFF);
    ICPara[0x10C + RGB * 2 + 1] = (unsigned char)((value >> 8) & 0xFF);
}
void ICCFD435ASetting::SetLowGrayTime(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(2, RGB, 0, 0x7F, 0x00);
        break;
    case 1:
        SetRegValue(2, RGB, 0, 0x7F, 0x80);
        break;
    default:
        break;
    }
}
void ICCFD435ASetting::SetDynamicEnergySaving(bool check, int RGB)
{
    if (check)
    {
        SetRegValue(3, RGB, 0, 0xFD, 0x02);
    }
    else
    {
        SetRegValue(3, RGB, 0, 0xFD, 0x00);
    }
}
void ICCFD435ASetting::SetWakeupSetting(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(4, RGB, 0, 0xFE, 0x00);
        break;
    case 1:
        SetRegValue(4, RGB, 0, 0xFE, 0x01);
        break;
    default:
        break;
    }
}
void ICCFD435ASetting::SetOpenCircuitDetectionThreshold(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(4, RGB, 1, 0xFC, 0x00);
        break;
    case 1:
        SetRegValue(4, RGB, 1, 0xFC, 0x01);
        break;
    case 2:
        SetRegValue(4, RGB, 1, 0xFC, 0x02);
        break;
    case 3:
        SetRegValue(4, RGB, 1, 0xFC, 0x03);
        break;
    }
}
void ICCFD435ASetting::SetOpenTestPointAdj(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(2, RGB, 1, 0xFD, 0x00);
        break;
    case 1:
        SetRegValue(2, RGB, 1, 0xFD, 0x02);
        break;
    default:
        break;
    }
}
void ICCFD435ASetting::SetOpenCircuitProtcetEnable(bool check, int RGB)
{
    if (check)
    {
        SetRegValue(2, RGB, 0, 0xFD, 0x02);
    }
    else
    {
        SetRegValue(2, RGB, 0, 0xFD, 0x00);
    }
}
void ICCFD435ASetting::SetOpenCircuitDynamicDetec(bool check, int RGB)
{
    if (check)
    {
        SetRegValue(3, RGB, 0, 0xBF, 0x40);
    }
    else
    {
        SetRegValue(3, RGB, 0, 0xBF, 0x00);
    }
}
void ICCFD435ASetting::SetScanMode(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(2, RGB, 0, 0xFE, 0x00);
        break;
    case 1:
        SetRegValue(2, RGB, 0, 0xFE, 0x01);
        break;
    default:
        break;
    }
}
void ICCFD435ASetting::SetGclkDoubleAlong(bool check, int RGB)
{
    if (check)
    {
        SetRegValue(3, RGB, 0, 0xFB, 0x04);
    }
    else
    {
        SetRegValue(3, RGB, 0, 0xFB, 0x00);
    }
}
void ICCFD435ASetting::SetConstantCurrentPoint(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(3, RGB, 0, 0xE7, 0x00);
        break;
    case 1:
        SetRegValue(3, RGB, 0, 0xE7, 0x10);
        break;
    case 2:
        SetRegValue(3, RGB, 0, 0xE7, 0x08);
        break;
    case 3:
        SetRegValue(3, RGB, 0, 0xE7, 0x18);
        break;
    }
}
void ICCFD435ASetting::SetOutputResponse(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(4, RGB, 1, 0x7F, 0x00);
        break;
    case 1:
        SetRegValue(4, RGB, 1, 0x7F, 0x80);
        break;
    default:
        break;
    }
}
void ICCFD435ASetting::SetPWMGraySetting(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(2, RGB, 0, 0xF3, 0x00);
        break;
    case 1:
        SetRegValue(2, RGB, 0, 0xF3, 0x04);
        break;
    case 2:
        SetRegValue(2, RGB, 0, 0xF3, 0x08);
        break;
    case 3:
        SetRegValue(2, RGB, 0, 0xF3, 0x0C);
        break;
    }
}
void ICCFD435ASetting::SetLowGrayDisplayOptimization(bool check, int RGB)
{
    if (check)
    {
        SetRegValue(3, RGB, 0, 0xDF, 0x00);
    }
    else
    {
        SetRegValue(3, RGB, 0, 0xDF, 0x20);
    }
}
void ICCFD435ASetting::SetLowGrayOptimizationMode(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(4, RGB, 0, 0xFD, 0x00);
        break;
    case 1:
        SetRegValue(4, RGB, 0, 0xFD, 0x02);
        break;
    default:
        break;
    }
}
void ICCFD435ASetting::SetCurrentGear(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(3, RGB, 1, 0xCF, 0x00);
        break;
    case 1:
        SetRegValue(3, RGB, 1, 0xCF, 0x10);
        break;
    case 2:
        SetRegValue(3, RGB, 1, 0xCF, 0x20);
        break;
    case 3:
        SetRegValue(3, RGB, 1, 0xCF, 0x30);
        break;
    }
}
void ICCFD435ASetting::SetCurrentGray(int index, int RGB)
{
    switch(index)
    {
    case 0:
        SetRegValue(4, RGB, 0, 0xDF, 0x00);
        break;
    case 1:
        SetRegValue(4, RGB, 0, 0xDF, 0x20);
        break;
    default:
        break;
    }
}
void ICCFD435ASetting::SetCurrentGraySetting(int index, int RGB)
{
    switch (index)
    {
    case 0:
        SetRegValue(4, RGB, 0, 0x3F, 0x00);
        break;
    case 1:
        SetRegValue(4, RGB, 0, 0x3F, 0x40);
        break;
    case 2:
        SetRegValue(4, RGB, 0, 0x3F, 0x80);
        break;
    case 3:
        SetRegValue(4, RGB, 0, 0x3F, 0xC0);
        break;
    default:
        break;
    }
}


void ICCFD435ASetting::on_SettingpushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);
    SetLowGrayscale(ui->LowGrayscaleRcomboBox->currentIndex(),0);
    SetLowGrayscale(ui->LowGrayscaleGcomboBox->currentIndex(),1);
    SetLowGrayscale(ui->LowGrayscaleBcomboBox->currentIndex(),2);

    SetColBlankAdj(ui->ColBlankAdjRcomboBox->currentIndex(),0);
    SetColBlankAdj(ui->ColBlankAdjGcomboBox->currentIndex(),1);
    SetColBlankAdj(ui->ColBlankAdjBcomboBox->currentIndex(),2);

    SetColBlankEnhance(ui->ColBlankEnhanceRcheckBox->isChecked(),0);
    SetColBlankEnhance(ui->ColBlankEnhanceGcheckBox->isChecked(),1);
    SetColBlankEnhance(ui->ColBlankEnhanceBcheckBox->isChecked(),2);

    SetColumnBlankTime(ui->ColumnBlankTimeRcomboBox->currentIndex(),0);
    SetColumnBlankTime(ui->ColumnBlankTimeGcomboBox->currentIndex(),1);
    SetColumnBlankTime(ui->ColumnBlankTimeBcomboBox->currentIndex(),2);

    SetCouplingStrengthAdj(ui->CouplingStrengthAdjRcomboBox->currentIndex(),0);
    SetCouplingStrengthAdj(ui->CouplingStrengthAdjGcomboBox->currentIndex(),1);
    SetCouplingStrengthAdj(ui->CouplingStrengthAdjBcomboBox->currentIndex(),2);

    SetCouplingRangeAdj(ui->CouplingRangeAdjRcomboBox->currentIndex(),0);
    SetCouplingRangeAdj(ui->CouplingRangeAdjGcomboBox->currentIndex(),1);
    SetCouplingRangeAdj(ui->CouplingRangeAdjBcomboBox->currentIndex(),2);

    SetCouplingOptimization(ui->CouplingOptimizationRcheckBox->isChecked(),0);
    SetCouplingOptimization(ui->CouplingOptimizationGcheckBox->isChecked(),1);
    SetCouplingOptimization(ui->CouplingOptimizationBcheckBox->isChecked(),2);

    SetPreDriveEnablement(ui->PreDriveEnablementRcheckBox->isChecked(),0);
    SetPreDriveEnablement(ui->PreDriveEnablementGcheckBox->isChecked(),1);
    SetPreDriveEnablement(ui->PreDriveEnablementBcheckBox->isChecked(),2);

    SetPreDriveMode(ui->PreDriveModeRcomboBox->currentIndex(),0);
    SetPreDriveMode(ui->PreDriveModeGcomboBox->currentIndex(),1);
    SetPreDriveMode(ui->PreDriveModeBcomboBox->currentIndex(),2);

    SetPreDriveTime(ui->PreDriveTimeRcomboBox->currentIndex(),0);
    SetPreDriveTime(ui->PreDriveTimeGcomboBox->currentIndex(),1);
    SetPreDriveTime(ui->PreDriveTimeBcomboBox->currentIndex(),2);

    SetLowGrayStrength(ui->LowGrayStrengthRcomboBox->currentIndex(),0);
    SetLowGrayStrength(ui->LowGrayStrengthGcomboBox->currentIndex(),1);
    SetLowGrayStrength(ui->LowGrayStrengthBcomboBox->currentIndex(),2);

    SetLowGrayTime(ui->DataOutputRcomboBox->currentIndex(),0);
    SetLowGrayTime(ui->DataOutputGcomboBox->currentIndex(),1);
    SetLowGrayTime(ui->DataOutputBcomboBox->currentIndex(),2);

    SetDynamicEnergySaving(ui->DynamicEnergySavingRcheckBox->isChecked(),0);
    SetDynamicEnergySaving(ui->DynamicEnergySavingGcheckBox->isChecked(),1);
    SetDynamicEnergySaving(ui->DynamicEnergySavingBcheckBox->isChecked(),2);

    SetWakeupSetting(ui->WakeupSettingRcomboBox->currentIndex(),0);
    SetWakeupSetting(ui->WakeupSettingGcomboBox->currentIndex(),1);
    SetWakeupSetting(ui->WakeupSettingBcomboBox->currentIndex(),2);

    SetOpenCircuitDetectionThreshold(ui->OpenCircuitDetectionThresholdRcomboBox->currentIndex(),0);
    SetOpenCircuitDetectionThreshold(ui->OpenCircuitDetectionThresholdGcomboBox->currentIndex(),1);
    SetOpenCircuitDetectionThreshold(ui->OpenCircuitDetectionThresholdBcomboBox->currentIndex(),2);

    SetOpenTestPointAdj(ui->OpenTestPointAdjRcomboBox->currentIndex(),0);
    SetOpenTestPointAdj(ui->OpenTestPointAdjGcomboBox->currentIndex(),1);
    SetOpenTestPointAdj(ui->OpenTestPointAdjBcomboBox->currentIndex(),2);

    SetOpenCircuitProtcetEnable(ui->OpenCircuitProtcetEnableRcheckBox->isChecked(),0);
    SetOpenCircuitProtcetEnable(ui->OpenCircuitProtcetEnableGcheckBox->isChecked(),1);
    SetOpenCircuitProtcetEnable(ui->OpenCircuitProtcetEnableBcheckBox->isChecked(),2);

    SetOpenCircuitDynamicDetec(ui->OpenCircuitDynamicDetecRcheckBox->isChecked(),0);
    SetOpenCircuitDynamicDetec(ui->OpenCircuitDynamicDetecGcheckBox->isChecked(),1);
    SetOpenCircuitDynamicDetec(ui->OpenCircuitDynamicDetecBcheckBox->isChecked(),2);

    SetScanMode(ui->ScanModeRcomboBox->currentIndex(),0);
    SetScanMode(ui->ScanModeGcomboBox->currentIndex(),1);
    SetScanMode(ui->ScanModeBcomboBox->currentIndex(),2);

    SetGclkDoubleAlong(ui->GclkDoubleAlongRcheckBox->isChecked(),0);
    SetGclkDoubleAlong(ui->GclkDoubleAlongGcheckBox->isChecked(),1);
    SetGclkDoubleAlong(ui->GclkDoubleAlongBcheckBox->isChecked(),2);

    SetConstantCurrentPoint(ui->ConstantCurrentPointRcomboBox->currentIndex(),0);
    SetConstantCurrentPoint(ui->ConstantCurrentPointGcomboBox->currentIndex(),1);
    SetConstantCurrentPoint(ui->ConstantCurrentPointBcomboBox->currentIndex(),2);

    SetOutputResponse(ui->OutputResponseRcomboBox->currentIndex(),0);
    SetOutputResponse(ui->OutputResponseGcomboBox->currentIndex(),1);
    SetOutputResponse(ui->OutputResponseBcomboBox->currentIndex(),2);

    SetPWMGraySetting(ui->PWMGraySettingRcomboBox->currentIndex(),0);
    SetPWMGraySetting(ui->PWMGraySettingGcomboBox->currentIndex(),1);
    SetPWMGraySetting(ui->PWMGraySettingBcomboBox->currentIndex(),2);

    SetLowGrayDisplayOptimization(ui->LowGrayDisplayOptimizationRcheckBox->isChecked(),0);
    SetLowGrayDisplayOptimization(ui->LowGrayDisplayOptimizationGcheckBox->isChecked(),1);
    SetLowGrayDisplayOptimization(ui->LowGrayDisplayOptimizationBcheckBox->isChecked(),2);

    SetLowGrayOptimizationMode(ui->LowGrayOptimizationModeRcomboBox->currentIndex(),0);
    SetLowGrayOptimizationMode(ui->LowGrayOptimizationModeGcomboBox->currentIndex(),1);
    SetLowGrayOptimizationMode(ui->LowGrayOptimizationModeBcomboBox->currentIndex(),2);

    SetCurrentGear(ui->CurrentGearRcomboBox->currentIndex(),0);
    SetCurrentGear(ui->CurrentGearGcomboBox->currentIndex(),1);
    SetCurrentGear(ui->CurrentGearBcomboBox->currentIndex(),2);


    SetCurrentGraySetting(ui->OutPutPowerTubeRcomboBox->currentIndex(),0);
    SetCurrentGraySetting(ui->OutPutPowerTubeGcomboBox->currentIndex(),1);
    SetCurrentGraySetting(ui->OutPutPowerTubeBcomboBox->currentIndex(),2);

//    //电流灰度分量亮度设置
//    if (ui->CurrentGrayRcomboBox->currentIndex() == 0x01)
//    {
//        ICPara[0xB8] = ui->CurrentGrayBrightnessRspinBox->value();
//    }
//    if (ui->CurrentGrayGcomboBox->currentIndex() == 0x01)
//    {
//        ICPara[0xB9] = ui->CurrentGrayBrightnessGspinBox->value();
//    }
//    if (ui->CurrentGrayBcomboBox->currentIndex() == 0x01)
//    {
//        ICPara[0xBA] = ui->CurrentGrayBrightnessBspinBox->value();
//    }



    bool result = UniversalInterface::SendALLPara();
    this->setCursor(Qt::ArrowCursor);
    if (result)
    {
        UniversalInterface::MessageBoxShow(tr("设置"),tr("设置成功"));
    }
    else{
        UniversalInterface::MessageBoxShow(tr("设置"),tr("设置失败"));
    }





}



//void ICCFD435ASetting::on_CurrentGrayRcomboBox_currentIndexChanged(int index)
//{
//    if (index == 0x01)
//    {
//        ui->CurrentGraySettingRcomboBox->setEnabled(true);
//        ui->CurrentGrayBrightnessRspinBox->setEnabled(true);
//    }
//    else
//    {
//        ui->CurrentGraySettingRcomboBox->setEnabled(false);
//        ui->CurrentGrayBrightnessRspinBox->setEnabled(false);
//    }
//}

//void ICCFD435ASetting::on_CurrentGrayGcomboBox_currentIndexChanged(int index)
//{
//    if (index == 0x01)
//    {
//        ui->CurrentGraySettingGcomboBox->setEnabled(true);
//        ui->CurrentGrayBrightnessGspinBox->setEnabled(true);
//    }
//    else
//    {
//        ui->CurrentGraySettingGcomboBox->setEnabled(false);
//        ui->CurrentGrayBrightnessGspinBox->setEnabled(false);
//    }
//}

//void ICCFD435ASetting::on_CurrentGrayBcomboBox_currentIndexChanged(int index)
//{
//    if (index == 0x01)
//    {
//        ui->CurrentGraySettingBcomboBox->setEnabled(true);
//        ui->CurrentGrayBrightnessBspinBox->setEnabled(true);
//    }
//    else
//    {
//        ui->CurrentGraySettingBcomboBox->setEnabled(false);
//        ui->CurrentGrayBrightnessBspinBox->setEnabled(false);
//    }
//}

void ICCFD435ASetting::on_AdvancedSettingpushButton_clicked()
{
    ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
    icadvanced->show();

}
