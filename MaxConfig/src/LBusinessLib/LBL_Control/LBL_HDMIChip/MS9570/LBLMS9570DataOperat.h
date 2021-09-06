/****************************************************************************
**
** This Interface file is part of the MS9570 module of the LBL.
** 这个是LBL中的MS9570模块中数据操作实现文件，该模块对外开放
**
** 该接口文件包含LED系统中MS9570数据相关操作
**
****************************************************************************/
#ifndef CVTE_H_LBL_MS9570CTRL_DATAOPERAT
#define CVTE_H_LBL_MS9570CTRL_DATAOPERAT
#pragma once

#include "LBLHDMIChipGlobal.h"
#include "LBL_MS9570_Struct.h"

namespace LBL
{
	namespace MS9570
	{
		class LBLMS9570DataOperat
		{
		public:
			LBLMS9570DataOperat();
			~LBLMS9570DataOperat();

			bool setBypass(int value);
			int  getBypass();

		private:
			SMS9570InfoAck m_data;
		};
	}
}
#endif
