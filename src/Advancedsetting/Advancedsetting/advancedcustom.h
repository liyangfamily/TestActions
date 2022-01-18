#ifndef ADVANCEDCUSTOM_H
#define ADVANCEDCUSTOM_H

//#include <QWidget>
#include <QDialog>

namespace Ui {
class AdvancedCustom;
}

class AdvancedCustom : public QDialog
{
    Q_OBJECT

public:
    explicit AdvancedCustom(QWidget *parent = nullptr);
    ~AdvancedCustom();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::AdvancedCustom *ui;

private:
    void InitForm();
    void LordForm();


};

#endif // ADVANCEDCUSTOM_H
