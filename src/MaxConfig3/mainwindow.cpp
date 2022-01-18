#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QButtonGroup>
#include <QStackedLayout>
#include <QThread>
#include <QMessageBox>
#include <QStatusBar>
#include <QTimer>
#include <QMouseEvent>
#include <QAction>
#include <QMenu>
#include <QVariant>
#include <QCursor>
#include <QDesktopServices>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProcess>
#include <QXmlStreamReader>
#include <Core/app_version.h>

#include "app.h"
#include "mcscreen.h"
#include "mcconnection.h"
#include "mcupgrade.h"
#include "mcsendercard.h"
#include "mcreceivecard.h"
#include "mccorrect.h"
#include "CustomWidget/mccussclistitemwidget.h"
#include "Core/versiondialog.h"
#include "Core/dialogs/restartdialog.h"
#include "Core/icore.h"

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
    initSystemMenu();
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
    initSystemMenu();
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
    addIgnoreWidget(ui->toolBtnAppIcon);
#endif
    //addIgnoreWidget(ui->labelAppName);
    ui->frameAppTitle->setMouseTracking(true);
    this->setMouseTracking(true);
    this->setAttribute(Qt::WA_AlwaysShowToolTips);//为不活动的窗口显示tooltip

    this->resize(1200, 700);
    //			QWidget *hidetitlebar1 = new QWidget;
    //			ui->dockWidget->setTitleBarWidget(hidetitlebar1); //!<隐藏dock标题栏

    //属性栏伸长
    ui->toolBtnAttributeExpand->setCheckable(true);
    slot_ExpandAttribute(false);
    connect(ui->toolBtnAttributeExpand,&QToolButton::clicked,this, &MainWindow::slot_ExpandAttribute);

    ui->frameNavigatSecond->hide();
    ui->labelAppIcon->setVisible(false);

    ConnectionDiagramScene::creatConnectionDiagramScene(this);
    ConnectionFrame::creatConnectionFrame(this);

    ConnectionFrame::instance()->view()->setScene(ConnectionDiagramScene::instance());
    ConnectionFrame::instance()->setCurrentMode(ConnectionDiagramScene::Mode::SceneView);
    // Add the vertical lines first, paint them red
    for (int x = 0; x <= ConnectionDiagramScene::instance()->sceneRect().width(); x += 30)
        ConnectionDiagramScene::instance()->addLine(x, 0, x, ConnectionDiagramScene::instance()->sceneRect().height(), QPen(QColor(Qt::darkGray).dark(200)))->setZValue(-100);

    // Now add the horizontal lines, paint them green
    for (int y = 0; y <= ConnectionDiagramScene::instance()->sceneRect().height(); y += 30)
        ConnectionDiagramScene::instance()->addLine(0, y, ConnectionDiagramScene::instance()->sceneRect().width(), y, QPen(QColor(Qt::darkGray).dark(200)))->setZValue(-100);
    //view->view()->fitInView(itemGroup.boundingRect());

    m_pnavigationBtnGroup = new QButtonGroup(this);
    m_pnavigationBtnGroup->setExclusive(true);
    m_pnavigationBtnGroup->addButton(ui->btnScreen, 0);
    m_pnavigationBtnGroup->addButton(ui->btnConnection, 1);
    m_pnavigationBtnGroup->addButton(ui->btnSC, 2);
    m_pnavigationBtnGroup->addButton(ui->btnRC, 3);
    m_pnavigationBtnGroup->addButton(ui->btnCorrect, 4);
    m_pnavigationBtnGroup->addButton(ui->btnUpgrade, 5);
    //m_pnavigationBtnGroup->addButton(ui->btnHelp, 6);
    ui->btnScreen->setCheckable(true);
    ui->btnConnection->setCheckable(true);
    ui->btnSC->setCheckable(true);
    ui->btnRC->setCheckable(true);
    ui->btnCorrect->setCheckable(true);
    ui->btnUpgrade->setCheckable(true);
    ui->btnHelp->setCheckable(false);

    m_pMCScreen = new MCScreen(this);
    m_pMCConnection = new MCConnection(this);
    m_pMCUpgrade = new MCUpgrade(this);
    m_pMCSenderCard = new MCSenderCard(this);
    m_pMCReceiveCard = new MCReceiveCard(this);
    m_pMCCorrect=new MCCorrect(this);

    //堆叠窗口
    QStackedLayout *pStacklayout = new QStackedLayout();
    pStacklayout->addWidget(m_pMCScreen);
    pStacklayout->addWidget(m_pMCConnection);
    pStacklayout->addWidget(m_pMCSenderCard);
    pStacklayout->addWidget(m_pMCReceiveCard);
    pStacklayout->addWidget(m_pMCCorrect);
    pStacklayout->addWidget(m_pMCUpgrade);
    connect(this, &MainWindow::display, pStacklayout, &QStackedLayout::setCurrentIndex);

    QStackedLayout *pStacklayout1 = new QStackedLayout();
    pStacklayout1->addWidget(ConnectionFrame::instance());
    ui->frameCentralView->setLayout(pStacklayout1);
    ui->frameAttributeContent->setLayout(pStacklayout);

    //隐藏边栏
    ui->frameShow->setVisible(false);

    on_btnScreen_toggled(true);

    connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_StartDetect, this, &MainWindow::slot_StartDetect);
    connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_DetectComplit, this, &MainWindow::slot_DetectComplit, Qt::QueuedConnection);
    connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_SenderCardOnline, this, &MainWindow::slot_SenderCardOnline, Qt::QueuedConnection);
    connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_SenderCardOffline, this, &MainWindow::slot_SenderCardOffline, Qt::QueuedConnection);
    connect(gSCItemMgr, &LBL::SCItem::LBLSCItemManager::sig_ConnectItem, this, &MainWindow::slot_ConnectItem, Qt::QueuedConnection);

    on_toolBtnRefreshSCList_clicked();
    return true;
}

