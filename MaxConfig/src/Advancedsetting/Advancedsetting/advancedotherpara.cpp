#include "advancedotherpara.h"
#include "ui_advancedotherpara.h"
#include "advancedsetting.h"

AdvancedOtherPara::AdvancedOtherPara(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvancedOtherPara)
{
    ui->setupUi(this);

    InitForm();
    LoadForm();
}

AdvancedOtherPara::~AdvancedOtherPara()
{
    delete ui;
}
void AdvancedOtherPara::InitForm()
{
    ui->SplicingModecomboBox->addItem("H31/M31");
    ui->SplicingModecomboBox->addItem("M30/M27Plus");

    ui->RotationMethodcomboBox->addItem(QString::fromLocal8Bit("0°"));
    ui->RotationMethodcomboBox->addItem(QString::fromLocal8Bit("90°"));
    ui->RotationMethodcomboBox->addItem(QString::fromLocal8Bit("180°"));
    ui->RotationMethodcomboBox->addItem(QString::fromLocal8Bit("270°"));

    ui->AdapterModelcomboBox->addItem("H31");
    ui->AdapterModelcomboBox->addItem("M30");
    ui->AdapterModelcomboBox->addItem("M27Plus");

    ui->VoltageControl1comboBox->addItem(QString::fromLocal8Bit("3.8V(标准)"));
    ui->VoltageControl1comboBox->addItem(QString::fromLocal8Bit("3.9V(1档)"));
    ui->VoltageControl1comboBox->addItem(QString::fromLocal8Bit("4.0V(2档)"));
    ui->VoltageControl1comboBox->addItem(QString::fromLocal8Bit("4.1V(3档)"));

    ui->VoltageControl2comboBox->addItem(QString::fromLocal8Bit("3.8V(标准)"));
    ui->VoltageControl2comboBox->addItem(QString::fromLocal8Bit("3.9V(1档)"));
    ui->VoltageControl2comboBox->addItem(QString::fromLocal8Bit("4.0V(2档)"));
    ui->VoltageControl2comboBox->addItem(QString::fromLocal8Bit("4.1V(3档)"));
}
void AdvancedOtherPara::LoadForm()
{
    ui->SplicingModecomboBox->setCurrentIndex(ModulePara[0x15]);
    ui->RotationMethodcomboBox->setCurrentIndex(ModulePara[0x16]);
    ui->AdapterModelcomboBox->setCurrentIndex(ModulePara[0x17]);
    ui->VoltageControl1comboBox->setCurrentIndex(ModulePara[0x32] & 0x03);
    ui->VoltageControl2comboBox->setCurrentIndex((ModulePara[0x32] >> 4) & 0x03);
    ui->ICTortuousspinBox->setValue((uchar)ModulePara[0x21]);
    ui->ChildspinBox->setValue((uchar)ICPara[0xB7]);
}
void AdvancedOtherPara::on_pushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);
    ModulePara[0x15] = ui->SplicingModecomboBox->currentIndex();
    ModulePara[0x16] = ui->RotationMethodcomboBox->currentIndex();
    ModulePara[0x17] = ui->AdapterModelcomboBox->currentIndex();
    ModulePara[0x32] = 0;
    ModulePara[0x32] = ModulePara[0x32] | (ui->VoltageControl1comboBox->currentIndex() & 0x03);
    ModulePara[0x32] = ModulePara[0x32] | ((ui->VoltageControl2comboBox->currentIndex() & 0x03) << 4);
    ModulePara[0x21] = (uchar)ui->ICTortuousspinBox->value();
    ICPara[0xB7] = (uchar)ui->ChildspinBox->value();


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
