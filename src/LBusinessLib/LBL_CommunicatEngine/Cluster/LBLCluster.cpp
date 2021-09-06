/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/

/*!
\class LBLCluster

\inmodule LBL_CommunicatEngine

\brief The class is the cluster management class of the communication library.

\code

\endcode

\note:

*/

#include "LBL_CommunicatEngine/LBLCluster.h"
#include "LBL_TaskEngine_IntegratedCtrlTask.h"
#include "../LBL_CommunicatEngine/NetEngine/LBL_NetEngine.h"
#include "../LBL_CommunicatEngine/TaskEngine/LBL_TaskEngine.h"

LBLCluster::LBLCluster(QObject *parent)
	: QObject(parent)
{
	qDebug() << __FUNCTION__;
	m_pNetEngine = new LBL_NetEngine(4096, this);
	m_pTaskEngine = new LBL_TaskEngine(this);
	connect(m_pNetEngine, &LBL_NetEngine::sig_Message, this, &LBLCluster::sig_Message, Qt::QueuedConnection);

	connect(m_pNetEngine, QOverload<QObject*, QAbstractSocket::SocketError>::of(&LBL_NetEngine::sig_SocketError),
		this, QOverload<QObject*, QAbstractSocket::SocketError>::of(&LBLCluster::sig_SocketError), Qt::QueuedConnection);
	connect(m_pNetEngine, QOverload<QObject*, QSerialPort::SerialPortError>::of(&LBL_NetEngine::sig_SocketError),
		this, QOverload<QObject*, QSerialPort::SerialPortError>::of(&LBLCluster::sig_SocketError), Qt::QueuedConnection);

	connect(m_pNetEngine, &LBL_NetEngine::sig_SendData, this, &LBLCluster::sig_SendedDataSteam, Qt::QueuedConnection);
	connect(m_pNetEngine, &LBL_NetEngine::sig_Data_Received, this, &LBLCluster::slot_Data_Received, Qt::QueuedConnection);
	connect(m_pNetEngine, &LBL_NetEngine::sig_Data_Sended, this, &LBLCluster::slot_Data_Sended, Qt::QueuedConnection);
	connect(m_pNetEngine, &LBL_NetEngine::sig_SocketAbort, this, &LBLCluster::slot_SocketAbort, Qt::QueuedConnection);
	
	connect(m_pNetEngine, QOverload<QObject*, const QString&, quint16>::of(&LBL_NetEngine::sig_NewUDPConnectionEstablish),
		this, QOverload<QObject*, const QString&, quint16>::of(&LBLCluster::slot_NewUDPConnectionEstablish), Qt::QueuedConnection);
	connect(m_pNetEngine, QOverload<QObject*, QString>::of(&LBL_NetEngine::sig_NewCOMConnectionEstablish),
		this, QOverload<QObject*, QString>::of(&LBLCluster::slot_NewCOMConnectionEstablish), Qt::QueuedConnection);

	m_nHeartBeatingTime = 20;
}

LBLCluster::~LBLCluster()
{
	qDebug() << __FUNCTION__;
	/*if (m_pNetEngine)
		m_pNetEngine->deleteLater();
	if (m_pTaskEngine)
		m_pTaskEngine->deleteLater();*/
}

LBLCluster * LBLCluster::instance()
{
	static LBLCluster m_global_Cluster;
	return &m_global_Cluster;
}

LBL_NetEngine * LBLCluster::netEngine()
{
	return m_pNetEngine;
}

LBL_TaskEngine * LBLCluster::taskEngine()
{
	return m_pTaskEngine;
}

int LBLCluster::heartBeatingThrdHold()
{
	return m_nHeartBeatingTime;
}

void LBLCluster::setHeartBeatingThrd(const int n)
{
	m_nHeartBeatingTime = n;
}

