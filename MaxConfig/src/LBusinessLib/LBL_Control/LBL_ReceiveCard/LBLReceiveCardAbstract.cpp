#include "LBLReceiveCardAbstract.h"
#include "LBLReceiveCardAbstract_p.h"

namespace LBL
{
	namespace RC
	{

		LBLReceiveCardAbstract::LBLReceiveCardAbstract(QObject* parent) :
			QObject(parent), d_ptr(new LBLReceiveCardAbstractPrivate)
		{
			Q_D(LBLReceiveCardAbstract);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		LBLReceiveCardAbstract::LBLReceiveCardAbstract(LBLReceiveCardAbstractPrivate& dd, QObject* parent) :
			QObject(parent), d_ptr(&dd)
		{
			Q_D(LBLReceiveCardAbstract);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		LBLReceiveCardAbstract::~LBLReceiveCardAbstract()
		{
			Q_D(LBLReceiveCardAbstract);
			d->m_packageMgr.unregisterAll();
			qDebug() << __FUNCTION__;
		}


		bool LBLReceiveCardAbstract::setDetectInfoStruct(SDetectItemInfo *detectInfo)
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

		bool LBLReceiveCardAbstract::parsingDataFrame(const LBLPackage& pack)
		{
			Q_D(LBLReceiveCardAbstract);
			return d->m_packageMgr.handle(pack);
		}

		quint16 LBLReceiveCardAbstract::writeFPGARegister(quint8 port, quint8 module, quint32 addr, QByteArray value, bool sync, int msec)
		{
            Q_UNUSED(port)
            Q_UNUSED(module)
            Q_UNUSED(addr)
            Q_UNUSED(value)
            Q_UNUSED(sync)
            Q_UNUSED(msec)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLReceiveCardAbstract::readFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 len, bool sync, int msec)
        {
			Q_UNUSED(port)
				Q_UNUSED(module)
				Q_UNUSED(addr)
				Q_UNUSED(len)
				Q_UNUSED(sync)
				Q_UNUSED(msec)
				return QByteArray();
        }

		QByteArray LBLReceiveCardAbstract::getFPGARegister()
		{
			return QByteArray();
		}

		quint16 LBLReceiveCardAbstract::writeModuleParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
		{
			Q_UNUSED(port)
				Q_UNUSED(module)
				Q_UNUSED(value)
				Q_UNUSED(sync)
				Q_UNUSED(msec)
				return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLReceiveCardAbstract::readModuleParam(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_UNUSED(port)
				Q_UNUSED(module)
				Q_UNUSED(sync)
				Q_UNUSED(msec)
				return QByteArray();
		}

		QByteArray LBLReceiveCardAbstract::getModuleParam()
		{
			return QByteArray();
		}

		quint16 LBLReceiveCardAbstract::writeDriveICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
		{
			Q_UNUSED(port)
				Q_UNUSED(module)
				Q_UNUSED(value)
				Q_UNUSED(sync)
				Q_UNUSED(msec)
				return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLReceiveCardAbstract::readDriveICParam(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_UNUSED(port)
				Q_UNUSED(module)
				Q_UNUSED(sync)
				Q_UNUSED(msec)
				return QByteArray();
		}

		QByteArray LBLReceiveCardAbstract::getDriveICParam()
		{
			return QByteArray();
		}

		quint16 LBLReceiveCardAbstract::writeDecodingICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
		{
			Q_UNUSED(port)
				Q_UNUSED(module)
				Q_UNUSED(value)
				Q_UNUSED(sync)
				Q_UNUSED(msec)
				return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QByteArray LBLReceiveCardAbstract::readDecodingICParam(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_UNUSED(port)
				Q_UNUSED(module)
				Q_UNUSED(sync)
				Q_UNUSED(msec)
				return QByteArray();
		}

		QByteArray LBLReceiveCardAbstract::getDecodingICParam()
		{
			return QByteArray();
		}

		quint16 LBLReceiveCardAbstract::writeSaveRCParamByRegister(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_UNUSED(port)
				Q_UNUSED(module)
			Q_UNUSED(sync)
				Q_UNUSED(msec)
            return LAPI::EResult::ER_NotSupportThisCommand;
        }

        quint16 LBLReceiveCardAbstract::writeCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec)
        {
            Q_UNUSED(port)
                Q_UNUSED(module)
                Q_UNUSED(sync)
                Q_UNUSED(msec)
                return LAPI::EResult::ER_NotSupportThisCommand;
        }

		quint16 LBLReceiveCardAbstract::writeCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_UNUSED(port)
				Q_UNUSED(module)
				Q_UNUSED(sync)
				Q_UNUSED(msec)
				return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLReceiveCardAbstract::writeCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_UNUSED(port)
				Q_UNUSED(module)
				Q_UNUSED(sync)
				Q_UNUSED(msec)
				return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLReceiveCardAbstract::readStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag, bool sync, int msec)
		{
			Q_UNUSED(portStart);
			Q_UNUSED(portCount);
			Q_UNUSED(moduleStart);
			Q_UNUSED(moduleCount);
			Q_UNUSED(lengthFlag);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QList<SRCStatusInfo> LBLReceiveCardAbstract::getStatusInfo()
		{
			return QList<SRCStatusInfo>();
		}

		quint16 LBLReceiveCardAbstract::readMonitorInfo(quint8 portIndex, bool sync, int msec)
		{
			Q_UNUSED(portIndex);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		QList<SRCMonitorInfo> LBLReceiveCardAbstract::getMonitorInfo()
		{
			return QList<SRCMonitorInfo>();
		}

		quint16 LBLReceiveCardAbstract::writeSaveRCParam(quint8 port, quint16 module, bool sync, int msec)
		{
			Q_UNUSED(port);
			Q_UNUSED(module);
			Q_UNUSED(sync);
			Q_UNUSED(msec);
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

	}
}
