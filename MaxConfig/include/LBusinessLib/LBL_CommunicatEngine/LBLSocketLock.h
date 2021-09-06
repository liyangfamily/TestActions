/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBLSOCKETLOCK
#define CVTE_H_LBLSOCKETLOCK
#pragma once

#include <LBL_CommunicatEngine/LBLEnginePackage>
#include <LBL_CommunicatEngine/LBLClusterProxy>

#include <QObject>
#include <QMutex>
#include <QUuid>
#include <QEvent>


class LBL_COMMUNICATENGINE_EXPORT LBLSyncWaiter : public QObject
{
	Q_OBJECT

public:
	LBLSyncWaiter(LBLEnginePackage packInfo);
	~LBLSyncWaiter();
	bool syncLock(int msec = 1500, bool force = false);
	LBLEnginePackage syncRecPackage();
protected:
	bool event(QEvent* e) override;
signals: 
	void sig_syncFinnish();

public slots:
	void slot_ParsingDataFrame(QObject *psource, LBLEnginePackage dataFrame);
private:
	QObject* m_socketObj = nullptr;
	bool m_forceWait = false;
	LBLEnginePackage m_syncPackage;
	LBLEnginePackage m_syncRecPackage;
};

class LBL_COMMUNICATENGINE_EXPORT LBLSocketExclusiveLock : public QObject
{
	Q_OBJECT

public:
	LBLSocketExclusiveLock(QObject *socketObj);
	~LBLSocketExclusiveLock();
	bool autoLock(int msec = 1000);
	QUuid exclusiveKey();
signals:
	void sig_locked();
public slots:
	void slot_TransThreadLocked(QObject * objSocket, bool bStatus, QUuid uuid);
private:
	QObject * m_socketObj = nullptr;
	QMutex m_exclusiveLock;

	QUuid m_exclusiveUuid;
};

class LBL_COMMUNICATENGINE_EXPORT LBLItemExclusiveLock : public QObject
{
	Q_OBJECT

public:
	LBLItemExclusiveLock(QString hostName);
	~LBLItemExclusiveLock();
	bool autoLock();
	QUuid exclusiveKey();

private:
	QString m_hostName;

	QUuid m_exclusiveUuid;
};
#endif
