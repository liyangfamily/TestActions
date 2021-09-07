#include "LBL_CommunicatEngine/LBLInteCtrlAndroidPackage.h"

LBLPackageInteCtrl_ReadAndroidVersionNum::LBLPackageInteCtrl_ReadAndroidVersionNum(quint64 versionType):
	m_versionType(versionType)
{
}

quint64 LBLPackageInteCtrl_ReadAndroidVersionNum::getVersionType() const
{
	quint64 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 4) {
		return value;
	}
    memcpy(&value, buffer.constData(), 4);
	return value;
}

QByteArray LBLPackageInteCtrl_ReadAndroidVersionNum::getReplyData() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() < 4) {
		return value;
	}
	value.append(buffer.mid(4, buffer.size() - 4));
	return value;
}

QByteArray LBLPackageInteCtrl_ReadAndroidVersionNum::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_versionType, 4);
	return temp;
}

LBLPackageInteCtrl_ReadAndroidNetInfo::LBLPackageInteCtrl_ReadAndroidNetInfo(quint8 communicatType):
	m_type(communicatType)
{
}

QString LBLPackageInteCtrl_ReadAndroidNetInfo::getDeviceName() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() < 40) {
		return value;
	}
	value.append(buffer.mid(0, 40));
	return value;
}

quint64 LBLPackageInteCtrl_ReadAndroidNetInfo::getRandomCode() const
{
	quint64 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 44) {
		return value;
	}
    memcpy(&value, buffer.constData() + 40, 4);
	return value;
}

quint8 LBLPackageInteCtrl_ReadAndroidNetInfo::getCommunicatType() const
{
	QByteArray buffer = getContent();
	if (buffer.size() < 45) {
		return 0;
	}
	return buffer.at(44);
}

quint8 LBLPackageInteCtrl_ReadAndroidNetInfo::getWirelessIPMode() const
{
	QByteArray buffer = getContent();
	if (buffer.size() < 46) {
		return 0;
	}
	return buffer.at(45);
}

QString LBLPackageInteCtrl_ReadAndroidNetInfo::getWirelessIP() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 50;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QString LBLPackageInteCtrl_ReadAndroidNetInfo::getWirelessSubnetMask() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 54;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QString LBLPackageInteCtrl_ReadAndroidNetInfo::getWirelessGateway() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 58;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QString LBLPackageInteCtrl_ReadAndroidNetInfo::getWirelessDNS1() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 62;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QString LBLPackageInteCtrl_ReadAndroidNetInfo::getWirelessDNS2() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 66;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

quint8 LBLPackageInteCtrl_ReadAndroidNetInfo::getWireIPMode() const
{
	QByteArray buffer = getContent();
	if (buffer.size() < 67) {
		return 0;
	}
	return buffer.at(66);
}

QString LBLPackageInteCtrl_ReadAndroidNetInfo::getWireIP() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 71;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QString LBLPackageInteCtrl_ReadAndroidNetInfo::getWireSubnetMask() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 75;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QString LBLPackageInteCtrl_ReadAndroidNetInfo::getWireGateway() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 79;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QString LBLPackageInteCtrl_ReadAndroidNetInfo::getWireDNS1() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 83;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QString LBLPackageInteCtrl_ReadAndroidNetInfo::getWireDNS2() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 87;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

LBLPackageInteCtrl_WriteAndroidNetInfo::LBLPackageInteCtrl_WriteAndroidNetInfo(quint64 randomCode, quint8 communicatType, quint8 ipMode):
	m_randomCode(randomCode),m_type(communicatType),m_ipMode(ipMode)
{
}

quint16 LBLPackageInteCtrl_WriteAndroidNetInfo::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint64 LBLPackageInteCtrl_WriteAndroidNetInfo::getRandomCode() const
{
	quint64 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 6) {
		return value;
	}
    memcpy(&value, buffer.constData() + 2, 4);
	return value;
}

quint8 LBLPackageInteCtrl_WriteAndroidNetInfo::getCommunicatType() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 7) {
		return value;
	}
	return buffer.at(6);
}

quint8 LBLPackageInteCtrl_WriteAndroidNetInfo::getIPMode() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 8) {
		return value;
	}
	return buffer.at(7);
}

