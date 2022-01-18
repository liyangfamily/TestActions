#include "LBLFileTransferCentralCtrl.h"
#include "LBLFileTransferAbstract_p.h"
#include <LBL_CommunicatEngine/LBLClusterProxy>
#include <LBL_CommunicatEngine/LBLSocketLock>

#include <QFile>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QTime>
#include <LBL_Core/LAPIDef>
#include <LBL_Core/LBLUIHelper>
#include "LBL_Core/LBLFileTransferChecker.h"
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
		}

        quint16 LBLFileTransferCentralCtrl::common_UpgradeFile(bool sync, int msec, quint16 fileType, QString filePath, quint8 portIndex, quint16 moduleIndex)
		{
			Q_D(LBLFileTransferAbstract);
			if (!d->m_upgradeFileFuture.isRunning()) {
				d->m_upgradeFileInterface.reset(new QFutureInterface<quint16>(QFutureInterfaceBase::Running));
				d->m_upgradeFileFuture = d->m_upgradeFileInterface->future();
				d->m_upgradeFileInterface->setProgressRange(0, 100);
				d->m_upgradeFileInterface->setProgressValue(0);

				d->m_upgradingSend = true;
				d->m_upgradingFileType = (LBLFileTransferPackage::EFileType)fileType;
                QtConcurrent::run(this, &LBLFileTransferCentralCtrl::common_concurrent_UpgradeFunction, fileType, filePath,portIndex,moduleIndex);
				if (sync) {
                    QEventLoop loop;
                    QTimer outTimer;
                    QTimer queryTimer;
                    outTimer.setSingleShot(true);
                    connect(&outTimer, &QTimer::timeout, [&]() {
                            loop.exit(-1) ;
                    });
                    connect(&queryTimer, &QTimer::timeout, [&]() {
                        if (this->isUpgradeFinished())
                            loop.exit(0) ;
                    });
                    outTimer.start(msec); // 超时
                    queryTimer.start(500); //查询间隔
                    int ret=loop.exec();
                    outTimer.stop();
                    queryTimer.stop();
                    if(ret==-1){
                        this->cancelUpgrade(LAPI::EResult::ER_SyncSendTimeOut);
                        return LAPI::EResult::ER_SyncSendTimeOut;
                    }
				}
				return LAPI::EResult::ER_Success;
			}
			else
                return LAPI::EResult::ER_FILE_Upgrade_AlreadyExistUpgrade;
        }

        quint16 LBLFileTransferCentralCtrl::common_UpgradeFile(bool sync, int msec, quint16 fileType, QByteArray data, quint8 portIndex, quint16 moduleIndex)
		{
			Q_D(LBLFileTransferAbstract);
			if (!d->m_upgradeFileFuture.isRunning()) {
				d->m_upgradeFileInterface.reset(new QFutureInterface<quint16>(QFutureInterfaceBase::Running));
				d->m_upgradeFileFuture = d->m_upgradeFileInterface->future();
				d->m_upgradeFileInterface->setProgressRange(0, 100);
				d->m_upgradeFileInterface->setProgressValue(0);
				d->m_upgradingSend = true;
				d->m_upgradingFileType = (LBLFileTransferPackage::EFileType)fileType;
                QtConcurrent::run(this, &LBLFileTransferCentralCtrl::common_concurrent_UpgradeFunction_D, fileType, data,portIndex,moduleIndex);
				if (sync) {
					QEventLoop loop;
					QTimer outTimer;
					QTimer queryTimer;
					outTimer.setSingleShot(true);
                    connect(&outTimer, &QTimer::timeout, [&]() {
                            loop.exit(-1) ;
                    });
                    connect(&queryTimer, &QTimer::timeout, [&]() {
                        if (this->isUpgradeFinished())
                            loop.exit(0) ;
                    });
					outTimer.start(msec); // 超时
					queryTimer.start(500); //查询间隔
                    int ret=loop.exec();
					outTimer.stop();
					queryTimer.stop();
                    if(ret==-1){
                        this->cancelUpgrade(LAPI::EResult::ER_SyncSendTimeOut);
                        return LAPI::EResult::ER_SyncSendTimeOut;
                    }
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
                msec=1000;
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

        quint16 LBLFileTransferCentralCtrl::common_RequestUpgrade_New(quint16 fileType, QUuid exclusiveKey, bool sync, int msec, quint8 portIndex, quint16 moduleIndex)
        {
            Q_D(LBLFileTransferAbstract);
            LBLPackageFileTransfer_CommonRequestUpgrade_New pack(fileType,portIndex,moduleIndex);
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

        quint16 LBLFileTransferCentralCtrl::common_concurrent_UpgradeFunction(quint16 fileType, QString filePath, quint8 portIndex, quint16 moduleIndex)
		{
			Q_D(LBLFileTransferAbstract);

			quint16 ret = 0;
            int progress = 0;
            resetCancelUpgrade();
			d->m_upgradeFileInterface->reportStarted();

			if (filePath.isEmpty()) {
				ret = LAPI::EResult::ER_FILE_Upgrade_FileNameEmpty;
				d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}

            //文件校验
            LBLFileTransferChecker checker(filePath);
            bool bRet=checker.check(); //会自动关闭文件
            if(bRet){
                quint16 calculateFileType = checker.fileType();
                if(calculateFileType!=0&& calculateFileType!=fileType){
                    ret = LAPI::EResult::ER_FILE_Upgrade_FileCheckFail;
                    d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
                    d->m_upgradeFileInterface->reportFinished(&ret);
                    return ret;
                }
            }
            else{
                ret = LAPI::EResult::ER_FILE_Upgrade_FileCheckFail;
                d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
                d->m_upgradeFileInterface->reportFinished(&ret);
                return ret;
            }

            //打开文件
            QFile file(filePath);
			if (!file.open(QIODevice::ReadOnly)) {
				ret = LAPI::EResult::ER_FILE_Upgrade_FileOpenFail;
				d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}
            QString fileName = checker.fileInfo().fileName();
			quint64 fileLength = file.size();
            QByteArray fileIdentifyContent = checker.hardwarHead();

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

            //握手
            quint16 handshakeRet=0;
//            if(checker.isValid()){
//                handshakeRet = common_StartSendFile_New(fileType, fileLength,filePath,fileIdentifyContent,portIndex,moduleIndex,\
//                                                        exclusiveKey, true, msec);
//            }
//            else{
                handshakeRet = common_StartSendFile(fileType, fileLength, fileName, exclusiveKey, true, msec);
            //}

            if(LBLPackage::EOperationResult::EOR_Success != handshakeRet){
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
                ret = d->m_upgradeCancel;
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
                    ret = d->m_upgradeCancel;
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
                        ret = d->m_upgradeCancel;
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
            quint16 requestRet=0;
            if(checker.isValid()){
                requestRet = common_RequestUpgrade_New(fileType, exclusiveKey, true, 1000,portIndex,moduleIndex);
            }
            else{
                requestRet = common_RequestUpgrade(fileType, exclusiveKey, true, 1000);
            }
            if(LBLPackage::EOperationResult::EOR_Success != requestRet){
                ret = LAPI::EResult::ER_FILE_Upgrade_RequestUpgradeFail;
                d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
                d->m_upgradeFileInterface->reportFinished(&ret);
                return ret;
            }

			if (d->m_upgradeCancel) {
                ret = d->m_upgradeCancel;
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
                    ret = d->m_upgradeCancel;
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

        quint16 LBLFileTransferCentralCtrl::common_concurrent_UpgradeFunction_D(quint16 fileType, const QByteArray &fileData, quint8 portIndex, quint16 moduleIndex)
        {
            quint16 ret=LAPI::EResult::ER_Fail;
            QString strFileName = LBLUIHelper::appRunTimeDataLocation() + "/" +
                        QCoreApplication::applicationName() + "_XXXXXX." + "bin";
            QTemporaryFile tmpFile(strFileName);
            if(tmpFile.open()){
                tmpFile.write(fileData);
                tmpFile.flush();
                tmpFile.close();
                ret=common_concurrent_UpgradeFunction(fileType,tmpFile.fileName(),portIndex,moduleIndex);
            }
            return ret;
        }
	
		bool LBLFileTransferCentralCtrl::init()
		{
			registerCallBack();
			return true;
		}

		void LBLFileTransferCentralCtrl::registerCallBack()
		{
			Q_D(LBLFileTransferAbstract);

            LBLFileTransferAbstract::registerCallBack();

			d->m_packageMgr.registerPackage(LBLPackageFileTransfer_CommonStartSendFile(),
                std::bind(&LBLFileTransferCentralCtrl::onParseCommon_StartSendFile, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageFileTransfer_CommonRequestUpgrade(),
				std::bind(&LBLFileTransferCentralCtrl::onParseCommon_RequestUpgrade, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageFileTransfer_CommonRequestUpgrade_New(),
                std::bind(&LBLFileTransferCentralCtrl::onParseCommon_RequestUpgrade_New, this, std::placeholders::_1));
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

        quint16 LBLFileTransferCentralCtrl::onParseCommon_RequestUpgrade_New(const QByteArray &data)
        {
            Q_D(LBLFileTransferAbstract);

            LBLPackageFileTransfer_CommonRequestUpgrade_New pack(data);
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
