#pragma once
/****************************************************************************
**
** This Interface file is part of the NT68400 module of the LBusinessLib.
** 这个是LBusinessLib中的NT68400模块接口文件，该模块不对外开放
**
** 该接口文件为LED系统NT68400的抽象发送卡类的私有数据类
**
****************************************************************************/
#ifndef CVTE_H_LBLNT68400ABSTRACT_P
#define CVTE_H_LBLNT68400ABSTRACT_P
#pragma once

#include "LBLNT68400Abstract.h"
#include <LBL_CommunicatEngine/LBLPackageManager>
#include "LBLNT68400Struct.h"

namespace LBL
{
	namespace NT68400
	{
		class LBLNT68400Abstract;
		class LBLNT68400AbstractPrivate
		{
			Q_DECLARE_PUBLIC(LBLNT68400Abstract)
		public:
			LBLNT68400AbstractPrivate() {}
			~LBLNT68400AbstractPrivate()
			{
				qDebug("~LBLNT68400AbstractPrivate()\n");
			}
			LBLNT68400Abstract *q_ptr;

		public:
			//公有数据定义
			SNT68400Data m_NT68400Data;
			//发送卡的探卡信息指针
			SDetectItemInfo* m_parentItemDetectInfo = nullptr;
			//负责数据包的分发
			LBLPackageManager m_packageMgr;
			LBLInteCtrlPackage::EDeviceType m_targetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_NT68400;
		};
	}
}
#endif
