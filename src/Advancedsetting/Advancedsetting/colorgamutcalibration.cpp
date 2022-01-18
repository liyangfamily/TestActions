#include "colorgamutcalibration.h"
#include "ui_colorgamutcalibration.h"
#include "advancedsetting.h"
#include "colorgamut.h"


ColorGamutCalibration::ColorGamutCalibration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorGamutCalibration)
{
    ui->setupUi(this);
    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag                  |= Qt::WindowMinimizeButtonHint;
    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    setWindowFlags(windowFlag);


}
#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif
ColorGamutCalibration::~ColorGamutCalibration()
{
    delete ui;
}

void ColorGamutCalibration::on_pushButtonR_clicked()
{
    LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_Red);
}

void ColorGamutCalibration::on_pushButtonG_clicked()
{
    LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_Green);
}

void ColorGamutCalibration::on_pushButtonB_clicked()
{
    LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_Blue);
}


double* ColorGamutCalibration::CreatTargetCoefficient(double originalValue[], double targetValue[])
{
    double* coefficient = new double[6];
    //计算红色原始刺激值
    double o_RX = originalValue[1] / originalValue[2] * originalValue[0];
    double o_RY = originalValue[0];
    double o_RZ = (1 - originalValue[1] - originalValue[2]) / originalValue[2] * originalValue[0];

    //计算绿色原始刺激值
    double o_GX = originalValue[4] / originalValue[5] * originalValue[3];
    double o_GY = originalValue[3];
    double o_GZ = (1 - originalValue[4] - originalValue[5]) / originalValue[5] * originalValue[3];

    //计算蓝色原始刺激值
    double o_BX = originalValue[7] / originalValue[8] * originalValue[6];
    double o_BY = originalValue[6];
    double o_BZ = (1 - originalValue[7] - originalValue[8]) / originalValue[8] * originalValue[6];

    //红色系数
    double gr, br;

    double a = (targetValue[1] * o_RX);
    double b = (targetValue[0] * o_RY);
    double c = (targetValue[0] * o_BY - targetValue[1] * o_BX);
    double d = (targetValue[0] * o_GY - targetValue[1] * o_GX);

    double temp_r = 1000 - targetValue[0] - targetValue[1];

    double f = (temp_r * o_RY);
    double g = (targetValue[1] * o_RZ);
    double h = (temp_r * o_GY - targetValue[1] * o_GZ);
    double j = (targetValue[1] * o_BZ - temp_r * o_BY);

    gr = ((a - b) * j - c * (f - g)) / (d * j + h * c);
    br = (f - g + h * gr) / j;

    coefficient[0] = gr;
    coefficient[1] = br;
    //绿色的系数
    double rg, bg;
    double temp_g = 1000 - targetValue[2] - targetValue[3];

    a = targetValue[3] * o_GX;
    b = targetValue[2] * o_GY;
    c = targetValue[2] * o_RY - targetValue[3] * o_RX;
    d = targetValue[2] * o_BY - targetValue[3] * o_BX;

    double k = (targetValue[3] * o_GZ);
    f = (temp_g * o_GY);
    g = (targetValue[3] * o_BZ + temp_g * o_BY);
    h = (temp_g * o_RY - targetValue[3] * o_RZ);

    bg = ((a - b) * h - c * (k - f)) / (d * h + c * g);
    rg = (k - f + bg * g) / h;

    coefficient[2] = rg;
    coefficient[3] = bg;

    //蓝色的系数
    double rb, gb;
    double temp_b = 1000 - targetValue[4] - targetValue[5];

    a = targetValue[5] * o_BX;
    b = targetValue[4] * o_BY;
    c = targetValue[4] * o_GY - targetValue[5] * o_GX;
    d = targetValue[4] * o_RY - targetValue[5] * o_RX;

    f = targetValue[5] * o_BZ;
    g = temp_b * o_BY;
    k = temp_b * o_RY - targetValue[1] * o_RZ;
    h = temp_b * o_GY - targetValue[1] * o_GZ;

    rb = ((a - b) * h - c * (f - g)) / (d * h - c * k);
    gb = (f - g - k * rb) / h;

    coefficient[4] = rb;
    coefficient[5] = gb;
    return coefficient;

}

QByteArray ColorGamutCalibration::Junheng(double* xishu, double Rt, double Gt, double Bt)
{
    double* afterjh = new double[9];

    double Bs = ((Bt - (Rt * xishu[1])) * (1 - (xishu[2] * xishu[0])) - (Gt - (Rt * xishu[0])) * (xishu[3] - (xishu[2] * xishu[1]))) /
            ((1 - (xishu[4] * xishu[1])) * (1 - (xishu[2] * xishu[0])) - (xishu[5] - (xishu[4] * xishu[0])) * (xishu[3] - (xishu[2] * xishu[1])));
    double Gs = (Gt - (Rt * xishu[0]) - Bs * (xishu[5] - (xishu[4] * xishu[0]))) / (1 - xishu[2] * xishu[0]);
    double Rs = Rt - (Gs * xishu[2]) - (Bs * xishu[4]);
    double Rsg = Rs * xishu[0];
    double Rsb = Rs * xishu[1];
    double Gsr = Gs * xishu[2];
    double Gsb = Gs * xishu[3];
    double Bsr = Bs * xishu[4];
    double Bsg = Bs * xishu[5];

    afterjh[0] = Rs;
    afterjh[1] = Rsg;
    afterjh[2] = Rsb;
    afterjh[3] = Gsr;
    afterjh[4] = Gs;
    afterjh[5] = Gsb;
    afterjh[6] = Bsr;
    afterjh[7] = Bsg;
    afterjh[8] = Bs;

    int intxishu[9];
    for (int i = 0; i < 9; i++)
    {
        intxishu[i] = (int)(afterjh[i] * 65535);
    }
    QByteArray para;
    para.resize(18);

    for (int i = 0; i < 9; i++)
    {
        para[i * 2] = (uchar)(intxishu[i] & 0xFF);
        para[i * 2 + 1] = (uchar)((intxishu[i] >> 8) & 0xFF);
    }

    return para;
}



