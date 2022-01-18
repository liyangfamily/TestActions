#include "LBL_SenderCardItem/LBLSCItemManager.h"
#include "DetectServer/LBLDetectServer.h"
#ifdef CVTE_SCOPEDPT
#include <QScopedPointer>
#endif // CVTE_SCOPEDPT
#include "LBL_SCItem_Factory.h"
#include <LBL_CommunicatEngine/LBLClusterProxy>

#include <QtConcurrent/QtConcurrentRun>
namespace LBL
{
	namespace SCItem
	{
#ifndef CVTE_SCOPEDPT
		LBLSCItemManager* LBLSCItemManager::m_instance = nullptr;
		//SenderCardMgr::CGarbo SenderCardMgr::Garbo; //--->1
#else
		static QScopedPointer<LBLSCItemManager> m_instance;
#endif // CVTE_SCOPEDPT

		LBLSCItemManager::~LBLSCItemManager()
		{
            stopDetectServer();
			/*if (m_detectServer)
				m_detectServer->deleteLater();*/
				//qDeleteAll(m_list_allItem);
		}

		LBLSCItemManager* LBLSCItemManager::getInstance(QObject* parent/* = 0*/)
		{
#ifndef CVTE_SCOPEDPT
			if (nullptr == m_instance)
			{
				m_instance = new LBLSCItemManager(parent);
			}
			return m_instance;
#else
			if (m_instance.isNull())
			{
				m_instance.reset(new LBLSCItemManager(parent));
			}
			return m_instance.data();
#endif // CVTE_SCOPEDPT

		}

		bool LBLSCItemManager::addItem(const SDetectItemInfo *info)
		{
			Q_ASSERT(info);
			if (!info)
			{
				return false;
			}
			LBLAbstractSCItem* item = nullptr;
			switch (info->senderCardClass)
			{
			case ESenderCardClass::ESC_2nd:
			{
				item = SenderCardItemFactory<LBLAbstractSCItem, SenderCardItem_2nd>::creatSenderItem(info, this);
				if (!item) //FIXME:按照此规范实现代码
					return false;
			}
			break;
			case ESenderCardClass::ESC_2nd_GZ:
			{
				item = SenderCardItemFactory<LBLAbstractSCItem, SenderCardItem_2nd_GZ>::creatSenderItem(info, this);
				if (!item)
					return false;
			}
			break;
			case ESenderCardClass::ESC_2nd_Plus:
			{
				//item = SenderCardItemFactory<LBLAbstractSCItem, SenderCardItem_PCON600>::creatSenderItem(info, this);
				item = SenderCardItemFactory<LBLAbstractSCItem, SenderCardItem_2ndPlus>::creatSenderItem(info, this);
				if (!item)
					return false;
			}
			break;
			case ESenderCardClass::ESC_PCON600:
			{
				item = SenderCardItemFactory<LBLAbstractSCItem, SenderCardItem_PCON600>::creatSenderItem(info, this);
				if (!item)
					return false;
			}
			break;
			case ESenderCardClass::ESC_Test:
			{
				qDebug() << "No sending card of this type.";
			}
			break;
			default:
			{
				item = SenderCardItemFactory<LBLAbstractSCItem, SenderCardItem_2nd>::creatSenderItem(info, this);
				if (!item) //FIXME:按照此规范实现代码
					return false;
			}
			break;
			}
			QMutexLocker locker(&m_mutex_protect_itemList);
			m_list_allItem.append(item);
            return true;
        }

        void LBLSCItemManager::setUsingItemList(QList<LBLAbstractSCItem *> list)
        {
            for(auto i:m_list_usingItem){
                disconnectItem(i->internalUuid());
            }
            m_list_usingItem=list;
        }

		bool LBLSCItemManager::connectItem(QUuid internalUuid)
		{
			if (1 <= m_list_usingItem.size()) {
				for (auto item : m_list_usingItem) {
					disconnectItem(item->internalUuid());
				}
				m_list_usingItem.clear();
				//return false;
			}
			LBLAbstractSCItem* item = getItemByInternalUuid(internalUuid);
			if (!item) {
				return false;
			}
			if (item->senderCardStatus() != ESenderCardStatus::ESS_Online) {
				return false;
			}

			if (m_list_usingItem.contains(item)) {
				return false;
			}
			m_list_usingItem.append(item);
			item->setUsing(true);
			emit sig_ConnectItem(internalUuid);
			qDebug() << __FUNCTION__ << "connectItem success.";
			return true;
		}