bool MainWindow::initSystemMenu()
{
    if(!m_languageMenu){
        m_languageMenu=new RoundedMenu(this);
    }
    const QString creatorTrPath = LBLUIHelper::appLocalsLocation();
    const QStringList languageFiles = QDir(LBLUIHelper::appLocalsLocation()).entryList(QStringList(QLatin1String("MaxConfig3*.qm")));

    for (const QString &languageFile : languageFiles) {
        int start = languageFile.indexOf('_') + 1;
        int end = languageFile.lastIndexOf('.');
        const QString locale = languageFile.mid(start, end-start);
        // no need to show a language that creator will not load anyway
        if (hasQmFilesForLocale(locale, creatorTrPath)) {
            QLocale tmpLocale(locale);
            QString languageItem = QLocale::languageToString(tmpLocale.language()) + QLatin1String(" (")
                    + QLocale::countryToString(tmpLocale.country()) + QLatin1Char(')');
            if(languageItem.contains(QLatin1String("Taiwan"))){
                languageItem.replace(QLatin1String("Taiwan"),("繁体中文"));
            }
            if(languageItem.contains(QLatin1String("China"))){
                languageItem.replace(QLatin1String("China"),("简体中文"));
            }
            QAction *language_action= m_languageMenu->addAction(languageItem);
            language_action->setData(QVariant(locale));
            connect(language_action,&QAction::triggered,this,&MainWindow::slot_languageChanged);
        }
    }
    //ui->toolBtnAppIcon->setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(ui->toolBtnAppIcon,&QToolButton::clicked,[=](){
//        m_languageMenu->exec(QCursor::pos());
//    });
    return true;
}

bool MainWindow::hasQmFilesForLocale(const QString &locale, const QString &creatorTrPath)
{
    static const QString trPath = LBLUIHelper::appLocalsLocation();

    const QString trFile = QLatin1String("/MaxConfig3_") + locale + QLatin1String(".qm");
    return QFile::exists(trPath + trFile) || QFile::exists(creatorTrPath + trFile);
}

