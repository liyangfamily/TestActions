#include "smartsetting.h"
#include "ui_smartsetting.h"
#include <QFile>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "advancedsetting.h"
#include <QDebug>
#include "universalinterface.h"
#include <qobject.h>
#include "smartsecondsetting.h"
#include "smartsecondsettingxian.h"
#include <QtCore/qmath.h>



SmartSetting::SmartSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmartSetting)
{
    ui->setupUi(this);




    initCombobox();


    LoadPara();

}




SmartSetting::~SmartSetting()
{
    delete ui;
}





void SmartSetting::LoadPara()
{

    //qDebug() << "load";

    ui->LEDBoxWspinBox->setValue((unsigned char)ModulePara[0x06] + (unsigned char)ModulePara[0x07] * 256);
    ui->LEDBoxHspinBox->setValue((unsigned char)ModulePara[0x08] + (unsigned char)ModulePara[0x09] * 256);

    ui->LightWspinBox->setValue((unsigned char)ModulePara[0x02] + (unsigned char)ModulePara[0x03] * 256);
    ui->LightHspinBox->setValue((unsigned char)ModulePara[0x04] + (unsigned char)ModulePara[0x05] * 256);

    ShowCombobox();

    ui->ScanspinBox->setValue(ModulePara[0x25]);
    ui->OneDataspinBox->setValue(ModulePara[0x1E]);

    switch (ModulePara[0x71]) {
    case 0:
        ui->CLKcomboBox->setCurrentIndex(2);
        break;
    case 1:
        ui->CLKcomboBox->setCurrentIndex(1);
        break;
    case 2:
        ui->CLKcomboBox->setCurrentIndex(0);
        break;
    default:
        ui->CLKcomboBox->setCurrentIndex(2);
        break;
    }


    ui->ScancomboBox->setCurrentIndex((ModulePara[0x23] >> 2) & 0x01);

}
void SmartSetting::initCombobox()
{
    QStringList ic;
    ic.append(QString::fromLocal8Bit("常规芯片"));

    //普通芯片需配寄存器
    ic.append("ICN-2038S");
    ic.append("MBI-5038");
    ic.append("SUM-2017T");
    ic.append("MBI-5124");
    ic.append("SUM-2017");

    //自解码芯片
    ic.append("SUM-2030");
    ic.append("SUM-2030T");
    ic.append("SUM-2032");
    ic.append("SUM-2131");
    ic.append("SUM-2033");
    ic.append("MBI-5252");
    ic.append("MBI-5041B");
    ic.append("MBI-5041Q");
    ic.append("MBI-5042/5041");
    ic.append("MBI-5042B");
    ic.append("MBI-5043");
    ic.append("MBI-5151");
    ic.append("MBI-5047");
    ic.append("MBI-5152");
    ic.append("MBI-5153");
    ic.append("MBI-5155");
    ic.append("SUM-2035");
    ic.append("SM-16259");
    ic.append("MBI-5353");
    ic.append("SUM-6086");
    ic.append("LS-9935");
    ic.append("ICN-2055/2069");
    ic.append("CFD-335A");
    ic.append("SUM-2035NEW");
    ic.append("ICN-2153");
    ic.append("FM-6363");
    ic.append("FM-6565");
    ic.append("LS-9935B");
    ic.append("CFD-435A");
    ic.append("CFD-555A");
    ic.append("CFD-455A");
    ic.append("DP-3246");


    ui->ICcomboBox->addItems(ic);

    ui->MOScomboBox->addItem(QString::fromLocal8Bit("直通译码"));
    ui->MOScomboBox->addItem(QString::fromLocal8Bit("138译码"));
    ui->MOScomboBox->addItem("RT5957");
    ui->MOScomboBox->addItem("SM5366");
    ui->MOScomboBox->addItem("ICND2018/2019");
    ui->MOScomboBox->addItem("C82018");
    ui->MOScomboBox->addItem("CFD2138");
    ui->MOScomboBox->addItem("RUL5158");

    ui->CLKcomboBox->addItem("100 MHz");
    ui->CLKcomboBox->addItem("125 MHz");
    ui->CLKcomboBox->addItem("150 MHz");

    ui->ScancomboBox->addItem(QString::fromLocal8Bit("行扫"));
    ui->ScancomboBox->addItem(QString::fromLocal8Bit("列扫"));

    ui->HubcomboBox->addItem("hub320");
    ui->HubcomboBox->addItem("hub75");
}

