/****************************************************************************
**
** This Interface file is part of the SenderCard module of the LBusinessLib.
** 这个是LBusinessLib中SenderCard的创建工厂模板类，该模块对外开放
**
** 该文件为LED系统中用于创建不同发送卡的工厂模板类
** C++模板类必须是实现和定义都放在头文件中，而且不用导出
**
****************************************************************************/
#ifndef CVTE_H_LBLSENDERCARDFACTORY
#define CVTE_H_LBLSENDERCARDFACTORY
#pragma once

#include "LBLSenderCardCentralCtrl.h"
#include "LBLSenderCardCentralCtrl_COM.h"

namespace LBL
{
	namespace SC
	{
		template<class AbstractSenderCard_t, class ConSenderCard_t>
		class LBLSenderCardFactory
		{
		public:
			~LBLSenderCardFactory()
			{
				qDebug("~LBLSenderCardFactory()\n");
			}
			static AbstractSenderCard_t* creatSenderCardDevice(SDetectItemInfo* info, QObject * parent = 0)
			{
				Q_ASSERT(info);
				AbstractSenderCard_t* item = new ConSenderCard_t(parent);
				item->setDetectInfoStruct(info);
				item->init();
				return item;
			}
		};
	}
}
#endif