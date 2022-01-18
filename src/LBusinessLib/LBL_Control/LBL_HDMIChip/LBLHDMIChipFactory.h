/****************************************************************************
**
** This Interface file is part of the HDMIChip module of the LBusinessLib.
** 这个是LBusinessLib中HDMIChip的创建工厂模板类，该模块对外开放
**
** 该文件为LED系统中用于创建不同发送卡的工厂模板类
** C++模板类必须是实现和定义都放在头文件中，而且不用导出
**
****************************************************************************/
#ifndef CVTE_H_LBLHDMICHIPFACTORY
#define CVTE_H_LBLHDMICHIPFACTORY
#pragma once

#include "LBLHDMIChipCentralCtrl.h"

namespace LBL
{
	namespace HDMIChip
	{
		template<class AbstractHDMIChip_t, class ConHDMIChip_t>
		class LBLHDMIChipFactory
		{
		public:
			~LBLHDMIChipFactory()
			{
			}
			static AbstractHDMIChip_t* creatHDMIChipDevice(SDetectItemInfo* info, QObject * parent = 0)
			{
				Q_ASSERT(info);
				AbstractHDMIChip_t* item = new ConHDMIChip_t(parent);
				item->setDetectInfoStruct(info);
				item->init();
				return item;
			}
		};
	}
}
#endif