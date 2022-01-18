#include "mccorrect.h"
#include "ui_mccorrect.h"

#include <LAPIControl>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QDir>
#include <QFileInfoList>
#include <QFileDialog>

#include "ConnectionControl/moduleItem.h"
#include "ConnectionControl/connectionView.h"
#include "ConnectionControl/connectionScene.h"

#include "Core/icore.h"
#include "app.h"
#include <QStatusBar>
#include <QtConcurrent/QtConcurrentMap>
using namespace Core;

#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif

MCCorrect::MCCorrect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MCCorrect)
{
    ui->setupUi(this);
    initViewAndScene();

    ui->spinBoxRow->setMinimum(0);
    ui->spinBoxRow->setEnabled(false);
    ui->spinBoxCol->setMinimum(0);
    ui->spinBoxCol->setEnabled(false);
    ui->spinBoxWidth->setMinimum(1);
    ui->spinBoxWidth->setMaximum(0xFFFF);
    ui->spinBoxWidth->setEnabled(false);
    ui->spinBoxHeight->setMinimum(1);
    ui->spinBoxHeight->setMaximum(0xFFFF);
    ui->spinBoxHeight->setEnabled(false);


    ui->spinBoxStartX->setMinimum(-0xFFFF);
    ui->spinBoxStartX->setMaximum(0xFFFF);

    ui->spinBoxStartY->setMinimum(-0xFFFF);
    ui->spinBoxStartY->setMaximum(0xFFFF);
    connect(ui->spinBoxStartX, QOverload<int>::of(&QSpinBox::valueChanged),this,&MCCorrect::slot_paintStartPosChanged);
    connect(ui->spinBoxStartY, QOverload<int>::of(&QSpinBox::valueChanged),this,&MCCorrect::slot_paintStartPosChanged);

    QButtonGroup* pButtonGroup = new QButtonGroup(this);
    pButtonGroup->setExclusive(true);
    pButtonGroup->addButton(ui->radioBtnSixPic);
    pButtonGroup->addButton(ui->radioBtnEightPic);
    pButtonGroup->addButton(ui->radioBtn10Pic);
    pButtonGroup->addButton(ui->radioBtnLowGray);
    ui->radioBtnEightPic->setChecked(true);

    //ui->groupBox_6->hide();
}

MCCorrect::~MCCorrect()
{
    delete ui;
}

void MCCorrect::initViewAndScene()
{
    m_scene = ConnectionDiagramScene::instance();

    m_view = ConnectionFrame::instance();
    //m_view->view()->setScene(m_scene);

    //ui->verticalLayout_2->addWidget(m_view);

    connect(m_scene,&ConnectionDiagramScene::sig_connectionSettingChanged,this,&MCCorrect::slot_updateConnectionSetting);
}

void MCCorrect::loadCorrectFilePath(QString path)
{
    QDir fileDir(path);
    if (!fileDir.exists()){
        qDebug()<<path<<" is no exists.";
        return;
    }
    QStringList filters;
    filters << QString("*.bin");
    fileDir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
    fileDir.setNameFilters(filters);
    QFileInfoList fileInfoList = fileDir.entryInfoList(QDir::Files, QDir::Name);
    QMap<int,QString> fileIndexMap;
    for(auto &&info:fileInfoList){
        QString filePath = info.absoluteFilePath();
        QString fileName = info.baseName();
        QStringList splitList = fileName.split("_");
        int fileNum = -1;
        fileNum = splitList.back().toInt();
        fileIndexMap.insert(fileNum,filePath);
    }
    if(m_scene){
        m_scene->setItemCorrectDataFilePath(fileIndexMap);
    }
}

void MCCorrect::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if(m_view){
        //m_view->view()->fitInView(m_scene->moduleBoundingRect(), Qt::KeepAspectRatio);
    }
}

void MCCorrect::slot_ConnectItem()
{
    on_btnConnectionRead_clicked();
}

void MCCorrect::slot_EnterNavigatPage()
{
    m_view->setCurrentMode(ConnectionDiagramScene::Mode::Correct);
    if(m_scene){
        m_scene->sortItemToCorrectData();
    }
    //m_view->setCurrentMode(m_view->currentMode());
    //m_view->view()->fitInView(m_scene->moduleBoundingRect(), Qt::KeepAspectRatio);
}

