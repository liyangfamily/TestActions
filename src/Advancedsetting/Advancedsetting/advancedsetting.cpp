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
#include <math.h>
#include "../MaxConfig3/Core/icore.h"

//普通界面
#include "universalinterface.h"
#include "smartsetting.h"
#include "rgbchange.h"
#include "datagroup.h"
#include "currentgain.h"
#include "flashsetting.h"
#include "grayfineprocessing.h"
#include "scanparamater.h"
#include "advancedotherpara.h"
#include "advancedcustom.h"
#include "colorgamut.h"

//行管界面
#include "mos5366config.h"
#include "mos5957config.h"
#include "moscfd2138config.h"
#include "mosc82018config.h"
#include "mosicnd2018config.h"

//芯片界面
#include "icadvancedsetting.h"
#include "iccfd435asetting.h"
#include "iccfd455asetting.h"
#include "icxm10480gsetting.h"
#include "icxm11202gsetting.h"


QByteArray ModulePara;
QByteArray ICPara;
QByteArray DataPara;


#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif

int TXDWorkClk = 150;

AdvancedSetting::AdvancedSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvancedSetting)
{
    ui->setupUi(this);
    //setWindowFlag(Qt::WindowContextHelpButtonHint,true);

    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag                  |= Qt::WindowMinimizeButtonHint;
    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    setWindowFlags(windowFlag);


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

    //setFixedSize(this->width(),this->height());

    LoadingPara();

    CreateAction();


    //ui->ButtonColorGamdat->setVisible(false);

    //ui->pushButton_2->setVisible(false);




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
    qDebug()<<"-------------------------------------";
    ui->TXDcomboBox->addItems(DclkGclkList);
    ui->comboBox_6->addItems(DclkGclkList);
//    ui->TXDcomboBox->setCurrentIndex(-1);
//    ui->comboBox_6->setCurrentIndex(-1);

    InitCombobox = false;

    qDebug() << "Start load";


    ui->TXDcomboBox->setCurrentIndex(ShowWorkFrequency(0x18));
    ui->comboBox_6->setCurrentIndex(ShowWorkFrequency(0x1B));

     //ShowPara = true;
    if ((int)ModulePara[0x18] != 0)
    {
        ui->comboBox_2->setCurrentText(QString::number((uchar)ModulePara[0x19] * 100 / (uchar)ModulePara[0x18]));
    }

    ui->comboBox_3->setCurrentText(QString::number((uchar)ModulePara[0x1A]));


    ShowPara = true;
    ui->lineEdit->setText(QString::number(((uchar)ModulePara[0x02] + (uchar)ModulePara[0x03] * 256),10));
    ui->lineEdit_2->setText(QString::number(((uchar)ModulePara[0x04] + (uchar)ModulePara[0x05] * 256),10));

    Showic();

    ui->lineEdit_4->setText(QString::number((uchar)ModulePara[0x25]));

    showMOS();

    ui->lineEdit_6->setText(QString::number((uchar)ModulePara[0x26]));

    if ((int)ModulePara[0x1B] != 0)
    {
        ui->comboBox_5->setCurrentText(QString::number((uchar)ModulePara[0x1C] * 100 / (uchar)ModulePara[0x1B]));
    }
    ui->comboBox_4->setCurrentText(QString::number((uchar)ModulePara[0x1D]));


    ui->comboBox_7->setCurrentIndex((uchar)ModulePara[0x29]);
    ui->spinBox_5->setValue((uchar)ModulePara[0x36]);


    ui->spinBox->setValue((uchar)ModulePara[0x2A]);
    ui->spinBox_2->setValue((uchar)ModulePara[0x2B]);
    ui->spinBox_3->setValue((uchar)ModulePara[0x2C]);
    ui->spinBox_4->setValue((uchar)ModulePara[0x2D]);

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
    qDebug() << "0x71:" <<(uchar)ModulePara[0x71];


    switch ((uchar)ModulePara[0x71])
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
    default:    //150M
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
    }


}

int AdvancedSetting::ShowWorkFrequency(int address)
{
    int index = 0;

    switch ((uchar)ModulePara[address])
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
    unsigned char index = (uchar)ModulePara[0x13] + (uchar)ModulePara[0x14] * 256;

    switch ((uchar)index)
    {
    case CONVENTSIONALCHIP:
        ui->lineEdit_3->setText(tr("常规芯片"));
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
    case ICND_2138:
        ui->lineEdit_3->setText("ICND-2138");
        break;
    case XM11202G:
        ui->lineEdit_3->setText("XM-11202G");
        break;
    case XM10480G:
        ui->lineEdit_3->setText("XM-10480G");
        break;
    default:
        break;

    }
}

