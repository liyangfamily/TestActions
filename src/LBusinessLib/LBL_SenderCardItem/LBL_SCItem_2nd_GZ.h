/****************************************************************************
**
** This Interface file is part of the SenderCardItem module of the LBusinessLib.
** 这个是LBusinessLib中AbstractSenderCardItem派生子类发送卡，该模块不对外开放
**
** 该接口文件为LED系统中2nd_GZ发送卡对象，用于管理2nd_GZ发送卡的业务和数据
**
****************************************************************************/
#ifndef CVTE_H_LBL_SENDERCARDITEM_2ND_GZ
#define CVTE_H_LBL_SENDERCARDITEM_2ND_GZ
#pragma once

#include "LBL_SCItem_2nd.h"

namespace LBL
{
    namespace SCItem
    {
        template<class AbstractSenderCardItem_t, class ConSenderCardItem_t>
        class SenderCardItemFactory; //前置声明，告诉编译器工厂为模板

        class SenderCardItem_2nd_GZPrivate;
        class LBL_SENDERCARDITEM_EXPORT SenderCardItem_2nd_GZ : public LBLAbstractSCItem
        {
            Q_DECLARE_PRIVATE(SenderCardItem_2nd_GZ)
        public:
            ~SenderCardItem_2nd_GZ();
            //发送卡属性
            virtual QString senderCardTag() const override;
            //发送卡属性
            virtual int maxPortCount() const override;
            virtual bool hasMS9570() const override;
            virtual bool hasNT68400() const override;
            virtual bool hasAndroid() const override;
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

            virtual quint16 readMCUAppVersion(bool sync, int msec) override;
            virtual QString getMCUAppVersion() override;
            virtual quint16 readMCUBootVersion(bool sync, int msec) override;
            virtual QString getMCUBootVersion() override;

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

            virtual quint16 writeSCNT68400Resolution(quint8 value, bool sync, int msec)override;
            virtual QByteArray readSCNT68400Resolution(bool sync, int msec)override;
            virtual quint8  getSCNT68400Resolution()override;

            virtual quint16 writeSC10BitSource(quint8 value, bool sync, int msec)override;
            virtual QByteArray readSC10BitSource(bool sync, int msec)override;
            virtual quint8  getSC10BitSource()override;

            virtual quint16 writeSCLowDelay(quint8 value, bool sync, int msec)override;
            virtual QByteArray readSCLowDelay(bool sync, int msec)override;
            virtual quint8  getSCLowDelay()override;
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

            virtual quint16 writeLowGrayCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec) override;
            virtual quint16 writeLowGrayCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec) override;
            virtual quint16 writeLowGrayCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec) override;

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

            virtual quint16 writeHDIMIDisplayArea(QSize value, quint8 channel, bool sync, int msec)override;
            virtual quint16 readHDIMIDisplayArea(quint8 channel, bool sync, int msec)override;
            virtual QSize  getHDIMIDisplayArea()override;

            virtual quint16 writeHDIMIAudioVolume(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readHDIMIAudioVolume(quint8 channel, bool sync, int msec)override;
            virtual quint8  getHDIMIAudioVolume()override;

            virtual quint16 resetHDMISetting(bool sync, int msec)override;

            //文件升级
            virtual quint16 upgradeFile(bool sync, int msec, quint16 fileType, QString fileName, quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF) override;
            virtual quint16 upgradeFile(bool sync, int msec, quint16 fileType, QByteArray dat, quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF) override;
            virtual quint16 requestFile(bool sync, int msec, quint16 fileType, QString fileName) override;
            virtual quint16 requestFile(bool sync, int msec, quint16 fileType, QByteArray& data) override;

            //EDID
            virtual QByteArray GetEDIDData() override;
            virtual quint16 writeHDMIEDID(int dataGroupIndex, quint8* pDataBuff,int dataLen) override;

            /*********************************************************************************************************
            **Android设备
            *********************************************************************************************************/
            virtual quint16 readAndroidVersion(bool sync, int msec) override;
            virtual QString getAndroidVersion() override;

        protected:
            SenderCardItem_2nd_GZ(QObject* parent = 0); //禁用外部创建
            SenderCardItem_2nd_GZ(SenderCardItem_2nd_GZPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
            bool registerControl() override;
            bool dispatcherPackage(const LBLEnginePackage& pack) override;
            friend class SenderCardItemFactory<LBLAbstractSCItem, SenderCardItem_2nd_GZ>; //声明为一对一的好友关系，让工厂可以访问protected构造函数
        };

    }
}
#endif
