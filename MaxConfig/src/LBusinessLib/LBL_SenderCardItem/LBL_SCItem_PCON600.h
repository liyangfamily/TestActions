/****************************************************************************
**
** This Interface file is part of the SenderCardItem module of the LBusinessLib.
** 这个是LBusinessLib中AbstractSenderCardItem派生子类发送卡，该模块不对外开放
**
** 该接口文件为LED系统中PCON600发送卡对象，用于管理2ndPlus发送卡的业务和数据
**
****************************************************************************/
#ifndef CVTE_H_LBL_SENDERCARDITEM_PCON600
#define CVTE_H_LBL_SENDERCARDITEM_PCON600
#pragma once

#include "LBL_SenderCardItem/LBLAbstractSCItem.h"

namespace LBL
{
	namespace SCItem
	{
		template<class AbstractSenderCardItem_t, class ConSenderCardItem_t> 
		class SenderCardItemFactory; //前置声明，告诉编译器工厂为模板

		class SenderCardItem_PCON600Private;
		class LBL_SENDERCARDITEM_EXPORT SenderCardItem_PCON600 : public LBLAbstractSCItem
		{
			Q_DECLARE_PRIVATE(SenderCardItem_PCON600)
		public:
			~SenderCardItem_PCON600();
			//发送卡属性
			virtual QString senderCardTag() const override;
			/*********************************************************************************************************
			**发送卡相关接口
            *********************************************************************************************************/
			quint16 writeBrightness(int value, bool sync, int msec) override;
			quint16 readBrightness(bool sync, int msec) override;
			int  getBrightness() override;

			//发送卡寄存器相关接口
			virtual quint16 writeSCFPGARegister(quint32 addr, QByteArray value, bool sync, int msec) override;
			virtual QByteArray readSCFPGARegister(quint32 addr, quint16 len, bool sync, int msec) override;
			virtual QByteArray getSCFPGARegister() override;

			virtual QByteArray readSCFPGAVersion(bool sync, int msec) override;
			virtual QString getSCFPGAVersion() override;

			virtual quint16 writeSCFPGAEthLoad(const QList<LBLSPort>& value, bool sync, int msec) override;
			virtual QByteArray readSCFPGAEthLoad(bool sync, int msec) override;
			virtual QList<LBLSPort> getSCFPGAEthLoad() override;

			virtual quint16 writeSaveSCParam(bool sync, int msec) override;

			virtual quint16 writeSCSelfTestMode(quint8 mode, bool sync, int msec) override;
			virtual QByteArray readSCSelfTestMode(bool sync, int msec) override;
			virtual quint8 getSCSelfTestMode() override;

			virtual quint16 writeSCSelfTestModeSpeed(quint8 speed, bool sync, int msec) override;
			virtual QByteArray readSCSelfTestModeSpeed(bool sync, int msec) override;
			virtual quint8 getSCSelfTestModeSpeed() override;

			virtual quint16 writeSCScreenBlack(quint8 value, bool sync, int msec) override;
			virtual QByteArray readSCScreenBlack(bool sync, int msec) override;
			virtual quint8 getSCScreenBlack() override;

			virtual quint16 writeSCScreenLock(quint8 value, bool sync, int msec) override;
			virtual QByteArray readSCScreenLock(bool sync, int msec) override;
			virtual quint8 getSCScreenLock() override;

			virtual quint16 writeSCZoomMode(quint8 value, bool sync, int msec) override;
			virtual QByteArray readSCZoomMode(bool sync, int msec) override;
			virtual quint8 getSCZoomMode() override;

			virtual quint16 writeSCZoomSize(QSize value, bool sync, int msec) override;
			virtual QByteArray readSCZoomSize(bool sync, int msec) override;
			virtual QSize getSCZoomSize() override;

			virtual quint16 writeSCErrorBitRateStatisticalSwitch(quint8 value, bool sync, int msec)override;
			virtual QByteArray readSCErrorBitRateStatisticalSwitch(bool sync, int msec)override;
			virtual quint8 getSCErrorBitRateStatisticalSwitch()override;

