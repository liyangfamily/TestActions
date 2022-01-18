#ifndef MOSICND2018CONFIG_H
#define MOSICND2018CONFIG_H

#include <QDialog>

namespace Ui {
class MOSICND2018config;
}

class MOSICND2018config : public QDialog
{
    Q_OBJECT

public:
    explicit MOSICND2018config(QWidget *parent = nullptr);
    ~MOSICND2018config();

private slots:
    void on_ShadowingModespinBox_valueChanged(int arg1);

    void on_ShadowingVoltagespinBox_valueChanged(double arg1);

    void on_ValuespinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    bool showinfo = false;
    void LoadForm();


private:
    Ui::MOSICND2018config *ui;
};

#endif // MOSICND2018CONFIG_H
