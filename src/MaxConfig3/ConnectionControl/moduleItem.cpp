#include "moduleItem.h"
#include "arrowItem.h"

#include "connectionScene.h"
#include "Utils/graphicstheme.h"
#include "Core/icore.h"

#include <qmath.h>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QApplication>
#include <QAction>
#include <QIcon>
#include <QFileInfo>
#include <QString>

using namespace Utils::GraphicsTheme;
// 自定义 Item
ModuleItem::ModuleItem(QGraphicsItem *parent)
	: QGraphicsPolygonItem(parent)
{
	// 画笔 - 边框色
	QPen p = pen();
	p.setWidth(g_ModuleTheme.BorderPenWidth);
	p.setColor(g_ModuleTheme.itemColor(ModultItemTheme::RectBorderColor));
	setPen(p);

	// 可选择、可移动
    setFlags(QGraphicsItem::ItemIsSelectable |/* QGraphicsItem::ItemIsMovable | */QGraphicsItem::ItemSendsGeometryChanges
             |QGraphicsItem::ItemIsFocusable);
}

ModuleItem::~ModuleItem()
{
}

void ModuleItem::setRect(QRectF rect)
{
	m_absoluteRect = rect;

	QRectF relativeArea = relativeRect();
	myPolygon.clear();
	myPolygon << QPointF(relativeArea.topLeft()) << QPointF(relativeArea.topRight())
		<< QPointF(relativeArea.bottomRight()) << QPointF(relativeArea.bottomLeft())
		<< QPointF(relativeArea.topLeft());
	setPolygon(myPolygon);

    m_centerPoint = m_absoluteRect.topLeft();
    setPos(m_centerPoint);

	m_correctHelper.setPaintRect(rect.toRect());
}

QRectF ModuleItem::rect() const
{
	return m_absoluteRect;
}

void ModuleItem::setPort(int port)
{
	m_port = port;

    m_correctHelper.setPort(m_port);
	// 画刷 - 背景色
	setBrush(g_ModuleTheme.portColor(ModultItemTheme::PortColor(m_port)));
}

int ModuleItem::port() const
{
	return m_port;
}

void ModuleItem::setModuleIndex(int index)
{
	m_moduleIndex = index;
    m_correctHelper.setModuleIndex(m_moduleIndex);
	update(this->boundingRect());
}

int ModuleItem::moduleIndex() const
{
    return m_moduleIndex;
}

void ModuleItem::setCorrectIndex(int index)
{
    m_correctIndex = index;
}

int ModuleItem::correctIndex() const
{
    return m_correctIndex;
}

void ModuleItem::setOrder(Order o)
{
	m_moduleOrder = o;
	update(this->boundingRect());
}

bool ModuleItem::isOrder(Order o) const
{
	return (m_moduleOrder == o);
}

bool ModuleItem::isConnected() const
{
	return (m_moduleOrder != Order::O_Null);
}

bool ModuleItem::clearItem()
{
	m_port = -1;
	m_moduleIndex = -1;
	m_moduleOrder = Order::O_Null;
	removeArrows();
	setBrush(g_ModuleTheme.portColor(ModultItemTheme::PortColor::Port_Null));
	return true;
}

void ModuleItem::addArrow(Arrow *arrow)
{
	arrows.append(arrow);
}

void ModuleItem::removeArrow(Arrow *arrow)
{
	int index = arrows.indexOf(arrow);

	if (index != -1)
		arrows.removeAt(index);
}

void ModuleItem::removeArrows()
{
	foreach(Arrow *arrow, arrows) {
		arrow->startItem()->removeArrow(arrow);
		arrow->endItem()->removeArrow(arrow);
		scene()->removeItem(arrow);
		delete arrow;
	}
}

