/****************************************************************************
**
** This Interface file is part of the MS9570 module of the LBusinessLib.
** 这个是LBusinessLib中MS9570的创建工厂模板类，该模块对外开放
**
** 该文件为LED系统中用于创建不同发送卡的工厂模板类
** C++模板类必须是实现和定义都放在头文件中，而且不用导出
**
****************************************************************************/
#ifndef CVTE_H_LBL_MS9570CTRLFACTORY
#define CVTE_H_LBL_MS9570CTRLFACTORY
#pragma once

#include "LBLMS9570CentralCtrl.h"

namespace LBL
{
	namespace MS9570
	{
		template<class AbstractMS9570Ctrl_t, class ConMS9570Ctrl_t>
		class MS9570CtrlFactory
		{
		public:
			~MS9570CtrlFactory()
            {
			}
			static AbstractMS9570Ctrl_t* creatSenderItem(SDetectItemInfo* info, QObject * parent = 0)
			{
				Q_ASSERT(info);
				AbstractMS9570Ctrl_t* item = new ConMS9570Ctrl_t(parent);
				item->setDetectInfoStruct(info);
				item->init();
				return item;
			}
		};

	}
}
#endif
