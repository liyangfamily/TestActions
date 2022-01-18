#include "datagroup.h"
#include "ui_datagroup.h"
#include <qstandarditemmodel.h>
#include <QDebug>
#include "advancedsetting.h"

DataGroup::DataGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataGroup)
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
DataGroup::~DataGroup()
{
    delete ui;
}


void DataGroup::InitForm()
{

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount((uchar)ModulePara[0x1F]);

    QStringList header;
    header<<tr("数据组数")<<tr("数据组交换")<<"Row"<<"Col";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(240,240,240);color: black;}");//设置表头背景和字体颜色
    //均分各列
    //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);

//    for (i=1;i<ui->tableWidget->rowCount();i++ )
//    {
//        for (j=1;j<ui->tableWidget->columnCount();j++)
//        {
//             qDebug() << "i=" << i << "j=" << j;
//            ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter);
//        }
//    }

     ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void DataGroup::LoadForm()
{
    int i = 0;

    for (i=0;i<ui->tableWidget->rowCount();i++ )
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number((uchar)DataPara[0x180 + i])));

        int datax = (uchar)DataPara[0x200 + i * 4 + 0] + (uchar)DataPara[0x200 + i * 4 + 1] * 256;
        int datay = (uchar)DataPara[0x200 + i * 4 + 2] + (uchar)DataPara[0x200 + i * 4 + 3] * 256;
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number((int)datay)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number((int)datax)));
    }

    ui->spinBox->setValue((uchar)ModulePara[0x1F]);
}

void DataGroup::on_spinBox_valueChanged(int arg1)
{
    ModulePara[0x1F] = (uchar)arg1;
    InitForm();
    LoadForm();
}


void DataGroup::on_pushButton_clicked()
{
     this->setCursor(Qt::WaitCursor);
    int i = 0;
    for (i=0;i<ui->tableWidget->rowCount();i++)
    {
        bool ok ;
        uchar byte1 = QString(ui->tableWidget->item(i,1)->text()).toInt(&ok,10);
        DataPara[0x180 + i] = byte1;
        int Row = QString(ui->tableWidget->item(i,2)->text()).toInt(&ok,10);
        int Col = QString(ui->tableWidget->item(i,3)->text()).toInt(&ok,10);

        DataPara[0x200 + i * 4 + 0] = Col & 0xFF;
        DataPara[0x200 + i * 4 + 1] = (Col >> 8) & 0xFF;

        DataPara[0x200 + i * 4 + 2] = Row & 0xFF;
        DataPara[0x200 + i * 4 + 3] = (Row >> 8) & 0xFF;
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
























