/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/

#include "LBL_CommunicatEngine/LBLSocketLock.h"
#include "LBL_CommunicatEngine/LBLPackageEvent.h"
#include "LBL_CommunicatEngine/LBLPackageDispatcher.h"
#include "LBL_CommunicatEngine/LBLPackage.h"
#include "LBL_CommunicatEngine/LBLCluster.h"

#include <LBL_Core/LBLSignalWaiter>

#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_Cored.lib")
#else
#pragma comment(lib,"LBL_Core.lib")
#endif
#endif
/*!
\class LBLSyncWaiter

\inmodule LBL_CommunicatEngine

\brief The class is based on the synchronization lock of the communication library implemented by LBLSignalWaiter.

\code
	LBLPackageInteCtrl_DetectInfo detectInfo;
	detectInfo.SetCmdTargetDevice(m_tagetDeviceType);
	detectInfo.build(0);
	QByteArray writeData = detectInfo.getDataToSend(); 

	SPackage pack(socketObj(), EPackageType::EPT_COM);
	QSerialPort* pSocket = qobject_cast<QSerialPort*>(socketObj());
	if (pSocket)
	{
		pack.setComName(pSocket->portName());
		pack.setData(writeData);
	}
	LBLSyncWaiter locker(pack);
	qCluster->slot_SendData(socketObj(), pack);
	if(locker.syncLock(5000)) {
		Spackage recPack=locker.syncRecPackage();
	} else {
		QMessageBox::information(0, "MyObject", "Timed out while waiting on longProcessFinished()", QMessageBox::Ok);
	}
\endcode

\note:
LBLSyncWaiter is not reentrant。
*/

LBLSyncWaiter::LBLSyncWaiter(LBLEnginePackage packInfo):
	m_socketObj(packInfo.socketObj()),m_syncPackage(packInfo)
{
	Q_ASSERT(m_socketObj);
	if (m_socketObj)
	{
		//connect(qCluster, &LBL_Cluster::sig_ParsingDataFrame, this, &LBLSyncWaiter::slot_ParsingDataFrame);
		gDispatcher->registerTransitObject(this);
	}
}

LBLSyncWaiter::~LBLSyncWaiter()
{
    //qDebug() << "LBLSyncWaiter unlocked.";
	gDispatcher->unregisterTransitObject(this);
}

bool LBLSyncWaiter::syncLock(int msec /*= 3000*/, bool force/* = false*/)
{
	m_forceWait = force;
	m_syncRecPackage = LBLEnginePackage();
	LBLSignalWaiter waiter(this, SIGNAL(sig_syncFinnish()));
	return waiter.wait(msec, force);
}