void SmartSetting::ShowCombobox()
{
    unsigned char index = (unsigned char)ModulePara[0x13] + (unsigned char)ModulePara[0x14] * 256;
    switch (index)
    {
    case CONVENTSIONALCHIP:
        ui->ICcomboBox->setCurrentIndex(0);
        break;
    case ICN_2038S:
        ui->ICcomboBox->setCurrentIndex(1);
        break;
    case MBI_5038:
        ui->ICcomboBox->setCurrentIndex(2);
        break;
    case SUM_2017T:
        ui->ICcomboBox->setCurrentIndex(3);
        break;
    case MBI_5124:
        ui->ICcomboBox->setCurrentIndex(4);
        break;
    case SUM_2017:
        ui->ICcomboBox->setCurrentIndex(5);
        break;
    case SUM_2030:
        ui->ICcomboBox->setCurrentIndex(6);
        break;
    case SUM_2030T:
        ui->ICcomboBox->setCurrentIndex(7);
        break;
    case SUM_2032:
        ui->ICcomboBox->setCurrentIndex(8);
        break;
    case SUM_2131:
        ui->ICcomboBox->setCurrentIndex(9);
        break;
    case SUM_2033:
        ui->ICcomboBox->setCurrentIndex(10);
        break;
    case MBI_5252:
        ui->ICcomboBox->setCurrentIndex(11);
        break;
    case MBI_5041B:
        ui->ICcomboBox->setCurrentIndex(12);
        break;
    case MBI_5041Q:
        ui->ICcomboBox->setCurrentIndex(13);
        break;
    case MBI_5042_5041:
        ui->ICcomboBox->setCurrentIndex(14);
        break;
    case MBI_5042B:
        ui->ICcomboBox->setCurrentIndex(15);
        break;
    case MBI_5043:
        ui->ICcomboBox->setCurrentIndex(16);
        break;
    case MBI_5151:
        ui->ICcomboBox->setCurrentIndex(17);
        break;
    case MBI_5047:
        ui->ICcomboBox->setCurrentIndex(18);
        break;
    case MBI_5152:
        ui->ICcomboBox->setCurrentIndex(19);
        break;
    case MBI_5153:
        ui->ICcomboBox->setCurrentIndex(20);
        break;
    case MBI_5155:
        ui->ICcomboBox->setCurrentIndex(21);
        break;
    case SUM_2035:
        ui->ICcomboBox->setCurrentIndex(22);
        break;
    case SM_16259:
        ui->ICcomboBox->setCurrentIndex(23);
        break;
    case MBI_5353:
        ui->ICcomboBox->setCurrentIndex(24);
        break;
    case SUM_6086:
        ui->ICcomboBox->setCurrentIndex(25);
        break;
    case LS_9935:
        ui->ICcomboBox->setCurrentIndex(26);
        break;
    case ICN_2055_2069:
        ui->ICcomboBox->setCurrentIndex(27);
        break;
    case CFD_335A:
        ui->ICcomboBox->setCurrentIndex(28);
        break;
    case SUM_2035NEW:
        ui->ICcomboBox->setCurrentIndex(29);
        break;
    case ICN_2153:
        ui->ICcomboBox->setCurrentIndex(30);
        break;
    case FM_6363:
        ui->ICcomboBox->setCurrentIndex(31);
        break;
    case FM_6565:
        ui->ICcomboBox->setCurrentIndex(32);
        break;
    case LS_9935B:
        ui->ICcomboBox->setCurrentIndex(33);
        break;
    case CFD_435A:
        ui->ICcomboBox->setCurrentIndex(34);
        break;
    case CFD_555A:
        ui->ICcomboBox->setCurrentIndex(35);
        break;
    case CFD_455A:
        ui->ICcomboBox->setCurrentIndex(36);
        break;
    case DP_3246:
        ui->ICcomboBox->setCurrentIndex(37);
    default:
        break;

    }


    ui->MOScomboBox->setCurrentIndex(ModulePara[0x12]);


}















