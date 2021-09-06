#ifndef ICADVANCEDSETTING_H
#define ICADVANCEDSETTING_H

#include <QWidget>
#include <QSpinBox>

namespace Ui {
class ICAdvancedSetting;
}

class ICAdvancedSetting : public QWidget
{
    Q_OBJECT

public:
    explicit ICAdvancedSetting(QWidget *parent = nullptr);
    ~ICAdvancedSetting();

private slots:
    void on_pushButton_clicked();

private:
    void Showic();
    void LoadForm();
    void SetspinBox();
    void ShowCount(int Num);

private:
    QSpinBox *spinbox[48];









private:
    Ui::ICAdvancedSetting *ui;
};

#endif // ICADVANCEDSETTING_H