void AdvancedSetting::showMOS()
{
    uchar index = (uchar)ModulePara[0x12];

    switch ((uchar)index)
    {
    case 0x00:
        ui->lineEdit_5->setText(tr("直通译码"));
        break;
    case 0x01:
        ui->lineEdit_5->setText(tr("138译码"));
        break;
    case 0x02:
        ui->lineEdit_5->setText(tr("5957译码"));
        break;
    case 0x03:
        ui->lineEdit_5->setText(tr("5366译码"));
        break;
    case 0x04:
        ui->lineEdit_5->setText(tr("2018/2019译码"));
        break;
    case 0x05:
        ui->lineEdit_5->setText(tr("C82018译码"));
        break;
    case 0x06:
        ui->lineEdit_5->setText(tr("CFD2138译码"));
        break;
    case 0x07:
        ui->lineEdit_5->setText(tr("RUL5158译码"));
    default:
        break;
    }
}
void AdvancedSetting::on_SmartSettingBtn_clicked()
{
//        SmartSetting *smartsetting = new SmartSetting();
//        smartsetting->show();
    SmartSetting *smartsetting = new SmartSetting(this);

    QObject::connect(smartsetting, SIGNAL(SendSignal()),this,SLOT(LoadingPara()));

    smartsetting->show();


}

