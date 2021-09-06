#pragma once
/****************************************************************************
**
** This Interface file is part of the ReceiveCard module of the LBusinessLib.
** 这个是LBusinessLib中的ReceiveCard模块接口文件，该模块不对外开放
**
** 该接口文件为LED系统ReceiveCard的抽象发送卡类的私有数据类
**
****************************************************************************/
#ifndef CVTE_H_LBLRECEIVECARDABSTRACT_P
#define CVTE_H_LBLRECEIVECARDABSTRACT_P
#pragma once

#include "LBLReceiveCardAbstract.h"
#include <LBL_CommunicatEngine/LBLPackageManager>

namespace LBL
{
	namespace RC
	{
		class LBLReceiveCardAbstract;
		class LBLReceiveCardAbstractPrivate
		{
			Q_DECLARE_PUBLIC(LBLReceiveCardAbstract)
		public:
			LBLReceiveCardAbstractPrivate() {}
			~LBLReceiveCardAbstractPrivate()
			{
				qDebug() << __FUNCTION__;
			}
			LBLReceiveCardAbstract *q_ptr;

		public:
			//公有数据定义
			SReceiveCardInfoAck m_realData;
			SReceiveCardInfoAck m_cacheData;

			QByteArray receiveCardFPGARegister; //临时储存读写发送卡寄存器的值，下一条指令会覆盖
			QByteArray moduleParam;
			QByteArray driveICParam;
			QByteArray decodingICParam;

			QList<SRCStatusInfo> m_rcStatusInfo;
			QList<SRCMonitorInfo> m_rcMonitorInfo;
			//发送卡的探卡信息指针
			SDetectItemInfo* m_parentItemDetectInfo = nullptr;
			//负责数据包的分发
			LBLPackageManager m_packageMgr;
			LBLInteCtrlPackage::EDeviceType m_targetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_NULL;
			LBLInteCtrlPackage::EDeviceType m_registerTargetDeviceType = LBLInteCtrlPackage::EDeviceType::EDT_NULL;
		};
	}
}
#endif
