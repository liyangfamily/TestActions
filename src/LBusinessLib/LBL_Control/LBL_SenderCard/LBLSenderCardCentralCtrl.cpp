#include "LBLSenderCardCentralCtrl.h"
#include "LBLSenderCardAbstract_p.h"
#include <LBL_CommunicatEngine/LBLClusterProxy>
#include <LBL_Core/LBLUIHelper>
namespace LBL
{
	namespace SC
	{

		LBLSenderCardCentralCtrl::LBLSenderCardCentralCtrl(QObject* parent):
			LBLSenderCardAbstract(parent)
		{
			Q_D(LBLSenderCardAbstract);
			d->q_ptr = this;
		}


		LBLSenderCardCentralCtrl::LBLSenderCardCentralCtrl(LBLSenderCardAbstractPrivate& dd, QObject* parent) :
			LBLSenderCardAbstract(dd, parent)
		{
			Q_D(LBLSenderCardAbstract);
			d->q_ptr = this;
		}

		LBLSenderCardCentralCtrl::~LBLSenderCardCentralCtrl()
		{
			qDebug() << __FUNCTION__;
		}

		quint16 LBLSenderCardCentralCtrl::writeFPGARegister(quint32 addr, QByteArray value, bool sync, int msec)
		{
			if (0 == value.size()) {
				return LAPI::EResult::ER_InDataError;
			}
			Q_D(LBLSenderCardAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteSCFPGARegister pack(addr, value);
			pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);
			LBLEnginePackage enginePack;
			enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
			enginePack.setData(pack.getDataToSend());
			if (sync) {
				LBLEnginePackage recEnginePack;
				if (!LBLClusterProxy::syncSend(enginePack, recEnginePack, msec)) {
					return LAPI::EResult::ER_SyncSendTimeOut;
				}
				quint16 ret = d->m_packageMgr.handle(LBLPackage(recEnginePack.data()));
				return ret;
			}
			else {
				LBLClusterProxy::asyncSend(enginePack);
			}

			return LAPI::EResult::ER_INTECTRL_Success;
		}

		QByteArray LBLSenderCardCentralCtrl::readFPGARegister(quint32 addr, quint16 len, bool sync, int msec)
		{
			Q_D(LBLSenderCardAbstract);
			//发送开始发送文件指令
			LBLPackageInteCtrl_ReadSCFPGARegister pack(addr, len);
			pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);
			LBLEnginePackage enginePack;
			enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
			enginePack.setData(pack.getDataToSend());
			if (sync) {
				LBLEnginePackage recEnginePack;
				if (!LBLClusterProxy::syncSend(enginePack, recEnginePack, msec)) {
					return  QByteArray();
				}
				LBLPackageInteCtrl_ReadSCFPGARegister pack(recEnginePack.data());
				quint16 ret = pack.getOperationResult();
				if (LAPI::EResult::ER_INTECTRL_Success != ret)
					return QByteArray();
				quint16 len = pack.getDataLength();
                Q_UNUSED(len);
				return pack.getReplyData();
				
			}
			else {
				LBLClusterProxy::asyncSend(enginePack);
			}
			return QByteArray();
		}

		QByteArray LBLSenderCardCentralCtrl::getFPGARegister()
		{
			Q_D(LBLSenderCardAbstract);
			return d->senderCardReadFPGARegister;
		}

		QByteArray LBLSenderCardCentralCtrl::readFPGAVersion(bool sync, int msec)
		{
			quint32 addr = ENormalSettingRegAddrs::ENSRA_FPGABigVersion;
			quint16 len = 5;
			return readFPGARegister(addr, len, sync, msec);
		}

		QString LBLSenderCardCentralCtrl::getFPGAVersion()
		{
			Q_D(LBLSenderCardAbstract);
			return d->m_gzData.normalSetting.getSendCardFPGAVersion();
		}

		quint16 LBLSenderCardCentralCtrl::writeFPGAEthLoad(const QList<LBLSPort>& value, bool sync, int msec)
		{
			if (value.size() > LBL_Max_UsingSenderCardPort)
				return LAPI::EResult::ER_InDataError;
			QByteArray tempData;
			for (int ethIndex = 0; ethIndex < LBL_Max_UsingSenderCardPort; ++ethIndex) {
				bool bFind = false;
				for (auto i : value) {
					if (ethIndex == i.index()) {
						tempData.append(i.toByteArray());
						bFind = true;
						break;
					}
				}
				if (!bFind) {
					LBLSPort temp;
					tempData.append(temp.toByteArray());
				}
			}
			quint32 addr = EEthLoadRegAddrs::EELRA_EthLoadArea;
			return writeFPGARegister(addr, tempData, sync, msec);
		}

