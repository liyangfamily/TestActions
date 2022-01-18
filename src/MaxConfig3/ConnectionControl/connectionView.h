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

#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QSharedPointer>
#include <QGraphicsView>
#include "connectionScene.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class ConnectionFrame;

class InteractiveView : public QGraphicsView
{
    Q_OBJECT
public:
	InteractiveView(ConnectionFrame *v);

	// 缩放的增量
	void setZoomDelta(qreal delta);
	qreal zoomDelta() const;

protected:
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	
#if QT_CONFIG(wheelevent)
	void wheelEvent(QWheelEvent *) Q_DECL_OVERRIDE;
#endif
public Q_SLOTS:
	void zoomIn();  // 放大
	void zoomOut();  // 缩小
	void zoom(float scaleFactor); // 缩放 - scaleFactor：缩放的比例因子
	void zoomTo(qreal scale = 1); // 缩放到

private:
	qreal m_zoomDelta;  // 缩放的增量
	qreal m_scale;  // 缩放值

private:
    ConnectionFrame *view;
};

class ConnectionFrame : public QFrame
{
    Q_OBJECT
public:
    explicit ConnectionFrame(QWidget *parent = 0);

    static void creatConnectionFrame(QWidget * parent);
    static ConnectionFrame* instance();

    InteractiveView *view() const;

    void setCurrentMode(ConnectionDiagramScene::Mode mode);
    ConnectionDiagramScene::Mode currentMode(){
        return m_currentMode;
    }
private slots:
    void resetView();
    void setResetButtonEnabled();
    void togglePointerMode();
    void toggleOpenGL();
    void toggleFitInView();
    void toggleAntialiasing();
    void print();
    void clearScene();

private:
    InteractiveView *graphicsView;
    QLabel *label;
    QLabel *label2;
    QToolButton *selectModeButton;
    QToolButton *dragModeButton;
    QToolButton *correctModeButton;
    QToolButton *openGlButton;
    QToolButton *fitInViewButton;
    QToolButton *antialiasButton;
    QToolButton *printButton;
    QToolButton *resetButton;
    QToolButton *clearButton;

    ConnectionDiagramScene::Mode m_currentMode=ConnectionDiagramScene::Mode::SceneEdit;
    static ConnectionFrame* s_connectionView;
};

#endif // VIEW_H
