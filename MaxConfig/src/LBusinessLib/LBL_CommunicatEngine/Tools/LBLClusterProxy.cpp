/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/

/*!
\class LBLClusterProxy

\inmodule LBL_CommunicatEngine

\brief The LBLClusterProxy class proxy the behavior of the  communication library uses a synchronous or asynchronous method.

\code
	LBLEnginePackage pack(item->socketObject(), EPackageType::EPT_UDP);
	pack.setNetInfo(item->netInfo().ipAddr, item->netInfo().port);
	pack.setData(writeData);
	LBLEnginePackage recPack;
	LBLClusterProxy::syncSend(pack, recPack);
\endcode

\note:
LBLCLusterProxy::asyncSend can't get the return result pass the callback function temporarily in the current design. if you want get return result,
maybe you can refer to class LBLPackageEvent and class LBLPackageDispatcher inmodule LBL_CommunicatEngine.
*/

#include "LBL_CommunicatEngine/LBLClusterProxy.h"
#include "LBL_CommunicatEngine/LBLSocketLock.h"

#include "LBL_CommunicatEngine/LBLCluster.h"

QMutex LBLClusterProxy::m_mutex_protect;
QMutex LBLClusterProxy::m_exclusive_protect;
QMap<QString, QUuid> LBLClusterProxy::m_hash_exclusiveHostName;

LBLClusterProxy::~LBLClusterProxy()
{
}

bool LBLClusterProxy::syncSend(const LBLEnginePackage& sendPack, LBLEnginePackage& recPack, int mesc/* = 1500*/,bool force/*=false*/)
{
	if (isItemExlusive(sendPack.hostName())) {
		qDebug() << QString("SyncSend====(%1)..is in Exclusive.").arg(sendPack.hostName());
		return false;
	}
	if (!m_mutex_protect.try_lock()) {
		qDebug() << "LBLClusterProxy::syncSend Lock Failed.";
		return false;
	}
	LBLSyncWaiter syncLocker(sendPack);
	gCluster->slot_SendData(sendPack.socketObj(), sendPack);
	if (syncLocker.syncLock(mesc, force))
	{
		m_mutex_protect.unlock();
		recPack = syncLocker.syncRecPackage();
		return true;
	}
	else
	{
		m_mutex_protect.unlock();
		qDebug() << "Timed out while waiting on syncSend(). hostName:" << sendPack.hostName();
		return false;
	}
}

bool LBLClusterProxy::exclusiveSyncSend(const LBLEnginePackage & sendPack, LBLEnginePackage & recPack, int mesc, bool force)
{
	if (isItemExlusive(sendPack.hostName())) {
		if (sendPack.exclusiveKey() != m_hash_exclusiveHostName[sendPack.hostName()]) {
			qDebug() << QString("%1 Exclusive key not matched.").arg(sendPack.hostName());
			return false;
		}
	}
	LBLSyncWaiter syncLocker(sendPack);
	gCluster->slot_SendData(sendPack.socketObj(), sendPack);
	if (syncLocker.syncLock(mesc, force))
	{
		recPack = syncLocker.syncRecPackage();
		return true;
	}
	else
	{
		qDebug() << "Timed out while waiting on syncSend(). hostName:" << sendPack.hostName();
		return false;
	}
}

bool LBLClusterProxy::asyncSend(const LBLEnginePackage& sendPack)
{
	if (isItemExlusive(sendPack.hostName())) {
		qDebug() << QString("SyncSend====(%1)..is in Exclusive.").arg(sendPack.hostName());
		return false;
	}
	if (sendPack.isEmpty() || nullptr == sendPack.socketObj())
		return false;
	return gCluster->slot_SendData(sendPack.socketObj(), sendPack);
}

QUuid LBLClusterProxy::setItemExlusive(QString hostName, bool enable)
{
	m_exclusive_protect.lock(); 
	QUuid id;
	if (enable) {
		id = QUuid::createUuid();
		m_hash_exclusiveHostName[hostName] = id;
	}
	else{
		id = QUuid();
		m_hash_exclusiveHostName.remove(hostName);
	}
	m_exclusive_protect.unlock();
	return id;
}

bool LBLClusterProxy::isItemExlusive(QString hostName)
{
	QMutexLocker m_locker(&m_exclusive_protect);
	return m_hash_exclusiveHostName.contains(hostName);
}
