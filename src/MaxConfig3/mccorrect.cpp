#include "mccorrect.h"
#include "ui_mccorrect.h"

#include <LAPIControl>
#include <QVBoxLayout>
#include <QButtonGroup>

#include "ConnectionControl/moduleItem.h"
#include "ConnectionControl/connectionView.h"
#include "ConnectionControl/connectionScene.h"

#include "Core/icore.h"
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


    ui->spinBoxStartX->setMinimum(0);
    ui->spinBoxStartX->setMaximum(0xFFFF);

    ui->spinBoxStartY->setMinimum(0);
    ui->spinBoxStartY->setMaximum(0xFFFF);
    connect(ui->spinBoxStartX, QOverload<int>::of(&QSpinBox::valueChanged),this,&MCCorrect::slot_paintStartPosChanged);
    connect(ui->spinBoxStartY, QOverload<int>::of(&QSpinBox::valueChanged),this,&MCCorrect::slot_paintStartPosChanged);

    QButtonGroup* pButtonGroup = new QButtonGroup(this);
    pButtonGroup->setExclusive(true);
    pButtonGroup->addButton(ui->radioBtnSixPic);
    pButtonGroup->addButton(ui->radioBtnEightPic);
    ui->radioBtnEightPic->setChecked(true);
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

void MCCorrect::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if(m_view){
        m_view->view()->fitInView(m_scene->moduleBoundingRect(), Qt::KeepAspectRatio);
    }
}

void MCCorrect::slot_ConnectItem()
{
    on_btnConnectionRead_clicked();
}

void MCCorrect::slot_EnterNavigatPage()
{
    m_view->setCurrentMode(ConnectionDiagramScene::Mode::Correct);
    //m_view->setCurrentMode(m_view->currentMode());
    m_view->view()->fitInView(m_scene->moduleBoundingRect(), Qt::KeepAspectRatio);
}

void MCCorrect::on_btnConnectionRead_clicked()
{
    if (LAPI::EResult::ER_Success == LAPI::ReadConnection()) {
        LBLConnection* connection = LAPI::GetConnection();
        if (connection) {
            m_scene->drawConnection(connection);
            ICore::statusBar()->showMessage(tr("连接关系读取成功."), 1000);
        }
    }
    else {
        ICore::statusBar()->showMessage(tr("连接关系读取失败."), 1000);
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
    LAPI::EResult ret = LAPI::WriteCalibrationDataErase(0xFF,0xFF);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCCorrect::on_btnReload_clicked()
{
    LAPI::EResult ret = LAPI::WriteCalibrationDataReload(0xFF,0xFF);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCCorrect::on_btnSend_clicked()
{
    QList<QPair<CorrectDataHelper*, QString>> filelist= ConnectionDiagramScene::instance()->correctInfoList();
    QFuture<QPair<CorrectDataHelper*, QSharedPointer<QByteArray>>> future = QtConcurrent::mapped(filelist, CorrectDataHelper::concurrentCreatImage);
    future.waitForFinished();
    QList<QPair<CorrectDataHelper*, QSharedPointer<QByteArray>>> ret = future.results();
    m_testScrrenHelper.showImageList(ret,CorrectDataHelper::correctDataType());
}

void MCCorrect::on_btnSave_clicked()
{
    LAPI::EResult ret = LAPI::WriteCalibrationDataSave(0xFF,0xFF);
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