bool LBLCluster::isSocketInExclusive(QObject* objSocket)
{
	bool bRet = false;
	m_mutex_ExclusiveLock.lock();
	if (m_hash_sockExclusive.contains(objSocket))
	{
		bRet = m_hash_sockExclusive[objSocket].isNull() ? false : true;
	}
	m_mutex_ExclusiveLock.unlock();
	return bRet;
}

QUuid LBLCluster::exclusiveKey(QObject* objSocket)
{
	QUuid id;
	m_mutex_ExclusiveLock.lock();
	if (m_hash_sockExclusive.contains(objSocket))
	{
		id = m_hash_sockExclusive[objSocket];
	}
	m_mutex_ExclusiveLock.unlock();
	return id;
}

void LBLCluster::readyToExit()
{
	this->netEngine()->deactiveImmediately();
}

bool LBLCluster::canExit()
{
	bool bRet = false;
	m_hash_mutex.lock();
	if (this->m_nodeToBeDel.isEmpty()&& this->m_hash_sock2node.isEmpty()) {
		this->taskEngine()->removeThreads(-1);
		bRet = m_pNetEngine->canExit() && m_pTaskEngine->canExit();
	}
	else {
		QList <LBL_TaskEngine_TaskBase *> toBedel;
		foreach(LBL_TaskEngine_TaskBase * pdelobj, m_nodeToBeDel)
		{
			if (pdelobj->ref() == 0)
				toBedel.push_back(pdelobj);
			else
			{
				qDebug() << QString("LBL_TaskEngine_TaskBase %1(ref %2) Waiting in del queue.").arg((quint64)pdelobj).arg(pdelobj->ref());
			}
		}
		foreach(LBL_TaskEngine_TaskBase * pdelobj, toBedel)
		{
			m_nodeToBeDel.removeAll(pdelobj);
			qDebug() << QString("LBL_TaskEngine_TaskBase %1(ref %2) deleting.").arg((quint64)pdelobj).arg(pdelobj->ref());
			pdelobj->deleteLater();
		}
	}
	m_hash_mutex.unlock();
	return bRet;
}

void LBLCluster::slot_SocketAbort(QObject * clientHandle)
{
	bool nHashContains = false;

	LBL_TaskEngine_TaskBase * pClientTask = 0;
	m_hash_mutex.lock();
	nHashContains = m_hash_sock2node.contains(clientHandle);
	if (nHashContains)
		pClientTask = m_hash_sock2node[clientHandle];
	if (pClientTask)
	{
		disconnect(pClientTask, &LBL_TaskEngine_TaskBase::sig_SendData, m_pNetEngine, &LBL_NetEngine::sig_SendData);
		disconnect(pClientTask, QOverload<const QString&, quint16>::of(&LBL_TaskEngine_TaskBase::sig_ConnectToUDP),
			m_pNetEngine, QOverload<const QString&, quint16>::of(&LBL_NetEngine::slot_ConnectToUDP));
		disconnect(pClientTask, QOverload<QString>::of(&LBL_TaskEngine_TaskBase::sig_ConnectToCOM),
			m_pNetEngine, QOverload<QString>::of(&LBL_NetEngine::slot_ConnectToCOM));
		disconnect(pClientTask, &LBL_TaskEngine_TaskBase::sig_Disconnect, m_pNetEngine, &LBL_NetEngine::sig_Disconnect);
		disconnect(pClientTask, &LBL_TaskEngine_TaskBase::sig_Message, this, &LBLCluster::sig_Message);
		disconnect(pClientTask, &LBL_TaskEngine_TaskBase::sig_ParsingInteCtrlDataFrame, this, &LBLCluster::sig_ParsingInteCtrlDataFrame);

		m_hash_sock2node.remove(clientHandle);
		m_hash_Name2node.remove(pClientTask->hostName());
		
		m_nodeToBeDel.push_back(pClientTask);
		emit sig_SocketAbort(clientHandle);
	}
	m_hash_mutex.unlock();

	//Try to delete objects
	QList <LBL_TaskEngine_TaskBase *> toBedel;
	foreach(LBL_TaskEngine_TaskBase * pdelobj, m_nodeToBeDel)
	{
		if (pdelobj->ref() == 0) {
			toBedel.push_back(pdelobj);
		}
		else
		{
			qDebug()<<QString("LBL_TaskEngine_TaskBase %1(ref %2) Waiting in del queue.").arg((quint64)pdelobj).arg(pdelobj->ref());
		}
	}
	foreach(LBL_TaskEngine_TaskBase * pdelobj, toBedel)
	{
		m_nodeToBeDel.removeAll(pdelobj);
		qDebug()<<QString("LBL_TaskEngine_TaskBase %1(ref %2) deleting.").arg((quint64)pdelobj).arg(pdelobj->ref());
		pdelobj->deleteLater();
	}
}

