#pragma once

#include <QObject>
#include <QRunnable>
#include <QThreadPool>
#include <QFutureInterface>
#include <QFuture>

class TestRunable : public QRunnable
{
public:
	TestRunable(QFutureInterface<void> futureInterface)
		: m_futureInterface(futureInterface)
	{
		
	}
	TestRunable()
	{
		m_futureInterface.setProgressRange(0, 100);
		m_futureInterface.setProgressValue(0);
	}
	QFuture<void> future() {
		return m_futureInterface.future();
	}
	virtual void run() override;
private:
	QFutureInterface<void> m_futureInterface;
};