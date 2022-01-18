#include "advancedotherpara.h"
#include "ui_advancedotherpara.h"
#include "advancedsetting.h"

AdvancedOtherPara::AdvancedOtherPara(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvancedOtherPara)
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

AdvancedOtherPara::~AdvancedOtherPara()
{
    delete ui;
}
void AdvancedOtherPara::InitForm()
{
    ui->SplicingModecomboBox->addItem("H31/M31");
    ui->SplicingModecomboBox->addItem("M30/M27Plus");

    ui->RotationMethodcomboBox->addItem(tr("0°"));
    ui->RotationMethodcomboBox->addItem(tr("90°"));
    ui->RotationMethodcomboBox->addItem(tr("180°"));
    ui->RotationMethodcomboBox->addItem(tr("270°"));

    ui->AdapterModelcomboBox->addItem("H31");
    ui->AdapterModelcomboBox->addItem("M30");
    ui->AdapterModelcomboBox->addItem("M27Plus");

    ui->VoltageControl1comboBox->addItem(tr("1档"));
    ui->VoltageControl1comboBox->addItem(tr("2档"));
    ui->VoltageControl1comboBox->addItem(tr("3档"));
    ui->VoltageControl1comboBox->addItem(tr("4档"));

    ui->VoltageControl2comboBox->addItem(tr("1档"));
    ui->VoltageControl2comboBox->addItem(tr("2档"));
    ui->VoltageControl2comboBox->addItem(tr("3档"));
    ui->VoltageControl2comboBox->addItem(tr("4档"));
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
    ModulePara[0x15] = (uchar)ui->SplicingModecomboBox->currentIndex();
    ModulePara[0x16] = (uchar)ui->RotationMethodcomboBox->currentIndex();
    ModulePara[0x17] = (uchar)ui->AdapterModelcomboBox->currentIndex();
    ModulePara[0x32] = 0;
    ModulePara[0x32] = (uchar)ModulePara[0x32] | (ui->VoltageControl1comboBox->currentIndex() & 0x03);
    ModulePara[0x32] = (uchar)ModulePara[0x32] | ((ui->VoltageControl2comboBox->currentIndex() & 0x03) << 4);
    ModulePara[0x21] = (uchar)ui->ICTortuousspinBox->value();
    ICPara[0xB7] = (uchar)ui->ChildspinBox->value();



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
