#ifndef SCANPARAMATER_H
#define SCANPARAMATER_H

#include <QWidget>

namespace Ui {
class Scanparamater;
}

class Scanparamater : public QWidget
{
    Q_OBJECT

public:
    explicit Scanparamater(QWidget *parent = nullptr);
    ~Scanparamater();

private slots:


    void on_Setting_clicked();

    void on_ScanCountspinBox_valueChanged(int arg1);

private:
    void InitForm();
    void LoadForm();






private:
    Ui::Scanparamater *ui;
};

#endif // SCANPARAMATER_H
