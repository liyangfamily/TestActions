#include "icxm11202gsetting.h"
#include "ui_icxm11202gsetting.h"
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "advancedsetting.h"



#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif
ICXM11202GSetting::ICXM11202GSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ICXM11202GSetting)
{
    ui->setupUi(this);
    Qt::WindowFlags windowFlag  = Qt::Dialog;
//    windowFlag                  |= Qt::WindowMinimizeButtonHint;
//    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    setWindowFlags(windowFlag);


    regpara.resize(2048);
    for (int i=0;i<regpara.length();i++)
    {
        regpara[i] = 0;
    }

    filename = LBLUIHelper::appParamDataLocation();
    QByteArray result;
    result = LAPI::ReadXMICParam(0x00,0x00);

    if (sizeof(result) > 0)
    {
        for (int i=0;i<result.length();i++)
        {
            regpara[i] = result[i];
        }
    }
    else
    {
        QByteArray data;
        data = Readbin(filename + "/regpara.bin");

        for (int i=0;i<data.length();i++)
        {
            regpara[i] = data[i];
        }
    }

    ParamToShow();
}



ICXM11202GSetting::~ICXM11202GSetting()
{
    delete ui;
}

int ICXM11202GSetting::GetDataToShow(ELY11202GroupIndex index, ELY11202RGB rgb)
{
    if (index == ELI_RefreshRate ||
        index == ELI_Chip_Column ||
        index == ELI_Chip_Row ||

        index == ELI_Current_Adjust1 ||
        index == ELI_Current_Adjust2 ||

        index == ELI_Current_Gain ||
        index == ELI_Disapparate_Level ||
        index == ELI_LowGray_Compen1 ||
        index == ELI_LowGray_Compen2 ||
        index == ELI_LowGray_Even ||
        index == ELI_DefectDetect_Level)
    {
        int tmpIndex = (int)index + (int)rgb;
        unsigned char tmpValue;
        if (index == ELI_Current_Adjust2)
        {
            tmpIndex = (int)ELI_Current_Adjust1 + (int)rgb;
        }
        else if (index == ELI_RefreshRate ||
            index == ELI_Chip_Column ||
            index == ELI_Chip_Row)
        {
            tmpIndex = (int)index;
        }

        tmpValue = regpara[tmpIndex * 6 + 5];
        switch ((int)index)
        {
        case ELI_RefreshRate:
            tmpValue &= 0x3F;
            break;
        case ELI_Chip_Column:
        case ELI_Chip_Row:
            return tmpValue;
        case ELI_Current_Adjust1:
            tmpValue = (tmpValue&0xC0)>>6;
            return (int)tmpValue;
            break;
        case ELI_Current_Adjust2:
            tmpValue = (tmpValue & 0x3F);
            return (int)tmpValue;
            break;
        case ELI_Current_Gain:
            switch (rgb)
            {
            case ELC_R:
                tmpValue &= 0x1F;
                break;
            case ELC_G:
                tmpValue &= 0x0F;
                break;
            case ELC_B:
                tmpValue &= 0x0F;
                break;
            }
            break;
        case ELI_Disapparate_Level:
            tmpValue &= 0x1F;
            break;
        case ELI_LowGray_Compen1:
            tmpValue &= 0x1F;
            break;
        case ELI_LowGray_Compen2:
            tmpValue &= 0x3F;
            break;
        case ELI_LowGray_Even:
            tmpValue &= 0x1F;
            break;
        case ELI_DefectDetect_Level:
            tmpValue &= 0x1F;
            break;
        }
        return (int)tmpValue + 1;
    }

    if (index == ELI_GradualTransition_Optimize)
    {
        int tmpIndex = (int)index;
        switch (rgb)
        {
        case ELC_R:
        {
            unsigned char tmpValue = regpara[tmpIndex * 6 + 5];

            tmpValue &= 0x0F;
            return tmpValue;
        }
        break;
        case ELC_G:
        {
            unsigned char tmpValue = regpara[tmpIndex * 6 + 5];

            tmpValue = ((tmpValue&0xF0)>>4);
            return tmpValue;
        }
        break;
        case ELC_B:
        {
            tmpIndex++;
            unsigned char tmpValue = regpara[tmpIndex * 6 + 5];

            tmpValue &= 0x0F;
            return tmpValue;
        }
        break;
        }
    }

    Q_ASSERT(0);
    return 0;
}

