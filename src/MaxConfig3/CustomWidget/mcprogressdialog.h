#ifndef MCPROGRESSDIALOG_H
#define MCPROGRESSDIALOG_H

#include <QProgressDialog>
#include <QTimer>

class MCProgressDialog : public QProgressDialog
{
    Q_OBJECT
public:
    explicit MCProgressDialog(QWidget *parent = nullptr);

public:
    void setTime(int msec=3000);
    void delayReset(int msec=500);
private:
    void handleTimeout();

private:
    QTimer m_quitTimer;
};

#endif // MCROUNDCORNERPICKER_H
