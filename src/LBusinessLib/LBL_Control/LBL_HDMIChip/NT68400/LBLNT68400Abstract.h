/****************************************************************************
**
** This Interface file is part of the NT68400 module of the LBL.
** 这个是LBL中的NT68400控制抽象类，该模块不对外开放
**
** 该接口文件包含LED系统中NT68400相关操作,与通信层联系
**
****************************************************************************/
#ifndef CVTE_H_LBLNT68400ABSTRACT
#define CVTE_H_LBLNT68400ABSTRACT
#pragma once

#include "../LBLHDMIChipGlobal.h"
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QScopedPointer>
#include <LBL_CommunicatEngine/LBLPackage>

namespace LBL
{
    namespace NT68400
    {
        class LBLNT68400AbstractPrivate;
        class LBL_HDMICHIP_EXPORT LBLNT68400Abstract :public QObject
        {
            Q_DECLARE_PRIVATE(LBLNT68400Abstract)
        public:
            virtual ~LBLNT68400Abstract();

            bool setDetectInfoStruct(SDetectItemInfo *detectInfo);
            bool parsingDataFrame(const LBLPackage& pack);

            virtual bool init() = 0;

        public:
            quint8 channelCount();
            //PQ-Normal
            virtual quint16 writePQ_Contrast(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readPQ_Contrast(quint8 channel, bool sync, int msec)=0;
            virtual quint8  getPQ_Contrast();

            virtual quint16 writePQ_DCRStatus(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readPQ_DCRStatus(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getPQ_DCRStatus();

            virtual quint16 writePQ_Sharpness(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readPQ_Sharpness(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getPQ_Sharpness();

            virtual quint16 writePQ_ScreenColorTemp(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readPQ_ScreenColorTemp(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getPQ_ScreenColorTemp();

            virtual quint16 writePQ_Color_R(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readPQ_Color_R(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getPQ_Color_R();

            virtual quint16 writePQ_Color_G(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readPQ_Color_G(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getPQ_Color_G();

            virtual quint16 writePQ_Color_B(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readPQ_Color_B(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getPQ_Color_B();

            virtual quint16 writePQ_SceneMode(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readPQ_SceneMode(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getPQ_SceneMode();

            virtual quint16 readAllPQNormalData(quint8 param, quint8 channel, bool sync, int msec)=0;
            //PQ-Advanced
            virtual quint16 writePQ_3DDEIStatus(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readPQ_3DDEIStatus(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getPQ_3DDEIStatus();

            virtual quint16 writePQ_HDRStatus(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readPQ_HDRStatus(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getPQ_HDRStatus();

            virtual quint16 writePQ_BrightFrame(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readPQ_BrightFrame(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getPQ_BrightFrame();

            virtual quint16 readAllPQAdvanceData(quint8 param, quint8 channel, bool sync, int msec)=0;

            //DP-Normal
            virtual quint16 writeDP_AspectRatio(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_AspectRatio(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getDP_AspectRatio();

            virtual quint16 writeDP_OverScanStatus(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_OverScanStatus(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getDP_OverScanStatus();

            virtual quint16 writeDP_PivotStatus(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_PivotStatus(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getDP_PivotStatus();

            virtual quint16 writeDP_FlipMode(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_FlipMode(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getPQ_FlipMode();

            virtual quint16 readAllDPNormalData(quint8 param, quint8 channel, bool sync, int msec)=0;
            //DP-Advanced
            virtual quint16 writeDP_PIPorPBP(quint8 param, quint8 channel, bool sync, int msec)=0;	//设置分屏模式： 0关  1-单窗口 2-两窗口 3左右分屏， 4三分屏1，5三分屏2， 6四分屏
            virtual quint16 readDP_PIPorPBP(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getDP_PIPorPBP();

            virtual quint16 writeDP_MainorPIPInput(quint8 param1, quint8 param2, quint8 param3, quint8 param4, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_MainorPIPInput(quint8 channel, bool sync, int msec) = 0;
            virtual QList<quint8> getDP_MainorPIPInputList();

            virtual quint16 resetHDMISetting(bool sync, int msec) = 0;

            virtual quint16 writeDP_WindowSize(quint16 param1, quint16 param2, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_WindowSize(quint8 channel, bool sync, int msec) = 0;
            virtual QSize  getDP_WindowSize();

            virtual quint16 writeDP_WindowPos(quint16 param1, quint16 param2, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_WindowPos(quint8 channel, bool sync, int msec) = 0;
            virtual QPoint  getDP_WindowPos();

            virtual quint16 writeDP_VideoWall(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_VideoWall(quint8 channel, bool sync, int msec)=0;
            virtual quint8  getDP_VideoWal();

            virtual quint16 writeDP_Ratio_H(quint16 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_Ratio_H(quint8 channel, bool sync, int msec) = 0;
            virtual quint16 getDP_Ratio_H();

            virtual quint16 writeDP_Ratio_V(quint16 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_Ratio_V(quint8 channel, bool sync, int msec) = 0;
            virtual quint16 getDP_Ratio_V();

            virtual quint16 writeDP_Start_H(quint16 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_Start_H(quint8 channel, bool sync, int msec) = 0;
            virtual quint16 getDP_Start_H();

            virtual quint16 writeDP_Start_V(quint16 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_Start_V(quint8 channel, bool sync, int msec) = 0;
            virtual quint16 getDP_Start_V();

            virtual quint16 writeDP_Size_H(quint16 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_Size_H(quint8 channel, bool sync, int msec) = 0;
            virtual quint16 getDP_Size_H();

            virtual quint16 writeDP_Size_V(quint16 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_Size_V(quint8 channel, bool sync, int msec) = 0;
            virtual quint16 getDP_Size_V();

            virtual quint16 writeDP_PIPWindowStatus(quint8 status, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readDP_PIPWindowStatus(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getDP_PIPWindowStatus();

            virtual quint16 readAllDPAdvanceData_PIP(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readAllDPAdvanceData_VideoWall(quint8 param, quint8 channel, bool sync, int msec)=0;

            //DP-TX
            virtual quint16 writeSetting_DP_TX(quint8 hdmi1, quint8 hdmi2, quint8 dp , quint8 channel, bool sync, int msec)=0;
            virtual quint16 readSetting_DP_TX(quint8 channel, bool sync, int msec) = 0;
            virtual QList<quint8> getSetting_DP_TX();

            virtual quint16 writeSetting_DP_TX_Pcon600(quint8 hdmi1, quint8 hdmi2, quint8 dp , quint8 channel, bool sync, int msec)=0;
            virtual quint16 readSetting_DP_TX_Pcon600(quint8 channel, bool sync, int msec) = 0;
            virtual bool    getSetting_DP_TX_Pcon600(quint8 &hdmi1, quint8 &hdmi2, quint8 &dp);

            virtual quint16 writeSetting_DP_TX_2ndPlus(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readSetting_DP_TX_2ndPlus(quint8 channel, bool sync, int msec)=0;
            virtual quint8  getSetting_DP_TX_2ndPlus();

            //writeting-Audi
            virtual quint16 writeSetting_Mute(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readSetting_Mute(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getSetting_Mute();

            virtual quint16 writeSetting_Volume(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readSetting_Volume(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getSetting_Volume();

            virtual quint16 writeSetting_AudioSrc(quint8 param, quint8 channel, bool sync, int msec)=0;	//channel：0：安卓（默认） 1:HDMI1=0; 2:HDMI2=0; 3:HDMI3
            virtual quint16 readSetting_AudioSrc(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getSetting_AudioSrc();

            virtual quint16 readAllSettingAudioData(quint8 param, quint8 channel, bool sync, int msec)=0;
            //writeting-Othe
            virtual quint16 writeSetting_DPSpeed(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readSetting_DPSpeed(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getSetting_DPSpee();

            virtual quint16 writeSetting_ByPass(quint8 param, quint8 channel, bool sync, int msec)=0;
            virtual quint16 readSetting_ByPass(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getSetting_ByPass();

            virtual quint16 readAllSettingOtherData(quint8 param, quint8 channel, bool sync, int msec)=0;

            //Sys-Normal
            virtual quint16 writeSys_PowerOn(quint8 channel, bool sync, int msec)=0;
            virtual quint16 writeSys_PowerOFF(quint8 channel, bool sync, int msec)=0;
            virtual quint16 writeSys_Reboot(quint8 channel, bool sync, int msec)=0;

            virtual quint16 writeSys_ResetNT68400(quint8 channel, bool sync, int msec)=0;
            virtual quint16 writeSys_UpgradNT68400(quint8 channel, bool sync, int msec)=0;
            virtual quint16 readSys_Version(quint8 channel, bool sync, int msec) = 0;
            virtual QString getSys_Version();

            virtual quint16 writeSys_DisplayArea(quint16 width, quint16 height, bool sync, int msec)=0;
            virtual quint16 readSys_DisplayArea(bool sync, int msec)=0;
            virtual QSize   getSys_DisplayArea();

            //FacTest
            virtual quint16 writeFacTest_UpdateEDID(quint8 dataGroupIndex, quint8* pDataBuff, quint8 dataLen, bool sync, int msec)=0;

            //Signal
            virtual quint16 readSignal_InputSignalInfo(quint8 channel, bool sync, int msec) = 0;
            virtual quint8  getSignal_InputSignalInfo_InputIndex();
            virtual quint8  getSignal_InputSignalInfo_Status();
            virtual QSize   getSignal_InputSignalInfo_Size();
            virtual quint8  getSignal_InputSignalInfo_FreqInt();
            virtual quint8  getSignal_InputSignalInfo_FreqDec();
            virtual quint8  getSignal_InputSignalInfo_IsInterlaced();
            virtual QString getSignal_InputSignalInfo();

            //EDID
            virtual QByteArray GetEDIDData()=0;

        protected:
            LBLNT68400Abstract(QObject* parent = 0);
            LBLNT68400Abstract(LBLNT68400AbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
            virtual quint8 convert_InputSource(LAPI::UI::EInputSource value); //从UI数据转换成68400实际数据
        protected:
            QScopedPointer<LBLNT68400AbstractPrivate> d_ptr;
        };
    }
}
#endif
