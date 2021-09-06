#include "advancedsetting.h"
#include "ui_advancedsetting.h"
#include <QDebug>
#include <qglobal.h>
#include <qfiledialog.h>
#include <qobject.h>
#include <QDialog>
#include <qmenu.h>
#include <QMenuBar>
#include <QStatusBar>

//普通界面
#include "universalinterface.h"
#include "smartsetting.h"
#include "rgbchange.h"
#include "datagroup.h"
#include "currentgain.h"
#include "mos5366config.h"
#include "mos5957config.h"
#include "moscfd2138.h"
#include "flashsetting.h"
#include "grayfineprocessing.h"
#include "scanparamater.h"
#include "advancedotherpara.h"
#include "advancedcustom.h"


//芯片界面
#include "icadvancedsetting.h"
#include "iccfd435asetting.h"
#include "iccfd455asetting.h"


QByteArray ModulePara;
QByteArray ICPara;
QByteArray DataPara;




int TXDWorkClk = 150;

AdvancedSetting::AdvancedSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvancedSetting)
{
    ui->setupUi(this);


    ui->comboBox_7->addItem("1");
    ui->comboBox_7->addItem("2");
    ui->comboBox_7->addItem("4");
    ui->comboBox_7->addItem("8");



    //LBLConnection* Connection = LAPI::GetConnection();

    bool result = UniversalInterface::ReadALLPara();
    if (result)
    {
        qDebug() << "Read Successful!!";
    }
    else
    {
        qDebug() << "Read False!!";
        ModulePara = UniversalInterface::Readbin(LBLUIHelper::appParamDataLocation() + "//ModulePara.bin");
        DataPara = UniversalInterface::Readbin(LBLUIHelper::appParamDataLocation() + "//DataPara.bin");
        ICPara = UniversalInterface::Readbin(LBLUIHelper::appParamDataLocation() + "//ICPara.bin");
    }




    LoadingPara();

    CreateAction();



    //ui->pushButton_2->setVisible(false);

    //qDebug() << "=========================";


}

AdvancedSetting::~AdvancedSetting()
{
    delete ui;
}


//void AdvancedSetting::romoveAllItem (QComboBox *cb)
//  {
//      int atemp = cb->count();

//     for (; atemp >= 0; atemp--)
//      {

//          cb->removeItem (atemp);
//          // cb->setItemText (atemp, "ddd");
//     }

// }

