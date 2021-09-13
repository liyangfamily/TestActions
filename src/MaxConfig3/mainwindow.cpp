#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QButtonGroup>
#include <QStackedLayout>
#include <QThread>
#include <QMessageBox>
#include <QStatusBar>
#include <QTimer>
#include <QMouseEvent>

#include "mcscreen.h"
#include "mcconnection.h"
#include "mcupgrade.h"
#include "mcsendercard.h"
#include "mcreceivecard.h"
#include "mccorrect.h"
#include "CustomWidget/mccussclistitemwidget.h"
#include "Core/versiondialog.h"

#include "ConnectionControl/moduleItem.h"
#include "ConnectionControl/connectionView.h"
#include "ConnectionControl/connectionScene.h"

#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif

#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LAPI_Controld.lib")
#else
#pragma comment(lib,"LAPI_Control.lib")
#endif // QT_DEBUG
#endif

namespace Core
{
namespace Internal
{
#ifdef Q_OS_WIN
MainWindow::MainWindow()
    : CFramelessWindow()
    , ui(new Ui::MainWindow)
    , m_coreImpl(new ICore(this))
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    init();
}
#else
MainWindow::MainWindow()
    : Utils::AppMainWindow()
    , ui(new Ui::MainWindow)
    , m_coreImpl(new ICore(this))
{
    ui->setupUi(this);
    //setWindowFlag(Qt::FramelessWindowHint);
    init();
}
#endif

MainWindow::~MainWindow()
{
    delete m_coreImpl;
    m_coreImpl = nullptr;

    delete ui;
    LAPI::ReadyExit();
    int maxWait = 0;
    while (!LAPI::CanExit())
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
    }
}

void MainWindow::restart()
{
    qApp->setProperty("restart", true);
    QTimer::singleShot(0, this, &QWidget::close);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
#ifdef Q_OS_WIN
    if (this->getIsMax()) {
        ui->toolBtnMaxSize->setToolTip(tr("Normal"));
        ui->toolBtnMaxSize->setProperty("maximizeProperty", "restore");
        ui->toolBtnMaxSize->style()->unpolish(ui->toolBtnMaxSize);
        ui->toolBtnMaxSize->style()->polish(ui->toolBtnMaxSize);
        ui->toolBtnMaxSize->update();
    }
    else{
        ui->toolBtnMaxSize->setToolTip(tr("Maximize"));
        ui->toolBtnMaxSize->setProperty("maximizeProperty", "");
        ui->toolBtnMaxSize->style()->unpolish(ui->toolBtnMaxSize);
        ui->toolBtnMaxSize->style()->polish(ui->toolBtnMaxSize);
        ui->toolBtnMaxSize->update();
    }
#endif
    QMainWindow::resizeEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
#ifndef Q_OS_WIN
    if (event->button() == Qt::LeftButton)
    {
        m_ptPress = event->pos();
        m_bPressed = ui->frameAppTitle->rect().contains(m_ptPress);
    }
#endif
    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
#ifndef Q_OS_WIN
    if (m_bPressed)
    {
        move(pos() + event->pos() - m_ptPress);
    }
#endif
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
#ifndef Q_OS_WIN
    m_bPressed = false;
#endif
    QMainWindow::mouseReleaseEvent(event);
}