bool ICXM11202GSetting::SetShowToData(ELY11202GroupIndex index, ELY11202RGB rgb, int value)
{
    if (index == ELI_RefreshRate ||
        index == ELI_Chip_Column ||
        index == ELI_Chip_Row ||

        index == ELI_Current_Adjust1 ||
        index == ELI_Current_Adjust2 ||

        index == ELI_Current_Gain ||
        index == ELI_Disapparate_Level ||
        index == ELI_LowGray_Compen1 ||
        index == ELI_LowGray_Compen2 ||
        index == ELI_LowGray_Even ||
        index == ELI_DefectDetect_Level)
    {
        //序号
        int tmpIndex = (int)index + (int)rgb;
        if (index == ELI_Current_Adjust2)
        {
            tmpIndex = (int)ELI_Current_Adjust1 + (int)rgb;
        }
        else if (index == ELI_RefreshRate ||
            index == ELI_Chip_Column ||
            index == ELI_Chip_Row)
        {
            tmpIndex = (int)index;
        }
        //值
        unsigned char tmpValue = (unsigned char)value-1;
        //有效性范围限定
        switch ((int)index)
        {
        case ELI_RefreshRate:
            tmpValue &= 0x3F;
            break;
        case ELI_Chip_Column:
        {
            tmpValue = (unsigned char)value;
            if (tmpValue<24 || tmpValue > 40)
            {
                Q_ASSERT(0);
                tmpValue = 24;
            }
        }
        break;
        case ELI_Chip_Row:
        {
            tmpValue = (unsigned char)value;
            if (tmpValue<16 || tmpValue > 36)
            {
                Q_ASSERT(0);
                tmpValue = 16;
            }
        }
        break;
        case ELI_Current_Adjust1:
        {
            tmpValue = (unsigned char)value;
            if (tmpValue < 1 || tmpValue>2)
            {
                Q_ASSERT(0);
                tmpValue = 1;
            }

            tmpValue = (regpara[tmpIndex * 6 + 5] & 0x3F) | (tmpValue << 6);
        }
        break;
        case ELI_Current_Adjust2:
        {
            tmpValue = (unsigned char)value;
            tmpValue &= 0x3F;

            tmpValue = (regpara[tmpIndex * 6 + 5] & 0xC0) | tmpValue;
        }
        break;
        case ELI_Current_Gain:
            switch (rgb)
            {
            case ELC_R:
                tmpValue &= 0x1F;
                break;
            case ELC_G:
                tmpValue &= 0x0F;
                break;
            case ELC_B:
                tmpValue &= 0x0F;
                break;
            }
            break;
        case ELI_Disapparate_Level:
            tmpValue &= 0x1F;
            break;
        case ELI_LowGray_Compen1:
            tmpValue &= 0x1F;
            break;
        case ELI_LowGray_Compen2:
            tmpValue &= 0x3F;
            break;
        case ELI_LowGray_Even:
            tmpValue &= 0x1F;
            break;
        case ELI_DefectDetect_Level:
            tmpValue &= 0x1F;
            break;
        }

        regpara[tmpIndex * 6 + 5] = tmpValue;

        regpara[tmpIndex * 6 + 0] = 0;
        regpara[tmpIndex * 6 + 1] = 0;
        regpara[tmpIndex * 6 + 2] = 0;
        switch ((int)index)
        {
        case ELI_RefreshRate:
            regpara[tmpIndex * 6 + 3] = 0x84;
            regpara[tmpIndex * 6 + 4] = 0xB2;
            break;
        case ELI_Chip_Column:
            regpara[tmpIndex * 6 + 3] = 0xA1;
            regpara[tmpIndex * 6 + 4] = 0xC0;
            break;
        case ELI_Chip_Row:
            regpara[tmpIndex * 6 + 3] = 0xA2;
            regpara[tmpIndex * 6 + 4] = 0xC0;
            break;

        case ELI_Current_Adjust1:
        case ELI_Current_Adjust2:
            regpara[tmpIndex * 6 + 3] = 0xA2 - (unsigned char)rgb;
            regpara[tmpIndex * 6 + 4] = 0xA5;
            break;
        case ELI_Current_Gain:
            regpara[tmpIndex * 6 + 3] = 0x80 + (unsigned char)rgb;
            regpara[tmpIndex * 6 + 4] = 0xD1;
            break;
        case ELI_Disapparate_Level:
            regpara[tmpIndex * 6 + 3] = 0xD3-(unsigned char)rgb;
            regpara[tmpIndex * 6 + 4] = 0xA5;
            break;
        case ELI_LowGray_Compen1:
            regpara[tmpIndex * 6 + 3] = 0xC3 - (unsigned char)rgb;
            regpara[tmpIndex * 6 + 4] = 0xA5;
            break;
        case ELI_LowGray_Compen2:
            regpara[tmpIndex * 6 + 3] = 0x81 + (unsigned char)rgb*0x10;
            regpara[tmpIndex * 6 + 4] = 0xD7;
            break;
        case ELI_LowGray_Even:
            regpara[tmpIndex * 6 + 3] = 0x86 + (unsigned char)rgb * 0x10;
            regpara[tmpIndex * 6 + 4] = 0xD7;
            break;
        case ELI_DefectDetect_Level:
            regpara[tmpIndex * 6 + 3] = 0xF0 + (unsigned char)rgb;
            regpara[tmpIndex * 6 + 4] = 0xA4;
            break;
        }
        return true;
    }

    if (index == ELI_GradualTransition_Optimize)
    {
        unsigned char tmpValue = (unsigned char)value;
        tmpValue &= 0x0F;

        int tmpIndex = (int)index;
        switch (rgb)
        {
        case ELC_R:
        {
            regpara[tmpIndex * 6 + 5] = (regpara[tmpIndex * 6 + 5] & 0xF0) | tmpValue;
            regpara[tmpIndex * 6 + 0] = 0;
            regpara[tmpIndex * 6 + 1] = 0;
            regpara[tmpIndex * 6 + 2] = 0;
            regpara[tmpIndex * 6 + 3] = 0xB5;
            regpara[tmpIndex * 6 + 4] = 0xD6;
        }
        break;
        case ELC_G:
        {
            regpara[tmpIndex * 6 + 5] = (regpara[tmpIndex * 6 + 5] & 0x0F) | (tmpValue << 4);
            regpara[tmpIndex * 6 + 0] = 0;
            regpara[tmpIndex * 6 + 1] = 0;
            regpara[tmpIndex * 6 + 2] = 0;
            regpara[tmpIndex * 6 + 3] = 0xB5;
            regpara[tmpIndex * 6 + 4] = 0xD6;
        }
        break;
        case ELC_B:
        {
            tmpIndex++;
            regpara[tmpIndex * 6 + 5] = (regpara[tmpIndex * 6 + 5] & 0xF0) | tmpValue;
            regpara[tmpIndex * 6 + 0] = 0;
            regpara[tmpIndex * 6 + 1] = 0;
            regpara[tmpIndex * 6 + 2] = 0;
            regpara[tmpIndex * 6 + 3] = 0xB4;
            regpara[tmpIndex * 6 + 4] = 0xD6;
        }
        break;
        }
        return true;
    }

    Q_ASSERT(0);
    return false;
}

/// <summary>
/// 设置对应寄存器的值
/// </summary>
void ICXM11202GSetting::SetRegValue(int Num, int value)
{
    regpara[Num * 6 + 5] = value;
}
unsigned char ICXM11202GSetting::GetRegValue(int Num)
{
    return regpara[Num * 6 + 5];
}

///读取txt文件
QByteArray ICXM11202GSetting::ReadFile(QString filepath)
{
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }

    QByteArray array;

    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);

        if(str.left(2)=="//" || str.count()<3)
        {
            continue;
        }

        while (true)
        {
            QString strTemp = str.left(2);
            str = str.right(str.count() - 3);
            if (2 == strTemp.count())
            {
                unsigned char tempByte = (unsigned char)(strTemp.toUInt(nullptr, 16));
                array.append(tempByte);
            }
            if (str.count() < 2)
            {
                break;
            }
        }
    }

    return array;
}


