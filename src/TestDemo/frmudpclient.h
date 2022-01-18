#ifndef FRMUDPCLIENT_H
#define FRMUDPCLIENT_H

#include "app.h"

#include <QWidget>
#include <QtNetwork>
#include <LBLEnginePackage>

#include <atomic>
#include <QTimer>
#include <QtConcurrent/QtConcurrentRun>
#include <QtConcurrent/QtConcurrentMap>
#include <LAPIControl>
namespace Ui {
class frmUdpClient;
}
#include <functional>
typedef std::function<void(QObject*, LBLEnginePackage)> FileOptCallBack; 

namespace Core {
	namespace Internal { 
		class ProgressManagerPrivate; }
}

class frmUdpClient : public QWidget
{
    Q_OBJECT

public:
    explicit frmUdpClient(QWidget *parent = 0);
    ~frmUdpClient();

private:
    Ui::frmUdpClient *ui;

	QObject *udpSocket = nullptr;
    QTimer *timer;

	void test(QObject* objSocket, LBLEnginePackage pack);
	void test1();
protected:
	bool event(QEvent* e) override;
	void initTable();
	void setTableData(const QList<LBL::SCItem::LBLAbstractSCItem*>&);
signals:
	void sig_ConnectTo(const QHostAddress & address, quint16 nPort);
	void sig_SendeData(QObject * objSocket, LBLEnginePackage pack);
	void sig_test(quint16, quint16);
private slots:
    void initForm();
    void initConfig();
    void saveConfig();
    void changeTimer();
    void append(int type, const QString &data, bool clear = false);

    void readData();
    void sendData(const QString &ip, int port, const QString &data);

	void slot_NewConnectionEstablish(QObject* objSocket, const QHostAddress& addr, quint16 port);
	void slot_ReceiveData(QObject* objSocket, LBLEnginePackage pack);
	void slot_SendData(QObject* objSocket, LBLEnginePackage pack);
	void slot_SocketAbort(QObject* objSocket);

	void slot_SenderCardOnline(SDetectItemInfo info);
	void slot_SenderCardOffline(SDetectItemInfo info);
	void slot_DetectComplit();
	void slotTableCellDoubleClicked(int row, int column);
	void slot_SliderValueChanged(int value);
	quint16 onParseReadBrightness(const QByteArray& data);
	quint16 onParseReadMCUAppVersion(const QByteArray& data);
	quint16 onParseReadMCUBootVersion(const QByteArray& data);
	quint16 onParseReadAndroidVersion(const QByteArray& data);
	quint16 onParseReadSCFPGARegister(const QByteArray& data);

	void rangeChanged(int a, int b);
	void valueChanged(int a);
	void finished();
	void timeout();
	void slot_upgradeTypeChanged(int index);
private slots:
    void on_btnOpen_clicked();
    void on_btnClose_clicked();
    void on_btnSave_clicked();
    void on_btnClear_clicked();
    void on_btnSend_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
	FileOptCallBack m_cb1;
	QFutureWatcher<void> *m_pWatcher = nullptr;
	QTimer m_timer;
	Core::Internal::ProgressManagerPrivate *m_progressManager = nullptr;
    std::atomic_int progress{0};
	int m_upgradeType = LBLFileTransferPackage::EFileType::EFT_SenderMCU;
};

#endif // FRMUDPCLIENT_H
