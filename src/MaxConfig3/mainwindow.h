#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Core/icore.h"
#include "Utils/appmainwindow.h"
#include "CustomWidget/framelesswindow.h"

#include <QListWidgetItem>
#include <QStatusBar>
#include <LAPIControl>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QEvent;
class QResizeEvent;
class QButtonGroup;
class MCScreen;
class MCConnection;
class MCUpgrade;
class MCSenderCard;
class MCReceiveCard;
class MCCorrect;
class MCCusSCListItemWidget;
class VersionDialog;
QT_END_NAMESPACE
namespace Core {

namespace Internal {

#ifdef Q_OS_WIN
class MainWindow : public CFramelessWindow
#else
class MainWindow : public Utils::AppMainWindow
#endif
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public:
    void restart();
protected:
    void resizeEvent(QResizeEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
private:
    bool init();
    void updateSCList();
signals:
    void display(int);
    void sig_EnterNavigatPage();
    void sig_ConnectionSCChanged();
private slots:
    void on_toolBtnRefreshSCList_clicked();
    void on_toolBtnSCListHide_clicked();
    void on_toolBtnSCListShow_clicked();
    void on_btnScreen_clicked();
    void on_btnConnection_clicked();
    void on_btnSC_clicked();
    void on_btnRC_clicked();
    void on_btnCorrect_clicked();
    void on_btnUpgrade_clicked();
    void on_btnHelp_clicked();

    void slot_SenderCardOnline(SDetectItemInfo info);
    void slot_SenderCardOffline(SDetectItemInfo info);
    void slot_StartDetect();
    void slot_DetectComplit();
    void slot_ConnectItem(QUuid internalUuid);

    void on_toolBtnMinSize_clicked();
    void on_toolBtnMaxSize_clicked();
    void on_toolBtnClose_clicked();
private:
    ICore *m_coreImpl = nullptr;

    QUuid m_curSCInternalUuid;
    QButtonGroup* m_pnavigationBtnGroup = nullptr;
    MCScreen* m_pMCScreen = nullptr;
    MCConnection* m_pMCConnection = nullptr;
    MCUpgrade* m_pMCUpgrade = nullptr;
    MCSenderCard* m_pMCSenderCard = nullptr;
    MCReceiveCard* m_pMCReceiveCard = nullptr;
    MCCorrect* m_pMCCorrect=nullptr;
    QMap<QUuid, QListWidgetItem*> m_detectSCWidgetMap;

    VersionDialog *m_versionDialog = nullptr;

    bool m_bPressed;
    QPoint m_ptPress;
};

}// namespace Internal
}// namespace Core
#endif // MAINWINDOW_H
