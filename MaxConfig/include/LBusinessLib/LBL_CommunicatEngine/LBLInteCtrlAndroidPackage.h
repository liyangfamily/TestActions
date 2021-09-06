#pragma once
#include "LBL_CommunicatEngine/LBLInteCtrlPackage.h"

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidVersionNum : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidVersionNum, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_ReadAndroidVersionNum(quint64 versionType);
	quint64 getVersionType() const;
	QByteArray getReplyData()const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidVersion);
	}
	QByteArray CmdContent() const override;
private:
	quint64 m_versionType = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidNetInfo : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidNetInfo, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_ReadAndroidNetInfo(quint8 communicatType);

	QString getDeviceName() const;
	quint64 getRandomCode() const;
	quint8  getCommunicatType() const;

	quint8  getWirelessIPMode() const;
	QString getWirelessIP() const;
	QString getWirelessSubnetMask() const;
	QString getWirelessGateway() const;
	QString getWirelessDNS1() const;
	QString getWirelessDNS2() const;

	quint8  getWireIPMode() const;
	QString getWireIP() const;
	QString getWireSubnetMask() const;
	QString getWireGateway() const;
	QString getWireDNS1() const;
	QString getWireDNS2() const;

	void  setReadCommunicatType(quint8 type) {
		m_type = type;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidIPInfo);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_type, 1);
	}
private:
	quint8 m_type = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteAndroidNetInfo : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteAndroidNetInfo, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteAndroidNetInfo(quint64 randomCode, quint8 communicatType, quint8 ipMode);
	void setRandomCode(quint64 value) {
		m_randomCode = value;
	}
	void setCommunicatType(quint8 value) {
		m_type = value;
	}
	void setIPMode(quint8 value) {
		m_ipMode = value;
	}
	void setIP(QString value) {
		m_ip = value;
	}
	void setSubnetMask(QString value) {
		m_subnetMask = value;
	}
	void setGateway(QString value) {
		m_gateway = value;
	}
	void setDNS1(QString value) {
		m_dns1 = value;
	}
	void setDNS2(QString value) {
		m_dns2 = value;
	}

	quint16 getOperationResult() const;
	quint64 getRandomCode() const;
	quint8  getCommunicatType() const;

	quint8  getIPMode() const;
	QString getIP() const;
	QString getSubnetMask() const;
	QString getGateway() const;
	QString getDNS1() const;
	QString getDNS2() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_AndroidIPInfo);
	}
	QByteArray CmdContent() const override;
private:
	quint64 m_randomCode = 0;
	quint8 m_type = 0;
	quint8 m_ipMode = 0;
	QString m_ip;
	QString m_subnetMask;
	QString m_gateway;
	QString m_dns1;
	QString m_dns2;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidNoSleep : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidNoSleep, LBLInteCtrlPackage)
public:
	quint8 getNoSleep() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidDoNotSleep);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteAndroidNoSleep : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteAndroidNoSleep, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteAndroidNoSleep(quint8 value);
	quint16 getOperationResult() const;
	void  setNoSleep(quint8 value) {
		m_NoSleep = value;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_AndroidDoNotSleep);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_NoSleep, 1);
	}
private:
	quint8 m_NoSleep = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidHotInfo : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidHotInfo, LBLInteCtrlPackage)
public:
	quint8  getStatus() const;
	quint8  is5G() const;
	quint8  isEncryption() const;

	QString getSSID() const;
	QString getPSW() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidHotInfo);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteAndroidKeyEvent : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteAndroidKeyEvent, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteAndroidKeyEvent(quint8 status, quint16 keyCode);
	void setStatus(quint8 value) {
		m_status = value;
	}
	void setKeyCode(quint16 keyCode) {
		m_keyCode = keyCode;
	}

	quint16 getOperationResult() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_AndroidKeyEvent);
	}
	QByteArray CmdContent() const override;

private:
	quint8 m_status = 0;
	quint16 m_keyCode = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidDeviceName : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidDeviceName, LBLInteCtrlPackage)
public:
	QString getDeviceName() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidDeviceName);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteAndroidDeviceName : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteAndroidDeviceName, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteAndroidDeviceName(QString value);
	void SetDeviceName(QString value) {
		m_name = value;
	}
	quint16 getOperationResult() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_AndroidDeviceName);
	}
	QByteArray CmdContent() const override;

private:
	QString m_name;
};


/*********************************************************************************************************
**Android 测试相关方案                                                                     
*********************************************************************************************************/

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidNetDeviceOnlineStatus : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidNetDeviceOnlineStatus, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_ReadAndroidNetDeviceOnlineStatus(QString value);
	void setIP(QString value) {
		m_ip = value;
	}
	quint16 getOperationResult() const;
	QString getIP() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidNetDeviceOnlineStatus);
	}
	QByteArray CmdContent() const override;
