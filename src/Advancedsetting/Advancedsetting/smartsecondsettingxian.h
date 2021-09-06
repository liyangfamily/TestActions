#ifndef SMARTSECONDSETTINGXIAN_H
#define SMARTSECONDSETTINGXIAN_H

#include <QWidget>
#include "form.h"
#include <LAPIControl>

namespace Ui {
class SmartSecondSettingXian;
}

class SmartSecondSettingXian : public QWidget
{
    Q_OBJECT

public:
    explicit SmartSecondSettingXian(QWidget *parent = nullptr);
    ~SmartSecondSettingXian();

private slots:
    void on_EmptypushButton_clicked();
    void on_RevokepushButton_clicked();
    void on_ClearpushButton_clicked();
    void on_FinishpushButton_clicked();
    void on_ExportpushButton_clicked();
    void TimerSetPicture1();
    void TimerSetPicture2();
    void update();
    void on_tableWidget_itemSelectionChanged();
    void GetTable();
    void closeEvent(QCloseEvent * e );

private:
    Ui::SmartSecondSettingXian *ui;

private:
    int Col = 0;
    int Row = 0;
    int Index = 1;
    int Colindex = 1;
    QByteArray XAPara;
    Form wf;
    //屏幕信息
    int ScreenX = 0;
    int ScreenY = 0;
    int ScreenWidth = 1;
    int ScreenHeight = 1;
    int xend = 0;
    bool Sign = true;
    QTimer *timer;
    int m_upgradeType = LBLFileTransferPackage::EFileType::EFT_LinearTableFile;

private:
    void InitForm();


signals:
    void SendSignal2();
    void SendSignal1();


};

#endif // SMARTSECONDSETTINGXIAN_H