void SmartSetting::on_ImportpushButton_clicked()
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

    //QString filename = QCoreApplication::applicationDirPath();
    QByteArray file = UniversalInterface::Readbin(fileName);

    //send file
    LAPI::EResult ret2 = LAPI::UpgradeFile(m_upgradeType,file);
    if (ret2 == LAPI::EResult::ER_INTECTRL_Success)
    {
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("导入文件"),QString::fromLocal8Bit("文件导入成功"));
    }
    else
    {
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("导入文件"),QString::fromLocal8Bit("文件导入失败"));
    }

}



void SmartSetting::on_pushButton_clicked()
{
    this->close();
}



void SmartSetting::on_NextpushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);

    //先发送默认连线关系文件
    LBLConnection* connection = LAPI::GetConnection();
    if (connection)
    {
        connection->clear();
        connection->setModuleHeight(512);
        connection->setModuleWidth(512);
        connection->setPortCount(1);
        connection->addPort(LBLSPort(0,QRectF(0,0,512,512)));
        connection->getPort(0).addModule(LBLSModule(0, QRectF(0,0,512,512)));
        if (LAPI::EResult::ER_Success != LAPI::WriteConnection(connection))
        {
            //ICore::statusBar()->showMessage(tr("连接关系发送失败."), 1000);
            UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("描点"),QString::fromLocal8Bit("设置失败！"));
              this->setCursor(Qt::ArrowCursor);
            return;
        }
    }
    else{
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("描点"),QString::fromLocal8Bit("设置失败！"));
          this->setCursor(Qt::ArrowCursor);
        return;
    }
    //读取描点默认模组参数文件
    ModulePara = UniversalInterface::Readbin(LBLUIHelper::appParamDataLocation() + "//DefaultModulePara.bin");
    quint16 value1 = 0;
    int index1 = ui->ICcomboBox->currentIndex();
    switch (index1)
    {
    //常规芯片
    case 0:
        value1 = CONVENTSIONALCHIP;
        break;
        //普通芯片需配寄存器
    case 1:
        value1 = ICN_2038S;
        break;
    case 2:
        value1 = MBI_5038;
        break;
    case 3:
        value1 = SUM_2017T;
        break;
    case 4:
        value1 = MBI_5124;
        break;
    case 5:
        value1 = SUM_2017;
        break;

        //自解码芯片
    case 6:
        value1 = SUM_2030;
         WriteScan(1, 4, 7);
        break;
    case 7:
        value1 = SUM_2030T;
         WriteScan(1, 4, 7);
        break;
    case 8:
        value1 = SUM_2032;
         WriteScan(1, 4, 7);
        break;
    case 9:
        value1 = SUM_2131;
          WriteScan(1, 5, 6);
        break;
    case 10:
        value1 = SUM_2033;
          WriteScan(1, 5, 6);
        break;
    case 11:
        value1 = MBI_5252;
         WriteScan(1, 4, 8);
        break;
    case 12:
        value1 = MBI_5041B;
        break;
    case 13:
        value1 = MBI_5041Q;
        break;
    case 14:
        value1 = MBI_5042_5041;
        break;
    case 15:
        value1 = MBI_5042B;
        break;
    case 16:
        value1 = MBI_5043;
        break;
    case 17:
        value1 = MBI_5151;
        break;
    case 18:
        value1 = MBI_5047;
        break;
    case 19:
        value1 = MBI_5152;
        break;
    case 20:
        value1 = MBI_5153;
           WriteScan(1, 5, 8);
        break;
    case 21:
        value1 = MBI_5155;
         WriteScan(1, 5, 8);
        break;
    case 22:
        value1 = SUM_2035;
         WriteScan(1, 5, 6);
        break;
    case 23:
        value1 = SM_16259;
         WriteScan(1, 5, 8);
        break;
    case 24:
        value1 = MBI_5353;
        ModulePara[0x5C] = ModulePara[0x5C] | 0x01;         //串行芯片设置
        WriteScan5353();
        break;
    case 25:
        value1 = SUM_6086;
        ModulePara[0x5C] = ModulePara[0x5C] | 0x01;         //串行芯片设置
        WriteScan(1, 5, 6);
        break;
    case 26:
        value1 = LS_9935;
        break;
    case 27:
        value1 = ICN_2055_2069;
        break;
    case 28:
        value1 = CFD_335A;
         WriteScan(1, 5, 6);
        break;
    case 29:
        value1 = SUM_2035NEW;
        break;
    case 30:
        value1 = ICN_2153;
        WriteScan(1, 5, 8);
        break;
    case 31:
        value1 = FM_6363;
        break;
    case 32:
        value1 = FM_6565;
        break;
    case 33:
        value1 = LS_9935B;
        break;
    case 34:
        value1 = CFD_435A;
         WriteScan(1, 5, 6);
        break;
    case 35:
        value1 = CFD_555A;
         WriteScan(1, 6, 6);
        break;
    case 36:
        value1 = CFD_455A;
         WriteScan(1, 6, 6);
        break;
    case 37:
        value1 = DP_3246;
        break;
    default:
        break;

    }


    int i = 0;
    //驱动芯片
    ModulePara[0x13] = value1 & 0xFF;
    ModulePara[0x14] = (value1 >> 8) & 0xFF;

    //箱体宽高
    ModulePara[0x06] = ui->LEDBoxWspinBox->value() & 0xFF;
    ModulePara[0x07] = (ui->LEDBoxWspinBox->value() >> 8) & 0xFF;
    ModulePara[0x08] = ui->LEDBoxHspinBox->value() & 0xFF;
    ModulePara[0x09] = (ui->LEDBoxHspinBox->value() >> 8) & 0xFF;

    //灯板宽高
    ModulePara[0x02] = ui->LightWspinBox->value() & 0xFF;
    ModulePara[0x03] = (ui->LightWspinBox->value() >> 8) & 0xFF;
    ModulePara[0x04] = ui->LightHspinBox->value() & 0xFF;
    ModulePara[0x05] = (ui->LightHspinBox->value() >> 8) & 0xFF;

    //行管
    ModulePara[0x12] = ui->MOScomboBox->currentIndex();

    //扫描 sn
    ModulePara[0x25] = ui->ScanspinBox->value();
    uchar sn = ui->ScanspinBox->value();

    //IC级联数/一组数据芯片数 cn
    ModulePara[0x1E] = ui->OneDataspinBox->value();
    cn = ui->OneDataspinBox->value();

    //系统时钟
    //ModulePara[0x71] = ui->CLKcomboBox->currentIndex();
    uchar fs = 0;
    switch (ui->CLKcomboBox->currentIndex())
    {
    case 0:
        fs = 100;
        ModulePara[0x71] = 0x02;
        break;
    case 1:
        fs = 125;
        ModulePara[0x71] = 0x01;
        break;
    case 2:
        fs = 150;
        ModulePara[0x71] = 0x00;
        break;
    default:
        fs = 150;
        break;
    }

    //行扫列扫
    if (ui->ScancomboBox->currentIndex() == 0)
    {
        ModulePara[0x23] = ModulePara[0x23] & 0xFB;
    }
    else
    {
        ModulePara[0x23] = ModulePara[0x23] | 0x04;
    }

    //hub320/hub75
    if (ui->HubcomboBox->currentIndex() == 0)
    {
        ModulePara[0x5C] = ModulePara[0x5C] & 0xBF;
    }
    else
    {
        ModulePara[0x5C] = ModulePara[0x5C] | 0x40;
    }

    //自解码芯片
    if (value1 > 0x80)
    {
        //DCLK/TXD分频
        ModulePara[0x18] = floor(fs * 1000000 / (cn * sn * channelCount * bitCount * FrameRate)) - 1;
    }
    else    //非自解码
    {
        //DCLK/TXD分频
        ModulePara[0x18] = floor(fs * 1000000 / (cn * sn * channelCount * bitCount * FrameRate * 2)) - 1;
    }
    //DCLK/TXD高电系数
    ModulePara[0x19] = ModulePara[0x18] / 2;
    //DCLK/TXD相位系数
    ModulePara[0x1A] = ModulePara[0x18] / 2;


    //西安协议
    //GCLK分频系数
    ModulePara[0x1B] = 0x0C;
    //GCLK高电系数
    ModulePara[0x1C] = 0x06;
    //GCLK相位系数
    ModulePara[0x1D] = 0x06;

    //IC级联数
    ModulePara[0x1E] = cn;
    //IC单向级联数
    ModulePara[0x20] = cn;





    //DataPara
    //读取默认行芯片参数
    QString MOSfilename = UniversalInterface::GetMOSFilename(ui->MOScomboBox->currentIndex());
    QByteArray MOSdata = UniversalInterface::ReadcsvContent("MOS",MOSfilename);

    for (i=0;i<MOSdata.length();i++)
    {
        DataPara[i] = MOSdata[i];
    }
    //扫描参数
    for (i=0;i<64;i++)
    {
        DataPara[0x80 + i] = i;
    }
    //Flash对应关系
    for (i=0;i<64;i++)
    {
        DataPara[0x100 + i] = i;
    }
    //数据组对应关系
    for (i=0;i<128;i++)
    {
        DataPara[0x180 + i] = i;
    }
    //数据组起始坐标
    for (i=0;i<4;i++)
    {
        DataPara[0x200 + i] = 0x00;
    }
    for (i=0x204;i<0x400;i++)
    {
        DataPara[i] = 0xFF;
    }



    //读取默认列芯片参数
    QString ICfilename = UniversalInterface::GetICFilename(value1);
    QByteArray icPara = UniversalInterface::ReadcsvContent("DriverIC",ICfilename);

    for (i=0;i<icPara.length();i++)
    {
        ICPara[i] = icPara[i];
    }

    switch (index1)
    {
    //常规芯片
    case 0:
        break;
        //普通芯片需配寄存器
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;

        //自解码芯片
    case 6:
        WriteScan(1, 4, 7);
        break;
    case 7:
        WriteScan(1, 4, 7);
        break;
    case 8:
        WriteScan(1, 4, 7);
        break;
    case 9:
        WriteScan(1, 5, 6);
        break;
    case 10:
        WriteScan(1, 5, 6);
        break;
    case 11:
        WriteScan(1, 4, 8);
        break;
    case 12:
        break;
    case 13:
        break;
    case 14:
        break;
    case 15:
        break;
    case 16:
        break;
    case 17:
        break;
    case 18:
        break;
    case 19:
        break;
    case 20:
        WriteScan(1, 5, 8);
        break;
    case 21:
        WriteScan(1, 5, 8);
        break;
    case 22:
        WriteScan(1, 5, 6);
        break;
    case 23:
        WriteScan(1, 5, 8);
        break;
    case 24:
        ModulePara[0x5C] = ModulePara[0x5C] | 0x01;         //串行芯片设置
        WriteScan5353();
        break;
    case 25:
        ModulePara[0x5C] = ModulePara[0x5C] | 0x01;         //串行芯片设置
        WriteScan(1, 5, 6);
        break;
    case 26:
        break;
    case 27:
        break;
    case 28:
        WriteScan(1, 5, 6);
        break;
    case 29:
        break;
    case 30:
        WriteScan(1, 5, 8);
        break;
    case 31:
        break;
    case 32:
        break;
    case 33:
        break;
    case 34:
        WriteScan(1, 5, 6);
        break;
    case 35:
        WriteScan(1, 6, 6);
        break;
    case 36:
        WriteScan(1, 6, 6);
        break;
    case 37:
        break;
    default:
        break;

    }

    if (UniversalInterface::SendALLPara())
    {
        emit SendSignal();

        QByteArray LinearTable = CreateDefaultTableXian();
        UniversalInterface::Writebin(LBLUIHelper::appParamDataLocation() + "//DefaultLinearTable.bin",LinearTable);

        //发送描点表
        LAPI::EResult ret1 = LAPI::UpgradeFile(m_upgradeType,LinearTable);
        if (ret1 == LAPI::EResult::ER_INTECTRL_Success)
        {
            SmartSecondSettingXian *smartsecondxian = new SmartSecondSettingXian();
            smartsecondxian->show();
        }
        else
        {
            UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("描点"),QString::fromLocal8Bit("设置失败！"));
        }
    }
    else
    {
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("描点"),QString::fromLocal8Bit("设置失败！"));
    }

    this->setCursor(Qt::ArrowCursor);



}


