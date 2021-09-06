#ifndef SMARTSETTING_H
#define SMARTSETTING_H

#include <QWidget>
//#include "advancedsetting.h"





namespace Ui {
class SmartSetting;
}

class SmartSetting : public QWidget
{
    Q_OBJECT


public:
    explicit SmartSetting(QWidget *parent = nullptr);
    ~SmartSetting();

private slots:


    void on_pushButton_clicked();


    void on_ImportpushButton_clicked();

    void on_NextpushButton_clicked();

public:
    void initCombobox();
    void ShowCombobox();

signals:
    void SendSignal();

public:
    void LoadPara();



//signals:
//    void sigRefreshAdvancedSettingForm();



private:
    Ui::SmartSetting *ui;
};

#endif // SMARTSETTING_H
