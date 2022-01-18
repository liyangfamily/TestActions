#include "LBLNT68400Abstract.h"
#include "LBLNT68400Abstract_p.h"


namespace LBL
{
    namespace NT68400
    {
        LBLNT68400Abstract::LBLNT68400Abstract(QObject* parent) :
            QObject(parent),d_ptr(new LBLNT68400AbstractPrivate)
        {
            Q_D(LBLNT68400Abstract);
            Q_UNUSED(d)
            d_ptr->q_ptr = this;
        }

        LBLNT68400Abstract::LBLNT68400Abstract(LBLNT68400AbstractPrivate & dd, QObject* parent) :
            QObject(parent), d_ptr(&dd)
        {
            Q_D(LBLNT68400Abstract);
            Q_UNUSED(d)
            d_ptr->q_ptr = this;
        }

        quint8 LBLNT68400Abstract::convert_InputSource(LAPI::UI::EInputSource value)
        {
            return value; //ui定义和NT68400一致
        }

        LBLNT68400Abstract::~LBLNT68400Abstract()
        {
            Q_D(LBLNT68400Abstract);
            d->m_packageMgr.unregisterAll();
        }

        bool LBLNT68400Abstract::setDetectInfoStruct(SDetectItemInfo *detectInfo)
        {
            Q_ASSERT(detectInfo);
            d_ptr->m_parentItemDetectInfo = detectInfo;
            return true;
        }
        bool LBLNT68400Abstract::parsingDataFrame(const LBLPackage & pack)
        {
            Q_D(LBLNT68400Abstract);
            return d->m_packageMgr.handle(pack);
        }

        quint8 LBLNT68400Abstract::channelCount()
        {
            return g_ChannelCount;
        }

        quint8 LBLNT68400Abstract::getPQ_Contrast()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_PQNormalData.contrast;
        }