QString LBLPackageInteCtrl_WriteAndroidNetInfo::getIP() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 12;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QString LBLPackageInteCtrl_WriteAndroidNetInfo::getSubnetMask() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 16;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QString LBLPackageInteCtrl_WriteAndroidNetInfo::getGateway() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 20;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QString LBLPackageInteCtrl_WriteAndroidNetInfo::getDNS1() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 24;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QString LBLPackageInteCtrl_WriteAndroidNetInfo::getDNS2() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 28;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QByteArray LBLPackageInteCtrl_WriteAndroidNetInfo::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_randomCode, 4);
	temp.append((char *)&m_type, 1);
	temp.append((char *)&m_ipMode, 1);
	QStringList list = m_ip.split(".");
	for (auto i : list) {
		temp.append(i.toInt());
	}
	list = m_subnetMask.split(".");
	for (auto i : list) {
		temp.append(i.toInt());
	}
	list = m_gateway.split(".");
	for (auto i : list) {
		temp.append(i.toInt());
	}
	list = m_dns1.split(".");
	for (auto i : list) {
		temp.append(i.toInt());
	}
	list = m_dns2.split(".");
	for (auto i : list) {
		temp.append(i.toInt());
	}
	return temp;
}

quint8 LBLPackageInteCtrl_ReadAndroidNoSleep::getNoSleep() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1)
	{
		return value;
	}
	value = buffer.at(0);
	return value;
}

LBLPackageInteCtrl_WriteAndroidNoSleep::LBLPackageInteCtrl_WriteAndroidNoSleep(quint8 value):
	m_NoSleep(value)
{
}

quint16 LBLPackageInteCtrl_WriteAndroidNoSleep::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadAndroidHotInfo::getStatus() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1)
	{
		return value;
	}
	value = buffer.at(0);
	return value;
}

quint8 LBLPackageInteCtrl_ReadAndroidHotInfo::is5G() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 2)
	{
		return value;
	}
	value = buffer.at(1);
	return value;
}

quint8 LBLPackageInteCtrl_ReadAndroidHotInfo::isEncryption() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3)
	{
		return value;
	}
	value = buffer.at(2);
	return value;
}

QString LBLPackageInteCtrl_ReadAndroidHotInfo::getSSID() const
{
	QString value;
	QByteArray buffer = getContent();
	if (buffer.size() < 5) {
		return value;
	}
	quint16 len;
    memcpy(&len, buffer.constData() + 3, 2);
	if (buffer.size() < 5 + len) {
		return value;
	}
	value = buffer.mid(5, len);
	return value;
}

QString LBLPackageInteCtrl_ReadAndroidHotInfo::getPSW() const
{
	QString value;
	QByteArray buffer = getContent();
	if (buffer.size() < 5) {
		return value;
	}
	quint16 len1;
    memcpy(&len1, buffer.constData() + 3, 2);
	if (buffer.size() < 5 + len1) {
		return value;
	}
	quint16 len2;
    memcpy(&len2, buffer.constData() + 5 + len1, 2);
	if (buffer.size() < 7 + len1 + len2) {
		return value;
	}
	value = buffer.mid(5 + len1 + 2, len2);
	return value;
}

LBLPackageInteCtrl_WriteAndroidKeyEvent::LBLPackageInteCtrl_WriteAndroidKeyEvent(quint8 status, quint16 keyCode) :
	m_status(status), m_keyCode(keyCode)
{
}

quint16 LBLPackageInteCtrl_WriteAndroidKeyEvent::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageInteCtrl_WriteAndroidKeyEvent::CmdContent() const
{
	QByteArray temp;
	temp.append(m_status);
	temp.append((char *)&m_keyCode, 2);
	return temp;
}

QString LBLPackageInteCtrl_ReadAndroidDeviceName::getDeviceName() const
{
	QString value;
	QByteArray buffer = getContent();
	if (buffer.size() < 40) {
		return value;
	}
	value = buffer.mid(0, 40);
	return value;
}



/*********************************************************************************************************
**测试相关                                                                     
*********************************************************************************************************/
LBLPackageInteCtrl_ReadAndroidNetDeviceOnlineStatus::LBLPackageInteCtrl_ReadAndroidNetDeviceOnlineStatus(QString value):
	m_ip(value)
{
}

