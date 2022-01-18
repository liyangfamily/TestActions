#include "mosicnd2018config.h"
#include "ui_mosicnd2018config.h"
#include "advancedsetting.h"

MOSICND2018config::MOSICND2018config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MOSICND2018config)
{
    ui->setupUi(this);
}

MOSICND2018config::~MOSICND2018config()
{
    delete ui;
}


void MOSICND2018config::LoadForm()
{
    showinfo = true;


    ui->ValuespinBox->setValue(DataPara[0x02]);
    if (((ui->ValuespinBox->value() - 8) & 0x08) == 0x08)
    {
        ui->ShadowingModespinBox->setValue(1);
        ui->ShadowingVoltagespinBox->setValue((ui->ValuespinBox->value() - 16) * 0.25 + 2);
    }
    else
    {
        ui->ShadowingModespinBox->setValue(0);
        ui->ShadowingVoltagespinBox->setValue((ui->ValuespinBox->value() - 8) * 0.25 + 2);
    }


    showinfo = false;
}

void MOSICND2018config::on_ShadowingModespinBox_valueChanged(int arg1)
{
    if (showinfo)
    {
        return;
    }
    showinfo = true;
    if (arg1 == 1)
    {
        DataPara[0x02] = DataPara[0x02] & 0x00;
        DataPara[0x02] = DataPara[0x02] | 0x08;
        DataPara[0x02]= DataPara[0x02] | (uchar)((ui->ShadowingVoltagespinBox->value() - 2.0) / 0.25);
    }
    else
    {
        DataPara[0x02] = DataPara[0x02] & 0x00;
        DataPara[0x02]= DataPara[0x02] | (uchar)((ui->ShadowingVoltagespinBox->value() - 2.0) / 0.25);
    }
    ui->ValuespinBox->setValue(DataPara[0x02] + 8);
    showinfo = false;
}

void MOSICND2018config::on_ShadowingVoltagespinBox_valueChanged(double arg1)
{
    if (showinfo)
    {
        return;
    }
    showinfo = true;
    if (ui->ShadowingModespinBox->value() == 1)
    {
        DataPara[0x02] = DataPara[0x02] & 0x00;
        DataPara[0x02] = DataPara[0x02] | 0x08;
        DataPara[0x02]= DataPara[0x02] | (uchar)((arg1 - 2.0) / 0.25);
    }
    else
    {
        DataPara[0x02] = DataPara[0x02] & 0x00;
        DataPara[0x02]= DataPara[0x02] | (uchar)((arg1 - 2.0) / 0.25);
    }
    ui->ValuespinBox->setValue(DataPara[0x02] + 8);
    showinfo = false;
}

void MOSICND2018config::on_ValuespinBox_valueChanged(int arg1)
{
    if (showinfo)
    {
        return;
    }
    showinfo = true;
    if (((arg1 - 8) & 0x08) == 0x08)
    {
        ui->ShadowingModespinBox->setValue(1);
        ui->ShadowingVoltagespinBox->setValue((ui->ValuespinBox->value() - 16) * 0.25 + 2);
    }
    else
    {
        ui->ShadowingModespinBox->setValue(0);
        ui->ShadowingVoltagespinBox->setValue((ui->ValuespinBox->value() - 8) * 0.25 + 2);
    }
    showinfo = false;
}

void MOSICND2018config::on_pushButton_clicked()
{
    DataPara[0x02] = (uchar)ui->ValuespinBox->value();

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
