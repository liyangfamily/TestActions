#include "icadvancedsetting.h"
#include "ui_icadvancedsetting.h"
#include "advancedsetting.h"
#include <QDebug>

ICAdvancedSetting::ICAdvancedSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ICAdvancedSetting)
{
    ui->setupUi(this);

    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag                  |= Qt::WindowMinimizeButtonHint;
    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    setWindowFlags(windowFlag);

    LoadForm();
    Showic();


}
#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif
ICAdvancedSetting::~ICAdvancedSetting()
{
    delete ui;
}
void ICAdvancedSetting::SetspinBox()
{
    //Reg1
    spinbox[0] = ui->Reg1RLowspinBox;
    spinbox[1] = ui->Reg1RHighspinBox;
    spinbox[2] = ui->Reg1GLowspinBox;
    spinbox[3] = ui->Reg1GHighspinBox;
    spinbox[4] = ui->Reg1BLowspinBox;
    spinbox[5] = ui->Reg1BHighspinBox;

    //Reg2
    spinbox[6] = ui->Reg2RLowspinBox;
    spinbox[7] = ui->Reg2RHighspinBox;
    spinbox[8] = ui->Reg2GLowspinBox;
    spinbox[9] = ui->Reg2GHighspinBox;
    spinbox[10] = ui->Reg2BLowspinBox;
    spinbox[11] = ui->Reg2BHighspinBox;

    //Reg3
    spinbox[12] = ui->Reg3RLowspinBox;
    spinbox[13] = ui->Reg3RHighspinBox;
    spinbox[14] = ui->Reg3GLowspinBox;
    spinbox[15] = ui->Reg3GHighspinBox;
    spinbox[16] = ui->Reg3BLowspinBox;
    spinbox[17] = ui->Reg3BHighspinBox;

    //Reg4
    spinbox[18] = ui->Reg4RLowspinBox;
    spinbox[19] = ui->Reg4RHighspinBox;
    spinbox[20] = ui->Reg4GLowspinBox;
    spinbox[21] = ui->Reg4GHighspinBox;
    spinbox[22] = ui->Reg4BLowspinBox;
    spinbox[23] = ui->Reg4BHighspinBox;

    //Reg5
    spinbox[24] = ui->Reg5RLowspinBox;
    spinbox[25] = ui->Reg5RHighspinBox;
    spinbox[26] = ui->Reg5GLowspinBox;
    spinbox[27] = ui->Reg5GHighspinBox;
    spinbox[28] = ui->Reg5BLowspinBox;
    spinbox[29] = ui->Reg5BHighspinBox;

    //Reg6
    spinbox[30] = ui->Reg6RLowspinBox;
    spinbox[31] = ui->Reg6RHighspinBox;
    spinbox[32] = ui->Reg6GLowspinBox;
    spinbox[33] = ui->Reg6GHighspinBox;
    spinbox[34] = ui->Reg6BLowspinBox;
    spinbox[35] = ui->Reg6BHighspinBox;

    //Reg7
    spinbox[36] = ui->Reg7RLowspinBox;
    spinbox[37] = ui->Reg7RHighspinBox;
    spinbox[38] = ui->Reg7GLowspinBox;
    spinbox[39] = ui->Reg7GHighspinBox;
    spinbox[40] = ui->Reg7BLowspinBox;
    spinbox[41] = ui->Reg7BHighspinBox;

    //Reg8
    spinbox[42] = ui->Reg8RLowspinBox;
    spinbox[43] = ui->Reg8RHighspinBox;
    spinbox[44] = ui->Reg8GLowspinBox;
    spinbox[45] = ui->Reg8GHighspinBox;
    spinbox[46] = ui->Reg8BLowspinBox;
    spinbox[47] = ui->Reg8BHighspinBox;


}

