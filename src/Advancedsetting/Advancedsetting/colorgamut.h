#ifndef COLORGAMUT_H
#define COLORGAMUT_H

#include <QDialog>
#include <QLabel>

extern std::vector<double> FirstCalibration;
extern std::vector<double> o_value;
extern std::vector<double> t_value;



namespace Ui {
class ColorGamut;
}





class ColorGamut : public QDialog
{
    Q_OBJECT

public:
    explicit ColorGamut(QWidget *parent = nullptr);
    ~ColorGamut();

private slots:


    void LoadForm();
    void on_pushButtonRed_clicked();
    void on_pushButtonGreen_clicked();
    void on_pushButtonBlue_clicked();
    void on_pushButtonWhite_clicked();
    void on_pushButtonNormal_clicked();
    void on_pushButtonNTSC_clicked();
    void on_pushButtonPAL_clicked();
    void on_pushButtonREC709_clicked();
    void on_pushButtonDCIP3_clicked();
    void on_pushButtonCustom_clicked();

    void myDraw();
    bool eventFilter(QObject *watched, QEvent *event);

    void on_O_Rx_textChanged(const QString &arg1);
    void on_O_Ry_textChanged(const QString &arg1);
    void on_O_Gx_textChanged(const QString &arg1);
    void on_O_Gy_textChanged(const QString &arg1);
    void on_O_Bx_textChanged(const QString &arg1);
    void on_O_By_textChanged(const QString &arg1);
    void on_T_Rx_textChanged(const QString &arg1);
    void on_T_Ry_textChanged(const QString &arg1);
    void on_T_Gx_textChanged(const QString &arg1);
    void on_T_Gy_textChanged(const QString &arg1);
    void on_T_Bx_textChanged(const QString &arg1);
    void on_T_By_textChanged(const QString &arg1);

    void SolveLine(double x1, double y1, double x2, double y2,double& k,double& b);
    void SolveIntersection(double k1, double b1, double k2, double b2, double& x, double& y);
    double solveY(double k, double b, double x);
    double solveX(double k, double b, double y);

    double* CreatTargetCoefficient(double originalValue[], double targetValue[]);
    QByteArray Junheng(double* xishu, double Rt, double Gt, double Bt);

    void on_pushButtonGamut_clicked();

    double* Matching(double OriValue[], double TarValue[]);
    double GetMianji(double value[]);
    void ShowMianji(double TarValue[], double EndValue[]);
    void ShowLabelValue();
    void SetTextBoxEnable(bool enable);



private:
    int GamutMode = 0;
    double bili = 100.0;

private:
    Ui::ColorGamut *ui;
};

#endif // COLORGAMUT_H
