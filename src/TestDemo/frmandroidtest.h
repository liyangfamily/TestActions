#pragma once

#include <QWidget>
#include <LAPIControl>

namespace Ui { class frmandroidtest; };

class frmandroidtest : public QWidget
{
	Q_OBJECT

public:
	frmandroidtest(QWidget *parent = Q_NULLPTR);
	~frmandroidtest();

private:
	Ui::frmandroidtest *ui;

private slots:
	void on_btn_DevNameRead_clicked();
	void on_btn_DevNameWrite_clicked();
	void on_btn_DevOnlineStatus_clicked();
	void on_radioBtn_Eth1_clicked();
	void on_radioBtn_Eth2_clicked();
	void on_btn_SetMACAddr_clicked();
	void on_btn_EnterTest_clicked();
	void on_btn_EthLoopTest_clicked();
	void on_btn_ReadUDiskStatus_clicked();
	void on_btn_OSDTest_clicked();
	void on_btn_RelaySwitch_clicked();
	void on_btn_OpticalSensorParam_clicked();
	void on_btn_ReadRouterStatus_clicked();
	void on_btn_WIFITest_clicked();
	void on_btn_ReadWIFIList_clicked();
	void on_btn_EnterKeyTest_clicked();
	void on_btn_ReadKeyTestStatus_clicked();
};