void LBLCluster::slot_Data_Received(QObject * clientHandle, LBLEnginePackage datablock)
{
	bool nHashContains = false;
	LBL_TaskEngine_TaskBase * pClientTask = 0;
	m_hash_mutex.lock();
	nHashContains = m_hash_sock2node.contains(clientHandle);
	if (false == nHashContains)
	{
		//后续改成工厂模式创建，在此处如果收到不包含在表中socket的内容，就新建一个任务
		LBL_TaskEngine_TaskBase * pnode = new LBL_TaskEngine_IntegratedCtrlTask(this, clientHandle, this);
		//using queued connection of send and revieve;
		connect(pnode, &LBL_TaskEngine_TaskBase::sig_SendData, m_pNetEngine, &LBL_NetEngine::sig_SendData, Qt::QueuedConnection);
		connect(pnode, QOverload<const QString&, quint16>::of(&LBL_TaskEngine_TaskBase::sig_ConnectToUDP),
			m_pNetEngine, QOverload<const QString&, quint16>::of(&LBL_NetEngine::slot_ConnectToUDP), Qt::QueuedConnection);
		connect(pnode, QOverload<QString>::of(&LBL_TaskEngine_TaskBase::sig_ConnectToCOM),
			m_pNetEngine, QOverload<QString>::of(&LBL_NetEngine::slot_ConnectToCOM), Qt::QueuedConnection);
		connect(pnode, &LBL_TaskEngine_TaskBase::sig_Disconnect, m_pNetEngine, &LBL_NetEngine::sig_Disconnect, Qt::QueuedConnection);
		connect(pnode, &LBL_TaskEngine_TaskBase::sig_Message, this, &LBLCluster::sig_Message, Qt::QueuedConnection);
		connect(pnode, &LBL_TaskEngine_TaskBase::sig_ParsingInteCtrlDataFrame, this, &LBLCluster::sig_ParsingInteCtrlDataFrame, Qt::QueuedConnection);
		m_hash_sock2node[clientHandle] = pnode;
		nHashContains = true;
		pClientTask = pnode;
	}
	else
	{
		pClientTask = m_hash_sock2node[clientHandle];
	}
	assert(nHashContains != 0 && pClientTask != 0);
	int nblocks = pClientTask->push_new_data(datablock);
	if (nblocks <= 1)
		m_pTaskEngine->slot_pushTask(pClientTask);
	m_hash_mutex.unlock();
}

void LBLCluster::slot_Data_Sended(QObject * clientHandle, qint64 bytesSend)
{
	emit sig_Data_Sended(clientHandle, bytesSend);
}

