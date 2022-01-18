#include "colorgamut.h"
#include "ui_colorgamut.h"
#include "universalinterface.h"
#include <QMovie>
#include "QPainter"
#include <math.h>
#include "advancedsetting.h"
#include <QMessageBox>
#include "colorgamutcalibration.h"


#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif

std::vector<double> FirstCalibration;
std::vector<double> o_value;
std::vector<double> t_value;


ColorGamut::ColorGamut(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorGamut)
{
    ui->setupUi(this);
    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag                  |= Qt::WindowMinimizeButtonHint;
    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    setWindowFlags(windowFlag);

    QMovie  * movie  = new  QMovie(LBLUIHelper::appParamDataLocation() + "//CIE193.bmp");
    ui->labelBmp->setMovie(movie);
    movie -> start();

    QMovie  * moviex  = new  QMovie(LBLUIHelper::appParamDataLocation() + "//x.png");
    ui->labelx->setMovie(moviex);
    moviex -> start();

    QMovie  * moviey  = new  QMovie(LBLUIHelper::appParamDataLocation() + "//y.png");
    ui->labely->setMovie(moviey);
    moviey -> start();

    ui->label->setParent(ui->labelBmp);
    ui->label->installEventFilter(this);

    LoadForm();


}

ColorGamut::~ColorGamut()
{
    delete ui;
}



bool ColorGamut::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label && event->type() == QEvent::Paint)
    {
        myDraw();
    }
    return QWidget::eventFilter(watched,event);

}


void ColorGamut::myDraw()
{
    QPainter painter(ui->label);
    try {
        painter.setPen(Qt::white);
        double o_Rx = ui->O_Rx->text().toDouble() * 400;
        double o_Ry = ui->O_Ry->text().toDouble() * 400;
        double o_Gx = ui->O_Gx->text().toDouble() * 400;
        double o_Gy = ui->O_Gy->text().toDouble() * 400;
        double o_Bx = ui->O_Bx->text().toDouble() * 400;
        double o_By = ui->O_By->text().toDouble() * 400;

        painter.drawLine(o_Rx,400-o_Ry,o_Gx,400-o_Gy);
        painter.drawLine(o_Gx,400-o_Gy,o_Bx,400-o_By);
        painter.drawLine(o_Rx,400-o_Ry,o_Bx,400-o_By);

        painter.setPen(Qt::black);
        double t_Rx = ui->T_Rx->text().toDouble() * 400;
        double t_Ry = ui->T_Ry->text().toDouble() * 400;
        double t_Gx = ui->T_Gx->text().toDouble() * 400;
        double t_Gy = ui->T_Gy->text().toDouble() * 400;
        double t_Bx = ui->T_Bx->text().toDouble() * 400;
        double t_By = ui->T_By->text().toDouble() * 400;

        painter.drawLine(t_Rx,400-t_Ry,t_Gx,400-t_Gy);
        painter.drawLine(t_Gx,400-t_Gy,t_Bx,400-t_By);
        painter.drawLine(t_Rx,400-t_Ry,t_Bx,400-t_By);

    }  catch (QString) {

    }
    painter.end();

    ShowLabelValue();
}

void ColorGamut::LoadForm()
{
    switch ((ModulePara[0x5C] >> 2) & 0x07)
    {
    case 0:
        ui->pushButtonNTSC->click();
        break;
    case 1:
        ui->pushButtonPAL->click();
        break;
    case 2:
        ui->pushButtonREC709->click();
        break;
    case 3:
        ui->pushButtonDCIP3->click();
        break;
    case 4:
        ui->pushButtonCustom->click();
        break;
    default:
        break;
    }
}


void ColorGamut::on_pushButtonRed_clicked()
{
    LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_Red);
}

void ColorGamut::on_pushButtonGreen_clicked()
{
    LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_Green);
}

void ColorGamut::on_pushButtonBlue_clicked()
{
    LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_Blue);
}

void ColorGamut::on_pushButtonWhite_clicked()
{
    LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_White);
}

void ColorGamut::on_pushButtonNormal_clicked()
{
    LAPI::WriteSCSelfTestMode(LAPI::UI::EPictureTestMode::EPTM_Normal);
}