			virtual quint16 writeSCCorrectionSwitch(quint8 value, bool sync, int msec)override;
			virtual QByteArray readSCCorrectionSwitch(bool sync, int msec)override;
			virtual quint8 getSCCorrectionSwitch()override;

			virtual quint16 writeSCSpreadSpectrumSwitch(quint8 value, bool sync, int msec)override;
			virtual QByteArray readSCSpreadSpectrumSwitch(bool sync, int msec)override;
			virtual quint8 getSCSpreadSpectrumSwitch()override;

			virtual quint16 writeSC24BitGammaSwitch(quint8 value, bool sync, int msec)override;
			virtual QByteArray readSC24BitGammaSwitch(bool sync, int msec)override;
			virtual quint8 getSC24BitGammaSwitch()override;

			virtual quint16 writeSCProtocolType(quint8 value, bool sync, int msec) override;
			virtual QByteArray readSCProtocolType(bool sync, int msec) override;
			virtual quint8  getSCProtocolType() override;
			/*********************************************************************************************************
			**连接关系相关
            *********************************************************************************************************/
			virtual quint16 writeConnection(LBLConnection* value, bool sync, int msec) override;
			virtual quint16 readConnection(bool sync, int msec) override;

			/*********************************************************************************************************
			**接收卡相关
            *********************************************************************************************************/
			virtual quint16 writeRCFPGARegister(quint8 port, quint8 module, quint32 addr, QByteArray value, bool sync, int msec) override;
			virtual QByteArray readRCFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 len, bool sync, int msec) override;
			virtual QByteArray getRCFPGARegister() override;

            virtual quint16 writeModuleParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec) override;
            virtual QByteArray readModuleParam(quint8 port, quint8 module, bool sync, int msec) override;
            virtual QByteArray getModuleParam() override;

