/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBLPACKAGEDISPATCHER
#define CVTE_H_LBLPACKAGEDISPATCHER
#pragma once
#include <LBL_CommunicatEngine/LBLInteCtrlPackage>
#include <LBL_CommunicatEngine/LBLFileTransferPackage>
#include <LBL_CommunicatEngine/LBLPackageEvent>

#include <QByteArray>
#include <QObject>
#include <QMap>
#include <QList>
#include <QMutex>
#include <QMutexLocker>

#define gDispatcher LBLPackageDispatcher::instance()

class LBL_COMMUNICATENGINE_EXPORT LBLPackageDispatcher : public QObject
{
	Q_OBJECT

public:
	typedef QMap<quint16, QList<QObject *>> CmdMap;
	typedef QMap<quint8, CmdMap> ProtocolMap;
	LBLPackageDispatcher(QObject *parent = nullptr);
	~LBLPackageDispatcher();
	 
	static LBLPackageDispatcher *instance();

	//register CMD
	template <class T>
	bool registerDispatcherPackage(const T &package, QObject* obj)
	{
		QMutexLocker locker(&m_mutex_protect);
		quint8 protocolNum = package.CmdProtocolNum();
        quint16 cmdNum = package.CmdRetNum();
		ProtocolMap::iterator iProtocolMap = m_maps.find(protocolNum);
		if (iProtocolMap != m_maps.end()) {
			CmdMap::iterator iCmdNumber = iProtocolMap.value().find(cmdNum);
			if (iCmdNumber != iProtocolMap.value().end()) {
				if (iCmdNumber->contains(obj))
				{
					qDebug() << "LBLPackageDispatcher" <<
						QString("registerPackage failed cmd name : %1   cmd number : %2 is existed").arg(protocolNum).arg(QString::number(cmdNum, 16));
					return false;
				}
			}
		}

		m_maps[protocolNum][cmdNum].append(obj);
		return true;
	}

	template <class T>
	void unregisterDispatcherPackage(const T &package, QObject* obj)
	{
		QMutexLocker locker(&m_mutex_protect);
		quint8 protocolNum = package.CmdProtocolNum();
		quint16 cmdNum = package.CmdNum();
		ProtocolMap::iterator iProtocolMap = m_maps.find(protocolNum);
		if (iProtocolMap != m_maps.end()) {
			CmdMap::iterator iCmdNumber = iProtocolMap.value().find(cmdNum);
			if (iCmdNumber != iProtocolMap.value().end()) {
				iCmdNumber->removeOne(obj);
			}
		}
	}
	void unregisterAllDispatcherPackage();

	//register Object
	bool registerTransitObject(QObject* transitObj); 
	void unregisterTransitObject(QObject* transitObj);
	void unregisterAllTransitObject();

protected:
	bool dispatcherPackage(const LBLEnginePackage &package);
	bool transitPackage(const LBLEnginePackage &package);
protected slots:
	void slot_ParsingInteCtrlDataFrame(QObject* objSocket, LBLEnginePackage pack);
private:
	QMutex m_mutex_protect;
	//用于储存按协议号和指令号注册的通知对象
	ProtocolMap m_maps;
	//用于储存中转通知对象
	QList<QObject*> m_transitObjList;
};
#endif
