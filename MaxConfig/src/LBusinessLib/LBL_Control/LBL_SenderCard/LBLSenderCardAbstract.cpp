#include "LBLSenderCardAbstract.h"
#include "LBLSenderCardAbstract_p.h"

namespace LBL
{
	namespace SC
	{
		LBLSenderCardAbstract::LBLSenderCardAbstract(QObject* parent) :
			QObject(parent), d_ptr(new LBLSenderCardAbstractPrivate)
		{
			Q_D(LBLSenderCardAbstract);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		LBLSenderCardAbstract::LBLSenderCardAbstract(LBLSenderCardAbstractPrivate& dd, QObject* parent) :
			QObject(parent), d_ptr(&dd)
		{
			Q_D(LBLSenderCardAbstract);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		LBLSenderCardAbstract::~LBLSenderCardAbstract()
		{
			Q_D(LBLSenderCardAbstract);
			d->m_packageMgr.unregisterAll();
			qDebug() << __FUNCTION__;
		}

		bool LBLSenderCardAbstract::setDetectInfoStruct(SDetectItemInfo *detectInfo)
		{
			Q_ASSERT(detectInfo);
			d_ptr->m_parentItemDetectInfo = detectInfo;
			if (d_ptr->m_parentItemDetectInfo->communType == ECommunicatType::ECT_COM)
			{
				d_ptr->m_targetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_MCU_In_Sender;
			}
			else
			{
				d_ptr->m_targetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_Android;
			}
			d_ptr->m_registerTargetDeviceType = d_ptr->m_targetDeviceType;
			if (detectInfo->senderCardClass == ESenderCardClass::ESC_2nd_GZ) {
				d_ptr->m_registerTargetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_MCU_In_Sender;
			}
			return true;
		}

		void LBLSenderCardAbstract::checkItemUuid()
		{
			Q_D(LBLSenderCardAbstract);
			if ((d->m_parentItemDetectInfo->uuidType == 0xFF)
				|| (d->m_parentItemDetectInfo->uuid.isNull() && d->m_parentItemDetectInfo->uuidType == 0x00))
			{
				if (LAPI::EResult::ER_Success != this->readSenderCardUuid(true, 150)) {
					qDebug() << d->m_parentItemDetectInfo->hostName << "Read Uuid Failed.";
				}
				else {
					d->m_parentItemDetectInfo->uuid = getSenderCardUuid();
					d->m_parentItemDetectInfo->uuidType = getSenderCardUuidType();
				}
			}
		}

		bool LBLSenderCardAbstract::parsingDataFrame(const LBLPackage& pack)
		{
			Q_D(LBLSenderCardAbstract);
			return d->m_packageMgr.handle(pack);
		}

		quint16 LBLSenderCardAbstract::writeFPGARegister(quint32 addr, QByteArray value, bool sync, int msec)
		{
            Q_UNUSED(addr)
            Q_UNUSED(value)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readFPGARegister(quint32 addr, quint16 len, bool sync, int msec)
        {
            Q_UNUSED(addr)
            Q_UNUSED(len)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return QByteArray();
        }

		QByteArray LBLSenderCardAbstract::getFPGARegister()
		{
			return QByteArray();
		}

		QByteArray LBLSenderCardAbstract::readFPGAVersion(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
				return QByteArray();
		}

		QString LBLSenderCardAbstract::getFPGAVersion()
		{
			return QString();
		}

		quint16 LBLSenderCardAbstract::writeFPGAEthLoad(const QList<LBLSPort>& value, bool sync, int msec)
		{
            Q_UNUSED(value)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readFPGAEthLoad(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
				return QByteArray();
		}

		QList<LBLSPort> LBLSenderCardAbstract::getFPGAEthLoad()
		{
			return QList<LBLSPort>();
		}

		quint16 LBLSenderCardAbstract::readMCUAppVersion(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QString LBLSenderCardAbstract::getMCUAppVersion()
		{
			return QString();
		}

		quint16 LBLSenderCardAbstract::readMCUBootVersion(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QString LBLSenderCardAbstract::getMCUBootVersion()
		{
			return QString();
		}

		QByteArray LBLSenderCardAbstract::readEthLoopTest(bool sync, int msec)
		{
			Q_UNUSED(sync)
				Q_UNUSED(msec)
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::getEthLoopTest_Count()
		{
			return quint8();
		}

		QMap<quint8, float> LBLSenderCardAbstract::getEthLoopTest_BitErrRate()
		{
			return QMap<quint8, float>();
		}

		quint16 LBLSenderCardAbstract::writeSelfTestModeOpen(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readSelfTestModeOpen(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::getSelfTestModeOpen()
		{
			return quint8();
		}

		quint16 LBLSenderCardAbstract::writeSelfTestModeStart(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readSelfTestModeStart(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::getSelfTestModeStart()
		{
			return quint8();
		}

		quint16 LBLSenderCardAbstract::writeSelfTestMode(quint8 mode, bool sync, int msec)
		{
			Q_UNUSED(mode);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readSelfTestMode(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::getSelfTestMode()
		{
			return quint8();
		}

		quint16 LBLSenderCardAbstract::writeSelfTestModeSpeed(quint8 speed, bool sync, int msec)
		{
			Q_UNUSED(speed);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readSelfTestModeSpeed(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::getSelfTestModeSpeed()
		{
			return quint8();
		}

		quint16 LBLSenderCardAbstract::sendConnectionBuffer(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLSenderCardAbstract::readConnectionBuffer(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::getConnectionBuffer()
		{
			return QByteArray();
		}

		quint16 LBLSenderCardAbstract::writeSaveSCParam(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLSenderCardAbstract::writeBrightness(int value, bool sync, int msec)
		{
            Q_UNUSED(value)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLSenderCardAbstract::readBrightness(bool sync, int msec)
        {
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		int LBLSenderCardAbstract::getBrightness()
		{
			return 0;
		}

		quint16 LBLSenderCardAbstract::writeSenderCardUuid(quint8 idType, QUuid uuid, bool sync, int msec)
		{
            Q_UNUSED(idType)
            Q_UNUSED(uuid)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLSenderCardAbstract::readSenderCardUuid(bool sync, int msec)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QUuid LBLSenderCardAbstract::getSenderCardUuid()
		{
			return QUuid();
		}

		quint8 LBLSenderCardAbstract::getSenderCardUuidType()
		{
			return quint8();
		}


		quint16 LBLSenderCardAbstract::writeScreenBlack(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readScreenBlack(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::getScreenBlack()
		{
			return quint8();
		}

		quint16 LBLSenderCardAbstract::writeScreenLock(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readScreenLock(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::getScreenLock()
		{
			return quint8();
		}

		quint16 LBLSenderCardAbstract::writeZoomMode(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readZoomMode(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::getZoomMode()
		{
			return quint8();
		}

		quint16 LBLSenderCardAbstract::writeZoomSize(QSize value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readZoomSize(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		QSize LBLSenderCardAbstract::getZoomSize()
		{
			return QSize();
		}

		quint16 LBLSenderCardAbstract::writeErrorBitRateStatisticalSwitch(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readErrorBitRateStatisticalSwitch(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::getErrorBitRateStatisticalSwitch()
		{
			return quint8();
		}

		quint16 LBLSenderCardAbstract::writeCorrectionSwitch(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readCorrectionSwitch(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::getCorrectionSwitch()
		{
			return quint8();
		}

		quint16 LBLSenderCardAbstract::writeSpreadSpectrumSwitch(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::readSpreadSpectrumSwitch(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::getSpreadSpectrumSwitch()
		{
			return quint8();
		}

		quint16 LBLSenderCardAbstract::write24BitGammaSwitch(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLSenderCardAbstract::read24BitGammaSwitch(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::get24BitGammaSwitch()
		{
			return quint8();
		}

		quint16 LBLSenderCardAbstract::writeProtocolType(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		QByteArray LBLSenderCardAbstract::readProtocolType(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return QByteArray();
		}

		quint8 LBLSenderCardAbstract::getProtocolType()
		{
			return quint8();
		}

	}
}
