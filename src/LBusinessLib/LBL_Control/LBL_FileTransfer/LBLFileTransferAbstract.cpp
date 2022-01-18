#include "LBLFileTransferAbstract.h"
#include "LBLFileTransferAbstract_p.h"

#include <LBL_CommunicatEngine/LBLClusterProxy>
#include <LBL_CommunicatEngine/LBLSocketLock>

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

        bool LBLFileTransferAbstract::cancelUpgrade(LAPI::EResult ret/* = LAPI::EResult::ER_FILE_Upgrade_ExternalCancel*/)
		{
			Q_D(LBLFileTransferAbstract);
            d->m_upgradeCancel = ret;
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

        quint16 LBLFileTransferAbstract::common_UpgradeFile(bool sync, int msec, quint16 fileType, QString filePath, quint8 portIndex, quint16 moduleIndex)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(filePath)
            Q_UNUSED(portIndex)
            Q_UNUSED(moduleIndex)
			return LAPI::EResult::ER_NotSupportThisCommand;
		}

        quint16 LBLFileTransferAbstract::common_UpgradeFile(bool sync, int msec, quint16 fileType, QByteArray data, quint8 portIndex, quint16 moduleIndex)
		{
            Q_UNUSED(sync)
            Q_UNUSED(msec)
            Q_UNUSED(fileType)
            Q_UNUSED(data)
            Q_UNUSED(portIndex)
            Q_UNUSED(moduleIndex)
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

        quint16 LBLFileTransferAbstract::common_StartSendFile_New(quint16 fileType, quint32 fileLength, QString fileName, QByteArray fileIdentifyContent, quint8 portIndex, quint16 moduleIndex, QUuid exclusiveKey, bool sync, int msec)
        {
            Q_D(LBLFileTransferAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageFileTransfer_CommonStartSendFile_New pack(fileType, fileLength, fileName,fileIdentifyContent,portIndex,moduleIndex);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBLEnginePackage enginePack;
            enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
            enginePack.setData(pack.getDataToSend());
            enginePack.setExClusiveKey(exclusiveKey);

            if (sync) {
                LBLEnginePackage recEnginePack;
                LBLClusterProxy::exclusiveSyncSend(enginePack, recEnginePack, msec);
                return d->m_packageMgr.handle(LBLPackage(recEnginePack.data()));
            }
            else
                return LBLClusterProxy::asyncSend(enginePack) ? LAPI::EResult::ER_INTECTRL_Success : LAPI::EResult::ER_INTECTRL_Fail_NoReason;
        }

        quint16 LBLFileTransferAbstract::common_SendFileData(quint32 fileID, quint16 packIndex, QByteArray packData, QUuid exclusiveKey, bool sync, int msec)
        {
            Q_D(LBLFileTransferAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageFileTransfer_CommonSendFileData pack(fileID, packIndex, packData);
            pack.SetCmdTargetDevice(d->m_targetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBLEnginePackage enginePack;
            enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
            enginePack.setData(pack.getDataToSend());
            enginePack.setExClusiveKey(exclusiveKey);

            if (sync) {
                LBLEnginePackage recEnginePack;
                LBLClusterProxy::exclusiveSyncSend(enginePack, recEnginePack, msec);
                return d->m_packageMgr.handle(LBLPackage(recEnginePack.data()));
            }
            else
                return LBLClusterProxy::asyncSend(enginePack) ? LAPI::EResult::ER_INTECTRL_Success : LAPI::EResult::ER_INTECTRL_Fail_NoReason;
        }

        void LBLFileTransferAbstract::resetCancelUpgrade()
        {
            Q_D(LBLFileTransferAbstract);
            d->m_upgradeCancel = LAPI::EResult::ER_INTECTRL_NULL;
            return;
        }

        void LBLFileTransferAbstract::registerCallBack()
        {
            Q_D(LBLFileTransferAbstract);

            d->m_packageMgr.registerPackage(LBLPackageFileTransfer_CommonStartSendFile_New(),
                std::bind(&LBLFileTransferAbstract::onParseCommon_StartSendFile_New, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageFileTransfer_CommonSendFileData(),
                std::bind(&LBLFileTransferAbstract::onParseCommon_SendFileData, this, std::placeholders::_1));
        }

        quint16 LBLFileTransferAbstract::onParseCommon_StartSendFile_New(const QByteArray &data)
        {
            Q_D(LBLFileTransferAbstract);

            LBLPackageFileTransfer_CommonStartSendFile_New pack(data);
            quint16 ret = pack.getOperationResult();
            if (LBLPackage::EOperationResult::EOR_Success == ret||
                    LBLPackage::EOperationResult::EOR_Success_UpgradeImmediately == ret) {
                d->m_commonAtomicParam.m_startSendFile_ID = pack.getSendFileID();
                d->m_commonAtomicParam.m_startSendFile_SinglePackLength = pack.getMaxLengthOfSinglePackage();
            }
            return ret;
        }

        quint16 LBLFileTransferAbstract::onParseCommon_SendFileData(const QByteArray & data)
        {
            LBLPackageFileTransfer_CommonSendFileData pack(data);
            quint16 ret = pack.getOperationResult();
            return ret;
        }
	}
}