bool MainWindow::init()
{
#ifdef Q_OS_WIN
    setTitleBar(ui->frameAppTitle);
    addIgnoreWidget(ui->toolBtnMinSize);
    addIgnoreWidget(ui->toolBtnMaxSize);
    addIgnoreWidget(ui->toolBtnClose);
#endif
    //addIgnoreWidget(ui->labelAppName);
    ui->frameAppTitle->setMouseTracking(true);
    this->setMouseTracking(true);
    this->setAttribute(Qt::WA_AlwaysShowToolTips);//为不活动的窗口显示tooltip

    this->resize(1200, 700);
    //			QWidget *hidetitlebar1 = new QWidget;
    //			ui->dockWidget->setTitleBarWidget(hidetitlebar1); //!<隐藏dock标题栏
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,0);
    ui->frameNavigatSecond->hide();

    ConnectionDiagramScene::creatConnectionDiagramScene(this);
    ConnectionFrame::creatConnectionFrame(this);

    ConnectionFrame::instance()->view()->setScene(ConnectionDiagramScene::instance());
    ConnectionFrame::instance()->setCurrentMode(ConnectionDiagramScene::Mode::SceneView);
    // Add the vertical lines first, paint them red
    for (int x = 0; x <= ConnectionDiagramScene::instance()->sceneRect().width(); x += 50)
        ConnectionDiagramScene::instance()->addLine(x, 0, x, ConnectionDiagramScene::instance()->sceneRect().height(), QPen(Qt::darkGray))->setZValue(-100);

    // Now add the horizontal lines, paint them green
    for (int y = 0; y <= ConnectionDiagramScene::instance()->sceneRect().height(); y += 50)
        ConnectionDiagramScene::instance()->addLine(0, y, ConnectionDiagramScene::instance()->sceneRect().width(), y, QPen(Qt::darkGray))->setZValue(-100);
    //view->view()->fitInView(itemGroup.boundingRect());

    m_pnavigationBtnGroup = new QButtonGroup(this);
    m_pnavigationBtnGroup->setExclusive(true);
    m_pnavigationBtnGroup->addButton(ui->btnScreen, 0);
    m_pnavigationBtnGroup->addButton(ui->btnConnection, 1);
    m_pnavigationBtnGroup->addButton(ui->btnSC, 2);
    m_pnavigationBtnGroup->addButton(ui->btnRC, 3);
    m_pnavigationBtnGroup->addButton(ui->btnCorrect, 4);
    m_pnavigationBtnGroup->addButton(ui->btnUpgrade, 5);
    m_pnavigationBtnGroup->addButton(ui->btnHelp, 6);
    ui->btnScreen->setCheckable(true);
    ui->btnConnection->setCheckable(true);
    ui->btnSC->setCheckable(true);
    ui->btnRC->setCheckable(true);
    ui->btnCorrect->setCheckable(true);
    ui->btnUpgrade->setCheckable(true);

    m_pMCScreen = new MCScreen(this);
    m_pMCConnection = new MCConnection(this);
    m_pMCUpgrade = new MCUpgrade(this);
    m_pMCSenderCard = new MCSenderCard(this);
    m_pMCReceiveCard = new MCReceiveCard(this);
    m_pMCCorrect=new MCCorrect(this);

    //堆叠窗口
    QStackedLayout *pStacklayout = new QStackedLayout(this);
    pStacklayout->addWidget(m_pMCScreen);
    pStacklayout->addWidget(m_pMCConnection);
    pStacklayout->addWidget(m_pMCSenderCard);
    pStacklayout->addWidget(m_pMCReceiveCard);
    pStacklayout->addWidget(m_pMCCorrect);
    pStacklayout->addWidget(m_pMCUpgrade);
    connect(this, &MainWindow::display, pStacklayout, &QStackedLayout::setCurrentIndex);

    QStackedLayout *pStacklayout1 = new QStackedLayout(this);
    pStacklayout1->addWidget(ConnectionFrame::instance());
    ui->frameCentralView->setLayout(pStacklayout1);
    ui->frameAttribute->setLayout(pStacklayout);

    //隐藏边栏
    ui->frameShow->setVisible(false);

    on_btnScreen_clicked();

    connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_StartDetect, this, &MainWindow::slot_StartDetect);
    connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_DetectComplit, this, &MainWindow::slot_DetectComplit, Qt::QueuedConnection);
    connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_SenderCardOnline, this, &MainWindow::slot_SenderCardOnline, Qt::QueuedConnection);
    connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_SenderCardOffline, this, &MainWindow::slot_SenderCardOffline, Qt::QueuedConnection);
    connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_ConnectItem, this, &MainWindow::slot_ConnectItem, Qt::QueuedConnection);

    on_toolBtnRefreshSCList_clicked();
    return true;
}

void MainWindow::updateSCList()
{
    QList<LBL::SCItem::LBLAbstractSCItem*> itemList;
    itemList = LAPI::GetAllItemList();
    for (auto item : itemList) {
        if (m_detectSCWidgetMap.contains(item->internalUuid())) {
            qobject_cast<MCCusSCListItemWidget*>(ui->listSenderCard->itemWidget(m_detectSCWidgetMap.value(item->internalUuid())))->updateItemWidget();
            continue;
        }
        MCCusSCListItemWidget* pItemWidget = new MCCusSCListItemWidget(ui->listSenderCard);
        pItemWidget->setSCItem(item);

        QListWidgetItem* pListWidgetItem = new QListWidgetItem(ui->listSenderCard);
        ui->listSenderCard->setItemWidget(pListWidgetItem, pItemWidget);

        m_detectSCWidgetMap.insert(item->internalUuid(), pListWidgetItem);
    }
    for (auto it = m_detectSCWidgetMap.begin(); it != m_detectSCWidgetMap.end();) {
        if (nullptr == LAPI::GetItemByInternalUuid(it.key())) {
            delete it.value();
            it = m_detectSCWidgetMap.erase(it);
            continue;
        }
        ++it;
    }
}