void AdvancedSetting::LoadingPara()
{

    ShowPara = true;
    InitCombobox = true;
    initList();
    ui->TXDcomboBox->clear();
    ui->comboBox_6->clear();
    ui->TXDcomboBox->addItems(DclkGclkList);
    ui->comboBox_6->addItems(DclkGclkList);
    ui->TXDcomboBox->setCurrentIndex(-1);
    ui->comboBox_6->setCurrentIndex(-1);

    InitCombobox = false;

    qDebug() << "Start load";


    ui->TXDcomboBox->setCurrentIndex(ShowWorkFrequency(0x18));
    ui->comboBox_6->setCurrentIndex(ShowWorkFrequency(0x1B));

     //ShowPara = true;
    if ((int)ModulePara[0x18] != 0)
    {
        ui->comboBox_2->setCurrentText(QString::number(ModulePara[0x19] * 100 / ModulePara[0x18]));
    }

    ui->comboBox_3->setCurrentText(QString::number((unsigned char)ModulePara[0x1A]));


    ShowPara = true;
    ui->lineEdit->setText(QString::number(((unsigned char)ModulePara[0x06] + (unsigned char)ModulePara[0x07] * 256),10));
    ui->lineEdit_2->setText(QString::number(((unsigned char)ModulePara[0x08] + (unsigned char)ModulePara[0x09] * 256),10));

    Showic();

    ui->lineEdit_4->setText(QString::number((unsigned char)ModulePara[0x25]));

    showMOS();

    ui->lineEdit_6->setText(QString::number((unsigned char)ModulePara[0x26]));

    if ((int)ModulePara[0x1B] != 0)
    {
        ui->comboBox_5->setCurrentText(QString::number(ModulePara[0x1C] * 100 / ModulePara[0x1B]));
    }
    ui->comboBox_4->setCurrentText(QString::number((unsigned char)ModulePara[0x1D]));


    ui->comboBox_7->setCurrentIndex(ModulePara[0x29]);
    ui->spinBox_5->setValue(ModulePara[0x36]);


    ui->spinBox->setValue(ModulePara[0x2A]);
    ui->spinBox_2->setValue(ModulePara[0x2B]);
    ui->spinBox_3->setValue(ModulePara[0x2C]);
    ui->spinBox_4->setValue(ModulePara[0x2D]);

    switch (ModulePara[0x71])
    {
    case 0x00:
        TXDWorkClk = 150;
        break;
    case 0x01:
        TXDWorkClk = 125;
        break;
    case 0x02:
        TXDWorkClk = 100;
        break;
    default:
        break;
    }


    if ((ModulePara[0x66] & 0x80) == 0x80)
    {
        ui->checkBox_2->setChecked(true);
    }
    else
    {
        ui->checkBox_2->setChecked(false);
    }

    if ((ModulePara[0x5C] & 0x20) == 0x20)
    {
        ui->checkBox->setChecked(true);
    }
    else
    {
        ui->checkBox->setChecked(false);
    }

    ShowPara = false;
}
void AdvancedSetting::initList()
{
    DclkGclkList.clear();
    //qDebug() << "0x71:" <<(uchar)ModulePara[0x71];
    switch (ModulePara[0x71])
    {
    case 0:     //150MHz
        DclkGclkList.append("37.5");
        DclkGclkList.append("30.0");
        DclkGclkList.append("25.0");
        DclkGclkList.append("21.4");
        DclkGclkList.append("18.8");
        DclkGclkList.append("16.7");
        DclkGclkList.append("15.0");
        DclkGclkList.append("13.6");
        DclkGclkList.append("12.5");
        DclkGclkList.append("11.5");
        DclkGclkList.append("10.7");
        DclkGclkList.append("10.0");
        DclkGclkList.append("9.4");
        DclkGclkList.append("8.8");
        DclkGclkList.append("8.3");
        DclkGclkList.append("7.9");
        DclkGclkList.append("7.5");
        DclkGclkList.append("7.1");
        DclkGclkList.append("6.8");
        DclkGclkList.append("6.5");
        DclkGclkList.append("6.3");
        DclkGclkList.append("6.0");
        DclkGclkList.append("5.8");
        DclkGclkList.append("5.6");
        DclkGclkList.append("5.4");
        DclkGclkList.append("5.2");
        DclkGclkList.append("5.0");
        DclkGclkList.append("4.8");
        DclkGclkList.append("4.7");
        DclkGclkList.append("4.5");
        DclkGclkList.append("4.4");
        DclkGclkList.append("4.3");
        DclkGclkList.append("4.2");
        DclkGclkList.append("4.1");
        DclkGclkList.append("3.9");
        DclkGclkList.append("3.8");
        DclkGclkList.append("3.7");
        DclkGclkList.append("3.6");
        DclkGclkList.append("3.5");
        DclkGclkList.append("3.3");
        DclkGclkList.append("3.2");
        DclkGclkList.append("3.1");
        DclkGclkList.append("3.0");
        DclkGclkList.append("2.9");
        DclkGclkList.append("2.8");
        DclkGclkList.append("2.6");
        DclkGclkList.append("2.5");
        DclkGclkList.append("2.4");
        break;
    case 1:     //125MHz
        DclkGclkList.append("31.3");
        DclkGclkList.append("25.0");
        DclkGclkList.append("20.8");
        DclkGclkList.append("17.8");
        DclkGclkList.append("15.6");
        DclkGclkList.append("13.9");
        DclkGclkList.append("12.5");
        DclkGclkList.append("11.4");
        DclkGclkList.append("10.4");
        DclkGclkList.append("9.6");
        DclkGclkList.append("8.9");
        DclkGclkList.append("8.3");
        DclkGclkList.append("7.8");
        DclkGclkList.append("7.4");
        DclkGclkList.append("6.9");
        DclkGclkList.append("6.6");
        DclkGclkList.append("6.3");
        DclkGclkList.append("6.0");
        DclkGclkList.append("5.7");
        DclkGclkList.append("5.4");
        DclkGclkList.append("5.2");
        DclkGclkList.append("5.0");
        DclkGclkList.append("4.8");
        DclkGclkList.append("4.6");
        DclkGclkList.append("4.5");
        DclkGclkList.append("4.3");
        DclkGclkList.append("4.2");
        DclkGclkList.append("4.0");
        DclkGclkList.append("3.9");
        DclkGclkList.append("3.8");
        DclkGclkList.append("3.7");
        DclkGclkList.append("3.6");
        DclkGclkList.append("3.5");
        DclkGclkList.append("3.4");
        DclkGclkList.append("3.3");
        DclkGclkList.append("3.2");
        DclkGclkList.append("3.1");
        DclkGclkList.append("3.0");
        DclkGclkList.append("2.9");
        DclkGclkList.append("2.8");
        DclkGclkList.append("2.7");
        DclkGclkList.append("2.6");
        DclkGclkList.append("2.5");
        DclkGclkList.append("2.4");
        DclkGclkList.append("2.3");
        DclkGclkList.append("2.2");
        DclkGclkList.append("2.1");
        DclkGclkList.append("2.0");
        break;
    case 0x02:      //100MHz
        DclkGclkList.append("25.00");
        DclkGclkList.append("20.00");
        DclkGclkList.append("16.67");
        DclkGclkList.append("14.29");
        DclkGclkList.append("12.50");
        DclkGclkList.append("11.11");
        DclkGclkList.append("10.00");
        DclkGclkList.append("9.09");
        DclkGclkList.append("8.33");
        DclkGclkList.append("7.69");
        DclkGclkList.append("7.14");
        DclkGclkList.append("6.67");
        DclkGclkList.append("6.25");
        DclkGclkList.append("5.88");
        DclkGclkList.append("5.56");
        DclkGclkList.append("5.26");
        DclkGclkList.append("5.00");
        DclkGclkList.append("4.76");
        DclkGclkList.append("4.55");
        DclkGclkList.append("4.35");
        DclkGclkList.append("4.17");
        DclkGclkList.append("4.00");
        DclkGclkList.append("3.85");
        DclkGclkList.append("3.70");
        DclkGclkList.append("3.57");
        DclkGclkList.append("3.45");
        DclkGclkList.append("3.33");
        DclkGclkList.append("3.23");
        DclkGclkList.append("3.13");
        DclkGclkList.append("3.03");
        DclkGclkList.append("2.94");
        DclkGclkList.append("2.86");
        DclkGclkList.append("2.78");
        DclkGclkList.append("2.70");
        DclkGclkList.append("2.63");
        DclkGclkList.append("2.56");
        DclkGclkList.append("2.50");
        DclkGclkList.append("2.38");
        DclkGclkList.append("2.33");
        DclkGclkList.append("2.22");
        DclkGclkList.append("2.17");
        DclkGclkList.append("2.08");
        DclkGclkList.append("2.00");
        DclkGclkList.append("1.92");
        DclkGclkList.append("1.85");
        DclkGclkList.append("1.75");
        DclkGclkList.append("1.69");
        DclkGclkList.append("1.61");
        break;
    }


}

