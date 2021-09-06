/*********************************************************************************************************
** This file is part of the LBL_Core module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBLSIGNALWAITER
#define CVTE_H_LBLSIGNALWAITER
#pragma once

#include <LBL_Core/LBLCoreGlobal>

#include <QObject>
#include <QEventLoop>

class LBLSignalWaiterPrivate;
class LBL_CORE_EXPORT LBLSignalWaiter : public QObject
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(LBLSignalWaiter)
public:
	LBLSignalWaiter(const QObject* sender, const char* signal);
	~LBLSignalWaiter();

	static bool wait(const QObject* sender, const char* signal, int msec = -1, QEventLoop::ProcessEventsFlags flags = QEventLoop::AllEvents);
	bool wait(int msec = -1, bool forceWait = false, QEventLoop::ProcessEventsFlags flags = QEventLoop::AllEvents);
	bool hasCapturedSignal() const;

public Q_SLOTS:
	void signalCaught();
	void cancelWait();

private:
	void timerEvent(QTimerEvent* event);
private:
	QScopedPointer<LBLSignalWaiterPrivate> d_ptr;
};
#endif
