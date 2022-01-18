#include "LBLMS9570CentralCtrl.h"
#include "LBLMS9570Abstract_p.h"
#include <LBL_CommunicatEngine/LBLClusterProxy>
#include <QFile>
#include "LBL_Core/LBLUIHelper.h"
namespace LBL
{
    namespace MS9570
    {
        LBLMS9570CentralCtrl::LBLMS9570CentralCtrl(QObject *parent):
            LBLMS9570Abstract(parent)
        {
            Q_D(LBLMS9570Abstract);
            d->q_ptr = this;
        }

        LBLMS9570CentralCtrl::LBLMS9570CentralCtrl(LBLMS9570AbstractPrivate & dd, QObject * parent) :
            LBLMS9570Abstract(dd, parent)
        {
            Q_D(LBLMS9570Abstract);
            d->q_ptr = this;
        }

        LBLMS9570CentralCtrl::~LBLMS9570CentralCtrl()
        {
        }

        bool LBLMS9570CentralCtrl::init()
        {
            registerCallBack();
            return true;
        }
        void LBLMS9570CentralCtrl::registerCallBack()
        {
        }

        quint16 LBLMS9570CentralCtrl::writeBaypass(quint8 value, bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLMS9570Abstract);
            /*****Write透传数据*****/
            SMS9570PenetratCommunicat penetratData(0x39, 0x23 \
                , QByteArray((const char*)&value, 1));

