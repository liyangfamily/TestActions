#include "mos5957config.h"
#include "ui_mos5957config.h"
#include "advancedsetting.h"

MOS5957config::MOS5957config(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MOS5957config)
{
    ui->setupUi(this);

    LoadForm();
}

MOS5957config::~MOS5957config()
{
    delete ui;
}

void MOS5957config::LoadForm()
{
    ui->spinBox->setMaximum(ModulePara[0x1B]);
    ui->spinBox->setValue(DataPara[0x01]);
}

void MOS5957config::on_pushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);
    DataPara[0x01] = ui->spinBox->value();


    bool result = false;
    result = UniversalInterface::SendALLPara();
    this->setCursor(Qt::ArrowCursor);
    if (result)
    {
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("设置"),QString::fromLocal8Bit("设置成功"));
    }
    else{
        UniversalInterface::MessageBoxShow(QString::fromLocal8Bit("设置"),QString::fromLocal8Bit("设置失败"));
    }
}
