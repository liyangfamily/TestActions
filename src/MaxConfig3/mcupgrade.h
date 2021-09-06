#ifndef MCUPGRADE_H
#define MCUPGRADE_H

#include <QWidget>
#include <QString>

#include <QTimer>

#include <LAPIControl>
#include <QtConcurrent/QtConcurrent>
namespace Ui {
class MCUpgrade;
}

class MCUpgrade : public QWidget
{
    Q_OBJECT

public:
    explicit MCUpgrade(QWidget *parent = nullptr);
    ~MCUpgrade();

private:
    Ui::MCUpgrade *ui;

protected:
	bool event(QEvent* e) override;
private:
	void cleanUpgradeWidget();
	void updateUpgrade();

	quint16 onParseReadMCUAppVersion(const QByteArray& data);
	quint16 onParseReadMCUBootVersion(const QByteArray& data);
	quint16 onParseReadAndroidVersion(const QByteArray& data);
	quint16 onParseReadSCFPGARegister(const QByteArray& data);
	quint16 onParseNT68400Data(const QByteArray& data);
signals:
	void upgradeResultReady(quint16 result);
	void requestStopUpgrade();
public slots:
	void slot_ConnectItem();
	void slot_EnterNavigatPage();
private slots:
	void on_btnSelectFile_clicked();
	void on_btnUpgrade_clicked();
	void on_btnClearFilePath_clicked();
	void slot_upgradeTypeChanged(int index);

	void onUpgradeFinished();
	void updateUpgardeProgressBar();

private:
	QFutureWatcher<quint16> m_upgradeWatcher;
	int m_upgradeType = LBLFileTransferPackage::EFileType::EFT_SenderMCU;
};

#endif // MCUPGRADE_H