void MCCorrect::on_btnConnectionRead_clicked()
{
    if (LAPI::EResult::ER_Success == LAPI::ReadConnection()) {
        LBLConnection* connection = LAPI::GetConnection();
        if (connection) {
            m_scene->drawConnection(connection);
            ICore::statusBar()->showMessage(tr("Connection relationship read successfully."), 1000);
        }
    }
    else {
        ICore::statusBar()->showMessage(tr("Connection relationship read failed."), 1000);
    }
}

void MCCorrect::slot_updateConnectionSetting()
{
    if(m_scene){
        ui->spinBoxRow->setValue(m_scene->rowCount());
        ui->spinBoxCol->setValue(m_scene->columnCount());
        ui->spinBoxWidth->setValue(m_scene->moduleWidth());
        ui->spinBoxHeight->setValue(m_scene->moduleHeight());
    }
}

void MCCorrect::slot_paintStartPosChanged()
{
    TestScreenHelper::setPaintStartPos(QPoint(ui->spinBoxStartX->value(),ui->spinBoxStartY->value()));
}

void MCCorrect::on_btnErase_clicked()
{
    LAPI::EResult ret = LAPI::EResult::ER_Fail;
    if(ui->radioBtnLowGray->isChecked()){
        ret = LAPI::WriteLowGrayCalibrationDataErase(0xFF,0xFF);
    }
    else{
        ret = LAPI::WriteCalibrationDataErase(0xFF,0xFF);
    }
    Core::ICore::showMessageLAPIResult(ret);
}

void MCCorrect::on_btnReload_clicked()
{
    LAPI::EResult ret = LAPI::EResult::ER_Fail;
    if(ui->radioBtnLowGray->isChecked()){
        ret = LAPI::WriteLowGrayCalibrationDataReload(0xFF,0xFF);
    }
    else{
        ret = LAPI::WriteCalibrationDataReload(0xFF,0xFF);
    }
    Core::ICore::showMessageLAPIResult(ret);
}

void MCCorrect::on_btnSend_clicked()
{
    TestScreenHelper *testScrrenHelper =new TestScreenHelper; //在绘制结束后，会调用deletelater
    QList<QPair<CorrectDataHelper*, QString>> filelist= ConnectionDiagramScene::instance()->correctInfoList();
    QFuture<QPair<CorrectDataHelper*, QSharedPointer<QByteArray>>> future = QtConcurrent::mapped(filelist, CorrectDataHelper::concurrentCreatImage);
    future.waitForFinished();
    QList<QPair<CorrectDataHelper*, QSharedPointer<QByteArray>>> ret = future.results();
    testScrrenHelper->showFullScreenImageList(ret,CorrectDataHelper::correctDataType());
}

void MCCorrect::on_btnSave_clicked()
{
    LAPI::EResult ret = LAPI::EResult::ER_Fail;
    if(ui->radioBtnLowGray->isChecked()){
        ret = LAPI::WriteLowGrayCalibrationDataSave(0xFF,0xFF);
    }
    else{
        ret = LAPI::WriteCalibrationDataSave(0xFF,0xFF);
    }
    Core::ICore::showMessageLAPIResult(ret);
}

void MCCorrect::on_radioBtnSixPic_clicked()
{
    CorrectDataHelper::setCorrectDataType(CorrectDataHelper::CDT_6P);
}

void MCCorrect::on_radioBtnEightPic_clicked()
{
    CorrectDataHelper::setCorrectDataType(CorrectDataHelper::CDT_8P);
}

void MCCorrect::on_radioBtn10Pic_clicked()
{
    CorrectDataHelper::setCorrectDataType(CorrectDataHelper::CDT_10P);
}

void MCCorrect::on_radioBtnLowGray_clicked()
{
    CorrectDataHelper::setCorrectDataType(CorrectDataHelper::CDT_2P_Lowgray);
}

void MCCorrect::on_toolBtnFullScreenData_clicked()
{
    QString filePath = QFileDialog::getExistingDirectory(nullptr,
        QApplication::tr("Open Full Screen Data Directory"),
        App::lastOpenPath,QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (filePath.isEmpty())
    {
        return;
    }
    App::lastOpenPath = filePath;
    App::writeConfig();

    ui->lineEditFullScreenData->setText(filePath);
    loadCorrectFilePath(filePath);
}

