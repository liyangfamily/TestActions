#include "LBLNT68400CentralCtrl.h"
#include "LBLNT68400Abstract_p.h"
#include <LBL_CommunicatEngine/LBLClusterProxy>
#include <QFile>

namespace LBL
{
    namespace NT68400
    {

        LBLNT68400CentralCtrl::LBLNT68400CentralCtrl(QObject *parent) :
            LBLNT68400Abstract(parent)
        {
            Q_D(LBLNT68400Abstract);
            d->q_ptr = this;
        }

        LBLNT68400CentralCtrl::LBLNT68400CentralCtrl(LBLNT68400AbstractPrivate & dd, QObject * parent) :
            LBLNT68400Abstract(dd, parent)
        {
            Q_D(LBLNT68400Abstract);
            d->q_ptr = this;
        }

        LBLNT68400CentralCtrl::~LBLNT68400CentralCtrl()
        {
        }

        bool LBLNT68400CentralCtrl::init()
        {
            registerCallBack();
            return true;
        }

        quint16 LBLNT68400CentralCtrl::writePQ_Contrast(quint8 param, quint8 channel, bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_SetContrast, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQNormalData.contrast = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readPQ_Contrast(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_GetContrast, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQNormalData.contrast = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writePQ_DCRStatus(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_SetDCRStatus, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQNormalData.status_DCR = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readPQ_DCRStatus(quint8 channel, bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_GetDCRStatus, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQNormalData.status_DCR = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writePQ_Sharpness(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_SetSharpness, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQNormalData.sharpness = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readPQ_Sharpness(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_GetSharpness, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQNormalData.sharpness = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writePQ_ScreenColorTemp(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_SetScreenColorTemp, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQNormalData.colorTemp = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readPQ_ScreenColorTemp(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_GetScreenColorTemp, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQNormalData.colorTemp = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writePQ_Color_R(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_SetColor_R, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

			QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
			if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
				d->m_NT68400Data.m_PQNormalData.color_R = replyData.at(0);
			}
			return ret;
		}

        quint16 LBLNT68400CentralCtrl::readPQ_Color_R(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_GetColor_R, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

			QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
			if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
				d->m_NT68400Data.m_PQNormalData.color_R = replyData.at(0);
			}
			return ret;
		}

        quint16 LBLNT68400CentralCtrl::writePQ_Color_G(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_SetColor_G, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

			QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
			if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
				d->m_NT68400Data.m_PQNormalData.color_G = replyData.at(0);
			}
			return ret;
		}

        quint16 LBLNT68400CentralCtrl::readPQ_Color_G(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_GetColor_G, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

			QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
			if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
				d->m_NT68400Data.m_PQNormalData.color_G = replyData.at(0);
			}
			return ret;
		}

        quint16 LBLNT68400CentralCtrl::writePQ_Color_B(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_SetColor_B, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

			QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
			if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
				d->m_NT68400Data.m_PQNormalData.color_B = replyData.at(0);
			}
			return ret;
		}

        quint16 LBLNT68400CentralCtrl::readPQ_Color_B(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_GetColor_B, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQNormalData.color_B = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writePQ_SceneMode(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_SetSceneMode, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQNormalData.sceneMode = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readPQ_SceneMode(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_GetSceneMode, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQNormalData.sceneMode = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readAllPQNormalData(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_GetAllNormalParam, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_PQNormalData, replyData.constData()+1, sizeof(SNT68400PictureQualityNormal));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writePQ_3DDEIStatus(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_Set3D_DEI_Status, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQAdvanceData.status_3DDEI = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readPQ_3DDEIStatus(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_Get3D_DEI_Status, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQAdvanceData.status_3DDEI = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writePQ_HDRStatus(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_SetHDR, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQAdvanceData.status_HDR = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readPQ_HDRStatus(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_GetHDR, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQAdvanceData.status_HDR = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writePQ_BrightFrame(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_SetBrightFrame, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQAdvanceData.brightFrame = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readPQ_BrightFrame(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_GetBrightFrame, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_PQAdvanceData.brightFrame = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readAllPQAdvanceData(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400PQ_ChildFlagCMDCode::EPQ_GetAllAdvancedParam, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && (int)sizeof(SNT68400PictureQualityAdvanced)+1 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_PQAdvanceData, replyData.constData() + 1, sizeof(SNT68400PictureQualityAdvanced));
            }
            return ret;
        }


        /*****************************************************************************************************************************************************/
        /*****************************************************************************************************************************************************/
        /*****************************************************************************************************************************************************/


        quint16 LBLNT68400CentralCtrl::writeDP_AspectRatio(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetAspectRatio, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPNormalData.aspectRatio = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_AspectRatio(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetAspectRatio, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPNormalData.aspectRatio = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_OverScanStatus(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetOverScanStatus, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPNormalData.status_overScan = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_OverScanStatus(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetOverScanStatus, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPNormalData.status_overScan = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_PivotStatus(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetPivotStatus, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPNormalData.status_pivot = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_PivotStatus(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetPivotStatus, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPNormalData.status_pivot = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_FlipMode(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetFlipMode, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPNormalData.flipMode = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_FlipMode(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetFlipMode, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPNormalData.flipMode = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readAllDPNormalData(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetAllNormalParam, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && (int)sizeof(SNT68400DisPlayNormal)+1 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPNormalData, replyData.constData() + 1, sizeof(SNT68400DisPlayNormal));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_PIPorPBP(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetPIPPBP, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPAdvanceData.PIPorPBP = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_PIPorPBP(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetPIPPBP, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPAdvanceData.PIPorPBP = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_MainorPIPInput(quint8 param1, quint8 param2, quint8 param3, quint8 param4, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append(param1);
            tempData.append(param2);
            tempData.append(param3);
            tempData.append(param4);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetMainPIP_Input, \
                channel, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 4 <= replyData.size()) {
                d->m_NT68400Data.m_DPAdvanceData.main_Input = replyData.at(0);
                d->m_NT68400Data.m_DPAdvanceData.PIP1_Input = replyData.at(1);
                d->m_NT68400Data.m_DPAdvanceData.PIP2_Input = replyData.at(2);
                d->m_NT68400Data.m_DPAdvanceData.PIP3_Input = replyData.at(3);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_MainorPIPInput(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetMainPIP_Input, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 4 <= replyData.size()) {
                d->m_NT68400Data.m_DPAdvanceData.main_Input = replyData.at(0);
                d->m_NT68400Data.m_DPAdvanceData.PIP1_Input = replyData.at(1);
                d->m_NT68400Data.m_DPAdvanceData.PIP2_Input = replyData.at(2);
                d->m_NT68400Data.m_DPAdvanceData.PIP3_Input = replyData.at(3);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::resetHDMISetting(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_System, ENT68400Sys_ChildFlagCMDCode::ESys_SetReset68400, \
                0, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 4 <= replyData.size()) {
                d->m_NT68400Data.m_DPAdvanceData.main_Input = replyData.at(0);
                d->m_NT68400Data.m_DPAdvanceData.PIP1_Input = replyData.at(1);
                d->m_NT68400Data.m_DPAdvanceData.PIP2_Input = replyData.at(2);
                d->m_NT68400Data.m_DPAdvanceData.PIP3_Input = replyData.at(3);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_WindowSize(quint16 param1, quint16 param2, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append((const char*)&param1, 2);
            tempData.append((const char*)&param2, 2);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetWindowSize, \
                channel, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
            if (ret == LAPI::EResult::ER_Success && 4 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.windowSize_Width, replyData.constData(), sizeof(quint16));
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.windowSize_Height, replyData.constData() + 2, sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_WindowSize(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetWindowSize, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 4 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.windowSize_Width, replyData.constData(), sizeof(quint16));
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.windowSize_Height, replyData.constData() + 2, sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_WindowPos(quint16 param1, quint16 param2, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append((const char*)&param1, 2);
            tempData.append((const char*)&param2, 2);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetWindowPos, \
                channel, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
            if (ret == LAPI::EResult::ER_Success && 4 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.windowPos_X, replyData.constData(), sizeof(quint16));
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.windowPos_Y, replyData.constData() + 2, sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_WindowPos(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetWindowPos, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 4 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.windowPos_X, replyData.constData(), sizeof(quint16));
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.windowPos_Y, replyData.constData() + 2, sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_VideoWall(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetVideoWall, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPAdvanceData.videoWall = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_VideoWall(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetVideoWall, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPAdvanceData.videoWall = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_Ratio_H(quint16 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append((const char*)&param, 2);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetRatio_H, \
                channel, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 2 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.ratio_H, replyData.constData(), sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_Ratio_H(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetRatio_H, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 2 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.ratio_H, replyData.constData(), sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_Ratio_V(quint16 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append((const char*)&param, 2);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetRatio_V, \
                channel, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 2 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.ratio_V, replyData.constData(), sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_Ratio_V(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetRatio_V, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 2 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.ratio_V, replyData.constData(), sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_Start_H(quint16 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append((const char*)&param, 2);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetStart_H, \
                channel, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 2 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.start_H, replyData.constData(), sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_Start_H(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetStart_H, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 2 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.start_H, replyData.constData(), sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_Start_V(quint16 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append((const char*)&param, 2);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetStart_V, \
                channel, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 2 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.start_V, replyData.constData(), sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_Start_V(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetStart_V, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 2 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.start_V, replyData.constData(), sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_Size_H(quint16 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append((const char*)&param, 2);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetSize_H, \
                channel, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 2 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.size_H, replyData.constData(), sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_Size_H(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetSize_H, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 2 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.size_H, replyData.constData(), sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_Size_V(quint16 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append((const char*)&param, 2);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetSize_V, \
                channel, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 2 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.size_V, replyData.constData(), sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_Size_V(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetSize_V, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 2 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.size_V, replyData.constData(), sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeDP_PIPWindowStatus(quint8 status, quint8 channel, bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetPIPWindowStatus, \
                channel, QByteArray((const char*)&status, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPAdvanceData.windowEnable = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readDP_PIPWindowStatus(quint8 channel, bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetPIPWindowStatus, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPAdvanceData.windowEnable = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readAllDPAdvanceData_PIP(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append((const char*)&param, 1);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetAllPIPAdvanceParam, \
                channel, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 14 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData, replyData.constData() + 1, 13);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readAllDPAdvanceData_VideoWall(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append((const char*)&param, 1);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetAllVideoWallAdvanceParam, \
                channel, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 15 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_DPAdvanceData.videoWall, replyData.constData() + 1, 14);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeSetting_DP_TX(quint8 hdmi1, quint8 hdmi2, quint8 dp, quint8 channel, bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray  param;
            param.resize(3);
            param[0] = hdmi1;
            param[1] = hdmi2;
            param[2] = dp;

            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_SetTX, \
                channel, param);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
            if (ret == LAPI::EResult::ER_Success && 3 <= replyData.size()) {
                d->m_NT68400Data.m_DPTXData.hdmi1 = replyData.at(0);
                d->m_NT68400Data.m_DPTXData.hdmi2 = replyData.at(1);
                d->m_NT68400Data.m_DPTXData.dp = replyData.at(2);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readSetting_DP_TX(quint8 channel, bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetTX, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 3 <= replyData.size()) {
                for(int i=0;i<replyData.size();++i){
                    memcpy(&d->m_NT68400Data.m_DPTXData.hdmi1+i,replyData.data()+i,1);
                }
//                d->m_NT68400Data.m_DPTXData.hdmi1 = replyData.at(0);
//                d->m_NT68400Data.m_DPTXData.hdmi2 = replyData.at(1);
//                d->m_NT68400Data.m_DPTXData.dp = replyData.at(2);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeSetting_DP_TX_Pcon600(quint8 hdmi1, quint8 hdmi2, quint8 dp, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);

            /*RK3399 设置68400 TX输出
            附加数据长度3
            ----PCON600--------
            byte13: HDMITX1
            byte14: HDMITX0
            byte15: DPTX0
            Src--0: Android; 1:PC（不存在）; 2:HDMI1;3:HDMI2;4:HDMI3;5:DP; 6:同屏"
            ----二代PLUS--------
            byte13: HDMI Out
            byte14: 固定 5同屏
            byte15: 固定 5同屏
            Src--0: Android; 1:PC; 2:HDMI1;3:HDMI2;4:HDMI3;5:同屏"
            -------------
            注意：
            1. 二代PLUS没有DP，同屏的值与pcon600不同
            2. HDMI仅能设置“同屏”和“HDMIx”
            3. pcon600没有PC源*/
            if( 1==dp || dp<0 || dp>6 )
            {//dp不能为pc源
                return LAPI::EResult::ER_INTECTRL_Fail_Param;
            }
            if( 2 != hdmi1 &&
                3 != hdmi1 &&
                4 != hdmi1 &&
                6 != hdmi1)
            {
                return LAPI::EResult::ER_INTECTRL_Fail_Param;
            }
            if( 2 != hdmi2 &&
                3 != hdmi2 &&
                4 != hdmi2 &&
                6 != hdmi2)
             {
                 return LAPI::EResult::ER_INTECTRL_Fail_Param;
             }

            /*****Write透传数据*****/
            QByteArray  param;
            param.resize(3);
            param[0] = hdmi2;
            param[1] = hdmi1;
            param[2] = dp;

            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400DP_ChildFlagCMDCode::EDP_SetTX, \
                channel, param);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 3 <= replyData.size()) {
                d->m_NT68400Data.m_DPTXData.hdmi2 = replyData.at(0);
                d->m_NT68400Data.m_DPTXData.hdmi1 = replyData.at(1);
                d->m_NT68400Data.m_DPTXData.dp = replyData.at(2);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readSetting_DP_TX_Pcon600(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetTX, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 3 <= replyData.size()) {
                d->m_NT68400Data.m_DPTXData.hdmi2 = replyData.at(0);
                d->m_NT68400Data.m_DPTXData.hdmi1 = replyData.at(1);
                d->m_NT68400Data.m_DPTXData.dp = replyData.at(2);
            }
            return ret;
        }


        quint16 LBLNT68400CentralCtrl::writeSetting_DP_TX_2ndPlus(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);

            /*RK3399 设置68400 TX输出
            附加数据长度3
            ----PCON600--------
            byte13: HDMITX1
            byte14: HDMITX0
            byte15: DPTX0
            Src--0: Android; 1:PC（不存在）; 2:HDMI1;3:HDMI2;4:HDMI3;5:DP; 6:同屏"
            ----二代PLUS--------
            byte13: HDMI Out
            byte14: 固定 5同屏
            byte15: 固定 5同屏
            Src--0: Android; 1:PC; 2:HDMI1;3:HDMI2;4:HDMI3;5:同屏"
            -------------
            注意：
            1. 二代PLUS没有DP，同屏的值与pcon600不同
            2. HDMI仅能设置“同屏”和“HDMIx”
            3. pcon600没有PC源*/
            if( 1 != param &&
                2 != param &&
                3 != param &&
                4 != param &&
                5 != param)
            {
                return LAPI::EResult::ER_INTECTRL_Fail_Param;
            }

            /*****Write透传数据*****/
            QByteArray  paramArray;
            paramArray.resize(3);
            paramArray[0] = param;
            paramArray[1] = 5;
            paramArray[2] = 5;

            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_PictureQuality, ENT68400DP_ChildFlagCMDCode::EDP_SetTX, \
                channel, paramArray);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 3 <= replyData.size()) {
                d->m_NT68400Data.m_DPTXData.hdmi2 = replyData.at(0);
                d->m_NT68400Data.m_DPTXData.hdmi1 = replyData.at(1);
                d->m_NT68400Data.m_DPTXData.dp = replyData.at(2);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readSetting_DP_TX_2ndPlus(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_DisplayPlay, ENT68400DP_ChildFlagCMDCode::EDP_GetTX, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_DPTXData.hdmi2 = replyData.at(0);
                d->m_NT68400Data.m_DPTXData.hdmi1 = replyData.at(1);
                d->m_NT68400Data.m_DPTXData.dp = replyData.at(2);
            }
            return ret;
        }


        /*****************************************************************************************************************************************************/
        /******************************************************************Setting-Audio**********************************************************************/
        /*****************************************************************************************************************************************************/


        quint16 LBLNT68400CentralCtrl::writeSetting_Mute(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Setting, ENT68400Setting_ChildFlagCMDCode::ESetting_SetMuteStatus, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_SettingAudioData.mute = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readSetting_Mute(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Setting, ENT68400Setting_ChildFlagCMDCode::ESetting_SetMuteStatus, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_SettingAudioData.mute = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeSetting_Volume(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Setting, ENT68400Setting_ChildFlagCMDCode::ESetting_SetVolume, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_SettingAudioData.volume = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readSetting_Volume(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Setting, ENT68400Setting_ChildFlagCMDCode::ESetting_GetVolume, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_SettingAudioData.volume = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeSetting_AudioSrc(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Setting, ENT68400Setting_ChildFlagCMDCode::ESetting_SetAudioSrc, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_SettingAudioData.audioSrc = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readSetting_AudioSrc(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Setting, ENT68400Setting_ChildFlagCMDCode::ESetting_GetAudioSrc, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_SettingAudioData.audioSrc = replyData.at(0);
            }
            return ret;
        }


        quint16 LBLNT68400CentralCtrl::readAllSettingAudioData(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Setting, ENT68400Setting_ChildFlagCMDCode::ESetting_RetAllAudioParam, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && (int)sizeof(SNT68400SettingAudio)+1 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_SettingAudioData, replyData.constData() + 1, sizeof(SNT68400SettingAudio));
            }
            return ret;
        }


        /*****************************************************************************************************************************************************/
        /******************************************************************Setting-Other**********************************************************************/
        /*****************************************************************************************************************************************************/


        quint16 LBLNT68400CentralCtrl::writeSetting_DPSpeed(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Setting, ENT68400Setting_ChildFlagCMDCode::ESetting_SetDPSpeed, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_SettingOtherData.DP_Speed = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readSetting_DPSpeed(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Setting, ENT68400Setting_ChildFlagCMDCode::ESetting_GetDPSpeed, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_SettingOtherData.DP_Speed = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeSetting_ByPass(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Setting, ENT68400Setting_ChildFlagCMDCode::ESetting_SetByPassStatus, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_SettingOtherData.ByPass = replyData.at(0);
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readSetting_ByPass(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Setting, ENT68400Setting_ChildFlagCMDCode::ESetting_GetByPassStatus, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 1 <= replyData.size()) {
                d->m_NT68400Data.m_SettingOtherData.ByPass = replyData.at(0);
            }
            return ret;
        }


        quint16 LBLNT68400CentralCtrl::readAllSettingOtherData(quint8 param, quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Setting, ENT68400Setting_ChildFlagCMDCode::ESetting_RetAllOtherParam, \
                channel, QByteArray((const char*)&param, 1));

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && (int)sizeof(SNT68400SettingOther)+1 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_SettingOtherData, replyData.constData() + 1, sizeof(SNT68400SettingOther));
            }
            return ret;
        }


        /*****************************************************************************************************************************************************/
        /******************************************************************System-Normal**********************************************************************/
        /*****************************************************************************************************************************************************/

        quint16 LBLNT68400CentralCtrl::writeSys_PowerOn(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_System, ENT68400Sys_ChildFlagCMDCode::ESys_SetPowerON, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success) {
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeSys_PowerOFF(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_System, ENT68400Sys_ChildFlagCMDCode::ESys_SetPowerOFF, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success) {
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeSys_Reboot(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_System, ENT68400Sys_ChildFlagCMDCode::ESys_SetReboot, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success) {
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeSys_ResetNT68400(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_System, ENT68400Sys_ChildFlagCMDCode::ESys_SetReset68400, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success) {
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeSys_UpgradNT68400(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_System, ENT68400Sys_ChildFlagCMDCode::ESys_RetReset68400Status, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success) {
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readSys_Version(quint8 channel , bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_System, ENT68400Sys_ChildFlagCMDCode::Esys_GetVersion, \
                channel, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && (int)sizeof(tagNT68400SystemNormal)-4 >= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_SysNormalData, replyData.constData(), replyData.size());
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeSys_DisplayArea(quint16 width, quint16 height, bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append((const char*)&width, 2);
            tempData.append((const char*)&height, 2);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_System, ENT68400Sys_ChildFlagCMDCode::ESys_SetDisplayArea, \
                0, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
            if (ret == LAPI::EResult::ER_Success && 4 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_SysNormalData.disWidth, replyData.constData(), sizeof(quint16));
                memcpy(&d->m_NT68400Data.m_SysNormalData.disHeight, replyData.constData() + 2, sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readSys_DisplayArea(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_System, ENT68400Sys_ChildFlagCMDCode::ESys_GetDisplayArea, \
                0, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 4 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_SysNormalData.disWidth, replyData.constData(), sizeof(quint16));
                memcpy(&d->m_NT68400Data.m_SysNormalData.disHeight, replyData.constData() + 2, sizeof(quint16));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::readSignal_InputSignalInfo(quint8 channel, bool sync, int msec)
        {
            Q_UNUSED(channel);
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);
            /*****Read透传数据*****/
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_Signal, ENT68400Signal_ChildFlagCMDCode::ESignal_GetSignalInfo, \
                0, QByteArray());

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 4 <= replyData.size()) {
                memcpy(&d->m_NT68400Data.m_SignalData, replyData.constData(), sizeof(SNT68400Signal));
            }
            return ret;
        }

        quint16 LBLNT68400CentralCtrl::writeFacTest_UpdateEDID(quint8 dataGroupIndex, quint8* pDataBuff, quint8 dataLen, bool sync, int msec)
        {
            Q_UNUSED(sync);
            if (dataGroupIndex >= 16 || nullptr == pDataBuff || dataLen != 16){
                return LAPI::EResult::ER_InDataError;
            }
            Q_D(LBLNT68400Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append(dataGroupIndex);
            tempData.append((const char*)pDataBuff, dataLen);
            SNT68400PenetratCommunicat penetratData(ENT68400MainFlagCMDCode::E_FacTest, ENT68400FacTest_ChildFlagCMDCode::EFacTest_SetUpdateEDID, \
                0, tempData);

            LBLPackageInteCtrl_Penetrate pack(g_NT68400PenetratePackageLen, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0));
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_Success && 4 <= replyData.size()) {
            }
            return ret;
        }

        void LBLNT68400CentralCtrl::registerCallBack()
        {

        }

        quint16 LBL::NT68400::LBLNT68400CentralCtrl::syncSend(QByteArray sendData, QByteArray & replyData, bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLNT68400Abstract);

            LBLEnginePackage enginePack;
            enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
            enginePack.setData(sendData);
            LBLEnginePackage recEnginePack;
            if(sync){
                LBLClusterProxy::syncSend(enginePack, recEnginePack, msec);
            }
            else{
                return LBLClusterProxy::asyncSend(enginePack);
            }

            LBLPackageInteCtrl_Penetrate rePack(recEnginePack.data());
            quint16 ret = rePack.getOperationResult();
            if (LAPI::EResult::ER_INTECTRL_Success != ret) {
                return ret;
            }
            SNT68400PenetratCommunicat rePenetratData(rePack.getReplyData());
            quint16 retP = rePenetratData.getOperationResult();
            if (retP == ENT68400StatusCMDCode::EStatus_SetSuccess || retP == ENT68400StatusCMDCode::EStatus_GetSuccess) {
                retP = retP == ENT68400StatusCMDCode::EStatus_SetSuccess ? LAPI::EResult::ER_INTECTRL_PENETRAT_SetSuccess : LAPI::EResult::ER_INTECTRL_PENETRAT_GetSuccess;
                retP = LAPI::EResult::ER_Success;
                replyData = rePenetratData.getReplyData();
            }
            return retP;
        }

        QByteArray LBLNT68400CentralCtrl::GetEDIDData()
        {
            QString fileName = LBLUIHelper::appParamDataLocation()+"//EDID//68400-HDMI-2.0.bin";

            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly))
            {
                return nullptr;
            }

            QByteArray data = file.readAll();
            file.close();

            return data;
        }
    }
}
