#pragma once
/****************************************************************************
**
** This Interface file is part of the SenderCard module of the LBusinessLib.
** 这个是LBusinessLib中的SenderCard模块接口文件，该模块不对外开放
**
** 该接口文件为LED系统SenderCard的抽象发送卡类的私有数据类
**
****************************************************************************/
#ifndef CVTE_H_LBLSENDERCARDABSTRACT_P
#define CVTE_H_LBLSENDERCARDABSTRACT_P
#pragma once

#include "LBLSenderCardAbstract.h"
#include <LBL_CommunicatEngine/LBLPackageManager>

namespace LBL
{
	namespace SC
	{
		class LBLSenderCardAbstract;
		class LBLSenderCardAbstractPrivate
		{
			Q_DECLARE_PUBLIC(LBLSenderCardAbstract)
		public:
			LBLSenderCardAbstractPrivate() {}
			~LBLSenderCardAbstractPrivate()
			{
				qDebug() << __FUNCTION__;
			}
			LBLSenderCardAbstract *q_ptr;

		public:
			//公有数据定义
			QByteArray senderCardReadFPGARegister; //临时储存读写发送卡寄存器的值，下一条指令会覆盖
			QList<QByteArray> senderCardConnectionBuffer; //通过集控指令读取的连线关系
			SSenderCardInfoAck m_realData;
			SSenderCardInfoAck m_cacheData;
			SGZSendCardData m_gzData;
            const float m_ethLoopBitErrRateThreshold = 0.1f;
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
