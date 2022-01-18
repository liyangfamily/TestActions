#include "mcprogressdialog.h"

#include <QTimer>
#include <QEventLoop>

MCProgressDialog::MCProgressDialog(QWidget *parent):
    QProgressDialog(parent)
{
    setWindowTitle(tr("Processing ..."));
    setWindowModality(Qt::WindowModal);
    setRange(0,0);
    setStyleSheet("QProgressDialog{color: #0F2C67;}");
    connect(&m_quitTimer,&QTimer::timeout,this,&MCProgressDialog::reject);
}

void MCProgressDialog::setTime(int msec)
{
    if(!m_quitTimer.isActive()){
        m_quitTimer.start(msec);
    }
}

void MCProgressDialog::delayReset(int msec)
{
    QEventLoop loop;
    QTimer outTimer;
    outTimer.setSingleShot(true);
    connect(&outTimer, &QTimer::timeout, [&]() {
            loop.exit(-1) ;
    });
    outTimer.start(msec); // 超时
    int ret=loop.exec();
    outTimer.stop();
    if(ret==-1){
        this->reset();
    }
}

