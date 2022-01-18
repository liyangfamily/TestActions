/****************************************************************************
**
** This Interface file is part of the NT68400 module of the LBL.
** 这个是LBL中的NT68400模块中集控实现文件，该模块不对外开放
**
** 该接口文件包含LED系统中NT68400集控相关操作
**
****************************************************************************/
#ifndef CVTE_H_LBLNT68400CENTRALCTRL
#define CVTE_H_LBLNT68400CENTRALCTRL
#pragma once

#include "LBLNT68400Abstract.h"

#include <LBL_CommunicatEngine/LBLInteCtrlPackage>
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_CommunicatEngined.lib")
#else
#pragma comment(lib,"LBL_CommunicatEngine.lib")
#endif // QT_DEBUG
#endif

namespace LBL
{
    namespace NT68400
    {

        template<class AbstractNT68400_t, class ConNT68400_t>
        class LBLNT68400Factory; //前置声明，告诉编译器工厂为模板

        class LBL_HDMICHIP_EXPORT LBLNT68400CentralCtrl : public LBLNT68400Abstract
        {
            Q_DECLARE_PRIVATE(LBLNT68400Abstract)
        public:
            ~LBLNT68400CentralCtrl();

        public:
            //PQ-Normal
            virtual quint16 writePQ_Contrast(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readPQ_Contrast(quint8 channel, bool sync, int msec)override;
            virtual quint16 writePQ_DCRStatus(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readPQ_DCRStatus(quint8 channel, bool sync, int msec)override;
            virtual quint16 writePQ_Sharpness(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readPQ_Sharpness(quint8 channel, bool sync, int msec)override;
            virtual quint16 writePQ_ScreenColorTemp(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readPQ_ScreenColorTemp(quint8 channel, bool sync, int msec)override;
            virtual quint16 writePQ_Color_R(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readPQ_Color_R(quint8 channel, bool sync, int msec)override;
            virtual quint16 writePQ_Color_G(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readPQ_Color_G(quint8 channel, bool sync, int msec)override;
            virtual quint16 writePQ_Color_B(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readPQ_Color_B(quint8 channel, bool sync, int msec)override;
            virtual quint16 writePQ_SceneMode(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readPQ_SceneMode(quint8 channel, bool sync, int msec)override;
            virtual quint16 readAllPQNormalData(quint8 param, quint8 channel, bool sync, int msec)override;
            //PQ-Advanced
            virtual quint16 writePQ_3DDEIStatus(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readPQ_3DDEIStatus(quint8 channel, bool sync, int msec)override;
            virtual quint16 writePQ_HDRStatus(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readPQ_HDRStatus(quint8 channel, bool sync, int msec)override;
            virtual quint16 writePQ_BrightFrame(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readPQ_BrightFrame(quint8 channel, bool sync, int msec)override;
            virtual quint16 readAllPQAdvanceData(quint8 param, quint8 channel, bool sync, int msec)override;

            //DP-Normal
            virtual quint16 writeDP_AspectRatio(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_AspectRatio(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_OverScanStatus(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_OverScanStatus(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_PivotStatus(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_PivotStatus(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_FlipMode(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_FlipMode(quint8 channel, bool sync, int msec)override;
            virtual quint16 readAllDPNormalData(quint8 param, quint8 channel, bool sync, int msec)override;
            //DP-Advanced
            virtual quint16 writeDP_PIPorPBP(quint8 param, quint8 channel, bool sync, int msec)override;	//设置分屏模式： 0关  1-单窗口 2-两窗口 3左右分屏， 4三分屏1，5三分屏2， 6四分屏
            virtual quint16 readDP_PIPorPBP(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_MainorPIPInput(quint8 param1, quint8 param2, quint8 param3, quint8 param4, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_MainorPIPInput(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_WindowSize(quint16 param1, quint16 param2, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_WindowSize(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_WindowPos(quint16 param1, quint16 param2, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_WindowPos(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_VideoWall(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_VideoWall(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_Ratio_H(quint16 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_Ratio_H(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_Ratio_V(quint16 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_Ratio_V(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_Start_H(quint16 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_Start_H(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_Start_V(quint16 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_Start_V(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_Size_H(quint16 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_Size_H(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_Size_V(quint16 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_Size_V(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeDP_PIPWindowStatus(quint8 status, quint8 channel, bool sync, int msec)override;
            virtual quint16 readDP_PIPWindowStatus(quint8 channel, bool sync, int msec)override;
            virtual quint16 readAllDPAdvanceData_PIP(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readAllDPAdvanceData_VideoWall(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 resetHDMISetting(bool sync, int msec) override;
            //DP-TX
            virtual quint16 writeSetting_DP_TX(quint8 hdmi1, quint8 hdmi2, quint8 dp , quint8 channel, bool sync, int msec)override;
            virtual quint16 readSetting_DP_TX(quint8 channel, bool sync, int msec)override;

            virtual quint16 writeSetting_DP_TX_Pcon600(quint8 hdmi1, quint8 hdmi2, quint8 dp, quint8 channel, bool sync, int msec)override;
            virtual quint16 readSetting_DP_TX_Pcon600(quint8 channel, bool sync, int msec)override;

            virtual quint16 writeSetting_DP_TX_2ndPlus(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readSetting_DP_TX_2ndPlus(quint8 channel, bool sync, int msec)override;

            //writeting-Audi
            virtual quint16 writeSetting_Mute(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readSetting_Mute(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeSetting_Volume(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readSetting_Volume(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeSetting_AudioSrc(quint8 param, quint8 channel, bool sync, int msec)override;	//channel：0：安卓（默认） 1:HDMI1override; 2:HDMI2override; 3:HDMI3
            virtual quint16 readSetting_AudioSrc(quint8 channel, bool sync, int msec)override;
            virtual quint16 readAllSettingAudioData(quint8 param, quint8 channel, bool sync, int msec)override;
            //writeting-Othe
            virtual quint16 writeSetting_DPSpeed(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readSetting_DPSpeed(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeSetting_ByPass(quint8 param, quint8 channel, bool sync, int msec)override;
            virtual quint16 readSetting_ByPass(quint8 channel, bool sync, int msec)override;
            virtual quint16 readAllSettingOtherData(quint8 param, quint8 channel, bool sync, int msec)override;

            //Sys-Normal
            virtual quint16 writeSys_PowerOn(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeSys_PowerOFF(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeSys_Reboot(quint8 channel, bool sync, int msec)override;

            virtual quint16 writeSys_ResetNT68400(quint8 channel, bool sync, int msec)override;
            virtual quint16 writeSys_UpgradNT68400(quint8 channel, bool sync, int msec)override;
            virtual quint16 readSys_Version(quint8 channel, bool sync, int msec)override;

            virtual quint16 writeSys_DisplayArea(quint16 width, quint16 height, bool sync, int msec)override;
            virtual quint16 readSys_DisplayArea(bool sync, int msec)override;

            //FacTest
            virtual quint16 writeFacTest_UpdateEDID(quint8 dataGroupIndex, quint8* pDataBuff, quint8 dataLen, bool sync, int msec)override;

            //Signal
            virtual quint16 readSignal_InputSignalInfo(quint8 channel, bool sync, int msec)override;

            //EDID
            virtual QByteArray GetEDIDData() override;

        protected:
            bool init() override;
            virtual void registerCallBack();

            quint16 syncSend(QByteArray sendData,QByteArray & replyData, bool sync, int msec);
        protected:
            LBLNT68400CentralCtrl(QObject* parent = 0); //禁用外部创建
            LBLNT68400CentralCtrl(LBLNT68400AbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
            friend class LBLNT68400Factory<LBLNT68400Abstract, LBLNT68400CentralCtrl>; //声明为一对一的好友关系，让工厂可以访问protected构造函数
        };

    }
}

#endif
