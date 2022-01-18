#ifndef FLASHSETTING_H
#define FLASHSETTING_H

#include <QDialog>

namespace Ui {
class FLASHsetting;
}

class FLASHsetting : public QDialog
{
    Q_OBJECT

public:
    explicit FLASHsetting(QWidget *parent = nullptr);
    ~FLASHsetting();

private slots:
    void on_FLASHSumCountspinBox_valueChanged(int arg1);

    void on_FLASHSetting_clicked();

private:
    void InitForm();
    void LoadForm();













private:
    Ui::FLASHsetting *ui;
};

#endif // FLASHSETTING_H