            LBLPackageInteCtrl_Penetrate pack(0, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0).getDataToSend());
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_INTECTRL_Success) {
                d->m_MS9570Data.bypass = value;
            }
            return ret;
        }
        quint16 LBLMS9570CentralCtrl::readBaypass(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLMS9570Abstract);
            /*****Write透传数据*****/
            quint8 value=0xF0;
            SMS9570PenetratCommunicat penetratData(0x39, 0x22 \
                , QByteArray(1, value));

            LBLPackageInteCtrl_Penetrate pack(0, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0).getDataToSend());
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_INTECTRL_Success) {
                d->m_MS9570Data.bypass = replyData.at(2);
            }
            return ret;
        }
        quint8 LBLMS9570CentralCtrl::getBaypass()
        {
            Q_D(LBLMS9570Abstract);
            return d->m_MS9570Data.bypass;
        }

        quint16 LBLMS9570CentralCtrl::writeOutputResolutionInfo(quint32 param1, quint32 param2, bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLMS9570Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append((const char*)&param1, 2);
            tempData.append((const char*)&param2, 2);
            SMS9570PenetratCommunicat penetratData(0x39, 0x51 \
                , tempData);

            LBLPackageInteCtrl_Penetrate pack(0, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0).getDataToSend());
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
            if (ret == LAPI::EResult::ER_INTECTRL_Success) {
                d->m_MS9570Data.outputWidth = param1;
                d->m_MS9570Data.outputHeight = param2;
            }
            return ret;
        }

        quint16 LBLMS9570CentralCtrl::readOutputResolutionInfo(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLMS9570Abstract);
            /*****Write透传数据*****/
            quint8 value=0xF0;
            SMS9570PenetratCommunicat penetratData(0x39, 0x50 \
                , QByteArray(1, value));

            LBLPackageInteCtrl_Penetrate pack(0, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0).getDataToSend());
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
            if (ret == LAPI::EResult::ER_INTECTRL_Success) {
                memcpy(&(d->m_MS9570Data.outputWidth), replyData.constData() + 2, 4);
                memcpy(&(d->m_MS9570Data.outputHeight), replyData.constData() + 2+4, 4);
            }
            return ret;
        }

        QSize LBLMS9570CentralCtrl::getOutputResolutionInfo()
        {
            Q_D(LBLMS9570Abstract);
            return QSize(d->m_MS9570Data.outputWidth,d->m_MS9570Data.outputHeight);
        }

        quint16 LBLMS9570CentralCtrl::readInputResolutionInfo(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLMS9570Abstract);
            /*****Write透传数据*****/
            quint8 value=0xF0;
            SMS9570PenetratCommunicat penetratData(0x39, 0x52 \
                , QByteArray(1, value));

            LBLPackageInteCtrl_Penetrate pack(0, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0).getDataToSend());
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, sync, msec);
            if (ret == LAPI::EResult::ER_INTECTRL_Success) {
                memcpy(&(d->m_MS9570Data.inputWidth), replyData.constData() + 2, 4);
                memcpy(&(d->m_MS9570Data.inputHeight), replyData.constData() + 2+4, 4);
                memcpy(&(d->m_MS9570Data.inputFrequency), replyData.constData() + 2+4+4, 1);
            }
            return ret;
        }

        QString LBLMS9570CentralCtrl::getInputResolutionInfo()
        {
            Q_D(LBLMS9570Abstract);
            QSize resolution = QSize(d->m_MS9570Data.inputWidth,d->m_MS9570Data.inputHeight);
            quint8 freqInt = d->m_MS9570Data.inputFrequency;
            return QString("%1X%2@%3Hz").arg(resolution.width())\
                .arg(resolution.height())\
                .arg(freqInt, 2,10,QChar('0'));
        }

        quint16 LBLMS9570CentralCtrl::writeHDMIEDID(int dataGroupIndex, quint8* pDataBuff, int dataLen)
        {
            Q_D(LBLMS9570Abstract);
            /*****Write透传数据*****/
            QByteArray tempData;
            tempData.append(dataGroupIndex);
            tempData.append((const char*)pDataBuff, dataLen);

            SMS9570PenetratCommunicat penetratData(0x39, 0x32 \
                                                   , QByteArray((const char*)&pDataBuff, 1));

            LBLPackageInteCtrl_Penetrate pack(0, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0).getDataToSend());
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, LBL_Defalut_SyncTimeout);
            if (ret == LAPI::EResult::ER_INTECTRL_Success) {
            }
            return ret;

            return quint16();
        }

        quint16 LBLMS9570CentralCtrl::syncSend(QByteArray sendData, QByteArray & replyData, bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLMS9570Abstract);

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
            SMS9570PenetratCommunicat rePenetratData(rePack.getReplyData());
            replyData = rePenetratData.getReplyData();
            return ret;
        }

        quint16 LBLMS9570CentralCtrl::readVersion(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(sync);
            Q_D(LBLMS9570Abstract);
            /*****Write透传数据*****/
            quint8 value = 0xF0;
            SMS9570PenetratCommunicat penetratData(0x39, 0x10 \
                , QByteArray(1, value));

            LBLPackageInteCtrl_Penetrate pack(4, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0).getDataToSend());
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_INTECTRL_Success) {
                memcpy(&(d->m_MS9570Data.version), replyData.constData() + 2, 2);
            }
            return ret;
        }

        QString LBLMS9570CentralCtrl::getVersion()
        {
            Q_D(LBLMS9570Abstract);
            return QString("0x%1").arg(QString::number(d->m_MS9570Data.version, 16));
        }

        quint16 LBLMS9570CentralCtrl::writeReset(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_D(LBLMS9570Abstract);
            /*****Write透传数据*****/
            quint8 value = 0x01;
            SMS9570PenetratCommunicat penetratData(0x39, 0x19 \
                , QByteArray((const char*)&value, 1));

            LBLPackageInteCtrl_Penetrate pack(0, LBLPackageInteCtrl_Penetrate::PenetrateMaxWaitTime, penetratData.build(0).getDataToSend());
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            QByteArray replyData;
            quint16 ret = syncSend(pack.getDataToSend(), replyData, true, msec);
            if (ret == LAPI::EResult::ER_INTECTRL_Success) {
            }
            return ret;
        }

        quint16 LBLMS9570CentralCtrl::writeColorMode(quint8 value, bool sync, int msec)
        {
            Q_UNUSED(value);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint16 LBLMS9570CentralCtrl::readColorMode(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint8 LBLMS9570CentralCtrl::getColorMode()
        {
            return quint8();
        }

        quint16 LBLMS9570CentralCtrl::writeRGBGain(quint8 rValue, quint8 gValue, quint8 bValue, bool sync, int msec)
        {
            Q_UNUSED(rValue);
            Q_UNUSED(gValue);
            Q_UNUSED(bValue);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint16 LBLMS9570CentralCtrl::readRGBGain(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        QList<quint8> LBLMS9570CentralCtrl::getRGBGain()
        {
            return QList<quint8>();
        }

        quint16 LBLMS9570CentralCtrl::writeBackLight(quint8 value, bool sync, int msec)
        {
            Q_UNUSED(value);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint16 LBLMS9570CentralCtrl::readBackLight(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint8 LBLMS9570CentralCtrl::getBackLight()
        {
            return quint8();
        }

        quint16 LBLMS9570CentralCtrl::writeInputSource(quint8 value, bool sync, int msec)
        {
            Q_UNUSED(value);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint16 LBLMS9570CentralCtrl::readInputSource(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint8 LBLMS9570CentralCtrl::getInputSource()
        {
            return quint8();
        }

        quint16 LBLMS9570CentralCtrl::writeImageRatio(quint8 value, bool sync, int msec)
        {
            Q_UNUSED(value);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint16 LBLMS9570CentralCtrl::readImageRatio(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint8 LBLMS9570CentralCtrl::getImageRatio()
        {
            return quint8();
        }

        quint16 LBLMS9570CentralCtrl::writeContrast(quint8 value, bool sync, int msec)
        {
            Q_UNUSED(value);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint16 LBLMS9570CentralCtrl::readContrast(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint8 LBLMS9570CentralCtrl::getContrast()
        {
            return quint8();
        }

        quint16 LBLMS9570CentralCtrl::writeVolume(quint8 value, bool sync, int msec)
        {
            Q_UNUSED(value);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint16 LBLMS9570CentralCtrl::readVolume(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return quint16();
        }

        quint8 LBLMS9570CentralCtrl::getVolume()
        {
            return quint8();
        }

        QByteArray LBLMS9570CentralCtrl::GetEDIDData()
        {
            QString fileName = LBLUIHelper::appParamDataLocation()+"//EDID//2nd_Default_EDID.bin";

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
