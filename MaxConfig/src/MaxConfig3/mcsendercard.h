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

	void on_btnSwitchBypass_clicked();
	void on_btnSwitch3_0Sys_clicked();
	void on_btnSwitchBlackScreen_clicked();
	void on_btnSwitchLockScreen_clicked();
	void on_btnSwitchErrorBitRateClean_clicked();
	void on_btnSwitchCorrect_clicked();
	void on_btnSwitchSCS_clicked();
	void on_btnSwitch24BitGamma_clicked();
	void on_btnSwitchZoomMode_clicked();
	void on_btnZoomSizeSend_clicked();

	void on_btnRegRead_clicked();
	void on_btnRegWrite_clicked();
};

#endif // MCSENDERCARD_H
