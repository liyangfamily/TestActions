#include "TestRunable.h"
#include "head.h"
void TestRunable::run()
{
	m_futureInterface.reportStarted();
	qDebug() << "myrunnable begin running...";
	for (int i = 0; i < 10; ++i)
	{
		if (m_futureInterface.isCanceled()) {
			break;
		}
		m_futureInterface.setProgressValueAndText(i*10, QString::fromLocal8Bit("完成了 %1 之中的 %2 步骤。").arg(10).arg(i));
		QThread::currentThread()->msleep(1000);
	}
	qDebug() << "myrunnable finish running...";

	m_futureInterface.reportFinished();
}
