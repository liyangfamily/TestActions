#ifndef MOSCFD2138_H
#define MOSCFD2138_H

#include <QDialog>

namespace Ui {
class MOSCFD2138config;
}

class MOSCFD2138config : public QDialog
{
    Q_OBJECT

public:
    explicit MOSCFD2138config(QWidget *parent = nullptr);
    ~MOSCFD2138config();

private slots:
    void on_ShadowingModespinBox_valueChanged(int arg1);

    void on_ShadowingVoltagespinBox_valueChanged(int arg1);

    void on_ValuespinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    bool showinfo = false;




private:
    void LoadPara();


private:
    Ui::MOSCFD2138config *ui;
};

#endif // MOSCFD2138_H
