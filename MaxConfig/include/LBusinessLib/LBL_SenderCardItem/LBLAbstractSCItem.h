/*********************************************************************************************************
** This file is part of the LBL_SenderCardItem module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBL_ABSTRACTSENDERCARDITEM
#define CVTE_H_LBL_ABSTRACTSENDERCARDITEM
#pragma once

#include <LBL_SenderCardItem/LBLSCItemGlobal>

#include <LBL_SenderCardItem/LBLSCItemStructGlobal>
#include <LBL_CommunicatEngine/LBLPackageDispatcher>

#include <LBL_Core/LBLConnection>
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_Cored.lib")
#else
#pragma comment(lib,"LBL_Core.lib")
#endif
#endif

#include <QString>
#include <QUuid>
#include <QScopedPointer>
#include <QtConcurrent/QtConcurrentRun>
namespace LBL
{
	namespace SCItem
	{
		class LBLAbstractSCItemPrivate;
		class LBL_SENDERCARDITEM_EXPORT LBLAbstractSCItem :public QObject//FIXME:类用C开头
		{
			Q_DECLARE_PRIVATE(LBLAbstractSCItem)
			friend class LBLSCItemManager;
		public:
			virtual ~LBLAbstractSCItem();
			bool setDetectInfoStruct(const SDetectItemInfo*);
			virtual bool registerControl() = 0;
			//发送卡对象属性获取，需要加入发送卡ID，序号相关的属性
            bool isUsing();
			QUuid internalUuid();
			EDeviceDetectType detectType() const;
			ECommunicatType communType() const;
			ESenderCardStatus senderCardStatus() const;
			ESenderCardClass senderCardClass() const;
			EProductType productType() const;
			SNetInfo netInfo() const;
			SComInfo comInfo() const;
			QObject* socketObject() const;
			QString hostName() const;
			quint8 itemUuidType() const;
			QUuid itemUuid() const;
			quint8 senderCardIndex() const;
			virtual QString senderCardTag() const;
			void checkItemInfo();
			/*********************************************************************************************************
			**发送卡相关接口                                                                     
            *********************************************************************************************************/
			virtual quint16 writeBrightness(int value, bool sync, int msec);
			virtual quint16 readBrightness(bool sync, int msec);
			virtual int  getBrightness();

			virtual quint16 writeSCFPGARegister(quint32 addr, QByteArray value, bool sync, int msec);
			virtual QByteArray readSCFPGARegister(quint32 addr, quint16 len, bool sync, int msec);
			virtual QByteArray getSCFPGARegister();

			virtual QByteArray readSCFPGAVersion(bool sync, int msec);
			virtual QString getSCFPGAVersion();

			virtual quint16 writeSCFPGAEthLoad(const QList<LBLSPort>& value, bool sync, int msec);
			virtual QByteArray readSCFPGAEthLoad(bool sync, int msec);
			virtual QList<LBLSPort> getSCFPGAEthLoad();

			virtual quint16 readMCUAppVersion(bool sync, int msec);
			virtual QString getMCUAppVersion();
			virtual quint16 readMCUBootVersion(bool sync, int msec);
			virtual QString getMCUBootVersion();

			virtual quint16 writeSaveSCParam(bool sync, int msec);

			virtual quint16 writeSCSelfTestMode(quint8 mode, bool sync, int msec);
			virtual QByteArray readSCSelfTestMode(bool sync, int msec);
			virtual quint8 getSCSelfTestMode();

			virtual quint16 writeSCSelfTestModeSpeed(quint8 speed, bool sync, int msec);
			virtual QByteArray readSCSelfTestModeSpeed(bool sync, int msec);
			virtual quint8 getSCSelfTestModeSpeed();

			virtual quint16 writeSCScreenBlack(quint8 value, bool sync, int msec);
			virtual QByteArray readSCScreenBlack(bool sync, int msec);
			virtual quint8 getSCScreenBlack();

			virtual quint16 writeSCScreenLock(quint8 value, bool sync, int msec);
			virtual QByteArray readSCScreenLock(bool sync, int msec);
			virtual quint8 getSCScreenLock();

			virtual quint16 writeSCZoomMode(quint8 value, bool sync, int msec);
			virtual QByteArray readSCZoomMode(bool sync, int msec);
			virtual quint8 getSCZoomMode();

			virtual quint16 writeSCZoomSize(QSize value, bool sync, int msec);
			virtual QByteArray readSCZoomSize(bool sync, int msec);
			virtual QSize getSCZoomSize();

			virtual quint16 writeSCErrorBitRateStatisticalSwitch(quint8 value, bool sync, int msec);
			virtual QByteArray readSCErrorBitRateStatisticalSwitch(bool sync, int msec);
			virtual quint8 getSCErrorBitRateStatisticalSwitch();

			virtual quint16 writeSCCorrectionSwitch(quint8 value, bool sync, int msec);
			virtual QByteArray readSCCorrectionSwitch(bool sync, int msec);
			virtual quint8 getSCCorrectionSwitch();

			virtual quint16 writeSCSpreadSpectrumSwitch(quint8 value, bool sync, int msec);
			virtual QByteArray readSCSpreadSpectrumSwitch(bool sync, int msec);
			virtual quint8 getSCSpreadSpectrumSwitch();

			virtual quint16 writeSC24BitGammaSwitch(quint8 value, bool sync, int msec);
			virtual QByteArray readSC24BitGammaSwitch(bool sync, int msec);
			virtual quint8 getSC24BitGammaSwitch();

			virtual quint16 writeSCProtocolType(quint8 value, bool sync, int msec);
			virtual QByteArray readSCProtocolType(bool sync, int msec);
			virtual quint8  getSCProtocolType();
			/*********************************************************************************************************
			**连接关系相关
            *********************************************************************************************************/
			virtual quint16 writeConnection(LBLConnection* value, bool sync = true, int msec = 5000);//默认同步读取
			virtual quint16 readConnection(bool sync = true, int msec = 3000); //默认同步读取
			LBLConnection* getConnection();

			/*********************************************************************************************************
			**接收卡相关                                                                     
            *********************************************************************************************************/
			virtual quint16 writeRCFPGARegister(quint8 port, quint8 module, quint32 addr, QByteArray value, bool sync, int msec);
			virtual QByteArray readRCFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 len, bool sync, int msec);
			virtual QByteArray getRCFPGARegister();

            virtual quint16 writeModuleParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec);
            virtual QByteArray readModuleParam(quint8 port, quint8 module, bool sync, int msec);
            virtual QByteArray getModuleParam();

            virtual quint16 writeDriveICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec);
            virtual QByteArray readDriveICParam(quint8 port, quint8 module, bool sync, int msec);
            virtual QByteArray getDriveICParam();

            virtual quint16 writeDecodingICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec);
            virtual QByteArray readDecodingICParam(quint8 port, quint8 module, bool sync, int msec);
            virtual QByteArray getDecodingICParam();

            virtual quint16 writeCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec);
            virtual quint16 writeCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec);
            virtual quint16 writeCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec);

			virtual QList<RC::SRCStatusInfo> readRCStatusInfo(bool sync, int msec);
			virtual QList<RC::SRCStatusInfo> readRCStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag, bool sync, int msec);
			virtual QList<RC::SRCStatusInfo> getRCStatusInfo();

			virtual QList<RC::SRCMonitorInfo> readRCMonitorInfo(quint8 portIndex, bool sync, int msec);
			virtual QList<RC::SRCMonitorInfo> getRCMonitorInfo();

            virtual quint16 writeSaveRCParam(quint8 port, quint16 module, bool sync, int msec);

			/*********************************************************************************************************
			**视频处理相关
			*********************************************************************************************************/
			virtual quint16 writeHDMIByPassStatus(const quint8 value, bool sync, int msec);
			virtual quint16 readHDMIByPassStatus(bool sync, int msec);
			virtual quint16 getHDMIByPassStatus();

			virtual quint16 writeHDMIImageRatio(const quint8 value, bool sync, int msec);
			virtual quint16 readHDMIImageRatio(bool sync, int msec);
			virtual quint8  getHDMIImageRatio();

			virtual quint16 writeHDMIInputSource(const quint8 value, bool sync, int msec);
			virtual quint16 readHDMIInputSource(bool sync, int msec);
			virtual quint8  getHDMIInputSource();

			virtual quint16 writeHDMIImageContrast(const quint8 value, bool sync, int msec);
			virtual quint16 readHDMIImageContrast(bool sync, int msec);
			virtual quint8  getHDMIImageContrast();

			virtual quint16 writeHDMIImageColorTtemperature(const quint8 value, bool sync, int msec);
			virtual quint16 readHDMIImageColorTtemperature(bool sync, int msec);
			virtual quint8  getHDMIImageColorTtemperature();

			virtual quint16 writeHDMIImageBrightness(const quint8 value, bool sync, int msec);
			virtual quint16 readHDMIImageBrightness(bool sync, int msec);
			virtual quint8  getHDMIImageBrightness();

			virtual quint16 writeHDMIRGBGain(const int rValue, const int gValue, const int bValue, bool sync, int msec);
			virtual quint16 readHDMIRGBGain(bool sync, int msec);
			virtual QList<quint8>  getHDMIRGBGain();

            virtual quint16 readHDMIInputSignalInfo(bool sync, int msec);
            virtual QString getHDMIInputSignalInfo();

			virtual quint16 readHDMIVersion(bool sync, int msec);
			virtual QString getHDMIVersion();

			virtual quint16 writeHDMIMultiScreenMode(const quint8 value, bool sync, int msec);
			virtual quint16 readHDMIMultiScreenMode(bool sync, int msec);
			virtual quint8  getHDMIMultiScreenMode();

			virtual quint16 writeHDMIMultiScreenInputSource(const quint8 param, const quint8 channel, bool sync, int msec);
			virtual quint16 writeHDMIMultiScreenInputSourceList(const QList<quint8>& values, bool sync, int msec);
			virtual quint16 readHDMIMultiScreenInputSource(const quint8 channel, bool sync, int msec);
			virtual QList<quint8>  getHDMIMultiScreenInputSource(const quint8 channel);

			virtual quint16 resetHDMISetting(bool sync, int msec);

			virtual quint16 writeHDIMIWindowSize(QSize value, quint8 channel, bool sync, int msec);
			virtual quint16 readHDIMIWindowSize(quint8 channel, bool sync, int msec);
			virtual QSize  getHDIMIWindowSize();

			virtual quint16 writeHDIMIWindowPos(QPoint value, quint8 channel, bool sync, int msec);
			virtual quint16 readHDIMIWindowPos(quint8 channel, bool sync, int msec);
			virtual QPoint  getHDIMIWindowPos();

			virtual quint16 writeHDIMIWindowStatus(quint8 status, quint8 channel, bool sync, int msec);
			virtual quint16 readHDIMIWindowStatus(quint8 channel, bool sync, int msec);
			virtual quint8  getHDIMIWindowStatus();

			virtual quint16 writeHDIMIAudioSrc(quint8 param, quint8 channel, bool sync, int msec);
			virtual quint16 readHDIMIAudioSrc(quint8 channel, bool sync, int msec);
			virtual quint8  getHDIMIAudioSrc();

			//文件升级
			virtual bool isUpgradeSend();
			virtual quint16 upgradingFileType();
			virtual quint8 upgradingPortIndex();
			virtual quint16 upgradingModuleIndex();

			virtual bool isUpgradeStarted();
			virtual bool isUpgrading();
			virtual bool isUpgradeFinished();
			virtual bool cancelUpgrade();
			virtual quint16 upgradeResult();
			virtual QFuture<quint16> upgradeFuture();
			virtual quint16 upgradeFile(bool sync, int msec, quint16 fileType, QString fileName);
			virtual quint16 upgradeFile(bool sync, int msec, quint16 fileType, QString fileName, quint8 portIndex, quint16 moduleIndex);
			virtual quint16 upgradeFile(bool sync, int msec, quint16 fileType, QByteArray data);
			virtual quint16 upgradeFile(bool sync, int msec, quint16 fileType, QByteArray data, quint8 portIndex, quint16 moduleIndex);
			virtual quint16 requestFile(bool sync, int msec, quint16 fileType, QString fileName);
			virtual quint16 requestFile(bool sync, int msec, quint16 fileType, QByteArray& data);

			/*********************************************************************************************************
			**Android设备                                                                     
			*********************************************************************************************************/
			virtual quint16 readAndroidVersion(bool sync, int msec);
			virtual QString getAndroidVersion();

			virtual quint16 writeKeyEvent(quint8 status, quint16 keyCode, bool sync, int msec);
			virtual quint16 getKeyEvent_Result();

			virtual quint16 writeDeviceName(QString name, bool sync, int msec);
			virtual quint16 readDeviceName(bool sync, int msec);
			virtual QString getDeviceName();

			/*********************************************************************************************************
			**Android设备 测试相关
			*********************************************************************************************************/
			virtual quint16 readNetDeviceOnlineStatus(QString ip, bool sync, int msec);
			virtual quint16 getNetDevice_Status();
			virtual QString getNetDevice_IP();

			virtual quint16 readSCEthLoopTestResult(bool sync, int msec) ;
			virtual quint16 getSCEthLoopTest_Result() ;
			virtual quint8  getSCEthLoopTest_EffectiveEthCount() ;
			virtual QByteArray  getSCEthLoopTest_ReplyData();
			virtual QMap<quint8, float>  getSCEthLoopTest_BitErrRate();

			virtual quint16 readUDiskMountingStatus(bool sync, int msec) ;
			virtual quint8  getUDiskMounting_Count() ;
			virtual QStringList getUDiskMounting_List() ;

			virtual quint16 writeStartOSDTest(bool sync, int msec) ;
			virtual quint8  getOSDTest_WhiteScreenTestResult() ;
			virtual quint8 getOSDTest_BlackScreenTestResult() ;

			virtual quint16 writeRelaySwitc(quint8 status, bool sync, int msec) ;
			virtual quint16 getRelaySwitc_Result() ;
			virtual quint8  getRelaySwitc_Status() ;

			virtual quint16 writeEnterKeyTest(quint8 status, bool sync, int msec) ;
			virtual quint8  getKeyTest_Result() ;

			virtual quint16 readKeyTestResult(bool sync, int msec) ;
			virtual quint8  getKeyTestResult_Count() ;
			virtual QList<quint16>  getKeyTestResult_List() ;

			virtual quint16 readOpticalSensorParam(bool sync, int msec) ;
			virtual quint16 getOpticalSensor_Param() ;

			virtual quint16 readRouterStatus(bool sync, int msec) ;
			virtual quint8 getRouter_5GWifiStatus() ;
			virtual quint8 getRouter_2_4GWifiStatus() ;

			virtual quint16 writeNetworkCardMACAddr(quint8 flage, QByteArray mac, bool sync, int msec) ;
			virtual quint16 getNetworkCardMACAddr_Results() ;
			virtual quint8  getNetworkCardMACAddr_Flage() ;
			virtual QByteArray getNetworkCardMACAddr_MAC() ;

			virtual quint16 writePlayTestSound_1KHZ(quint8 status, bool sync, int msec) ;
			virtual quint16 getPlayTestSound_Results() ;
			virtual quint8  getPlayTestSound_Status() ;

			virtual quint16 writeWIFIModuleScanTest(quint8 status, bool sync, int msec) ;
			virtual quint16 getWIFIModuleScanTest_Results() ;

			virtual quint16 readWIFIScanList(bool sync, int msec) ;
			virtual quint8  getWIFIScanList_Count() ;

			virtual quint16 readLoadPowerAmplifierChipParam(bool sync, int msec) ;
			virtual quint8  getPowerAmplifierChipParam_Results() ;
			virtual quint8  getPowerAmplifierChipParam_30Results() ;
			virtual quint8  getPowerAmplifierChipParam_31Results() ;

			virtual quint16 readCOMLoopTestResult(bool sync, int msec);
			virtual quint8 getCOMLoopTest_INResult();
			virtual quint8 getCOMLoopTest_OUTResult();

			virtual quint16 writeEnterTestMode(QString key, bool sync, int msec) ;
			virtual quint16  getEnterTestMode_Results() ;
		protected:
			LBLAbstractSCItem(QObject* parent = 0); //禁用外部创建
			LBLAbstractSCItem(LBLAbstractSCItemPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化

			virtual bool dispatcherPackage(const LBLEnginePackage& pack) = 0;
			virtual bool event(QEvent* e) override;

			void setSenderCardStatus(ESenderCardStatus);
            void setUsing(bool bUsing);
			const SDetectItemInfo& getDetectInfoStruct();
		protected:
			QScopedPointer<LBLAbstractSCItemPrivate> d_ptr;
		};

	}
}
#endif
