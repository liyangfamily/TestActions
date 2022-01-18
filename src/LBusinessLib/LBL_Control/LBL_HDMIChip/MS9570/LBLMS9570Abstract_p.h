/****************************************************************************
**
** This Interface file is part of the MS9570 module of the LBusinessLib.
** 这个是LBusinessLib中的MS9570模块接口文件，该模块不对外开放
**
** 该接口文件为LED系统MS9570的抽象发送卡类的私有数据类
**
****************************************************************************/
#ifndef CVTE_H_LBL_IMS9570_CTRL_P
#define CVTE_H_LBL_IMS9570_CTRL_P
#pragma once

#include "LBLMS9570Abstract.h"
#include "LBLMS9570DataOperat.h"
#include <LBL_CommunicatEngine/LBLPackageManager>
namespace LBL
{
	namespace MS9570
	{
		class LBLMS9570Abstract;
		class LBLMS9570AbstractPrivate
		{
			Q_DECLARE_PUBLIC(LBLMS9570Abstract)
		public:
			LBLMS9570AbstractPrivate() {}
			~LBLMS9570AbstractPrivate()
            {
			}
			LBLMS9570Abstract *q_ptr;

		public:
			//公有数据定义
			SMS9570InfoAck m_MS9570Data;
			//发送卡的探卡信息指针
			SDetectItemInfo* m_parentItemDetectInfo = nullptr;
			//负责数据包的分发
			LBLPackageManager m_packageMgr;
			LBLInteCtrlPackage::EDeviceType m_targetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_MS9570;
		};
	}
}
#endif