void ColorGamut::on_pushButtonNTSC_clicked()
{
    SetTextBoxEnable(false);
    GamutMode = 0;

   ui->pushButtonNTSC->setStyleSheet("background-color: rgb(0, 255, 0);");
   ui->pushButtonPAL->setStyleSheet("background-color: rgb(31, 44, 61);");
   ui->pushButtonREC709->setStyleSheet("background-color: rgb(31, 44, 61);");
   ui->pushButtonDCIP3->setStyleSheet("background-color: rgb(31, 44, 61);");
   ui->pushButtonCustom->setStyleSheet("background-color: rgb(31, 44, 61);");

    ui->T_Rx->setText("0.670");
    ui->T_Ry->setText("0.330");

    ui->T_Gx->setText("0.210");
    ui->T_Gy->setText("0.710");

    ui->T_Bx->setText("0.140");
    ui->T_By->setText("0.080");

}

void ColorGamut::on_pushButtonPAL_clicked()
{
    SetTextBoxEnable(false);
    GamutMode = 1;
    ui->pushButtonNTSC->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonPAL->setStyleSheet("background-color: rgb(0, 255, 0);");
    ui->pushButtonREC709->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonDCIP3->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonCustom->setStyleSheet("background-color: rgb(31, 44, 61);");

    ui->T_Rx->setText("0.640");
    ui->T_Ry->setText("0.330");

    ui->T_Gx->setText("0.290");
    ui->T_Gy->setText("0.600");

    ui->T_Bx->setText("0.150");
    ui->T_By->setText("0.060");
}

void ColorGamut::on_pushButtonREC709_clicked()
{
    SetTextBoxEnable(false);
    GamutMode = 2;
    ui->pushButtonNTSC->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonPAL->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonREC709->setStyleSheet("background-color: rgb(0, 255, 0);");
    ui->pushButtonDCIP3->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonCustom->setStyleSheet("background-color: rgb(31, 44, 61);");

    ui->T_Rx->setText("0.640");
    ui->T_Ry->setText("0.330");

    ui->T_Gx->setText("0.300");
    ui->T_Gy->setText("0.600");

    ui->T_Bx->setText("0.150");
    ui->T_By->setText("0.060");
}

void ColorGamut::on_pushButtonDCIP3_clicked()
{
    SetTextBoxEnable(false);
    GamutMode = 3;
    ui->pushButtonNTSC->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonPAL->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonREC709->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonDCIP3->setStyleSheet("background-color: rgb(0, 255, 0);");
    ui->pushButtonCustom->setStyleSheet("background-color: rgb(31, 44, 61);");

    ui->T_Rx->setText("0.680");
    ui->T_Ry->setText("0.320");

    ui->T_Gx->setText("0.265");
    ui->T_Gy->setText("0.690");

    ui->T_Bx->setText("0.150");
    ui->T_By->setText("0.060");
}

void ColorGamut::on_pushButtonCustom_clicked()
{
    ui->pushButtonNTSC->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonPAL->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonREC709->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonDCIP3->setStyleSheet("background-color: rgb(31, 44, 61);");
    ui->pushButtonCustom->setStyleSheet("background-color: rgb(0, 255, 0);");

    SetTextBoxEnable(true);
}

void ColorGamut::on_O_Rx_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->label->update();
}

void ColorGamut::on_O_Ry_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->label->update();
}

void ColorGamut::on_O_Gx_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->label->update();
}

void ColorGamut::on_O_Gy_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->label->update();
}

void ColorGamut::on_O_Bx_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->label->update();
}

void ColorGamut::on_O_By_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->label->update();
}

void ColorGamut::on_T_Rx_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->label->update();
}

void ColorGamut::on_T_Ry_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->label->update();
}

void ColorGamut::on_T_Gx_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->label->update();
}

void ColorGamut::on_T_Gy_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->label->update();
}

void ColorGamut::on_T_Bx_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->label->update();
}

void ColorGamut::on_T_By_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->label->update();
}


