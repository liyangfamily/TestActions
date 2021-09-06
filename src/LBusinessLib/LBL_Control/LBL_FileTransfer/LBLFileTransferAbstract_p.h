#pragma once
/****************************************************************************
**
** This Interface file is part of the FileTransfer module of the LBusinessLib.
** 这个是LBusinessLib中的FileTransfer模块接口文件，该模块不对外开放
**
** 该接口文件为LED系统FileTransfer的抽象发送卡类的私有数据类
**
****************************************************************************/
#ifndef CVTE_H_LBLFILETRANSFERABSTRACT_P
#define CVTE_H_LBLFILETRANSFERABSTRACT_P
#pragma once

#include "LBLFileTransferAbstract.h"
#include <LBL_CommunicatEngine/LBLPackageManager>

#include <atomic>
#include <QtConcurrent/QtConcurrentRun>
namespace LBL
{
	namespace FileTransfer
	{
		class LBLFileTransferAbstract;
		class LBLFileTransferAbstractPrivate
		{
			Q_DECLARE_PUBLIC(LBLFileTransferAbstract)
		public:
			LBLFileTransferAbstractPrivate() {}
			~LBLFileTransferAbstractPrivate()
			{
				qDebug() << __FUNCTION__;
			}
			LBLFileTransferAbstract *q_ptr;

		public:
			//公有数据定义
			struct SCommonAtomicParam {
                std::atomic_int m_startSendFile_ID{0};
                std::atomic_int m_startSendFile_SinglePackLength{0};
                std::atomic_int m_sendFileData_FailReason{0};
                std::atomic_int m_requestUpgrade_FailReason{0};
                std::atomic_int m_queryStatus_OperatSteps{0};
                std::atomic_int m_queryStatus_OperatProgress {0};
			}m_commonAtomicParam;
			QString m_stepName;

			struct SForMCUAtomicParam {
                std::atomic_int m_requestUpgrade_SinglePackLength{0};
                std::atomic_int m_sendFileData_FailReason{0};


                std::atomic_int m_requestFile_SinglePackLength{0};
                std::atomic_int m_requestFile_TotalFileLength{0};
                std::atomic_int m_requestFile_FailReason{0};
			}m_forMCUAtomicParam;
			QByteArray m_requestFileArray;
			//发送卡的探卡信息指针
			SDetectItemInfo* m_parentItemDetectInfo = nullptr;
			//负责数据包的分发
			LBLPackageManager m_packageMgr;
			LBLInteCtrlPackage::EDeviceType m_targetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_NULL;
			LBLInteCtrlPackage::EDeviceType m_registerTargetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_NULL;

			//升级进程控制
            std::atomic_bool m_upgradeCancel{false}; //是否取消升级
			bool m_upgradingSend = true;
			LBLFileTransferPackage::EFileType m_upgradingFileType = LBLFileTransferPackage::EFT_SelectFile;
			quint8 m_upgradingPort = 0xFF;
			quint16 m_upgradingModule = 0xFFFF;
			QFuture<quint16> m_upgradeFileFuture;
			QSharedPointer<QFutureInterface<quint16>> m_upgradeFileInterface;
		};
	}
}
#endif
