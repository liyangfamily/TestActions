#include "testscreenhelper.h"
#include "correctdatahelper.h"

#include <QPainter>

QPoint TestScreenHelper::m_paintStartPos;

TestScreenHelper::TestScreenHelper(QWidget *parent)
	: QDialog(parent)
{
	this->setWindowFlags(Qt::ToolTip | Qt::WindowStaysOnTopHint);	//窗口
	this->move(0, 0);
	this->setCursor(QCursor(Qt::BlankCursor));
	connect(&m_showTimer, &QTimer::timeout, this, &TestScreenHelper::showImageTimeOut);
}

TestScreenHelper::~TestScreenHelper()
{
}

void TestScreenHelper::showImageList(QList<QPair<CorrectDataHelper*, QSharedPointer<QByteArray>>> imageData,
                                     const CorrectDataHelper::CorrectDataType type)
{
    switch (type)
    {
    case CorrectDataHelper::CDT_6P:
    {
        m_drawImageCount = 6;
    }
        break;
    case CorrectDataHelper::CDT_8P:
    {
        m_drawImageCount = 8;
    }
        break;
    default:
        break;
    }
	m_drawImageIndex = 0;
	m_imageData = imageData;
	m_imageList.clear();
	QRect boundingRect;
	for (auto item : m_imageData) {
		boundingRect |= item.first->paintRect();
        m_imageList.append(qMakePair(item.first,
                     CorrectDataHelper::correctDataToImageList((item.second.get()),
                     item.first->paintRect(), item.first->correctDataType())));
    }
    boundingRect.moveTo(boundingRect.topLeft()+m_paintStartPos);
    this->setGeometry(boundingRect);
	this->show();
	this->raise();
    m_showTimer.start(500);
}

void TestScreenHelper::setPaintStartPos(const QPoint &pt)
{
    m_paintStartPos=pt;
}

QPoint TestScreenHelper::paintStartPos()
{
    return m_paintStartPos;
}

void TestScreenHelper::showImageTimeOut()
{
    m_drawImageIndex++;
    if (m_drawImageIndex > m_drawImageCount) {
        m_showTimer.stop();
        hide();
        close();
        m_imageData.clear();
        m_imageList.clear();
    }
	update();
}

void TestScreenHelper::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
	QPainter painter(this);

	if (m_showTimer.isActive()) {
		for (auto item : m_imageList) {
			if (item.second.size() > m_drawImageIndex) {
                QRect rt=QRect(item.first->paintRect().topLeft()-this->geometry().topLeft(),\
                                                        item.first->paintRect().size());
                painter.drawImage(rt,item.second.at(m_drawImageIndex));
			}
		}
	}
}