void ColorGamut::SolveLine(double x1, double y1, double x2, double y2,double& k,double& b)
{
    k = (y1 - y2) / (x1 - x2);
    b = (x1 * y2 - x2 * y1) / (x1 - x2);
}
/// <summary>
/// 任意两条直线，求交点
/// </summary>
/// <param name="k1"></param>
/// <param name="b1"></param>
/// <param name="k2"></param>
/// <param name="b2"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void ColorGamut::SolveIntersection(double k1, double b1, double k2, double b2, double& x, double& y)
{
    x = (b2 - b1) / (k1 - k2);
    y = (k1 * b2 - k2 * b1) / (k1 - k2);
}

double ColorGamut::solveY(double k, double b, double x)
{
    double y = k * x + b;
    return y;
}
double ColorGamut::solveX(double k, double b, double y)
{
    double x = (y - b) / k;
    return x;
}

double* ColorGamut::Matching(double OriValue[], double TarValue[])
{
    //确定直线RG
    double k1;
    double b1;
    SolveLine(OriValue[0], OriValue[1], OriValue[2], OriValue[3], k1, b1);
    //确定直线RB
    double k2;
    double b2;
    SolveLine(OriValue[0], OriValue[1], OriValue[4], OriValue[5], k2, b2);
    //确定直线GB
    double k3;
    double b3;
    SolveLine(OriValue[2], OriValue[3], OriValue[4], OriValue[5], k3, b3);

    //确定直线R`G`
    double k4;
    double b4;
    SolveLine(TarValue[0], TarValue[1], TarValue[2], TarValue[3], k4, b4);
    //确定直线R`B`
    double k5;
    double b5;
    SolveLine(TarValue[0], TarValue[1], TarValue[4], TarValue[5], k5, b5);
    //确定直线G`B`
    double k6;
    double b6;
    SolveLine(TarValue[2], TarValue[3], TarValue[4], TarValue[5], k6, b6);

    double* EndTarValue = new double[6];

    //计算Rt

    double Yr11 = solveY(k1, b1, TarValue[0]);
    double Yr12 = solveY(k2, b2, TarValue[0]);

    if ((TarValue[1] <= Yr11) && (TarValue[1] >= Yr12))
    {
        EndTarValue[0] = TarValue[0];
        EndTarValue[1] = TarValue[1];
    }
    else if ((TarValue[1] > Yr11) && (TarValue[1] < Yr12))
    {
        EndTarValue[0] = OriValue[0];
        EndTarValue[1] = OriValue[1];
    }
    else if ((TarValue[1] > Yr11) && (TarValue[1] >= Yr12))
    {
        double Xg1;
        double Yg1;
        SolveIntersection(k1, b1, k5, b5, Xg1, Yg1);
        if (Xg1 <= OriValue[0])
        {
            EndTarValue[0] = Xg1 - 0.0001;
            EndTarValue[1] = Yg1 - 0.0001;
        }
        else
        {
            EndTarValue[0] = OriValue[0];
            EndTarValue[1] = OriValue[1];
        }
    }
    else if ((TarValue[1] <= Yr11) && (TarValue[1] < Yr12))
    {
        double Xg1;
        double Yg1;
        SolveIntersection(k2, b2, k4, b4, Xg1, Yg1);
        if (Xg1 <= OriValue[0])
        {
            EndTarValue[0] = Xg1 - 0.0001;
            EndTarValue[1] = Yg1 + 0.0001;
        }
        else
        {
            EndTarValue[0] = OriValue[0];
            EndTarValue[1] = OriValue[1];
        }
    }

    //计算Gt

    double Yg11 = solveY(k1, b1, TarValue[2]);
    double Xg11 = solveX(k3, b3, TarValue[3]);

    if ((TarValue[3] <= Yg11) && (TarValue[2] >= Xg11))
    {
        EndTarValue[2] = TarValue[2];
        EndTarValue[3] = TarValue[3];
    }
    else if ((TarValue[3] > Yg11) && (TarValue[2] < Xg11))
    {
        EndTarValue[2] = OriValue[2];
        EndTarValue[3] = OriValue[3];
    }
    else if ((TarValue[3] > Yg11) && (TarValue[2] >= Xg11))
    {
        double Xg1;
        double Yg1;
        SolveIntersection(k1, b1, k6, b6, Xg1, Yg1);
        if (Xg1 >= OriValue[2])
        {
            EndTarValue[2] = Xg1;
            EndTarValue[3] = Yg1 - 0.0001;

        }
        else
        {
            EndTarValue[2] = OriValue[2];
            EndTarValue[3] = OriValue[3];
        }
    }
    else if ((TarValue[3] <= Yg11) && (TarValue[2]) < Xg11)
    {
        double Xg1;
        double Yg1;
        SolveIntersection(k3, b3, k4, b4, Xg1, Yg1);
        if (Yg1 <= OriValue[3])
        {

            EndTarValue[2] = Xg1 + 0.0001;
            EndTarValue[3] = Yg1;

        }
        else
        {
            EndTarValue[2] = OriValue[2];
            EndTarValue[3] = OriValue[3];
        }
    }

    //计算Bt

    double Yb11 = solveY(k2, b2, TarValue[4]);
    double Xb11 = solveX(k3, b3, TarValue[5]);

    if ((TarValue[5] >= Yb11) && (TarValue[4] >= Xb11))
    {
        EndTarValue[4] = TarValue[4];
        EndTarValue[5] = TarValue[5];
    }
    else if ((TarValue[5] < Yb11) && (TarValue[4] < Xb11))
    {
        EndTarValue[4] = OriValue[4];
        EndTarValue[5] = OriValue[5];
    }
    else if ((TarValue[5] < Yb11) && (TarValue[4] >= Xb11))
    {
        double Xb1;
        double Yb1;
        SolveIntersection(k2, b2, k6, b6, Xb1, Yb1);
        if (Xb1 >= OriValue[4])
        {

            EndTarValue[4] = Xb1;
            EndTarValue[5] = Yb1 + 0.0001;
        }
        else
        {
            EndTarValue[4] = OriValue[4];
            EndTarValue[5] = OriValue[5];
        }
    }
    else if ((TarValue[5] >= Yb11) && (TarValue[4] < Xb11))
    {
        double Xb1;
        double Yb1;
        SolveIntersection(k3, b3, k5, b5, Xb1, Yb1);
        if (Yb1 >= OriValue[5])
        {

            EndTarValue[4] = Xb1 + 0.0001;
            EndTarValue[5] = Yb1;
        }
        else
        {
            EndTarValue[4] = OriValue[4];
            EndTarValue[5] = OriValue[5];
        }
    }


    return EndTarValue;
}

