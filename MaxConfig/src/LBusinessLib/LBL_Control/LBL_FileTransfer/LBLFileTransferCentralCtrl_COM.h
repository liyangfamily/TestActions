/****************************************************************************
**
** This Interface file is part of the FileTransfer module of the LBL.
** 这个是LBL中的FileTransfer模块中集控实现文件，该模块不对外开放
**
** 该接口文件包含LED系统中FileTransfer集控相关操作
**
****************************************************************************/
#ifndef CVTE_H_LBLFILETRANSFERCENTRALCTRL_COM
#define CVTE_H_LBLFILETRANSFERCENTRALCTRL_COM
#pragma once

#include "LBLFileTransferAbstract.h"

namespace LBL
{
	namespace FileTransfer
	{
		template<class AbstractFileTransfer_t, class ConFileTransfer_t>
		class LBLFileTransferFactory; //前置声明，告诉编译器工厂为模板

		class LBL_FILETRANSFER_EXPORT LBLFileTransferCentralCtrl_COM : public LBLFileTransferAbstract
		{
			Q_DECLARE_PRIVATE(LBLFileTransferAbstract)

		public:
			~LBLFileTransferCentralCtrl_COM();

			quint16 forMCU_RequestFile(bool sync, int msec, quint16 fileType, QString filePath);
			quint16 forMCU_RequestFile(bool sync, int msec, quint16 fileType, QByteArray& data);
			quint16 forMCU_UpgradeFile(bool sync, int msec, quint16 fileType, QString filePath, quint8 portIndex, quint16 moduleIndex);
			quint16 forMCU_UpgradeFile(bool sync, int msec,quint16 fileType, QByteArray data, quint8 portIndex, quint16 moduleIndex);

		protected:
			//For广州MCU
			int calculateHandshakeWaitingTime(quint16 fileType);
			quint16 forMCU_RequestUpgrade(quint16 fileType, quint32 fileLength, quint8 portIndex, quint16 moduleIndex, \
				QUuid exclusiveKey, QByteArray& rePackage, bool sync, int msec);
			quint16 forMCU_SendFileData(quint16 fileType, quint32 packIndex, QByteArray packData, quint8 portIndex, quint16 moduleIndex, \
				QUuid exclusiveKey, QByteArray& rePackage, bool sync, int msec);
			quint16 forMCU_SendRequestFile(quint16 fileType, QUuid exclusiveKey, QByteArray& rePackage, bool sync, int msec);
			quint16 forMCU_ReceiveFileData(quint16 fileType, quint32 packIndex, QUuid exclusiveKey, QByteArray& rePackage, bool sync, int msec);
			quint16 forMCU_concurrent_RequestFunction(quint16 fileType);
			quint16 forMCU_concurrent_UpgradeFunction(quint16 fileType, QString fileName, quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF);
		protected:
			bool init();
			virtual void registerCallBack();
			quint16 onParseForMCU_RequestUpgrade(const QByteArray& data);
			quint16 onParseForMCU_SendFileData(const QByteArray& data);
			quint16 onParseForMCU_RequestFile(const QByteArray& data);
			quint16 onParseForMCU_ReceiveFileData(const QByteArray& data);
		protected:
			LBLFileTransferCentralCtrl_COM(QObject* parent = 0); //禁用外部创建
			LBLFileTransferCentralCtrl_COM(LBLFileTransferAbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
			friend class LBLFileTransferFactory<LBLFileTransferAbstract, LBLFileTransferCentralCtrl_COM>; //声明为一对一的好友关系，让工厂可以访问protected构造函数
		};

	}
}

#endif