///写入txt文件
bool ICXM11202GSetting::WriteFile(QString filepath,QByteArray array)
{
    QFile file(filepath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    file.write("//XM11202_default_initial_code\n\n");

    QString str;
    for (int i = 0; i < array.length(); i++)
    {
        if (0 == i % 6)
        {
            str += "\n";
        }
        str += QString::number(array[i] & 0xFF, 16).toUpper().rightJustified(2, QChar('0')) + " ";
    }
    file.write(str.toUtf8());
    file.flush();
    file.close();


    return true;
}

void ICXM11202GSetting::ParamToShow()
{
    ShowInfo = true;
    //刷新倍率
    ui->RefreshRatelspinBox->setValue(GetDataToShow(ELI_RefreshRate, ELC_R));
    //单芯片列行
    ui->SingleChipColspinBox->setValue(GetDataToShow(ELI_Chip_Column, ELC_R));
    ui->SingleChipRowspinBox->setValue(GetDataToShow(ELI_Chip_Row, ELC_R));

    ui->CurrentRegulation1RspinBox->setValue(GetDataToShow(ELI_Current_Adjust1, ELC_R));
    ui->CurrentRegulation1GspinBox->setValue(GetDataToShow(ELI_Current_Adjust1, ELC_G));
    ui->CurrentRegulation1BspinBox->setValue(GetDataToShow(ELI_Current_Adjust1, ELC_B));

    ui->CurrentRegulation2RspinBox->setValue(GetDataToShow(ELI_Current_Adjust2, ELC_R));
    ui->CurrentRegulation2GspinBox->setValue(GetDataToShow(ELI_Current_Adjust2, ELC_G));
    ui->CurrentRegulation2BspinBox->setValue(GetDataToShow(ELI_Current_Adjust2, ELC_B));

    ui->CurrentGainRspinBox->setValue(GetDataToShow(ELI_Current_Gain, ELC_R));
    ui->CurrentGainGspinBox->setValue(GetDataToShow(ELI_Current_Gain, ELC_G));
    ui->CurrentGainBspinBox->setValue(GetDataToShow(ELI_Current_Gain, ELC_B));

    ui->EliminationLevelRspinBox->setValue(GetDataToShow(ELI_Disapparate_Level, ELC_R));
    ui->EliminationLevelGspinBox->setValue(GetDataToShow(ELI_Disapparate_Level, ELC_G));
    ui->EliminationLevelBspinBox->setValue(GetDataToShow(ELI_Disapparate_Level, ELC_B));

    ui->FineAdjLGCCRspinBox->setValue(GetDataToShow(ELI_LowGray_Compen1, ELC_R));
    ui->FineAdjLGCCGspinBox->setValue(GetDataToShow(ELI_LowGray_Compen1, ELC_G));
    ui->FineAdjLGCCBspinBox->setValue(GetDataToShow(ELI_LowGray_Compen1, ELC_B));

    ui->RoughAdjGCCRspinBox->setValue(GetDataToShow(ELI_LowGray_Compen2, ELC_R));
    ui->RoughAdjGCCGspinBox->setValue(GetDataToShow(ELI_LowGray_Compen2, ELC_G));
    ui->RoughAdjGCCBspinBox->setValue(GetDataToShow(ELI_LowGray_Compen2, ELC_B));

    ui->GradientOptimizationRspinBox->setValue(GetDataToShow(ELI_GradualTransition_Optimize, ELC_R));
    ui->GradientOptimizationGspinBox->setValue(GetDataToShow(ELI_GradualTransition_Optimize, ELC_G));
    ui->GradientOptimizationBspinBox->setValue(GetDataToShow(ELI_GradualTransition_Optimize, ELC_B));

    ui->LowAshUniformityRspinBox->setValue(GetDataToShow(ELI_LowGray_Even, ELC_R));
    ui->LowAshUniformityGspinBox->setValue(GetDataToShow(ELI_LowGray_Even, ELC_G));
    ui->LowAshUniformityBspinBox->setValue(GetDataToShow(ELI_LowGray_Even, ELC_B));

    ui->DefectDetectionLevelRspinBox->setValue(GetDataToShow(ELI_DefectDetect_Level, ELC_R));
    ui->DefectDetectionLevelGspinBox->setValue(GetDataToShow(ELI_DefectDetect_Level, ELC_G));
    ui->DefectDetectionLevelBspinBox->setValue(GetDataToShow(ELI_DefectDetect_Level, ELC_B));

    ui->EnergySavingcheckBox->setChecked(GetRegValue(34)==0xF7);
    ui->UseDefectDetectioncheckBox->setChecked(regpara[13 * 6 + 4] == (char)0x13);
    ui->LowGrayCorrectioncheckBox->setChecked(GetRegValue(35) == 1);

    int value1 = GetRegValue(7) + GetRegValue(8) * 256;
    int value2 = value1*GetRegValue(4) * 2;
    if (value2 > 32768)
    {
        ui->lineEdit_4->setText("16Bit");
    }
    else if (value2 > 16384)
    {
        ui->lineEdit_4->setText("15Bit");
    }
    else if (value2 > 8192)
    {
        ui->lineEdit_4->setText("14Bit");
    }
    else
    {
    }

    ui->groupBox_3->setVisible(false);
    ui->AdvancedSettinggroupBox->setVisible(true);
    ui->CurrentSettinggroupBox->setVisible(true);
    ui->AdvancedSettingpushButton->setText(tr("高级模式"));

    GetGlobalReg();

    ShowInfo = false;
}

void ICXM11202GSetting::ShowToParam()
{
    //刷新倍率
    SetShowToData(ELI_RefreshRate, ELC_R, ui->RefreshRatelspinBox->value());
    //单芯片列行
    SetShowToData(ELI_Chip_Column, ELC_R, ui->SingleChipColspinBox->value());
    SetShowToData(ELI_Chip_Row, ELC_R, ui->SingleChipRowspinBox->value());

    //电流调节1/2
    SetShowToData(ELI_Current_Adjust1, ELC_R, ui->CurrentRegulation1RspinBox->value());
    SetShowToData(ELI_Current_Adjust1, ELC_G, ui->CurrentRegulation1GspinBox->value());
    SetShowToData(ELI_Current_Adjust1, ELC_B, ui->CurrentRegulation1BspinBox->value());

    SetShowToData(ELI_Current_Adjust2, ELC_R, ui->CurrentRegulation2RspinBox->value());
    SetShowToData(ELI_Current_Adjust2, ELC_G, ui->CurrentRegulation2GspinBox->value());
    SetShowToData(ELI_Current_Adjust2, ELC_B, ui->CurrentRegulation2BspinBox->value());

    //电流增益
    SetShowToData(ELI_Current_Gain, ELC_R, ui->CurrentGainRspinBox->value());
    SetShowToData(ELI_Current_Gain, ELC_G, ui->CurrentGainGspinBox->value());
    SetShowToData(ELI_Current_Gain, ELC_B, ui->CurrentGainBspinBox->value());

    //消影等级
    SetShowToData(ELI_Disapparate_Level, ELC_R, ui->EliminationLevelRspinBox->value());
    SetShowToData(ELI_Disapparate_Level, ELC_G, ui->EliminationLevelGspinBox->value());
    SetShowToData(ELI_Disapparate_Level, ELC_B, ui->EliminationLevelBspinBox->value());

    //低灰偏色补偿1
    SetShowToData(ELI_LowGray_Compen1, ELC_R, ui->FineAdjLGCCRspinBox->value());
    SetShowToData(ELI_LowGray_Compen1, ELC_G, ui->FineAdjLGCCGspinBox->value());
    SetShowToData(ELI_LowGray_Compen1, ELC_B, ui->FineAdjLGCCBspinBox->value());

    //低灰偏色补偿2
    SetShowToData(ELI_LowGray_Compen2, ELC_R, ui->RoughAdjGCCRspinBox->value());
    SetShowToData(ELI_LowGray_Compen2, ELC_G, ui->RoughAdjGCCGspinBox->value());
    SetShowToData(ELI_LowGray_Compen2, ELC_B, ui->RoughAdjGCCBspinBox->value());

    //渐变过渡优化
    SetShowToData(ELI_GradualTransition_Optimize, ELC_R, ui->GradientOptimizationRspinBox->value());
    SetShowToData(ELI_GradualTransition_Optimize, ELC_G, ui->GradientOptimizationGspinBox->value());
    SetShowToData(ELI_GradualTransition_Optimize, ELC_B, ui->GradientOptimizationBspinBox->value());

    //低灰均匀性
    SetShowToData(ELI_LowGray_Even, ELC_R, ui->LowAshUniformityRspinBox->value());
    SetShowToData(ELI_LowGray_Even, ELC_G, ui->LowAshUniformityGspinBox->value());
    SetShowToData(ELI_LowGray_Even, ELC_B, ui->LowAshUniformityBspinBox->value());

    //去坏点侦测等级
    SetShowToData(ELI_DefectDetect_Level, ELC_R, ui->DefectDetectionLevelRspinBox->value());
    SetShowToData(ELI_DefectDetect_Level, ELC_G, ui->DefectDetectionLevelGspinBox->value());
    SetShowToData(ELI_DefectDetect_Level, ELC_B, ui->DefectDetectionLevelBspinBox->value());

    //节能模式
    if (ui->EnergySavingcheckBox->isChecked())
    {
        SetRegValue(34, 0xF7);
    }
    else
    {
        SetRegValue(34, 0xF0);
    }

    //去坏点
    if (ui->UseDefectDetectioncheckBox->isChecked())
    {
        regpara[13 * 6 + 4] = 0x13;
    }
    else
    {
        regpara[13 * 6 + 4] = 0x00;
    }
}

void ICXM11202GSetting::SetToDefault()
{
    int index = 0;
    for (int index = 0; index <= 44; index++)
    {
        regpara[index * 6 + 0] = 0;
        regpara[index * 6 + 1] = 0;
        regpara[index * 6 + 2] = 0;
    }

    //XM CMD EN
    index = 0;
    regpara[index * 6 + 3] = 0x00;
    regpara[index * 6 + 4] = 0xFF;
    regpara[index * 6 + 5] = 0x11;

    index = 1;
    regpara[index * 6 + 1] = 0x80;
    regpara[index * 6 + 2] = 0x20;
    regpara[index * 6 + 3] = 0x01;
    regpara[index * 6 + 4] = 0x00;
    regpara[index * 6 + 5] = 0x00;

    index = 2;
    regpara[index * 6 + 3] = 0x80;
    regpara[index * 6 + 4] = 0xFF;
    regpara[index * 6 + 5] = 0x11;
    index = 3;
    regpara[index * 6 + 3] = 0x80;
    regpara[index * 6 + 4] = 0xFF;
    regpara[index * 6 + 5] = 0x20;

    //全局寄存器
    index = 7;
    regpara[index * 6 + 3] = 0xEA;
    regpara[index * 6 + 4] = 0xB2;
    regpara[index * 6 + 5] = 0x02;
    index = 8;
    regpara[index * 6 + 3] = 0xEB;
    regpara[index * 6 + 4] = 0xB2;
    regpara[index * 6 + 5] = 0x26;
    index = 9;
    regpara[index * 6 + 3] = 0x00;
    regpara[index * 6 + 4] = 0x00;
    regpara[index * 6 + 5] = 0x00;
    index = 10;
    regpara[index * 6 + 3] = 0x00;
    regpara[index * 6 + 4] = 0x00;
    regpara[index * 6 + 5] = 0x00;
    index = 11;
    regpara[index * 6 + 3] = 0x00;
    regpara[index * 6 + 4] = 0x00;
    regpara[index * 6 + 5] = 0x00;

    //OSD
    index = 13;
    regpara[index * 6 + 3] = 0x00;
    regpara[index * 6 + 4] = 0x00;
    regpara[index * 6 + 5] = 0x00;

    //节能
    index = 34;
    regpara[index * 6 + 3] = 0xDB;
    regpara[index * 6 + 4] = 0xB2;
    regpara[index * 6 + 5] = 0xF0;
    index = 35;
    regpara[index * 6 + 3] = 0xA0;
    regpara[index * 6 + 4] = 0xD0;
    regpara[index * 6 + 5] = 0x00;
    index = 36;
    regpara[index * 6 + 3] = 0xB8;
    regpara[index * 6 + 4] = 0xD6;
    regpara[index * 6 + 5] = 0x2A;
    index = 37;
    regpara[index * 6 + 3] = 0x80;
    regpara[index * 6 + 4] = 0xD7;
    regpara[index * 6 + 5] = 0x22;
    index = 38;
    regpara[index * 6 + 3] = 0x90;
    regpara[index * 6 + 4] = 0xD7;
    regpara[index * 6 + 5] = 0x22;
    index = 39;
    regpara[index * 6 + 3] = 0xA0;
    regpara[index * 6 + 4] = 0xD7;
    regpara[index * 6 + 5] = 0x22;

    //刷新倍率
    SetShowToData(ELI_RefreshRate, ELC_R, 64);
    //单芯片列行
    SetShowToData(ELI_Chip_Column, ELC_R, 40);
    SetShowToData(ELI_Chip_Row, ELC_R, 36);

    //开短路侦测功能开关
    index = 40;
    regpara[index * 6 + 3] = 0x90;
    regpara[index * 6 + 4] = 0xB3;
    regpara[index * 6 + 5] = 0x40;

    //开短路侦测阀值
    index = 44;
    regpara[index * 6 + 3] = 0xF6;
    regpara[index * 6 + 4] = 0xA4;
    regpara[index * 6 + 5] = 0x41;


    //电流调节1/2
    SetShowToData(ELI_Current_Adjust1, ELC_R, 1);
    SetShowToData(ELI_Current_Adjust1, ELC_G, 1);
    SetShowToData(ELI_Current_Adjust1, ELC_B, 1);

    SetShowToData(ELI_Current_Adjust2, ELC_R, 1);
    SetShowToData(ELI_Current_Adjust2, ELC_G, 1);
    SetShowToData(ELI_Current_Adjust2, ELC_B, 1);

    //电流增益
    SetShowToData(ELI_Current_Gain, ELC_R, 0x1F + 1);
    SetShowToData(ELI_Current_Gain, ELC_G, 0x0F + 1);
    SetShowToData(ELI_Current_Gain, ELC_B, 0x0F + 1);

    //消影等级
    SetShowToData(ELI_Disapparate_Level, ELC_R, 0x08 + 1);
    SetShowToData(ELI_Disapparate_Level, ELC_G, 0x0E + 1);
    SetShowToData(ELI_Disapparate_Level, ELC_B, 0x12 + 1);

    //低灰偏色补偿1
    SetShowToData(ELI_LowGray_Compen1, ELC_R, 0x08 + 1);
    SetShowToData(ELI_LowGray_Compen1, ELC_G, 0x0E + 1);
    SetShowToData(ELI_LowGray_Compen1, ELC_B, 0x12 + 1);

    //低灰偏色补偿2
    SetShowToData(ELI_LowGray_Compen2, ELC_R, 0x00 + 1);
    SetShowToData(ELI_LowGray_Compen2, ELC_G, 0x00 + 1);
    SetShowToData(ELI_LowGray_Compen2, ELC_B, 0x00 + 1);

    //渐变过渡优化
    SetShowToData(ELI_GradualTransition_Optimize, ELC_R, 0x08 + 1);
    SetShowToData(ELI_GradualTransition_Optimize, ELC_G, 0x08 + 1);
    SetShowToData(ELI_GradualTransition_Optimize, ELC_B, 0x08 + 1);

    //低灰均匀性
    SetShowToData(ELI_LowGray_Even, ELC_R, 0x00 + 1);
    SetShowToData(ELI_LowGray_Even, ELC_G, 0x00 + 1);
    SetShowToData(ELI_LowGray_Even, ELC_B, 0x00 + 1);

    //去坏点侦测等级
    SetShowToData(ELI_DefectDetect_Level, ELC_R, 0x08 + 1);
    SetShowToData(ELI_DefectDetect_Level, ELC_G, 0x1D + 1);
    SetShowToData(ELI_DefectDetect_Level, ELC_B, 0x1D + 1);
}

void ICXM11202GSetting::on_SettingBtn_clicked()
{
    setCursor(Qt::WaitCursor);
    ShowToParam();

    //低灰校正启用
    if (ui->LowGrayCorrectioncheckBox->isChecked())
    {
        SetRegValue(35, 1);
    }
    else {
        SetRegValue(35, 0);
    }

    SetGlobalReg();

    Writebin(filename + "/regpara.bin", regpara);

    setCursor(Qt::ArrowCursor);


    LAPI::EResult ret2 = LAPI::WriteXMICParam(0xFF,0xFF,regpara);

   setCursor(Qt::ArrowCursor);

   if (ret2 == LAPI::EResult::ER_INTECTRL_Success)
   {
       UniversalInterface::MessageBoxShow(tr("发送"), tr("发送成功!"));
    }
    else
    {
       UniversalInterface::MessageBoxShow(tr("发送"), tr("发送失败!"));
    }

}

void ICXM11202GSetting::SetGlobalReg()
{
     bool ok ;
    regpara[7 * 6 + 0] = QString(ui->lineEdit_5->text()).toInt(&ok,16);
    regpara[7 * 6 + 1] = QString(ui->lineEdit_6->text()).toInt(&ok,16);
    regpara[7 * 6 + 2] = QString(ui->lineEdit_7->text()).toInt(&ok,16);
    regpara[7 * 6 + 3] = QString(ui->lineEdit_8->text()).toInt(&ok,16);
    regpara[7 * 6 + 4] = QString(ui->lineEdit_9->text()).toInt(&ok,16);
    regpara[7 * 6 + 5] = QString(ui->lineEdit_10->text()).toInt(&ok,16);

    regpara[8 * 6 + 0] = QString(ui->lineEdit_11->text()).toInt(&ok,16);
    regpara[8 * 6 + 1] = QString(ui->lineEdit_12->text()).toInt(&ok,16);
    regpara[8 * 6 + 2] = QString(ui->lineEdit_13->text()).toInt(&ok,16);
    regpara[8 * 6 + 3] = QString(ui->lineEdit_14->text()).toInt(&ok,16);
    regpara[8 * 6 + 4] = QString(ui->lineEdit_15->text()).toInt(&ok,16);
    regpara[8 * 6 + 5] = QString(ui->lineEdit_16->text()).toInt(&ok,16);

    regpara[9 * 6 + 0] = QString(ui->lineEdit_17->text()).toInt(&ok,16);
    regpara[9 * 6 + 1] = QString(ui->lineEdit_18->text()).toInt(&ok,16);
    regpara[9 * 6 + 2] = QString(ui->lineEdit_19->text()).toInt(&ok,16);
    regpara[9 * 6 + 3] = QString(ui->lineEdit_20->text()).toInt(&ok,16);
    regpara[9 * 6 + 4] = QString(ui->lineEdit_21->text()).toInt(&ok,16);
    regpara[9 * 6 + 5] = QString(ui->lineEdit_22->text()).toInt(&ok,16);

    regpara[10 * 6 + 0] = QString(ui->lineEdit_23->text()).toInt(&ok,16);
    regpara[10 * 6 + 1] = QString(ui->lineEdit_24->text()).toInt(&ok,16);
    regpara[10 * 6 + 2] = QString(ui->lineEdit_25->text()).toInt(&ok,16);
    regpara[10 * 6 + 3] = QString(ui->lineEdit_26->text()).toInt(&ok,16);
    regpara[10 * 6 + 4] = QString(ui->lineEdit_27->text()).toInt(&ok,16);
    regpara[10 * 6 + 5] = QString(ui->lineEdit_28->text()).toInt(&ok,16);

    regpara[11 * 6 + 0] = QString(ui->lineEdit_29->text()).toInt(&ok,16);
    regpara[11 * 6 + 1] = QString(ui->lineEdit_30->text()).toInt(&ok,16);
    regpara[11 * 6 + 2] = QString(ui->lineEdit_31->text()).toInt(&ok,16);
    regpara[11 * 6 + 3] = QString(ui->lineEdit_32->text()).toInt(&ok,16);
    regpara[11 * 6 + 4] = QString(ui->lineEdit_33->text()).toInt(&ok,16);
    regpara[11 * 6 + 5] = QString(ui->lineEdit_34->text()).toInt(&ok,16);

    regpara[12 * 6 + 0] = QString(ui->lineEdit_35->text()).toInt(&ok,16);
    regpara[12 * 6 + 1] = QString(ui->lineEdit_36->text()).toInt(&ok,16);
    regpara[12 * 6 + 2] = QString(ui->lineEdit_37->text()).toInt(&ok,16);
    regpara[12 * 6 + 3] = QString(ui->lineEdit_38->text()).toInt(&ok,16);
    regpara[12 * 6 + 4] = QString(ui->lineEdit_39->text()).toInt(&ok,16);
    regpara[12 * 6 + 5] = QString(ui->lineEdit_40->text()).toInt(&ok,16);
}

void ICXM11202GSetting::GetGlobalReg()
{
    ui->lineEdit_5->setText(QByteArray::number(regpara[7 * 6 + 0] & 0xFF,16));
    ui->lineEdit_6->setText(QByteArray::number(regpara[7 * 6 + 1] & 0xFF, 16));
    ui->lineEdit_7->setText(QByteArray::number(regpara[7 * 6 + 2] & 0xFF, 16));
    ui->lineEdit_8->setText(QByteArray::number(regpara[7 * 6 + 3] & 0xFF, 16));
    ui->lineEdit_9->setText(QByteArray::number(regpara[7 * 6 + 4] & 0xFF, 16));
    ui->lineEdit_10->setText(QByteArray::number(regpara[7 * 6 + 5] & 0xFF, 16));

    ui->lineEdit_11->setText(QByteArray::number(regpara[8 * 6 + 0] & 0xFF, 16));
    ui->lineEdit_12->setText(QByteArray::number(regpara[8 * 6 + 1] & 0xFF, 16));
    ui->lineEdit_13->setText(QByteArray::number(regpara[8 * 6 + 2] & 0xFF, 16));
    ui->lineEdit_14->setText(QByteArray::number(regpara[8 * 6 + 3] & 0xFF, 16));
    ui->lineEdit_15->setText(QByteArray::number(regpara[8 * 6 + 4] & 0xFF, 16));
    ui->lineEdit_16->setText(QByteArray::number(regpara[8 * 6 + 5] & 0xFF, 16));

    ui->lineEdit_17->setText(QByteArray::number(regpara[9 * 6 + 0] & 0xFF, 16));
    ui->lineEdit_18->setText(QByteArray::number(regpara[9 * 6 + 1] & 0xFF, 16));
    ui->lineEdit_19->setText(QByteArray::number(regpara[9 * 6 + 2] & 0xFF, 16));
    ui->lineEdit_20->setText(QByteArray::number(regpara[9 * 6 + 3] & 0xFF, 16));
    ui->lineEdit_21->setText(QByteArray::number(regpara[9 * 6 + 4] & 0xFF, 16));
    ui->lineEdit_22->setText(QByteArray::number(regpara[9 * 6 + 5] & 0xFF, 16));

    ui->lineEdit_23->setText(QByteArray::number(regpara[10 * 6 + 0] & 0xFF, 16));
    ui->lineEdit_24->setText(QByteArray::number(regpara[10 * 6 + 1] & 0xFF, 16));
    ui->lineEdit_25->setText(QByteArray::number(regpara[10 * 6 + 2] & 0xFF, 16));
    ui->lineEdit_26->setText(QByteArray::number(regpara[10 * 6 + 3] & 0xFF, 16));
    ui->lineEdit_27->setText(QByteArray::number(regpara[10 * 6 + 4] & 0xFF, 16));
    ui->lineEdit_28->setText(QByteArray::number(regpara[10 * 6 + 5] & 0xFF, 16));

    ui->lineEdit_29->setText(QByteArray::number(regpara[11 * 6 + 0] & 0xFF, 16));
    ui->lineEdit_30->setText(QByteArray::number(regpara[11 * 6 + 1] & 0xFF, 16));
    ui->lineEdit_31->setText(QByteArray::number(regpara[11 * 6 + 2] & 0xFF, 16));
    ui->lineEdit_32->setText(QByteArray::number(regpara[11 * 6 + 3] & 0xFF, 16));
    ui->lineEdit_33->setText(QByteArray::number(regpara[11 * 6 + 4] & 0xFF, 16));
    ui->lineEdit_34->setText(QByteArray::number(regpara[11 * 6 + 5] & 0xFF, 16));

    ui->lineEdit_35->setText(QByteArray::number(regpara[12 * 6 + 0] & 0xFF, 16));
    ui->lineEdit_36->setText(QByteArray::number(regpara[12 * 6 + 1] & 0xFF, 16));
    ui->lineEdit_37->setText(QByteArray::number(regpara[12 * 6 + 2] & 0xFF, 16));
    ui->lineEdit_38->setText(QByteArray::number(regpara[12 * 6 + 3] & 0xFF, 16));
    ui->lineEdit_39->setText(QByteArray::number(regpara[12 * 6 + 4] & 0xFF, 16));
    ui->lineEdit_40->setText(QByteArray::number(regpara[12 * 6 + 5] & 0xFF, 16));
}

void ICXM11202GSetting::Writebin(QString path, QByteArray bytes)
{
    QFile f(path);      //定义一个文件
    if (f.open(QIODevice::WriteOnly))       //打开文件
    {
        QDataStream qs(&f);             //定义一个数据流
        int i = 0;
        for(i=0;i<bytes.length();i++)
        {
            qs << (uint8_t)bytes[i];      //把数组中的数据写到数据流，即写入文件中
        }
        f.close();
    }
    else
    {
        qDebug() << "Failed";
    }
}
QByteArray ICXM11202GSetting::Readbin(QString path)
{
    QByteArray ba;
    QFile f(path);      //定义一个文件
    if (f.open(QIODevice::ReadOnly))       //打开文件
    {
        ba = f.readAll();
        f.close();
        //qDebug() << ba;
    }
    else
    {
        qDebug() << "Failed";
    }
    return ba;
}



void ICXM11202GSetting::on_PresetApushButton_clicked()
{

    QByteArray array1 = ReadGamdat(filename + "/Gamma/XM11202G-GammaA.gamdat");

    quint16 fileType = LBLFileTransferPackage::EFileType::EFT_GammaFile_16Bit;
    LAPI::EResult ret = LAPI::UpgradeFile(fileType,array1,true,3000);
    if (ret==LAPI::EResult::ER_Success)
    {
        UniversalInterface::MessageBoxShow(tr("Gamma"), tr("发送成功!"));
    }
    else
    {
        UniversalInterface::MessageBoxShow(tr("Gamma"), tr("发送失败!"));
    }

}

void ICXM11202GSetting::on_PresetBpushButton_clicked()
{
    QByteArray array1 = ReadGamdat(filename + "/Gamma/XM11202G-GammaB.gamdat");
    quint16 fileType = LBLFileTransferPackage::EFileType::EFT_GammaFile_16Bit;
    LAPI::EResult ret = LAPI::UpgradeFile(fileType,array1,true,3000);
    if (ret==LAPI::EResult::ER_Success)
    {
        UniversalInterface::MessageBoxShow(tr("Gamma"), tr("发送成功!"));
    }
    else
    {
        UniversalInterface::MessageBoxShow(tr("Gamma"), tr("发送失败!"));
    }
}

void ICXM11202GSetting::on_PresetCpushButton_clicked()
{
    QByteArray array1 = ReadGamdat(filename + "/Gamma/XM11202G-GammaC.gamdat");
    quint16 fileType = LBLFileTransferPackage::EFileType::EFT_GammaFile_16Bit;
    LAPI::EResult ret = LAPI::UpgradeFile(fileType,array1,true,3000);
    if (ret==LAPI::EResult::ER_Success)
    {
        UniversalInterface::MessageBoxShow(tr("Gamma"), tr("发送成功!"));
    }
    else
    {
        UniversalInterface::MessageBoxShow(tr("Gamma"), tr("发送失败!"));
    }
}

void ICXM11202GSetting::on_PresetDpushButton_clicked()
{
    QByteArray array1 = ReadGamdat(filename + "/Gamma/XM11202G-GammaD.gamdat");
    quint16 fileType = LBLFileTransferPackage::EFileType::EFT_GammaFile_16Bit;
    LAPI::EResult ret = LAPI::UpgradeFile(fileType,array1,true,3000);
    if (ret==LAPI::EResult::ER_Success)
    {
        UniversalInterface::MessageBoxShow(tr("Gamma"), tr("发送成功!"));
    }
    else
    {
        UniversalInterface::MessageBoxShow(tr("Gamma"), tr("发送失败!"));
    }
}

void ICXM11202GSetting::on_DefectDetectionpushButton_clicked()
{
    setCursor(Qt::WaitCursor);
    LAPI::EResult ret = LAPI::clearDeadPoint(0xFF,0xFF);
    if (ret == LAPI::EResult::ER_Success)
    {
        if (ui->UseDefectDetectioncheckBox->isChecked())
        {
            regpara[13 * 6 + 4] = 0x13;
        }
        QThread::sleep(1);
        LAPI::EResult ret2 = LAPI::WriteXMICParam(0xFF,0xFF,regpara);
        if (ret2 == LAPI::EResult::ER_Success)
        {
            UniversalInterface::MessageBoxShow(tr("去坏点"),tr("触发成功"));
        }
    }
    setCursor(Qt::ArrowCursor);

}




///读取.gamdat文件
QByteArray ICXM11202GSetting::ReadGamdat(QString filepath)
{
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }

    QByteArray array;
    QByteArray line = file.readLine();
    QString str(line);
    QString strs = str.split('#')[5];

    QStringList gama = strs.split(',');
    //qDebug() << gama.count() << "----------------------";
    for (int i = 0;i < gama.count();i++)
    {
        unsigned char tempByte = (unsigned char)(gama[i].toUInt(nullptr,10));
        array.append(tempByte);
        //qDebug() << "----------------------" << tempByte;
        tempByte = (unsigned char)(gama[i].toUInt(nullptr,10) >> 8);
        array.append(tempByte);
        //qDebug() << "----------------------" << tempByte;
    }
    return array;
}