double ColorGamut::GetMianji(double value[])
{
    double mianji = (value[0] * (value[3] - value[5]) + value[2] * (value[5] - value[1]) + value[4] * (value[1] - value[3])) / 2.0;
    return mianji;
}
void ColorGamut::ShowMianji(double TarValue[], double EndValue[])
{
    double Value1 = GetMianji(TarValue);
    double Value2 = GetMianji(EndValue);

    bili = Value2 / Value1 * 100.0;

    ui->labelValue->setText(QString::number(bili,'f',2) + "%");
}
void ColorGamut::ShowLabelValue()
{
    //增加目标值自动匹配
    double OriValue[6];
    double TarValue[6];
    double* EndTarValue = new double[6];

    OriValue[0] = ui->O_Rx->text().toDouble();
    OriValue[1] = ui->O_Ry->text().toDouble();
    OriValue[2] = ui->O_Gx->text().toDouble();
    OriValue[3] = ui->O_Gy->text().toDouble();
    OriValue[4] = ui->O_Bx->text().toDouble();
    OriValue[5] = ui->O_By->text().toDouble();

    TarValue[0] = ui->T_Rx->text().toDouble();
    TarValue[1] = ui->T_Ry->text().toDouble();
    TarValue[2] = ui->T_Gx->text().toDouble();
    TarValue[3] = ui->T_Gy->text().toDouble();
    TarValue[4] = ui->T_Bx->text().toDouble();
    TarValue[5] = ui->T_By->text().toDouble();

    EndTarValue = Matching(OriValue, TarValue);
    ShowMianji(TarValue, EndTarValue);
}

void ColorGamut::SetTextBoxEnable(bool enable)
{
    ui->T_Rx->setEnabled(enable);
    ui->T_Ry->setEnabled(enable);

    ui->T_Gx->setEnabled(enable);
    ui->T_Gy->setEnabled(enable);

    ui->T_Bx->setEnabled(enable);
    ui->T_By->setEnabled(enable);

}







