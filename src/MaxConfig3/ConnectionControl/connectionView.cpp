/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "connectionView.h"

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif
#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#else
#include <QtWidgets>
#endif
#include <qmath.h>

#include "Core/icore.h"

InteractiveView::InteractiveView(ConnectionFrame *v)
	: QGraphicsView(v),
	view(v),
	m_scale(1.0),
	m_zoomDelta(0.1)
{
	setRenderHint(QPainter::Antialiasing, false);
	setDragMode(QGraphicsView::RubberBandDrag);
	setOptimizationFlags(QGraphicsView::DontSavePainterState);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	setSceneRect(0, 0, SHRT_MAX, SHRT_MAX);
	centerOn(0, 0);
}

void InteractiveView::setZoomDelta(qreal delta)
{
	// 建议增量范围
	Q_ASSERT_X(delta >= 0.0 && delta <= 1.0,
		"InteractiveView::setZoomDelta", "Delta should be in range [0.0, 1.0].");
	m_zoomDelta = delta;
}

qreal InteractiveView::zoomDelta() const
{
	return m_zoomDelta;
}

void InteractiveView::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Plus:  // 放大
		zoomIn();
		break;
	case Qt::Key_Minus:  // 缩小
		zoomOut();
		break;
	case Qt::Key_Alt:
	{
		setCursor(Qt::OpenHandCursor);
		setDragMode(QGraphicsView::ScrollHandDrag);
		dynamic_cast<ConnectionDiagramScene*>(this->scene())->setInteractive(false);
	}
		break;
	default:
		QGraphicsView::keyPressEvent(event);
	}
}

void InteractiveView::keyReleaseEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Alt:
	{
		setCursor(Qt::ArrowCursor);
		setDragMode(QGraphicsView::RubberBandDrag);
		dynamic_cast<ConnectionDiagramScene*>(this->scene())->setInteractive(true);
	}
		break;
	default:
		QGraphicsView::keyReleaseEvent(event);
	}
}

#if QT_CONFIG(wheelevent)
void InteractiveView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier) {
		// 滚轮的滚动量
		QPoint scrollAmount = e->angleDelta();
		// 正值表示滚轮远离使用者（放大），负值表示朝向使用者（缩小）
		scrollAmount.y() > 0 ? zoomIn() : zoomOut();
    } 
	else if (e->modifiers() & Qt::ShiftModifier) {
		if (e->delta() > 0)
			this->horizontalScrollBar()->triggerAction(QAbstractSlider::SliderSingleStepSub);
		else
			this->horizontalScrollBar()->triggerAction(QAbstractSlider::SliderSingleStepAdd);
		e->accept();
	}
	else {
		
        QGraphicsView::wheelEvent(e);
    }
}
#endif

void InteractiveView::zoomIn()
{
	zoom(1 + m_zoomDelta);
}

void InteractiveView::zoomOut()
{
	zoom(1 - m_zoomDelta);
}

void InteractiveView::zoom(float scaleFactor)
{
	qreal scaled = m_scale * scaleFactor;
	if (scaled < 0.1 || scaled > 10) {
		return;
	}
	zoomTo(scaled);
}

void InteractiveView::zoomTo(qreal scale /*= 1*/)
{
	if (scale < 0.1 || scale > 10) {
		return;
	}
	m_scale = scale;
	QMatrix oldMatrix = this->matrix();
	this->resetMatrix();
	this->translate(oldMatrix.dx(), oldMatrix.dy());
	this->scale(scale, scale);
	qDebug() << m_scale;
}



ConnectionFrame* ConnectionFrame::s_connectionView = nullptr;

ConnectionFrame::ConnectionFrame(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(Sunken | StyledPanel);
    graphicsView = new InteractiveView(this);

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);

    resetButton = new QToolButton;
    resetButton->setText(tr("Reset"));
    resetButton->setEnabled(false);

    // Label layout
    QHBoxLayout *labelLayout = new QHBoxLayout;
    label2 = new QLabel(tr("Pointer Mode"));
    selectModeButton = new QToolButton;
    selectModeButton->setText(tr("Select"));
    selectModeButton->setCheckable(true);
    selectModeButton->setChecked(true);
    dragModeButton = new QToolButton;
    dragModeButton->setText(tr("Drag"));
    dragModeButton->setCheckable(true);
    dragModeButton->setChecked(false);
	correctModeButton = new QToolButton;
	correctModeButton->setText(tr("Correct"));
	correctModeButton->setCheckable(true);
	correctModeButton->setChecked(false);
    antialiasButton = new QToolButton;
    antialiasButton->setText(tr("Antialiasing"));
    antialiasButton->setCheckable(true);
    antialiasButton->setChecked(false);
    fitInViewButton = new QToolButton;
    fitInViewButton->setText(tr("Fit Screen"));
    fitInViewButton->setCheckable(false);
    fitInViewButton->setChecked(false);
    openGlButton = new QToolButton;
    openGlButton->setText(tr("OpenGL"));
    openGlButton->setCheckable(true);
