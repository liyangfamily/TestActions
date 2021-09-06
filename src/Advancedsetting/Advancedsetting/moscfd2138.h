#ifndef MOSCFD2138_H
#define MOSCFD2138_H

#include <QWidget>

namespace Ui {
class MOSCFD2138;
}

class MOSCFD2138 : public QWidget
{
    Q_OBJECT

public:
    explicit MOSCFD2138(QWidget *parent = nullptr);
    ~MOSCFD2138();

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
    Ui::MOSCFD2138 *ui;
};

#endif // MOSCFD2138_H
