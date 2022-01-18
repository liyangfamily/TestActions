#include "LBLAndroidCentralCtrl.h"
#include "LBLAndroidAbstract_p.h"
#include <LBL_CommunicatEngine/LBLClusterProxy>

namespace LBL
{
	namespace Android
	{

		LBLAndroidCentralCtrl::LBLAndroidCentralCtrl(QObject* parent) :
			LBLAndroidAbstract(parent)
		{
			Q_D(LBLAndroidAbstract);
			d->q_ptr = this;
		}


		LBLAndroidCentralCtrl::LBLAndroidCentralCtrl(LBLAndroidAbstractPrivate& dd, QObject* parent) :
			LBLAndroidAbstract(dd, parent)
		{
			Q_D(LBLAndroidAbstract);
			d->q_ptr = this;
		}

		LBLAndroidCentralCtrl::~LBLAndroidCentralCtrl()
        {
		}

		
		quint16 LBLAndroidCentralCtrl::readAndroidVersion(bool sync, int msec)
		{
			return readVersionNumber(0x01, sync, msec);
		}

		QString LBLAndroidCentralCtrl::getAndroidVersion()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_androidVersion;
		}

		quint16 LBLAndroidCentralCtrl::readVersionNumber(qint64 type, bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadAndroidVersionNum pack(type);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLAndroidCentralCtrl::writeNoSleep(quint8 value, bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteAndroidNoSleep pack(value);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLAndroidCentralCtrl::readNoSleep(bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadAndroidNoSleep pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint8 LBLAndroidCentralCtrl::getNoSleep()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_noSleep;
		}

		quint16 LBLAndroidCentralCtrl::writeKeyEvent(quint8 status, quint16 keyCode, bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteAndroidKeyEvent pack(status, keyCode);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLAndroidCentralCtrl::getKeyEvent_Result()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_keyEvent_Result;
		}

		quint16 LBLAndroidCentralCtrl::writeDeviceName(QString name, bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteAndroidDeviceName pack(name);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLAndroidCentralCtrl::readDeviceName(bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadAndroidDeviceName pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		QString LBLAndroidCentralCtrl::getDeviceName()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_deviceName;
		}

		quint16 LBLAndroidCentralCtrl::readNetDeviceOnlineStatus(QString ip, bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadAndroidNetDeviceOnlineStatus pack(ip);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLAndroidCentralCtrl::getNetDevice_Status()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_netDeviceOnline_Status;
		}

		QString LBLAndroidCentralCtrl::getNetDevice_IP()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_netDevice_IP;
		}

		quint16 LBLAndroidCentralCtrl::readSCEthLoopTestResult(bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadAndroidSCEthLoopTestResult pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLAndroidCentralCtrl::getSCEthLoopTest_Result()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_scEthLoopTest_Result;
		}

		quint8 LBLAndroidCentralCtrl::getSCEthLoopTest_EffectiveEthCount()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_scEthLoopTest_EffectiveEthCount;
		}

		QByteArray LBLAndroidCentralCtrl::getSCEthLoopTest_ReplyData()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_scEthLoopTest_ReplyData;
		}

		quint16 LBLAndroidCentralCtrl::readUDiskMountingStatus(bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadAndroidUDiskMountingStatus pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint8 LBLAndroidCentralCtrl::getUDiskMounting_Count()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_uDiskMounting_Count;
		}

