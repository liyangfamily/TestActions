#ifndef CVTE_H_LBL_TASKENGINE_WORKINGTHREAD
#define CVTE_H_LBL_TASKENGINE_WORKINGTHREAD
#pragma once
#include <QObject>

class LBL_TaskEngine;
class LBL_TaskEngine_WorkingThread :public QObject
{
	Q_OBJECT
public:
	explicit LBL_TaskEngine_WorkingThread(LBL_TaskEngine * taskEngine, QObject *parent = 0);
	~LBL_TaskEngine_WorkingThread();
	bool m_bBusy;

protected:
	LBL_TaskEngine * m_taskEngine;
	bool m_bRuning;

signals:
	void sig_taskFinished(LBL_TaskEngine_WorkingThread* taskThread);
public slots:
	void slot_SetStopMark(LBL_TaskEngine_WorkingThread* taskThread);
	void slot_FetchNewTask(LBL_TaskEngine_WorkingThread* taskThread);

};
#endif 