//
     //将扫描数写入寄存器中，只改变扫描数的几位，其他位不变
     //
void SmartSetting::WriteScan(int Regnum, int ByteCount, int StartByte)
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
    REGnew[0] = (REGold[0] & ~((int)(qPow(2, ByteCount) - 1) << StartByte)) | ((int)(ui->ScanspinBox->value() - 1) << StartByte);
    REGnew[1] = (REGold[1] & ~((int)(qPow(2, ByteCount) - 1) << StartByte)) | ((int)(ui->ScanspinBox->value() - 1) << StartByte);
    REGnew[2] = (REGold[2] & ~((int)(qPow(2, ByteCount) - 1) << StartByte)) | ((int)(ui->ScanspinBox->value() - 1) << StartByte);

    for (i = 0; i < Regnew.length(); i += 2)
    {
        Regnew[i] = (uchar)(REGnew[i / 2] % 256);
        Regnew[i + 1] = (uchar)(REGnew[i / 2] / 256);
    }
    for (i = 0; i < Regnew.length(); i++)
    {
        ICPara[0x100 + i + (Regnum - 1) * 6] = Regnew[i];
    }
}
//
    //将扫描数写入寄存器中，只改变扫描数的几位，其他位不变
    //
void SmartSetting::WriteScan5353()
{
    int REGold = 0;

    REGold = ICPara[0x100] + ICPara[0x101] * 256;

    REGold = (REGold & ~((int)(qPow(2, 5) - 1) << 5)) | ((int)(ui->ScanspinBox->value() - 1) << 5);

    ICPara[0x100] = (uchar)(REGold % 256);
    ICPara[0x101] = (uchar)(REGold / 256);
}




QByteArray SmartSetting::CreateDefaultTableXian()
{
    int i = 0;
    QByteArray LinearTable;
    LinearTable.resize(1024 * 2);
    for (i=0;i<LinearTable.size();i++)
    {
        LinearTable[i] = 0;
    }
    for (i=0;i<cn*16;i++)
    {
        LinearTable[i * 2 + 0] = (((cn * 16) - 1) - i) / 16;
        LinearTable[i * 2 + 1] = (((cn * 16) - 1) - i) % 16;
    }
    return LinearTable;
}





















