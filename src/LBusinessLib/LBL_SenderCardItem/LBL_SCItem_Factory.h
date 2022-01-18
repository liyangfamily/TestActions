/****************************************************************************
**
** This Interface file is part of the SenderCardItem module of the LBusinessLib.
** 这个是LBusinessLib中AbstractSenderCard的创建工厂模板类，该模块对外开放
**
** 该文件为LED系统中用于创建不同发送卡的工厂模板类
** C++模板类必须是实现和定义都放在头文件中，而且不用导出
**
****************************************************************************/
#ifndef CVTE_H_LBL_SENDERCARDITEMFACTORY
#define CVTE_H_LBL_SENDERCARDITEMFACTORY
#pragma once

#include "LBL_SCItem_2nd.h"
#include "LBL_SCItem_2nd_GZ.h"
#include "LBL_SCItem_2ndPlus.h"
#include "LBL_SCItem_PCON600.h"

namespace LBL
{
	namespace SCItem
	{
		template<class AbstractSenderCardItem_t, class ConSenderCardItem_t>
		class LBL_SENDERCARDITEM_TEMPLATE SenderCardItemFactory
		{
		public:
			~SenderCardItemFactory()
            {
			}
			//使用静态函数可以不用声明对象便可直接创建
			static AbstractSenderCardItem_t* creatSenderItem(const SDetectItemInfo* info , QObject * parent = 0)
			{
				AbstractSenderCardItem_t* item = new ConSenderCardItem_t(parent);
				item->setDetectInfoStruct(info);
				item->registerControl();
				return item;
			}
		};

	}
}
#endif
