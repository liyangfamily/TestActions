#pragma once
/****************************************************************************
**
** This Interface file is part of the HDMIChip module of the LBusinessLib.
** 这个是LBusinessLib中的HDMIChip模块接口文件，该模块不对外开放
**
** 该接口文件为LED系统HDMIChip的抽象发送卡类的私有数据类
**
****************************************************************************/
#ifndef CVTE_H_LBLHDMICHIPABSTRACT_P
#define CVTE_H_LBLHDMICHIPABSTRACT_P
#pragma once

#include "LBLHDMIChipAbstract.h"
#include <LBL_CommunicatEngine/LBLPackageManager>

namespace LBL
{
	namespace HDMIChip
	{
		class LBLHDMIChipAbstract;
		class LBLHDMIChipAbstractPrivate
		{
			Q_DECLARE_PUBLIC(LBLHDMIChipAbstract)
		public:
			LBLHDMIChipAbstractPrivate() {}
			~LBLHDMIChipAbstractPrivate()
            {
			}
			LBLHDMIChipAbstract *q_ptr;

		public:
			//公有数据定义
			struct SHDMIChipInfo {
				quint8 m_volume = 0;
				quint8 m_bypass = 0;
				quint8 m_ratio = 0;
				quint8 m_source = 0;
				quint8 m_contrast = 0;
				quint8 m_colortemperature = 0;
				quint8 m_brightness = 0;
				quint8 m_rGain = 0;
				quint8 m_gGain = 0;
				quint8 m_bGain = 0;
				QSize m_resolutionSize;
				quint8 m_refreshRate = 0;
				quint8 m_sceneMode = 0;
				quint8 m_splitScreenMode = 0;
			};
			SHDMIChipInfo m_realData;
			SHDMIChipInfo m_cacheData;
			//发送卡的探卡信息指针
			SDetectItemInfo* m_parentItemDetectInfo = nullptr;
			//负责数据包的分发
			LBLPackageManager m_packageMgr;
			LBLInteCtrlPackage::EDeviceType m_targetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_NULL;
		};
	}
}
#endif
