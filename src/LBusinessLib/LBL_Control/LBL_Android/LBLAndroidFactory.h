/****************************************************************************
**
** This Interface file is part of the Android module of the LBusinessLib.
** 这个是LBusinessLib中Android的创建工厂模板类，该模块对外开放
**
** 该文件为LED系统中用于创建不同发送卡的工厂模板类
** C++模板类必须是实现和定义都放在头文件中，而且不用导出
**
****************************************************************************/
#ifndef CVTE_H_LBLANDROIDFACTORY
#define CVTE_H_LBLANDROIDFACTORY
#pragma once

#include "LBLAndroidCentralCtrl.h"

namespace LBL
{
	namespace Android
	{
		template<class AbstractAndroid_t, class ConAndroid_t>
		class LBLAndroidFactory
		{
		public:
			~LBLAndroidFactory()
            {
			}

			static AbstractAndroid_t* creatAndroidDevice(SDetectItemInfo* info, QObject * parent = 0) //FIXME：函数名有问题
			{
				Q_ASSERT(info);
				AbstractAndroid_t* item = new ConAndroid_t(parent);
				item->setDetectInfoStruct(info);
				item->init();
				return item;
			}
		};
	}
}
#endif