void AdvancedSetting::on_TXDcomboBox_currentIndexChanged(int index)
{
    if (InitCombobox)
    {
        return;
    }

    uchar value = 0;
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

    ui->comboBox_2->setCurrentText(QString::number((uchar)ModulePara[0x19] * 100 / (uchar)ModulePara[0x18]));
    ui->comboBox_3->setCurrentText(QString::number(value/2));

    if (!ShowPara)
    {
        ui->comboBox_2->setCurrentIndex(value/2);
        ModulePara[0x19] = qRound((uchar)ModulePara[0x18] * ui->comboBox_2->currentText().toInt() / 100.0);
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
    ModulePara[0x19] = qRound((uchar)ModulePara[0x18] * arg1.toUInt() / 100.0);
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
    uchar value = 0;
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
    ui->comboBox_5->setCurrentText(QString::number((uchar)ModulePara[0x1C] * 100 / (uchar)ModulePara[0x1B]));
    ui->comboBox_4->setCurrentText(QString::number(value/2));

    if (!ShowPara)
    {
        ui->comboBox_5->setCurrentIndex(value/2);
        ModulePara[0x1C] = qRound((uchar)ModulePara[0x1B] * ui->comboBox_5->currentText().toInt() / 100.0);
    }

    int VR = VisionRefresh();
    ui->lineEdit_8->setText(QString::number(VR));

}
void AdvancedSetting::on_comboBox_5_currentIndexChanged(const QString &arg1)
{
    if(ShowPara)
    {
        return;
    }
    ModulePara[0x1C] = qRound((uchar)ModulePara[0x1B] * arg1.toUInt() / 100.0);
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
    ModulePara[0x29] = (uchar)index;
    int VR = VisionRefresh();
    ui->lineEdit_8->setText(QString::number(VR));

    int index1 = (unsigned char)ModulePara[0x13]/* + (unsigned char)ModulePara[0x14] * 256*/;

    qDebug() << "index1:" << index1;
    switch (index1)
    {
    case CONVENTSIONALCHIP:
        break;
    case ICN_2038S:
        break;
    case MBI_5038:
        break;
    case SUM_2017T:
        break;
    case MBI_5124:
        break;
    case SUM_2017:
        break;
        //自解码芯片
    case SUM_2030:
          WriteFrequencyDoubling(1, 2, 11);
        break;
    case SUM_2030T:
          WriteFrequencyDoubling(1, 2, 11);
        break;
    case SUM_2032:
          WriteFrequencyDoubling(1, 2, 11);
        break;
    case SUM_2131:
          WriteFrequencyDoubling(1, 2, 11);
        break;
    case SUM_2033:
          WriteFrequencyDoubling(1, 2, 11);
        break;
    case MBI_5252:
        break;
    case MBI_5041B:
        break;
    case MBI_5041Q:
        break;
    case MBI_5042_5041:
        break;
    case MBI_5042B:
        break;
    case MBI_5043:
        break;
    case MBI_5151:
        break;
    case MBI_5047:
        break;
    case MBI_5152:
        break;
    case MBI_5153:
        break;
    case MBI_5155:
        break;
    case SUM_2035:
          WriteFrequencyDoubling(1, 2, 11);
        break;
    case SM_16259:
          WriteFrequencyDoubling(1, 2, 13);
        break;
    case MBI_5353:
        //WriteFrequencyDoubling5353();
        break;
    case SUM_6086:
        WriteFrequencyDoubling(1, 2, 11);
        break;
    case LS_9935:
        break;
    case ICN_2055_2069:
        break;
    case CFD_335A:
        WriteFrequencyDoubling(1, 2, 11);
        break;
    case SUM_2035NEW:
        break;
    case ICN_2153:
        break;
    case FM_6363:
        break;
    case FM_6565:
        break;
    case LS_9935B:
        break;
    case CFD_435A:
        WriteFrequencyDoubling(1, 2, 11);
        break;
    case CFD_555A:
        WriteFrequencyDoubling(1, 2, 12);
        break;
    case CFD_455A:
        WriteFrequencyDoubling(1, 2, 12);
        break;
    case DP_3246:
        break;
    case ICND_2138:
        break;
    case XM11202G:
        break;
    case XM10480G:
        break;
    default:
        break;

    }
}

void AdvancedSetting::on_spinBox_valueChanged(int arg1)
{
    ModulePara[0x2A] = (uchar)arg1;
}

void AdvancedSetting::on_spinBox_2_valueChanged(int arg1)
{
    ModulePara[0x2B] = (uchar)arg1;
}

void AdvancedSetting::on_spinBox_3_valueChanged(int arg1)
{
    ModulePara[0x2C] = (uchar)arg1;
}


void AdvancedSetting::on_spinBox_4_valueChanged(int arg1)
{
    ModulePara[0x2D] = (uchar)arg1;

    int VR = VisionRefresh();
      ui->lineEdit_8->setText(QString::number(VR));
}



void AdvancedSetting::on_spinBox_5_valueChanged(int arg1)
{
    ModulePara[0x36] = (uchar)arg1;
}






void AdvancedSetting::on_pushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);

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
            ModulePara[i] = (uchar)file[i];
            DataPara[i] = (uchar)file[i + 1024];
            ICPara[i] = (uchar)file[i + 2048];

        }
        LoadingPara();

        int VR = VisionRefresh();
        ui->lineEdit_8->setText(QString::number(VR));
        UniversalInterface::MessageBoxShow(tr("导入文件"),tr("文件导入成功"));
    }
    else
    {
        UniversalInterface::MessageBoxShow(tr("导入文件"),tr("文件长度不符"));
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
            file[i] = (uchar)ModulePara[i];
            file[i + 1024] = (uchar)DataPara[i];
            file[i + 2048] = (uchar)ICPara[i];
        }
        //fileName即是选择的文件名
        UniversalInterface::Writebin(fileName,file);
        UniversalInterface::MessageBoxShow(tr("导出文件"),tr("文件导出成功"));
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

    uchar GclkValue = (uchar)ModulePara[0x1B];
    uchar TXDValue = (uchar)ModulePara[0x18];

    //倍频
    if (ui->comboBox_7->currentText().toUInt() != 0)
    {
        FrequencyDoubling = 1024 / ui->comboBox_7->currentText().toUInt();
    }
    else
    {
        FrequencyDoubling = 1024;
    }

    //子场个数
    //int SubField = ICPara[5];
    //扫描数
    uchar Scannum = (uchar)ModulePara[0x25];

    //扫描方向芯片数
    //int Chipnum =

    //低灰补偿
    uchar Lowgrayadd = (uchar)ICPara[0x83];
    //首行补偿
    uchar Firstadd = (uchar)ICPara[0x82];


    //换行延时

    uchar NewlineDelay = (uchar)ModulePara[0x2D];

    if (GclkValue == 0 || ReadFieldFrequency == 0 || Scannum == 0)
    {
        return 0;
    }

    //视觉刷新率计算
    int icNumber = (uchar)ModulePara[0x13] /*+ (uchar)ModulePara[0x14] * 256*/;
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
                if ((ICPara[0x10C] & 0x04) == 0x04)
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
            if ((ICPara[0x10C] & 0x04) == 0x04)
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
                beipin = 256 / chu;
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
        ModulePara[0x5C] = (uchar)ModulePara[0x5C] | 0x20;
    }
    else
    {
        ModulePara[0x5C] = (uchar)ModulePara[0x5C] & 0xDF;
    }


    //发送参数
    bool result = UniversalInterface::SendALLPara();

    if (result)
    {
        UniversalInterface::MessageBoxShow(tr("设置"),tr("设置成功"));
    }
    else{
         UniversalInterface::MessageBoxShow(tr("设置"),tr("设置失败"));
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
        ModulePara[0x66] = (uchar)ModulePara[0x66] | 0x80;
    }
    else
    {
        ModulePara[0x66] = (uchar)ModulePara[0x66] & 0x7F;
    }

    //发送参数
    bool result = UniversalInterface::SendALLPara();

    if (result)
    {
        UniversalInterface::MessageBoxShow(tr("设置"),tr("设置成功"));
    }
    else{
         UniversalInterface::MessageBoxShow(tr("设置"),tr("设置失败"));
    }
     this->setCursor(Qt::ArrowCursor);
}