void ICXM11202GSetting::on_CurrentRegulation1RspinBox_valueChanged(int arg1)
{
    double value = arg1 * (0.16+0.0025*ui->CurrentRegulation2RspinBox->value()) * ui->CurrentGainRspinBox->value();
    QString str = QString::number(value,'g',3);
    ui->CurrentOutputRlineEdit->setText(str);
}

void ICXM11202GSetting::on_CurrentRegulation2RspinBox_valueChanged(int arg1)
{
    double value = ui->CurrentRegulation1RspinBox->value() * (0.16+0.0025*arg1) * ui->CurrentGainRspinBox->value();
    QString str = QString::number(value,'g',3);
    ui->CurrentOutputRlineEdit->setText(str);
}

void ICXM11202GSetting::on_CurrentGainRspinBox_valueChanged(int arg1)
{
    double value = ui->CurrentRegulation1RspinBox->value() * (0.16+0.0025*ui->CurrentRegulation2RspinBox->value()) * arg1;
    QString str = QString::number(value,'g',3);
    ui->CurrentOutputRlineEdit->setText(str);
}


void ICXM11202GSetting::on_CurrentRegulation1GspinBox_valueChanged(int arg1)
{
    double value = arg1 * (0.16+0.0025*ui->CurrentRegulation2GspinBox->value()) * ui->CurrentGainGspinBox->value();
    QString str = QString::number(value,'g',3);
    ui->CurrentOutputGlineEdit->setText(str);
}

