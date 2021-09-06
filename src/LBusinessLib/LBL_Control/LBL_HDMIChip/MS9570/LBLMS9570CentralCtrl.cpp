#include "LBLMS9570CentralCtrl.h"
#include "LBLMS9570Abstract_p.h"
#include <LBL_CommunicatEngine/LBLClusterProxy>

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
			qDebug() << __FUNCTION__;
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

		quint16 LBLMS9570CentralCtrl::writeOutputResolutionInfo(quint16 param1, quint16 param2, bool sync, int msec)
		{
            Q_UNUSED(param1);
            Q_UNUSED(param2);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
			return quint16();
		}

		quint16 LBLMS9570CentralCtrl::readOutputResolutionInfo(bool sync, int msec)
		{
            Q_UNUSED(sync);
            Q_UNUSED(msec);
			return quint16();
		}

		QSize LBLMS9570CentralCtrl::getOutputResolutionInfo()
		{
			return QSize();
		}

		quint16 LBLMS9570CentralCtrl::readInputResolutionInfo(bool sync, int msec)
		{
            Q_UNUSED(sync);
            Q_UNUSED(msec);
			return quint16();
		}

		QSize LBLMS9570CentralCtrl::getInputResolutionInfo()
		{
			return QSize();
		}

		quint16 LBLMS9570CentralCtrl::writeHDMIEDID(int index, QByteArray pdata)
		{
            Q_UNUSED(index);
            Q_UNUSED(pdata);
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
			LBLClusterProxy::syncSend(enginePack, recEnginePack, msec);

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
				memcpy_s(&(d->m_MS9570Data.version), 2, replyData.constData() + 2, 2);
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
            Q_UNUSED(msec);
			return quint16();
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

	}
}
