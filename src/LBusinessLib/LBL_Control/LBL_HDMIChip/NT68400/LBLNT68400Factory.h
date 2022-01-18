/****************************************************************************
**
** This Interface file is part of the NT68400 module of the LBusinessLib.
** 这个是LBusinessLib中NT68400的创建工厂模板类，该模块对外开放
**
** 该文件为LED系统中用于创建不同发送卡的工厂模板类
** C++模板类必须是实现和定义都放在头文件中，而且不用导出
**
****************************************************************************/
#ifndef CVTE_H_LBLNT68400FACTORY
#define CVTE_H_LBLNT68400FACTORY
#pragma once

#include "LBLNT68400CentralCtrl.h"

namespace LBL
{
	namespace NT68400
	{
		template<class AbstractNT68400_t, class ConNT68400_t>
		class LBLNT68400Factory
		{
		public:
			~LBLNT68400Factory()
            {
			}
			static AbstractNT68400_t* creatNT68400Device(SDetectItemInfo* info, QObject * parent = 0)
			{
				Q_ASSERT(info);
				AbstractNT68400_t* item = new ConNT68400_t(parent);
				item->setDetectInfoStruct(info);
				item->init();
				return item;
			}
		};
	}
}
#endif
