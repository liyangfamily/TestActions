#pragma once

#include <QMap>
#include <QList>
#include <QWidget>
#include <Utils/testscreenhelper.h>
QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsScene;
class QGraphicsView;
QT_END_NAMESPACE

namespace Ui { class MCConnection; };
class ModuleItem;
class ConnectionFrame;
class ConnectionDiagramScene;
class MCConnection : public QWidget
{
	Q_OBJECT

public:
	MCConnection(QWidget *parent = Q_NULLPTR);
	~MCConnection();

private:
	Ui::MCConnection *ui;

    ConnectionFrame *m_view;
    ConnectionDiagramScene *m_scene;
	QButtonGroup* m_portBtnGroup = nullptr;

private:
	void initViewAndScene();

protected:
	void resizeEvent(QResizeEvent *event) override;
public slots:
	void slot_ConnectItem();
	void slot_EnterNavigatPage();
	void on_btnItemClear_clicked();
    void on_btnImport_clicked();
    void on_btnExport_clicked();
	void on_btnConnectionRead_clicked();
	void on_btnConnectionSend_clicked();

    void slot_OperatPortClicked();
    void slot_OperatPortChanged(int port);
    void slot_updateConnectionSetting();

private:
	TestScreenHelper m_testScrrenHelper;
};
