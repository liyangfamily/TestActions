#include "frmandroidtest.h"
#include "ui_frmandroidtest.h"
#include "quiwidget.h"
#include <QMessageBox>

#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LAPI_Controld.lib")
#else
#pragma comment(lib,"LAPI_Control.lib")
#endif // QT_DEBUG
#endif

frmandroidtest::frmandroidtest(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::frmandroidtest();
	ui->setupUi(this);

	ui->radioBtn_Eth1->setChecked(true);
	ui->btn_RelaySwitch->setCheckable(true);
	ui->btn_WIFITest->setCheckable(true);
	ui->btn_EnterKeyTest->setCheckable(true);
}

frmandroidtest::~frmandroidtest()
{
	delete ui;
}

void frmandroidtest::on_btn_DevNameRead_clicked()
{
	LAPI::ReadDeviceName(true);
	ui->lineEdit_DevName->setText(LAPI::GetDeviceName());
	ui->textBrowser->append(QString("设备名:%1.").arg(LAPI::GetDeviceName()));
}

void frmandroidtest::on_btn_DevNameWrite_clicked()
{
	QString name = ui->lineEdit_DevName->text();
	LAPI::EResult ret = LAPI::WriteDeviceName(name, true);
	QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), \
		ret == LAPI::ER_INTECTRL_Success ? QString::fromLocal8Bit("成功") : QString::fromLocal8Bit("失败"), QMessageBox::Yes, QMessageBox::Yes);
}

void frmandroidtest::on_btn_DevOnlineStatus_clicked()
{
	QString ip = ui->lineEdit_DevOnlinStatus->text();
	if (!LBLUIHelper::isIP(ip)) {
		QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), \
			QString::fromLocal8Bit("IP地址错误"), QMessageBox::Yes, QMessageBox::Yes);
	}
    LAPI::ReadNetDeviceOnlineStatus(ip, true);
	ui->textBrowser->append(QString("检测设备IP:%1, 状态：%2.").arg(LAPI::GetNetDevice_IP()).arg(1 == LAPI::GetNetDevice_Status() ? "已连接" : "未连接"));
}

void frmandroidtest::on_radioBtn_Eth1_clicked()
{
	ui->radioBtn_Eth2->setChecked(false);
	ui->radioBtn_Eth1->setChecked(true);
}

void frmandroidtest::on_radioBtn_Eth2_clicked()
{
	ui->radioBtn_Eth2->setChecked(true);
	ui->radioBtn_Eth1->setChecked(false);
}

void frmandroidtest::on_btn_SetMACAddr_clicked()
{
	QString mac = ui->lineEdit_MACAddr->text();
	if (!LBLUIHelper::isMac(mac)) {
		QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), \
			QString::fromLocal8Bit("MAC地址错误"), QMessageBox::Yes, QMessageBox::Yes);
	}
	mac = mac.replace("-", "");
	quint8 flage = ui->radioBtn_Eth1->isChecked() ? 1 : 2;
    LAPI::WriteNetworkCardMACAddr(flage, QByteArray::fromHex(mac.toLocal8Bit()), true);
	QString temp = "";
	QString hex = LAPI::GetNetworkCardMACAddr_MAC().toHex();
	for (int i = 0; i < hex.length(); i = i + 2) {
		temp += hex.mid(i, 2) + " ";
	}
    temp = temp.trimmed().toUpper();

	ui->textBrowser->append(QString("%1MAC地址：%2, 结果：%3.").arg(ui->radioBtn_Eth1->isChecked() ? "Eth1" : "Eth2") \
		.arg(temp).arg(1 == LAPI::GetNetworkCardMACAddr_Results() ? "成功" : "失败"));
}

void frmandroidtest::on_btn_EnterTest_clicked()
{
    LAPI::WriteEnterTestMode("StartSender2PlusFactoryTest", true);
	ui->textBrowser->append(QString("进入工厂测试：%1.\n").arg(1 == LAPI::GetEnterTestMode_Results() ? "成功" : "失败"));
}

void frmandroidtest::on_btn_EthLoopTest_clicked()
{
    LAPI::ReadSCEthLoopTestResult(true);
	/*ui->textBrowser->append(QString("发送卡网口自回环测试：%1 , 有效网口数：%2 , 附加内容：%3.")\
		.arg(1 == LAPI::GetSCEthLoopTest_Result() ? "成功" : "失败")\
		.arg(LAPI::GetSCEthLoopTest_EffectiveEthCount())\
		.arg(QUIHelper::byteArrayToHexStr(LAPI::GetSCEthLoopTest_ReplyData())));*/
	ui->textBrowser->append(QString("发送卡网口自回环测试：有效网口数：%1.")\
		.arg(LAPI::GetSCEthLoopTest_EffectiveEthCount()));
	QMap<quint8, float> tempMap = LAPI::GetSCEthLoopTest_BitErrRate();
	for (auto i = tempMap.cbegin(); i != tempMap.cend(); ++i) {
		QString errRate;
		if (i.value() > 0.01) {
			errRate = "<font color=\"#FF0000\">" + QString::number(i.value(), 'f', 6) + "</font> ";
		}
		else {
			errRate = QString::number(i.value(), 'f', 6);
		}
		ui->textBrowser->append(QString("网口：%1 , 误码率：%2.")\
			.arg(i.key())\
			.arg(errRate));
	}
}