void ICXM11202GSetting::on_CurrentRegulation2GspinBox_valueChanged(int arg1)
{
    double value = ui->CurrentRegulation1GspinBox->value() * (0.16+0.0025*arg1) * ui->CurrentGainGspinBox->value();
    QString str = QString::number(value,'g',3);
    ui->CurrentOutputGlineEdit->setText(str);
}

void ICXM11202GSetting::on_CurrentGainGspinBox_valueChanged(int arg1)
{
    double value = ui->CurrentRegulation1GspinBox->value() * (0.16+0.0025*ui->CurrentRegulation2GspinBox->value()) * arg1;
    QString str = QString::number(value,'g',3);
    ui->CurrentOutputGlineEdit->setText(str);
}


void ICXM11202GSetting::on_CurrentRegulation1BspinBox_valueChanged(int arg1)
{
    double value = arg1 * (0.16+0.0025*ui->CurrentRegulation2BspinBox->value()) * ui->CurrentGainBspinBox->value();
    QString str = QString::number(value,'f',3);
    ui->CurrentOutputBlineEdit->setText(str);
}

void ICXM11202GSetting::on_CurrentRegulation2BspinBox_valueChanged(int arg1)
{
    double value = ui->CurrentRegulation1BspinBox->value() * (0.16+0.0025*arg1) * ui->CurrentGainBspinBox->value();
    QString str = QString::number(value,'f',3);
    ui->CurrentOutputBlineEdit->setText(str);
}