int AdvancedSetting::ShowWorkFrequency(int address)
{
    int index = 0;

    switch (ModulePara[address])
    {
    case 4:
        index = 0;
        break;
    case 5:
        index = 1;
        break;
    case 6:
        index = 2;
        break;
    case 7:
        index = 3;
        break;
    case 8:
        index = 4;
        break;
    case 9:
        index = 5;
        break;
    case 10:
        index = 6;
        break;
    case 11:
        index = 7;
        break;
    case 12:
        index = 8;
        break;
    case 13:
        index = 9;
        break;
    case 14:
        index = 10;
        break;
    case 15:
        index = 11;
        break;
    case 16:
        index = 12;
        break;
    case 17:
        index = 13;
        break;
    case 18:
        index = 14;
        break;
    case 19:
        index = 15;
        break;
    case 20:
        index = 16;
        break;
    case 21:
        index = 17;
        break;
    case 22:
        index = 18;
        break;
    case 23:
        index = 19;
        break;
    case 24:
        index = 20;
        break;
    case 25:
        index = 21;
        break;
    case 26:
        index = 22;
        break;
    case 27:
        index = 23;
        break;
    case 28:
        index = 24;
        break;
    case 29:
        index = 25;
        break;
    case 30:
        index = 26;
        break;
    case 31:
        index = 27;
        break;
    case 32:
        index = 28;
        break;
    case 33:
        index = 29;
        break;
    case 34:
        index = 30;
        break;
    case 35:
        index = 31;
        break;
    case 36:
        index = 32;
        break;
    case 37:
        index = 33;
        break;
    case 38:
        index = 34;
        break;
    case 39:
        index = 35;
        break;
    case 40:
        index = 36;
        break;
    case 42:
        index = 37;
        break;
    case 43:
        index = 38;
        break;
    case 45:
        index = 39;
        break;
    case 46:
        index = 40;
        break;
    case 48:
        index = 41;
        break;
    case 50:
        index = 42;
        break;
    case 52:
        index = 43;
        break;
    case 54:
        index = 44;
        break;
    case 57:
        index = 45;
        break;
    case 59:
        index = 46;
        break;
    case 62:
        index = 47;
        break;
    default:
        index = 0;
        break;
    }

    return index;

}

void AdvancedSetting::Showic()
{
    unsigned char index = (unsigned char)ModulePara[0x13] + (unsigned char)ModulePara[0x14] * 256;

    switch (index)
    {
    case CONVENTSIONALCHIP:
        ui->lineEdit_3->setText(QString::fromLocal8Bit("常规芯片"));
        break;
    case ICN_2038S:
        ui->lineEdit_3->setText("ICN-2038S");
        break;
    case MBI_5038:
        ui->lineEdit_3->setText("MBI-5038");
        break;
    case SUM_2017T:
        ui->lineEdit_3->setText("SUM-2017T");
        break;
    case MBI_5124:
        ui->lineEdit_3->setText("MBI-5124");
        break;
    case SUM_2017:
        ui->lineEdit_3->setText("SUM-2017");
        break;
    case SUM_2030:
        ui->lineEdit_3->setText("SUM-2030");
        break;
    case SUM_2030T:
        ui->lineEdit_3->setText("SUM-2030T");
        break;
    case SUM_2032:
        ui->lineEdit_3->setText("SUM-2032");
        break;
    case SUM_2131:
        ui->lineEdit_3->setText("SUM-2131");
        break;
    case SUM_2033:
        ui->lineEdit_3->setText("SUM-2033");
        break;
    case MBI_5252:
        ui->lineEdit_3->setText("MBI-5252");
        break;
    case MBI_5041B:
        ui->lineEdit_3->setText("MBI-5041B");
        break;
    case MBI_5041Q:
        ui->lineEdit_3->setText("MBI-5041Q");
        break;
    case MBI_5042_5041:
        ui->lineEdit_3->setText("MBI-5042/5041");
        break;
    case MBI_5042B:
        ui->lineEdit_3->setText("MBI-5042B");
        break;
    case MBI_5043:
        ui->lineEdit_3->setText("MBI-5043");
        break;
    case MBI_5151:
        ui->lineEdit_3->setText("MBI-5151");
        break;
    case MBI_5047:
        ui->lineEdit_3->setText("MBI-5047");
        break;
    case MBI_5152:
        ui->lineEdit_3->setText("MBI-5152");
        break;
    case MBI_5153:
        ui->lineEdit_3->setText("MBI-5153");
        break;
    case MBI_5155:
        ui->lineEdit_3->setText("MBI-5155");
        break;
    case SUM_2035:
        ui->lineEdit_3->setText("SUM-2035");
        break;
    case SM_16259:
        ui->lineEdit_3->setText("SM-16259");
        break;
    case MBI_5353:
        ui->lineEdit_3->setText("MBI-5353");
        break;
    case SUM_6086:
        ui->lineEdit_3->setText("SUM-6086");
        break;
    case LS_9935:
        ui->lineEdit_3->setText("LS-9935");
        break;
    case ICN_2055_2069:
        ui->lineEdit_3->setText("ICN-2055/2069");
        break;
    case CFD_335A:
        ui->lineEdit_3->setText("CFD-335A");
        break;
    case SUM_2035NEW:
        ui->lineEdit_3->setText("SUM-2035NEW");
        break;
    case ICN_2153:
        ui->lineEdit_3->setText("ICN-2153");
        break;
    case FM_6363:
        ui->lineEdit_3->setText("FM-6363");
        break;
    case FM_6565:
        ui->lineEdit_3->setText("FM-6565");
        break;
    case LS_9935B:
        ui->lineEdit_3->setText("LS-9935B");
        break;
    case CFD_435A:
        ui->lineEdit_3->setText("CFD-435A");
        break;
    case CFD_555A:
        ui->lineEdit_3->setText("CFD-555A");
        break;
    case CFD_455A:
        ui->lineEdit_3->setText("CFD-455A");
        break;
    case DP_3246:
        ui->lineEdit_3->setText("DP-3246");
        break;
    default:
        break;

    }
}