		QStringList LBLAndroidCentralCtrl::getUDiskMounting_List()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_uDiskMounting_List;
		}

		quint16 LBLAndroidCentralCtrl::writeStartOSDTest(bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteAndroidStartOSDTest pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint8 LBLAndroidCentralCtrl::getOSDTest_WhiteScreenTestResult()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_OSDTest_WhiteScreenTestResult;
		}

		quint8 LBLAndroidCentralCtrl::getOSDTest_BlackScreenTestResult()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_OSDTest_BlackScreenTestResult;
		}

		quint16 LBLAndroidCentralCtrl::writeRelaySwitc(quint8 status, bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteAndroidRelaySwitc pack(status);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLAndroidCentralCtrl::getRelaySwitc_Result()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_RelaySwitc_Result;
		}

		quint8 LBLAndroidCentralCtrl::getRelaySwitc_Status()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_RelaySwitc_Status;
		}

		quint16 LBLAndroidCentralCtrl::writeEnterKeyTest(quint8 status, bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteAndroidEnterKeyTest pack(status);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint8 LBLAndroidCentralCtrl::getKeyTest_Result()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_EnterKeyTest_Result;
		}

		quint16 LBLAndroidCentralCtrl::readKeyTestResult(bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadAndroidKeyTestResult pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint8 LBLAndroidCentralCtrl::getKeyTestResult_Count()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_KeyTestResult_Count;
		}

		QList<quint16> LBLAndroidCentralCtrl::getKeyTestResult_List()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_KeyTestResult_List;
		}

		quint16 LBLAndroidCentralCtrl::readOpticalSensorParam(bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadAndroidOpticalSensorParam pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLAndroidCentralCtrl::getOpticalSensor_Param()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_OpticalSensor_Param;
		}

		quint16 LBLAndroidCentralCtrl::readRouterStatus(bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadAndroidRouterStatus pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint8 LBLAndroidCentralCtrl::getRouter_5GWifiStatus()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_Router_5GWifiStatus;
		}

		quint8 LBLAndroidCentralCtrl::getRouter_2_4GWifiStatus()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_Router_2_4GWifiStatus;
		}

		quint16 LBLAndroidCentralCtrl::writeNetworkCardMACAddr(quint8 flage, QByteArray mac, bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteAndroidNetworkCardMACAddr pack(flage, mac);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLAndroidCentralCtrl::getNetworkCardMACAddr_Results()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_NetworkCardMACAddr_Results;
		}

		quint8 LBLAndroidCentralCtrl::getNetworkCardMACAddr_Flage()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_NetworkCardMACAddr_Flage;
		}

		QByteArray LBLAndroidCentralCtrl::getNetworkCardMACAddr_MAC()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_NetworkCardMACAddr_MAC;
		}

		quint16 LBLAndroidCentralCtrl::writePlayTestSound_1KHZ(quint8 status, bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteAndroidPalyTestSound_1KHZ pack(status);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLAndroidCentralCtrl::getPlayTestSound_Results()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_PalyTestSound_Results;
		}

		quint8 LBLAndroidCentralCtrl::getPlayTestSound_Status()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_PalyTestSound_Status;
		}

		quint16 LBLAndroidCentralCtrl::writeWIFIModuleScanTest(quint8 status, bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteAndroidWIFIModuleScanTest pack(status);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLAndroidCentralCtrl::getWIFIModuleScanTest_Results()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_WIFIModuleScanTest_Results;
		}

		quint16 LBLAndroidCentralCtrl::readWIFIScanList(bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadAndroidWIFIScanList pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint8 LBLAndroidCentralCtrl::getWIFIScanList_Count()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_WIFIScanList_Count;
		}

		quint16 LBLAndroidCentralCtrl::readLoadPowerAmplifierChipParam(bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadAndroidLoadPowerAmplifierChipParam pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint8 LBLAndroidCentralCtrl::getPowerAmplifierChipParam_Results()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_PowerAmplifierChipParam_Results;
		}

		quint8 LBLAndroidCentralCtrl::getPowerAmplifierChipParam_30Results()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_PowerAmplifierChipParam_30Results;
		}

		quint8 LBLAndroidCentralCtrl::getPowerAmplifierChipParam_31Results()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_PowerAmplifierChipParam_31Results;
		}

		quint16 LBLAndroidCentralCtrl::readSCCOMLoopTestResult(bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadAndroidCOMLoopTestResults pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint8 LBLAndroidCentralCtrl::getSCCOMLoopTest_INResult()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_scCOMLoopTest_INResult;
		}

		quint8 LBLAndroidCentralCtrl::getSCCOMLoopTest_OUTResult()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_scCOMLoopTest_OUTResult;
		}

		quint16 LBLAndroidCentralCtrl::writeEnterTestMode(QString key, bool sync, int msec)
		{
			Q_D(LBLAndroidAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteAndroidEnterTestMode pack;
			pack.setKey(key);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLAndroidCentralCtrl::getEnterTestMode_Results()
		{
			Q_D(LBLAndroidAbstract);
			return d->m_EnterTestMode_Results;
		}

		bool LBLAndroidCentralCtrl::init()
		{
			registerCallBack();
			return true;
		}

		void LBLAndroidCentralCtrl::registerCallBack()
		{
			Q_D(LBLAndroidAbstract);
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadAndroidVersionNum(),
				std::bind(&LBLAndroidCentralCtrl::onParseReadVersionNumber, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadAndroidNoSleep(),
				std::bind(&LBLAndroidCentralCtrl::onParseReadNoSleep, this, std::placeholders::_1));

			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteAndroidKeyEvent(),
				std::bind(&LBLAndroidCentralCtrl::onParseWriteKeyEvent, this, std::placeholders::_1));

			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteAndroidDeviceName(),
				std::bind(&LBLAndroidCentralCtrl::onParseWriteDeviceName, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadAndroidDeviceName(),
				std::bind(&LBLAndroidCentralCtrl::onParseReadDeviceName, this, std::placeholders::_1));

			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadAndroidNetDeviceOnlineStatus(),
				std::bind(&LBLAndroidCentralCtrl::onParseReadNetDeviceOnlineStatus, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadAndroidSCEthLoopTestResult(),
				std::bind(&LBLAndroidCentralCtrl::onParseReadSCEthLoopTestResult, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadAndroidUDiskMountingStatus(),
				std::bind(&LBLAndroidCentralCtrl::onParseReadUDiskMountingStatus, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteAndroidStartOSDTest(),
				std::bind(&LBLAndroidCentralCtrl::onParseWriteStartOSDTest, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteAndroidRelaySwitc(),
				std::bind(&LBLAndroidCentralCtrl::onParseWriteRelaySwitc, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteAndroidEnterKeyTest(),
				std::bind(&LBLAndroidCentralCtrl::onParseWriteEnterKeyTest, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadAndroidKeyTestResult(),
				std::bind(&LBLAndroidCentralCtrl::onParseReadKeyTestResult, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadAndroidOpticalSensorParam(),
				std::bind(&LBLAndroidCentralCtrl::onParseReadOpticalSensorParam, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadAndroidRouterStatus(),
				std::bind(&LBLAndroidCentralCtrl::onParseReadRouterStatus, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteAndroidNetworkCardMACAddr(),
				std::bind(&LBLAndroidCentralCtrl::onParseWriteNetworkCardMACAddr, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteAndroidPalyTestSound_1KHZ(),
				std::bind(&LBLAndroidCentralCtrl::onParseWritePalyTestSound_1KHZ, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteAndroidWIFIModuleScanTest(),
				std::bind(&LBLAndroidCentralCtrl::onParseWriteWIFIModuleScanTest, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadAndroidWIFIScanList(),
				std::bind(&LBLAndroidCentralCtrl::onParseReadWIFIScanList, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadAndroidLoadPowerAmplifierChipParam(),
				std::bind(&LBLAndroidCentralCtrl::onParseReadLoadPowerAmplifierChipParam, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadAndroidCOMLoopTestResults(),
				std::bind(&LBLAndroidCentralCtrl::onParseReadCOMLoopTestResults, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteAndroidEnterTestMode(),
				std::bind(&LBLAndroidCentralCtrl::onParseWriteEnterTestMode, this, std::placeholders::_1));
		}

		quint16 LBLAndroidCentralCtrl::onParseReadVersionNumber(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_ReadAndroidVersionNum pack(data);
			quint64 versionType = pack.getVersionType();
			QByteArray version = pack.getReplyData();
			switch (versionType)
			{
			case 0x01:
			{
				quint16 len = 0;
                memcpy(&len, version.constData(), 2);
				d->m_androidVersion = version.mid(2, len);
			}
			break;
			default:
				break;
			}
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseReadNoSleep(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_ReadAndroidNoSleep pack(data);
			d->m_noSleep = pack.getNoSleep();
			return d->m_noSleep;
		}

		quint16 LBLAndroidCentralCtrl::onParseWriteKeyEvent(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_WriteAndroidKeyEvent pack(data);
			d->m_keyEvent_Result = pack.getOperationResult();
			return d->m_keyEvent_Result;
		}

		quint16 LBLAndroidCentralCtrl::onParseWriteDeviceName(const QByteArray & data)
		{
            LBLPackageInteCtrl_WriteAndroidDeviceName pack(data);
			return pack.getOperationResult();
		}

		quint16 LBLAndroidCentralCtrl::onParseReadDeviceName(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_ReadAndroidDeviceName pack(data);
			d->m_deviceName = pack.getDeviceName();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseReadNetDeviceOnlineStatus(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_ReadAndroidNetDeviceOnlineStatus pack(data);
			d->m_netDeviceOnline_Status = pack.getOperationResult();
			d->m_netDevice_IP = pack.getIP();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseReadSCEthLoopTestResult(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_ReadAndroidSCEthLoopTestResult pack(data);
			d->m_scEthLoopTest_Result = pack.getOperationResult();
			d->m_scEthLoopTest_EffectiveEthCount = pack.getEffectiveEthCount();
			d->m_scEthLoopTest_ReplyData = pack.getReplyData();
			return d->m_scEthLoopTest_Result;
		}

		quint16 LBLAndroidCentralCtrl::onParseReadUDiskMountingStatus(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_ReadAndroidUDiskMountingStatus pack(data);
			d->m_uDiskMounting_Count = pack.getUDiskCount();
			d->m_uDiskMounting_List = pack.getUDiskNameList();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseWriteStartOSDTest(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_WriteAndroidStartOSDTest pack(data);
			d->m_OSDTest_WhiteScreenTestResult = pack.getWhiteScreenTestResult();
			d->m_OSDTest_BlackScreenTestResult = pack.getBlackScreenTestResult();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseWriteRelaySwitc(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_WriteAndroidRelaySwitc pack(data);
			d->m_RelaySwitc_Result = pack.getOperationResult();
			d->m_RelaySwitc_Status = pack.getStatus();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseWriteEnterKeyTest(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_WriteAndroidEnterKeyTest pack(data);
			d->m_EnterKeyTest_Result = pack.getResult();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseReadKeyTestResult(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_ReadAndroidKeyTestResult pack(data);
			d->m_KeyTestResult_Count = pack.getKeyCount();
			d->m_KeyTestResult_List = pack.getResultList();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseReadOpticalSensorParam(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_ReadAndroidOpticalSensorParam pack(data);
			d->m_OpticalSensor_Param = pack.getParam();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseReadRouterStatus(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_ReadAndroidRouterStatus pack(data);
			d->m_Router_5GWifiStatus = pack.get5GWifiStatus();
			d->m_Router_2_4GWifiStatus = pack.get2_4GWifiStatus();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseWriteNetworkCardMACAddr(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_WriteAndroidNetworkCardMACAddr pack(data);
			d->m_NetworkCardMACAddr_Results = pack.getOperationResult();
			d->m_NetworkCardMACAddr_Flage = pack.getFlage();
			d->m_NetworkCardMACAddr_MAC = pack.getMAC();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseWritePalyTestSound_1KHZ(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_WriteAndroidPalyTestSound_1KHZ pack(data);
			d->m_PalyTestSound_Results = pack.getOperationResult();
			d->m_PalyTestSound_Status = pack.getStatus();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseWriteWIFIModuleScanTest(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_WriteAndroidWIFIModuleScanTest pack(data);
			d->m_WIFIModuleScanTest_Results = pack.getOperationResult();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseReadWIFIScanList(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_ReadAndroidWIFIScanList pack(data);
			d->m_WIFIScanList_Count = pack.getListCount();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseReadLoadPowerAmplifierChipParam(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_ReadAndroidLoadPowerAmplifierChipParam pack(data);
			d->m_PowerAmplifierChipParam_Results = pack.getOperationResult();
			d->m_PowerAmplifierChipParam_30Results = pack.getPowerAmplifierChip30Result();
			d->m_PowerAmplifierChipParam_31Results = pack.getPowerAmplifierChip31Result();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseReadCOMLoopTestResults(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_ReadAndroidCOMLoopTestResults pack(data);
			d->m_scCOMLoopTest_Result = pack.getOperationResult();
			d->m_scCOMLoopTest_INResult = pack.getCOMINResult();
			d->m_scCOMLoopTest_OUTResult = pack.getCOMOUTResult();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLAndroidCentralCtrl::onParseWriteEnterTestMode(const QByteArray & data)
		{
			Q_D(LBLAndroidAbstract);
			LBLPackageInteCtrl_WriteAndroidEnterTestMode pack(data);
			d->m_EnterTestMode_Results = pack.getOperationResult();
			return LBLPackage::EOR_Success;
		}

	}
}
