#include "LBLFileTransferCentralCtrl.h"
#include "LBLFileTransferAbstract_p.h"
#include <LBL_CommunicatEngine/LBLClusterProxy>
#include <LBL_CommunicatEngine/LBLSocketLock>

#include <QFile>
#include <QFileInfo>
#include <QTime>
#include <LBL_Core/LAPIDef>
#include <LBL_Core/LBLUIHelper>
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_Cored.lib")
#else
#pragma comment(lib,"LBL_Core.lib")
#endif
#endif

#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif

#include <QTimer>
#include <QEventLoop>
#include <QCoreApplication>

namespace LBL
{
	namespace FileTransfer
	{

		LBLFileTransferCentralCtrl::LBLFileTransferCentralCtrl(QObject* parent) :
			LBLFileTransferAbstract(parent)
		{
			Q_D(LBLFileTransferAbstract);
            Q_UNUSED(d)
			d->q_ptr = this;
		}


		LBLFileTransferCentralCtrl::LBLFileTransferCentralCtrl(LBLFileTransferAbstractPrivate& dd, QObject* parent) :
			LBLFileTransferAbstract(dd, parent)
		{
			Q_D(LBLFileTransferAbstract);
            Q_UNUSED(d)
			d->q_ptr = this;
		}

		LBLFileTransferCentralCtrl::~LBLFileTransferCentralCtrl()
		{
			qDebug() << __FUNCTION__;
		}