void LBLCluster::slot_NewUDPConnectionEstablish(QObject* clientHandle, const QString& addr, quint16 port)
{
	bool nHashContains = false;
	LBL_TaskEngine_TaskBase * pClientTask = 0;
	m_hash_mutex.lock();
	nHashContains = m_hash_sock2node.contains(clientHandle);
	if (false == nHashContains)
	{
		//后续根据端口号不同new不同的Task，使用简单工厂即可
		LBL_TaskEngine_IntegratedCtrlUDPTask * pnode = new LBL_TaskEngine_IntegratedCtrlUDPTask(this, clientHandle, this);
		QString hostName = LBLEnginePackage::genHostName(addr, port);
		pnode->setHostName(hostName);
		qDebug() << "New Connection. IP:" << addr << " Port:" << port;
		connect(pnode, &LBL_TaskEngine_TaskBase::sig_SendData, m_pNetEngine, &LBL_NetEngine::sig_SendData, Qt::QueuedConnection);
		connect(pnode, QOverload<const QString&, quint16>::of(&LBL_TaskEngine_TaskBase::sig_ConnectToUDP),
			m_pNetEngine, QOverload<const QString&, quint16>::of(&LBL_NetEngine::slot_ConnectToUDP), Qt::QueuedConnection);
		/*connect(pnode, QOverload<QString>::of(&LBL_TaskEngine_TaskBase::sig_ConnectToCOM),
			m_pNetEngine, QOverload<QString>::of(&LBL_NetEngine::slot_ConnectToCOM), Qt::QueuedConnection);*/
		connect(pnode, &LBL_TaskEngine_TaskBase::sig_Disconnect, m_pNetEngine, &LBL_NetEngine::sig_Disconnect, Qt::QueuedConnection);
		connect(pnode, &LBL_TaskEngine_TaskBase::sig_Message, this, &LBLCluster::sig_Message, Qt::QueuedConnection);
		connect(pnode, &LBL_TaskEngine_TaskBase::sig_ParsingInteCtrlDataFrame, this, &LBLCluster::sig_ParsingInteCtrlDataFrame, Qt::QueuedConnection);
		m_hash_sock2node[clientHandle] = pnode;
		m_hash_Name2node[hostName] = pnode;
		nHashContains = true;
		pClientTask = pnode;
	}
	else
	{
		pClientTask = m_hash_sock2node[clientHandle];
	}
	m_hash_mutex.unlock();
	Q_ASSERT(nHashContains != 0 && pClientTask != 0);
	emit sig_NewUDPConnectionEstablish(clientHandle, addr, port);
}

void LBLCluster::slot_NewCOMConnectionEstablish(QObject* clientHandle, QString comName)
{
	bool nHashContains = false;
	LBL_TaskEngine_TaskBase * pClientTask = 0;
	m_hash_mutex.lock();
	nHashContains = m_hash_sock2node.contains(clientHandle);
	if (false == nHashContains)
	{
		LBL_TaskEngine_TaskBase * pnode = new LBL_TaskEngine_IntegratedCtrlCOMTask(this, clientHandle, this);
		QString hostName = LBLEnginePackage::genHostName(comName); 
		pnode->setHostName(hostName);
		qDebug() << "New Connection. COM:" << comName;
		//using queued connection of send and revieve;
		connect(pnode, &LBL_TaskEngine_TaskBase::sig_SendData, m_pNetEngine, &LBL_NetEngine::sig_SendData, Qt::QueuedConnection);
		/*connect(pnode, QOverload<const QHostAddress&, quint16>::of(&LBL_TaskEngine_TaskBase::sig_ConnectToUDP),
			m_pNetEngine, QOverload<const QHostAddress&, quint16>::of(&LBL_NetEngine::slot_ConnectToUDP), Qt::QueuedConnection);*/
		connect(pnode, QOverload<QString>::of(&LBL_TaskEngine_TaskBase::sig_ConnectToCOM),
			m_pNetEngine, QOverload<QString>::of(&LBL_NetEngine::slot_ConnectToCOM), Qt::QueuedConnection);
		connect(pnode, &LBL_TaskEngine_TaskBase::sig_Disconnect, m_pNetEngine, &LBL_NetEngine::sig_Disconnect, Qt::QueuedConnection);
		connect(pnode, &LBL_TaskEngine_TaskBase::sig_Message, this, &LBLCluster::sig_Message, Qt::QueuedConnection);
		connect(pnode, &LBL_TaskEngine_TaskBase::sig_ParsingInteCtrlDataFrame, this, &LBLCluster::sig_ParsingInteCtrlDataFrame, Qt::QueuedConnection);
		m_hash_sock2node[clientHandle] = pnode;
		m_hash_Name2node[hostName] = pnode;
		nHashContains = true;
		pClientTask = pnode;
	}
	else
	{
		pClientTask = m_hash_sock2node[clientHandle];
	}
	m_hash_mutex.unlock();
	Q_ASSERT(nHashContains != 0 && pClientTask != 0);
	emit sig_NewCOMConnectionEstablish(clientHandle, comName);
}

