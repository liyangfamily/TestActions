#include "LBLFileTransferAbstract.h"
#include "LBLFileTransferAbstract_p.h"

namespace LBL
{
	namespace FileTransfer
	{

		LBLFileTransferAbstract::LBLFileTransferAbstract(QObject* parent) :
			QObject(parent), d_ptr(new LBLFileTransferAbstractPrivate)
		{
			Q_D(LBLFileTransferAbstract);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		LBLFileTransferAbstract::LBLFileTransferAbstract(LBLFileTransferAbstractPrivate& dd, QObject* parent) :
			QObject(parent), d_ptr(&dd)
		{
			Q_D(LBLFileTransferAbstract);
            Q_UNUSED(d)
			d_ptr->q_ptr = this;
		}

		LBLFileTransferAbstract::~LBLFileTransferAbstract()
		{
			Q_D(LBLFileTransferAbstract);
			d->m_packageMgr.unregisterAll();
			qDebug() << __FUNCTION__;
		}

		bool LBLFileTransferAbstract::setDetectInfoStruct(SDetectItemInfo *detectInfo)
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

		bool LBLFileTransferAbstract::parsingDataFrame(const LBLPackage& pack)
		{
			Q_D(LBLFileTransferAbstract);
			return d->m_packageMgr.handle(pack);
		}

		bool LBLFileTransferAbstract::isUpgradeSend()
		{
			Q_D(LBLFileTransferAbstract);
			return d->m_upgradingSend;
		}

		quint16 LBLFileTransferAbstract::upgradingFileType()
		{
			Q_D(LBLFileTransferAbstract);
			return d->m_upgradingFileType;
		}

		quint8 LBLFileTransferAbstract::upgradingPortIndex()
		{
			Q_D(LBLFileTransferAbstract);
			return d->m_upgradingPort;
		}

		quint16 LBLFileTransferAbstract::upgradingModuleIndex()
		{
			Q_D(LBLFileTransferAbstract);
			return d->m_upgradingModule;
		}

		bool LBLFileTransferAbstract::isUpgradeStarted()
		{
			Q_D(LBLFileTransferAbstract);
			return d->m_upgradeFileFuture.isStarted();
		}

		bool LBLFileTransferAbstract::isUpgrading()
		{
			Q_D(LBLFileTransferAbstract);
			return d->m_upgradeFileFuture.isRunning();
		}

		bool LBLFileTransferAbstract::isUpgradeFinished()
		{
			Q_D(LBLFileTransferAbstract);
			return d->m_upgradeFileFuture.isFinished();
		}

		bool LBLFileTransferAbstract::cancelUpgrade()
		{
			Q_D(LBLFileTransferAbstract);
			d->m_upgradeCancel = true;
			return true;
		}

		quint16 LBLFileTransferAbstract::upgradeResult()
		{
			Q_D(LBLFileTransferAbstract);
			if (d->m_upgradeFileFuture.isFinished()) {
				if (d->m_upgradeFileFuture.isResultReadyAt(0)) {
					return d->m_upgradeFileFuture.result();
				}
			}
			return 0;
		}

		QFuture<quint16> LBLFileTransferAbstract::upgradeFuture()
		{
			Q_D(LBLFileTransferAbstract);
			return d->m_upgradeFileFuture;
		}

		quint16 LBLFileTransferAbstract::common_UpgradeFile(bool sync, int msec, quint16 fileType, QString filePath)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(filePath)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLFileTransferAbstract::common_UpgradeFile(bool sync, int msec, quint16 fileType, QByteArray data)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(data)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLFileTransferAbstract::forMCU_RequestFile(bool sync, int msec, quint16 fileType, QString filePath)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(filePath)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLFileTransferAbstract::forMCU_RequestFile(bool sync, int msec, quint16 fileType, QByteArray& data)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(data)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLFileTransferAbstract::forMCU_UpgradeFile(bool sync, int msec, quint16 fileType, QString filePath, quint8 portIndex, quint16 moduleIndex)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(filePath)
            Q_UNUSED(portIndex)
            Q_UNUSED(moduleIndex)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLFileTransferAbstract::forMCU_UpgradeFile(bool sync, int msec, quint16 fileType, QByteArray data, quint8 portIndex, quint16 moduleIndex)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(data)
            Q_UNUSED(portIndex)
            Q_UNUSED(moduleIndex)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

		quint16 LBLFileTransferAbstract::getRequestFileData(QByteArray & fileData)
		{
			Q_D(LBLFileTransferAbstract);
			if (d->m_upgradeFileFuture.isFinished()) {
				fileData = d->m_requestFileArray;
				return LAPI::EResult::ER_Success;
			}
			else
				return LAPI::EResult::ER_FILE_Upgrade_TransmissionNotOver;

		}

	}
}
