/*********************************************************************************************************
** This file is part of the LBL_SenderCardItem module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBLSCITEMMANAGER
#define CVTE_H_LBLSCITEMMANAGER
#pragma once

#include <LBL_SenderCardItem/LBLSCItemGlobal>
#include <LBL_SenderCardItem/LBLSCItemStructGlobal>
#include <LBL_SenderCardItem/LBLAbstractSCItem>

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#define CVTE_SCOPEDPT
//#undef  CVTE_SCOPEDPT

#define gSCItemMgr LBL::SCItem::LBLSCItemManager::getInstance()

class LBLDetectServer;
namespace LBL
{
	namespace SCItem
	{
		class LBL_SENDERCARDITEM_EXPORT LBLSCItemManager :public QObject
		{
			Q_OBJECT
		public:
			~LBLSCItemManager();
			static LBLSCItemManager* getInstance(QObject* parent = 0);

			bool addItem(const SDetectItemInfo*);
            void setUsingItemList(QList<LBLAbstractSCItem*> list);
            bool connectItem(QUuid internalUuid);
            bool disconnectItem(QUuid internalUuid);
			QList<LBLAbstractSCItem*> getUsingItemList();
			QList<LBLAbstractSCItem*> getAllItemList();

			//探卡服务
			bool startDetectServer(quint16 detectIntervalTime, quint16 everyDetectIntervalTime, quint16 everyDetectCount);
			void stopDetectServer();

			//测试用接口函数，不一定保留，有删除风险
			LBLAbstractSCItem* getItemByInternalUuid(QUuid internalUuid);
			LBLAbstractSCItem* getItemByHostName(const SDetectItemInfo& info);
			LBLAbstractSCItem* getItemBySocketObject(const QObject* objSocket);
			bool contains(const SDetectItemInfo& info);
			bool containsInUsing(const SDetectItemInfo& info);
			bool containsInRabbishCan(const SDetectItemInfo& info);
			LBLAbstractSCItem* getRabiishItemByHostName(const SDetectItemInfo& info);

			void test();
		protected:
			bool deleteItem(QUuid);
			bool clearItem();

		protected slots :
			void slot_DetectComplit();
			void sig_SingleDetectComplite();
			void slot_DisconnectFromCOM(const QObject* objSocket);
		signals:
			void sig_SenderCardOnline(SDetectItemInfo info);
			void sig_SenderCardOffline(SDetectItemInfo hostName);
            void sig_StartDetect();
            void sig_DetectComplit();
			void sig_ConnectItem(QUuid internalUuid);
			void sig_DisConnectItem(QUuid internalUuid);
			void sig_CurrentItemChanged(QUuid internalUuid);
		private:
			void emptyRabbishCan();
			void parsingDetectInfoList(const QList<SDetectItemInfo>&);

			//测试用接口函数，不一定保留，有删除风险
			bool moveToRabiishCan(LBLAbstractSCItem*);
			bool restoreFormRabiishCan(LBLAbstractSCItem*);
		private:
			LBLSCItemManager(QObject* parent = 0);
			LBLSCItemManager(const LBLSCItemManager&) = delete;
			LBLSCItemManager& operator=(const LBLSCItemManager&) = delete;

#ifndef CVTE_SCOPEDPT
			static LBLSCItemManager* m_instance;

			class CGarbo
			{
			public:
				~CGarbo()
                {
					if (LBLSCItemManager::m_instance)
					{
						delete LBLSCItemManager::m_instance;
						LBLSCItemManager::m_instance = nullptr;
					}
				}
			};
			//static CGarbo Garbo;	//--->1
#endif // CVTE_SCOPEDPT

			QMutex m_mutex_protect_itemList;
			//在使用中的Item
			QList<LBLAbstractSCItem*> m_list_usingItem;
			//所有的Item
			QList<LBLAbstractSCItem*> m_list_allItem;
			QMutex m_mutex_protect_rabbish;
			//需要删除的
			QSet<LBLAbstractSCItem*> m_set_rabbish_can;

			LBLDetectServer* m_detectServer = nullptr;
		};
	}
}
#endif
