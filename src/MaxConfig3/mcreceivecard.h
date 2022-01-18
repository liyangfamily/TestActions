#ifndef MCRECEIVECARD_H
#define MCRECEIVECARD_H

#include <QWidget>
#include <LAPIControl>
#include "mcmonitor.h"

namespace Ui {
class MCReceiveCard;
}
class MCGammaTable;
class MCReceiveCard : public QWidget
{
	Q_OBJECT
	enum ERCStatusInfoTableCol
	{
		ECol_PortIndex = 0,
		ECol_ModuleIndex,
		ECol_HardWareVer,
		ECol_SoftWareVer,
        ECol_MCUVer,
		ECol_ProtocolType,
		ECol_PackLoseRate,
		ECol_BitErrorRate,
		ECol_Upgrade,
	};
public:
    explicit MCReceiveCard(QWidget *parent = nullptr);
    ~MCReceiveCard();

private:
    Ui::MCReceiveCard *ui;
    MCMonitor* m_monitor = nullptr;
    MCGammaTable* m_gamma = nullptr;

protected:
	bool event(QEvent* e) override;
private:
    void cleanReceiveCardWidget();
    void updateReceiveCard();

	void initRCStatusInfo();
	void updateRCStatusInfo(QList<LBL::RC::SRCStatusInfo>&);

    quint16 onParseReadRCFPGARegister(const QByteArray& data);

public slots:
	void slot_ConnectItem();
	void slot_EnterNavigatPage();
private slots:
    void on_btnParamImport_clicked();
    void on_btnParamExport_clicked();
    void on_btnParamSave_clicked();

    void on_btnGamma_clicked();

    void on_btnRCUpgradeAll_clicked();
    void on_btnRCInfoRefresh_clicked();

    void on_checkBoxRegBroadCast_clicked();
    void on_btnRegRead_clicked();
    void on_btnRegWrite_clicked();
    void on_btnRegImport_clicked();
    void on_btnRegExport_clicked();

	void slot_rcTableWidgetUpgrade_clicked();
};

#endif // MCRECEIVECARD_H