        bool LBLSCItemManager::disconnectItem(QUuid internalUuid)
        {
            LBLAbstractSCItem* item= getItemByInternalUuid(internalUuid);
            if(item&&m_list_usingItem.contains(item)){
                m_list_usingItem.removeOne(item);
				item->setUsing(false);
				emit sig_DisConnectItem(internalUuid);
                qDebug()<<__FUNCTION__<<"disconnectItem success.";
                return true;
            }
            return false;
        }

		bool LBLSCItemManager::deleteItem(QUuid id)
		{
			QMutexLocker locker(&m_mutex_protect_itemList);
			for (QList<LBLAbstractSCItem*>::iterator it = m_list_allItem.begin(); it != m_list_allItem.end(); ++it)
			{
				if ((*it)->internalUuid() == id)
				{
					(*it)->deleteLater();
					m_list_allItem.erase(it);
					return true;
				}
			}
			return false;
		}

		bool LBLSCItemManager::clearItem()
		{
			QMutexLocker locker(&m_mutex_protect_itemList);
			qDeleteAll(m_list_allItem);
			m_list_allItem.clear();
			return true;
		}

        QList<LBLAbstractSCItem*> LBLSCItemManager::getUsingItemList()
		{
			QMutexLocker locker(&m_mutex_protect_itemList);
			return m_list_usingItem;
		}

		QList<LBLAbstractSCItem*> LBLSCItemManager::getAllItemList()
		{
			QMutexLocker locker(&m_mutex_protect_itemList);
			return m_list_allItem;
		}

		bool LBLSCItemManager::startDetectServer(quint16 detectIntervalTime, quint16 everyDetectIntervalTime, quint16 everyDetectCount)
		{
			emptyRabbishCan();
			return m_detectServer->slot_startDetectServer(detectIntervalTime, everyDetectIntervalTime, everyDetectCount);
		}

		void LBLSCItemManager::stopDetectServer()
		{
			m_detectServer->slot_stopDetectServer();
		}

		LBL::SCItem::LBLAbstractSCItem* LBLSCItemManager::getItemByInternalUuid(QUuid internalUuid)
		{
			QMutexLocker locker(&m_mutex_protect_itemList);
			for (QList<LBLAbstractSCItem*>::iterator it = m_list_allItem.begin(); it != m_list_allItem.end(); ++it)
			{
				if ((*it)->internalUuid() == internalUuid)
				{
					return *it;
				}
			}
			qDebug() << "Can't get senderCardItem by internalUuid: " << internalUuid.toString(QUuid::WithoutBraces);
			return nullptr;
		}

		LBLAbstractSCItem * LBLSCItemManager::getItemByHostName(const SDetectItemInfo& info)
		{
			QMutexLocker locker(&m_mutex_protect_itemList);
			for (QList<LBLAbstractSCItem*>::iterator it = m_list_allItem.begin(); it != m_list_allItem.end(); ++it)
			{
				if ((*it)->getDetectInfoStruct() == info)
				{
					return *it;
				}
			}
			qDebug() << "Can't get senderCardItem by hostName: " << info.hostName;
			return nullptr;
		}

		LBLAbstractSCItem * LBLSCItemManager::getItemBySocketObject(const QObject * objSocket)
		{
			QMutexLocker locker(&m_mutex_protect_itemList);
			for (QList<LBLAbstractSCItem*>::iterator it = m_list_allItem.begin(); it != m_list_allItem.end(); ++it)
			{
				if ((*it)->getDetectInfoStruct().socketObj == objSocket)
				{
					return *it;
				}
			}
			qDebug() << "Can't get senderCardItem by socketObj: " << (quint64)objSocket;
			return nullptr;
		}

		bool LBLSCItemManager::contains(const SDetectItemInfo& info)
		{
			return getItemByHostName(info) == nullptr ? false : true;
		}

		bool LBLSCItemManager::containsInUsing(const SDetectItemInfo& info)
		{
			QMutexLocker locker(&m_mutex_protect_itemList);
			for (QList<LBLAbstractSCItem*>::iterator it = m_list_usingItem.begin(); it != m_list_usingItem.end(); ++it)
			{
				if ((*it)->getDetectInfoStruct() == info)
				{
					return true;
				}
			}
			return false;
		}