bool LBLCluster::slot_SendData(QObject * objSocket, LBLEnginePackage pack)
{
	m_hash_mutex.lock();
	if (m_hash_sock2node.contains(objSocket))
	{
		if (this->isSocketInExclusive(objSocket))
		{
			QUuid id = exclusiveKey(objSocket);
			if (id == pack.exclusiveKey())
			{
				netEngine()->slot_SendData(objSocket, pack);
				m_hash_mutex.unlock();
				return true;
			}
			else
			{
				qDebug() << tr("(%1)..is in Exclusive.").arg((quint64)objSocket);
				m_hash_mutex.unlock();
				return false;
			}
		}
		else
		{
			netEngine()->slot_SendData(objSocket, pack);
			m_hash_mutex.unlock();
			return true;
		}
	}
	m_hash_mutex.unlock();
	return false;
}

void LBLCluster::slot_Disconnect(QObject * objSocket)
{
	m_hash_mutex.lock();
	if (m_hash_sock2node.contains(objSocket))
		netEngine()->slot_Disconnect(objSocket);
	m_hash_mutex.unlock();
}

bool LBLCluster::slot_ConnectToUDP(const QString & address, quint16 nPort)
{
	QString hostName = LBLEnginePackage::genHostName(address, nPort);
	if (m_hash_Name2node.contains(hostName))
	{
		qDebug() << hostName << ", connection already existing.";
		return false;
	}
	return netEngine()->slot_ConnectToUDP(address, nPort);
}

bool LBLCluster::slot_ConnectToCOM(QString comName)
{
	QString hostName = LBLEnginePackage::genHostName(comName);
	if (m_hash_Name2node.contains(hostName))
	{
		qDebug() << hostName << ", connection already existing.";
		return false;
	}
	return netEngine()->slot_ConnectToCOM(comName);
}

void LBLCluster::slot_SendHelloPackage()
{
	m_hash_mutex.lock();
	for (QMap<QObject *, LBL_TaskEngine_TaskBase *>::iterator p = m_hash_sock2node.begin();
		p != m_hash_sock2node.end(); p++)
	{
		if (!isSocketInExclusive(p.key()))
			p.value()->sendHelloPackage();
	}
	m_hash_mutex.unlock();
}

void LBLCluster::slot_KickDeadClients()
{
	m_hash_mutex.lock();
	for (QMap<QObject *, LBL_TaskEngine_TaskBase *>::iterator p = m_hash_sock2node.begin();
		p != m_hash_sock2node.end(); p++)
	{
		p.value()->checkHeartBeating();
	}
	m_hash_mutex.unlock();
}

void LBLCluster::slot_SetSocketExlusive(QObject* objSocket, bool enable)
{
	m_hash_mutex.lock();
	if (m_hash_sock2node.contains(objSocket))
	{
		m_mutex_ExclusiveLock.lock();
		QUuid id;
		if (enable)
		{
			id = QUuid::createUuid();
			m_hash_sockExclusive[objSocket] = id;
		}
		else
		{
			id = QUuid();
			m_hash_sockExclusive[objSocket] = id;
		}
		m_mutex_ExclusiveLock.unlock();
		emit sig_ExlusiveLocked(objSocket, enable, id);
	}
	m_hash_mutex.unlock();
}