double* ColorGamut::CreatTargetCoefficient(double originalValue[], double targetValue[])
{
    double* coefficient = new double[6];
    //计算红色原始刺激值
    double o_RX = QString::asprintf("%.5f",originalValue[1] / originalValue[2] * originalValue[0]).toDouble();
    double o_RY = originalValue[0];
    double o_RZ = QString::asprintf("%.5f",(1 - originalValue[1] - originalValue[2]) / originalValue[2] * originalValue[0]).toDouble();

    //计算绿色原始刺激值
    double o_GX = QString::asprintf("%.5f",originalValue[4] / originalValue[5] * originalValue[3]).toDouble();
    double o_GY = originalValue[3];
    double o_GZ = QString::asprintf("%.5f",(1 - originalValue[4] - originalValue[5]) / originalValue[5] * originalValue[3]).toDouble();

    //计算蓝色原始刺激值
    double o_BX = QString::asprintf("%.5f",originalValue[7] / originalValue[8] * originalValue[6]).toDouble();
    double o_BY = originalValue[6];
    double o_BZ = QString::asprintf("%.5f",(1 - originalValue[7] - originalValue[8]) / originalValue[8] * originalValue[6]).toDouble();

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

    gr = QString::asprintf("%.5f",((a - b) * j - c * (f - g)) / (d * j + h * c)).toDouble();
    br = QString::asprintf("%.5f",(f - g + h * gr) / j).toDouble();

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

    bg = QString::asprintf("%.5f",((a - b) * h - c * (k - f)) / (d * h + c * g)).toDouble();
    rg = QString::asprintf("%.5f",(k - f + bg * g) / h).toDouble();

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

    rb = QString::asprintf("%.5f",((a - b) * h - c * (f - g)) / (d * h - c * k)).toDouble();
    gb = QString::asprintf("%.5f",(f - g - k * rb) / h).toDouble();

    coefficient[4] = rb;
    coefficient[5] = gb;
    return coefficient;

}



QByteArray ColorGamut::Junheng(double* xishu, double Rt, double Gt, double Bt)
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

    if (Rs < 0.16)
    {
        Rs = 0.16;
        Rsg = xishu[0] * 0.16;
        Rsb = xishu[1] * 0.16;
    }
    if (Rs > 1)
    {
        Rs = 1;
        Rsg = xishu[0];
        Rsb = xishu[1];
    }
    if (Gs < 0.16)
    {
        Gs = 0.16;
        Gsr = xishu[2] * 0.16;
        Gsb = xishu[3] * 0.16;
    }
    if (Gs > 1)
    {
        Gs = 1;
        Gsr = xishu[2];
        Gsb = xishu[3];
    }
    if (Bs < 0.16)
    {
        Bs = 0.16;
        Bsr = xishu[4] * 0.16;
        Bsg = xishu[5] * 0.16;
    }
    if (Bs > 1)
    {
        Bs = 1;
        Bsr = xishu[4];
        Bsg = xishu[5];
    }

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


