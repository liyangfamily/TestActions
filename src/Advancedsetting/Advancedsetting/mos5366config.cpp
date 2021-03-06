#include "mos5366config.h"
#include "ui_mos5366config.h"
#include "advancedsetting.h"

MOS5366config::MOS5366config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MOS5366config)
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
MOS5366config::~MOS5366config()
{
    delete ui;
}


void MOS5366config::LoadForm()
{
    showinfo = true;
    if ((DataPara[0x01] & 0x02) == 0x02)
    {
        ui->ShadowingModespinBox->setValue(1);
    }
    else
    {
        ui->ShadowingModespinBox->setValue(2);
    }

    ui->ShadowingVoltagespinBox->setValue(((uchar)DataPara[0x01] >> 2) & 0x0F + 1);
    ui->ValuespinBox->setValue((uchar)DataPara[0x01] & 0x3F);

    ui->CascadeControlspinBox->setValue((uchar)DataPara[0x02] + (uchar)DataPara[0x03] * 256);

    showinfo = false;
}

void MOS5366config::on_ShadowingModespinBox_valueChanged(int arg1)
{
    if (showinfo) return;
    showinfo = true;

    if (arg1 == 1)
    {
        DataPara[0x01] = (uchar)DataPara[0x01] & 0xFD;
        DataPara[0x01] = (uchar)DataPara[0x01] | 0x02;
    }
    else
    {
        DataPara[0x01] = (uchar)DataPara[0x01] & 0xFD;
    }
    ui->ValuespinBox->setValue((uchar)DataPara[0x01]);
    showinfo = false;

}

void MOS5366config::on_ShadowingVoltagespinBox_valueChanged(int arg1)
{
    if (showinfo) return;
    showinfo = true;
    DataPara[0x01] = (uchar)DataPara[0x01] & 0xC3;
    DataPara[0x01] = (uchar)DataPara[0x01] | ((arg1 - 1) << 2);

    ui->ValuespinBox->setValue((uchar)DataPara[0x01]);
    showinfo = false;
}

void MOS5366config::on_ValuespinBox_valueChanged(int arg1)
{
    if (showinfo) return;
    showinfo = true;
    if ((arg1 & 0x02) == 0x02)
    {
        ui->ShadowingModespinBox->setValue(1);
    }
    else
    {
        ui->ShadowingModespinBox->setValue(2);
    }
    ui->ShadowingVoltagespinBox->setValue((arg1 >> 2) & 0x0F + 1);
    showinfo = false;
}

void MOS5366config::on_SettingpushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);
    DataPara[0x01] = ui->ValuespinBox->value();
    DataPara[0x02] = ui->CascadeControlspinBox->value() % 256;
    DataPara[0x03] = ui->CascadeControlspinBox->value() / 256;

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