            virtual quint16 writeDriveICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec) override;
            virtual QByteArray readDriveICParam(quint8 port, quint8 module, bool sync, int msec) override;
            virtual QByteArray getDriveICParam() override;

            virtual quint16 writeDecodingICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec) override;
            virtual QByteArray readDecodingICParam(quint8 port, quint8 module, bool sync, int msec) override;
            virtual QByteArray getDecodingICParam() override;

            virtual quint16 writeCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec) override;
			virtual quint16 writeCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec) override;
            virtual quint16 writeCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec) override;

			virtual QList<RC::SRCStatusInfo> readRCStatusInfo(bool sync, int msec) override;
			virtual QList<RC::SRCStatusInfo> readRCStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag, bool sync, int msec)override;
			virtual QList<RC::SRCStatusInfo> getRCStatusInfo() override;

			virtual QList<RC::SRCMonitorInfo> readRCMonitorInfo(quint8 portIndex, bool sync, int msec) override;
			virtual QList<RC::SRCMonitorInfo> getRCMonitorInfo() override;

            virtual quint16 writeSaveRCParam(quint8 port, quint16 module, bool sync, int msec) override;

			/*********************************************************************************************************
			**视频处理相关
			*********************************************************************************************************/
			virtual quint16 writeHDMIByPassStatus(const quint8 value, bool sync, int msec) override;
			virtual quint16 readHDMIByPassStatus(bool sync, int msec) override;
			virtual quint16 getHDMIByPassStatus() override;

			virtual quint16 writeHDMIImageRatio(const quint8 value, bool sync, int msec) override;
			virtual quint16 readHDMIImageRatio(bool sync, int msec) override;
			virtual quint8  getHDMIImageRatio() override;

			virtual quint16 writeHDMIInputSource(const quint8 value, bool sync, int msec) override;
			virtual quint16 readHDMIInputSource(bool sync, int msec) override;
			virtual quint8  getHDMIInputSource() override;

			virtual quint16 writeHDMIImageContrast(const quint8 value, bool sync, int msec) override;
			virtual quint16 readHDMIImageContrast(bool sync, int msec) override;
			virtual quint8  getHDMIImageContrast() override;

			virtual quint16 writeHDMIImageColorTtemperature(const quint8 value, bool sync, int msec) override;
			virtual quint16 readHDMIImageColorTtemperature(bool sync, int msec) override;
			virtual quint8  getHDMIImageColorTtemperature() override;

			virtual quint16 writeHDMIImageBrightness(const quint8 value, bool sync, int msec) override;
			virtual quint16 readHDMIImageBrightness(bool sync, int msec) override;
			virtual quint8  getHDMIImageBrightness() override;

			virtual quint16 writeHDMIRGBGain(const int rValue, const int gValue, const int bValue, bool sync, int msec) override;
			virtual quint16 readHDMIRGBGain(bool sync, int msec) override;
			virtual QList<quint8> getHDMIRGBGain() override;

			virtual quint16 readHDMIInputSignalInfo(bool sync, int msec) override;
			virtual QString getHDMIInputSignalInfo() override;

			virtual quint16 readHDMIVersion(bool sync, int msec) override;
			virtual QString getHDMIVersion() override;

			virtual quint16 writeHDMIMultiScreenMode(const quint8 value, bool sync, int msec) override;
			virtual quint16 readHDMIMultiScreenMode(bool sync, int msec) override;
			virtual quint8  getHDMIMultiScreenMode() override;

			virtual quint16 writeHDMIMultiScreenInputSource(const quint8 param, const quint8 channel, bool sync, int msec)override;
			virtual quint16 writeHDMIMultiScreenInputSourceList(const QList<quint8>& values, bool sync, int msec)override;
			virtual quint16 readHDMIMultiScreenInputSource(const quint8 channel, bool sync, int msec)override;
			virtual QList<quint8>  getHDMIMultiScreenInputSource(const quint8 channel)override;
			
			virtual quint16 resetHDMISetting(bool sync, int msec) override;

			virtual quint16 writeHDIMIWindowSize(QSize value, quint8 channel, bool sync, int msec)  override;
			virtual quint16 readHDIMIWindowSize(quint8 channel, bool sync, int msec)  override;
			virtual QSize  getHDIMIWindowSize()  override;

			virtual quint16 writeHDIMIWindowPos(QPoint value, quint8 channel, bool sync, int msec)  override;
			virtual quint16 readHDIMIWindowPos(quint8 channel, bool sync, int msec)  override;
			virtual QPoint  getHDIMIWindowPos()  override;

			virtual quint16 writeHDIMIWindowStatus(quint8 status, quint8 channel, bool sync, int msec)  override;
			virtual quint16 readHDIMIWindowStatus(quint8 channel, bool sync, int msec)  override;
			virtual quint8  getHDIMIWindowStatus()  override;

			virtual quint16 writeHDIMIAudioSrc(quint8 param, quint8 channel, bool sync, int msec) override;
			virtual quint16 readHDIMIAudioSrc(quint8 channel, bool sync, int msec)  override;
			virtual quint8  getHDIMIAudioSrc()  override;

			//文件升级
			virtual quint16 upgradeFile(bool sync, int msec, quint16 fileType, QString fileName) override;
			virtual quint16 upgradeFile(bool sync, int msec, quint16 fileType, QByteArray data) override;
			virtual quint16 requestFile(bool sync, int msec, quint16 fileType, QString fileName) override;
			virtual quint16 requestFile(bool sync, int msec, quint16 fileType, QByteArray& data) override;

			/*********************************************************************************************************
			**Android设备
			*********************************************************************************************************/
			virtual quint16 readAndroidVersion(bool sync, int msec) override;
			virtual QString getAndroidVersion() override;

			virtual quint16 writeKeyEvent(quint8 status, quint16 keyCode, bool sync, int msec) override;
			virtual quint16 getKeyEvent_Result() override;

			virtual quint16 writeDeviceName(QString name, bool sync, int msec) override;
			virtual quint16 readDeviceName(bool sync, int msec) override;
			virtual QString getDeviceName() override;

			/*********************************************************************************************************
			**Android设备 测试相关
			*********************************************************************************************************/
			virtual quint16 readNetDeviceOnlineStatus(QString ip, bool sync, int msec) override;
			virtual quint16 getNetDevice_Status() override;
			virtual QString getNetDevice_IP() override;

			virtual quint16 readSCEthLoopTestResult(bool sync, int msec) override;
			virtual quint16 getSCEthLoopTest_Result() override;
			virtual quint8  getSCEthLoopTest_EffectiveEthCount() override;
			virtual QByteArray  getSCEthLoopTest_ReplyData() override;
			virtual QMap<quint8, float>  getSCEthLoopTest_BitErrRate() override;

			virtual quint16 readUDiskMountingStatus(bool sync, int msec) override;
			virtual quint8  getUDiskMounting_Count() override;
			virtual QStringList getUDiskMounting_List() override;

			virtual quint16 writeStartOSDTest(bool sync, int msec) override;
			virtual quint8  getOSDTest_WhiteScreenTestResult() override;
			virtual quint8 getOSDTest_BlackScreenTestResult() override;

			virtual quint16 writeRelaySwitc(quint8 status, bool sync, int msec) override;
			virtual quint16 getRelaySwitc_Result() override;
			virtual quint8  getRelaySwitc_Status() override;

			virtual quint16 writeEnterKeyTest(quint8 status, bool sync, int msec) override;
			virtual quint8  getKeyTest_Result() override;

			virtual quint16 readKeyTestResult(bool sync, int msec) override;
			virtual quint8  getKeyTestResult_Count() override;
			virtual QList<quint16>  getKeyTestResult_List() override;

			virtual quint16 readOpticalSensorParam(bool sync, int msec) override;
			virtual quint16 getOpticalSensor_Param() override;

			virtual quint16 readRouterStatus(bool sync, int msec) override;
			virtual quint8 getRouter_5GWifiStatus() override;
			virtual quint8 getRouter_2_4GWifiStatus() override;

			virtual quint16 writeNetworkCardMACAddr(quint8 flage, QByteArray mac, bool sync, int msec) override;
			virtual quint16 getNetworkCardMACAddr_Results() override;
			virtual quint8  getNetworkCardMACAddr_Flage() override;
			virtual QByteArray getNetworkCardMACAddr_MAC() override;

			virtual quint16 writePlayTestSound_1KHZ(quint8 status, bool sync, int msec) override;
			virtual quint16 getPlayTestSound_Results() override;
			virtual quint8  getPlayTestSound_Status() override;

			virtual quint16 writeWIFIModuleScanTest(quint8 status, bool sync, int msec) override;
			virtual quint16 getWIFIModuleScanTest_Results() override;

			virtual quint16 readWIFIScanList(bool sync, int msec) override;
			virtual quint8  getWIFIScanList_Count() override;

			virtual quint16 readLoadPowerAmplifierChipParam(bool sync, int msec) override;
			virtual quint8  getPowerAmplifierChipParam_Results() override;
			virtual quint8  getPowerAmplifierChipParam_30Results() override;
			virtual quint8  getPowerAmplifierChipParam_31Results() override;

			virtual quint16 readCOMLoopTestResult(bool sync, int msec) override;
			virtual quint8 getCOMLoopTest_INResult() override;
			virtual quint8 getCOMLoopTest_OUTResult() override;

			virtual quint16 writeEnterTestMode(QString key, bool sync, int msec) override;
			virtual quint16  getEnterTestMode_Results() override;
		protected:
			SenderCardItem_PCON600(QObject* parent = 0); //禁用外部创建
			SenderCardItem_PCON600(SenderCardItem_PCON600Private& dd, QObject* parent = 0);; // 允许子类通过它们自己的私有结构体来初始化
			bool registerControl() override; 
			bool dispatcherPackage(const LBLEnginePackage& pack) override;
			friend class SenderCardItemFactory<LBLAbstractSCItem, SenderCardItem_PCON600>; //声明为一对一的好友关系，让工厂可以访问protected构造函数
		};
	}
}
#endif
