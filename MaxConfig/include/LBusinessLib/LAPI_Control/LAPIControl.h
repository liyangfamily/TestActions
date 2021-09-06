/****************************************************************************
**
** This Interface file is part of the Control module of the LAPI.
** 这个是LAPI中的Control模块接口文件
**
** 该接口文件包含LED系统控制相关的接口函数，本头文件为C++实现
**
****************************************************************************/
#ifndef CVTE_H_ILAPI_CONTROL
#define CVTE_H_ILAPI_CONTROL
#pragma once

#include <LAPI_Control/LAPIGlobal>
#include <LBL_Core/LAPIDef>
#include <LBL_Core/LBLDef>
#include <LBL_Core/LBLUIHelper>
/*#include <LBL_Core/LBLConnection>
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_Cored.lib")
#else
#pragma comment(lib,"LBL_Core.lib")
#endif*/
//加载发送卡库
#include <LBL_SenderCardItem/LBLAbstractSCItem>
#include <LBL_SenderCardItem/LBLSCItemManager>
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_SenderCardItemd.lib")
#else
#pragma comment(lib,"LBL_SenderCardItem.lib")
#endif // QT_DEBUG
#endif

//加载通信库
#include <LBL_CommunicatEngine/LBLCluster>
#include <LBL_CommunicatEngine/LBLPackageDispatcher>
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_CommunicatEngined.lib")
#else
#pragma comment(lib,"LBL_CommunicatEngine.lib")
#endif // QT_DEBUG
#endif