		QByteArray LBLSenderCardCentralCtrl::readFPGAEthLoad(bool sync, int msec)
		{
			quint32 addr = EEthLoadRegAddrs::EELRA_EthLoadArea;
			quint16 len = LBL_Max_UsingSenderCardPort * 8;
			return readFPGARegister(addr, len, sync, msec);
		}

		QList<LBLSPort> LBLSenderCardCentralCtrl::getFPGAEthLoad()
		{
			Q_D(LBLSenderCardAbstract);
			QList<LBLSPort> allPortArea;
			for (int pos = 0, ethIndex = 0; ethIndex < LBL_Max_UsingSenderCardPort; ++ethIndex, pos += 8) {
				LBLSPort tempArea;
				tempArea.setIndex(ethIndex);
				tempArea.fromByteArray(QByteArray((char*)(d->m_gzData.sendCardEthLoad.ethLoadArea + pos), 8));
				allPortArea.append(tempArea);
			}
			return allPortArea;
		}

		quint16 LBLSenderCardCentralCtrl::readMCUAppVersion(bool sync, int msec)
		{
			Q_D(LBLSenderCardAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadMCUAppVersion pack;
			pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);
			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		QString LBLSenderCardCentralCtrl::getMCUAppVersion()
		{
			Q_D(LBLSenderCardAbstract);
			return d->m_realData.mcuAppVersion;
		}

		quint16 LBLSenderCardCentralCtrl::readMCUBootVersion(bool sync, int msec)
		{
			Q_D(LBLSenderCardAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadMCUBootVersion pack;
			pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);
			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		QString LBLSenderCardCentralCtrl::getMCUBootVersion()
		{
			Q_D(LBLSenderCardAbstract);
			return d->m_realData.mcuBootVersion;
		}

		QByteArray LBLSenderCardCentralCtrl::readEthLoopTest(bool sync, int msec)
		{
			quint32 addr = EProjectSelfTestRegAddrs::EPSTRA_EthErrorRate;
			quint16 len = LBL_Max_SupportSenderCardPort * sizeof(SEthErrorRate);
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::getEthLoopTest_Count()
		{
			Q_D(LBLSenderCardAbstract);
			quint8 effectiveEth = 0;
			for (auto i : d->m_gzData.projectSelfTest.errorRate) {
				if (0 != i.allPackageCount && d->m_ethLoopBitErrRateThreshold >= (float)i.ErrorPackageCount/ (float)i.allPackageCount) {
					++effectiveEth;
				}
			}
			return effectiveEth;
		}

		QMap<quint8, float> LBLSenderCardCentralCtrl::getEthLoopTest_BitErrRate()
		{
			Q_D(LBLSenderCardAbstract);
			QMap<quint8, float> bitErrRateMap;
			for (int i = 0; i < LBL_Max_SupportSenderCardPort;++i) {
				SEthErrorRate temp = d->m_gzData.projectSelfTest.errorRate[i];
				if (0 == temp.allPackageCount) {
					continue;
				}
				bitErrRateMap.insert(i, (float)temp.ErrorPackageCount / (float)temp.allPackageCount);
			}
			return bitErrRateMap;
		}

		quint16 LBLSenderCardCentralCtrl::writeSelfTestModeOpen(quint8 value, bool sync, int msec)
		{
			/*if (readSelfTestModeOpen(sync, msec).isEmpty()) {
				return LAPI::EResult::ER_INTECTRL_Fail_NoRet;
			}*/
			Q_D(LBLSenderCardAbstract);
			quint8 writeValue = d->m_gzData.selfTest.testModeStatus;
			/*LBLUIHelper::bitSet(writeValue, 0, LBLUIHelper::bitGet(value, 0));*/
			if (LBLUIHelper::bitGet(writeValue, 0) == LBLUIHelper::bitGet(value, 0)) {
				return LAPI::EResult::ER_Success;
			}
			QByteArray tempData;
			tempData.append(value);
			quint32 addr = ESelfTestRegAddrs::ESTRA_TestModeStatus;
			quint16 ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				d->m_gzData.selfTest.testModeStatus = value;
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::readSelfTestModeOpen(bool sync, int msec)
		{
			quint32 addr = ESelfTestRegAddrs::ESTRA_TestModeStatus;
			quint16 len = 1;
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::getSelfTestModeOpen()
		{
			Q_D(LBLSenderCardAbstract);
			return LBLUIHelper::bitGet(d->m_gzData.selfTest.testModeStatus, 0);
		}

		quint16 LBLSenderCardCentralCtrl::writeSelfTestModeStart(quint8 value, bool sync, int msec)
		{
			if (readSelfTestModeOpen(sync, msec).isEmpty()) {
				return LAPI::EResult::ER_INTECTRL_Fail_NoRet;
			}
			Q_D(LBLSenderCardAbstract);
			quint8 writeValue = d->m_gzData.selfTest.testModeStatus;
			if (LBLUIHelper::bitGet(writeValue, 5) == LBLUIHelper::bitGet(value, 0)) {
				return LAPI::EResult::ER_Success;
			}
			LBLUIHelper::bitSet(writeValue, 5, LBLUIHelper::bitGet(value, 0));
			QByteArray tempData;
			tempData.append(writeValue);
			quint32 addr = ESelfTestRegAddrs::ESTRA_TestModeStatus;
			quint16 ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				d->m_gzData.selfTest.testModeStatus = writeValue;
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::readSelfTestModeStart(bool sync, int msec)
		{
			quint32 addr = ESelfTestRegAddrs::ESTRA_TestModeStatus;
			quint16 len = 1;
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::getSelfTestModeStart()
		{
			Q_D(LBLSenderCardAbstract);
			return LBLUIHelper::bitGet(d->m_gzData.selfTest.testModeStatus, 0);
		}

		quint16 LBLSenderCardCentralCtrl::writeSelfTestMode(quint8 mode, bool sync, int msec)
		{
			LAPI::UI::EPictureTestMode value = (LAPI::UI::EPictureTestMode)mode;
			
			quint16 ret = writeSelfTestModeOpen(value == LAPI::UI::EPictureTestMode::EPTM_Normal ? 0 : 1, true, 1500);
			if (ret != LAPI::EResult::ER_Success) {
				return ret;
            }
			QByteArray tempData;
			tempData.append(mode);
			quint32 addr = ESelfTestRegAddrs::ESTRA_TestSourceMode;
			ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				Q_D(LBLSenderCardAbstract);
				d->m_gzData.selfTest.testSourceMode = mode;
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::readSelfTestMode(bool sync, int msec)
		{
			QByteArray temp = readSelfTestModeOpen(sync, msec);
			if (temp.isEmpty()) {
				return temp;
			}
			quint32 addr = ESelfTestRegAddrs::ESTRA_TestSourceMode;
			quint16 len = 1;
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::getSelfTestMode()
		{
			Q_D(LBLSenderCardAbstract);
			if (getSelfTestModeOpen() == 0) {
				return LAPI::UI::EPictureTestMode::EPTM_Normal;
			}
			else {
				return d->m_gzData.selfTest.testSourceMode;
			}
		}

		quint16 LBLSenderCardCentralCtrl::writeSelfTestModeSpeed(quint8 speed, bool sync, int msec)
		{
			LAPI::UI::EPictureTestModeSpeed value = (LAPI::UI::EPictureTestModeSpeed)speed;

			quint16 ret = writeSelfTestModeStart(value == LAPI::UI::EPictureTestModeSpeed::EPTS_Stop? 1 : 0, true, 1500);
			if (ret != LAPI::EResult::ER_Success) {
				return ret;
            }
			QByteArray tempData;
			tempData.append(speed);
			quint32 addr = ESelfTestRegAddrs::ESTRA_TestSourceSpeed;
			ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				Q_D(LBLSenderCardAbstract);
				d->m_gzData.selfTest.testSourceSpeed = speed;
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::readSelfTestModeSpeed(bool sync, int msec)
		{
			QByteArray temp = readSelfTestModeStart(sync, msec);
			if (temp.isEmpty()) {
				return temp;
			}
			quint32 addr = ESelfTestRegAddrs::ESTRA_TestSourceSpeed;
			quint16 len = 1;
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::getSelfTestModeSpeed()
		{
			Q_D(LBLSenderCardAbstract);
			if (getSelfTestModeStart() == 1) {
				return LAPI::UI::EPictureTestModeSpeed::EPTS_Stop;
			}
			else {
				return d->m_gzData.selfTest.testSourceSpeed;
			}
		}

		quint16 LBLSenderCardCentralCtrl::sendConnectionBuffer(bool sync, int msec)
		{
			Q_D(LBLSenderCardAbstract);
			d->senderCardConnectionBuffer.clear();
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_SendConnection pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBLEnginePackage enginePack;
			enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
			enginePack.setData(pack.getDataToSend());
			if (sync) {
				LBLEnginePackage recEnginePack;
				LBLClusterProxy::syncSend(enginePack, recEnginePack, msec);
				return d->m_packageMgr.handle(LBLPackage(recEnginePack.data()));
			}
			else {

				return LBLClusterProxy::asyncSend(enginePack) ? LAPI::EResult::ER_INTECTRL_Success : LAPI::EResult::ER_INTECTRL_Fail_NoReason;
			}
		}

		quint16 LBLSenderCardCentralCtrl::readConnectionBuffer(bool sync, int msec)
		{
			Q_D(LBLSenderCardAbstract);
			d->senderCardConnectionBuffer.clear();
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadConnection pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBLEnginePackage enginePack;
			enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
			enginePack.setData(pack.getDataToSend());
			if (sync) {
				LBLEnginePackage recEnginePack;
				LBLClusterProxy::syncSend(enginePack, recEnginePack, msec, true);
				return d->m_packageMgr.handle(LBLPackage(recEnginePack.data()));
			}
			else {

				return LBLClusterProxy::asyncSend(enginePack) ? LAPI::EResult::ER_INTECTRL_Success : LAPI::EResult::ER_INTECTRL_Fail_NoReason;
			}
		}

		QByteArray LBLSenderCardCentralCtrl::getConnectionBuffer()
		{
			Q_D(LBLSenderCardAbstract);
			QByteArray data;
			for (auto i : d->senderCardConnectionBuffer) {
				data.append(i);
			}
			return data;
		}

		quint16 LBLSenderCardCentralCtrl::writeSaveSCParam(bool sync, int msec)
		{
			Q_D(LBLSenderCardAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteSaveSCParam pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);
			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLSenderCardCentralCtrl::writeBrightness(int value, bool sync, int msec)
		{
			Q_D(LBLSenderCardAbstract);
			//在此处组好集控的包，直接调用通信层
			d->m_cacheData.brightness= value;
			LBLPackageInteCtrl_WriteVideoSourceBrightness pack(value);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);
			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLSenderCardCentralCtrl::readBrightness(bool sync, int msec)
		{
			Q_D(LBLSenderCardAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadVideoSourceBrightness pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);
			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		int LBLSenderCardCentralCtrl::getBrightness()
		{
			Q_D(LBLSenderCardAbstract);
			return d->m_realData.brightness;
		}

		quint16 LBLSenderCardCentralCtrl::writeSenderCardUuid(quint8 idType, QUuid uuid, bool sync, int msec)
		{
			Q_D(LBLSenderCardAbstract);
			//在此处组好集控的包，直接调用通信层
			d->m_cacheData.senderCardUuidType = idType;
			d->m_cacheData.senderCardUuid = uuid;
			LBLPackageInteCtrl_WriteSenderCardUuid pack(idType, uuid);
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);
			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		quint16 LBLSenderCardCentralCtrl::readSenderCardUuid(bool sync, int msec)
		{
			Q_D(LBLSenderCardAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadSenderCardUuid pack;
			pack.SetCmdTargetDevice(d->m_targetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);
			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		QUuid LBLSenderCardCentralCtrl::getSenderCardUuid()
		{
			Q_D(LBLSenderCardAbstract);
			return d->m_realData.senderCardUuid;
		}

		quint8 LBLSenderCardCentralCtrl::getSenderCardUuidType()
		{
			Q_D(LBLSenderCardAbstract);
			return d->m_realData.senderCardUuidType;
		}

		quint16 LBLSenderCardCentralCtrl::writeScreenBlack(quint8 value, bool sync, int msec)
		{
			if (readScreenBlack(sync, msec).isEmpty()) {
				return LAPI::EResult::ER_INTECTRL_Fail_NoRet;
			}
			Q_D(LBLSenderCardAbstract);
			quint8 writeValue = d->m_gzData.reciverCtrl.screenCtrlPara;
			LBLUIHelper::bitSet(writeValue, 0, LBLUIHelper::bitGet(value, 0));
			QByteArray tempData;
			tempData.append(writeValue);
			quint32 addr = EReciverCtrlRegAddrs::ERCRA_ScreenCtrlParam;
			quint16 ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				d->m_gzData.reciverCtrl.screenCtrlPara = writeValue;
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::readScreenBlack(bool sync, int msec)
		{
			quint32 addr = EReciverCtrlRegAddrs::ERCRA_ScreenCtrlParam;
			quint16 len = 1;
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::getScreenBlack()
		{
			Q_D(LBLSenderCardAbstract);
			return LBLUIHelper::bitGet(d->m_gzData.reciverCtrl.screenCtrlPara, 0);
		}

		quint16 LBLSenderCardCentralCtrl::writeScreenLock(quint8 value, bool sync, int msec)
		{
			if (readScreenLock(sync, msec).isEmpty()) {
				return LAPI::EResult::ER_INTECTRL_Fail_NoRet;
			}
			Q_D(LBLSenderCardAbstract);
			quint8 writeValue = d->m_gzData.reciverCtrl.screenCtrlPara;
			LBLUIHelper::bitSet(writeValue, 1, LBLUIHelper::bitGet(value, 0));
			QByteArray tempData;
			tempData.append(writeValue);
			quint32 addr = EReciverCtrlRegAddrs::ERCRA_ScreenCtrlParam;
			quint16 ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				d->m_gzData.reciverCtrl.screenCtrlPara = writeValue;
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::readScreenLock(bool sync, int msec)
		{
			quint32 addr = EReciverCtrlRegAddrs::ERCRA_ScreenCtrlParam;
			quint16 len = 1;
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::getScreenLock()
		{
			Q_D(LBLSenderCardAbstract);
			return LBLUIHelper::bitGet(d->m_gzData.reciverCtrl.screenCtrlPara, 1);
		}

		quint16 LBLSenderCardCentralCtrl::writeZoomMode(quint8 value, bool sync, int msec)
		{
			if (readZoomMode(sync, msec).isEmpty()) {
				return LAPI::EResult::ER_INTECTRL_Fail_NoRet;
			}
			Q_D(LBLSenderCardAbstract);
			quint8 writeValue = d->m_gzData.normalSetting.scFeatureSwitch;
			LBLUIHelper::bitSet(writeValue, 1, LBLUIHelper::bitGet(value, 0));
			QByteArray tempData;
			tempData.append(writeValue);
			quint32 addr = ENormalSettingRegAddrs::ENSRA_SenderCardFeatureSwitch;
			quint16 ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				d->m_gzData.normalSetting.scFeatureSwitch = writeValue;
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::readZoomMode(bool sync, int msec)
		{
			quint32 addr = ENormalSettingRegAddrs::ENSRA_SenderCardFeatureSwitch;
			quint16 len = 1;
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::getZoomMode()
		{
			Q_D(LBLSenderCardAbstract);
			return LBLUIHelper::bitGet(d->m_gzData.normalSetting.scFeatureSwitch, 1);
		}

		quint16 LBLSenderCardCentralCtrl::writeZoomSize(QSize value, bool sync, int msec)
		{
			Q_D(LBLSenderCardAbstract);
			QByteArray tempData;
			quint16 tempValue = value.width();
			tempData.append((char *)&tempValue, 2);
			tempValue = value.height();
			tempData.append((char *)&tempValue, 2);
			quint32 addr = ENormalSettingRegAddrs::ENSRA_ZoomWidht;
			quint16 ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				d->m_gzData.normalSetting.zoomWidth = value.width();
				d->m_gzData.normalSetting.zoomHeight = value.height();
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::readZoomSize(bool sync, int msec)
		{
			quint32 addr = ENormalSettingRegAddrs::ENSRA_ZoomWidht;
			quint16 len = 4;
			return readFPGARegister(addr, len, sync, msec);
		}

		QSize LBLSenderCardCentralCtrl::getZoomSize()
		{
			Q_D(LBLSenderCardAbstract);
			return QSize(d->m_gzData.normalSetting.zoomWidth, d->m_gzData.normalSetting.zoomHeight);
		}

		quint16 LBLSenderCardCentralCtrl::writeErrorBitRateStatisticalSwitch(quint8 value, bool sync, int msec)
		{
			if (readErrorBitRateStatisticalSwitch(sync, msec).isEmpty()) {
				return LAPI::EResult::ER_INTECTRL_Fail_NoRet;
			}
			Q_D(LBLSenderCardAbstract);
			quint8 writeValue = d->m_gzData.normalSetting.rcFeatureSwitch;
			LBLUIHelper::bitSet(writeValue, 0, LBLUIHelper::bitGet(value, 0));
			QByteArray tempData;
			tempData.append(writeValue);
			quint32 addr = ENormalSettingRegAddrs::ENSRA_ReceiveCardFeatureSwitch;
			quint16 ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				d->m_gzData.normalSetting.rcFeatureSwitch = writeValue;
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::readErrorBitRateStatisticalSwitch(bool sync, int msec)
		{
			quint32 addr = ENormalSettingRegAddrs::ENSRA_ReceiveCardFeatureSwitch;
			quint16 len = 1;
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::getErrorBitRateStatisticalSwitch()
		{
			Q_D(LBLSenderCardAbstract);
			return LBLUIHelper::bitGet(d->m_gzData.normalSetting.rcFeatureSwitch, 0);
		}

		quint16 LBLSenderCardCentralCtrl::writeCorrectionSwitch(quint8 value, bool sync, int msec)
		{
			if (readErrorBitRateStatisticalSwitch(sync, msec).isEmpty()) {
				return LAPI::EResult::ER_INTECTRL_Fail_NoRet;
			}
			Q_D(LBLSenderCardAbstract);
			quint8 writeValue = d->m_gzData.normalSetting.rcFeatureSwitch;
			LBLUIHelper::bitSet(writeValue, 2, LBLUIHelper::bitGet(value, 0));
			QByteArray tempData;
			tempData.append(writeValue);
			quint32 addr = ENormalSettingRegAddrs::ENSRA_ReceiveCardFeatureSwitch;
			quint16 ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				d->m_gzData.normalSetting.rcFeatureSwitch = writeValue;
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::readCorrectionSwitch(bool sync, int msec)
		{
			quint32 addr = ENormalSettingRegAddrs::ENSRA_ReceiveCardFeatureSwitch;
			quint16 len = 1;
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::getCorrectionSwitch()
		{
			Q_D(LBLSenderCardAbstract);
			return LBLUIHelper::bitGet(d->m_gzData.normalSetting.rcFeatureSwitch, 2);
		}

		quint16 LBLSenderCardCentralCtrl::writeSpreadSpectrumSwitch(quint8 value, bool sync, int msec)
		{
			if (readErrorBitRateStatisticalSwitch(sync, msec).isEmpty()) {
				return LAPI::EResult::ER_INTECTRL_Fail_NoRet;
			}
			Q_D(LBLSenderCardAbstract);
			quint8 writeValue = d->m_gzData.normalSetting.rcFeatureSwitch;
			LBLUIHelper::bitSet(writeValue, 3, LBLUIHelper::bitGet(value, 0));
			QByteArray tempData;
			tempData.append(writeValue);
			quint32 addr = ENormalSettingRegAddrs::ENSRA_ReceiveCardFeatureSwitch;
			quint16 ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				d->m_gzData.normalSetting.rcFeatureSwitch = writeValue;
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::readSpreadSpectrumSwitch(bool sync, int msec)
		{
			quint32 addr = ENormalSettingRegAddrs::ENSRA_ReceiveCardFeatureSwitch;
			quint16 len = 1;
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::getSpreadSpectrumSwitch()
		{
			Q_D(LBLSenderCardAbstract);
			return LBLUIHelper::bitGet(d->m_gzData.normalSetting.rcFeatureSwitch, 3);
		}

		quint16 LBLSenderCardCentralCtrl::write24BitGammaSwitch(quint8 value, bool sync, int msec)
		{
			if (readErrorBitRateStatisticalSwitch(sync, msec).isEmpty()) {
				return LAPI::EResult::ER_INTECTRL_Fail_NoRet;
			}
			Q_D(LBLSenderCardAbstract);
			quint8 writeValue = d->m_gzData.normalSetting.rcFeatureSwitch;
			LBLUIHelper::bitSet(writeValue, 4, LBLUIHelper::bitGet(value, 0));
			QByteArray tempData;
			tempData.append(writeValue);
			quint32 addr = ENormalSettingRegAddrs::ENSRA_ReceiveCardFeatureSwitch;
			quint16 ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				d->m_gzData.normalSetting.rcFeatureSwitch = writeValue;
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::read24BitGammaSwitch(bool sync, int msec)
		{
			quint32 addr = ENormalSettingRegAddrs::ENSRA_ReceiveCardFeatureSwitch;
			quint16 len = 1;
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::get24BitGammaSwitch()
		{
			Q_D(LBLSenderCardAbstract);
			return LBLUIHelper::bitGet(d->m_gzData.normalSetting.rcFeatureSwitch, 4);
		}

		quint16 LBLSenderCardCentralCtrl::writeProtocolType(quint8 value, bool sync, int msec)
		{
			if (readProtocolType(sync, msec).isEmpty()) {
				return LAPI::EResult::ER_INTECTRL_Fail_NoRet;
			}
			Q_D(LBLSenderCardAbstract);
			quint8 writeValue = d->m_gzData.reciverCtrl.protocolType;
			LBLUIHelper::bitSet(writeValue, 0, LBLUIHelper::bitGet(value, 0));
			QByteArray tempData;
			tempData.append(writeValue);
			quint32 addr = EReciverCtrlRegAddrs::ERCRA_ProtocolType;
			quint16 ret = writeFPGARegister(addr, tempData, sync, msec);
			if (ret == LAPI::EResult::ER_Success) {
				d->m_gzData.reciverCtrl.protocolType = writeValue;
			}
			return ret;
		}

		QByteArray LBLSenderCardCentralCtrl::readProtocolType(bool sync, int msec)
		{
			quint32 addr = EReciverCtrlRegAddrs::ERCRA_ProtocolType;
			quint16 len = 1;
			return readFPGARegister(addr, len, sync, msec);
		}

		quint8 LBLSenderCardCentralCtrl::getProtocolType()
		{
			Q_D(LBLSenderCardAbstract);
			return LBLUIHelper::bitGet(d->m_gzData.reciverCtrl.protocolType, 0);
		}

		bool LBLSenderCardCentralCtrl::init()
		{
			registerCallBack();
			return true;
		}

		void LBLSenderCardCentralCtrl::registerCallBack()
		{
			Q_D(LBLSenderCardAbstract);

			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteSCFPGARegister(),
				std::bind(&LBLSenderCardCentralCtrl::onParseWriteFPGARegister, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadSCFPGARegister(),
				std::bind(&LBLSenderCardCentralCtrl::onParseReadFPGARegister, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadMCUAppVersion(),
				std::bind(&LBLSenderCardCentralCtrl::onParseReadMCUAppVersion, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadMCUBootVersion(),
				std::bind(&LBLSenderCardCentralCtrl::onParseReadMCUBootVersion, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteSaveSCParam(),
				std::bind(&LBLSenderCardCentralCtrl::onParseWriteSaveSCParam, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadVideoSourceBrightness(),
				std::bind(&LBLSenderCardCentralCtrl::onParseReadBrightness, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteVideoSourceBrightness(),		
				std::bind(&LBLSenderCardCentralCtrl::onParseWriteBrightness, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteSenderCardUuid(),
				std::bind(&LBLSenderCardCentralCtrl::onParseWriteSenderCardUuid, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadSenderCardUuid(),
				std::bind(&LBLSenderCardCentralCtrl::onParseReadSenderCardUuid, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_SendConnection(),
				std::bind(&LBLSenderCardCentralCtrl::onParseSendConnection, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadConnection(),
				std::bind(&LBLSenderCardCentralCtrl::onParseReadConnection, this, std::placeholders::_1));
		}

		quint16 LBLSenderCardCentralCtrl::onParseWriteFPGARegister(const QByteArray& data)
        {
			LBLPackageInteCtrl_WriteSCFPGARegister pack(data);
			quint16 ret = pack.getOperationResult();
			return ret;
		}

		quint16 LBLSenderCardCentralCtrl::onParseReadFPGARegister(const QByteArray & data)
		{
			Q_D(LBLSenderCardAbstract);
			LBLPackageInteCtrl_ReadSCFPGARegister pack(data);
			quint16 ret = pack.getOperationResult();
			if (LAPI::EResult::ER_INTECTRL_Success != ret)
				return ret;
			quint16 len = pack.getDataLength();
			d->senderCardReadFPGARegister = pack.getReplyData();
			switch (pack.getAddress())
			{
			case ENormalSettingRegAddrs::ENSRA_FPGABigVersion:
			{
				memcpy_s(&(d->m_gzData.normalSetting.FPGABigVersio), len, d->senderCardReadFPGARegister, len);
			}
			break;
			case ENormalSettingRegAddrs::ENSRA_SenderCardFeatureSwitch:
			{
				memcpy_s(&(d->m_gzData.normalSetting.scFeatureSwitch), len, d->senderCardReadFPGARegister, len);
			}
			break;
			case ENormalSettingRegAddrs::ENSRA_ReceiveCardFeatureSwitch:
			{
				memcpy_s(&(d->m_gzData.normalSetting.rcFeatureSwitch), len, d->senderCardReadFPGARegister, len);
			}
			case ENormalSettingRegAddrs::ENSRA_ZoomWidht:
			{
				memcpy_s(&(d->m_gzData.normalSetting.zoomWidth), len, d->senderCardReadFPGARegister, len);
			}
			break;
			case ESelfTestRegAddrs::ESTRA_TestModeStatus:
			{
				memcpy_s(&(d->m_gzData.selfTest.testModeStatus), len, d->senderCardReadFPGARegister, len);
			}
			break;
			case ESelfTestRegAddrs::ESTRA_TestSourceMode:
			{
				memcpy_s(&(d->m_gzData.selfTest.testSourceMode), len, d->senderCardReadFPGARegister, len);
			}
			break;
			case ESelfTestRegAddrs::ESTRA_TestSourceSpeed:
			{
				memcpy_s(&(d->m_gzData.selfTest.testSourceSpeed), len, d->senderCardReadFPGARegister, len);
			}
			break;
			case EEthLoadRegAddrs::EELRA_EthLoadArea:
			{
				memcpy_s(&(d->m_gzData.sendCardEthLoad.ethLoadArea), len, d->senderCardReadFPGARegister, len);
			}
			break;
			case EReciverCtrlRegAddrs::ERCRA_ScreenCtrlParam:
			{
				memcpy_s(&(d->m_gzData.reciverCtrl.screenCtrlPara), len, d->senderCardReadFPGARegister, len);
			}
			break;
			case EReciverCtrlRegAddrs::ERCRA_ProtocolType:
			{
				memcpy_s(&(d->m_gzData.reciverCtrl.protocolType), len, d->senderCardReadFPGARegister, len);
			}
			break;
			case EProjectSelfTestRegAddrs::EPSTRA_EthErrorRate:
			{
				memcpy_s(&(d->m_gzData.projectSelfTest.errorRate), len, d->senderCardReadFPGARegister, len);
			}
			break;
			default:
				break;
			}
			return ret;
		}

		quint16 LBLSenderCardCentralCtrl::onParseReadMCUAppVersion(const QByteArray & data)
		{
			Q_D(LBLSenderCardAbstract);
			LBLPackageInteCtrl_ReadMCUAppVersion pack(data);
			d->m_realData.mcuAppVersion = pack.getVersion();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLSenderCardCentralCtrl::onParseReadMCUBootVersion(const QByteArray & data)
		{
			Q_D(LBLSenderCardAbstract);
			LBLPackageInteCtrl_ReadMCUBootVersion pack(data);
			d->m_realData.mcuBootVersion = pack.getVersion();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLSenderCardCentralCtrl::onParseWriteSaveSCParam(const QByteArray & data)
        {
			LBLPackageInteCtrl_WriteSaveSCParam pack(data);
			return pack.getOperationResult();
		}

		quint16 LBLSenderCardCentralCtrl::onParseWriteBrightness(const QByteArray & data)
		{
			Q_D(LBLSenderCardAbstract);

			LBLPackageInteCtrl_WriteVideoSourceBrightness pack(data);
			quint16 ret = pack.getOperationResult();
			if (ret == LBLPackage::EOR_Success)
			{
				d->m_realData.brightness = d->m_cacheData.brightness;
			}
			return ret;
		}

		quint16 LBLSenderCardCentralCtrl::onParseReadBrightness(const QByteArray & data)
		{
			Q_D(LBLSenderCardAbstract);

			LBLPackageInteCtrl_ReadVideoSourceBrightness pack(data);
			d->m_realData.brightness = pack.getBrightness();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLSenderCardCentralCtrl::onParseWriteSenderCardUuid(const QByteArray & data)
		{
			Q_D(LBLSenderCardAbstract);

			LBLPackageInteCtrl_WriteSenderCardUuid pack(data);
			quint16 ret = pack.getOperationResult();
			if (ret == LBLPackage::EOR_Success)
			{
				d->m_realData.senderCardUuid = d->m_cacheData.senderCardUuid;
				d->m_realData.senderCardUuidType = d->m_cacheData.senderCardUuidType;
			}
			return ret;
		}

		quint16 LBLSenderCardCentralCtrl::onParseReadSenderCardUuid(const QByteArray & data)
		{
			Q_D(LBLSenderCardAbstract);

			LBLPackageInteCtrl_ReadSenderCardUuid pack(data);
			d->m_parentItemDetectInfo->uuid = getSenderCardUuid();
			d->m_parentItemDetectInfo->uuidType = getSenderCardUuidType();
			d->m_realData.senderCardUuid = pack.getSenderCardUuid();
			d->m_realData.senderCardUuidType = pack.getSenderCardUuidType();
			return LBLPackage::EOR_Success;
		}

		quint16 LBLSenderCardCentralCtrl::onParseSendConnection(const QByteArray & data)
        {
			LBLPackageInteCtrl_SendConnection pack(data);
			return pack.getOperationResult();
		}
		
		quint16 LBLSenderCardCentralCtrl::onParseReadConnection(const QByteArray& data)
		{
			Q_D(LBLSenderCardAbstract);

			LBLPackageInteCtrl_ReadConnection pack(data);
			quint16 ret = pack.getOperationResult();
			quint16 len = pack.getReplayDataLength();
            Q_UNUSED(len);
			if (ret == LBLPackage::EOR_Success)
			{
				QByteArray reData = pack.getReplyData();
				if (!d->senderCardConnectionBuffer.contains(reData)) {
					d->senderCardConnectionBuffer.append(reData);
				}
			}
			return ret;
		}
	}
}