void ICXM11202GSetting::on_CurrentGainBspinBox_valueChanged(int arg1)
{
    double value = ui->CurrentRegulation1BspinBox->value() * (0.16+0.0025*ui->CurrentRegulation2BspinBox->value()) * arg1;
    QString str = QString::number(value,'f',3);
    ui->CurrentOutputBlineEdit->setText(str);
}

void ICXM11202GSetting::on_RefreshRatelspinBox_valueChanged(int arg1)
{
    int value1 = GetRegValue(7) + GetRegValue(8) * 256;
    int value2 = value1*arg1 * 2;
    if (value2 > 32766)
    {
        ui->lineEdit_4->setText("16Bit");
    }
    else if (value2 > 16384 && value2 <= 32766)
    {
        ui->lineEdit_4->setText("15Bit");
    }
    else if (value2 > 8192 && value2 <= 16384)
    {
        ui->lineEdit_4->setText("14Bit");
    }
    else
    {

    }
}



void ICXM11202GSetting::on_SaveFilepushButton_clicked()
{
    ShowToParam();

    SetGlobalReg();

    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,tr("Open Config"), "", tr("TXT Files (*.txt);; TXT Files (*.txt)"));
    if (!fileName.isNull())
    {
        WriteFile(fileName,regpara);   //fileName是文件名

        int ret = QMessageBox::information(this, tr("保存文件"), tr("文件保存成功!"),QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }
    else
    {

    }
}

