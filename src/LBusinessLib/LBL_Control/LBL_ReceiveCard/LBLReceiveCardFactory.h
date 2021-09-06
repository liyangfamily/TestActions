/****************************************************************************
**
** This Interface file is part of the ReceiveCard module of the LBusinessLib.
** 这个是LBusinessLib中ReceiveCard的创建工厂模板类，该模块对外开放
**
** 该文件为LED系统中用于创建不同发送卡的工厂模板类
** C++模板类必须是实现和定义都放在头文件中，而且不用导出
**
****************************************************************************/
#ifndef CVTE_H_LBLRECEIVECARDFACTORY
#define CVTE_H_LBLRECEIVECARDFACTORY
#pragma once

#include "LBLReceiveCardCentralCtrl.h"

namespace LBL
{
	namespace RC
	{
		template<class AbstractReceiveCard_t, class ConReceiveCard_t>
		class LBLReceiveCardFactory
		{
		public:
			~LBLReceiveCardFactory()
			{
				qDebug("~LBLReceiveCardFactory()\n");
			}
			static AbstractReceiveCard_t* creatReceiveCardDevice(SDetectItemInfo* info, QObject * parent = 0) //FIXME：函数名有问题
			{
				Q_ASSERT(info);
				AbstractReceiveCard_t* item = new ConReceiveCard_t(parent);
				item->setDetectInfoStruct(info);
				item->init();
				return item;
			}
		};
	}
}

#endif