private:
	QString m_ip;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidSCEthLoopTestResult : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidSCEthLoopTestResult, LBLInteCtrlPackage)
public:
	quint16 getOperationResult() const;
	quint8  getEffectiveEthCount() const;
	QByteArray getReplyData() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidSCEthLoopTestResults);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidUDiskMountingStatus : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidUDiskMountingStatus, LBLInteCtrlPackage)
public:
	quint8  getUDiskCount() const;
	QStringList getUDiskNameList() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_AndroidUDiskMountingStatus);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteAndroidStartOSDTest : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteAndroidStartOSDTest, LBLInteCtrlPackage)
public:
	quint8  getWhiteScreenTestResult() const;
	quint8  getBlackScreenTestResult() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_AndroidStatOSDTest);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteAndroidRelaySwitc : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteAndroidRelaySwitc, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteAndroidRelaySwitc(quint8 value);
	void setStatus(quint8 value) {
		m_status = value;
	}

	quint16 getOperationResult() const;
	quint8  getStatus() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_AndroidRelaySwitc);
	}
	QByteArray CmdContent() const override;
private:
	quint8 m_status;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteAndroidEnterKeyTest : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteAndroidEnterKeyTest, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteAndroidEnterKeyTest(quint8 value);
	void setStatus(quint8 value) {
		m_status = value;
	}

	quint8 getResult() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_AndroidEnterKeyTest);
	}
	QByteArray CmdContent() const override;
private:
	quint8 m_status;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidKeyTestResult : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidKeyTestResult, LBLInteCtrlPackage)
public:

	quint8 getKeyCount() const;
	QList<quint16> getResultList() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidKeyTestResult);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidOpticalSensorParam : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidOpticalSensorParam, LBLInteCtrlPackage)
public:

	quint16 getParam() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidOpticalSensorParam);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidRouterStatus : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidRouterStatus, LBLInteCtrlPackage)
public:

	quint8 get5GWifiStatus() const;
	quint8 get2_4GWifiStatus() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidRouterStatus);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteAndroidNetworkCardMACAddr : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteAndroidNetworkCardMACAddr, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteAndroidNetworkCardMACAddr(quint8 flage, QByteArray mac);
	void setFlage(quint8 value) {
		m_flage = value;
	}
	void setMAC(QByteArray value) {
		m_mac = value;
	}

	quint16 getOperationResult() const;
	quint8 getFlage() const;
	QByteArray getMAC() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_AndroidNetworkCardMACAddr);
	}
	QByteArray CmdContent() const override;
private:
	quint8 m_flage;
	QByteArray m_mac;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteAndroidPalyTestSound_1KHZ : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteAndroidPalyTestSound_1KHZ, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteAndroidPalyTestSound_1KHZ(quint8 value);
	void setStatus(quint8 value) {
		m_status = value;
	}
	quint16 getOperationResult() const;
	quint8 getStatus() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_AndroidPalyTestSound_1KHZ);
	}
	QByteArray CmdContent() const override;
private:
	quint8 m_status;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteAndroidWIFIModuleScanTest : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteAndroidWIFIModuleScanTest, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteAndroidWIFIModuleScanTest(quint8 value);
	void setStatus(quint8 value) {
		m_status = value;
	}
	quint16 getOperationResult() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_AndroidWIFIModuleScanTest);
	}
	QByteArray CmdContent() const override;
private:
	quint8 m_status;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidWIFIScanList : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidWIFIScanList, LBLInteCtrlPackage)
public:

	quint8 getListCount() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidWIFIScanList);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidLoadPowerAmplifierChipParam : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidLoadPowerAmplifierChipParam, LBLInteCtrlPackage)
public:

	quint16 getOperationResult() const;
	quint8 getPowerAmplifierChip30Result() const;
	quint8 getPowerAmplifierChip31Result() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidLoadPowerAmplifierChipParame);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadAndroidCOMLoopTestResults : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadAndroidCOMLoopTestResults, LBLInteCtrlPackage)
public:

	quint16 getOperationResult() const;
	quint8 getCOMINResult() const;
	quint8 getCOMOUTResult() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_AndroidCOMLoopTestResults);
	}
	QByteArray CmdContent() const override;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteAndroidEnterTestMode : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteAndroidEnterTestMode, LBLInteCtrlPackage)
public:
	void setKey(QString value) {
		m_key = value;
	}
	quint16 getOperationResult() const;
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_AndroidEnterTestMode);
	}
	QByteArray CmdContent() const override;
private:
	QString m_key;
};
