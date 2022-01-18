/****************************************************************************
**
** This Interface file is part of the SenderCardItem module of the LBusinessLib.
** 这个是LBusinessLib中的SenderCard模块接口文件，该模块不对外开放
**
** 该接口文件为LED系统发送卡的抽象发送卡类的私有数据类
**
****************************************************************************/
#ifndef CVTE_H_LBL_ABSTRACTSENDERCARDITEM_P
#define CVTE_H_LBL_ABSTRACTSENDERCARDITEM_P
#pragma once

//加载Androidd库
#include "../LBL_Control/LBL_Android/LBLAndroidFactory.h"
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_Androidd.lib")
#else
#pragma comment(lib,"LBL_Android.lib")
#endif // QT_DEBUG
#endif

//加载SenderCard库
#include "../LBL_Control/LBL_SenderCard/LBLSenderCardFactory.h"
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_SenderCardd.lib")
#else
#pragma comment(lib,"LBL_SenderCard.lib")
#endif // QT_DEBUG
#endif

//加载ReceiveCard库
#include "../LBL_Control/LBL_ReceiveCard/LBLReceiveCardFactory.h"
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_ReceiveCardd.lib")
#else
#pragma comment(lib,"LBL_ReceiveCard.lib")
#endif // QT_DEBUG
#endif

//加载FileTransfer库
#include "../LBL_Control/LBL_FileTransfer/LBLFileTransferFactory.h"
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_FileTransferd.lib")
#else
#pragma comment(lib,"LBL_FileTransfer.lib")
#endif // QT_DEBUG
#endif

#include "LBL_SenderCardItem/LBLAbstractSCItem.h"
#include "LBL_SenderCardItem/LBLSCItemStructGlobal.h"

namespace LBL
{
	namespace SCItem
	{
		class LBLAbstractSCItem;
		class LBLAbstractSCItemPrivate
		{
			Q_DECLARE_PUBLIC(LBLAbstractSCItem)
		public:
			LBLAbstractSCItemPrivate() {}
			virtual ~LBLAbstractSCItemPrivate()
            {
			}
			LBLAbstractSCItem *q_ptr;

		public:
			//所有发送卡公有的数据，如果发送卡有其特有的数据，考虑继承该私有类
            bool m_isUsing=false;
			QUuid itemID = QUuid::createUuid(); //内建uuid
			SDetectItemInfo m_detectInfo;
			LBLConnection m_connection;
			Android::LBLAndroidAbstract* m_AndroidCtrl = nullptr; //AndroidCtrl控制
			SC::LBLSenderCardAbstract* m_SenderCardCtrl = nullptr; //SenderCard控制
			RC::LBLReceiveCardAbstract* m_ReceiveCardCtrl = nullptr; //ReceiveCard控制
            FileTransfer::LBLFileTransferAbstract* m_FileTransfer = nullptr; //文件传输控制


			//联合数据
			QList<RC::SRCStatusInfo> m_allRCStatusInfo; //所有接收卡状态信息
            QList<RC::SRCStatusInfo> m_allRCStatusCacheInfo; //所有接收卡缓存状态信息
		};
	}
}
#endif
