/****************************************************************************
**
** This Interface file is part of the FileTransfer module of the LBL.
** 这个是LBL中的FileTransfer控制抽象类，该模块不对外开放
**
** 该接口文件包含LED系统中FileTransfer相关操作,与通信层联系
**
****************************************************************************/
#ifndef CVTE_H_LBLFILETRANSFERABSTRACT
#define CVTE_H_LBLFILETRANSFERABSTRACT
#pragma once

#include "LBLFiletransferGlobal.h"
#include <QObject>
#include <QScopedPointer>
#include <LBL_CommunicatEngine/LBLFileTransferPackage>
#include <LBL_Core/LAPIDef>
#include <QFuture>
#include <QFutureInterface>
#include <QFutureWatcher>
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_CommunicatEngined.lib")
#else
#pragma comment(lib,"LBL_CommunicatEngine.lib")
#endif // QT_DEBUG
#endif

namespace LBL
{
	namespace FileTransfer
	{
		class LBLFileTransferAbstractPrivate;
		class LBL_FILETRANSFER_EXPORT LBLFileTransferAbstract :public QObject
		{
			Q_DECLARE_PRIVATE(LBLFileTransferAbstract)
		public:
			virtual ~LBLFileTransferAbstract();

			bool setDetectInfoStruct(SDetectItemInfo *detectInfo);
			virtual bool init() = 0;
			//由发送卡分发数据包
			virtual bool parsingDataFrame(const LBLPackage& pack);

			virtual bool isUpgradeSend();
			virtual quint16 upgradingFileType();
			virtual quint8 upgradingPortIndex();
			virtual quint16 upgradingModuleIndex();

			virtual bool isUpgradeStarted();
			virtual bool isUpgrading();
			virtual bool isUpgradeFinished();
            virtual bool cancelUpgrade(LAPI::EResult ret = LAPI::EResult::ER_FILE_Upgrade_ExternalCancel);
			virtual quint16 upgradeResult();
			virtual QFuture<quint16> upgradeFuture();

			/*********************************************************************************************************
			**与Android的文件传输                                                                     
            *********************************************************************************************************/
			//virtual quint16 common_RequestFile(quint16 fileType);
            virtual quint16 common_UpgradeFile(bool sync, int msec, quint16 fileType, QString filePath, quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF);
            virtual quint16 common_UpgradeFile(bool sync, int msec, quint16 fileType, QByteArray data, quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF);

			/*********************************************************************************************************
            **与MCU的文件传输      -后续会与Android统一
            *********************************************************************************************************/
			virtual quint16 forMCU_RequestFile(bool sync, int msec, quint16 fileType, QString filePath);
			virtual quint16 forMCU_RequestFile(bool sync, int msec, quint16 fileType, QByteArray& data);
			virtual quint16 forMCU_UpgradeFile(bool sync, int msec, quint16 fileType, QString filePath, quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF);
			virtual quint16 forMCU_UpgradeFile(bool sync, int msec, quint16 fileType, QByteArray data, quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF);

			/*********************************************************************************************************
			**用于获取回读到的文件数据                                                                     
            *********************************************************************************************************/
			virtual quint16 getRequestFileData(QByteArray& fileData);

        protected:
            //标准文件传输
            virtual quint16 common_StartSendFile_New(quint16 fileType, quint32 fileLength, QString fileName, QByteArray fileIdentifyContent,\
                                             quint8 portIndex, quint16 moduleIndex, QUuid exclusiveKey, bool sync, int msec);
            virtual quint16 common_SendFileData(quint32 fileID, quint16 packIndex, QByteArray packData, QUuid exclusiveKey, bool sync, int msec);
        protected:
            void resetCancelUpgrade();
            virtual void registerCallBack();
            virtual quint16 onParseCommon_StartSendFile_New(const QByteArray& data);
            virtual quint16 onParseCommon_SendFileData(const QByteArray& data);
		protected:
			LBLFileTransferAbstract(QObject* parent = 0);
			LBLFileTransferAbstract(LBLFileTransferAbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化

		protected:
			QScopedPointer<LBLFileTransferAbstractPrivate> d_ptr;
		};
	}
}
#endif
