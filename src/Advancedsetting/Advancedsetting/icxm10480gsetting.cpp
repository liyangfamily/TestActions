#include "icxm10480gsetting.h"
#include "ui_icxm10480gsetting.h"
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "advancedsetting.h"
#include <QThread>
//#include "UTF8Define.h"

#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif
ICXM10480GSetting::ICXM10480GSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ICXM10480GSetting)
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

    Loadformpara();
}

ICXM10480GSetting::~ICXM10480GSetting()
{
    delete ui;
}


/// <summary>
/// 设置对应寄存器的值
/// </summary>
void ICXM10480GSetting::SetRegValue(int Num, int value)
{
    regpara[Num * 6 + 5] = (uchar)value;
}
unsigned char ICXM10480GSetting::GetRegValue(int Num)
{
    return (uchar)regpara[Num * 6 + 5];
}

///读取txt文件
QByteArray ICXM10480GSetting::ReadFile(QString filepath)
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
        int count = str.split(' ').count();

        if (count >= 6 && str.split(' ')[0] != "")
        {

            for (int i = 0;i < 6;i++)
            {
                QString strTemp = str.right(str.length()-3*i).left(2);
                unsigned char tempByte = (unsigned char)(strTemp.toUInt(nullptr,16));
                //qDebug() << tempByte << "------------------";
                array.append(tempByte);
            }
        }
    }

    return array;
}