#include <QTimer>
bool LBLSyncWaiter::syncLockEventLoop(int msec /*= 3000*/)
{
    QEventLoop loop;
    QTimer outTimer;
    outTimer.setSingleShot(true);
    connect(&outTimer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(this, &LBLSyncWaiter::sig_syncFinnish, &loop, &QEventLoop::quit);
    outTimer.start(msec); // 超时
    loop.exec();
    if(outTimer.isActive()){
        outTimer.stop();
        return true;
    }
    else{
        outTimer.stop();
        return false;
    }
}

LBLEnginePackage LBLSyncWaiter::syncRecPackage()
{
	return m_syncRecPackage;
}

bool LBLSyncWaiter::event(QEvent * e)
{
	if (e->type() == LBLPackageEvent::s_transitPackage_eventType)
	{
		LBLPackageEvent *tempE = static_cast<LBLPackageEvent*>(e);
		slot_ParsingDataFrame(tempE->package().socketObj(), tempE->package());
	}
	return QObject::event(e);
}

void LBLSyncWaiter::slot_ParsingDataFrame(QObject *psource, LBLEnginePackage dataFrame)
{
	if (psource != m_socketObj)
		return;
	if (dataFrame.hostName() != m_syncPackage.hostName())
		return;
	LBLPackage syncPack(m_syncPackage.data());
	LBLPackage recPack(dataFrame.data());
#if 1//改过后的流水号
	if (syncPack.getProtocolNum() == recPack.getProtocolNum() &&
		syncPack.getSerialNum() == recPack.getSerialNum() &&
		syncPack.getCmdNum() == recPack.getCmdNum() - 1)
	{
		if (!m_forceWait) {
			emit sig_syncFinnish();
		}
		m_syncRecPackage = dataFrame;
	}
#else
	if (syncPack.getProtocolNum() == recPack.getProtocolNum() &&
		syncPack.getCmdNum() == recPack.getCmdNum() - 1)
	{
		if (syncPack.getTargetDevice() != LBLPackage::EDeviceType::EDT_MCU_In_Sender) {
			if (syncPack.getSerialNum() != recPack.getSerialNum()) {
				return;
			}
		}
		else {
			if (syncPack.getSerialNum() + 1 != recPack.getSerialNum()) {
				return;
			}
		}
		if (!m_forceWait) {
			emit sig_syncFinnish();
		}
		m_syncRecPackage = dataFrame;
	}
#endif
}

/*********************************************************************************************************/

/*!
\class LBLSocketExclusiveLock

\inmodule LBL_CommunicatEngine

\brief The class is based on the socket Exclusive lock of the communication library implemented by LBLSignalWaiter.

LBLSocketExclusiveLock::autolock():when it returns true, you can get the exclusive key.

\code
	LBLSocketExclusiveLock locker(socketObj);
	if(locker.autoLock(5000)) {
		QUuid exclusiveKey=locker.exclusiveKey();
		for(int i=0;i<1000;++i)
		{
			SPackage tempPack(QByteArray());
			tempPack.setExclusiveKey(exclusiveKey);
			qCluster->slot_SendData(socketObj,tempPack);
		}
	} else {
		QMessageBox::information(0, "MyObject", "Timed out while waiting on longProcessFinished()", QMessageBox::Ok);
	}
\endcode

\note:
LBLSocketExclusiveLock is not reentrant。
*/

LBLSocketExclusiveLock::LBLSocketExclusiveLock(QObject * socketObj):
	m_socketObj(socketObj)
{
	Q_ASSERT(m_socketObj);
	connect(gCluster, &LBLCluster::sig_ExlusiveLocked, this, &LBLSocketExclusiveLock::slot_TransThreadLocked, Qt::QueuedConnection);
}

LBLSocketExclusiveLock::~LBLSocketExclusiveLock()
{
	gCluster->slot_SetSocketExlusive(m_socketObj, false);
    //qDebug() << "LBLItemExclusiveLock unlocked.";
}

bool LBLSocketExclusiveLock::autoLock(int msec)
{
	m_exclusiveUuid = QUuid();
	LBLSignalWaiter waiter(this, SIGNAL(sig_locked()));
	//通知去锁
	gCluster->slot_SetSocketExlusive(m_socketObj, true);
	return waiter.wait(msec);
}

QUuid LBLSocketExclusiveLock::exclusiveKey()
{
	return m_exclusiveUuid;
}

void LBLSocketExclusiveLock::slot_TransThreadLocked(QObject * objSocket, bool bStatus, QUuid uuid)
{
	if (objSocket != m_socketObj)
	{
		return;
	}
	if (bStatus)
	{
		m_exclusiveUuid = uuid;
		emit sig_locked();
		qDebug() << "LBLItemExclusiveLock locked.";
	}
}


LBLItemExclusiveLock::LBLItemExclusiveLock(QString hostName) :
	m_hostName(hostName)
{
}

LBLItemExclusiveLock::~LBLItemExclusiveLock()
{
	LBLClusterProxy::setItemExlusive(m_hostName, false);
    //qDebug() << "LBLItemExclusiveLock unlocked.";
}

bool LBLItemExclusiveLock::autoLock()
{
	m_exclusiveUuid = QUuid();
	//通知去锁
	m_exclusiveUuid = LBLClusterProxy::setItemExlusive(m_hostName, true);
	return !m_exclusiveUuid.isNull();
}

QUuid LBLItemExclusiveLock::exclusiveKey()
{
	return m_exclusiveUuid;
}
