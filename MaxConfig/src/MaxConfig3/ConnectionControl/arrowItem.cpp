#include "arrowItem.h"
#include "moduleItem.h"

#include "Utils/graphicstheme.h"

#include <qmath.h>
#include <QPainter>

using namespace Utils::GraphicsTheme;

Arrow::Arrow(ModuleItem *startItem, ModuleItem *endItem, QGraphicsItem *parent)
	: QGraphicsLineItem(parent)
{
	myStartItem = startItem;
	myEndItem = endItem;
	setFlag(QGraphicsItem::ItemIsSelectable, true);
}
//! [0]

//! [1]
QRectF Arrow::boundingRect() const
{
	qreal extra = (pen().width() + 30) / 1;

	return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
		line().p2().y() - line().p1().y()))
		.normalized()
		.adjusted(-extra, -extra, extra, extra);
}
//! [1]

//! [2]
QPainterPath Arrow::shape() const
{
	QPainterPath path = QGraphicsLineItem::shape();
	path.addPolygon(arrowHead);
	return path;
}
//! [2]

//! [3]
void Arrow::updatePosition()
{
	QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
	setLine(line);
}

void Arrow::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	if (event->button() == Qt::RightButton) {
		event->accept();
		return;
	}

	QGraphicsLineItem::mousePressEvent(event);
}
void Arrow::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsLineItem::mouseMoveEvent(event);
}
void Arrow::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsLineItem::mouseReleaseEvent(event);
}

void Arrow::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    Q_UNUSED(event)
}

//! [3]

//! [4]
void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
	QWidget *)
{
	QColor color;
	if (isSelected()) {
		color = g_ModuleTheme.itemColor(ModultItemTheme::ArrowSelectColor);
	}
	else {
		color = g_ModuleTheme.itemColor(ModultItemTheme::ArrowColor);
	}
	QPen myPen = pen();
	myPen.setColor(color);
	myPen.setWidth(g_ModuleTheme.ArrowPenWidth);
	qreal arrowSize = g_ModuleTheme.ArrowSize;
	painter->setPen(myPen);
	painter->setBrush(color);
	//! [4] //! [5]

	QLineF centerLine(myStartItem->sceneBoundingRect().center(), myEndItem->sceneBoundingRect().center());
	setLine(centerLine);
	//! [5] //! [6]

	double angle = std::atan2(-line().dy(), line().dx());

	QPointF arrowP1 = line().center() - QPointF(sin(angle + M_PI / 3) * arrowSize,
		cos(angle + M_PI / 3) * arrowSize);
	QPointF arrowP2 = line().center() - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
		cos(angle + M_PI - M_PI / 3) * arrowSize);

	arrowHead.clear();
	arrowHead << line().center() << arrowP1 << arrowP2;
	//! [6] //! [7]
	painter->drawLine(line());
	painter->drawPolygon(arrowHead);
	if (isSelected()) {
		painter->setPen(QPen(color, 1, Qt::DashLine));
		painter->setBrush(Qt::NoBrush);
		//painter->drawRect(boundingRect());
	}
}
//! [7]
