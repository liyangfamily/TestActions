#include "rgbchange.h"
#include "ui_rgbchange.h"
#include "advancedsetting.h"

RGBchange::RGBchange(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RGBchange)
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

void RGBchange::InitForm()
{
    ui->comboBox->addItem(tr("红"));
    ui->comboBox->addItem(tr("绿"));
    ui->comboBox->addItem(tr("蓝"));

    ui->comboBox_2->addItem(tr("红"));
    ui->comboBox_2->addItem(tr("绿"));
    ui->comboBox_2->addItem(tr("蓝"));

    ui->comboBox_3->addItem(tr("红"));
    ui->comboBox_3->addItem(tr("绿"));
    ui->comboBox_3->addItem(tr("蓝"));

    ui->comboBox_4->addItem(tr("红"));
    ui->comboBox_4->addItem(tr("绿"));
    ui->comboBox_4->addItem(tr("蓝"));
    ui->comboBox_4->addItem(tr("黑"));
}

void RGBchange::LoadForm()
{
    ui->comboBox->setCurrentIndex((uchar)ModulePara[0x24] & 0x03);
    ui->comboBox_2->setCurrentIndex(((uchar)ModulePara[0x24] >> 2) & 0x03);
    ui->comboBox_3->setCurrentIndex(((uchar)ModulePara[0x24] >> 4) & 0x03);
    ui->comboBox_4->setCurrentIndex(((uchar)ModulePara[0x24] >> 6) & 0x03);
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
        UniversalInterface::MessageBoxShow(tr("Set up"),tr("SetupSuccessfully"));
    }
    else{
        UniversalInterface::MessageBoxShow(tr("Set up"),tr("Setup failed"));
    }

}






















