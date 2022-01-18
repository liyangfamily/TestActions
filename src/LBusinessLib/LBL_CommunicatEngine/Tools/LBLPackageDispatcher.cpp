/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/

/*!
\class LBLPackageDispatcher

\inmodule LBL_CommunicatEngine

\brief The LBLPackageDispatcher class responsible for distributing the data packets parsed by the communication library to all registered objects.

\code
	qDispatcher->registerTransitObject(this);
	or
	LBLPackageInteCtrl_DetectInfo pack;
	qDispatcher->registerDispatcherPackage(pack,this);
\endcode

\note:
LBLPackageDispatcher use QCoreApplication::postEvent pose LBLPackageEvent, packge data in a event.
LBLPackageDispatcher::dispatcherPackage() this function will determine the protocol number and CMD number in the package to find corresponding registered objcets.
LBLPackageDispatcher::transitPackage this function will directly forwards the package data to the corresponding objects.
*/

#include "LBL_CommunicatEngine/LBLPackageDispatcher.h"
#include "LBL_CommunicatEngine/LBLCluster.h"
 
#include <QCoreApplication>

LBLPackageDispatcher::LBLPackageDispatcher(QObject *parent)
	: QObject(parent)
{
	connect(gCluster, &LBLCluster::sig_ParsingInteCtrlDataFrame, this, &LBLPackageDispatcher::slot_ParsingInteCtrlDataFrame);
}

LBLPackageDispatcher::~LBLPackageDispatcher()
{
}

LBLPackageDispatcher * LBLPackageDispatcher::instance()
{
	static LBLPackageDispatcher m_global_dispatcher;
	return &m_global_dispatcher;
}

//void LBLPackageDispatcher::unregisterDispatcherPackage(LBLPackage package, QObject* obj)
//{
//	QMutexLocker locker(&m_mutex_protect);
//	quint8 protocolNum = package.CmdProtocolNum();
//	quint16 cmdNum = package.CmdNum();
//	ProtocolMap::iterator iProtocolMap = m_maps.find(protocolNum);
//	if (iProtocolMap != m_maps.end()) {
//		CmdMap::iterator iCmdNumber = iProtocolMap.value().find(cmdNum);
//		if (iCmdNumber != iProtocolMap.value().end()) {
//			iCmdNumber->removeOne(obj);
//		}
//	}
//}

void LBLPackageDispatcher::unregisterAllDispatcherPackage()
{
	QMutexLocker locker(&m_mutex_protect);
	ProtocolMap::iterator iMaps = m_maps.begin();
	while (iMaps != m_maps.end()) {
		CmdMap::iterator iCmdNumber = iMaps.value().begin();
		while (iCmdNumber != iMaps.value().end()) {
			iCmdNumber->clear();
			iMaps.value().erase(iCmdNumber++);
		}
		m_maps.erase(iMaps++);
	}
}

bool LBLPackageDispatcher::registerTransitObject(QObject* transitObj)
{
	QMutexLocker locker(&m_mutex_protect);
	if (m_transitObjList.contains(transitObj))
	{
		return false;
	}
	else
	{
		m_transitObjList.append(transitObj);
		return true;
	}
}

void LBLPackageDispatcher::unregisterTransitObject(QObject* transitObj)
{
	QMutexLocker locker(&m_mutex_protect);
	if (m_transitObjList.contains(transitObj))
	{
		m_transitObjList.removeOne(transitObj);
	}
}

void LBLPackageDispatcher::unregisterAllTransitObject()
{
	QMutexLocker locker(&m_mutex_protect);
	m_transitObjList.clear();
}

bool LBLPackageDispatcher::dispatcherPackage(const LBLEnginePackage &package)
{
	LBLPackage tempPackage(package.data());

	quint8 protocolNum = tempPackage.getProtocolNum();
	quint16 cmdNum = tempPackage.getCmdNum();

	ProtocolMap::iterator iMaps = m_maps.find(protocolNum);
	if (iMaps != m_maps.end()) {
		CmdMap::iterator iCmdNumber = iMaps.value().find(cmdNum);
		if (iCmdNumber != iMaps.value().end()) {
			QList<QObject*>& objList = iCmdNumber.value();
			foreach(QObject* item, objList)
			{
				LBLPackageEvent *event = new LBLPackageEvent(LBLPackageEvent::s_disPatcherPackage_eventType, protocolNum, cmdNum);
				event->setSourceDevice(tempPackage.getSourceDevice());
				event->setPackage(package);
				QCoreApplication::postEvent(item, event);
			}
			//qDebug() << "LBLPackageDispatcher" << QString("handle cmd number : %1 .").arg(QString::number(cmdNum, 16));
			return true;
		}
		else {
			//qDebug() << "LBLPackageDispatcher" << QString("unknown cmd number : %1 ").arg(QString::number(cmdNum, 16));
			return false;
		}
	}
	else {
		//qDebug() << "LBLPackageDispatcher" << QString("unknown protocol name : %1 ").arg(protocolNum);
		return false;
	}
}

bool LBLPackageDispatcher::transitPackage(const LBLEnginePackage &package)
{
	foreach(QObject* item, m_transitObjList)
	{
		LBLPackageEvent *event = new LBLPackageEvent(LBLPackageEvent::s_transitPackage_eventType);
		event->setPackage(package);
		QCoreApplication::postEvent(item, event);
	}
	return true;
}
#include <QTime>
#include <LBL_Core/LBLUIHelper>
void LBLPackageDispatcher::slot_ParsingInteCtrlDataFrame(QObject* objSocket, LBLEnginePackage pack)
{
    if(LBLUIHelper::enableCommunicatLog()){
        QString frame;
        frame = LBLUIHelper::byteArrayToHexStr(pack.data());
        qInfo()<<QString("RX:Host:%2, Length:%3, Data:%4").arg(pack.hostName()).arg(pack.data().size()).arg(frame);
    }
    Q_UNUSED(objSocket)
	//转发包，让对应的对象去处理
	this->transitPackage(pack);
	//分发包，处理后分发给关注的object
	this->dispatcherPackage(pack);
}

