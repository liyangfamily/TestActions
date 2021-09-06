/****************************************************************************
**
** This Interface file is part of the MS9570 module of the LBL.
** �����LBL�е�MS9570ģ�������ݲ���ʵ���ļ�����ģ����⿪��
**
** �ýӿ��ļ�����LEDϵͳ��MS9570������ز���
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