void ColorGamut::on_pushButtonGamut_clicked()
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

    for (int i=0;i<9;i++)
    {
        o_value.push_back(originalValue[i]);
    }



    //判断是否输入目标值
    if ((ui->T_Rx->text() == "") || (ui->T_Ry->text() == ""))
    {
        UniversalInterface::MessageBoxShow(tr("输入"),tr("请输入目标值！"));
        this->setCursor(Qt::ArrowCursor);
        return;
    }
    if ((ui->T_Gx->text() == "") || (ui->T_Gy->text() == ""))
    {
        UniversalInterface::MessageBoxShow(tr("输入"),tr("请输入目标值！"));
        this->setCursor(Qt::ArrowCursor);
        return;
    }
    if ((ui->T_Bx->text() == "") || (ui->T_By->text() == ""))
    {
        UniversalInterface::MessageBoxShow(tr("输入"),tr("请输入目标值！"));
        this->setCursor(Qt::ArrowCursor);
        return;
    }

    double targetValue[6];
    targetValue[0] = ui->T_Rx->text().toDouble() * 1000;
    targetValue[1] = ui->T_Ry->text().toDouble() * 1000;
    targetValue[2] = ui->T_Gx->text().toDouble() * 1000;
    targetValue[3] = ui->T_Gy->text().toDouble() * 1000;
    targetValue[4] = ui->T_Bx->text().toDouble() * 1000;
    targetValue[5] = ui->T_By->text().toDouble() * 1000;

    for (int i=0;i<6;i++)
    {
        if (targetValue[i] > 1000)
        {
            UniversalInterface::MessageBoxShow(tr("输入"),tr("目标值输入数据有误！"));
            this->setCursor(Qt::ArrowCursor);
            return;
        }
    }

    for (int i=0;i<6;i++)
    {
        t_value.push_back(targetValue[i]);
    }


    double* coefficient = new double[6];
    coefficient = CreatTargetCoefficient(originalValue, targetValue);

    bool prob = false;

    for (int i = 0; i < 6; i++)
    {
        if (coefficient[i] < 0)
        {
            prob = true;
            break;
        }
    }

    if (prob)
    {
        //增加目标值自动匹配
        double OriValue[6];
        double TarValue[6];
        double *EndTarValue = new double[6];

        OriValue[0] = ui->O_Rx->text().toDouble();
        OriValue[1] = ui->O_Ry->text().toDouble();
        OriValue[2] = ui->O_Gx->text().toDouble();
        OriValue[3] = ui->O_Gy->text().toDouble();
        OriValue[4] = ui->O_Bx->text().toDouble();
        OriValue[5] = ui->O_By->text().toDouble();

        TarValue[0] = ui->T_Rx->text().toDouble();
        TarValue[1] = ui->T_Ry->text().toDouble();
        TarValue[2] = ui->T_Gx->text().toDouble();
        TarValue[3] = ui->T_Gy->text().toDouble();
        TarValue[4] = ui->T_Bx->text().toDouble();
        TarValue[5] = ui->T_By->text().toDouble();

        EndTarValue = Matching(OriValue, TarValue);
        ShowMianji(TarValue, EndTarValue);

        double endtarValue[6];
        for (int i=0;i<6;i++)
        {
            endtarValue[i] = EndTarValue[i] * 1000;
        }
        coefficient = CreatTargetCoefficient(originalValue, endtarValue);
    }

    for (int i=0;i<6;i++)
    {
        FirstCalibration.push_back(coefficient[i]);
    }

    QByteArray para = Junheng(coefficient, 1, 1, 1);

    for (int i = 0; i < 18; i++)
    {
        ModulePara[0x3E + i] = para[i];
    }


    switch (GamutMode)
    {
        case 0:
            ModulePara[0x5C] = ModulePara[0x5C] & 0xE3;
            ModulePara[0x5C] = ModulePara[0x5C] | 0x00;
            break;
        case 1:
            ModulePara[0x5C] = ModulePara[0x5C] & 0xE3;
            ModulePara[0x5C] = ModulePara[0x5C] | 0x06;
            break;
        case 2:
            ModulePara[0x5C] = ModulePara[0x5C] & 0xE3;
            ModulePara[0x5C] = ModulePara[0x5C] | 0x08;
            break;
        case 3:
            ModulePara[0x5C] = ModulePara[0x5C] & 0xE3;
            ModulePara[0x5C] = ModulePara[0x5C] | 0x0C;
            break;
        case 4:
            ModulePara[0x5C] = ModulePara[0x5C] & 0xE3;
            ModulePara[0x5C] = ModulePara[0x5C] | 0x10;
            break;
    }

    bool result = UniversalInterface::SendALLPara();

    this->setCursor(Qt::ArrowCursor);
    if (result)
    {
        //提示是否继续进行转换
        if(QMessageBox::Yes == QMessageBox::question(this,tr("完成"),tr("初始色域转换已完成，是否精确调整?"),QMessageBox::Yes | QMessageBox:: No))
        {
            ColorGamutCalibration *colorgamutcalibration = new ColorGamutCalibration(this);
            colorgamutcalibration->show();
        }
        else
        {
            UniversalInterface::MessageBoxShow(tr("完成"),tr("色域转换完成！"));
            this->setCursor(Qt::ArrowCursor);
            return;
        }
    }

}
