/****************************************************************************
**
** This Interface file is part of the SenderCardItem module of the LBusinessLib.
** 这个是LBusinessLib中的PCON600发送卡的私有数据文件，该模块不对外开放
**
** 该接口文件为LED系统发送卡的2nd_GZ发送卡类的私有数据类
**
****************************************************************************/
#ifndef CVTE_H_LBL_SENDERCARDITEM_PCON600_P
#define CVTE_H_LBL_SENDERCARDITEM_PCON600_P
#pragma once

#include "LBL_SCItem_Abstract_p.h"



//加载HDMI库
#include "../LBL_Control/LBL_HDMIChip/LBLHDMIChipFactory.h"
#include "../LBL_Control/LBL_HDMIChip/NT68400/LBLNT68400Factory.h"
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_HDMIChipd.lib")
#else
#pragma comment(lib,"LBL_HDMIChip.lib")
#endif // QT_DEBUG
#endif

namespace LBL
{
	namespace SCItem
	{
		class SenderCardItem_PCON600;
		class SenderCardItem_PCON600Private :public LBLAbstractSCItemPrivate
		{
			Q_DECLARE_PUBLIC(SenderCardItem_PCON600)
		public:
			SenderCardItem_PCON600Private() {}
			~SenderCardItem_PCON600Private()
            {
			}

		public:
			//发送卡特有数据
			HDMIChip::LBLHDMIChipAbstract* m_HDMIChip = nullptr; //HDMI芯片控制
			NT68400::LBLNT68400Abstract* m_NT68400Ctrl = nullptr; //NT68400控制

		};
	}
}
#endif