void AdvancedSetting::on_rgbChangeBtn_clicked()
{
    RGBchange *rgbchange = new RGBchange(this);
    rgbchange->show();
}

void AdvancedSetting::on_dataGroupBtn_clicked()
{
    DataGroup *datagroup = new DataGroup(this);
    datagroup->show();
}







void AdvancedSetting::CreateAction()
{
    ui->toolButton->setToolButtonStyle( Qt::ToolButtonTextUnderIcon);
    ui->toolButton->setPopupMode(QToolButton::InstantPopup);
    // 创建QMenu
    QMenu *menu = new QMenu();
    //创建QAction
    QAction *ICconfig = new QAction(tr("驱动芯片设置"),AdvancedSetting::ui->toolButton);
    menu->addAction(ICconfig);
    connect(ICconfig,SIGNAL(triggered()),this,SLOT(ICconfigShow()));

    QAction *CurrentConfig = new QAction(tr("电流增益设置"),AdvancedSetting::ui->toolButton);
    menu->addAction(CurrentConfig);
    connect(CurrentConfig,SIGNAL(triggered()),this,SLOT(CurrentConfigShow()));

    QAction *MOSConfig = new QAction(tr("行管设置"),AdvancedSetting::ui->toolButton);
    menu->addAction(MOSConfig);
    connect(MOSConfig,SIGNAL(triggered()),this,SLOT(MOSConfigShow()));

    QAction *FLASHConfig = new QAction(tr("FLASH设置"),AdvancedSetting::ui->toolButton);
    menu->addAction(FLASHConfig);
    connect(FLASHConfig,SIGNAL(triggered()),this,SLOT(FLASHConfig()));

    QAction *GrayFineProcessing = new QAction(tr("灰度精细处理"),AdvancedSetting::ui->toolButton);
    menu->addAction(GrayFineProcessing);
    connect(GrayFineProcessing,SIGNAL(triggered()),this,SLOT(GrayFineProcessingShow()));

    QAction *Scan = new QAction(tr("扫描表设置"),AdvancedSetting::ui->toolButton);
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

    uint16_t index = (unsigned char)ModulePara[0x13]/* + (unsigned char)ModulePara[0x14] * 256*/;

    switch (index)
    {
    case CONVENTSIONALCHIP:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case ICN_2038S:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5038:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case SUM_2017T:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5124:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case SUM_2017:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case SUM_2030:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case SUM_2030T:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case SUM_2032:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case SUM_2131:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case SUM_2033:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5252:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5041B:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5041Q:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5042_5041:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5042B:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5043:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5151:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5047:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5152:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5153:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5155:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case SUM_2035:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case SM_16259:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case MBI_5353:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case SUM_6086:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case LS_9935:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case ICN_2055_2069:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case CFD_335A:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case SUM_2035NEW:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case ICN_2153:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case FM_6363:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case FM_6565:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case LS_9935B:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case CFD_435A:
    {
        ICCFD435ASetting *iccfd435a = new ICCFD435ASetting(this);
        iccfd435a->show();
        break;
    }
    case CFD_555A:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case CFD_455A:
    {
        ICCFD455ASetting *iccfd455a = new ICCFD455ASetting(this);
        iccfd455a->show();
        break;
    }
    case DP_3246:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case ICND_2138:
    {
        ICAdvancedSetting *icadvanced = new ICAdvancedSetting(this);
        icadvanced->show();
        break;
    }
    case XM11202G:
    {
        ICXM11202GSetting *icxm11202 = new ICXM11202GSetting(this);
        icxm11202->show();
        break;
    }
    case XM10480G:
    {
        ICXM10480GSetting *icxm10480g = new ICXM10480GSetting(this);
        icxm10480g->show();
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
    CurrentGain *currentgain = new CurrentGain(this);
    currentgain->show();
}
void AdvancedSetting::MOSConfigShow()
{
    switch ((uchar)ModulePara[0x12])
    {
    case 0:
        break;
    case 1:
        break;
    case 2:
    {
        MOS5957config *mos5957 = new MOS5957config(this);
        mos5957->show();
        break;
    }
    case 3:
    {
        MOS5366config *mos5366 = new MOS5366config(this);
        mos5366->show();
        break;
    }
    case 4:
    {
        MOSICND2018config *mosicnd2018 = new MOSICND2018config(this);
        mosicnd2018->show();
        break;
    }
    case 5:
    {
        MOSC82018config *mosc82018 = new MOSC82018config(this);
        mosc82018->show();
        break;
    }
    case 6:
    {
        MOSCFD2138config *moscfd2138 = new MOSCFD2138config(this);
        moscfd2138->show();
        break;
    }
    default:
        break;
    }
}
void AdvancedSetting::FLASHConfig()
{
    FLASHsetting *flashsetting = new FLASHsetting(this);
    flashsetting->show();
}
void AdvancedSetting::GrayFineProcessingShow()
{
    GrayFineProcessing *grayfinepro = new GrayFineProcessing(this);
    grayfinepro->show();
}
void AdvancedSetting::ScanShow()
{
    Scanparamater *scanpara = new Scanparamater(this);
    scanpara->show();
}



void AdvancedSetting::on_OtherpushButton_clicked()
{
    AdvancedOtherPara *advancedother = new AdvancedOtherPara(this);
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
        UniversalInterface::MessageBoxShow(tr("回读"),tr("回读成功"));
    }
    else{
         UniversalInterface::MessageBoxShow(tr("回读"),tr("回读失败"));
    }

}

void AdvancedSetting::on_pushButton_2_clicked()
{


    AdvancedCustom *custom = new AdvancedCustom(this);

    //UniversalInterface::showRaise(custom);
     //Core::ICore::showCenter(custom);
    custom->show();
}

void AdvancedSetting::on_SavepushButton_clicked()
{
    LAPI::EResult ret = LAPI::WriteSaveRCParam(0xFF, 0xFF, true);
    if (ret == LAPI::EResult::ER_INTECTRL_Success)
    {
        UniversalInterface::MessageBoxShow(tr("保存"),tr("保存成功"));
    }
    else
    {
        UniversalInterface::MessageBoxShow(tr("保存"),tr("保存成功"));
    }
}



void AdvancedSetting::on_ButtonColorGamdat_clicked()
{
    ColorGamut *colorgamut = new ColorGamut(this);
    colorgamut->show();
}
void AdvancedSetting::WriteFrequencyDoubling(int Regnum, int ByteCount, int StartByte)
{
    int i = 0;
    QByteArray Regold;
    Regold.resize(6);
    QByteArray Regnew;
    Regnew.resize(6);
    int REGold[3];
    int REGnew[3];

    for (i = 0; i < Regold.length(); i++)
    {
        Regold[i] = (uchar)ICPara[0x100 + i + (Regnum - 1) * 6];
    }

    for (i = 0; i < 3; i++)
    {
        REGold[i] = (uchar)Regold[i * 2] + Regold[i * 2 + 1] * 256;
    }

    REGnew[0] = (REGold[0] & ~((int)(pow(2, ByteCount) - 1) << StartByte)) | (ModulePara[0x29] << StartByte);
    REGnew[1] = (REGold[1] & ~((int)(pow(2, ByteCount) - 1) << StartByte)) | (ModulePara[0x29] << StartByte);
    REGnew[2] = (REGold[2] & ~((int)(pow(2, ByteCount) - 1) << StartByte)) | (ModulePara[0x29] << StartByte);

    for (i = 0; i < Regnew.length(); i += 2)
    {
        Regnew[i] = (uchar)(REGnew[i / 2] % 256);
        Regnew[i + 1] = (uchar)(REGnew[i / 2] / 256);
    }

    for (i = 0; i < Regnew.length(); i++)
    {
        ICPara[0x100 + i + (Regnum - 1) * 6] = (uchar)Regnew[i];
    }

}