void AdvancedSetting::showMOS()
{
    unsigned char index = ModulePara[0x12];

    switch (index)
    {
    case 0x00:
        ui->lineEdit_5->setText(QString::fromLocal8Bit("直通译码"));
        break;
    case 0x01:
        ui->lineEdit_5->setText(QString::fromLocal8Bit("138译码"));
        break;
    case 0x02:
        ui->lineEdit_5->setText(QString::fromLocal8Bit("5957译码"));
        break;
    case 0x03:
        ui->lineEdit_5->setText(QString::fromLocal8Bit("5366译码"));
        break;
    case 0x04:
        ui->lineEdit_5->setText(QString::fromLocal8Bit("2018/2019译码"));
        break;
    case 0x05:
        ui->lineEdit_5->setText(QString::fromLocal8Bit("C82018译码"));
        break;
    case 0x06:
        ui->lineEdit_5->setText(QString::fromLocal8Bit("CFD2138译码"));
        break;
    case 0x07:
        ui->lineEdit_5->setText(QString::fromLocal8Bit("RUL5158译码"));
    default:
        break;
    }
}
void AdvancedSetting::on_SmartSettingBtn_clicked()
{
//        SmartSetting *smartsetting = new SmartSetting();
//        smartsetting->show();
    SmartSetting *smartsetting = new SmartSetting();

    QObject::connect(smartsetting, SIGNAL(SendSignal()),this,SLOT(LoadingPara()));

    smartsetting->show();


}

void AdvancedSetting::on_TXDcomboBox_currentIndexChanged(int index)
{
    if (InitCombobox)
    {
        return;
    }

    unsigned char value = 0;
    switch (index)
    {
    case 0:
        value = 4;
        break;
    case 1:
        value = 5;
        break;
    case 2:
        value = 6;
        break;
    case 3:
        value = 7;
        break;
    case 4:
        value = 8;
        break;
    case 5:
        value = 9;
        break;
    case 6:
        value = 10;
        break;
    case 7:
        value = 11;
        break;
    case 8:
        value = 12;
        break;
    case 9:
        value = 13;
        break;
    case 10:
        value = 14;
        break;
    case 11:
        value = 15;
        break;
    case 12:
        value = 16;
        break;
    case 13:
        value = 17;
        break;
    case 14:
        value = 18;
        break;
    case 15:
        value = 19;
        break;
    case 16:
        value = 20;
        break;
    case 17:
        value = 21;
        break;
    case 18:
        value = 22;
        break;
    case 19:
        value = 23;
        break;
    case 20:
        value = 24;
        break;
    case 21:
        value = 25;
        break;
    case 22:
        value = 26;
        break;
    case 23:
        value = 27;
        break;
    case 24:
        value = 28;
        break;
    case 25:
        value = 29;
        break;
    case 26:
        value = 30;
        break;
    case 27:
        value = 31;
        break;
    case 28:
        value = 32;
        break;
    case 29:
        value = 33;
        break;
    case 30:
        value = 34;
        break;
    case 31:
        value = 35;
        break;
    case 32:
        value = 36;
        break;
    case 33:
        value = 37;
        break;
    case 34:
        value = 38;
        break;
    case 35:
        value = 39;
        break;
    case 36:
        value = 40;
        break;
    case 37:
        value = 42;
        break;
    case 38:
        value = 43;
        break;
    case 39:
        value = 45;
        break;
    case 40:
        value = 46;
        break;
    case 41:
        value = 48;
        break;
    case 42:
        value = 50;
        break;
    case 43:
        value = 52;
        break;
    case 44:
        value = 54;
        break;
    case 45:
        value = 57;
        break;
    case 46:
        value = 59;
        break;
    case 47:
        value = 62;
        break;
    default:
        break;
    }

    ModulePara[0x18] = value;

    ui->comboBox_2->clear();
    ui->comboBox_3->clear();

    int i = 0;
    for (i=0;i<value;i++)
    {
        ui->comboBox_2->addItem(QString::number(i * 100 / value));
        ui->comboBox_3->addItem(QString::number(i));
    }

    ui->comboBox_2->setCurrentText(QString::number((unsigned char)ModulePara[0x19] * 100 / (unsigned char)ModulePara[0x18]));
    ui->comboBox_3->setCurrentText(QString::number(value/2));

    if (!ShowPara)
    {
        ui->comboBox_2->setCurrentIndex(value/2);
        ModulePara[0x19] = qRound((unsigned char)ModulePara[0x18] * ui->comboBox_2->currentText().toInt() / 100.0);
    }

    int VR = VisionRefresh();
    ui->lineEdit_8->setText(QString::number(VR));

}
void AdvancedSetting::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    if(ShowPara)
    {
        return;
    }
    ModulePara[0x19] = qRound((unsigned char)ModulePara[0x18] * arg1.toUInt() / 100.0);
    qDebug() << "SetModulePara[0x19]:" << (uchar)ModulePara[0x19];
}
void AdvancedSetting::on_comboBox_3_currentIndexChanged(int index)
{
    if(ShowPara)
    {
        return;
    }
    ModulePara[0x1A] = index;
}



