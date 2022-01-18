#ifndef SMARTSETTING_H
#define SMARTSETTING_H

#include <QDialog>
//#include "advancedsetting.h"
#include <LAPIControl>




namespace Ui {
class SmartSetting;
}

class SmartSetting : public QDialog
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
    QByteArray CreateDefaultTableXian();

signals:
    void SendSignal();

public:
    void LoadPara();
    void WriteScan(int Regnum, int ByteCount, int StartByte);
     void WriteScan5353();

private:
    //DCLK/TXD 指驱动芯片通道数16，目前默认为16，后续需要根据驱动芯片类型自动取值；
    uchar channelCount = 16;
    //指驱动芯片需要传输的单像素点bit数据，目前默认为16后续需要根据驱动芯片类型自动取值；
    uchar bitCount = 16;
    //指当前视频源帧频 60
    uchar FrameRate = 60;
    //一组数据芯片数
    uchar cn = 0;
    //描点文件类型
    int m_upgradeType = LBLFileTransferPackage::EFileType::EFT_LinearTableFile;





//signals:
//    void sigRefreshAdvancedSettingForm();



private:
    Ui::SmartSetting *ui;
};

#endif // SMARTSETTING_H
