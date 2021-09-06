/****************************************************************************
**
** This Interface file is part of the NT68400 module of the LBusinessLib.
** �����LBusinessLib��NT68400�Ĵ�������ģ���࣬��ģ����⿪��
**
** ���ļ�ΪLEDϵͳ�����ڴ�����ͬ���Ϳ��Ĺ���ģ����
** C++ģ���������ʵ�ֺͶ��嶼����ͷ�ļ��У����Ҳ��õ���
**
****************************************************************************/
#ifndef CVTE_H_LBLNT68400FACTORY
#define CVTE_H_LBLNT68400FACTORY
#pragma once

#include "LBLNT68400CentralCtrl.h"

namespace LBL
{
	namespace NT68400
	{
		template<class AbstractNT68400_t, class ConNT68400_t>
		class LBLNT68400Factory
		{
		public:
			~LBLNT68400Factory()
			{
				qDebug("~LBLNT68400Factory()\n");
			}
			static AbstractNT68400_t* creatNT68400Device(SDetectItemInfo* info, QObject * parent = 0)
			{
				Q_ASSERT(info);
				AbstractNT68400_t* item = new ConNT68400_t(parent);
				item->setDetectInfoStruct(info);
				item->init();
				return item;
			}
		};
	}
}
#endif