void AdvancedSetting::on_comboBox_6_currentIndexChanged(int index)
{
    if (InitCombobox)
    {
        return;
    }
    unsigned char value = 0;
    switch (index)
    {
    case 0:
        value = 4;
        break;
    case 1:
        value = 5;
        break;
    case 2:
        value = 6;
        break;
    case 3:
        value = 7;
        break;
    case 4:
        value = 8;
        break;
    case 5:
        value = 9;
        break;
    case 6:
        value = 10;
        break;
    case 7:
        value = 11;
        break;
    case 8:
        value = 12;
        break;
    case 9:
        value = 13;
        break;
    case 10:
        value = 14;
        break;
    case 11:
        value = 15;
        break;
    case 12:
        value = 16;
        break;
    case 13:
        value = 17;
        break;
    case 14:
        value = 18;
        break;
    case 15:
        value = 19;
        break;
    case 16:
        value = 20;
        break;
    case 17:
        value = 21;
        break;
    case 18:
        value = 22;
        break;
    case 19:
        value = 23;
        break;
    case 20:
        value = 24;
        break;
    case 21:
        value = 25;
        break;
    case 22:
        value = 26;
        break;
    case 23:
        value = 27;
        break;
    case 24:
        value = 28;
        break;
    case 25:
        value = 29;
        break;
    case 26:
        value = 30;
        break;
    case 27:
        value = 31;
        break;
    case 28:
        value = 32;
        break;
    case 29:
        value = 33;
        break;
    case 30:
        value = 34;
        break;
    case 31:
        value = 35;
        break;
    case 32:
        value = 36;
        break;
    case 33:
        value = 37;
        break;
    case 34:
        value = 38;
        break;
    case 35:
        value = 39;
        break;
    case 36:
        value = 40;
        break;
    case 37:
        value = 42;
        break;
    case 38:
        value = 43;
        break;
    case 39:
        value = 45;
        break;
    case 40:
        value = 46;
        break;
    case 41:
        value = 48;
        break;
    case 42:
        value = 50;
        break;
    case 43:
        value = 52;
        break;
    case 44:
        value = 54;
        break;
    case 45:
        value = 57;
        break;
    case 46:
        value = 59;
        break;
    case 47:
        value = 62;
        break;
    default:
        break;
    }

    ui->comboBox_5->clear();
    ui->comboBox_4->clear();

    ModulePara[0x1B] = value;

    int i = 0;
    for (i=0;i<value;i++)
    {
        ui->comboBox_5->addItem(QString::number(i * 100 / value));
        ui->comboBox_4->addItem(QString::number(i));
    }
    ui->comboBox_5->setCurrentText(QString::number((unsigned char)ModulePara[0x1C] * 100 / (unsigned char)ModulePara[0x1B]));
    ui->comboBox_4->setCurrentText(QString::number(value/2));

    if (!ShowPara)
    {
        ui->comboBox_5->setCurrentIndex(value/2);
        ModulePara[0x1C] = qRound((unsigned char)ModulePara[0x1B] * ui->comboBox_5->currentText().toInt() / 100.0);
    }

}
void AdvancedSetting::on_comboBox_5_currentIndexChanged(const QString &arg1)
{
    if(ShowPara)
    {
        return;
    }
    ModulePara[0x1C] = qRound((unsigned char)ModulePara[0x1B] * arg1.toUInt() / 100.0);
}
void AdvancedSetting::on_comboBox_4_currentIndexChanged(int index)
{
    if(ShowPara)
    {
        return;
    }
    ModulePara[0x1D] = index;
}





void AdvancedSetting::on_comboBox_7_currentIndexChanged(int index)
{
    ModulePara[0x29] = index;
}

void AdvancedSetting::on_spinBox_valueChanged(int arg1)
{
    ModulePara[0x2A] = arg1;
}

void AdvancedSetting::on_spinBox_2_valueChanged(int arg1)
{
    ModulePara[0x2B] = arg1;
}

void AdvancedSetting::on_spinBox_3_valueChanged(int arg1)
{
    ModulePara[0x2C] = arg1;
}


void AdvancedSetting::on_spinBox_4_valueChanged(int arg1)
{
    ModulePara[0x2D] = arg1;

    int VR = VisionRefresh();
      ui->lineEdit_8->setText(QString::number(VR));
}



void AdvancedSetting::on_spinBox_5_valueChanged(int arg1)
{
    ModulePara[0x36] = arg1;
}






void AdvancedSetting::on_pushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);

    bool result = UniversalInterface::SendALLPara();
    this->setCursor(Qt::ArrowCursor);

    if (result)
    {
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("设置"),QString::fromLocal8Bit("设置成功"));
    }
    else{
         UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("设置"),QString::fromLocal8Bit("设置失败"));
    }



}








