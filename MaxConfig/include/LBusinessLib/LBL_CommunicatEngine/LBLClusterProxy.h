/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.                                                                     
*********************************************************************************************************/
#ifndef CVTE_H_LBLCLUSTERPROXY
#define CVTE_H_LBLCLUSTERPROXY
#pragma once

#include <LBL_CommunicatEngine/LBLCommunicatEngineGlobal>
#include <LBL_CommunicatEngine/LBLEnginePackage>

#include <QMutex>
#include <QMap>
#include <QString>
#include <QUuid>

class LBL_COMMUNICATENGINE_EXPORT LBLClusterProxy: public QObject
{
	friend class LBLItemExclusiveLock;
public:
	~LBLClusterProxy();

	static bool syncSend(const LBLEnginePackage& sendPack, LBLEnginePackage& recPack, int mesc = LBL_Defalut_SyncTimeout, bool force = false);
	static bool exclusiveSyncSend(const LBLEnginePackage& sendPack, LBLEnginePackage& recPack, int mesc = LBL_Defalut_SyncTimeout, bool force = false);
	static bool asyncSend(const LBLEnginePackage& sendPack);

protected:
	static QUuid setItemExlusive(QString hostName, bool enable);
	static bool isItemExlusive(QString hostName);
private:
	static QMutex m_mutex_protect;
	static QMutex m_exclusive_protect;
	static QMap<QString, QUuid> m_hash_exclusiveHostName;

};
#endif 
