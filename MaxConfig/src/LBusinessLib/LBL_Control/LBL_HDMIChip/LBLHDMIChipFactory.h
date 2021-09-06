/****************************************************************************
**
** This Interface file is part of the HDMIChip module of the LBusinessLib.
** �����LBusinessLib��HDMIChip�Ĵ�������ģ���࣬��ģ����⿪��
**
** ���ļ�ΪLEDϵͳ�����ڴ�����ͬ���Ϳ��Ĺ���ģ����
** C++ģ���������ʵ�ֺͶ��嶼����ͷ�ļ��У����Ҳ��õ���
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
				qDebug() << __FUNCTION__;
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