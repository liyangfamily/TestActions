#include "LBL_TaskEngine_TaskBase.h"

LBL_TaskEngine_TaskBase::LBL_TaskEngine_TaskBase(QObject *parent /*= 0*/) : 
	QObject(parent)
{
	m_refCount = 0;
}

LBL_TaskEngine_TaskBase::~LBL_TaskEngine_TaskBase()
{
}

int LBL_TaskEngine_TaskBase::push_new_data(const LBLEnginePackage & dataArray)
{
	int res = 0;
	m_mutex_rawData.lock();

	m_list_RawData.push_back(dataArray);
	res = m_list_RawData.size();
	m_mutex_rawData.unlock();
	m_last_Report = QDateTime::currentDateTime();
	return res;
}
 
QObject * LBL_TaskEngine_TaskBase::socketObj()
{
	return m_pSocket;
}

void LBL_TaskEngine_TaskBase::setHostName(QString name)
{
	m_strTaskName = name;
}

QString LBL_TaskEngine_TaskBase::hostName()
{
	return m_strTaskName;
}

int LBL_TaskEngine_TaskBase::addRef()
{
	QMutexLocker locker(&m_mutex_ref);
	m_refCount++;

	return m_refCount;
}

int LBL_TaskEngine_TaskBase::delRef()
{
	QMutexLocker locker(&m_mutex_ref);
	m_refCount--;

	return m_refCount;
}

int LBL_TaskEngine_TaskBase::ref()
{
	QMutexLocker locker(&m_mutex_ref);
	//return 1;
	return m_refCount;
}

bool LBL_TaskEngine_TaskBase::lockRun()
{
	return m_mutex_run.tryLock();
}

void LBL_TaskEngine_TaskBase::unlockRun()
{
	return m_mutex_run.unlock();
}