#include <QMessageBox>
void ModuleItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(ConnectionDiagramScene::instance()->isSceneMode(ConnectionDiagramScene::ModuleParam)){
        //QMessageBox::information(Core::ICore::mainWindow(),"Test","This is Test Dialog.");
    }
    if(!m_test.isEmpty()){
        if(m_test.contains(event->pos())){
            //m_center = true;
            this->update();
        }
    }
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void ModuleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		if (event->modifiers() == Qt::ShiftModifier) {
            //qDebug() << "Custom item left clicked with shift key.";
			// 选中 item
			setSelected(true);
		}
		else if (event->modifiers() == Qt::AltModifier) {
            //qDebug() << "Custom item left clicked with alt key.";
		}
		else {
            //qDebug() << "Custom item left clicked.";
			event->accept();
			//QGraphicsItem::mousePressEvent(event);
		}
	}
	else if (event->button() == Qt::RightButton) {
        //qDebug() << "Custom item right clicked.";
		if (!scene()->selectedItems().contains(this)) {
			scene()->clearSelection();
			setSelected(true);
		}
		//QGraphicsItem::mousePressEvent(event);
		//event->accept();
	}
}

void ModuleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if ((event->modifiers() == Qt::AltModifier)) {
		QPointF pos = event->scenePos();
	}
	else if (event->modifiers() != Qt::AltModifier) {
        //qDebug() << "Custom item moved.";
		QGraphicsItem::mouseMoveEvent(event);
        //qDebug() << "moved" << pos();
	}
}

void ModuleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if ((event->modifiers() == Qt::AltModifier)) {

	}
	else {
		QGraphicsItem::mouseReleaseEvent(event);
	}
}

void ModuleItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (this->isConnected() && this->isSelected() && ConnectionDiagramScene::instance()->isSceneMode(ConnectionDiagramScene::Correct)) {
		m_correctHelper.correctMenu()->exec(event->screenPos());
	}
}

QVariant ModuleItem::itemChange(GraphicsItemChange change, const QVariant & value)
{
	if (change == ItemPositionChange && scene()) // 控件发生移动
	{
		QPointF newPos = value.toPointF(); //即将要移动的位置
		QRectF rect(0, 0, scene()->width(), scene()->height()); // 你要限制的区域
		if (!rect.contains(newPos)) // 是否在区域内
		{
			newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
			newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
			return newPos;
		}
	}
	return QGraphicsItem::itemChange(change, value);
}

QRectF ModuleItem::relativeRect()
{
	QRectF relativeArea = QRectF(0, 0, m_absoluteRect.width(), m_absoluteRect.height());
    //relativeArea.moveTo(-relativeArea.width() / 2, -relativeArea.height() / 2);
	return relativeArea;
}

int ModuleItem::type() const
{
    return Type;
}

void ModuleItem::focusOutEvent(QFocusEvent *event)
{
    if(m_center){
        m_center = false;
        this->update();
    }
    qDebug()<<"111111111111";
    QGraphicsItem::focusOutEvent(event);
}

void ModuleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/)
{
    Q_UNUSED(widget)
	painter->save();
	QPen p = pen();
	p.setWidth(g_ModuleTheme.BorderPenWidth);
	p.setColor(g_ModuleTheme.itemColor(ModultItemTheme::RectBorderColor));
	QColor color = g_ModuleTheme.portColor(ModultItemTheme::PortColor(m_port));
	QColor fillColor = (option->state & QStyle::State_Selected) ? color.light(120) : color;
	painter->setPen(p);
	painter->setBrush(fillColor);
	painter->drawPolygon(myPolygon);
	painter->restore();

	//QGraphicsPolygonItem::paint(painter, option, widget);
	QRectF rectItem = this->relativeRect();
	qreal ratioItem = rectItem.height() / rectItem.width();
    Q_UNUSED(ratioItem)

	painter->setPen(g_ModuleTheme.itemColor(ModultItemTheme::RectAnchorPointBorderColor));
	painter->setBrush(QBrush(g_ModuleTheme.itemColor(ModultItemTheme::RectAnchorPointColor)));
	painter->setFont(g_ModuleTheme.ItemFont);

	//set rectAnchorPointSize
	QSize rectSize = QSize(g_ModuleTheme.RectAnchorPointSize, g_ModuleTheme.RectAnchorPointSize);
	QRectF rect(rectItem.center() - QPointF(rectSize.width() / 2, rectSize.height() / 2), rectSize);

	//draw Start
	if (m_moduleOrder == Order::O_Start) {
		QLineF line(rectItem.center(), rectItem.center() + QPointF(g_ModuleTheme.RectAnchorPointSize / 2, 0));
		//set line angle
		if (!arrows.isEmpty()) {
			Arrow *arrow = arrows.front();
			if (arrow) {
				qreal linrAngle = arrow->line().angle();
				line.setAngle(linrAngle);
			}
		}
		if (!line.isNull()) {
			qreal arrowSize = g_ModuleTheme.RectAnchorPointSize;
			double angle = std::atan2(-line.dy(), line.dx());

			QPointF arrowP1 = line.p2() - QPointF(sin(angle + M_PI / 3) * arrowSize,
				cos(angle + M_PI / 3) * arrowSize);
			QPointF arrowP2 = line.p2() - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
				cos(angle + M_PI - M_PI / 3) * arrowSize);
			QPolygonF arrowHead;
			arrowHead << line.p2() << arrowP1 << arrowP2;

			painter->drawPolygon(arrowHead);
		}
	}
	//draw End
	else if (m_moduleOrder == Order::O_End) {
		painter->drawRect(rect);
	}
	else if (m_moduleOrder == Order::O_InQueen) {
        m_test = rect.adjusted(8, 8, -8, -8);
        painter->save();
        if(m_center){
            painter->setBrush(Qt::white);
        }
        painter->drawEllipse(rect.adjusted(8, 8, -8, -8));
        painter->restore();
	}
    QPointF textStartPos=rectItem.topLeft();
	//draw Port and Module Index
    painter->translate(20, 20);
    painter->setPen(g_ModuleTheme.itemColor(ModultItemTheme::TextColor));
	if (m_moduleOrder != Order::O_Null) {
		QFontMetrics fm(g_ModuleTheme.ItemFont);
        QString text = QString(" %1-%2").arg(m_port + 1).arg(m_moduleIndex+1);
        if(ConnectionDiagramScene::instance()->sceneMode()==ConnectionDiagramScene::Correct){
            text = QString(" %1").arg(m_correctIndex);
        }
        int width = rectItem.width() - 40; // 显示文本的宽度，为窗口的宽度减去 40 像素
        int flags = Qt::TextWrapAnywhere | Qt::AlignLeft; // 自动换行
        // 计算文本在指定宽度下的包围矩形
        QFontMetrics metrics = painter->fontMetrics();
        QRect textBoundingRect = metrics.boundingRect(QRect(0, 0, width, 1), flags, text);
        //painter->drawRect(textBoundingRect);
        painter->drawText(textBoundingRect, flags, text);
        textStartPos+=QPointF(0,textBoundingRect.height());
	}
    //draw Correct File Info
    if(m_correctHelper.isLoaded()){
        QFontMetrics fm(g_ModuleTheme.ItemFont);
        QString filePath=m_correctHelper.correctFileInfo().second;
        QFileInfo fileInfo(filePath);
        QString text = QString("%1:%2").arg(QApplication::tr("Correct File")).arg(fileInfo.fileName());
        int width = rectItem.width() - 40; // 显示文本的宽度，为窗口的宽度减去 40 像素
        int flags = Qt::TextWrapAnywhere | Qt::AlignLeft; // 自动换行
        // 计算文本在指定宽度下的包围矩形
        QFontMetrics metrics = painter->fontMetrics();
        QRect textBoundingRect = metrics.boundingRect(QRect(0, 0, width, 1), flags, text);
        painter->translate(0, textStartPos.y());
        //painter->drawRect(textBoundingRect);
        painter->drawText(textBoundingRect, flags, text);
        textStartPos+=QPointF(0,textBoundingRect.height());

    }
}
