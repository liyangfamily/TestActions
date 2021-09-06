#ifndef GRAYFINEPROCESSING_H
#define GRAYFINEPROCESSING_H

#include <QWidget>

namespace Ui {
class GrayFineProcessing;
}

class GrayFineProcessing : public QWidget
{
    Q_OBJECT

public:
    explicit GrayFineProcessing(QWidget *parent = nullptr);
    ~GrayFineProcessing();

private slots:
    void on_pushButton_clicked();

    void on_CompensationRhorizontalSlider_valueChanged(int value);

    void on_CompensationGhorizontalSlider_valueChanged(int value);

    void on_CompensationBhorizontalSlider_valueChanged(int value);

    void on_LimitRhorizontalSlider_valueChanged(int value);

    void on_LimitGhorizontalSlider_valueChanged(int value);

    void on_LimitBhorizontalSlider_valueChanged(int value);

private:
    void LoadForm();








private:
    Ui::GrayFineProcessing *ui;
};

#endif // GRAYFINEPROCESSING_H