		quint16 LBLFileTransferCentralCtrl::common_UpgradeFile(bool sync, int msec, quint16 fileType, QString filePath)
		{
			Q_D(LBLFileTransferAbstract);
			if (!d->m_upgradeFileFuture.isRunning()) {
				d->m_upgradeFileInterface.reset(new QFutureInterface<quint16>(QFutureInterfaceBase::Running));
				d->m_upgradeFileFuture = d->m_upgradeFileInterface->future();
				d->m_upgradeFileInterface->setProgressRange(0, 100);
				d->m_upgradeFileInterface->setProgressValue(0);

				d->m_upgradingSend = true;
				d->m_upgradingFileType = (LBLFileTransferPackage::EFileType)fileType;
				QtConcurrent::run(this, &LBLFileTransferCentralCtrl::common_concurrent_UpgradeFunction, fileType, filePath);
				if (sync) {
					QEventLoop loop;
					QTimer outTimer;
					QTimer queryTimer;
					outTimer.setSingleShot(true);
					connect(&outTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
					connect(&queryTimer, &QTimer::timeout, [&]() {
						if (this->isUpgradeFinished())
							loop.quit();
					});
					outTimer.start(msec); // 超时
					queryTimer.start(500); //查询间隔
					loop.exec();
					outTimer.stop();
					queryTimer.stop();
				}
				return LAPI::EResult::ER_Success;
			}
			else
				return LAPI::EResult::ER_FILE_Upgrade_AlreadyExistUpgrade;
		}

		quint16 LBLFileTransferCentralCtrl::common_UpgradeFile(bool sync, int msec, quint16 fileType, QByteArray data)
		{
			Q_D(LBLFileTransferAbstract);
			if (!d->m_upgradeFileFuture.isRunning()) {
				d->m_upgradeFileInterface.reset(new QFutureInterface<quint16>(QFutureInterfaceBase::Running));
				d->m_upgradeFileFuture = d->m_upgradeFileInterface->future();
				d->m_upgradeFileInterface->setProgressRange(0, 100);
				d->m_upgradeFileInterface->setProgressValue(0);

				QString runtimeConnectionFilePath = LBLUIHelper::appRunTimeDataLocation() + "/" + LBLUIHelper::appRunTimeConnectionDataFileName();
				QFile file(runtimeConnectionFilePath);
				if (!file.open(QIODevice::WriteOnly))
					return LAPI::EResult::ER_FILE_Upgrade_RunTimeFileCreatFail;
				file.write(data);
				file.close();
				d->m_upgradingSend = true;
				d->m_upgradingFileType = (LBLFileTransferPackage::EFileType)fileType;
				QtConcurrent::run(this, &LBLFileTransferCentralCtrl::common_concurrent_UpgradeFunction, fileType, runtimeConnectionFilePath);
				if (sync) {
					QEventLoop loop;
					QTimer outTimer;
					QTimer queryTimer;
					outTimer.setSingleShot(true);
					connect(&outTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
					connect(&queryTimer, &QTimer::timeout, [&]() {
						if (this->isUpgradeFinished())
							loop.quit();
					});
					outTimer.start(msec); // 超时
					queryTimer.start(500); //查询间隔
					loop.exec();
					outTimer.stop();
					queryTimer.stop();
				}
				return LAPI::EResult::ER_Success;
			}
			else
				return LAPI::EResult::ER_FILE_Upgrade_AlreadyExistUpgrade;
		}

		/*********************************************************************************************************
		**标准文件传输                                                                     
        *********************************************************************************************************/

		int LBLFileTransferCentralCtrl::calculateHandshakeWaitingTime(quint16 fileType)
		{
			int msec = 5 * 1000;
			switch (LBLFileTransferPackage::EFileType(fileType))
			{
			case LBLFileTransferPackage::EFileType::EFT_SenderMonitor:
				break;
			case LBLFileTransferPackage::EFileType::EFT_SenderMCU:
				break;
			case LBLFileTransferPackage::EFileType::EFT_SenderFPGA:
				msec = 15 * 1000;
				break;
			case LBLFileTransferPackage::EFileType::EFT_SenderParam:
				break;
			case LBLFileTransferPackage::EFileType::EFT_ReciverMCU:
				break;
			case LBLFileTransferPackage::EFileType::EFT_ReciverFPGA:
				break;
			case LBLFileTransferPackage::EFileType::EFT_ReciverParam:
				break;
			case LBLFileTransferPackage::EFileType::EFT_ConnectionFile:
				break;
			case LBLFileTransferPackage::EFileType::EFT_GammaFile:
				break;
			case LBLFileTransferPackage::EFileType::EFT_GammaFile_512B:
				break;
			default:
				msec = 5 * 1000;
				break;
			}
			return msec;
		}

		quint16 LBLFileTransferCentralCtrl::common_StartSendFile(quint16 fileType,quint32 fileLength, QString fileName, QUuid exclusiveKey, bool sync, int msec)
		{
			Q_D(LBLFileTransferAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageFileTransfer_CommonStartSendFile pack(fileType, fileLength, fileName);
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

		quint16 LBLFileTransferCentralCtrl::common_SendFileData(quint32 fileID, quint16 packIndex, QByteArray packData, QUuid exclusiveKey, bool sync, int msec)
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

		quint16 LBLFileTransferCentralCtrl::common_RequestUpgrade(quint16 fileType, QUuid exclusiveKey, bool sync, int msec)
		{
			Q_D(LBLFileTransferAbstract);
			LBLPackageFileTransfer_CommonRequestUpgrade pack(fileType);
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

		quint16 LBLFileTransferCentralCtrl::common_QueryUpgradeStatus(quint16 fileType, QUuid exclusiveKey, bool sync, int msec)
		{
			Q_D(LBLFileTransferAbstract);
			LBLPackageFileTransfer_CommonQueryUpgradeStatus pack(fileType);
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

		quint16 LBLFileTransferCentralCtrl::common_concurrent_UpgradeFunction(quint16 fileType, QString filePath)
		{
			Q_D(LBLFileTransferAbstract);

			quint16 ret = 0;
			int progress = 0;
			d->m_upgradeCancel = false;
			d->m_upgradeFileInterface->reportStarted();

			if (filePath.isEmpty()) {
				ret = LAPI::EResult::ER_FILE_Upgrade_FileNameEmpty;
				d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}

			QFile file(filePath);
			QFileInfo info(file);
			if (!file.open(QIODevice::ReadOnly)) {
				ret = LAPI::EResult::ER_FILE_Upgrade_FileOpenFail;
				d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}
			QString fileName = info.fileName();
			quint64 fileLength = file.size();

			int msec = calculateHandshakeWaitingTime(fileType);

			progress = 7;
			d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Establishing connection...")); //建立连接中

			QUuid exclusiveKey;
			//LBLSocketExclusiveLock locker(d->m_parentItemDetectInfo->socketObj);
			//if (locker.autoLock(5000)) {
			LBLItemExclusiveLock locker(d->m_parentItemDetectInfo->hostName);
			if (locker.autoLock()) {
				exclusiveKey = locker.exclusiveKey();
			}
			else {
				file.close();
				ret = LAPI::EResult::ER_CannotEnterExclusiveMode;
				d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}

			if (LBLPackage::EOperationResult::EOR_Success != common_StartSendFile(fileType, fileLength, fileName, exclusiveKey, true, msec)) {
				file.close();
				ret = LAPI::EResult::ER_FILE_Handshake_Fail;
				d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}

			progress = 8;
			d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Establish connection.")); //建立连接

			quint32 fileID = d->m_commonAtomicParam.m_startSendFile_ID;
			quint16 singlePackLength = d->m_commonAtomicParam.m_startSendFile_SinglePackLength;

			if (0 == singlePackLength) {
                file.close();
				ret = LAPI::EResult::ER_FILE_Upgrade_IllegalSinglePackLength;
				d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}
			if (d->m_upgradeCancel) {
                file.close();
				ret = LAPI::EResult::ER_FILE_Upgrade_ExternalCancel;
				d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}

			//发送数据
			progress = 9;
			d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Start transmit file data."));
			int packageCount = fileLength / singlePackLength;
			if (0 != fileLength % singlePackLength)
				packageCount += 1;
			for (int i = 0; i < packageCount; i++) {
				if (d->m_upgradeCancel) {
					file.close(); 
					ret = LAPI::EResult::ER_FILE_Upgrade_ExternalCancel;
					d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
					d->m_upgradeFileInterface->reportFinished(&ret);
					return ret;
				}
				d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Transmiting...")); //更新进度
				progress = 10 + (50 * i) / packageCount; //更新进度
				int tempSendLen = singlePackLength;
				if (i == packageCount - 1) {
					tempSendLen = fileLength - singlePackLength * (packageCount - 1);
				}
				//读取文件
				QByteArray packageData;
				packageData.resize(tempSendLen);
				file.seek(i * singlePackLength);
                qint64 readLen = file.read(packageData.data(), tempSendLen);
                Q_UNUSED(readLen)
				for (int j = 0; j < 3; ++j)  {//重传2次
					if (d->m_upgradeCancel) {
						file.close();
						ret = LAPI::EResult::ER_FILE_Upgrade_ExternalCancel;
						d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
						d->m_upgradeFileInterface->reportFinished(&ret);
						return ret;
					}

					if (LBLFileTransferPackage::ESFS_Success == common_SendFileData(fileID, i, packageData, exclusiveKey, true, 1500))
						break;

					d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Retrying now: %1").arg(j + 1));

					if (j == 2) {
						file.close();
						ret = LAPI::EResult::ER_FILE_SendFileData_TooManyFailedRetransmissions;
						d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
						d->m_upgradeFileInterface->reportFinished(&ret);
						return ret;
					}
				}
			}
			file.close();

			//请求升级
			if (LBLPackage::EOperationResult::EOR_Success != common_RequestUpgrade(fileType, exclusiveKey, true, 1500)) {
				ret = LAPI::EResult::ER_FILE_Upgrade_RequestUpgradeFail;
				d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}

			if (d->m_upgradeCancel) {
				ret = LAPI::EResult::ER_FILE_Upgrade_ExternalCancel;
				d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}

			if (fileType == LBLFileTransferPackage::EFileType::EFT_ConnectionFile) {
				progress = 100;
				ret = LAPI::EResult::ER_FILE_UpgradeStatus_Success;
				d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Upgrade success."));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}

			//查询状态
			QTime time;
			time.start();
			int timeoutmm = 30 * 1000;
			int queryUpgradeFaildCount = 0;
			while (true) {
				if (d->m_upgradeCancel) {
					ret = LAPI::EResult::ER_FILE_Upgrade_ExternalCancel;
					d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
					d->m_upgradeFileInterface->reportFinished(&ret);
					return ret;
				}
				if (time.elapsed() > timeoutmm) {
					ret = LAPI::EResult::ER_FILE_UpgradeStatus_Fail;
					d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
					d->m_upgradeFileInterface->reportFinished(&ret);
					return ret;
				}

				if (LBLPackage::EOperationResult::EOR_Success == common_QueryUpgradeStatus(fileType, exclusiveKey, true, 1500)) {
					if (progress > 0) {
						time.restart();
						//progress = (65 + (30 * d->m_commonAtomicParam.m_queryStatus_OperatProgress) / 100);
						switch (d->m_commonAtomicParam.m_queryStatus_OperatSteps)
						{
						case LBLFileTransferPackage::EUS_NULL:
							break;
						case LBLFileTransferPackage::EUS_Erase:
						{
							progress = (61 + (7 * d->m_commonAtomicParam.m_queryStatus_OperatProgress) / 100);
							d->m_stepName = tr("Erasing...");
						}
							break;
						case LBLFileTransferPackage::EUS_Upgaradeing:
						{
							progress = (69 + (22 * d->m_commonAtomicParam.m_queryStatus_OperatProgress) / 100);
							d->m_stepName = tr("Upgrading...");
						}
							break;
						case LBLFileTransferPackage::EUS_Rebooting:
						{
							progress = progress < 100 ? ++progress : progress;
							d->m_stepName = tr("Restarting...");
						}
							break;
						case LBLFileTransferPackage::EUS_Waitting:
						{
							progress = progress < 100 ? ++progress : progress;
							d->m_stepName = tr("Waiting...");
						}
							break;
						default:
							break;
						}
						d->m_upgradeFileInterface->setProgressValueAndText(progress, d->m_stepName);
					}
					int steps = d->m_commonAtomicParam.m_queryStatus_OperatSteps;
					if (steps == LBLFileTransferPackage::EUS_UpgaradeSucess) {
						break;
					}
					if (steps == LBLFileTransferPackage::EUS_UpgaradeFaild) {
						ret = LAPI::EResult::ER_FILE_UpgradeStatus_Fail;
						d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
						d->m_upgradeFileInterface->reportFinished(&ret);
						return  ret;
					}
				}
				else {
					++queryUpgradeFaildCount;
					if (queryUpgradeFaildCount > 10) {
						ret = LAPI::EResult::ER_FILE_UpgradeStatus_StatusNotReplied;
						d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
						d->m_upgradeFileInterface->reportFinished(&ret);
						return  ret;
					}
				}
				QThread::msleep(2000);
			}
			progress = 100;
			ret = LAPI::EResult::ER_FILE_UpgradeStatus_Success;
			d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Upgrade success."));
			d->m_upgradeFileInterface->reportFinished(&ret);
			return  ret;
		}
	
		bool LBLFileTransferCentralCtrl::init()
		{
			registerCallBack();
			return true;
		}

		void LBLFileTransferCentralCtrl::registerCallBack()
		{
			Q_D(LBLFileTransferAbstract);

			d->m_packageMgr.registerPackage(LBLPackageFileTransfer_CommonStartSendFile(),
				std::bind(&LBLFileTransferCentralCtrl::onParseCommon_StartSendFile, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageFileTransfer_CommonSendFileData(),
				std::bind(&LBLFileTransferCentralCtrl::onParseCommon_SendFileData, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageFileTransfer_CommonRequestUpgrade(),
				std::bind(&LBLFileTransferCentralCtrl::onParseCommon_RequestUpgrade, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageFileTransfer_CommonQueryUpgradeStatus(),
				std::bind(&LBLFileTransferCentralCtrl::onParseCommon_QueryUpgradeStatus, this, std::placeholders::_1));
		}
		quint16 LBLFileTransferCentralCtrl::onParseCommon_StartSendFile(const QByteArray & data)
		{
			Q_D(LBLFileTransferAbstract);

			LBLPackageFileTransfer_CommonStartSendFile pack(data);
			quint16 ret = pack.getOperationResult();
			if (LBLPackage::EOperationResult::EOR_Success == ret) {
				d->m_commonAtomicParam.m_startSendFile_ID = pack.getSendFileID();
				d->m_commonAtomicParam.m_startSendFile_SinglePackLength = pack.getMaxLengthOfSinglePackage();
			}
			return ret;
		}
		quint16 LBLFileTransferCentralCtrl::onParseCommon_SendFileData(const QByteArray & data)
        {
			LBLPackageFileTransfer_CommonSendFileData pack(data);
			quint16 ret = pack.getOperationResult();
			return ret;
		}
		quint16 LBLFileTransferCentralCtrl::onParseCommon_RequestUpgrade(const QByteArray & data)
		{
			Q_D(LBLFileTransferAbstract);

			LBLPackageFileTransfer_CommonRequestUpgrade pack(data);
			quint16 ret = pack.getOperationResult();
			if (LBLPackage::EOperationResult::EOR_Success != ret) {
				d->m_commonAtomicParam.m_requestUpgrade_FailReason = pack.getOperatFailReason();
				return pack.getOperatFailReason() == 0x01 ? LAPI::EResult::ER_FILE_RequestUpgrade_FileNotExist : LAPI::EResult::ER_FILE_RequestUpgrade_FileDamage;
			}
			return ret;
		}
		quint16 LBLFileTransferCentralCtrl::onParseCommon_QueryUpgradeStatus(const QByteArray & data)
		{
			Q_D(LBLFileTransferAbstract);

			LBLPackageFileTransfer_CommonQueryUpgradeStatus pack(data);
			quint16 ret = pack.getOperationResult();
			if (LBLPackage::EOperationResult::EOR_Success == ret) {
				d->m_commonAtomicParam.m_queryStatus_OperatSteps = pack.getOperatSteps();
				d->m_commonAtomicParam.m_queryStatus_OperatProgress = pack.getOperatProgress();
			}
			return ret;
		}
	}
}
