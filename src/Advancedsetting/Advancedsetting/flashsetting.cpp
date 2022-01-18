#include "flashsetting.h"
#include "ui_flashsetting.h"
#include "advancedsetting.h"

FLASHsetting::FLASHsetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FLASHsetting)
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

FLASHsetting::~FLASHsetting()
{
    delete ui;
}
void FLASHsetting::InitForm()
{

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount((uchar)ModulePara[0x28]);

    QStringList header;
    header<<tr("FLASH端口")<<tr("FLASH对应编号");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(240,240,240);color: black;}");//设置表头背景和字体颜色

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    //均分各列
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void FLASHsetting::LoadForm()
{
    int i = 0;

    for (i=0;i<ui->tableWidget->rowCount();i++ )
    {

        int FlashNumber = (uchar)DataPara[0x100 + i];

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(FlashNumber)));
    }
    ui->FLASHSumCountspinBox->setValue((uchar)ModulePara[0x28]);

}

void FLASHsetting::on_FLASHSumCountspinBox_valueChanged(int arg1)
{
    ModulePara[0x28] = arg1;
    InitForm();
    LoadForm();
}

void FLASHsetting::on_FLASHSetting_clicked()
{
    this->setCursor(Qt::WaitCursor);
    int i = 0;
    for (i=0;i<ui->tableWidget->rowCount();i++)
    {
        bool ok ;


        uchar Number = QString(ui->tableWidget->item(i,1)->text()).toInt(&ok,10);

        DataPara[0x100 + i] = Number;

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
