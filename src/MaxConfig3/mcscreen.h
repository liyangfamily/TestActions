#ifndef MCSCREEN_H
#define MCSCREEN_H

#include <QWidget>
#include <LBL_Advanved/Advancedsetting>

namespace Ui {
class mcScreen;
}
class MCMS9570AdvSetting;
class MCNT68400AdvSetting;
class MCScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MCScreen(QWidget *parent = nullptr);
    ~MCScreen();

private:
    Ui::mcScreen *ui;

protected:
    bool event(QEvent* e) override;
private:
    void initSliderAndSpinBoxSignal();
    void cleanScreenWidget();
    void updateScreen();

    quint16 onParseReadBrightness(const QByteArray& data);
    quint16 onParseReadVideoSource(quint8 source);
    quint16 onParseSourceColortemperature(const QByteArray& data);
    quint16 onParseReadMCUAppVersion(const QByteArray& data);
    quint16 onParseReadMCUBootVersion(const QByteArray& data);
    quint16 onParseReadAndroidVersion(const QByteArray& data);
    quint16 onParseReadSCFPGARegister(const QByteArray& data);
    AdvancedSetting *advancedsetting=nullptr;
    MCNT68400AdvSetting *m_nt68400advSetDlg=nullptr;
    MCMS9570AdvSetting* m_ms9570advSetDlg=nullptr;
public slots:
    void slot_ConnectItem();
    void slot_EnterNavigatPage();
private slots:
    void slot_BrightnessValueChanged(int value);
    void on_radioBtnHDMI1_clicked();
    void on_radioBtnHDMI2_clicked();
    void on_radioBtnHDMI3_clicked();
    void on_radioBtnAndroid_clicked();
    void on_radioBtnPC_clicked();
    void on_radioBtnDP_clicked();

    void on_radioBtnWarm_clicked();
    void on_radioBtnNormal_clicked();
    void on_radioBtnCool_clicked();
    void on_radioBtnCCT_toggled(bool checked);
    void on_radioBtnRGB_toggled(bool checked);
    void on_radioBtnRGB_clicked();
    void on_btnModuleParam_clicked();
    void on_btnVideoSetting_clicked();
};

#endif // MCSCREEN_H