        quint8 LBLNT68400Abstract::getPQ_DCRStatus()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_PQNormalData.status_DCR;
        }

        quint8 LBLNT68400Abstract::getPQ_Sharpness()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_PQNormalData.sharpness;
        }

        quint8 LBLNT68400Abstract::getPQ_ScreenColorTemp()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_PQNormalData.colorTemp;
        }

        quint8 LBLNT68400Abstract::getPQ_Color_R()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_PQNormalData.color_R;
        }

        quint8 LBLNT68400Abstract::getPQ_Color_G()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_PQNormalData.color_G;
        }

        quint8 LBLNT68400Abstract::getPQ_Color_B()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_PQNormalData.color_B;
        }

        quint8 LBLNT68400Abstract::getPQ_SceneMode()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_PQNormalData.sceneMode;
        }

        quint8 LBLNT68400Abstract::getPQ_3DDEIStatus()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_PQAdvanceData.status_3DDEI;
        }

        quint8 LBLNT68400Abstract::getPQ_HDRStatus()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_PQAdvanceData.status_HDR;
        }

        quint8 LBLNT68400Abstract::getPQ_BrightFrame()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_PQAdvanceData.brightFrame;
        }

        quint8 LBLNT68400Abstract::getDP_AspectRatio()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPNormalData.aspectRatio;
        }

        quint8 LBLNT68400Abstract::getDP_OverScanStatus()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPNormalData.status_overScan;
        }

        quint8 LBLNT68400Abstract::getDP_PivotStatus()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPNormalData.status_pivot;
        }

        quint8 LBLNT68400Abstract::getPQ_FlipMode()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPNormalData.flipMode;
        }

        quint8 LBLNT68400Abstract::getDP_PIPorPBP()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPAdvanceData.PIPorPBP;
        }

        QList<quint8> LBLNT68400Abstract::getDP_MainorPIPInputList()
        {
            Q_D(LBLNT68400Abstract);
            QList<quint8> list;
            list << d->m_NT68400Data.m_DPAdvanceData.main_Input << d->m_NT68400Data.m_DPAdvanceData.PIP1_Input \
                << d->m_NT68400Data.m_DPAdvanceData.PIP2_Input << d->m_NT68400Data.m_DPAdvanceData.PIP3_Input;
            return list;
        }

        QSize LBLNT68400Abstract::getDP_WindowSize()
        {
            Q_D(LBLNT68400Abstract);
            return QSize(d->m_NT68400Data.m_DPAdvanceData.windowSize_Width, d->m_NT68400Data.m_DPAdvanceData.windowSize_Height);
        }

        QPoint LBLNT68400Abstract::getDP_WindowPos()
        {
            Q_D(LBLNT68400Abstract);
            return QPoint(d->m_NT68400Data.m_DPAdvanceData.windowPos_X, d->m_NT68400Data.m_DPAdvanceData.windowPos_Y);
        }

        quint8 LBLNT68400Abstract::getDP_VideoWal()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPAdvanceData.videoWall;
        }

        quint16 LBLNT68400Abstract::getDP_Ratio_H()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPAdvanceData.ratio_H;
        }

        quint16 LBLNT68400Abstract::getDP_Ratio_V()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPAdvanceData.ratio_V;
        }

        quint16 LBLNT68400Abstract::getDP_Start_H()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPAdvanceData.start_H;
        }

        quint16 LBLNT68400Abstract::getDP_Start_V()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPAdvanceData.start_V;
        }

        quint16 LBLNT68400Abstract::getDP_Size_H()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPAdvanceData.size_H;
        }

        quint16 LBLNT68400Abstract::getDP_Size_V()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPAdvanceData.size_V;
        }

        quint8 LBLNT68400Abstract::getDP_PIPWindowStatus()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPAdvanceData.windowEnable;
        }

        QList<quint8> LBLNT68400Abstract::getSetting_DP_TX()
        {
            Q_D(LBLNT68400Abstract);
            QList<quint8> list;
            list << d->m_NT68400Data.m_DPTXData.hdmi1 << d->m_NT68400Data.m_DPTXData.hdmi2 \
                << d->m_NT68400Data.m_DPTXData.dp;
            return list;
        }

        bool LBLNT68400Abstract::getSetting_DP_TX_Pcon600(quint8 &hdmi1, quint8 &hdmi2, quint8 &dp)
        {
            Q_D(LBLNT68400Abstract);
            hdmi1 = d->m_NT68400Data.m_DPTXData.hdmi1;
            hdmi2 = d->m_NT68400Data.m_DPTXData.hdmi2;
            dp = d->m_NT68400Data.m_DPTXData.dp;
            return true;
        }
        quint8  LBLNT68400Abstract::getSetting_DP_TX_2ndPlus()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_DPTXData.hdmi2;
        }

        quint8 LBLNT68400Abstract::getSetting_Mute()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_SettingAudioData.mute;
        }

        quint8 LBLNT68400Abstract::getSetting_Volume()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_SettingAudioData.volume;
        }

        quint8 LBLNT68400Abstract::getSetting_AudioSrc()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_SettingAudioData.audioSrc;
        }

        quint8 LBLNT68400Abstract::getSetting_DPSpee()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_SettingOtherData.DP_Speed;
        }

        quint8 LBLNT68400Abstract::getSetting_ByPass()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_SettingOtherData.ByPass;
        }

        QString LBLNT68400Abstract::getSys_Version()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_SysNormalData.getNT68400Version();
        }

        QSize LBLNT68400Abstract::getSys_DisplayArea()
        {
            Q_D(LBLNT68400Abstract);
            return QSize(d->m_NT68400Data.m_SysNormalData.disWidth, d->m_NT68400Data.m_SysNormalData.disHeight);
        }

        quint8 LBLNT68400Abstract::getSignal_InputSignalInfo_InputIndex()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_SignalData.inputIndex;
        }

        quint8 LBLNT68400Abstract::getSignal_InputSignalInfo_Status()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_SignalData.signalStatus;
        }

        QSize LBLNT68400Abstract::getSignal_InputSignalInfo_Size()
        {
            Q_D(LBLNT68400Abstract);
            return QSize(d->m_NT68400Data.m_SignalData.inputSignalWidth, d->m_NT68400Data.m_SignalData.inputSignalHeight);
        }

        quint8 LBLNT68400Abstract::getSignal_InputSignalInfo_FreqInt()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_SignalData.inputFreqInt;
        }

        quint8 LBLNT68400Abstract::getSignal_InputSignalInfo_FreqDec()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_SignalData.inputFreqDec;
        }

        quint8 LBLNT68400Abstract::getSignal_InputSignalInfo_IsInterlaced()
        {
            Q_D(LBLNT68400Abstract);
            return d->m_NT68400Data.m_SignalData.isInterlaced;
        }

        QString LBLNT68400Abstract::getSignal_InputSignalInfo()
        {
            QSize resolution = getSignal_InputSignalInfo_Size();
            quint8 freqInt = getSignal_InputSignalInfo_FreqInt();
            quint8 freqDec = getSignal_InputSignalInfo_FreqDec();
            quint8 isInterlaced = getSignal_InputSignalInfo_IsInterlaced();
            return QString("%1X%2%3@%4.%5Hz").arg(resolution.width())\
                    .arg(resolution.height())\
                    .arg((isInterlaced == NT68400::ENT68400SignalType::ESignal_Interlace) ? "I" : "P")\
                    .arg(freqInt, 2,10,QChar('0'))\
                    .arg(freqDec, 2, 10, QChar('0'));
        }

        QByteArray LBLNT68400Abstract::GetEDIDData()
        {
            Q_D(LBLNT68400Abstract);
            return d->q_ptr->GetEDIDData();
        }

}
}
