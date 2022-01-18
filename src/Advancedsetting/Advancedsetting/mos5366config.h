#ifndef MOS5366CONFIG_H
#define MOS5366CONFIG_H

#include <QDialog>

namespace Ui {
class MOS5366config;
}

class MOS5366config : public QDialog
{
    Q_OBJECT

public:
    explicit MOS5366config(QWidget *parent = nullptr);
    ~MOS5366config();


private slots:
    void on_ShadowingModespinBox_valueChanged(int arg1);

    void on_ShadowingVoltagespinBox_valueChanged(int arg1);

    void on_ValuespinBox_valueChanged(int arg1);

    void on_SettingpushButton_clicked();

private:
    bool showinfo = false;





private:
    void LoadForm();











private:
    Ui::MOS5366config *ui;
};

#endif // MOS5366CONFIG_H