void ICAdvancedSetting::Showic()
{
    uchar index = (uchar)ModulePara[0x13]/* + (uchar)ModulePara[0x14] * 256*/;

    switch (index)
    {
    case CONVENTSIONALCHIP:
        ui->IClineEdit->setText(tr("常规芯片"));
        ShowCount(0);
        break;
    case ICN_2038S:
        ui->IClineEdit->setText("ICN-2038S");
        ShowCount(2);
        break;
    case MBI_5038:
        ui->IClineEdit->setText("MBI-5038");
        ShowCount(1);
        break;
    case SUM_2017T:
        ui->IClineEdit->setText("SUM-2017T");
        ShowCount(1);
        break;
    case MBI_5124:
        ui->IClineEdit->setText("MBI-5124");
        ShowCount(1);
        break;
    case SUM_2017:
        ui->IClineEdit->setText("SUM-2017");
        ShowCount(1);
        break;
    case SUM_2030 :
        ui->IClineEdit->setText("SUM-2030");
        ShowCount(2);
        break;
    case SUM_2030T:
        ui->IClineEdit->setText("SUM-2030T");
        ShowCount(2);
        break;
    case SUM_2032:
        ui->IClineEdit->setText("SUM-2032");
        ShowCount(2);
        break;
    case SUM_2131:
        ui->IClineEdit->setText("SUM-2131");
        ShowCount(3);
        break;
    case SUM_2033:
        ui->IClineEdit->setText("SUM-2033");
        ShowCount(3);
        break;
    case MBI_5252:
        ui->IClineEdit->setText("MBI-5252");
        ShowCount(2);
        break;
    case MBI_5041B:
        ui->IClineEdit->setText("MBI-5041B");
        ShowCount(1);
        break;
    case MBI_5041Q:
        ui->IClineEdit->setText("MBI-5041Q");
        ShowCount(1);
        break;
    case MBI_5042_5041:
        ui->IClineEdit->setText("MBI-5042/5041");
        ShowCount(1);
        break;
    case MBI_5042B:
        ui->IClineEdit->setText("MBI-5042B");
        ShowCount(1);
        break;
    case MBI_5043:
        ui->IClineEdit->setText("MBI-5043");
        ShowCount(1);
        break;
    case MBI_5151:
        ui->IClineEdit->setText("MBI-5151");
        ShowCount(2);
        break;
    case MBI_5047:
        ui->IClineEdit->setText("MBI-5047");
          ShowCount(1);
        break;
    case MBI_5152:
        ui->IClineEdit->setText("MBI-5152");
         ShowCount(2);
        break;
    case MBI_5153:
        ui->IClineEdit->setText("MBI-5153");
         ShowCount(3);
        break;
    case MBI_5155:
        ui->IClineEdit->setText("MBI-5155");
         ShowCount(2);
        break;
    case SUM_2035:
        ui->IClineEdit->setText("SUM-2035");
         ShowCount(4);
        break;
    case SM_16259:
        ui->IClineEdit->setText("SM-16259");
         ShowCount(3);
        break;
    case MBI_5353:
        ui->IClineEdit->setText("MBI-5353");
        ShowCount(4);
        break;
    case SUM_6086:
        ui->IClineEdit->setText("SUM-6086");
        ShowCount(4);
        break;
    case LS_9935:
        ui->IClineEdit->setText("LS-9935");
        break;
    case ICN_2055_2069:
        ui->IClineEdit->setText("ICN-2055/2069");
        break;
    case CFD_335A:
        ui->IClineEdit->setText("CFD-335A");
        ShowCount(4);
        break;
    case SUM_2035NEW:
        ui->IClineEdit->setText("SUM-2035NEW");
        break;
    case ICN_2153:
        ui->IClineEdit->setText("ICN-2153");
        ShowCount(4);
        break;
    case FM_6363:
        ui->IClineEdit->setText("FM-6363");
        break;
    case FM_6565:
        ui->IClineEdit->setText("FM-6565");
        break;
    case LS_9935B:
        ui->IClineEdit->setText("LS-9935B");
        break;
    case CFD_435A:
        ui->IClineEdit->setText("CFD-435A");
        ShowCount(4);
        break;
    case CFD_555A:
        ui->IClineEdit->setText("CFD-555A");
        ShowCount(8);
        break;
    case CFD_455A:
        ui->IClineEdit->setText("CFD-455A");
        ShowCount(4);
        break;
    default:
        break;
    }
}

void ICAdvancedSetting::LoadForm()
{
     SetspinBox();
    int i = 0;
    for (i=0;i<48;i++)
    {
        spinbox[i]->setValue((uchar)ICPara[0x100 + i]);
    }


}

void ICAdvancedSetting::ShowCount(int Num)
{
    if (Num > 8)
    {
        return;
    }
    int i=0;
//    for (i=0;i<Num*6;i++)
//    {
//        spinbox[i]->setEnabled(true);
//    }
    for (i=Num*6;i<8*6;i++)
    {
        spinbox[i]->setEnabled(false);
        //qDebug()<< "-----------"<<i;
    }
}

void ICAdvancedSetting::on_pushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);
    int i = 0;
    for (i=0;i<48;i++)
    {
        ICPara[0x100 + i] = (uchar)spinbox[i]->value();
    }
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