		bool LBLSCItemManager::containsInRabbishCan(const SDetectItemInfo& info)
		{
			QMutexLocker locker(&m_mutex_protect_rabbish);
			for (QSet<LBLAbstractSCItem*>::iterator it = m_set_rabbish_can.begin(); it != m_set_rabbish_can.end(); ++it)
			{
				if ((*it)->getDetectInfoStruct() == info)
				{
					return true;
				}
			}
			return false;
		}

		LBL::SCItem::LBLAbstractSCItem* LBLSCItemManager::getRabiishItemByHostName(const SDetectItemInfo& info)
		{
			QMutexLocker locker(&m_mutex_protect_rabbish);
			for (QSet<LBLAbstractSCItem*>::iterator it = m_set_rabbish_can.begin(); it != m_set_rabbish_can.end(); ++it)
			{
				if ((*it)->getDetectInfoStruct() == info)
				{
					return *it;
				}
			}
			qDebug() << "Can't get Rabiish senderCardItem by hostName: " << info.hostName;
			return nullptr;
		}

		void LBLSCItemManager::test()
		{
			//LBLSocketExclusiveLock exLock(item->socketObject());
			//if (exLock.autoLock(10000))
			//{//独占成功
			//	QUuid id = exLock.exclusiveKey();
			//	int i = 0;
            //}
		}

		void LBLSCItemManager::slot_DetectComplit()
		{
            parsingDetectInfoList(m_detectServer->getDetectInfoList()); 
			emit sig_DetectComplit();
            //QtConcurrent::run(this, &LBLSCItemManager::parsingDetectInfoList, m_detectServer->getDetectInfoList());
		}

		void LBLSCItemManager::sig_SingleDetectComplite()
		{
			parsingDetectInfoList(m_detectServer->getDetectInfoList());
		}

		void LBLSCItemManager::slot_DisconnectFromCOM(const QObject* objSocket)
		{
			if (!objSocket) {
				return;
			}
			auto temp = getItemBySocketObject(objSocket);
			if (!temp) {
				return;
			}
			temp->setSenderCardStatus(ESenderCardStatus::ESS_OffLine);
			emit sig_SenderCardOffline(temp->getDetectInfoStruct());
			emit sig_DetectComplit();
		}

		void LBLSCItemManager::parsingDetectInfoList(const QList<SDetectItemInfo>& currentDetectInfoList)
		{
			//原来有现在没有了
			for (QList<LBLAbstractSCItem*>::iterator it = m_list_allItem.begin(); it != m_list_allItem.end();)
			{
				const SDetectItemInfo& tempS = (*it)->getDetectInfoStruct();
				if (!currentDetectInfoList.contains(tempS))
				{
					//找到senditem，设置状态为离线
					LBLAbstractSCItem* senderCardItem = (*it);
					if (nullptr == senderCardItem)
					{
						++it;
						continue;
					}
					if (gCluster->isSocketInExclusive(senderCardItem->socketObject()))
					{
						//防止启用独占模式，探卡服务还在继续运行，解析不到数据导致断线
						qDebug() << "Socket of " << senderCardItem->hostName() << " is in Exclusive, pass parsing.";
						++it;
						continue;
                    }
                    if (LBLClusterProxy::isItemExlusive(senderCardItem->hostName()))
                    {
                        //防止启用独占模式，探卡服务还在继续运行，解析不到数据导致断线
                        qDebug() << "Socket of " << senderCardItem->hostName() << " is in Exclusive, pass parsing.";
                        ++it;
                        continue;
                    }
					//掉线了
					qDebug() << tempS.hostName << " offline**********************************************************************.";
					emit sig_SenderCardOffline(tempS);
					if (senderCardItem->senderCardStatus() != ESenderCardStatus::ESS_OffLine)
					{
						//如果是在线就先设置为离线
						senderCardItem->setSenderCardStatus(ESenderCardStatus::ESS_OffLine);
					}
					else
					{
						//如果已近是离线了，就把hostName放入垃圾桶，等待删除
						if (moveToRabiishCan(senderCardItem))
						{
							QMutexLocker locker(&m_mutex_protect_itemList);
							it = m_list_allItem.erase(it);//从探卡队列删除
							continue;
						}
					}
				}
				++it;
			}
			//现在有
			foreach(SDetectItemInfo item, currentDetectInfoList)
			{
				emit sig_SenderCardOnline(item);
				if (!contains(item))
				{//原来没有
					//新增
					qDebug() << item.hostName << " new online.";
					//看看是否在垃圾桶中，匹配信息，在的话就恢复
					if (containsInRabbishCan(item))
					{
						LBLAbstractSCItem* rabiishSenderCardItem = getRabiishItemByHostName(item);
						if (item == rabiishSenderCardItem->getDetectInfoStruct())
						{
							restoreFormRabiishCan(rabiishSenderCardItem);
							rabiishSenderCardItem->setDetectInfoStruct(&item);
						}
						else
						{
							//否则新建一个发送卡
							addItem(&item);
						}
					}
					else
					{
						//否则新建一个发送卡
						addItem(&item);
					}
				}
				else
				{
					//原来有,更新探卡信息
					getItemByHostName(item)->setDetectInfoStruct(&item);
					getItemByHostName(item)->checkItemInfo();
					qDebug() << item.hostName << " Update detectinfo.";
				}
            }
		}