void MainWindow::on_toolBtnRefreshSCList_clicked()
{
    LAPI::StartDetectServer();
    ui->listSenderCard->clear();
    m_detectSCWidgetMap.clear();
}

void MainWindow::on_toolBtnSCListHide_clicked()
{
    ui->frameSCList->setVisible(false);
    ui->frameShow->setVisible(true);
}

void MainWindow::on_toolBtnSCListShow_clicked()
{
    ui->frameSCList->setVisible(true);
    ui->frameShow->setVisible(false);
}

void MainWindow::on_btnScreen_clicked()
{
    ui->btnScreen->setChecked(true);
    ui->btnScreen->update();
    emit display(0);
    m_pMCScreen->slot_EnterNavigatPage();
}

void MainWindow::on_btnConnection_clicked()
{
    ui->btnConnection->setChecked(true);
    emit display(1);
    m_pMCConnection->slot_EnterNavigatPage();
}

void MainWindow::on_btnSC_clicked()
{
    ui->btnSC->setChecked(true);
    emit display(2);
    m_pMCSenderCard->slot_EnterNavigatPage();
}

void MainWindow::on_btnRC_clicked()
{
    ui->btnRC->setChecked(true);
    emit display(3);
    m_pMCReceiveCard->slot_EnterNavigatPage();
}

void MainWindow::on_btnCorrect_clicked()
{
    ui->btnCorrect->setChecked(true);
    emit display(4);
    m_pMCCorrect->slot_EnterNavigatPage();
}

void MainWindow::on_btnUpgrade_clicked()
{
    ui->btnUpgrade->setChecked(true);
    emit display(5);
    m_pMCUpgrade->slot_EnterNavigatPage();
}

void MainWindow::on_btnHelp_clicked()
{
    if (!m_versionDialog) {
        m_versionDialog = new VersionDialog(this);
        connect(m_versionDialog, &QDialog::finished,
                [this](){
            if (m_versionDialog) {
                m_versionDialog->deleteLater();
                m_versionDialog = nullptr;
            }
        });
        m_versionDialog->show();
    } else {
        m_versionDialog->raise();
        m_versionDialog->show();
    }
}

void MainWindow::slot_SenderCardOnline(SDetectItemInfo info)
{
    Q_UNUSED(info);
}

void MainWindow::slot_SenderCardOffline(SDetectItemInfo info)
{
    Q_UNUSED(info);
}

void MainWindow::slot_StartDetect()
{
    this->statusBar()->showMessage(tr("Refreshing..."));
}

void MainWindow::slot_DetectComplit()
{
    this->statusBar()->showMessage(tr("Refresh complete."), 1000);
    updateSCList();
}

void MainWindow::slot_ConnectItem(QUuid internalUuid)
{
    Q_UNUSED(internalUuid);
    if (!m_pnavigationBtnGroup) {
        return;
    }
    updateSCList();
    m_pMCConnection->slot_ConnectItem();
    switch (m_pnavigationBtnGroup->checkedId())
    {
    case 0:
        m_pMCScreen->slot_ConnectItem();
        break;
    case 1:
        m_pMCConnection->slot_ConnectItem();
        break;
    case 2:
        m_pMCSenderCard->slot_ConnectItem();
        break;
    case 3:
        m_pMCReceiveCard->slot_ConnectItem();
        break;
    case 4  :
        m_pMCCorrect->slot_ConnectItem();
        break;
    case 5:
        m_pMCUpgrade->slot_ConnectItem();
        break;
    default:
        break;
    }
}

void MainWindow::on_toolBtnMinSize_clicked()
{
    showMinimized();
}

void MainWindow::on_toolBtnMaxSize_clicked()
{
    if (this->isMaximized()) {
        this->showNormal();
        ui->toolBtnMaxSize->setToolTip(tr("Maximize"));
        ui->toolBtnMaxSize->setProperty("maximizeProperty", "");
    }
    else{
        this->showMaximized();
        ui->toolBtnMaxSize->setToolTip(tr("Normal"));
        ui->toolBtnMaxSize->setProperty("maximizeProperty", "restore");
    }
    ui->toolBtnMaxSize->style()->unpolish(ui->toolBtnMaxSize);
    ui->toolBtnMaxSize->style()->polish(ui->toolBtnMaxSize);
    ui->toolBtnMaxSize->update();
}

void MainWindow::on_toolBtnClose_clicked()
{
    close();
}

} // namespace Internal
}// namespace Core
