#ifndef MCSENDERCARD_H
#define MCSENDERCARD_H

#include <QWidget>
#include <LAPIControl>

namespace Ui {
class MCSenderCard;
}

class MCSenderCard : public QWidget
{
    Q_OBJECT

public:
    explicit MCSenderCard(QWidget *parent = nullptr);
    ~MCSenderCard();

private:
    Ui::MCSenderCard *ui;

protected:
    bool event(QEvent* e) override;
private:
    void cleanSenderCardWidget();
    void updateSenderCard();
    void showZoomModeDetails(bool b);
    void setSenderCardTestMode(LAPI::UI::EPictureTestMode mode);
public slots:
    void slot_ConnectItem();
    void slot_EnterNavigatPage();
private slots:
    void on_btnTestNormal_clicked();
    void on_btnTestRed_clicked();
    void on_btnTestGreen_clicked();
    void on_btnTestBlue_clicked();
    void on_btnTestWhite_clicked();
    void on_btnTestBlack_clicked();
    void on_btnTestLeftSlash_clicked();
    void on_btnTestRightSlash_clicked();
    void on_btnTestHorizontalSlash_clicked();
    void on_btnTestVerticalSlash_clicked();
    void on_btnTestGradientRed_clicked();
    void on_btnTestGradientGreen_clicked();
    void on_btnTestGradientBlue_clicked();
    void on_btnTestGradientWhite_clicked();

    void on_btnSwitchBypass_clicked();
    void on_btnSwitch3_0Sys_clicked();
    void on_btnSwitchBlackScreen_clicked();
    void on_btnSwitchLockScreen_clicked();
    void on_btnSwitchErrorBitRateClean_clicked();
    void on_btnSwitchCorrect_clicked();
    void on_btnSwitchSCS_clicked();
    void on_btnSwitch24BitGamma_clicked();
    void on_btn10bitSource_clicked();
    void on_btnLowDelay_clicked();
    void on_btnSwitchZoomMode_clicked();
    void on_btnZoomSizeSend_clicked();

    void slot_comboBoxNT68400Resolutions_IndexChanged(int d);

    void on_btnRegRead_clicked();
    void on_btnRegWrite_clicked();
    void on_CutoutSetpushButton_clicked();
};

#endif // MCSENDERCARD_H
