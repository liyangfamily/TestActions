#include "frmmain.h"
#include "ui_frmmain.h"
#include "quiwidget.h"
#include <LBLCluster>
using namespace Core;
using namespace Core::Internal;
frmMain::frmMain(QWidget *parent) : QWidget(parent), ui(new Ui::frmMain)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(App::CurrentIndex);

	App::mainWindow = this;
	m_progressManager = new ProgressManagerPrivate;

	QHBoxLayout* hLayout = new QHBoxLayout(this);
	hLayout->setContentsMargins(0, 0, 5, 2);
	hLayout->setSpacing(0);
	hLayout->addSpacerItem(new QSpacerItem(20, 25, QSizePolicy::Expanding));
	App::statusBar = hLayout;
	ui->widget_3->setLayout(hLayout);

	m_progressManager->progressView()->setParent(this);
	m_progressManager->init();

	//QFutureInterface<void>* m_fakeFutureInterface = new QFutureInterface<void>(QFutureInterfaceBase::Running);
	//QFuture<void> future = m_fakeFutureInterface->future();
	//m_fakeFutureInterface->setProgressRange(0, 100);
	//m_fakeFutureInterface->setProgressValue(50);
	////m_futureWatcher.setFuture(future);
	//const Core::FutureProgress *progress = Core::ProgressManager::addTask(
	//	future, QObject::tr("Cppcheck"), "AutoTest.Task.Index");
}

frmMain::~frmMain()
{
    delete ui;

	/*qCluster->readyToExit();
	int maxWait = 0;
	while (!qCluster->canExit())
	{
		QCoreApplication::processEvents();
		QThread::currentThread()->msleep(200);
		maxWait++;
		if (maxWait >= 150)
		{
			if (QMessageBox::information(0, tr("Confire Exit"),
				tr("There are still some clients alive in the server. continue waiting?"),
				QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
				maxWait = 0;
			else
				break;
		}
	}*/
}

void frmMain::on_tabWidget_currentChanged(int index)
{
    App::CurrentIndex = index;
    App::writeConfig();
}
#include "progressmanager/TestRunable.h"
void frmMain::on_btnTest_clicked()
{
	/*QFutureInterface<void>* m_fakeFutureInterface = new QFutureInterface<void>(QFutureInterfaceBase::Running);
	QFuture<void> future = m_fakeFutureInterface->future();
	m_fakeFutureInterface->setProgressRange(0, 100);
	m_fakeFutureInterface->setProgressValue(50);*/
	//m_futureWatcher.setFuture(future);
	auto myRunnable = new TestRunable();
	auto future = myRunnable->future();
	myRunnable->setAutoDelete(true);
	Core::FutureProgress *progress = Core::ProgressManager::addTask(
		future, QObject::tr("Cppcheckccccccccccc"), "AutoTest.Task.Index");
	progress->setSubtitle("hahahahahhahhah");
	QThreadPool::globalInstance()->start(myRunnable);
	return;
}
