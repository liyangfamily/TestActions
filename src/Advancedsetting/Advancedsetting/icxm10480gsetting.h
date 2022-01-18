﻿#ifndef ICXM10480GSETTING_H
#define ICXM10480GSETTING_H

#include <QDialog>

namespace Ui {
class ICXM10480GSetting;
}

class ICXM10480GSetting : public QDialog
{
    Q_OBJECT

public:
    explicit ICXM10480GSetting(QWidget *parent = nullptr);
    ~ICXM10480GSetting();

public:

    void SetRegValue(int Num, int value);
    unsigned char GetRegValue(int Num);
    QByteArray ReadFile(QString filepath);
    bool WriteFile(QString filepath,QByteArray array);
    void Writebin(QString path, QByteArray bytes);
    QByteArray Readbin(QString path);
    void Loadformpara();
    QByteArray ReadGamdat(QString filepath);
    //void MessageBoxShow(QString title,QString str);
    QString filename;
    void SetGlobalReg();
    void GetGlobalReg();

public:
    QByteArray regpara;

private slots:
    void on_SettingBtn_clicked();

    void on_PresetApushButton_clicked();

    void on_PresetBpushButton_clicked();

    void on_PresetCpushButton_clicked();

    void on_PresetDpushButton_clicked();

    void on_CurrentRegulation1RspinBox_valueChanged(int arg1);

    void on_CurrentRegulation2RspinBox_valueChanged(int arg1);

    void on_CurrentGainRspinBox_valueChanged(int arg1);

    void on_CurrentRegulation1GspinBox_valueChanged(int arg1);

    void on_CurrentRegulation2GspinBox_valueChanged(int arg1);

    void on_CurrentGainGspinBox_valueChanged(int arg1);

    void on_CurrentRegulation1BspinBox_valueChanged(int arg1);

    void on_CurrentRegulation2BspinBox_valueChanged(int arg1);

    void on_CurrentGainBspinBox_valueChanged(int arg1);

    void on_RefreshRatelspinBox_valueChanged(int arg1);

    void on_SaveFilepushButton_clicked();

    void on_LoadFilepushButton_clicked();

    void on_AdvancedSettingpushButton_clicked();

    void on_pushButton_clicked();

    void on_ReadBackpushButton_clicked();

    void GetFormValue();

    void on_UseDefectDetectioncheckBox_clicked();

private:
    Ui::ICXM10480GSetting *ui;
};

#endif // ICXM11202GSETTING_H