quint16 LBLPackageInteCtrl_ReadAndroidNetDeviceOnlineStatus::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QString LBLPackageInteCtrl_ReadAndroidNetDeviceOnlineStatus::getIP() const
{
	QString value;
	QByteArray buffer = getContent();
	int pos = 6;
	if (buffer.size() < pos) {
		return value;
	}
	value = QString("%1.%2.%3.%4").arg(buffer.at(pos - 4)).arg(buffer.at(pos - 3)).arg(buffer.at(pos - 2)).arg(buffer.at(pos - 1));
	return value;
}

QByteArray LBLPackageInteCtrl_ReadAndroidNetDeviceOnlineStatus::CmdContent() const
{
	QByteArray temp;
	QStringList list = m_ip.split(".");
	for (auto i : list) {
		temp.append(i.toInt());
	}
	return  temp;
}

quint16 LBLPackageInteCtrl_ReadAndroidSCEthLoopTestResult::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadAndroidSCEthLoopTestResult::getEffectiveEthCount() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3){
		return value;
	}
	value = buffer.at(2);
	return value;
}

QByteArray LBLPackageInteCtrl_ReadAndroidSCEthLoopTestResult::getReplyData() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() < 203) {
		return value;
	}
	value.append(buffer.mid(3, buffer.size() - 3));
	return value;
}

quint8 LBLPackageInteCtrl_ReadAndroidUDiskMountingStatus::getUDiskCount() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

QStringList LBLPackageInteCtrl_ReadAndroidUDiskMountingStatus::getUDiskNameList() const
{
	QStringList value;
	QByteArray buffer = getContent();
	if (buffer.size() != getReplayDataLength()) {
		return QStringList();
	}
	quint8 count = getUDiskCount();
	int pos = 1;
	for (int i = 0; i < count; ++i) {
		quint8 nameLen = buffer.at(pos);
		pos += 1;
		value.append(buffer.mid(pos, nameLen));
		pos += nameLen;
	}
	return value;
}

quint8 LBLPackageInteCtrl_WriteAndroidStartOSDTest::getWhiteScreenTestResult() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

quint8 LBLPackageInteCtrl_WriteAndroidStartOSDTest::getBlackScreenTestResult() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 2) {
		return value;
	}
	value = buffer.at(1);
	return value;
}

LBLPackageInteCtrl_WriteAndroidRelaySwitc::LBLPackageInteCtrl_WriteAndroidRelaySwitc(quint8 value):
	m_status(value)
{
}

quint16 LBLPackageInteCtrl_WriteAndroidRelaySwitc::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_WriteAndroidRelaySwitc::getStatus() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	value = buffer.at(2);
	return value;
}

QByteArray LBLPackageInteCtrl_WriteAndroidRelaySwitc::CmdContent() const
{
	QByteArray temp;
	temp.append(m_status);
	return temp;
}

LBLPackageInteCtrl_WriteAndroidEnterKeyTest::LBLPackageInteCtrl_WriteAndroidEnterKeyTest(quint8 value) :
	m_status(value)
{

}

quint8 LBLPackageInteCtrl_WriteAndroidEnterKeyTest::getResult() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

QByteArray LBLPackageInteCtrl_WriteAndroidEnterKeyTest::CmdContent() const
{
	QByteArray temp;
	temp.append(m_status);
	return temp;
}

quint8 LBLPackageInteCtrl_ReadAndroidKeyTestResult::getKeyCount() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

QList<quint16> LBLPackageInteCtrl_ReadAndroidKeyTestResult::getResultList() const
{
	QList<quint16> value;
	QByteArray buffer = getContent();
	if (buffer.size() != getReplayDataLength()) {
		return QList<quint16>();
	}
	quint8 keyCount = getKeyCount();
	int pos = 1;
	for (int i = 0; i < keyCount; ++i) {
		quint16 keyCode = 0;
		QByteArray keyArray = buffer.mid(pos, 2);
        memcpy(&keyCode, keyArray.constData(), 2);
		value.append(keyCode);
		pos += 2;
	}
	return value;
}

quint16 LBLPackageInteCtrl_ReadAndroidOpticalSensorParam::getParam() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 2) {
		return value;
	}
    memcpy(&value, buffer.constData(), 2);
	return value;
}