void AdvancedSetting::on_pushButton_3_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("Open File"), "", tr("bin Files (*.bin)"));
    if (!fileName.isNull())
    {
        //fileName即是选择的文件名
    }
    else
    {
        return;
    }
    QByteArray file = UniversalInterface::Readbin(fileName);

    if(file.length() == 1024 * 3)
    {

        for (int i=0;i<1024;i++)
        {
            ModulePara[i] = file[i];
            DataPara[i] = file[i + 1024];
            ICPara[i] = file[i + 2048];

        }
        LoadingPara();
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("导入文件"),QString::fromLocal8Bit("文件导入成功"));
    }
    else
    {
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("导入文件"),QString::fromLocal8Bit("文件长度不符"));
    }

}

void AdvancedSetting::on_pushButton_4_clicked()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,tr("Open File"), "", tr("bin Files (*.bin)"));

    if (!fileName.isEmpty())
    {
        QByteArray file;
        file.resize(1024*3);
        for (int i=0;i<1024;i++)
        {
            file[i] = ModulePara[i];
            file[i + 1024] = DataPara[i];
            file[i + 2048] = ICPara[i];
        }
        //fileName即是选择的文件名
        UniversalInterface::Writebin(fileName,file);
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("导出文件"),QString::fromLocal8Bit("文件导出成功"));
    }
    else
    {
        return;
    }



}

int AdvancedSetting::VisionRefresh()
{
    int ReadFieldFrequency = 0;
    if (ReadFieldFrequency == 0)
    {
        ReadFieldFrequency = 60;
    }
    int VR = 0;

    int FrequencyDoubling = 0;

    int GclkValue = ModulePara[0x1B];
    int TXDValue = ModulePara[0x18];


    //倍频
    if (ui->comboBox_7->currentText().toUInt() != 0)
    {
        FrequencyDoubling = 1024 / ui->comboBox_7->currentText().toUInt();
    }

    //子场个数
    //int SubField = ICPara[5];
    //扫描数
    int Scannum = ModulePara[0x25];
    //扫描方向芯片数
    //int Chipnum =

    //低灰补偿
    int Lowgrayadd = ICPara[0x83];
    //首行补偿
    int Firstadd = ICPara[0x82];
    //换行延时

    int NewlineDelay = ModulePara[0x2D];


    //视觉刷新率计算
    int icNumber = (unsigned char)ModulePara[0x13] + (unsigned char)ModulePara[0x14] * 256;
    if (icNumber < 0x81)
    {
        //非自解码
        if(ui->lineEdit_3->text() == "ICN-2038S")
        {
            VR = (int)(1 / (((8 * 16 * 2 + NewlineDelay) * Scannum) * (1 / (ui->TXDcomboBox->currentText().toUInt() * 1000000))));
        }
        else
        {

        }
    }
    else
    {
        //自解码
        if(ui->lineEdit_3->text() == "MBI-5043")
        {
            if ((ICPara[0x100] & 0x08) == 0x08)
            {
                VR = (int)((TXDWorkClk * 1000000 / GclkValue) * 2 / 1024);
            }
            else
            {
                VR = (int)((TXDWorkClk * 1000000 / GclkValue) / 1024);
            }
        }
        else
        {
            if ((ui->lineEdit_3->text() == "SUM-2033") || (ui->lineEdit_3->text() == "SUM-2035") || (ui->lineEdit_3->text() == "SUM-6086") || (ui->lineEdit_3->text() == "CFD-335A") || (ui->lineEdit_3->text() == "CFD-435A"))
            {
                if ((ICPara[0x11F] & 0x04) == 0x04)
                {
                    VR = (int)((TXDWorkClk * 1000000 / GclkValue / ReadFieldFrequency - Firstadd - ((TXDValue / GclkValue) * 48)) / (Scannum * (FrequencyDoubling / 2 + Lowgrayadd + NewlineDelay)));
                }
                else
                {
                    VR = (int)((TXDWorkClk * 1000000 / GclkValue / ReadFieldFrequency - Firstadd - ((TXDValue / GclkValue) * 48)) / (Scannum * (FrequencyDoubling + Lowgrayadd + NewlineDelay)));
                }
            }
            else if (ui->lineEdit_3->text() == "MBI-5353")
            {
                if ((ICPara[0x100] & 0x08) == 0x08)
                {
                    VR = (int)((TXDWorkClk * 1000000 / GclkValue / ReadFieldFrequency - Firstadd - ((TXDValue / GclkValue) * 48)) / (Scannum * (FrequencyDoubling / 2 + Lowgrayadd + NewlineDelay)));
                }
                else
                {
                    VR = (int)((TXDWorkClk * 1000000 / GclkValue / ReadFieldFrequency - Firstadd - ((TXDValue / GclkValue) * 48)) / (Scannum * (FrequencyDoubling + Lowgrayadd + NewlineDelay)));
                }
            }
            else if  (ui->lineEdit_3->text() == "CFD-455A")
            {
                //混频
                if ((ICPara[0x106] & 0x08) == 0x08)
                {
                    VR = (int)((TXDWorkClk * 1000000 / GclkValue / ReadFieldFrequency - 16 - ((TXDValue / GclkValue) * 48)) / (Scannum * (40 + 17 + NewlineDelay)));
                }
                else
                {
                    if ((ICPara[0x11F] & 0x04) == 0x04)
                    {
                        VR = (int)((TXDWorkClk * 1000000 / GclkValue / ReadFieldFrequency - Firstadd - ((TXDValue / GclkValue) * 48)) / (Scannum * (FrequencyDoubling / 2 + Lowgrayadd + NewlineDelay)));
                    }
                    else
                    {
                        VR = (int)((TXDWorkClk * 1000000 / GclkValue / ReadFieldFrequency - Firstadd - ((TXDValue / GclkValue) * 48)) / (Scannum * (FrequencyDoubling + Lowgrayadd + NewlineDelay)));
                    }
                }
            }
            else
            {
                VR = (int)((TXDWorkClk * 1000000 / GclkValue / ReadFieldFrequency - Firstadd - ((TXDValue / GclkValue) * 48)) / (Scannum * (FrequencyDoubling + Lowgrayadd + NewlineDelay)));
            }
        }

    }


    //非自解码
    if (icNumber < 0x81)
    {

    }
    else
    {
        double beipin = 0;
        double chu = 0;
        if ((ui->lineEdit_3->text() == "SUM-2035") || (ui->lineEdit_3->text() == "SUM-6086") || (ui->lineEdit_3->text() == "SUM-2033") || (ui->lineEdit_3->text() == "CFD-335A") || (ui->lineEdit_3->text() == "CFD-435A"))
        {
            if ((ICPara[0x100] & 0x08) == 0x08)
            {
                chu = 2;
            }
            else
            {
                chu = 1;
            }
            switch (ui->comboBox_7->currentIndex())
            {
            case 0:
                beipin = 1024 / chu;
                break;
            case 1:
                beipin = 512 / chu;
                break;
            case 2:
                beipin = 256 / chu;
                break;
            case 3:
                beipin = 128 / chu;
                break;
            default:
                break;
            }
        }
        else if (ui->lineEdit_3->text() == "CFD-455A")
        {
            //混频
            if ((ICPara[0x106] & 0x08) == 0x08)
            {
                beipin = 40;
            }
            else if ((ICPara[0x10C] & 0x04) == 0x04)
            {
                chu = 2;
            }
            else
            {
                chu = 1;
            }

            switch (ui->comboBox_7->currentIndex())
            {
            case 0:
                beipin = 1024 / chu;
                break;
            case 1:
                beipin = 512 / chu;
                break;
            case 2:
            {
                //qDebug() << "----------------";

                beipin = 256 / chu;
                //qDebug() << "++++++++++++++";
            }
                break;
            case 3:
                beipin = 128 / chu;
                break;
            default:
                break;
            }
        }
        else
        {
            switch (ui->comboBox_7->currentIndex())
            {
            case 0:
                beipin = 1024;
                break;
            case 1:
                beipin = 512;
                break;
            case 2:
                beipin = 256;
                break;
            case 3:
                beipin = 128;
                break;
            default:
                break;
            }
        }
        //亮度效率
        double Efficiency = 0;


        Efficiency = (VR * Scannum * (beipin)) / (TXDWorkClk * 1000000 / GclkValue * 1.0 / ReadFieldFrequency) * 100.0;

        ui->lineEdit_7->setText(QString::number(Efficiency,'f',2));

    }

    if (ui->lineEdit_3->text() == "ICN-2038S")
    {

    }
    else
    {
         VR = (int)(VR * 1.0) * ReadFieldFrequency;
    }



    return VR;
}