///写入txt文件
bool ICXM10480GSetting::WriteFile(QString filepath,QByteArray array)
{
    QFile file(filepath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    file.write("//XM11202_default_initial_code\n\n");

    int i = 0;
    for (i=0;i<array.length()/6;i++)
    {
        QString str ;
        for (int j=0;j<6;j++)
        {

            str += QString::number((uchar)array[i * 6 + j] & 0xFF,16).toUpper().rightJustified(2,QChar('0')) + " ";
        }
        str += "\n";
        file.write(str.toUtf8());
    }


    return true;
}




void ICXM10480GSetting::Loadformpara()
{
     unsigned char value=0;
    //电流调节1
    ui->CurrentRegulation1RspinBox->setValue(GetRegValue(14) >> 6);
    ui->CurrentRegulation1GspinBox->setValue(GetRegValue(15) >> 6);
    ui->CurrentRegulation1BspinBox->setValue(GetRegValue(16) >> 6);

    //电流调节2
    ui->CurrentRegulation2RspinBox->setValue(GetRegValue(14) & 0x3F);
    ui->CurrentRegulation2GspinBox->setValue(GetRegValue(15) & 0x3F);
    ui->CurrentRegulation2BspinBox->setValue(GetRegValue(16) & 0x3F);

    //电流增益
    ui->CurrentGainRspinBox->setValue(GetRegValue(17)+1);
    ui->CurrentGainGspinBox->setValue(GetRegValue(18)+1);
    ui->CurrentGainBspinBox->setValue(GetRegValue(19)+1);

    //消影等级
    ui->EliminationLevelRspinBox->setValue(GetRegValue(20)+1);
    ui->EliminationLevelGspinBox->setValue(GetRegValue(21)+1);
    ui->EliminationLevelBspinBox->setValue(GetRegValue(22)+1);

    //低灰偏色补偿1
    ui->FineAdjLGCCRspinBox->setValue(GetRegValue(23)+1);
    ui->FineAdjLGCCGspinBox->setValue(GetRegValue(24)+1);
    ui->FineAdjLGCCBspinBox->setValue(GetRegValue(25)+1);

    //低灰偏色补偿2
    ui->RoughAdjGCCRspinBox->setValue(GetRegValue(26)+1);
    ui->RoughAdjGCCGspinBox->setValue(GetRegValue(27)+1);
    ui->RoughAdjGCCBspinBox->setValue(GetRegValue(28)+1);

    //低灰偏色补偿3
    value = GetRegValue(29);
    ui->AdjGCCRspinBox->setValue((value & 0x0F) + 1);
    ui->AdjGCCGspinBox->setValue((value >> 4) + 1);
    ui->AdjGCCBspinBox->setValue(GetRegValue(30)+1);

    //渐变过渡优化1
    ui->GradientOptimizationRspinBox->setValue(GetRegValue(31)+1);
    ui->GradientOptimizationGspinBox->setValue(GetRegValue(32)+1);
    ui->GradientOptimizationBspinBox->setValue(GetRegValue(33)+1);

    //渐变过渡优化2
    ui->GradientOptimizationRspinBox_2->setValue(GetRegValue(34)+1);
    ui->GradientOptimizationGspinBox_2->setValue(GetRegValue(35)+1);
    ui->GradientOptimizationBspinBox_2->setValue(GetRegValue(36)+1);

    //低灰均匀性
    ui->LowAshUniformityRspinBox->setValue(GetRegValue(37)+1);
    ui->LowAshUniformityGspinBox->setValue(GetRegValue(38)+1);
    ui->LowAshUniformityBspinBox->setValue(GetRegValue(39)+1);

    //去坏点侦测等级
    ui->DefectDetectionLevelRspinBox->setValue(GetRegValue(43)+1);
    ui->DefectDetectionLevelGspinBox->setValue(GetRegValue(44)+1);
    ui->DefectDetectionLevelBspinBox->setValue(GetRegValue(45)+1);

    //节能模式
    value = GetRegValue(40);
    if (value == 0xF7)
    {
        ui->EnergySavingcheckBox->setChecked(true);
    }

    //去坏点
    if (regpara[13 * 6 + 4] == (char)0x13)
    {
        ui->UseDefectDetectioncheckBox->setChecked(true);
    }


    ui->SingleChipColspinBox->setValue(GetRegValue(5));
    ui->SingleChipRowspinBox->setValue(GetRegValue(6));
    ui->RefreshRatelspinBox->setValue(GetRegValue(4));



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

    if (GetRegValue(41) == 1<<4)
    {
        ui->LowGrayCorrectioncheckBox->setChecked(true);
    }

    //首行暗线补偿
    ui->FirstDarkLineCompensationRspinBox->setValue(GetRegValue(47) * 256 + GetRegValue(48));
    ui->FirstDarkLineCompensationGspinBox->setValue(GetRegValue(49) * 256 + GetRegValue(50));
    ui->FirstDarkLineCompensationBspinBox->setValue(GetRegValue(51) * 256 + GetRegValue(52));


    ui->groupBox_3->setVisible(false);
    ui->AdvancedSettinggroupBox->setVisible(true);
    ui->CurrentSettinggroupBox->setVisible(true);
    ui->AdvancedSettingpushButton->setText(tr("高级模式"));

    GetGlobalReg();

}


void ICXM10480GSetting::on_SettingBtn_clicked()
{
    setCursor(Qt::WaitCursor);

    GetFormValue();

    Writebin(filename + "/regpara.bin", regpara);

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

void ICXM10480GSetting::GetFormValue()
{
    unsigned char value = 0;
    //电流调节1/2
    unsigned char current = 0;
    //R
    current = ((ui->CurrentRegulation1RspinBox->value() << 6) + ui->CurrentRegulation2RspinBox->value());
    SetRegValue(14, current);
    //G
    current = ((ui->CurrentRegulation1GspinBox->value() << 6) + ui->CurrentRegulation2GspinBox->value());
    SetRegValue(15, current);
    //B
    current = ((ui->CurrentRegulation1BspinBox->value() << 6) + ui->CurrentRegulation2BspinBox->value());
    SetRegValue(16, current);

    //电流增益
    SetRegValue(17, ui->CurrentGainRspinBox->value()-1);
    SetRegValue(18, ui->CurrentGainGspinBox->value()-1);
    SetRegValue(19, ui->CurrentGainBspinBox->value()-1);

    //消影等级
    SetRegValue(20, ui->EliminationLevelRspinBox->value()-1);
    SetRegValue(21, ui->EliminationLevelGspinBox->value()-1);
    SetRegValue(22, ui->EliminationLevelBspinBox->value()-1);

    //低灰偏色补偿1
    SetRegValue(23, ui->FineAdjLGCCRspinBox->value()-1);
    SetRegValue(24, ui->FineAdjLGCCGspinBox->value()-1);
    SetRegValue(25, ui->FineAdjLGCCBspinBox->value()-1);

    //低灰偏色补偿2
    SetRegValue(26, ui->RoughAdjGCCRspinBox->value()-1);
    SetRegValue(27, ui->RoughAdjGCCGspinBox->value()-1);
    SetRegValue(28, ui->RoughAdjGCCBspinBox->value()-1);

    //低灰偏色补偿3
    value = ui->AdjGCCRspinBox->value()-1 + ((ui->AdjGCCGspinBox->value()-1) << 4);
    SetRegValue(29,value);
    SetRegValue(30,ui->AdjGCCBspinBox->value()-1);

    //渐变过渡优化
    SetRegValue(31, ui->GradientOptimizationRspinBox->value()-1);
    SetRegValue(32, ui->GradientOptimizationGspinBox->value()-1);
    SetRegValue(33, ui->GradientOptimizationBspinBox->value()-1);

    //渐变过渡优化2
    SetRegValue(34, ui->GradientOptimizationRspinBox_2->value()-1);
    SetRegValue(35, ui->GradientOptimizationGspinBox_2->value()-1);
    SetRegValue(36, ui->GradientOptimizationBspinBox_2->value()-1);

    //低灰均匀性
    SetRegValue(37, ui->LowAshUniformityRspinBox->value()-1);
    SetRegValue(38, ui->LowAshUniformityGspinBox->value()-1);
    SetRegValue(39, ui->LowAshUniformityBspinBox->value()-1);

    //去坏点侦测等级
    SetRegValue(43, ui->DefectDetectionLevelRspinBox->value()-1);
    SetRegValue(44, ui->DefectDetectionLevelGspinBox->value()-1);
    SetRegValue(45, ui->DefectDetectionLevelBspinBox->value()-1);

    //节能模式
    if (ui->EnergySavingcheckBox->isChecked())
    {
        SetRegValue(40, 0xF7);
    }
    else
    {
        SetRegValue(40, 0xF0);
    }

    //去坏点
    if (ui->UseDefectDetectioncheckBox->isChecked())
    {
        regpara[13 * 6 + 4] = 0x13;
    }
    else
    {
        regpara[13 * 6 + 4] = 0x12;
    }

    //单芯片列行
    SetRegValue(5, ui->SingleChipColspinBox->value());
    SetRegValue(6, ui->SingleChipRowspinBox->value());

    //刷新倍率
    SetRegValue(4, ui->RefreshRatelspinBox->value());

    //低灰校正启用
    if (ui->LowGrayCorrectioncheckBox->isChecked())
    {
        SetRegValue(41, 1<<4);
    }
    else {
        SetRegValue(41, 0<<4);
    }

    //首行暗线补偿
    SetRegValue(47,(ui->FirstDarkLineCompensationRspinBox->value()>>8) & 0xFF);
    SetRegValue(48,ui->FirstDarkLineCompensationRspinBox->value() & 0xFF);
    SetRegValue(49,(ui->FirstDarkLineCompensationGspinBox->value()>>8) & 0xFF);
    SetRegValue(50,ui->FirstDarkLineCompensationGspinBox->value() & 0xFF);
    SetRegValue(51,(ui->FirstDarkLineCompensationBspinBox->value()>>8) & 0xFF);
    SetRegValue(52,ui->FirstDarkLineCompensationBspinBox->value() & 0xFF);

    SetGlobalReg();
}

void ICXM10480GSetting::SetGlobalReg()
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

void ICXM10480GSetting::GetGlobalReg()
{

    ui->lineEdit_5->setText(QString("%1").arg((uchar)regpara[7 * 6 + 0],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_6->setText(QString("%1").arg((uchar)regpara[7 * 6 + 1],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_7->setText(QString("%1").arg((uchar)regpara[7 * 6 + 2],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_8->setText(QString("%1").arg((uchar)regpara[7 * 6 + 3],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_9->setText(QString("%1").arg((uchar)regpara[7 * 6 + 4],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_10->setText(QString("%1").arg((uchar)regpara[7 * 6 + 5],2,16,QLatin1Char('0')).toUpper());


    ui->lineEdit_11->setText(QString("%1").arg((uchar)regpara[8 * 6 + 0],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_12->setText(QString("%1").arg((uchar)regpara[8 * 6 + 1],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_13->setText(QString("%1").arg((uchar)regpara[8 * 6 + 2],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_14->setText(QString("%1").arg((uchar)regpara[8 * 6 + 3],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_15->setText(QString("%1").arg((uchar)regpara[8 * 6 + 4],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_16->setText(QString("%1").arg((uchar)regpara[8 * 6 + 5],2,16,QLatin1Char('0')).toUpper());

    ui->lineEdit_17->setText(QString("%1").arg((uchar)regpara[9 * 6 + 0],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_18->setText(QString("%1").arg((uchar)regpara[9 * 6 + 1],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_19->setText(QString("%1").arg((uchar)regpara[9 * 6 + 2],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_20->setText(QString("%1").arg((uchar)regpara[9 * 6 + 3],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_21->setText(QString("%1").arg((uchar)regpara[9 * 6 + 4],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_22->setText(QString("%1").arg((uchar)regpara[9 * 6 + 5],2,16,QLatin1Char('0')).toUpper());

    ui->lineEdit_23->setText(QString("%1").arg((uchar)regpara[10 * 6 + 0],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_24->setText(QString("%1").arg((uchar)regpara[10 * 6 + 1],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_25->setText(QString("%1").arg((uchar)regpara[10 * 6 + 2],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_26->setText(QString("%1").arg((uchar)regpara[10 * 6 + 3],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_27->setText(QString("%1").arg((uchar)regpara[10 * 6 + 4],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_28->setText(QString("%1").arg((uchar)regpara[10 * 6 + 5],2,16,QLatin1Char('0')).toUpper());

    ui->lineEdit_29->setText(QString("%1").arg((uchar)regpara[11 * 6 + 0],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_30->setText(QString("%1").arg((uchar)regpara[11 * 6 + 1],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_31->setText(QString("%1").arg((uchar)regpara[11 * 6 + 2],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_32->setText(QString("%1").arg((uchar)regpara[11 * 6 + 3],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_33->setText(QString("%1").arg((uchar)regpara[11 * 6 + 4],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_34->setText(QString("%1").arg((uchar)regpara[11 * 6 + 5],2,16,QLatin1Char('0')).toUpper());

    ui->lineEdit_35->setText(QString("%1").arg((uchar)regpara[12 * 6 + 0],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_36->setText(QString("%1").arg((uchar)regpara[12 * 6 + 1],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_37->setText(QString("%1").arg((uchar)regpara[12 * 6 + 2],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_38->setText(QString("%1").arg((uchar)regpara[12 * 6 + 3],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_39->setText(QString("%1").arg((uchar)regpara[12 * 6 + 4],2,16,QLatin1Char('0')).toUpper());
    ui->lineEdit_40->setText(QString("%1").arg((uchar)regpara[12 * 6 + 5],2,16,QLatin1Char('0')).toUpper());

}




void ICXM10480GSetting::Writebin(QString path, QByteArray bytes)
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
QByteArray ICXM10480GSetting::Readbin(QString path)
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



void ICXM10480GSetting::on_PresetApushButton_clicked()
{

    QByteArray array1 = ReadGamdat(filename + "/Gamma/XM10480G-GammaA.gamdat");


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

void ICXM10480GSetting::on_PresetBpushButton_clicked()
{
    QByteArray array1 = ReadGamdat(filename + "/Gamma/XM10480G-GammaB.gamdat");
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

void ICXM10480GSetting::on_PresetCpushButton_clicked()
{
    QByteArray array1 = ReadGamdat(filename + "/Gamma/XM10480G-GammaC.gamdat");
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

void ICXM10480GSetting::on_PresetDpushButton_clicked()
{
    QByteArray array1 = ReadGamdat(filename + "/Gamma/XM10480G-GammaD.gamdat");
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


void ICXM10480GSetting::on_pushButton_clicked()
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
QByteArray ICXM10480GSetting::ReadGamdat(QString filepath)
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
    for (int i = 0;i < gama.count();i++)
    {
        unsigned char tempByte = (unsigned char)(gama[i].toUInt(nullptr,10));
        array.append(tempByte);
        tempByte = (unsigned char)(gama[i].toUInt(nullptr,10) >> 8);
        array.append(tempByte);
    }
    return array;
}


void ICXM10480GSetting::on_ReadBackpushButton_clicked()
{
    QByteArray result;
    result = LAPI::ReadXMICParam(0x00,0x00);
    //Writebin(filename + "/result.bin", result);

    if (sizeof(result) > 0)
    {
        regpara = result;
        Loadformpara();
        UniversalInterface::MessageBoxShow(tr("回读"), tr("回读成功!"));
    }
    else
    {
        UniversalInterface::MessageBoxShow(tr("回读"), tr("回读失败!"));
        return;
    }
}

void ICXM10480GSetting::on_CurrentRegulation1RspinBox_valueChanged(int arg1)
{
    double value = arg1 * (0.16+0.0025*ui->CurrentRegulation2RspinBox->value()) * ui->CurrentGainRspinBox->value();
    QString str = QString::number(value,'g',3);
    ui->CurrentOutputRlineEdit->setText(str);
}

void ICXM10480GSetting::on_CurrentRegulation2RspinBox_valueChanged(int arg1)
{
    double value = ui->CurrentRegulation1RspinBox->value() * (0.16+0.0025*arg1) * ui->CurrentGainRspinBox->value();
    QString str = QString::number(value,'g',3);
    ui->CurrentOutputRlineEdit->setText(str);
}

void ICXM10480GSetting::on_CurrentGainRspinBox_valueChanged(int arg1)
{
    double value = ui->CurrentRegulation1RspinBox->value() * (0.16+0.0025*ui->CurrentRegulation2RspinBox->value()) * arg1;
    QString str = QString::number(value,'g',3);
    ui->CurrentOutputRlineEdit->setText(str);
}


void ICXM10480GSetting::on_CurrentRegulation1GspinBox_valueChanged(int arg1)
{
    double value = arg1 * (0.16+0.0025*ui->CurrentRegulation2GspinBox->value()) * ui->CurrentGainGspinBox->value();
    QString str = QString::number(value,'g',3);
    ui->CurrentOutputGlineEdit->setText(str);
}

void ICXM10480GSetting::on_CurrentRegulation2GspinBox_valueChanged(int arg1)
{
    double value = ui->CurrentRegulation1GspinBox->value() * (0.16+0.0025*arg1) * ui->CurrentGainGspinBox->value();
    QString str = QString::number(value,'g',3);
    ui->CurrentOutputGlineEdit->setText(str);
}

void ICXM10480GSetting::on_CurrentGainGspinBox_valueChanged(int arg1)
{
    double value = ui->CurrentRegulation1GspinBox->value() * (0.16+0.0025*ui->CurrentRegulation2GspinBox->value()) * arg1;
    QString str = QString::number(value,'g',3);
    ui->CurrentOutputGlineEdit->setText(str);
}


void ICXM10480GSetting::on_CurrentRegulation1BspinBox_valueChanged(int arg1)
{
    double value = arg1 * (0.16+0.0025*ui->CurrentRegulation2BspinBox->value()) * ui->CurrentGainBspinBox->value();
    QString str = QString::number(value,'f',3);
    ui->CurrentOutputBlineEdit->setText(str);
}

void ICXM10480GSetting::on_CurrentRegulation2BspinBox_valueChanged(int arg1)
{
    double value = ui->CurrentRegulation1BspinBox->value() * (0.16+0.0025*arg1) * ui->CurrentGainBspinBox->value();
    QString str = QString::number(value,'f',3);
    ui->CurrentOutputBlineEdit->setText(str);
}

void ICXM10480GSetting::on_CurrentGainBspinBox_valueChanged(int arg1)
{
    double value = ui->CurrentRegulation1BspinBox->value() * (0.16+0.0025*ui->CurrentRegulation2BspinBox->value()) * arg1;
    QString str = QString::number(value,'f',3);
    ui->CurrentOutputBlineEdit->setText(str);
}

void ICXM10480GSetting::on_RefreshRatelspinBox_valueChanged(int arg1)
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



void ICXM10480GSetting::on_SaveFilepushButton_clicked()
{
    GetFormValue();

    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,("Open Config"), "", ("TXT Files (*.txt);; TXT Files (*.txt)"));
    if (!fileName.isNull())
    {
        WriteFile(fileName,regpara);   //fileName是文件名

        UniversalInterface::MessageBoxShow(tr("保存文件"), tr("文件保存成功!"));
    }
    else
    {

    }
}
//
//void ICXM11202GSetting::MessageBoxShow(const char title, QString str)
//{
//	//QMessageBox msg(this);//对话框设置父组件
//	//msg.setWindowTitle(title);//对话框标题
//	//msg.setText(str);//对话框提示文本
//	//msg.setIcon(QMessageBox::NoIcon);//设置图标类型
//	//msg.setStandardButtons(QMessageBox::Ok | QMessageBox:: Cancel);//对话框上包含的按钮
//
//	//if(msg.exec() == QMessageBox::Ok)//模态调用
//	//{
//	//    msg.close();
//	//}
//
//
//}


void ICXM10480GSetting::on_LoadFilepushButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,("Open Config"), "", ("TXT Files (*.txt);; CID Files (*.txt)"));

    if (!fileName.isNull())
    {
        //fileName即是选择的文件名
    }
    else
    {
        return;
    }


    QByteArray data;
    data = ReadFile(fileName);

    for (int i=0;i<data.length();i++)
    {
        regpara[i] = data[i];
    }

    Loadformpara();

    UniversalInterface::MessageBoxShow(tr("加载文件"), tr("文件加载成功!"));
}



void ICXM10480GSetting::on_AdvancedSettingpushButton_clicked()
{
    if(ui->AdvancedSettingpushButton->text() == tr("高级模式"))
    {
        ui->groupBox_3->setVisible(true);
        ui->AdvancedSettinggroupBox->setVisible(false);
        ui->CurrentSettinggroupBox->setVisible(false);
        ui->ChipRlabel->setVisible(false);
        ui->ChipGlabel->setVisible(false);
        ui->ChipBlabel->setVisible(false);
        ui->AdvancedSettingpushButton->setText(tr("普通模式"));
    }
    else if(ui->AdvancedSettingpushButton->text() == tr("普通模式"))
    {
        ui->groupBox_3->setVisible(false);
        ui->AdvancedSettinggroupBox->setVisible(true);
        ui->CurrentSettinggroupBox->setVisible(true);
        ui->ChipRlabel->setVisible(true);
        ui->ChipGlabel->setVisible(true);
        ui->ChipBlabel->setVisible(true);
        ui->AdvancedSettingpushButton->setText(tr("高级模式"));
    }
    else{}
}



void ICXM10480GSetting::on_UseDefectDetectioncheckBox_clicked()
{
    if (!ui->UseDefectDetectioncheckBox->isChecked())
    {
        setCursor(Qt::WaitCursor);
        LAPI::EResult ret = LAPI::clearDeadPoint(0xFF,0xFF);
        if (ret == LAPI::EResult::ER_Success)
        {
            if (ui->UseDefectDetectioncheckBox->isChecked())
            {
                regpara[13 * 6 + 4] = 0x00;
            }

            LAPI::EResult ret2 = LAPI::WriteXMICParam(0xFF,0xFF,regpara);
            if (ret2 == LAPI::EResult::ER_Success)
            {
                UniversalInterface::MessageBoxShow(tr("去坏点"),tr("关闭成功"));
            }
        }
        setCursor(Qt::ArrowCursor);
    }

}
