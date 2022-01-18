/****************************************************************************
**
** This Interface file is part of the FileTransfer module of the LBL.
** 这个是LBL中的FileTransfer模块中集控实现文件，该模块不对外开放
**
** 该接口文件包含LED系统中FileTransfer集控相关操作
**
****************************************************************************/
#ifndef CVTE_H_LBLFILETRANSFERCENTRALCTRL
#define CVTE_H_LBLFILETRANSFERCENTRALCTRL
#pragma once

#include "LBLFileTransferAbstract.h"

namespace LBL
{
	namespace FileTransfer
	{
		template<class AbstractFileTransfer_t, class ConFileTransfer_t>
		class LBLFileTransferFactory; //前置声明，告诉编译器工厂为模板

        //this class in order to solve the LUPDATE: Qualifying with unknown namespace/class
        class TestTransfer1 : public LBLFileTransferAbstract
        {
            Q_OBJECT
        public:
            TestTransfer1(){};
        };

		class LBL_FILETRANSFER_EXPORT LBLFileTransferCentralCtrl : public LBLFileTransferAbstract
		{
			Q_DECLARE_PRIVATE(LBLFileTransferAbstract)
            Q_OBJECT
		public:
			~LBLFileTransferCentralCtrl();

            //quint16 common_RequestFile(quint16 fileType);
            quint16 common_UpgradeFile(bool sync, int msec, quint16 fileType, QString filePath, quint8 portIndex, quint16 moduleIndex);
            quint16 common_UpgradeFile(bool sync, int msec, quint16 fileType, QByteArray data, quint8 portIndex, quint16 moduleIndex);

		protected:
			//标准文件传输
			int calculateHandshakeWaitingTime(quint16 fileType);
            quint16 common_StartSendFile(quint16 fileType, quint32 fileLength, QString fileName, QUuid exclusiveKey, bool sync, int msec);

			quint16 common_RequestUpgrade(quint16 fileType, QUuid exclusiveKey, bool sync, int msec);
            quint16 common_RequestUpgrade_New(quint16 fileType, QUuid exclusiveKey, bool sync, int msec,quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF);
			quint16 common_QueryUpgradeStatus(quint16 fileType, QUuid exclusiveKey, bool sync, int msec);
            quint16 common_concurrent_UpgradeFunction(quint16 fileType, QString filePath,quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF);
            quint16 common_concurrent_UpgradeFunction_D(quint16 fileType, const QByteArray& fileData, quint8 portIndex = 0xFF, quint16 moduleIndex = 0xFFFF);
			
		protected:
			bool init();
			virtual void registerCallBack();
            quint16 onParseCommon_StartSendFile(const QByteArray& data);
			quint16 onParseCommon_RequestUpgrade(const QByteArray& data);
            quint16 onParseCommon_RequestUpgrade_New(const QByteArray& data);
			quint16 onParseCommon_QueryUpgradeStatus(const QByteArray& data);
		protected:
			LBLFileTransferCentralCtrl(QObject* parent = 0); //禁用外部创建
			LBLFileTransferCentralCtrl(LBLFileTransferAbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
			friend class LBLFileTransferFactory<LBLFileTransferAbstract, LBLFileTransferCentralCtrl>; //声明为一对一的好友关系，让工厂可以访问protected构造函数
		};

	}
}

#endif
