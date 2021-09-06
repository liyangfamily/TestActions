#include "LBLHDMIChipAbstract.h"
#include "LBLHDMIChipAbstract_p.h"


namespace LBL
{
	namespace HDMIChip
	{
		LBLHDMIChipAbstract::LBLHDMIChipAbstract(QObject* parent) :
			QObject(parent), d_ptr(new LBLHDMIChipAbstractPrivate)
		{
			Q_D(LBLHDMIChipAbstract);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		LBLHDMIChipAbstract::LBLHDMIChipAbstract(LBLHDMIChipAbstractPrivate & dd, QObject* parent) :
			QObject(parent), d_ptr(&dd)
		{
			Q_D(LBLHDMIChipAbstract);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		LBLHDMIChipAbstract::~LBLHDMIChipAbstract()
		{
			Q_D(LBLHDMIChipAbstract);
			qDebug() << __FUNCTION__;
			d->m_packageMgr.unregisterAll();
		}

		bool LBLHDMIChipAbstract::setDetectInfoStruct(SDetectItemInfo * detectInfo)
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
			return true;
		}
		bool LBLHDMIChipAbstract::parsingDataFrame(const LBLPackage & pack)
		{
			Q_D(LBLHDMIChipAbstract);
			return d->m_packageMgr.handle(pack);
		}

		quint16 LBLHDMIChipAbstract::writeVolume(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLHDMIChipAbstract::readVolume(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLHDMIChipAbstract::getVolume()
		{
			return quint8();
		}

		quint16 LBLHDMIChipAbstract::writeBypass(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint16 LBLHDMIChipAbstract::readBypass(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint8 LBLHDMIChipAbstract::getBypasss()
		{
			return quint8();
		}
		quint16 LBLHDMIChipAbstract::writeRatio(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint16 LBLHDMIChipAbstract::readRatio(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint8 LBLHDMIChipAbstract::getRatio()
		{
			return quint8();
		}
		quint16 LBLHDMIChipAbstract::writeSource(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint16 LBLHDMIChipAbstract::readSource(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint8 LBLHDMIChipAbstract::getSource()
		{
			return quint8();
		}
		quint16 LBLHDMIChipAbstract::writeContrast(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint16 LBLHDMIChipAbstract::readContrast(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint8 LBLHDMIChipAbstract::getContrast()
		{
			return quint8();
		}
		quint16 LBLHDMIChipAbstract::writeColortemperature(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint16 LBLHDMIChipAbstract::readColortemperature(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint8 LBLHDMIChipAbstract::getColortemperature()
		{
			return quint8();
		}
		quint16 LBLHDMIChipAbstract::writeBrightness(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint16 LBLHDMIChipAbstract::readBrightness(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint8 LBLHDMIChipAbstract::getBrightness()
		{
			return quint8();
		}
		quint16 LBLHDMIChipAbstract::writeRGain(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint16 LBLHDMIChipAbstract::readRGain(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint8 LBLHDMIChipAbstract::getRGain()
		{
			return quint8();
		}
		quint16 LBLHDMIChipAbstract::writeGGain(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint16 LBLHDMIChipAbstract::readGGain(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint8 LBLHDMIChipAbstract::getGGain()
		{
			return quint8();
		}
		quint16 LBLHDMIChipAbstract::writeBGain(quint8 value, bool sync, int msec)
		{
			Q_UNUSED(value);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint16 LBLHDMIChipAbstract::readBGain(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint8 LBLHDMIChipAbstract::getBGain()
		{
			return quint8();
		}
		quint16 LBLHDMIChipAbstract::writeRGBGain(quint8 rValue, quint8 gValue, quint8 bValue, bool sync, int msec)
		{
			Q_UNUSED(rValue);
			Q_UNUSED(gValue);
			Q_UNUSED(bValue);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		quint16 LBLHDMIChipAbstract::readRGBGain(bool sync, int msec)
		{
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}
		QList<quint8> LBLHDMIChipAbstract::getRGBGain()
		{
            return QList<quint8>();
        }

        quint16 LBLHDMIChipAbstract::writeResolution(quint32 width, quint32 height,quint8 refreshRate, bool sync, int msec)
        {
            Q_UNUSED(width);
            Q_UNUSED(height);
            Q_UNUSED(refreshRate);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        quint16 LBLHDMIChipAbstract::readResolution(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        QSize LBLHDMIChipAbstract::getResolution()
        {
            return QSize();
        }

        quint8 LBLHDMIChipAbstract::getRefreshRate()
        {
            return quint8();
        }

        quint16 LBLHDMIChipAbstract::readCombinationInfo(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        quint16 LBLHDMIChipAbstract::writeSceneMode(quint8 value, bool sync, int msec)
        {
            Q_UNUSED(value);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        quint16 LBLHDMIChipAbstract::readSceneMode(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        quint8 LBLHDMIChipAbstract::getSceneMode()
        {
            return quint8();
        }

        quint16 LBLHDMIChipAbstract::writeSplitScreenMode(quint8 value, bool sync, int msec)
        {
            Q_UNUSED(value);
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        quint16 LBLHDMIChipAbstract::readSplitScreenMode(bool sync, int msec)
        {
            Q_UNUSED(sync);
            Q_UNUSED(msec);
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        quint8 LBLHDMIChipAbstract::getSplitScreenMode()
        {
            return quint8();
        }
	}
}
