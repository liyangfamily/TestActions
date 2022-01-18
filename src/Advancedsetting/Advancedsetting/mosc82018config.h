#ifndef MOSC82018CONFIG_H
#define MOSC82018CONFIG_H

#include <QDialog>

namespace Ui {
class MOSC82018config;
}

class MOSC82018config : public QDialog
{
    Q_OBJECT

public:
    explicit MOSC82018config(QWidget *parent = nullptr);
    ~MOSC82018config();

private slots:
    void LoadForm();
    void on_pushButton_clicked();

    void on_ShadowingModespinBox_valueChanged(int arg1);

    void on_ShadowingVoltagespinBox_valueChanged(int arg1);


    void on_ValuespinBox_valueChanged(int arg1);

private:
    bool showinfo = false;


private:
    Ui::MOSC82018config *ui;
};

#endif // MOSC82018CONFIG_H