		void SCItem::LBLSCItemManager::emptyRabbishCan()
		{
			QMutexLocker locker(&m_mutex_protect_rabbish);
			//清空垃圾桶，删除所有sendItem，从map中也移出
			for (QSet<LBLAbstractSCItem*>::iterator it = m_set_rabbish_can.begin(); it != m_set_rabbish_can.end();)
			{
				qDebug() << (*it)->hostName() << " delete From the RabiishCan.";
				(*it)->deleteLater();
				it = m_set_rabbish_can.erase(it);
			}
		}

		bool SCItem::LBLSCItemManager::moveToRabiishCan(LBLAbstractSCItem *item)
		{
			//
			if (nullptr == item)
			{
				return false;
			}
			if (containsInUsing(item->getDetectInfoStruct()))
			{
				//设备正常使用，不放入垃圾桶
				qDebug() << item->hostName() << " is using, do not add to the rabiishcan.";
				return false;
			}
			if (contains(item->getDetectInfoStruct()))
			{
				m_mutex_protect_rabbish.lock();
				m_set_rabbish_can.insert(item);//放入垃圾桶
				m_mutex_protect_rabbish.unlock();
				qDebug() << item->hostName() << " movet to the rabiishcan.";
				return true;
			}
			return false;
		}

		bool SCItem::LBLSCItemManager::restoreFormRabiishCan(LBLAbstractSCItem *item)
		{
			//
			if (nullptr == item)
			{
				return false;
			}
			if (contains(item->getDetectInfoStruct()))
			{
				//探卡队列中含有该设备，不恢复
				qDebug() << item->hostName() << " is in queen.";
				return false;
			}
			m_mutex_protect_rabbish.lock();
			if (m_set_rabbish_can.contains(item))
			{
				m_mutex_protect_rabbish.unlock();
				m_set_rabbish_can.remove(item);//从垃圾桶删除
				m_mutex_protect_itemList.lock();
				m_list_allItem.push_back(item);//放入探卡队列
				m_mutex_protect_itemList.unlock();
				qDebug() << item->hostName() << " Resotre From the rabiishcan.";
				return true;
			}
			m_mutex_protect_rabbish.unlock();
			return false;
		}

		LBLSCItemManager::LBLSCItemManager(QObject* parent/* = 0*/) :
			QObject(parent)
        {
			m_detectServer = new LBLDetectServer(this);
            connect(m_detectServer, &LBLDetectServer::sig_StartDetect, this, &LBLSCItemManager::sig_StartDetect);
			connect(m_detectServer, &LBLDetectServer::sig_DetectComplite, this, &LBLSCItemManager::slot_DetectComplit);
			connect(m_detectServer, &LBLDetectServer::sig_SingleDetectComplite, this, &LBLSCItemManager::sig_SingleDetectComplite);
			connect(m_detectServer, &LBLDetectServer::sig_DisconnectFromCOM, this, &LBLSCItemManager::slot_DisconnectFromCOM);
			if (false == QMetaType::isRegistered(QMetaType::type("SDetectItemInfo")))
				qRegisterMetaType<SDetectItemInfo>("SDetectItemInfo");
#ifndef CVTE_SCOPEDPT
			static CGarbo Garbo;
#endif // CVTE_SCOPEDPT
		}
	}
}
