#include "moscfd2138config.h"
#include "ui_moscfd2138config.h"
#include "advancedsetting.h"

MOSCFD2138config::MOSCFD2138config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MOSCFD2138config)
{
    ui->setupUi(this);

    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag                  |= Qt::WindowMinimizeButtonHint;
    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    setWindowFlags(windowFlag);

    LoadPara();
}

#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif

MOSCFD2138config::~MOSCFD2138config()
{
    delete ui;
}

void MOSCFD2138config::LoadPara()
{
    showinfo = true;
    ui->ValuespinBox->setValue((uchar)DataPara[0x02]);
    if ((ui->ValuespinBox->value() & 0x08) == 0x08)
    {
        ui->ShadowingModespinBox->setValue(1);
        ui->ShadowingVoltagespinBox->setValue(ui->ValuespinBox->value() - 8);
    }
    else
    {
        ui->ShadowingModespinBox->setValue(0);
        ui->ShadowingVoltagespinBox->setValue(ui->ValuespinBox->value());
    }

    ui->CascadeControlspinBox->setValue((uchar)DataPara[0x03] + (uchar)DataPara[0x04] * 256);
    showinfo = false;
}

void MOSCFD2138config::on_ShadowingModespinBox_valueChanged(int arg1)
{
    if (showinfo)
    {
        return;
    }
    showinfo = true;
    if (arg1 == 1)
    {
        DataPara[0x02] = (uchar)DataPara[0x02] & 0x00;
        DataPara[0x02] = (uchar)DataPara[0x02] | 0x08;
        DataPara[0x02] = (uchar)DataPara[0x02] | ui->ShadowingVoltagespinBox->value();
    }
    else
    {
        DataPara[0x02] = (uchar)DataPara[0x02] & 0x00;
        DataPara[0x02] = (uchar)DataPara[0x02] | ui->ShadowingVoltagespinBox->value();
    }
    ui->ValuespinBox->setValue((uchar)DataPara[0x02]);

    showinfo = false;
}

void MOSCFD2138config::on_ShadowingVoltagespinBox_valueChanged(int arg1)
{
    if (showinfo)
    {
        return;
    }
    showinfo = true;
    if (ui->ShadowingModespinBox->value() == 1)
    {
        DataPara[0x02] = (uchar)DataPara[0x02] & 0x00;
        DataPara[0x02] = (uchar)DataPara[0x02] | 0x08;
        DataPara[0x02] = (uchar)DataPara[0x02] | arg1;
    }
    else
    {
        DataPara[0x02] = (uchar)DataPara[0x02] & 0x00;
        DataPara[0x02] = (uchar)DataPara[0x02] | arg1;
    }
    ui->ValuespinBox->setValue((uchar)DataPara[0x02]);

    showinfo = false;
}


void MOSCFD2138config::on_ValuespinBox_valueChanged(int arg1)
{
    if (showinfo)
    {
        return;
    }
    showinfo = true;
    if ((arg1 & 0x08) == 0x08)
    {
        ui->ShadowingModespinBox->setValue(1);
        ui->ShadowingVoltagespinBox->setValue(ui->ValuespinBox->value() - 8);
    }
    else
    {
        ui->ShadowingModespinBox->setValue(0);
        ui->ShadowingVoltagespinBox->setValue(ui->ValuespinBox->value());
    }
    showinfo = false;
}

void MOSCFD2138config::on_pushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);
    DataPara[0x02] = ui->ValuespinBox->value();
    DataPara[0x03] = ui->CascadeControlspinBox->value() % 256;
    DataPara[0x04] = ui->CascadeControlspinBox->value() / 256;

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






