quint8 LBLPackageInteCtrl_ReadAndroidRouterStatus::get5GWifiStatus() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

quint8 LBLPackageInteCtrl_ReadAndroidRouterStatus::get2_4GWifiStatus() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 2) {
		return value;
	}
	value = buffer.at(1);
	return value;
}

LBLPackageInteCtrl_WriteAndroidNetworkCardMACAddr::LBLPackageInteCtrl_WriteAndroidNetworkCardMACAddr(quint8 flage, QByteArray mac):
	m_flage(flage),m_mac(mac)
{
}

quint16 LBLPackageInteCtrl_WriteAndroidNetworkCardMACAddr::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_WriteAndroidNetworkCardMACAddr::getFlage() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	value = buffer.at(2);
	return value;
}

QByteArray LBLPackageInteCtrl_WriteAndroidNetworkCardMACAddr::getMAC() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() < 9) {
		return value;
	}
	value.append(buffer.mid(3, buffer.size() - 3));
	return value;
}

QByteArray LBLPackageInteCtrl_WriteAndroidNetworkCardMACAddr::CmdContent() const
{
	QByteArray temp;
	temp.append(m_flage);
	temp.append(m_mac);
	return temp;
}

LBLPackageInteCtrl_WriteAndroidPalyTestSound_1KHZ::LBLPackageInteCtrl_WriteAndroidPalyTestSound_1KHZ(quint8 value):
	m_status(value)
{
}

quint16 LBLPackageInteCtrl_WriteAndroidPalyTestSound_1KHZ::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_WriteAndroidPalyTestSound_1KHZ::getStatus() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	value = buffer.at(2);
	return value;
}

QByteArray LBLPackageInteCtrl_WriteAndroidPalyTestSound_1KHZ::CmdContent() const
{
	QByteArray temp;
	temp.append(m_status);
	return temp;
}

LBLPackageInteCtrl_WriteAndroidWIFIModuleScanTest::LBLPackageInteCtrl_WriteAndroidWIFIModuleScanTest(quint8 value) :
	m_status(value)
{
}

quint16 LBLPackageInteCtrl_WriteAndroidWIFIModuleScanTest::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageInteCtrl_WriteAndroidWIFIModuleScanTest::CmdContent() const
{
	QByteArray temp;
	temp.append(m_status);
	return temp;
}

quint8 LBLPackageInteCtrl_ReadAndroidWIFIScanList::getListCount() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

quint16 LBLPackageInteCtrl_ReadAndroidLoadPowerAmplifierChipParam::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadAndroidLoadPowerAmplifierChipParam::getPowerAmplifierChip30Result() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	value = buffer.at(2);
	return value;
}

quint8 LBLPackageInteCtrl_ReadAndroidLoadPowerAmplifierChipParam::getPowerAmplifierChip31Result() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 4) {
		return value;
	}
	value = buffer.at(3);
	return value;
}

quint16 LBLPackageInteCtrl_WriteAndroidEnterTestMode::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageInteCtrl_WriteAndroidEnterTestMode::CmdContent() const
{
	QByteArray temp;
	temp.fill(0, 32);
	QByteArray name = m_key.left(32).toLocal8Bit();
	temp.replace(0, name.size(), name);
	return temp;
}

LBLPackageInteCtrl_WriteAndroidDeviceName::LBLPackageInteCtrl_WriteAndroidDeviceName(QString value):
	m_name(value)
{
}

quint16 LBLPackageInteCtrl_WriteAndroidDeviceName::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageInteCtrl_WriteAndroidDeviceName::CmdContent() const
{
	QByteArray temp; 
	temp.fill(0, 40);
	QByteArray name = m_name.left(40).toLocal8Bit();
	temp.replace(0, name.size(), name);
	return temp;
}

quint16 LBLPackageInteCtrl_ReadAndroidCOMLoopTestResults::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadAndroidCOMLoopTestResults::getCOMINResult() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

quint8 LBLPackageInteCtrl_ReadAndroidCOMLoopTestResults::getCOMOUTResult() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 2) {
		return value;
	}
	value = buffer.at(1);
	return value;
}

QByteArray LBLPackageInteCtrl_ReadAndroidCOMLoopTestResults::CmdContent() const
{
	QByteArray temp;
	temp.append(char(1));
	return temp;
}