void ICXM11202GSetting::on_LoadFilepushButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("Open Config"), "", tr("TXT Files (*.txt);; CID Files (*.txt)"));

    if (!fileName.isNull())
    {
        //fileName即是选择的文件名
    }
    else
    {
        return;
    }

    QByteArray fileArray = ReadFile(fileName);
    memcpy( regpara.data(), fileArray.data(), qMin(fileArray.count(), regpara.count()));

    ParamToShow();

    int ret = QMessageBox::information(this, tr("加载文件"), tr("文件加载成功!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
}

void ICXM11202GSetting::on_AdvancedSettingpushButton_clicked()
{
    if(ui->AdvancedSettingpushButton->text() == tr("高级模式"))
    {
        ui->groupBox_3->setVisible(true);
        ui->AdvancedSettinggroupBox->setVisible(false);
        ui->CurrentSettinggroupBox->setVisible(false);
        ui->AdvancedSettingpushButton->setText(tr("普通模式"));
    }
    else if(ui->AdvancedSettingpushButton->text() == tr("普通模式"))
    {
        ui->groupBox_3->setVisible(false);
        ui->AdvancedSettinggroupBox->setVisible(true);
        ui->CurrentSettinggroupBox->setVisible(true);
        ui->AdvancedSettingpushButton->setText(tr("高级模式"));
    }
    else{}
}

void ICXM11202GSetting::on_pushButton_Readback_clicked()
{
    QByteArray result;
    result = LAPI::ReadXMICParam(0x00,0x00);
    //Writebin(filename + "/result.bin", result);

    if (sizeof(result) > 0)
    {
        regpara = result;
         ParamToShow();
        UniversalInterface::MessageBoxShow(tr("回读"), tr("回读成功!"));
    }
    else
    {
        UniversalInterface::MessageBoxShow(tr("回读"), tr("回读失败!"));
        return;
    }

}

void ICXM11202GSetting::on_pushButton_ClearDeadPoint_clicked()
{
    setCursor(Qt::WaitCursor);
    LAPI::EResult ret = LAPI::clearDeadPoint(0xFF,0xFF);
    if (ret == LAPI::EResult::ER_Success)
    {
        if (ui->UseDefectDetectioncheckBox->isChecked())
        {
            regpara[13 * 6 + 4] = 0x13;
        }
        QThread::sleep(1);
        LAPI::EResult ret2 = LAPI::WriteXMICParam(0xFF,0xFF,regpara);
        if (ret2 == LAPI::EResult::ER_Success)
        {
            UniversalInterface::MessageBoxShow(tr("去坏点"),tr("触发成功"));
        }
    }
    setCursor(Qt::ArrowCursor);
}

void ICXM11202GSetting::on_pushButton_Default_clicked()
{
    SetToDefault();
    ParamToShow();
}

void ICXM11202GSetting::on_UseDefectDetectioncheckBox_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    if (ShowInfo) return;
    //去坏点
    if (ui->UseDefectDetectioncheckBox->isChecked())
    {
        regpara[13 * 6 + 4] = 0x13;
    }
    else
    {
        regpara[13 * 6 + 4] = 0x00;
    }

    //取消去坏点
    if (!ui->UseDefectDetectioncheckBox->isChecked())
    {
        on_pushButton_ClearDeadPoint_clicked();
    }
}

