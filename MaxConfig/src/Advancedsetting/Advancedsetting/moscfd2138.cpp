#include "moscfd2138.h"
#include "ui_moscfd2138.h"
#include "advancedsetting.h"

MOSCFD2138::MOSCFD2138(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MOSCFD2138)
{
    ui->setupUi(this);

    LoadPara();
}

MOSCFD2138::~MOSCFD2138()
{
    delete ui;
}

void MOSCFD2138::LoadPara()
{
    showinfo = true;
    ui->ValuespinBox->setValue(DataPara[0x01]);
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

    ui->CascadeControlspinBox->setValue(DataPara[0x02] + DataPara[0x03] * 256);
    showinfo = false;
}

void MOSCFD2138::on_ShadowingModespinBox_valueChanged(int arg1)
{
    if (showinfo)
    {
        return;
    }
    showinfo = true;
    if (arg1 == 1)
    {
        DataPara[0x01] = DataPara[0x01] & 0x00;
        DataPara[0x01] = DataPara[0x01] | 0x08;
        DataPara[0x01] = DataPara[0x01] | ui->ShadowingVoltagespinBox->value();
    }
    else
    {
        DataPara[0x01] = DataPara[0x01] & 0x00;
        DataPara[0x01] = DataPara[0x01] | ui->ShadowingVoltagespinBox->value();
    }
    ui->ValuespinBox->setValue(DataPara[0x01]);

    showinfo = false;
}

void MOSCFD2138::on_ShadowingVoltagespinBox_valueChanged(int arg1)
{
    if (showinfo)
    {
        return;
    }
    showinfo = true;
    if (ui->ShadowingModespinBox->value() == 1)
    {
        DataPara[0x01] = DataPara[0x01] & 0x00;
        DataPara[0x01] = DataPara[0x01] | 0x08;
        DataPara[0x01] = DataPara[0x01] | arg1;
    }
    else
    {
        DataPara[0x01] = DataPara[0x01] & 0x00;
        DataPara[0x01] = DataPara[0x01] | arg1;
    }
    ui->ValuespinBox->setValue(DataPara[0x01]);

    showinfo = false;
}


void MOSCFD2138::on_ValuespinBox_valueChanged(int arg1)
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

void MOSCFD2138::on_pushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);
    DataPara[0x01] = ui->ValuespinBox->value();
    DataPara[0x02] = ui->CascadeControlspinBox->value() % 256;
    DataPara[0x03] = ui->CascadeControlspinBox->value() / 256;

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






