void frmandroidtest::on_btn_ReadUDiskStatus_clicked()
{
    LAPI::ReadUDiskMountingStatus(true);
	ui->textBrowser->append(QString("U盘挂载数量：%1.").arg(LAPI::GetUDiskMounting_Count()));
	for (auto i : LAPI::GetUDiskMounting_List()) {
		ui->textBrowser->append(i);
	}
}

void frmandroidtest::on_btn_OSDTest_clicked()
{
    LAPI::WriteStartOSDTest(true);
	ui->textBrowser->append(QString("白屏测试结果：%1.").arg(1 == LAPI::GetOSDTest_WhiteScreenTestResult() ? "成功" : "失败"));
	ui->textBrowser->append(QString("黑屏测试结果：%1.").arg(1 == LAPI::GetOSDTest_BlackScreenTestResult() ? "成功" : "失败"));
}

void frmandroidtest::on_btn_RelaySwitch_clicked()
{
	if (ui->btn_RelaySwitch->isChecked()) {
		ui->btn_RelaySwitch->setText("继电器关");
        LAPI::WriteRelaySwitc(1, true);
		ui->textBrowser->append(QString("继电器开：%1.").arg(1 == LAPI::GetRelaySwitc_Result() ? "成功" : "失败"));
	}
	else {
		ui->btn_RelaySwitch->setText("继电器开");
        LAPI::WriteRelaySwitc(2, true);
		ui->textBrowser->append(QString("继电器关：%1.").arg(1 == LAPI::GetRelaySwitc_Result() ? "成功" : "失败"));
	}
}

void frmandroidtest::on_btn_OpticalSensorParam_clicked()
{
    LAPI::ReadOpticalSensorParam(true);
	ui->textBrowser->append(QString("感光元件参数：%1.").arg(LAPI::GetOpticalSensor_Param()));
}

void frmandroidtest::on_btn_ReadRouterStatus_clicked()
{
    LAPI::ReadRouterStatus(true);
	ui->textBrowser->append(QString("5GWiFi：%1.").arg(1 == LAPI::GetRouter_5GWifiStatus() ? "开启" : "关闭"));
	ui->textBrowser->append(QString("2.4GWiFi：%1.").arg(1 == LAPI::GetRouter_2_4GWifiStatus() ? "开启" : "关闭"));
}

void frmandroidtest::on_btn_WIFITest_clicked()
{
	if (ui->btn_WIFITest->isChecked()) {
		ui->btn_WIFITest->setText("WiFi扫描关闭");
        LAPI::WriteWIFIModuleScanTest(1, true);
		ui->textBrowser->append(QString("WiFi扫描开启：%1.").arg(1 == LAPI::GetWIFIModuleScanTest_Results() ? "成功" : "失败"));
	}
	else {
		ui->btn_WIFITest->setText("WiFi扫描开启");
        LAPI::WriteWIFIModuleScanTest(2, true);
		ui->textBrowser->append(QString("WiFi扫描关闭：%1.").arg(1 == LAPI::GetWIFIModuleScanTest_Results() ? "成功" : "失败"));
	}
}

void frmandroidtest::on_btn_ReadWIFIList_clicked()
{
    LAPI::ReadWIFIScanList(true);
	ui->textBrowser->append(QString("扫描到的WiFi数量：%1.").arg(LAPI::GetWIFIScanList_Count()));
}

void frmandroidtest::on_btn_EnterKeyTest_clicked()
{
	if (ui->btn_EnterKeyTest->isChecked()) {
		ui->btn_EnterKeyTest->setText("停止按键测试");
		LAPI::EResult ret = LAPI::WriteEnterKeyTest(1, true);
		if (LAPI::EResult::ER_INTECTRL_Success != ret) {
			ui->textBrowser->append(QString("开始按键测试失败."));
			return;
		}
		ui->textBrowser->append(QString("开始按键测试：%1.").arg(1 == LAPI::GetKeyTest_Result() ? "成功" : "失败"));
	}
	else {
		ui->btn_EnterKeyTest->setText("开始按键测试");
		LAPI::EResult ret = LAPI::WriteEnterKeyTest(2, true);
		if (LAPI::EResult::ER_INTECTRL_Success != ret) {
			ui->textBrowser->append(QString("停止按键测试失败."));
			return;
		}
		ui->textBrowser->append(QString("停止按键测试：%1.").arg(2 == LAPI::GetKeyTest_Result() ? "成功" : "失败"));
	}
}

void frmandroidtest::on_btn_ReadKeyTestStatus_clicked()
{
	LAPI::EResult ret = LAPI::ReadKeyTestResult(true);
	if (LAPI::EResult::ER_INTECTRL_Success != ret) {
		ui->textBrowser->append(QString("读取按键测试结果失败."));
		return;
	}
	ui->textBrowser->append(QString("按键测试收到的数据长度：%1.").arg(LAPI::GetKeyTestResult_Count()));
	for (auto i : LAPI::GetKeyTestResult_List()) {
		ui->textBrowser->append(QString::number(i));
	}
}