void AdvancedSetting::on_checkBox_clicked(bool checked)
{
    if (ShowPara)
    {
        return;
    }

      this->setCursor(Qt::WaitCursor);
    if (checked)
    {
        ModulePara[0x5C] = ModulePara[0x5C] | 0x20;
    }
    else
    {
        ModulePara[0x5C] = ModulePara[0x5C] & 0xDF;
    }


    //发送参数
    bool result = UniversalInterface::SendALLPara();

    if (result)
    {
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("设置"),QString::fromLocal8Bit("设置成功"));
    }
    else{
         UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("设置"),QString::fromLocal8Bit("设置失败"));
    }
     this->setCursor(Qt::ArrowCursor);
}
void AdvancedSetting::on_checkBox_2_clicked(bool checked)
{
    if (ShowPara)
    {
        return;
    }

    this->setCursor(Qt::WaitCursor);
    if (checked)
    {
        ModulePara[0x66] = ModulePara[0x66] | 0x80;
    }
    else
    {
        ModulePara[0x66] = ModulePara[0x66] & 0x7F;
    }

    //发送参数
    bool result = UniversalInterface::SendALLPara();

    if (result)
    {
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("设置"),QString::fromLocal8Bit("设置成功"));
    }
    else{
         UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("设置"),QString::fromLocal8Bit("设置失败"));
    }
     this->setCursor(Qt::ArrowCursor);
}


void AdvancedSetting::on_rgbChangeBtn_clicked()
{
    RGBchange *rgbchange = new RGBchange();
    rgbchange->show();
}

void AdvancedSetting::on_dataGroupBtn_clicked()
{
    DataGroup *datagroup = new DataGroup();
    datagroup->show();
}







