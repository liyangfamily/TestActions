#include "LBL_TaskEngine.h"
#include "LBL_TaskEngine_TaskBase.h"
#include "LBL_TaskEngine_WorkingThread.h"

LBL_TaskEngine::LBL_TaskEngine(QObject *parent/* = 0*/) : 
	QObject(parent)
{
	m_nExistingThreads = 0;
	creatThreads(m_nThread);
}

LBL_TaskEngine::~LBL_TaskEngine()
{
	qDebug() << __FUNCTION__;
}

int LBL_TaskEngine::creatThreads(int nThreads)
{
	if (nThreads >= 1 && nThreads <= 128)
	{
		for (int i = 0; i < nThreads; i++)
		{
			LBL_TaskEngine_WorkingThread * thread = new LBL_TaskEngine_WorkingThread(this);
			m_vec_workingThreads.push_back(thread);
			QThread * pTh = new QThread(this); 
			m_vec_InternalworkingThreads.push_back(pTh);
			thread->moveToThread(pTh);
			connect(this, &LBL_TaskEngine::sig_start_work, thread, &LBL_TaskEngine_WorkingThread::slot_FetchNewTask, Qt::QueuedConnection);
			connect(this, &LBL_TaskEngine::sig_stop_work, thread, &LBL_TaskEngine_WorkingThread::slot_SetStopMark, Qt::QueuedConnection);
			connect(thread, &LBL_TaskEngine_WorkingThread::sig_taskFinished, this, &LBL_TaskEngine::slot_finished_task, Qt::QueuedConnection);
			pTh->start();
			m_mutex_protect.lock();
			m_nExistingThreads++;
			m_mutex_protect.unlock();
		}

	}
	return m_vec_workingThreads.size();
}

int LBL_TaskEngine::removeThreads(int nThreads)
{
	int nsz = m_vec_workingThreads.size();
	if (nThreads<0 || nThreads>nsz)
		nThreads = nsz;

	for (int i = 0; i < nThreads; i++)
	{
		emit sig_stop_work(m_vec_workingThreads.last()); //发送信号给工作线程，让他自己退出并销毁
		m_vec_InternalworkingThreads.last()->deleteLater();
		m_vec_workingThreads.pop_back();
		m_vec_InternalworkingThreads.pop_back();
	}
	return m_vec_workingThreads.size();
}

int LBL_TaskEngine::threadsCount()
{
	return m_vec_workingThreads.size();
}

int LBL_TaskEngine::payload()
{
	int res = 0;
	m_mutex_protect.lock();
    res = int(m_list_tasks.size());
	m_mutex_protect.unlock();

	return res;
}

int LBL_TaskEngine::idleThreads()
{
	int idle = 0;
	int nsz = m_vec_workingThreads.size();
	for (int i = 0; i < nsz; i++)
	{
		if (m_vec_workingThreads[i]->m_bBusy == false)
			idle++;
	}
	return idle;
}

bool LBL_TaskEngine::canExit()
{
	return m_nExistingThreads == 0 ? true : false;
}

LBL_TaskEngine_TaskBase * LBL_TaskEngine::popTask(bool * bValid)
{
	*bValid = false;
	LBL_TaskEngine_TaskBase * funcres = 0;
	m_mutex_protect.lock();
	if (m_list_tasks.empty() == false)
	{
		funcres = *m_list_tasks.begin();
		m_list_tasks.pop_front();
		*bValid = true;
	}
	m_mutex_protect.unlock();
	return funcres;
}

void LBL_TaskEngine::slot_pushTask(LBL_TaskEngine_TaskBase * task, bool bFire)
{
	m_mutex_protect.lock();
	m_list_tasks.push_back(task);
	task->addRef();
	m_mutex_protect.unlock();

	int nsz = m_vec_workingThreads.size();
	if (0 == nsz) {
		creatThreads(m_nThread);
	}
	if (bFire == true)
		for (int i = 0; i < nsz; i++)
		{
			if (m_vec_workingThreads[i]->m_bBusy == false)
			{
				slot_finished_task(m_vec_workingThreads[i]);
				break;
			}
		}
}

void LBL_TaskEngine::slot_finished_task(LBL_TaskEngine_WorkingThread* taskThread)
{
	int res = 0;
	m_mutex_protect.lock();
    res = int(m_list_tasks.size());
	m_mutex_protect.unlock();
	if (res)
		emit sig_start_work(taskThread);
}
