#include "rgbchange.h"
#include "ui_rgbchange.h"
#include "advancedsetting.h"

RGBchange::RGBchange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RGBchange)
{
    ui->setupUi(this);



    InitForm();
    LoadForm();

}

void RGBchange::InitForm()
{
    ui->comboBox->addItem(QString::fromLocal8Bit("红"));
    ui->comboBox->addItem(QString::fromLocal8Bit("绿"));
    ui->comboBox->addItem(QString::fromLocal8Bit("蓝"));

    ui->comboBox_2->addItem(QString::fromLocal8Bit("红"));
    ui->comboBox_2->addItem(QString::fromLocal8Bit("绿"));
    ui->comboBox_2->addItem(QString::fromLocal8Bit("蓝"));

    ui->comboBox_3->addItem(QString::fromLocal8Bit("红"));
    ui->comboBox_3->addItem(QString::fromLocal8Bit("绿"));
    ui->comboBox_3->addItem(QString::fromLocal8Bit("蓝"));

    ui->comboBox_4->addItem(QString::fromLocal8Bit("红"));
    ui->comboBox_4->addItem(QString::fromLocal8Bit("绿"));
    ui->comboBox_4->addItem(QString::fromLocal8Bit("蓝"));
    ui->comboBox_4->addItem(QString::fromLocal8Bit("黑"));
}

void RGBchange::LoadForm()
{
    ui->comboBox->setCurrentIndex(ModulePara[0x24] & 0x03);
    ui->comboBox_2->setCurrentIndex((ModulePara[0x24] >> 2) & 0x03);
    ui->comboBox_3->setCurrentIndex((ModulePara[0x24] >> 4) & 0x03);
    ui->comboBox_4->setCurrentIndex((ModulePara[0x24] >> 6) & 0x03);
}





RGBchange::~RGBchange()
{
    delete ui;
}

void RGBchange::on_pushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);
    ModulePara[0x24] = (ui->comboBox_4->currentIndex() << 6) | (ui->comboBox_3->currentIndex() << 4) | (ui->comboBox_2->currentIndex() << 2) | (ui->comboBox->currentIndex());

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






















