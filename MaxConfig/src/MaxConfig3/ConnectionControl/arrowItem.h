#pragma once
#include <QGraphicsLineItem>

class ModuleItem;
class Arrow : public QGraphicsLineItem
{
public:
	enum { Type = UserType + 4 };

	Arrow(ModuleItem *startItem, ModuleItem *endItem,
		QGraphicsItem *parent = 0);

	int type() const override { return Type; }
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	ModuleItem *startItem() const { return myStartItem; }
	ModuleItem *endItem() const { return myEndItem; }

	void updatePosition();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

private:
	ModuleItem *myStartItem;
	ModuleItem *myEndItem;
	QPolygonF arrowHead;
};