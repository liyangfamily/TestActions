#include "advancedcustom.h"
#include "ui_advancedcustom.h"
#include "advancedsetting.h"

AdvancedCustom::AdvancedCustom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvancedCustom)
{
    ui->setupUi(this);

    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag                  |= Qt::WindowMinimizeButtonHint;
    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    //windowFlag                  |= Qt::WindowStaysOnTopHint;
    setWindowFlags(windowFlag);

    InitForm();
}

#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif


AdvancedCustom::~AdvancedCustom()
{
    delete ui;
}
void AdvancedCustom::InitForm()
{
    QByteArray CustomPara = UniversalInterface::Readbin(LBLUIHelper::appParamDataLocation() + "//Custom.bin");


    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(CustomPara.length() / 2);

    QStringList header;
    header<<tr("Addr")<<tr("Value");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(240,240,240);color: black;}");//设置表头背景和字体颜色

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    //均分各列
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    int i = 0;
    for (i=0;i<ui->tableWidget->rowCount();i++ )
    {
        int addr = (uchar)CustomPara[i * 2 + 0] + (uchar)CustomPara[i * 2 + 1] * 256;

        qDebug() << "Addr:" << addr;
        char chBuf[20];
        sprintf(chBuf,"%02x",addr);
        QString key = QString::fromUtf8(chBuf);

        qDebug() << "Key:" <<key;
        ui->tableWidget->setItem(i,0,new QTableWidgetItem("0x" + key));


        if (addr < 0x400)
        {
            ui->tableWidget->setItem(i,1,new QTableWidgetItem("0x" + QString("%1").arg((uchar)ModulePara[addr],2,16,QLatin1Char('0')).toUpper()));
        }
        else if ((addr >= 0x400) && (addr < 0x800))
        {
             ui->tableWidget->setItem(i,1,new QTableWidgetItem("0x" + QString("%1").arg((uchar)DataPara[addr - 0x400],2,16,QLatin1Char('0')).toUpper()));
        }
        else if ((addr >= 0x800) && (addr < 0xC00))
        {
             ui->tableWidget->setItem(i,1,new QTableWidgetItem("0x" + QString("%1").arg((uchar)ICPara[addr - 0x800],2,16,QLatin1Char('0')).toUpper()));
        }
    }

}

void AdvancedCustom::LordForm()
{


}





void AdvancedCustom::on_pushButton_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
}

void AdvancedCustom::on_pushButton_2_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void AdvancedCustom::on_pushButton_3_clicked()
{
    this->setCursor(Qt::WaitCursor);
    int i = 0;
    QByteArray CustomPara;
    CustomPara.resize(ui->tableWidget->rowCount() * 2);
    for (i=0;i<CustomPara.length();i++)
    {
        CustomPara[i] = 0;
    }


    for (i=0;i<ui->tableWidget->rowCount();i++)
    {
        bool result =  ui->tableWidget->item(i,0) == NULL || (ui->tableWidget->item(i,0) && ui->tableWidget->item(i,0)->text() == tr(""));
        if (result == NULL)
        {
            QString str = ui->tableWidget->item(i,0)->text();
            quint32 addr = 0;
            if (str.length() == 4)
            {
                addr = UniversalInterface::ConvertHexChar(str[2].toLatin1()) * 16 + UniversalInterface::ConvertHexChar(str[3].toLatin1());
            }
            else if (str.length() == 5)
            {
                addr = (uchar)UniversalInterface::ConvertHexChar(str[2].toLatin1()) * 256 + (uchar)UniversalInterface::ConvertHexChar(str[3].toLatin1()) * 16 + (uchar)UniversalInterface::ConvertHexChar(str[4].toLatin1());
            }

            result =  ui->tableWidget->item(i,1) == NULL || (ui->tableWidget->item(i,1) && ui->tableWidget->item(i,1)->text() == tr(""));
            if (result == NULL)
            {
                QString str1 = ui->tableWidget->item(i,1)->text();
                uchar value = 0;
                if (str1.length() == 4)
                {
                    value = UniversalInterface::ConvertHexChar(str1[2].toLatin1()) * 16 + UniversalInterface::ConvertHexChar(str1[3].toLatin1());
                }

                if (addr < 0x400)
                {
                    ModulePara[addr] = value;
                }
                else if ((addr >= 0x400) && (addr < 0x800))
                {
                    DataPara[addr - 0x400] = value;
                }
                else if ((addr >= 0x800) && (addr < 0xC00))
                {
                    ICPara[addr - 0x800] = value;
                }
                CustomPara[i * 2 + 0] = (uchar)(addr % 256);
                CustomPara[i * 2 + 1] = (uchar)(addr / 256);
            }
        }
    }

    //发送参数
    bool result = UniversalInterface::SendALLPara();

    if (result)
    {
        UniversalInterface::Writebin(LBLUIHelper::appParamDataLocation() + "//Custom.bin",CustomPara);
        UniversalInterface::MessageBoxShow(tr("Set up"),tr("SetupSuccessfully"));
    }
    else{
         UniversalInterface::MessageBoxShow(tr("Set up"),tr("Setup failed"));
    }
    this->setCursor(Qt::ArrowCursor);

}