void AdvancedSetting::CreateAction()
{
    ui->toolButton->setToolButtonStyle( Qt::ToolButtonTextUnderIcon);
    ui->toolButton->setPopupMode(QToolButton::InstantPopup);
    // 创建QMenu
    QMenu *menu = new QMenu();
    //创建QAction
    QAction *ICconfig = new QAction(QString::fromLocal8Bit("驱动芯片设置"),AdvancedSetting::ui->toolButton);
    menu->addAction(ICconfig);
    connect(ICconfig,SIGNAL(triggered()),this,SLOT(ICconfigShow()));

    QAction *CurrentConfig = new QAction(QString::fromLocal8Bit("电流增益设置"),AdvancedSetting::ui->toolButton);
    menu->addAction(CurrentConfig);
    connect(CurrentConfig,SIGNAL(triggered()),this,SLOT(CurrentConfigShow()));

    QAction *MOSConfig = new QAction(QString::fromLocal8Bit("行管设置"),AdvancedSetting::ui->toolButton);
    menu->addAction(MOSConfig);
    connect(MOSConfig,SIGNAL(triggered()),this,SLOT(MOSConfigShow()));

    QAction *FLASHConfig = new QAction(QString::fromLocal8Bit("FLASH设置"),AdvancedSetting::ui->toolButton);
    menu->addAction(FLASHConfig);
    connect(FLASHConfig,SIGNAL(triggered()),this,SLOT(FLASHConfig()));

    QAction *GrayFineProcessing = new QAction(QString::fromLocal8Bit("灰度精细处理"),AdvancedSetting::ui->toolButton);
    menu->addAction(GrayFineProcessing);
    connect(GrayFineProcessing,SIGNAL(triggered()),this,SLOT(GrayFineProcessingShow()));

    QAction *Scan = new QAction(QString::fromLocal8Bit("扫描表设置"),AdvancedSetting::ui->toolButton);
    menu->addAction(Scan);
    connect(Scan,SIGNAL(triggered()),this,SLOT(ScanShow()));

    ui->toolButton->setStyleSheet("QToolButton::menu-indicator{image:None;}");

    // 为QToolButton设置菜单
    ui->toolButton->setMenu(menu);
}
void AdvancedSetting::on_toolButton_clicked()
{

}
void AdvancedSetting::ICconfigShow()
{
    //qDebug() << QStringLiteral("驱动芯片设置");

    uint16_t index = (unsigned char)ModulePara[0x13] + (unsigned char)ModulePara[0x14] * 256;

    switch (index)
    {
    case CONVENTSIONALCHIP:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case ICN_2038S:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5038:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case SUM_2017T:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5124:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case SUM_2017:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case SUM_2030:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case SUM_2030T:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case SUM_2032:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case SUM_2131:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case SUM_2033:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5252:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5041B:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5041Q:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5042_5041:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5042B:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5043:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5151:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5047:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5152:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5153:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5155:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case SUM_2035:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case SM_16259:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case MBI_5353:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case SUM_6086:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case LS_9935:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case ICN_2055_2069:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case CFD_335A:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case SUM_2035NEW:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case ICN_2153:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case FM_6363:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case FM_6565:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case LS_9935B:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case CFD_435A:
    {
        ICCFD435ASetting *iccfd435a = new ICCFD435ASetting();
        iccfd435a->show();
        break;
    }
    case CFD_555A:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    case CFD_455A:
    {
        ICCFD455ASetting *iccfd455a = new ICCFD455ASetting();
        iccfd455a->show();
        break;
    }
    case DP_3246:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting();
        icadvanced->show();
        break;
    }
    default:
        break;

    }

    int VR = VisionRefresh();
    ui->lineEdit_8->setText(QString::number(VR));
}
void AdvancedSetting::CurrentConfigShow()
{
    CurrentGain *currentgain = new CurrentGain();
    currentgain->show();
}
void AdvancedSetting::MOSConfigShow()
{
    //qDebug() << QStringLiteral("行管设置");
    switch (ModulePara[0x12])
    {
    case 0:
        break;
    case 1:
        break;
    case 2:
    {
        MOS5957config *mos5957 = new MOS5957config();
        mos5957->show();
        break;
    }
    case 3:
    {
        MOS5366config *mos5366 = new MOS5366config();
        mos5366->show();
        break;
    }
    case 4:
        break;
    case 5:
        break;
    case 6:
    {
        MOSCFD2138 *moscfd2138 = new MOSCFD2138();
        moscfd2138->show();
        break;
    }
    default:
        break;
    }
}
void AdvancedSetting::FLASHConfig()
{
    FLASHsetting *flashsetting = new FLASHsetting();
    flashsetting->show();
}
void AdvancedSetting::GrayFineProcessingShow()
{
    GrayFineProcessing *grayfinepro = new GrayFineProcessing();
    grayfinepro->show();
}
void AdvancedSetting::ScanShow()
{
    Scanparamater *scanpara = new Scanparamater();
    scanpara->show();
}



void AdvancedSetting::on_OtherpushButton_clicked()
{
    AdvancedOtherPara *advancedother = new AdvancedOtherPara();
    advancedother->show();

//    QString filename = UniversalInterface::GetMOSFilename(0x02);
//    QByteArray aa = UniversalInterface::getExcelContent("MOS",filename);
//    for (int i=0;i<aa.length();i++)
//    {
//        qDebug() << QString::number(aa[i]);
//    }

}

void AdvancedSetting::on_ReadpushButton_clicked()
{
    bool result = UniversalInterface::ReadALLPara();

    if (result)
    {
          LoadingPara();
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("回读"),QString::fromLocal8Bit("回读成功"));
    }
    else{
         UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("回读"),QString::fromLocal8Bit("回读失败"));
    }

}

void AdvancedSetting::on_pushButton_2_clicked()
{
    AdvancedCustom *custom = new AdvancedCustom();
    custom->show();
}
