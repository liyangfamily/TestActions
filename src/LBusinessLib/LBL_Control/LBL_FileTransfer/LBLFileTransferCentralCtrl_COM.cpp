#include "LBLFileTransferCentralCtrl_COM.h"
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

		LBLFileTransferCentralCtrl_COM::LBLFileTransferCentralCtrl_COM(QObject* parent) :
			LBLFileTransferAbstract(parent)
		{
			Q_D(LBLFileTransferAbstract);
            Q_UNUSED(d)
			d->q_ptr = this;
		}


		LBLFileTransferCentralCtrl_COM::LBLFileTransferCentralCtrl_COM(LBLFileTransferAbstractPrivate& dd, QObject* parent) :
			LBLFileTransferAbstract(dd, parent)
		{
			Q_D(LBLFileTransferAbstract);
            Q_UNUSED(d)
			d->q_ptr = this;
		}

		LBLFileTransferCentralCtrl_COM::~LBLFileTransferCentralCtrl_COM()
        {
		}

		quint16 LBLFileTransferCentralCtrl_COM::forMCU_RequestFile(bool sync, int msec, quint16 fileType, QString filePath)
		{
			Q_D(LBLFileTransferAbstract);
			if (!d->m_upgradeFileFuture.isRunning()) {
				d->m_upgradeFileInterface.reset(new QFutureInterface<quint16>(QFutureInterfaceBase::Running));
				d->m_upgradeFileFuture = d->m_upgradeFileInterface->future();
				d->m_upgradeFileInterface->setProgressRange(0, 100);
				d->m_upgradeFileInterface->setProgressValue(0);

				d->m_upgradingSend = false;
				d->m_upgradingFileType = (LBLFileTransferPackage::EFileType)fileType;
				QtConcurrent::run(this, &LBLFileTransferCentralCtrl_COM::forMCU_concurrent_RequestFunction, fileType);
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
					//保存文件
					QFile file(filePath);
					if (!file.open(QIODevice::WriteOnly))
						return LAPI::EResult::ER_FILE_Upgrade_RunTimeFileCreatFail;
					QByteArray requestData;
					getRequestFileData(requestData);
					file.write(requestData);
					file.close();
				}
				return LAPI::EResult::ER_Success;
			}
			else
				return LAPI::EResult::ER_FILE_Upgrade_AlreadyExistUpgrade;
		}

		quint16 LBLFileTransferCentralCtrl_COM::forMCU_RequestFile(bool sync, int msec, quint16 fileType, QByteArray& data)
		{
			Q_D(LBLFileTransferAbstract);
			if (!d->m_upgradeFileFuture.isRunning()) {
				d->m_upgradeFileInterface.reset(new QFutureInterface<quint16>(QFutureInterfaceBase::Running));
				d->m_upgradeFileFuture = d->m_upgradeFileInterface->future();
				d->m_upgradeFileInterface->setProgressRange(0, 100);
				d->m_upgradeFileInterface->setProgressValue(0);

				d->m_upgradingSend = false;
				d->m_upgradingFileType = (LBLFileTransferPackage::EFileType)fileType;
                QtConcurrent::run(this, &LBLFileTransferCentralCtrl_COM::forMCU_concurrent_RequestFunction, fileType);
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
					//保存文件
					return getRequestFileData(data);
				}
				return LAPI::EResult::ER_Success;
			}
			else
				return LAPI::EResult::ER_FILE_Upgrade_AlreadyExistUpgrade;
		}

		quint16 LBLFileTransferCentralCtrl_COM::forMCU_UpgradeFile(bool sync, int msec, quint16 fileType, QString filePath, quint8 portIndex, quint16 moduleIndex)
		{
			Q_D(LBLFileTransferAbstract);
			if (!d->m_upgradeFileFuture.isRunning()) {
				d->m_upgradeFileInterface.reset(new QFutureInterface<quint16>(QFutureInterfaceBase::Running));
				d->m_upgradeFileFuture = d->m_upgradeFileInterface->future();
				d->m_upgradeFileInterface->setProgressRange(0, 100);
				d->m_upgradeFileInterface->setProgressValue(0);

				d->m_upgradingSend = true;
				d->m_upgradingFileType = (LBLFileTransferPackage::EFileType)fileType;
				d->m_upgradingPort = portIndex;
				d->m_upgradingModule = moduleIndex;
				QtConcurrent::run(this, &LBLFileTransferCentralCtrl_COM::forMCU_concurrent_UpgradeFunction, fileType, filePath, \
					portIndex, moduleIndex);
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

		quint16 LBLFileTransferCentralCtrl_COM::forMCU_UpgradeFile(bool sync, int msec, quint16 fileType, QByteArray data, quint8 portIndex, quint16 moduleIndex)
		{
			Q_D(LBLFileTransferAbstract);
			if (!d->m_upgradeFileFuture.isRunning()) {
				d->m_upgradeFileInterface.reset(new QFutureInterface<quint16>(QFutureInterfaceBase::Running));
				d->m_upgradeFileFuture = d->m_upgradeFileInterface->future();
				d->m_upgradeFileInterface->setProgressRange(0, 100);
				d->m_upgradeFileInterface->setProgressValue(0);
//				QString runtimeConnectionFilePath = LBLUIHelper::appRunTimeDataLocation() + "/" + LBLUIHelper::appRunTimeConnectionDataFileName();
//				QFile file(runtimeConnectionFilePath);
//				if (!file.open(QIODevice::WriteOnly))
//					return LAPI::EResult::ER_FILE_Upgrade_RunTimeFileCreatFail;
//				file.write(data);
//				file.close();
				d->m_upgradingSend = true;
				d->m_upgradingFileType = (LBLFileTransferPackage::EFileType)fileType;
				d->m_upgradingPort = portIndex;
				d->m_upgradingModule = moduleIndex;
                QtConcurrent::run(this, &LBLFileTransferCentralCtrl_COM::forMCU_concurrent_UpgradeFunction_D, fileType, data, \
					portIndex, moduleIndex);
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

		int LBLFileTransferCentralCtrl_COM::calculateHandshakeWaitingTime(quint16 fileType)
		{
			int msec = 30 * 1000;
			switch (LBLFileTransferPackage::EFileType(fileType))
			{
			case LBLFileTransferPackage::EFileType::EFT_SenderMonitor:
				break;
			case LBLFileTransferPackage::EFileType::EFT_SenderMCU:
				msec = 5 * 1000;
				break;
			case LBLFileTransferPackage::EFileType::EFT_SenderFPGA:
				msec = 30 * 1000;
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

        quint16 LBLFileTransferCentralCtrl_COM::forMCU_RequestUpgrade(quint16 fileType, quint32 fileLength, quint8 portIndex, quint16 moduleIndex, \
            QUuid exclusiveKey, QByteArray & rePackage, bool sync, int msec)
        {
            Q_D(LBLFileTransferAbstract);
            //在此处组好集控的包，直接调用通信层
            LBLPackageFileTransfer_RequestUpgradeForMCU pack(fileType, fileLength, portIndex, moduleIndex);
            pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
            pack.initByDetectInfo(d->m_parentItemDetectInfo);
            pack.build(0);

            LBLEnginePackage enginePack;
            enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
            enginePack.setData(pack.getDataToSend());
            enginePack.setExClusiveKey(exclusiveKey);

            if (sync) {
                LBLEnginePackage recEnginePack;
                LBLClusterProxy::exclusiveSyncSend(enginePack, recEnginePack, msec);
                rePackage = recEnginePack.data();
                return d->m_packageMgr.handle(LBLPackage(recEnginePack.data()));
            }
            else
                return LBLClusterProxy::asyncSend(enginePack) ? LAPI::EResult::ER_INTECTRL_Success : LAPI::EResult::ER_INTECTRL_Fail_NoReason;
        }

		quint16 LBLFileTransferCentralCtrl_COM::forMCU_SendFileData(quint16 fileType, quint32 packIndex, QByteArray packData, quint8 portIndex, \
			quint16 moduleIndex, QUuid exclusiveKey, QByteArray & rePackage, bool sync, int msec)
		{
			Q_D(LBLFileTransferAbstract);
			//在此处组好集控的包，直接调用通信层
            LBLPackageFileTransfer_SendFileDataForMCU pack(fileType, packIndex, packData, portIndex, moduleIndex);
			pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBLEnginePackage enginePack;
            enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
			enginePack.setData(pack.getDataToSend());
			enginePack.setExClusiveKey(exclusiveKey);

			if (sync) {
				LBLEnginePackage recEnginePack;
				LBLClusterProxy::exclusiveSyncSend(enginePack, recEnginePack, msec);
				rePackage = recEnginePack.data();
				return d->m_packageMgr.handle(LBLPackage(recEnginePack.data()));
			}
			else
				return LBLClusterProxy::asyncSend(enginePack) ? LAPI::EResult::ER_INTECTRL_Success : LAPI::EResult::ER_INTECTRL_Fail_NoReason;
		}

		quint16 LBLFileTransferCentralCtrl_COM::forMCU_SendRequestFile(quint16 fileType, QUuid exclusiveKey, QByteArray & rePackage, bool sync, int msec)
		{
			Q_D(LBLFileTransferAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageFileTransfer_RequestFileForMCU pack(fileType);
			pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBLEnginePackage enginePack;
			enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
			enginePack.setData(pack.getDataToSend());
			enginePack.setExClusiveKey(exclusiveKey);

			if (sync) {
				LBLEnginePackage recEnginePack;
				LBLClusterProxy::exclusiveSyncSend(enginePack, recEnginePack, msec);
				rePackage = recEnginePack.data();
				return d->m_packageMgr.handle(LBLPackage(recEnginePack.data()));
			}
			else
				return LBLClusterProxy::asyncSend(enginePack) ? LAPI::EResult::ER_INTECTRL_Success : LAPI::EResult::ER_INTECTRL_Fail_NoReason;
		}

		quint16 LBLFileTransferCentralCtrl_COM::forMCU_ReceiveFileData(quint16 fileType, quint32 packIndex, QUuid exclusiveKey, QByteArray & rePackage, bool sync, int msec)
		{
			Q_D(LBLFileTransferAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageFileTransfer_ReceiveFileDataForMCU pack(fileType, packIndex);
			pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);

			LBLEnginePackage enginePack;
			enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
			enginePack.setData(pack.getDataToSend());
			enginePack.setExClusiveKey(exclusiveKey);

			if (sync) {
				LBLEnginePackage recEnginePack;
				LBLClusterProxy::exclusiveSyncSend(enginePack, recEnginePack, msec);
				rePackage = recEnginePack.data();
				return d->m_packageMgr.handle(LBLPackage(recEnginePack.data()));
			}
			else
				return LBLClusterProxy::asyncSend(enginePack) ? LAPI::EResult::ER_INTECTRL_Success : LAPI::EResult::ER_INTECTRL_Fail_NoReason;
		}

		quint16 LBLFileTransferCentralCtrl_COM::forMCU_concurrent_RequestFunction(quint16 fileType)
		{
			Q_D(LBLFileTransferAbstract);
			d->m_requestFileArray.clear();

			quint16 ret = 0; 
            int progress = 0;
            resetCancelUpgrade();
			d->m_upgradeFileInterface->reportStarted();
			
			int msec = calculateHandshakeWaitingTime(fileType);

			progress = 9;
			d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Establishing connection...")); //建立连接中

			QUuid exclusiveKey;
			LBLItemExclusiveLock locker(d->m_parentItemDetectInfo->hostName);
			if (locker.autoLock()) {
				exclusiveKey = locker.exclusiveKey();
			}
			else {
				ret = LAPI::EResult::ER_CannotEnterExclusiveMode;
				d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}
			progress = 13;
			d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Establishing connection..."));

			QByteArray rePackage;
			if (LBLPackage::EOperationResult::EOR_Success != forMCU_SendRequestFile(fileType, exclusiveKey, rePackage, true, msec)) {
				ret = LAPI::EResult::ER_FILE_Handshake_Fail;
				d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}
			progress = 17;
			d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Establish connection."));

			LBLPackageFileTransfer_RequestFileForMCU requestUpgradePack(rePackage);
			quint32 fileLength = requestUpgradePack.getTotalFileLength();
			quint16 singlePackLength = requestUpgradePack.getSinglePackageLenth();

			if (0 == singlePackLength) {
				ret = LAPI::EResult::ER_FILE_Upgrade_IllegalSinglePackLength;
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

			//发送数据
			progress = 19;
			d->m_upgradeFileInterface->setProgressValueAndText(19, tr("Start transmit file data."));
			int packageCount = fileLength / singlePackLength;
			if (0 != fileLength % singlePackLength)
				packageCount += 1;
			for (int i = 0; i < packageCount; i++) {
				if (d->m_upgradeCancel) {
                    ret = d->m_upgradeCancel;
					d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
					d->m_upgradeFileInterface->reportFinished(&ret);
					return ret;
				}
				progress = 20 + (75 * i) / packageCount; //更新进度
				d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Transmiting...")); //更新进度
				int tempSendLen = singlePackLength;
				if (i == packageCount - 1) {
					tempSendLen = fileLength - singlePackLength * (packageCount - 1);
				}
				//读取文件
				QByteArray packageData;
				packageData.resize(tempSendLen);
				if (d->m_upgradeCancel) {
                    ret = d->m_upgradeCancel;
					d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
					d->m_upgradeFileInterface->reportFinished(&ret);
					return ret;
				}

				if (LBLFileTransferPackage::ESFS_Success != forMCU_ReceiveFileData(fileType, i, exclusiveKey, rePackage, true, 3000)) {
					ret = LAPI::EResult::ER_FILE_SendFileData_NotResponse;
					d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
					d->m_upgradeFileInterface->reportFinished(&ret);
					return ret;
				}
				LBLPackageFileTransfer_ReceiveFileDataForMCU receiveFileDataPack(rePackage);
				d->m_requestFileArray.append(receiveFileDataPack.getPackageData());
			}

			//d->m_upgradeStatus = LBLFileTransferPackage::EUpgradeStatus::EUS_Waitting;
			//for (int i = 0; i < 5; i++) {
			//	if (d->m_upgradeCancel) {
			//		return LAPI::EResult::ER_FILE_Upgrade_ExternalCancel;
			//	}
			//	d->m_upgradeProgress = 95 + (5 * i) / 5; //更新进度
			//	QThread::msleep(1000);
			//}
			progress = 100;
			ret = LAPI::EResult::ER_FILE_RequestUpgrade_Success; 
			d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Upgrade success."));
			d->m_upgradeFileInterface->reportFinished(&ret);
			return ret;
		}

		quint16 LBLFileTransferCentralCtrl_COM::forMCU_concurrent_UpgradeFunction(quint16 fileType, QString filePath, quint8 portIndex, quint16 moduleIndex)
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
            quint16 fileOffsetPos = 0;
            if(fileType == LBLFileTransferPackage::EFileType::EFT_SenderMCU ||
                    fileType == LBLFileTransferPackage::EFileType::EFT_SenderFPGA){
                if(checker.isValid()){
                    fileOffsetPos = LBLFileTransferChecker::m_fileHeadLength;
                }
            }
            QString fileName = checker.fileInfo().fileName();
            quint64 fileLength = file.size() - fileOffsetPos;
            QByteArray fileIdentifyContent = checker.hardwarHead();

			int msec = calculateHandshakeWaitingTime(fileType);

			progress = 9;
			d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Establishing connection...")); //建立连接中

			QUuid exclusiveKey;
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
            QByteArray rePackage;
            quint16 handshakeRet=0;
            if(checker.isValid()){
                handshakeRet = common_StartSendFile_New(fileType, fileLength,filePath,fileIdentifyContent, portIndex, moduleIndex, \
                                                        exclusiveKey,true, msec);
            }
            else{
                handshakeRet = forMCU_RequestUpgrade(fileType, fileLength, portIndex, moduleIndex, exclusiveKey, \
                                                     rePackage, true, msec);
            }

            if(LBLPackage::EOperationResult::EOR_Success != handshakeRet
                    && LBLPackage::EOperationResult::EOR_Success_UpgradeImmediately != handshakeRet){
                file.close();
                ret = LAPI::EResult::ER_FILE_Handshake_Fail;
                d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
                d->m_upgradeFileInterface->reportFinished(&ret);
                return ret;
            }

			progress = 13;
            d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Establish connection.")); //建立连接

            //获取文件传输识别码和单包长度
            quint32 fileID=0;
            quint16 singlePackLength=0;
            if(checker.isValid()){
                fileID= d->m_commonAtomicParam.m_startSendFile_ID;
                singlePackLength= d->m_commonAtomicParam.m_startSendFile_SinglePackLength;
            }
            else{
                LBLPackageFileTransfer_RequestUpgradeForMCU requestUpgradePack(rePackage);
                singlePackLength = requestUpgradePack.getMaxLengthOfSinglePackage();
            }

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
			progress = 17;
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
				progress = 19 + (75 * i) / packageCount;
				d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Transmiting...")); //更新进度
				int tempSendLen = singlePackLength;
				if (i == packageCount - 1) {
					tempSendLen = fileLength - singlePackLength * (packageCount - 1);
				}
				//读取文件
				QByteArray packageData;
				packageData.resize(tempSendLen);
                file.seek(i * singlePackLength + fileOffsetPos);
				qint64 readLen = file.read(packageData.data(), tempSendLen);
				Q_UNUSED(readLen);
				if (d->m_upgradeCancel) {
					file.close();
                    ret = d->m_upgradeCancel;
					d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
					d->m_upgradeFileInterface->reportFinished(&ret);
					return ret;
				}
                quint16 sendDataRet=0;
                if(checker.isValid()){
                    sendDataRet = common_SendFileData(fileID, i, packageData, exclusiveKey, true, 1500);
                }
                else{
                    sendDataRet = forMCU_SendFileData(fileType, i, packageData, portIndex, moduleIndex, \
                                                      exclusiveKey, rePackage, true, 3000);
                }
                if (LBLFileTransferPackage::ESFS_Success != sendDataRet) {
					file.close();
					ret = LAPI::EResult::ER_FILE_SendFileData_NotResponse;
					d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
					d->m_upgradeFileInterface->reportFinished(&ret);
					return ret;
				}
			}
			file.close();

			if (fileType == LBLFileTransferPackage::EFileType::EFT_ConnectionFile) {
				progress = 100;
				ret = LAPI::EResult::ER_FILE_UpgradeStatus_Success;
				d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Upgrade success."));
				d->m_upgradeFileInterface->reportFinished(&ret);
				return ret;
			}

			for (int i = 0; i < 5; i++) {
				if (d->m_upgradeCancel) {
					file.close();
                    ret = d->m_upgradeCancel;
					d->m_upgradeFileInterface->setProgressValueAndText(++progress, tr("Upgrade failed, Err Code: 0x%1").arg(QString::number(ret, 16).toUpper()));
					d->m_upgradeFileInterface->reportFinished(&ret);
					return ret;
				}
				progress = 95 + (4 * i) / 5;
				d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Waitting...")); //更新进度
				QThread::msleep(1000);
			}
			progress = 100;
			ret = LAPI::EResult::ER_FILE_UpgradeStatus_Success;
			d->m_upgradeFileInterface->setProgressValueAndText(progress, tr("Upgrade success."));
			d->m_upgradeFileInterface->reportFinished(&ret);
            return ret;
        }

        quint16 LBLFileTransferCentralCtrl_COM::forMCU_concurrent_UpgradeFunction_D(quint16 fileType, const QByteArray &fileData, quint8 portIndex, quint16 moduleIndex)
        {
            quint16 ret=LAPI::EResult::ER_Fail;
            QString strFileName = LBLUIHelper::appRunTimeDataLocation() + "/" +
                        QCoreApplication::applicationName() + "_XXXXXX." + "bin";
            QTemporaryFile tmpFile(strFileName);
            if(tmpFile.open()){
                tmpFile.write(fileData);
                tmpFile.flush();
                tmpFile.close();
                ret=forMCU_concurrent_UpgradeFunction(fileType,tmpFile.fileName(),portIndex,moduleIndex);
            }
            return ret;
        }

		bool LBLFileTransferCentralCtrl_COM::init()
		{
			registerCallBack();
			return true;
		}

		void LBLFileTransferCentralCtrl_COM::registerCallBack()
		{
			Q_D(LBLFileTransferAbstract);

            LBLFileTransferAbstract::registerCallBack();

            d->m_packageMgr.registerPackage(LBLPackageFileTransfer_RequestUpgradeForMCU(),
                std::bind(&LBLFileTransferCentralCtrl_COM::onParseForMCU_RequestUpgrade, this, std::placeholders::_1));
            d->m_packageMgr.registerPackage(LBLPackageFileTransfer_SendFileDataForMCU(),
                std::bind(&LBLFileTransferCentralCtrl_COM::onParseForMCU_SendFileData, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageFileTransfer_RequestFileForMCU(),
				std::bind(&LBLFileTransferCentralCtrl_COM::onParseForMCU_RequestFile, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageFileTransfer_ReceiveFileDataForMCU(),
				std::bind(&LBLFileTransferCentralCtrl_COM::onParseForMCU_ReceiveFileData, this, std::placeholders::_1));
        }

        quint16 LBLFileTransferCentralCtrl_COM::onParseForMCU_RequestUpgrade(const QByteArray & data)
        {
            LBLPackageFileTransfer_RequestUpgradeForMCU pack(data);
            quint16 ret = pack.getOperationResult();
            if (LBLPackage::EOperationResult::EOR_Success == ret) {
            }
            return ret;
        }

        quint16 LBLFileTransferCentralCtrl_COM::onParseForMCU_SendFileData(const QByteArray & data)
        {
            LBLPackageFileTransfer_SendFileDataForMCU pack(data);
			quint16 ret = pack.getOperationResult();
			if (LBLPackage::EOperationResult::EOR_Success == ret) {
			}
			return ret;
		}

		quint16 LBLFileTransferCentralCtrl_COM::onParseForMCU_RequestFile(const QByteArray & data)
        {
			LBLPackageFileTransfer_RequestFileForMCU pack(data);
			quint16 ret = pack.getOperationResult();
			if (LBLPackage::EOperationResult::EOR_Success == ret) {
			}
			return ret;
		}

		quint16 LBLFileTransferCentralCtrl_COM::onParseForMCU_ReceiveFileData(const QByteArray & data)
        {
			LBLPackageFileTransfer_ReceiveFileDataForMCU pack(data);
			quint16 ret = pack.getOperationResult();
			if (LBLPackage::EOperationResult::EOR_Success == ret) {
			}
            return ret;
        }


	}
}
