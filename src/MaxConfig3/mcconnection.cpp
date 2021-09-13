#include "mcconnection.h"
#include "ui_mcconnection.h"

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

MCConnection::MCConnection(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::MCConnection)
{
	ui->setupUi(this);

	initViewAndScene();

	m_portBtnGroup = new QButtonGroup(this);
	for (int i = 0; i < 20; ++i) {
		QPushButton *btn = this->findChild<QPushButton*>(QString("btnPort%1").arg(i + 1));
		m_portBtnGroup->addButton(btn, i);
		btn->setCheckable(true);
        connect(btn, &QPushButton::clicked, this,&MCConnection::slot_OperatPortClicked);
    }
	ui->btnPort1->setChecked(true);

    connect(ui->spinBoxRow, QOverload<int>::of(&QSpinBox::valueChanged),m_scene,&ConnectionDiagramScene::setRowCount);
    connect(ui->spinBoxCol, QOverload<int>::of(&QSpinBox::valueChanged),m_scene,&ConnectionDiagramScene::setColumnCount);
    connect(ui->spinBoxWidth, QOverload<int>::of(&QSpinBox::valueChanged),m_scene,&ConnectionDiagramScene::setModuleWidth);
    connect(ui->spinBoxHeight, QOverload<int>::of(&QSpinBox::valueChanged),m_scene,&ConnectionDiagramScene::setModuleHeight);

	ui->spinBoxRow->setMinimum(0);
	//ui->spinBoxRow->setValue(5);
	ui->spinBoxCol->setMinimum(0);
	//ui->spinBoxCol->setValue(5);
	ui->spinBoxWidth->setMinimum(1);
	ui->spinBoxWidth->setMaximum(0xFFFF);
	//ui->spinBoxWidth->setValue(480);
	ui->spinBoxHeight->setMinimum(1);
	ui->spinBoxHeight->setMaximum(0xFFFF);
	//ui->spinBoxHeight->setValue(270);

}

MCConnection::~MCConnection()
{
	delete ui;
}

void MCConnection::initViewAndScene()
{
//	ConnectionDiagramScene::creatConnectionDiagramScene(this);
    m_scene = ConnectionDiagramScene::instance();

    m_view = ConnectionFrame::instance();
//    m_view->view()->setScene(m_scene);
//    m_view->setCurrentMode(ConnectionDiagramScene::Mode::SceneEdit);

//    ui->verticalLayout_2->addWidget(m_view);

//	// Add the vertical lines first, paint them red
//	for (int x = 0; x <= m_scene->sceneRect().width(); x += 50)
//		m_scene->addLine(x, 0, x, m_scene->sceneRect().height(), QPen(Qt::darkGray))->setZValue(-100);

//	// Now add the horizontal lines, paint them green
//	for (int y = 0; y <= m_scene->sceneRect().height(); y += 50)
//		m_scene->addLine(0, y, m_scene->sceneRect().width(), y, QPen(Qt::darkGray))->setZValue(-100);
//	//view->view()->fitInView(itemGroup.boundingRect());

    connect(m_scene,&ConnectionDiagramScene::sig_operatPortChanged,this,&MCConnection::slot_OperatPortChanged);
    connect(m_scene,&ConnectionDiagramScene::sig_connectionSettingChanged,this,&MCConnection::slot_updateConnectionSetting);
}


void MCConnection::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
    //m_view->view()->fitInView(m_scene->moduleBoundingRect(), Qt::KeepAspectRatio);
	
}

void MCConnection::slot_ConnectItem()
{
	on_btnConnectionRead_clicked();
}

void MCConnection::slot_EnterNavigatPage()
{
    m_view->setCurrentMode(ConnectionDiagramScene::Mode::SceneEdit);
    //m_view->setCurrentMode(m_view->currentMode());
    //m_view->view()->fitInView(m_scene->moduleBoundingRect(), Qt::KeepAspectRatio);
}

void MCConnection::on_btnItemClear_clicked()
{
    m_scene->clearModuleConnection();
}

void MCConnection::on_btnConnectionRead_clicked()
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

void MCConnection::on_btnConnectionSend_clicked()
{
    LBLConnection* connection = LAPI::GetConnection();
    if (connection) {
        m_scene->creatConnection(connection);
        if (LAPI::EResult::ER_Success == LAPI::WriteConnection(connection)) {
            ICore::statusBar()->showMessage(tr("Connection relationship send successfully."), 1000);
        }
        else {
            ICore::statusBar()->showMessage(tr("Connection relationship send failed."), 1000);
        }
    }
}

void MCConnection::slot_OperatPortClicked()
{
    if (m_portBtnGroup) {
        ConnectionDiagramScene::instance()->setOperatPort(m_portBtnGroup->checkedId());
    }
}

void MCConnection::slot_OperatPortChanged(int port)
{
    if (m_portBtnGroup) {
        QAbstractButton* btn = m_portBtnGroup->button(port);
        if (btn) {
            btn->setChecked(true);
            ConnectionDiagramScene::instance()->setOperatPort(port);
        }
    }
}

void MCConnection::slot_updateConnectionSetting()
{
    if(m_scene){
        ui->spinBoxRow->setValue(m_scene->rowCount());
        ui->spinBoxCol->setValue(m_scene->columnCount());
        ui->spinBoxWidth->setValue(m_scene->moduleWidth());
        ui->spinBoxHeight->setValue(m_scene->moduleHeight());
    }
}