void MainWindow::updateSCList()
{
    const QList<LBL::SCItem::LBLAbstractSCItem*>& itemList = LAPI::GetAllItemList();
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
//    ui->listSenderCard->clear();
//    m_detectSCWidgetMap.clear();
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

void MainWindow::on_btnScreen_toggled(bool checked)
{
    ui->btnScreen->setChecked(checked);
    if(checked){
        emit display(0);
        QMetaObject::invokeMethod(m_pMCScreen, "slot_EnterNavigatPage", Qt::QueuedConnection);
    }
}

void MainWindow::on_btnConnection_toggled(bool checked)
{
    ui->btnConnection->setChecked(checked);
    if(checked){
        emit display(1);
        QMetaObject::invokeMethod(m_pMCConnection, "slot_EnterNavigatPage", Qt::QueuedConnection);
    }
}

void MainWindow::on_btnSC_toggled(bool checked)
{
    ui->btnSC->setChecked(checked);
    if(checked){
        emit display(2);
        QMetaObject::invokeMethod(m_pMCSenderCard, "slot_EnterNavigatPage", Qt::QueuedConnection);
    }
}

void MainWindow::on_btnRC_toggled(bool checked)
{
    ui->btnRC->setChecked(checked);
    if(checked){
        emit display(3);
        QMetaObject::invokeMethod(m_pMCReceiveCard, "slot_EnterNavigatPage", Qt::QueuedConnection);
    }
}

void MainWindow::on_btnCorrect_toggled(bool checked)
{
    ui->btnCorrect->setChecked(checked);
    if(checked){
        emit display(4);
        QMetaObject::invokeMethod(m_pMCCorrect, "slot_EnterNavigatPage", Qt::QueuedConnection);
    }
}

void MainWindow::on_btnUpgrade_toggled(bool checked)
{
    ui->btnUpgrade->setChecked(checked);
    if(checked){
        emit display(5);
        QMetaObject::invokeMethod(m_pMCUpgrade, "slot_EnterNavigatPage", Qt::QueuedConnection);
    }
}

void MainWindow::on_btnHelp_clicked()
{
    ui->btnHelp->setChecked(false);
    if(!m_helpMenu){
        m_helpMenu=new RoundedMenu(this);
        QAction *option = m_helpMenu->addAction(tr("Language"));
        if(m_languageMenu){
            option->setMenu(m_languageMenu);
        }
        option = m_helpMenu->addAction(tr("Manual"));
        connect(option,&QAction::triggered,this,&MainWindow::slot_manualShow);

        option = m_helpMenu->addAction(tr("About MaxConfig"));
        connect(option,&QAction::triggered,this,&MainWindow::slot_aboutDlgShow);

        option = m_helpMenu->addAction(tr("Check For Updates"));
        connect(option,&QAction::triggered,this,&MainWindow::slot_checkForUpdates);

    }
    QPoint pos = ui->btnHelp->mapToGlobal(QPoint(0,ui->btnHelp->size().height()));

    m_helpMenu->exec(pos);
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
    //close();
    LAPI::CancelUpgrade();
    qApp->quit();
}

void MainWindow::slot_languageChanged()
{
    QAction *sender1= qobject_cast<QAction*>(sender());
    if(!sender1){
        return;
    }
    const QString currentLocale = App::lastLanguage;
    if (sender1->data().toString() ==  currentLocale){
        return;
    }
    App::lastLanguage=sender1->data().toString();
    App::writeConfig();
    RestartDialog dialog(ICore::dialogParent(),
                         tr("The language change will take effect after restart."));
    dialog.exec();
}

void MainWindow::slot_manualShow()
{
    QString openSourceTxt = QString("file:///%1").arg(LBLUIHelper::appDocLocation()+"/MaxConfig3_Manual.pdf");
    QDesktopServices::openUrl(QUrl(openSourceTxt, QUrl::TolerantMode));
}

void MainWindow::slot_aboutDlgShow()
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

void MainWindow::slot_checkForUpdates()
{
    qDebug()<<"Check For Updates...";
    QString program(QString("%1%2").arg(LBLUIHelper::appPath()).arg("/maintenancetool.exe"));
    qDebug()<<"Updates Program:"<<program;

    QUrl url(QString("https://raw.githubusercontent.com/liyangfamily/TestIFW/master/repository/Updates.xml"));
    QNetworkAccessManager manager;
    QEventLoop loop;
    qDebug() << "Reading code form:" << url.toString();
    //发出请求
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //开启子事件循环
    loop.exec();


    //将读到的信息写入文件
    QByteArray data = reply->readAll();

    QString appVersion,releaseData;
    QXmlStreamReader updateXml(data);
    while(!updateXml.atEnd()){
        QXmlStreamReader::TokenType nType = updateXml.readNext();

        switch(nType){
        case QXmlStreamReader::StartElement:{
            QString elementName = updateXml.name().toString();
            if(elementName == "PackageUpdate"){
                qDebug()<<"Start Parse <PackageUpdate> Element...";
                while(!updateXml.atEnd()){
                    updateXml.readNext();
                    if(updateXml.isStartElement()){
                        QString elementName = updateXml.name().toString();
                        if(elementName == "DisplayName"){
                            qDebug()<<"DisplayName:"<<updateXml.readElementText();
                        }
                        else if(elementName == "Version"){
                            appVersion = updateXml.readElementText();
                            qDebug()<<"Version:"<<appVersion;
                        }
                        else if(elementName == "ReleaseDate"){
                            releaseData = updateXml.readElementText();
                            qDebug()<<"ReleaseDate:"<<releaseData;
                        }
                    }
                    else if(updateXml.isEndElement()){
                        QString elementName = updateXml.name().toString();
                        if(elementName == "PackageUpdate"){
                            qDebug()<<"End Parse <PackageUpdate> Element...";
                            break;
                        }
                    }
                }
            }
        }
            break;
         default:
            break;
        }
    }

    qDebug()<<"Current App Version:"<<Core::Constants::IDE_VERSION_LONG;
    if(appVersion == Core::Constants::IDE_VERSION_LONG){
        QMessageBox::information(ICore::mainWindow(),tr("Tip"),tr("Already the latest version."));
        return;
    }
    if(appVersion > Core::Constants::IDE_VERSION_LONG){
        int opt = QMessageBox::question(ICore::mainWindow(), tr("Available Update!"),
                                        tr("Version: %1\n\nReleaseData:%2\n\nDo you need an update?").arg(appVersion).arg(releaseData),
                                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (opt == QMessageBox::No)
        {
            qDebug() << "Update Canceled.";
            return;
        }
        QStringList updateArgs;
        updateArgs<<QString("--script=%1%2").arg(LBLUIHelper::appPath()).arg("/script/updatescript.qs");
        qDebug()<<"Update Args:"<<updateArgs;
        bool success = QProcess::startDetached(program,updateArgs);
        if(!success){
            qDebug() << "Update Failed.";
            QMessageBox::critical(ICore::mainWindow(),tr("Error"),tr("Can't Start Update Program."));
            return;
        }
        this->on_toolBtnClose_clicked();
        qDebug() << "Update Success.";
        return;
    }
    if(appVersion.isEmpty()){
        QMessageBox::information(ICore::mainWindow(),tr("Tip"),tr("No updates available."));
        qDebug()<<tr("No updates available.");
        return;
    }
}

void MainWindow::slot_ExpandAttribute(bool b)
{
    if(b){
        ui->splitter->setSizes(QList<int>()<<200<<300);
        ui->splitter->setStretchFactor(0,0);
        ui->splitter->setStretchFactor(1,2);
        ui->toolBtnAttributeExpand->setToolTip(tr("Shrink"));
    }
    else{
        ui->splitter->setSizes(QList<int>()<<200<<300);
        ui->splitter->setStretchFactor(0,2);
        ui->splitter->setStretchFactor(1,0);
        ui->toolBtnAttributeExpand->setToolTip(tr("Expansion"));
    }
}
} // namespace Internal
}// namespace Core