#ifndef __cplusplus
extern "C" {
#endif
    namespace LAPI
    {
        /*
        * Comments:启动探卡幅度
        * Param in:
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall StartDetectServer(quint16 detectIntervalTime = 1 * 1000, quint16 everyDetectIntervalTime = 30 * 1000, quint16 everyDetectCount = 2);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall StoptDetectServer();

        /*
        * Comments:获取发送卡列表
        * Param in:列表变量
        * Param out:列表变量
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT QList<LBL::SCItem::LBLAbstractSCItem*> LAPI_Stdcall GetUsingItemList();
        ILAPI_CONTROL_EXPORT QList<LBL::SCItem::LBLAbstractSCItem*> LAPI_Stdcall GetAllItemList();
        ILAPI_CONTROL_EXPORT LBL::SCItem::LBLAbstractSCItem* LAPI_Stdcall GetItemByInternalUuid(QUuid internalUuid);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall SetUsingItemByInternalUuid(QUuid internalUuid);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ConnectItemByInternalUuid(QUuid internalUuid);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall DisconnectItemByInternalUuid(QUuid internalUuid);

        /*
        * Comments:控制API退出清理工作
        * Param in:
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadyExit();
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall CanExit();

        /*********************************************************************************************************
        **发送卡相关
        *********************************************************************************************************/
        /*
        * Comments:设置、获取亮度
        * Param in:int
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteBrightness(const int, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadBrightness(bool sync = false, int msec = LBL_Defalut_SyncTimeout);

        /*
        * Comments:读写发送卡寄存器
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteSCFPGARegister(quint32 addr, QByteArray value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCFPGARegister(quint32 addr, quint16 len, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall GetSCFPGARegister();

        /*
        * Comments:读发送卡FPGA版本号，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCFPGAVersion(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QString LAPI_Stdcall GetSCFPGAVersion();

        /*
        * Comments:读发送卡FPGA网口带载，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteSCFPGAEthLoad(const QList<LBLSPort>& value, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCFPGAEthLoad(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QList<LBLSPort> LAPI_Stdcall GetSCFPGAEthLoad();

        /*
        * Comments:读发广州发送卡MCU版本号
        * SenderCard：2ndGZ
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadMCUAppVersion(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QString LAPI_Stdcall GetMCUAppVersion();
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadMCUBootVersion(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QString LAPI_Stdcall GetMCUBootVersion();

        /*
        * Comments:写保存发送卡参数
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteSaveSCParam(bool sync = false, int msec = LBL_Defalut_SyncTimeout);

        /*
        * Comments:连接关系，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteConnection(LBLConnection* value, bool sync = true, int msec = 5000);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadConnection(bool sync = true, int msec = 400);
        ILAPI_CONTROL_EXPORT LBLConnection* LAPI_Stdcall GetConnection();

        /*
        * Comments:发送卡测试模式，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult WriteSCSelfTestMode(UI::EPictureTestMode mode, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCSelfTestMode(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT UI::EPictureTestMode LAPI_Stdcall GetSCSelfTestMode();

        /*
        * Comments:发送卡测试模式速度，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult WriteSCSelfTestModeSpeed(UI::EPictureTestModeSpeed speed, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCSelfTestModeSpeed(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT UI::EPictureTestModeSpeed LAPI_Stdcall GeSCtSelfTestModeSpeed();
        /*
        * Comments:发送卡黑屏，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult WriteSCScreenBlack(quint8 value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCScreenBlack(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCScreenBlack();
        /*
        * Comments:发送卡锁屏，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult WriteSCScreenLock(quint8 value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCScreenLock(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCScreenLock();
        /*
        * Comments:发送卡缩放模式，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult WriteSCZoomMode(quint8 value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCZoomMode(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCZoomMode();
        /*
        * Comments:发送卡缩放尺寸，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult WriteSCZoomSize(QSize value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCZoomSize(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QSize LAPI_Stdcall GetSCZoomSize();
        /*
        * Comments:发送卡误码率统计开关，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult WriteSCErrorBitRateStatisticalSwitch(quint8 value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCErrorBitRateStatisticalSwitch(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCErrorBitRateStatisticalSwitch();
        /*
        * Comments:发送卡校正开关，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult WriteSCCorrectionSwitch(quint8 value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCCorrectionSwitch(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCCorrectionSwitch();
        /*
        * Comments:发送卡展频开关，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult WriteSCSpreadSpectrumSwitch(quint8 value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCSpreadSpectrumSwitch(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCSpreadSpectrumSwitch();
        /*
        * Comments:发送卡24bitGamma开关，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult WriteSC24BitGammaSwitch(quint8 value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSC24BitGammaSwitch(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSC24BitGammaSwitch();

        /*
        * Comments:发送卡协议类型，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult WriteSCProtocolType(quint8 value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadSCProtocolType(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetSCProtocolType();
        /*********************************************************************************************************
        **接收卡相关
        *********************************************************************************************************/
        /*
        * Comments:读写接收卡FPGA寄存器，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteRCFPGARegister(quint8 port, quint8 module, quint32 addr, QByteArray value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadRCFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 len, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall GetRCFPGARegister();

        /*
        * Comments:读写接收卡模组参数，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteModuleParam(quint8 port, quint8 module, QByteArray value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadModuleParam(quint8 port, quint8 module, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall GetModuleParam();

        /*
        * Comments:读写接收卡驱动芯片参数，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteDriveICParam(quint8 port, quint8 module, QByteArray value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadDriveICParam(quint8 port, quint8 module, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall GetDriveICParam();

        /*
        * Comments:读写接收卡译码芯片参数，需同步读取
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteDecodingICParam(quint8 port, quint8 module, QByteArray value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall ReadDecodingICParam(quint8 port, quint8 module, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall GetDecodingICParam();

        /*
        * Comments:写接收卡校正数据擦除
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteCalibrationDataErase(quint8 port, quint8 module, bool sync = true, int msec = LBL_Defalut_SyncTimeout);


        /*

        * Comments:写接收卡校正数据
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteCalibrationDataSave(quint8 port, quint8 module, bool sync = true, int msec = LBL_Defalut_SyncTimeout);

        /*
        * Comments:写接收卡校正数据重加载
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteCalibrationDataReload(quint8 port, quint8 module, bool sync = true, int msec = LBL_Defalut_SyncTimeout);

        /*
       * Comments:读接收卡状态信息，lengthflag不用填
       * SenderCard：2ndPlus、2ndGZ、PCON600
       */
        ILAPI_CONTROL_EXPORT QList<LBL::RC::SRCStatusInfo> LAPI_Stdcall ReadRCStatusInfo(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QList<LBL::RC::SRCStatusInfo> LAPI_Stdcall ReadRCStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag = 0, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QList<LBL::RC::SRCStatusInfo> LAPI_Stdcall GetRCStatusInfo();

        /*
       * Comments:读接收卡监控信息
       * SenderCard：2ndPlus、2ndGZ、PCON600
       */
        ILAPI_CONTROL_EXPORT QList<LBL::RC::SRCMonitorInfo> LAPI_Stdcall ReadRCMonitorInfo(quint8 portIndex = 0xFF, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QList<LBL::RC::SRCMonitorInfo> LAPI_Stdcall GetRCMonitorInfo();

        /*
        * Comments:写保存接收卡参数
        * SenderCard：2ndPlus、2ndGZ、PCON600
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteSaveRCParam(quint8 port, quint16 module, bool sync = false, int msec = LBL_Defalut_SyncTimeout);

        /*********************************************************************************************************
        **视频源相关
        *********************************************************************************************************/
        /*
        * Comments:设置、获取HDMI芯片Bypass状态
        * Param in:quint8
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDMIByPassStatus(const quint8 value, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDMIByPassStatus(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetHDMIByPassStatus();

        /*
        * Comments:设置、获取HDMI芯片屏幕显示比例
        * Param in:quint8
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDMIImageRatio(const quint8 value, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDMIImageRatio(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetHDMIImageRatio();

        /*
        * Comments:设置、获取HDMI芯片视频源
        * Param in:quint8
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDMIInputSource(const quint8 value, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDMIInputSource(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT UI::EInputSource  LAPI_Stdcall GetHDMIInputSource();

        /*
        * Comments:设置、获取HDMI芯片对比度
        * Param in:quint8
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDMIImageContrast(const quint8 value, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDMIImageContrast(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetHDMIImageContrast();

        /*
        * Comments:设置、获取HDMI芯片色温
        * Param in:quint8
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDMIImageColorTtemperature(const quint8 value, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDMIImageColorTtemperature(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetHDMIImageColorTtemperature();

        /*
        * Comments:设置、获取HDMI芯片亮度
        * Param in:quint8
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDMIImageBrightness(const quint8 value, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDMIImageBrightness(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetHDMIImageBrightness();

        /*
        * Comments:设置、获取HDMI芯片RGB增益
        * Param in:quint8
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDMIRGBGain(const int rValue = -1, const int gValue = -1, const int bValue = -1, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDMIRGBGain(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QList<quint8> LAPI_Stdcall GetHDMIRGBGain();

        /*
        * Comments:获取HDMI芯片带载信号，需同步获取
        * Param in:
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDMIInputSignalInfo(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QString LAPI_Stdcall GetHDMIInputSignalInfo();

        /*
        * Comments:获取HDMI版本号，需同步获取
        * Param in:
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDMIVersion(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QString LAPI_Stdcall GetHDMIVersion();

        /*
        * Comments:获取HDMI多屏模式，需同步获取
        * Param in:
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall writeHDMIMultiScreenMode(const UI::EMultiScreenMode value, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall readHDMIMultiScreenMode(bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT UI::EMultiScreenMode  LAPI_Stdcall  getHDMIMultiScreenMode();

        /*
        * Comments:获取HDMI多屏输入源，需同步获取
        * Param in:
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDMIMultiScreenInputSource(const quint8 param, const UI::EHDMIChannel channel = UI::EHDMIChannel::EHC_All, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDMIMultiScreenInputSourceList(const QList<quint8>& values, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDMIMultiScreenInputSource(const UI::EHDMIChannel channel = UI::EHDMIChannel::EHC_All, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QList<quint8> LAPI_Stdcall GetHDMIMultiScreenInputSource(const UI::EHDMIChannel channel = UI::EHDMIChannel::EHC_All);

        /*
        * Comments:HDMI reset
        * Param in:
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ResetHDMISetting(bool sync = true, int msec = LBL_Defalut_SyncTimeout);

        /*
        * Comments:HDMI WindowSize
        * Param in:
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDIMIWindowSize(QSize value, UI::EHDMIChannel channel, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDIMIWindowSize(UI::EHDMIChannel channel, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QSize LAPI_Stdcall GetHDIMIWindowSize();

        /*
        * Comments:HDMI WindowPos
        * Param in:
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDIMIWindowPos(QPoint value, UI::EHDMIChannel channel, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDIMIWindowPos(UI::EHDMIChannel channel, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QPoint LAPI_Stdcall GetHDIMIWindowPos();

        /*
        * Comments:HDMI WindowStatus
        * Param in:
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDIMIWindowStatus(quint8 status, UI::EHDMIChannel channel, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDIMIWindowStatus(UI::EHDMIChannel channel, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetHDIMIWindowStatus();

        /*
        * Comments:HDMI AudioSrc
        * Param in:
        * Param out:
        * @Return Result
        */
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteHDIMIAudioSrc(quint8 param, UI::EHDMIChannel channel, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadHDIMIAudioSrc(UI::EHDMIChannel channel, bool sync = true, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetHDIMIAudioSrc();


        /*********************************************************************************************************
        **文件传输相关
        *********************************************************************************************************/
        /*
        * Comments:升级
        * Param in:
        * Param out:
        * @Return Result
        */
        //文件升级
        ILAPI_CONTROL_EXPORT bool LAPI_Stdcall IsUpgradeSend();
        ILAPI_CONTROL_EXPORT quint16 LAPI_Stdcall UpgradingFileType();
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall UpgradingPortIndex();
        ILAPI_CONTROL_EXPORT quint16 LAPI_Stdcall UpgradingModuleIndex();

        ILAPI_CONTROL_EXPORT bool LAPI_Stdcall IsUpgradeStarted();
        ILAPI_CONTROL_EXPORT bool LAPI_Stdcall IsUpgrading();
        ILAPI_CONTROL_EXPORT bool LAPI_Stdcall IsUpgradeFinished();
        ILAPI_CONTROL_EXPORT bool LAPI_Stdcall CancelUpgrade();
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall UpgradeResult();
        ILAPI_CONTROL_EXPORT QFuture<quint16> LAPI_Stdcall UpgradeFuture();
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall UpgradeFile(quint16 fileType, QString fileName,bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall UpgradeFile(quint16 fileType, QString fileName, quint8 portIndex, quint16 moduleIndex, bool sync = false, int msec = LBL_Defalut_SyncTimeout);

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall UpgradeFile(quint16 fileType, QByteArray data, bool sync, int msec);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall UpgradeFile(quint16 fileType, QByteArray data, quint8 portIndex, quint16 moduleIndex, bool sync, int msec);

        /*********************************************************************************************************
        **Android设备
        *********************************************************************************************************/
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadAndroidVersion(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QString LAPI_Stdcall GetAndroidVersion();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteKeyEvent(quint8 status, quint16 keyCode, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint16 LAPI_Stdcall GetKeyEvent_Result();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteDeviceName(QString name, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadDeviceName(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT QString LAPI_Stdcall GetDeviceName();

        /*********************************************************************************************************
        **Android设备 测试相关
        *********************************************************************************************************/
        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadNetDeviceOnlineStatus(QString ip, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint16 LAPI_Stdcall GetNetDevice_Status();
        ILAPI_CONTROL_EXPORT QString LAPI_Stdcall GetNetDevice_IP();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadSCEthLoopTestResult(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint16 LAPI_Stdcall GetSCEthLoopTest_Result();
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetSCEthLoopTest_EffectiveEthCount();
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall GetSCEthLoopTest_ReplyData();
        ILAPI_CONTROL_EXPORT QMap<quint8, float> LAPI_Stdcall GetSCEthLoopTest_BitErrRate();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadUDiskMountingStatus(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetUDiskMounting_Count();
        ILAPI_CONTROL_EXPORT QStringList LAPI_Stdcall GetUDiskMounting_List();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteStartOSDTest(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetOSDTest_WhiteScreenTestResult();
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetOSDTest_BlackScreenTestResult();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteRelaySwitc(quint8 status, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint16 LAPI_Stdcall GetRelaySwitc_Result();
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetRelaySwitc_Status();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteEnterKeyTest(quint8 status, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetKeyTest_Result();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadKeyTestResult(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetKeyTestResult_Count();
        ILAPI_CONTROL_EXPORT QList<quint16> LAPI_Stdcall GetKeyTestResult_List();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadOpticalSensorParam(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint16 LAPI_Stdcall GetOpticalSensor_Param();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadRouterStatus(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetRouter_5GWifiStatus();
        ILAPI_CONTROL_EXPORT quint8 LAPI_Stdcall GetRouter_2_4GWifiStatus();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteNetworkCardMACAddr(quint8 flage, QByteArray mac, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint16 LAPI_Stdcall GetNetworkCardMACAddr_Results();
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetNetworkCardMACAddr_Flage();
        ILAPI_CONTROL_EXPORT QByteArray LAPI_Stdcall GetNetworkCardMACAddr_MAC();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WritePlayTestSound_1KHZ(quint8 status, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint16 LAPI_Stdcall GetPlayTestSound_Results();
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetPlayTestSound_Status();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteWIFIModuleScanTest(quint8 status, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint16 LAPI_Stdcall GetWIFIModuleScanTest_Results();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadWIFIScanList(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetWIFIScanList_Count();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadLoadPowerAmplifierChipParam(bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetPowerAmplifierChipParam_Results();
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetPowerAmplifierChipParam_30Results();
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetPowerAmplifierChipParam_31Results();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall ReadCOMLoopTestResult(bool sync, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetCOMLoopTest_INResult();
        ILAPI_CONTROL_EXPORT quint8  LAPI_Stdcall GetCOMLoopTest_OUTResult();

        ILAPI_CONTROL_EXPORT EResult LAPI_Stdcall WriteEnterTestMode(QString key, bool sync = false, int msec = LBL_Defalut_SyncTimeout);
        ILAPI_CONTROL_EXPORT quint16 LAPI_Stdcall GetEnterTestMode_Results();
    }
#ifndef __cplusplus
}
#endif

#endif /*CVTE_H_ILAPI_CONTROL*/