void ColorGamutCalibration::on_pushButtonConfig_clicked()
{
    this->setCursor(Qt::WaitCursor);

    //判断是否输入原始值
    if ((ui->O_RL->text() == "") || (ui->O_Rx->text() == "") || (ui->O_Ry->text() == ""))
    {
        UniversalInterface::MessageBoxShow(tr("输入"),tr("请输入原始值！"));
        this->setCursor(Qt::ArrowCursor);
        return;
    }
    if ((ui->O_GL->text() == "") || (ui->O_Gx->text() == "") || (ui->O_Gy->text() == ""))
    {
        UniversalInterface::MessageBoxShow(tr("输入"),tr("请输入原始值！"));
        this->setCursor(Qt::ArrowCursor);
        return;
    }
    if ((ui->O_BL->text() == "") || (ui->O_Bx->text() == "") || (ui->O_By->text() == ""))
    {
        UniversalInterface::MessageBoxShow(tr("输入"),tr("请输入原始值！"));
        this->setCursor(Qt::ArrowCursor);
        return;
    }

    double originalValue[9];
    originalValue[0] = ui->O_RL->text().toDouble();
    originalValue[1] = ui->O_Rx->text().toDouble();
    originalValue[2] = ui->O_Ry->text().toDouble();
    originalValue[3] = ui->O_GL->text().toDouble();
    originalValue[4] = ui->O_Gx->text().toDouble();
    originalValue[5] = ui->O_Gy->text().toDouble();
    originalValue[6] = ui->O_BL->text().toDouble();
    originalValue[7] = ui->O_Bx->text().toDouble();
    originalValue[8] = ui->O_By->text().toDouble();

    for (int i=0;i<9;i++)
    {
        if (i % 3 == 0) continue;
        if (originalValue[i] > 1)
        {
            UniversalInterface::MessageBoxShow(tr("输入"),tr("原始值输入数据有误！"));
            this->setCursor(Qt::ArrowCursor);
            return;
        }
    }

    double targetvalue[6];
    for (int i=0;i<6;i++)
    {
        targetvalue[i] = t_value[i];
    }

    double aftercalibration[9];

    double originalValue_R[9];
    double originalValue_G[9];
    double originalValue_B[9];
    for (int i=0;i<9;i++)
    {
        originalValue_R[i] = o_value[i];
        originalValue_G[i] = o_value[i];
        originalValue_B[i] = o_value[i];
    }

    //计算红色
    originalValue_R[0] = originalValue[0];
    originalValue_R[1] = originalValue[1];
    originalValue_R[2] = originalValue[2];

    double* coefficient_R = CreatTargetCoefficient(originalValue_R,targetvalue);

    aftercalibration[0] = coefficient_R[0];
    aftercalibration[1] = coefficient_R[1];

    //计算绿色
    originalValue_G[3] = originalValue[3];
    originalValue_G[4] = originalValue[4];
    originalValue_G[5] = originalValue[5];

    double* coefficient_G = CreatTargetCoefficient(originalValue_G,targetvalue);

    aftercalibration[2] = coefficient_G[2];
    aftercalibration[3] = coefficient_G[3];

    //计算蓝色
    originalValue_B[6] = originalValue[6];
    originalValue_B[7] = originalValue[7];
    originalValue_B[8] = originalValue[8];

    double* coefficient_B = CreatTargetCoefficient(originalValue_B,targetvalue);

    aftercalibration[4] = coefficient_B[4];
    aftercalibration[5] = coefficient_B[5];

    double EndCalibration[6];
    for (int i=0;i<6;i++)
    {
        EndCalibration[i] = aftercalibration[i] + FirstCalibration[i];
    }
    for (int i = 0; i < 3; i++)
    {
        if ((EndCalibration[i * 2 + 0] < 0) || (EndCalibration[i * 2 + 1] < 0))
        {
            EndCalibration[i * 2 + 0] = FirstCalibration[i * 2 + 0];
            EndCalibration[i * 2 + 1] = FirstCalibration[i * 2 + 1];
        }
    }

    QByteArray Para = Junheng(EndCalibration,1,1,1);
    for (int i = 0; i < 18; i++)
    {
        ModulePara[0x3E + i] = Para[i];
        qDebug() << "------------------------para[" << i << "] = " << (uchar)Para[i];
    }

    bool result = UniversalInterface::SendALLPara();

    this->setCursor(Qt::ArrowCursor);
    if (result)
    {
        UniversalInterface::MessageBoxShow(tr("完成"),tr("色域转换完成！"));
        return;
    }
}
