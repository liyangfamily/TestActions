#include "mos5957config.h"
#include "ui_mos5957config.h"
#include "advancedsetting.h"

MOS5957config::MOS5957config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MOS5957config)
{
    ui->setupUi(this);

    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag                  |= Qt::WindowMinimizeButtonHint;
    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    setWindowFlags(windowFlag);

    LoadForm();
}
#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif
MOS5957config::~MOS5957config()
{
    delete ui;
}

void MOS5957config::LoadForm()
{
    ui->spinBox->setMaximum((uchar)ModulePara[0x1B]);
    ui->spinBox->setValue((uchar)DataPara[0x01]);
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
        UniversalInterface::MessageBoxShow(tr("设置"),tr("设置成功"));
    }
    else{
        UniversalInterface::MessageBoxShow(tr("设置"),tr("设置失败"));
    }
}
