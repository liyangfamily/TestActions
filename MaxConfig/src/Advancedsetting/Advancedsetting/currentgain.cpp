#include "currentgain.h"
#include "ui_currentgain.h"
#include "advancedsetting.h"
#include <QDebug>
#include <math.h>

CurrentGain::CurrentGain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentGain)
{
    ui->setupUi(this);


    LoadForm();
}

CurrentGain::~CurrentGain()
{
    delete ui;
}

void CurrentGain::LoadForm()
{
    Showic();

}

void CurrentGain::ShowScrool(bool type)
{
    ui->CurrentGainRSlider->setEnabled(type);
    ui->CurrentGainGSlider->setEnabled(type);
    ui->CurrentGainBSlider->setEnabled(type);
}


void CurrentGain::Showic()
{
    unsigned char index = (unsigned char)ModulePara[0x13] + (unsigned char)ModulePara[0x14] * 256;



    switch (index)
    {
    case CONVENTSIONALCHIP:
        ui->lineEdit->setText(QStringLiteral("常规芯片"));
        ShowScrool(false);
        break;
    case ICN_2038S:
        ui->lineEdit->setText("ICN-2038S");
        ShowScrool(true);
        initMetroTrackBar(1, 4, 7);
        if (ui->CurrentGainRSlider->value() < 7)
        {
            double Rvalue = (ui->CurrentGainRSlider->value() * 0.03125 + 0.25) * 100;
            ui->ValueRlabel->setText(QString::number(Rvalue,'f',2) + "%");
        }
        else
        {
            double Rvalue = ((ui->CurrentGainRSlider->value() - 7) * 0.0625 + 0.5) * 100;
            ui->ValueRlabel->setText(QString::number(Rvalue,'f',2) + "%");
        }
        if (ui->CurrentGainGSlider->value() < 7)
        {
            double Gvalue = (ui->CurrentGainGSlider->value() * 0.03125 + 0.25) * 100;
            ui->ValueGlabel->setText(QString::number(Gvalue,'f',2) + "%");
        }
        else
        {
            double Gvalue = ((ui->CurrentGainGSlider->value() - 7) * 0.0625 + 0.5) * 100;
            ui->ValueGlabel->setText(QString::number(Gvalue,'f',2) + "%");
        }
        if (ui->CurrentGainBSlider->value() < 7)
        {
            double Bvalue = (ui->CurrentGainBSlider->value() * 0.03125 + 0.25) * 100;
            ui->ValueBlabel->setText(QString::number(Bvalue,'f',2) + "%");
        }
        else
        {
            double Bvalue = ((ui->CurrentGainBSlider->value() - 7) * 0.0625 + 0.5) * 100;
            ui->ValueBlabel->setText(QString::number(Bvalue,'f',2) + "%");
        }

        break;
    case MBI_5038:
        ui->lineEdit->setText("MBI-5038");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case SUM_2017T:
        ui->lineEdit->setText("SUM-2017T");
        ShowScrool(true);
        initMetroTrackBar(1, 5, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case MBI_5124:
        ui->lineEdit->setText("MBI-5124");
         ShowScrool(false);
        break;
    case SUM_2017:
        ui->lineEdit->setText("SUM-2017");
          ShowScrool(false);
        break;
    case SUM_2030 :
        ui->lineEdit->setText("SUM-2030");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case SUM_2030T:
        ui->lineEdit->setText("SUM-2030T");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case SUM_2032:
        ui->lineEdit->setText("SUM-2032");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case SUM_2131:
        ui->lineEdit->setText("SUM-2131");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case SUM_2033:
        ui->lineEdit->setText("SUM-2033");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case MBI_5252:
        ui->lineEdit->setText("MBI-5252");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case MBI_5041B:
        ui->lineEdit->setText("MBI-5041B");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 4);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case MBI_5041Q:
        ui->lineEdit->setText("MBI-5041Q");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 4);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case MBI_5042_5041:
        ui->lineEdit->setText("MBI-5042/5041");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 4);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case MBI_5042B:
        ui->lineEdit->setText("MBI-5042B");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 4);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case MBI_5043:
        ui->lineEdit->setText("MBI-5043");
        ShowScrool(true);
        init5043MetroTrackBar(6, 4);
        if (ui->CurrentGainRSlider->value() <= 32)
        {
            ui->ValueRlabel->setText(QString::number(((ui->CurrentGainRSlider->value() * 3 + 32) * 100.0 / 256),'f',2) + "%");
        }
        else
        {
            ui->ValueRlabel->setText(QString::number((((ui->CurrentGainRSlider->value() - 32) * 3 + 33) * 100.0 / 65),'f',2) + "%");
        }
        if (ui->CurrentGainGSlider->value() <= 32)
        {
            ui->ValueGlabel->setText(QString::number(((ui->CurrentGainGSlider->value() * 3 + 32) * 100.0 / 256),'f',2) + "%");
        }
        else
        {
            ui->ValueGlabel->setText(QString::number((((ui->CurrentGainGSlider->value() - 32) * 3 + 33) * 100.0 / 65),'f',2) + "%");
        }
        if (ui->CurrentGainBSlider->value() <= 32)
        {
            ui->ValueBlabel->setText(QString::number(((ui->CurrentGainBSlider->value() * 3 + 32) * 100.0 / 256),'f',2) + "%");
        }
        else
        {
            ui->ValueBlabel->setText(QString::number((((ui->CurrentGainBSlider->value() - 32) * 3 + 33) * 100.0 / 65),'f',2) + "%");
        }
        break;
    case MBI_5151:
        ui->lineEdit->setText("MBI-5151");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case MBI_5047:
        ui->lineEdit->setText("MBI-5047");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case MBI_5152:
        ui->lineEdit->setText("MBI-5152");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case MBI_5153:
        ui->lineEdit->setText("MBI-5153");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case MBI_5155:
        ui->lineEdit->setText("MBI-5155");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number(ui->CurrentGainRSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number(ui->CurrentGainGSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number(ui->CurrentGainBSlider->value() * 100.0 / MaxValue,'f',2) + "%");
        break;
    case SUM_2035:
        ui->lineEdit->setText("SUM-2035");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number((ui->CurrentGainRSlider->value() + 21) * 100.0 / 84.0,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number((ui->CurrentGainGSlider->value() + 21) * 100.0 / 84.0,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number((ui->CurrentGainBSlider->value() + 21) * 100.0 / 84.0,'f',2) + "%");
        break;
    case SM_16259:
        ui->lineEdit->setText("SM-16259");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number((ui->CurrentGainRSlider->value() + 1) * 100.0 / 64.0,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number((ui->CurrentGainGSlider->value() + 1) * 100.0 / 64.0,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number((ui->CurrentGainBSlider->value() + 1) * 100.0 / 64.0,'f',2) + "%");
        break;
    case MBI_5353:
        ui->lineEdit->setText("MBI-5353");
        ShowScrool(true);
        init5353MetroTrackBar(7, 2);
        ui->ValueRlabel->setText(QString::number((ui->CurrentGainRSlider->value() + 1) * 100.0 / 128.0,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number((ui->CurrentGainGSlider->value() + 1) * 100.0 / 128.0,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number((ui->CurrentGainBSlider->value() + 1) * 100.0 / 128.0,'f',2) + "%");
        break;
    case SUM_6086:
        ui->lineEdit->setText("SUM-6086");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number((ui->CurrentGainRSlider->value() + 1) * 100.0 / 64.0,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number((ui->CurrentGainGSlider->value() + 1) * 100.0 / 64.0,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number((ui->CurrentGainBSlider->value() + 1) * 100.0 / 64.0,'f',2) + "%");
        break;
    case LS_9935:
        ui->lineEdit->setText("LS-9935");
        break;
    case ICN_2055_2069:
        ui->lineEdit->setText("ICN-2055/2069");
        break;
    case CFD_335A:
        ui->lineEdit->setText("CFD-335A");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number((ui->CurrentGainRSlider->value() / 2.0 + 8.5) * 100.0 / 40.0,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number((ui->CurrentGainGSlider->value() / 2.0 + 8.5) * 100.0 / 40.0,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number((ui->CurrentGainBSlider->value() / 2.0 + 8.5) * 100.0 / 40.0,'f',2) + "%");
        break;
    case SUM_2035NEW:
        ui->lineEdit->setText("SUM-2035NEW");
        break;
    case ICN_2153:
        ui->lineEdit->setText("ICN-2153");
        break;
    case FM_6363:
        ui->lineEdit->setText("FM-6363");
        break;
    case FM_6565:
        ui->lineEdit->setText("FM-6565");
        break;
    case LS_9935B:
        ui->lineEdit->setText("LS-9935B");
        break;
    case CFD_435A:
        ui->lineEdit->setText("CFD-435A");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number((ui->CurrentGainRSlider->value() / 2.0 + 8.5) * 100.0 / 40.0,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number((ui->CurrentGainGSlider->value() / 2.0 + 8.5) * 100.0 / 40.0,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number((ui->CurrentGainBSlider->value() / 2.0 + 8.5) * 100.0 / 40.0,'f',2) + "%");
        break;
    case CFD_555A:
        ui->lineEdit->setText("CFD-555A");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number((ui->CurrentGainRSlider->value() / 2.0 + 8.5) * 100.0 / 40.0,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number((ui->CurrentGainGSlider->value() / 2.0 + 8.5) * 100.0 / 40.0,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number((ui->CurrentGainBSlider->value() / 2.0 + 8.5) * 100.0 / 40.0,'f',2) + "%");
        break;
    case CFD_455A:
        ui->lineEdit->setText("CFD-455A");
        ShowScrool(true);
        initMetroTrackBar(1, 6, 0);
        ui->ValueRlabel->setText(QString::number((ui->CurrentGainRSlider->value() / 2.0 + 8.5) * 100.0 / 40.0,'f',2) + "%");
        ui->ValueGlabel->setText(QString::number((ui->CurrentGainGSlider->value() / 2.0 + 8.5) * 100.0 / 40.0,'f',2) + "%");
        ui->ValueBlabel->setText(QString::number((ui->CurrentGainBSlider->value() / 2.0 + 8.5) * 100.0 / 40.0,'f',2) + "%");
        break;
    case DP_3246:
        break;
    default:
        break;

    }


}


void CurrentGain::initMetroTrackBar(int Regnum, int ByteCount, int StartByte)
{
    int i = 0;
    QByteArray Regold;
    Regold.resize(6);
    QByteArray Regnew;
    Regnew.resize(6);
    int REGold[3];

    ui->CurrentGainRSlider->setMaximum((pow(2,ByteCount) - 1));
    ui->CurrentGainGSlider->setMaximum((pow(2,ByteCount) - 1));
    ui->CurrentGainBSlider->setMaximum((pow(2,ByteCount) - 1));
    MaxValue = pow(2,ByteCount) - 1;


    for (i = 0; i < Regold.length(); i++)
    {
        Regold[i] = ICPara[0x100 + i + (Regnum - 1) * 6];
    }

    for (i = 0; i < 3; i++)
    {
        REGold[i] = Regold[i * 2] + Regold[i * 2 + 1] * 256;
    }

    ui->CurrentGainRSlider->setValue((REGold[0] >> StartByte) & ((int)(pow(2,ByteCount) - 1)));
    ui->CurrentGainGSlider->setValue((REGold[1] >> StartByte) & ((int)(pow(2,ByteCount) - 1)));
    ui->CurrentGainBSlider->setValue((REGold[2] >> StartByte) & ((int)(pow(2,ByteCount) - 1)));


}

void CurrentGain::init5043MetroTrackBar(int ByteCount, int StartByte)
{
    QByteArray Regold;
    Regold.resize(6);
    QByteArray Regnew;
    Regnew.resize(6);
    int REGold[3];

    ui->CurrentGainRSlider->setMaximum((pow(2,ByteCount) - 1));
    ui->CurrentGainGSlider->setMaximum((pow(2,ByteCount) - 1));
    ui->CurrentGainBSlider->setMaximum((pow(2,ByteCount) - 1));
    MaxValue = pow(2,ByteCount) - 1;

    REGold[0] = ICPara[0x100] + ICPara[0x101] * 256;
    REGold[1] = ICPara[0x102] + ICPara[0x103] * 256;
    REGold[2] = ICPara[0x104] + ICPara[0x105] * 256;

    ui->CurrentGainRSlider->setValue((REGold[0] >> StartByte) & ((int)(pow(2,ByteCount) - 1)));
    ui->CurrentGainGSlider->setValue((REGold[1] >> StartByte) & ((int)(pow(2,ByteCount) - 1)));
    ui->CurrentGainBSlider->setValue((REGold[2] >> StartByte) & ((int)(pow(2,ByteCount) - 1)));

}

void CurrentGain::init5353MetroTrackBar(int ByteCount, int StartByte)
{
    QByteArray Regold;
    Regold.resize(6);
    QByteArray Regnew;
    Regnew.resize(6);
    int REGold[3];

    ui->CurrentGainRSlider->setMaximum((pow(2,ByteCount) - 1));
    ui->CurrentGainGSlider->setMaximum((pow(2,ByteCount) - 1));
    ui->CurrentGainBSlider->setMaximum((pow(2,ByteCount) - 1));
    MaxValue = pow(2,ByteCount) - 1;

    REGold[0] = ICPara[0x106] + ICPara[0x107] * 256;
    REGold[1] = ICPara[0x108] + ICPara[0x109] * 256;
    REGold[2] = ICPara[0x10A] + ICPara[0x10B] * 256;

    ui->CurrentGainRSlider->setValue((REGold[0] >> StartByte) & ((int)(pow(2,ByteCount) - 1)));
    ui->CurrentGainGSlider->setValue((REGold[1] >> StartByte) & ((int)(pow(2,ByteCount) - 1)));
    ui->CurrentGainBSlider->setValue((REGold[2] >> StartByte) & ((int)(pow(2,ByteCount) - 1)));

}


































QString CurrentGain::getpercent(int value)
{
    unsigned char index = (unsigned char)ModulePara[19] + (unsigned char)ModulePara[20] * 256;

    QString percent = "";

    switch (index)
    {
    case CONVENTSIONALCHIP:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case ICN_2038S:

        if (value < 7)
        {
            percent = QString::number((value * 0.03125 + 0.25) * 100,'f',2);
        }
        else
        {
            percent = QString::number(((value - 7) * 0.0625 + 0.5) * 100,'f',2);
        }
        break;
    case MBI_5038:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case SUM_2017T:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case MBI_5124:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case SUM_2017:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case SUM_2030 :
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case SUM_2030T:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case SUM_2032:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case SUM_2131:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case SUM_2033:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case MBI_5252:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case MBI_5041B:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case MBI_5041Q:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case MBI_5042_5041:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case MBI_5042B:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case MBI_5043:
        //percent = (((value + 4.2) * 100.0 / 67.2) * 2).ToString("0.00");

        if (value <= 32)
        {
            percent = QString::number((value * 3 + 32) * 100.0 / 256,'f',2);
        }
        else
        {
            percent = QString::number(((value - 32) * 3 + 33) * 100.0 / 65,'f',2);
        }
        break;
    case MBI_5151:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case MBI_5047:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case MBI_5152:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case MBI_5153:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case MBI_5155:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case SUM_2035:
        percent = QString::number((value + 21) * 100.0 / 84.0,'f',2);        // 21*100/84为最小百分比，63+21=84 63级调节
        break;
    case SM_16259:
        percent = QString::number((value + 1) * 100.0 / 64.0,'f',2);
        break;
    case MBI_5353:
        percent = QString::number((value + 1) * 100.0 / 128.0,'f',2);
        break;
    case SUM_6086:
        percent = QString::number(value * 100.0 / MaxValue,'f',2);
        break;
    case LS_9935:
        break;
    case ICN_2055_2069:
        break;
    case CFD_335A:
        percent = QString::number((value / 2.0 + 8.5) * 100.0 / 40.0,'f',2);
        break;
    case SUM_2035NEW:
        break;
    case ICN_2153:
        //percent = ((value + 54.86) * 100.0 / (384 + 54.86)).ToString("0.00");
        break;
    case FM_6363:
        break;
    case FM_6565:
        break;
    case LS_9935B:
        break;
    case CFD_435A:
        percent =  QString::number((value / 2.0 + 8.5) * 100.0 / 40.0,'f',2);
        break;
    case CFD_555A:
        percent =  QString::number((value / 2.0 + 8.5) * 100.0 / 40.0,'f',2);
        break;
    case CFD_455A:
        percent =  QString::number((value / 2.0 + 8.5) * 100.0 / 40.0,'f',2);
        break;
    default:
        break;

    }

    return percent;
}


void CurrentGain::on_CurrentGainRSlider_valueChanged(int value)
{
    ui->ValueRlabel->setText(getpercent(value) + "%");
    if (ui->SynccheckBox->isChecked())
    {
        ui->CurrentGainGSlider->setValue(value);
        ui->CurrentGainBSlider->setValue(value);
    }
}

void CurrentGain::on_CurrentGainGSlider_valueChanged(int value)
{
    ui->ValueGlabel->setText(getpercent(value) + "%");
    if (ui->SynccheckBox->isChecked())
    {
        ui->CurrentGainRSlider->setValue(value);
        ui->CurrentGainBSlider->setValue(value);
    }
}

void CurrentGain::on_CurrentGainBSlider_valueChanged(int value)
{
    ui->ValueBlabel->setText(getpercent(value) + "%");
    if (ui->SynccheckBox->isChecked())
    {
        ui->CurrentGainRSlider->setValue(value);
        ui->CurrentGainGSlider->setValue(value);
    }
}







void CurrentGain::on_SettingBtn_clicked()
{
     this->setCursor(Qt::WaitCursor);
    if (!ui->CurrentGainRSlider->isEnabled() || !ui->CurrentGainGSlider->isEnabled() || !ui->CurrentGainBSlider->isEnabled())
    {
        return;
    }

    unsigned char index = (unsigned char)ModulePara[19] + (unsigned char)ModulePara[20] * 256;

    QString percent = "";

    switch (index)
    {
    case CONVENTSIONALCHIP:
        break;
    case ICN_2038S:
        WriteCurrent(1, 4, 7);
        break;
    case MBI_5038:
        WriteCurrent(1, 6, 0);
        break;
    case SUM_2017T:
        WriteCurrent(1, 5, 0);
        break;
    case MBI_5124:
        break;
    case SUM_2017:
        break;
    case SUM_2030 :
        WriteCurrent(1, 6, 0);
        break;
    case SUM_2030T:
        break;
    case SUM_2032:
        WriteCurrent(1, 6, 0);
        break;
    case SUM_2131:
        WriteCurrent(1, 6, 0);
        break;
    case SUM_2033:
        WriteCurrent(1, 6, 0);
        break;
    case MBI_5252:
        WriteCurrent(1, 6, 0);
        break;
    case MBI_5041B:
        break;
    case MBI_5041Q:
        break;
    case MBI_5042_5041:
        WriteCurrent(1, 6, 4);
        break;
    case MBI_5042B:
        break;
    case MBI_5043:
        Write5043Current(6, 4);
        break;
    case MBI_5151:
        WriteCurrent(1, 6, 0);
        break;
    case MBI_5047:
        break;
    case MBI_5152:
        WriteCurrent(1, 6, 0);
        break;
    case MBI_5153:
        WriteCurrent(1, 6, 0);
        break;
    case MBI_5155:
        WriteCurrent(1, 6, 0);
        break;
    case SUM_2035:
        WriteCurrent(1, 6, 0);
        break;
    case SM_16259:
        WriteCurrent(1, 6, 0);
        break;
    case MBI_5353:
        Write5353Current(7, 2);
        break;
    case SUM_6086:
        WriteCurrent(1, 6, 0);
        break;
    case LS_9935:
        break;
    case ICN_2055_2069:
        break;
    case CFD_335A:
        WriteCurrent(1, 6, 0);
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
        WriteCurrent(1, 6, 0);
        break;
    case CFD_555A:
        WriteCurrent(1, 6, 0);
        break;
    case CFD_455A:
        WriteCurrent(1, 6, 0);
        break;
    default:
        break;

    }


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

void CurrentGain::WriteCurrent(int Regnum,int ByteCount, int StartByte)
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
        Regold[i] = ICPara[0x100 + i + (Regnum - 1) * 6];
    }

    for (i = 0; i < 3; i++)
    {
        REGold[i] = Regold[i * 2] + Regold[i * 2 + 1] * 256;
    }

    REGnew[0] = (REGold[0] & ~((int)(pow(2,ByteCount) - 1) << StartByte)) | (ui->CurrentGainRSlider->value() << StartByte);
    REGnew[1] = (REGold[1] & ~((int)(pow(2,ByteCount) - 1) << StartByte)) | (ui->CurrentGainGSlider->value() << StartByte);
    REGnew[2] = (REGold[2] & ~((int)(pow(2,ByteCount) - 1) << StartByte)) | (ui->CurrentGainBSlider->value() << StartByte);

    for (i = 0; i < Regnew.length(); i += 2)
    {
        Regnew[i] = (unsigned char)(REGnew[i / 2] % 256);
        Regnew[i + 1] = (unsigned char)(REGnew[i / 2] / 256);
    }
    for (i = 0; i < Regnew.length(); i++)
    {
        ICPara[256 + i + (Regnum - 1) * 6] = Regnew[i];
    }
}
void CurrentGain::Write5353Current(int ByteCount, int StartByte)
{
    int i = 0;
    QByteArray Regold;
    Regold.resize(6);

    QByteArray Regnew;
    Regnew.resize(6);

    int REGold[3];
    int REGnew[3];

    REGold[0] = ICPara[0x106] + ICPara[0x107] * 256;
    REGold[1] = ICPara[0x10C] + ICPara[0x10D] * 256;
    REGold[2] = ICPara[0x112] + ICPara[0x113] * 256;

    REGnew[0] = (REGold[0] & ~((int)(pow(2,ByteCount) - 1) << StartByte)) | (ui->CurrentGainRSlider->value() << StartByte);
    REGnew[1] = (REGold[1] & ~((int)(pow(2,ByteCount) - 1) << StartByte)) | (ui->CurrentGainGSlider->value() << StartByte);
    REGnew[2] = (REGold[2] & ~((int)(pow(2,ByteCount) - 1) << StartByte)) | (ui->CurrentGainBSlider->value() << StartByte);

    for (i = 0; i < Regnew.length(); i += 2)
    {
        Regnew[i] = (unsigned char)(REGnew[i / 2] % 256);
        Regnew[i + 1] = (unsigned char)(REGnew[i / 2] / 256);
    }

    ICPara[0x106] = Regnew[0];
    ICPara[0x107] = Regnew[1];
    ICPara[0x10C] = Regnew[2];
    ICPara[0x10D] = Regnew[3];
    ICPara[0x112] = Regnew[4];
    ICPara[0x113] = Regnew[5];

}



void CurrentGain::Write5043Current(int ByteCount, int StartByte)
{
    int i = 0;

    QByteArray Regnew;
    Regnew.resize(6);

    int REGold[3];
    int REGnew[3];

    REGold[0] = ICPara[0x100] + ICPara[0x101] * 256;
    REGold[1] = ICPara[0x102] + ICPara[0x103] * 256;
    REGold[2] = ICPara[0x104] + ICPara[0x105] * 256;

    REGnew[0] = (REGold[0] & ~((int)(pow(2,ByteCount) - 1) << StartByte)) | (ui->CurrentGainRSlider->value() << StartByte);
    REGnew[1] = (REGold[1] & ~((int)(pow(2,ByteCount) - 1) << StartByte)) | (ui->CurrentGainGSlider->value() << StartByte);
    REGnew[2] = (REGold[2] & ~((int)(pow(2,ByteCount) - 1) << StartByte)) | (ui->CurrentGainBSlider->value() << StartByte);

    for (i = 0; i < Regnew.length(); i += 2)
    {
        Regnew[i] = (unsigned char)(REGnew[i / 2] % 256);
        Regnew[i + 1] = (unsigned char)(REGnew[i / 2] / 256);
    }

    for (i = 0; i < Regnew.length(); i++)
    {
        ICPara[0x100 + i] = Regnew[i];
    }
}






















