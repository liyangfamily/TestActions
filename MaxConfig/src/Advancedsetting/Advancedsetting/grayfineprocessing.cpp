#include "grayfineprocessing.h"
#include "ui_grayfineprocessing.h"
#include "advancedsetting.h"

GrayFineProcessing::GrayFineProcessing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GrayFineProcessing)
{
    ui->setupUi(this);

    LoadForm();
}

GrayFineProcessing::~GrayFineProcessing()
{
    delete ui;
}

void GrayFineProcessing::LoadForm()
{
    ui->CompensationRhorizontalSlider->setValue((unsigned char)ModulePara[0x37]);
    ui->CompensationGhorizontalSlider->setValue((unsigned char)ModulePara[0x38]);
    ui->CompensationBhorizontalSlider->setValue((unsigned char)ModulePara[0x39]);
    ui->ValuespinBox->setValue((unsigned char)ModulePara[0x3A]);
    ui->LimitRhorizontalSlider->setValue((unsigned char)ModulePara[0x3B]);
    ui->LimitGhorizontalSlider->setValue((unsigned char)ModulePara[0x3C]);
    ui->LimitBhorizontalSlider->setValue((unsigned char)ModulePara[0x3D]);
}

void GrayFineProcessing::on_pushButton_clicked()
{
    this->setCursor(Qt::WaitCursor);
    ModulePara[0x37] = ui->CompensationRhorizontalSlider->value();
    ModulePara[0x38] = ui->CompensationGhorizontalSlider->value();
    ModulePara[0x39] = ui->CompensationBhorizontalSlider->value();
    ModulePara[0x3A] = ui->ValuespinBox->value();
    ModulePara[0x3B] = ui->LimitRhorizontalSlider->value();
    ModulePara[0x3C] = ui->LimitGhorizontalSlider->value();
    ModulePara[0x3D] = ui->LimitBhorizontalSlider->value();

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

void GrayFineProcessing::on_CompensationRhorizontalSlider_valueChanged(int value)
{
    ui->CompensationRlabel->setText(QString::number(value));
}

void GrayFineProcessing::on_CompensationGhorizontalSlider_valueChanged(int value)
{
    ui->CompensationGlabel->setText(QString::number(value));
}

void GrayFineProcessing::on_CompensationBhorizontalSlider_valueChanged(int value)
{
    ui->CompensationBlabel->setText(QString::number(value));
}

void GrayFineProcessing::on_LimitRhorizontalSlider_valueChanged(int value)
{
    ui->LimitRlabel->setText(QString::number(value));
}

void GrayFineProcessing::on_LimitGhorizontalSlider_valueChanged(int value)
{
    ui->LimitGlabel->setText(QString::number(value));
}

void GrayFineProcessing::on_LimitBhorizontalSlider_valueChanged(int value)
{
    ui->LimitBlabel->setText(QString::number(value));
}
