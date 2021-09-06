/****************************************************************************
**
** This Interface file is part of the SenderCardItem module of the LBusinessLib.
** 这个是LBusinessLib中的2nd发送卡的私有数据文件，该模块不对外开放
**
** 该接口文件为LED系统发送卡的2nd发送卡类的私有数据类
**
****************************************************************************/
#ifndef CVTE_H_LBL_SENDERCARDITEM_2ND_P
#define CVTE_H_LBL_SENDERCARDITEM_2ND_P
#pragma once

#include "LBL_SCItem_Abstract_p.h"

//加载HDMI库
#include "../LBL_Control/LBL_HDMIChip/LBLHDMIChipFactory.h"
#include "../LBL_Control/LBL_HDMIChip/MS9570/LBL_MS9570_Factory.h"
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
		class SenderCardItem_2nd;
		class SenderCardItem_2ndPrivate :public LBLAbstractSCItemPrivate
		{
			Q_DECLARE_PUBLIC(SenderCardItem_2nd)
		public:
			SenderCardItem_2ndPrivate() {
				m_detectInfo.senderCardClass = ESenderCardClass::ESC_2nd;
			}
			~SenderCardItem_2ndPrivate()
			{
				qDebug("~SenderCardItem_2ndPrivate()\n");
			}

		public:
			//2nd发送卡特有数据
			HDMIChip::LBLHDMIChipAbstract* m_HDMIChip = nullptr; //HDMI芯片控制
			MS9570::LBLMS9570Abstract* m_MS9570Ctrl = nullptr; //MS9570控制

		};
	}
}
#endif