#ifndef QT_NO_OPENGL
    openGlButton->setEnabled(QGLFormat::hasOpenGL());
#else
    openGlButton->setEnabled(false);
#endif
    printButton = new QToolButton;
    printButton->setText("Print");
    printButton->setIcon(QIcon(QPixmap(":/fileprint.png")));

    QButtonGroup *pointerModeGroup = new QButtonGroup(this);
    pointerModeGroup->setExclusive(true);
    pointerModeGroup->addButton(selectModeButton);
    pointerModeGroup->addButton(dragModeButton);
    pointerModeGroup->addButton(correctModeButton);

    labelLayout->addWidget(label2);
    labelLayout->addWidget(selectModeButton);
    labelLayout->addWidget(dragModeButton);
    labelLayout->addWidget(correctModeButton);
    labelLayout->addStretch();
    //labelLayout->addWidget(antialiasButton);
    labelLayout->addWidget(fitInViewButton);
    labelLayout->addWidget(resetButton);
    labelLayout->addWidget(printButton);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(labelLayout, 0, 0);
    topLayout->addWidget(graphicsView, 1, 0);
    setLayout(topLayout);

    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetView()));
    connect(graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(setResetButtonEnabled()));
    connect(graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(setResetButtonEnabled()));
    connect(selectModeButton, SIGNAL(clicked()), this, SLOT(togglePointerMode()));
    connect(dragModeButton, SIGNAL(clicked()), this, SLOT(togglePointerMode()));
    connect(correctModeButton, SIGNAL(clicked()), this, SLOT(togglePointerMode()));
    connect(antialiasButton, SIGNAL(toggled(bool)), this, SLOT(toggleAntialiasing()));
    connect(fitInViewButton, SIGNAL(clicked()), this, SLOT(toggleFitInView()));
    connect(openGlButton, SIGNAL(toggled(bool)), this, SLOT(toggleOpenGL()));
    connect(printButton, SIGNAL(clicked()), this, SLOT(print()));

    antialiasButton->setChecked(true);
}

void ConnectionFrame::creatConnectionFrame(QWidget *parent)
{
    s_connectionView = new ConnectionFrame(parent);
}

ConnectionFrame *ConnectionFrame::instance()
{
    if (!s_connectionView) {
        QSharedPointer<ConnectionFrame> p(new ConnectionFrame(Core::ICore::mainWindow()));
        s_connectionView = p.get();
    }
    return s_connectionView;
}

InteractiveView *ConnectionFrame::view() const
{
    return graphicsView;
}

void ConnectionFrame::setCurrentMode(ConnectionDiagramScene::Mode mode)
{
    m_currentMode=mode;
    switch(mode){
    case ConnectionDiagramScene::Mode::SceneEdit:
    {
        ConnectionDiagramScene::instance()->setSceneMode(mode);
        graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
        selectModeButton->show();
        dragModeButton->show();
        correctModeButton->hide();
        selectModeButton->setChecked(true);
    }
    break;
    case ConnectionDiagramScene::Mode::SceneView:
    {
        ConnectionDiagramScene::instance()->setSceneMode(mode);
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        selectModeButton->show();
        dragModeButton->show();
        correctModeButton->hide();
        dragModeButton->setChecked(true);
    }
    break;
    case ConnectionDiagramScene::Mode::Correct:
    {
        ConnectionDiagramScene::instance()->setSceneMode(mode);
        graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
        selectModeButton->hide();
        dragModeButton->hide();
        correctModeButton->show();
        correctModeButton->setChecked(true);
    }
    break;
    default:
        break;
    }
}

void ConnectionFrame::resetView()
{
    graphicsView->zoomTo(0.5);
    graphicsView->ensureVisible(QRectF(0, 0, 0, 0));

    resetButton->setEnabled(false);
}

void ConnectionFrame::setResetButtonEnabled()
{
    resetButton->setEnabled(true);
}

void ConnectionFrame::togglePointerMode()
{
	if (selectModeButton->isChecked()) {
        setCurrentMode(ConnectionDiagramScene::SceneEdit);
	}
    else if (dragModeButton->isChecked()) {
        setCurrentMode(ConnectionDiagramScene::SceneView);
	}
    else if (correctModeButton->isChecked()) {
        setCurrentMode(ConnectionDiagramScene::Correct);
	}
}

void ConnectionFrame::toggleOpenGL()
{
#ifndef QT_NO_OPENGL
    graphicsView->setViewport(openGlButton->isChecked() ? new QGLWidget(QGLFormat(QGL::SampleBuffers)) : new QWidget);
#endif
}

void ConnectionFrame::toggleFitInView()
{
    this->view()->fitInView(ConnectionDiagramScene::instance()->moduleBoundingRect(), Qt::KeepAspectRatio);

    resetButton->setEnabled(true);
}

void ConnectionFrame::toggleAntialiasing()
{
    graphicsView->setRenderHint(QPainter::Antialiasing, antialiasButton->isChecked());
}

void ConnectionFrame::print()
{
#if QT_CONFIG(printdialog)
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        graphicsView->render(&painter);
    }
#endif
}
