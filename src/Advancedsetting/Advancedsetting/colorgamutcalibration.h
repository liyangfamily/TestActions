#ifndef COLORGAMUTCALIBRATION_H
#define COLORGAMUTCALIBRATION_H

#include <QDialog>

namespace Ui {
class ColorGamutCalibration;
}

class ColorGamutCalibration : public QDialog
{
    Q_OBJECT

public:
    explicit ColorGamutCalibration(QWidget *parent = nullptr);
    ~ColorGamutCalibration();

private slots:
    void on_pushButtonR_clicked();

    void on_pushButtonG_clicked();

    void on_pushButtonB_clicked();

    void on_pushButtonConfig_clicked();

    QByteArray Junheng(double* xishu, double Rt, double Gt, double Bt);

    double* CreatTargetCoefficient(double originalValue[], double targetValue[]);

private:
    Ui::ColorGamutCalibration *ui;
};

#endif // COLORGAMUTCALIBRATION_H
