/*********************************************************************************************************/
/*任务处理引擎，任务队列采用FIFO。                                                                     
*********************************************************************************************************/
#ifndef CVTE_H_LBL_TASKENGINE
#define CVTE_H_LBL_TASKENGINE
#pragma once

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QVector>
#include <list>

class LBL_TaskEngine_TaskBase;
class LBL_TaskEngine_WorkingThread;
class LBL_TaskEngine : public QObject
{
	Q_OBJECT
	friend class LBL_TaskEngine_WorkingThread;
public:
	explicit LBL_TaskEngine(QObject *parent = 0);
	~LBL_TaskEngine();
	int creatThreads(int nThreads);
	int removeThreads(int nThreads);
	int threadsCount();
	int payload();
	int idleThreads(); 

	bool canExit();

protected:
	QMutex m_mutex_protect;

	QVector<LBL_TaskEngine_WorkingThread *> m_vec_workingThreads;
	QVector<QThread *> m_vec_InternalworkingThreads;

	std::list< LBL_TaskEngine_TaskBase * > m_list_tasks;
	int m_nExistingThreads;
	int m_nThread = 4;

protected:
	LBL_TaskEngine_TaskBase* popTask(bool *bValid);

signals:
	void sig_start_work(LBL_TaskEngine_WorkingThread* taskThread);
	void sig_stop_work(LBL_TaskEngine_WorkingThread* taskThread);
public slots:
	void slot_finished_task(LBL_TaskEngine_WorkingThread* taskThread);
	void slot_pushTask(LBL_TaskEngine_TaskBase* task, bool bFire = true);
};
#endif
