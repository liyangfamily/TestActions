/****************************************************************************
**
** This Interface file is part of the FileTransfer module of the LBusinessLib.
** 这个是LBusinessLib中FileTransfer的创建工厂模板类，该模块对外开放
**
** 该文件为LED系统中用于创建不同发送卡的工厂模板类
** C++模板类必须是实现和定义都放在头文件中，而且不用导出
**
****************************************************************************/
#ifndef CVTE_H_LBLFILETRANSFERFACTORY
#define CVTE_H_LBLFILETRANSFERFACTORY
#pragma once

#include "LBLFileTransferCentralCtrl.h"
#include "LBLFileTransferCentralCtrl_COM.h"

namespace LBL
{
	namespace FileTransfer
	{
		template<class AbstractFileTransfer_t, class ConFileTransfer_t>
		class LBLFileTransferFactory
		{
		public:
			~LBLFileTransferFactory()
			{
				qDebug("~LBLFileTransferFactory()\n");
			}
			static AbstractFileTransfer_t* creatFileTransferDevice(SDetectItemInfo* info, QObject * parent = 0) //FIXME：函数名有问题
			{
				Q_ASSERT(info);
				AbstractFileTransfer_t* item = new ConFileTransfer_t(parent);
				item->setDetectInfoStruct(info);
				item->init();
				return item;
			}
		};
	}
}
#endif