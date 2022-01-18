#pragma once
#include "Utils/correctdatahelper.h"

#include <QMenu>
#include <QColor>
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <QFocusEvent>
// 自定义 Item
class Arrow;
class ModuleItem : public QGraphicsPolygonItem
{
public:
	enum { Type = UserType + 15 };
	enum Order
	{
		O_Null = 0, //无排列
		O_Start = 1, //队列头
		O_InQueen = 2, //队列中
		O_End = 3, ////队列尾
	};
	
	explicit ModuleItem(QGraphicsItem *parent = 0);
	~ModuleItem();
	void setRect(QRectF rect);
	QRectF rect() const;
	void setPort(int port);
	int port() const;
	void setModuleIndex(int index);
	int moduleIndex() const;
    void setCorrectIndex(int index);
    int correctIndex() const;
	void setOrder(Order o);
	bool isOrder(Order o) const;
	bool isConnected() const;
	bool clearItem();
	void addArrow(Arrow *arrow);
	void removeArrow(Arrow *arrow);
	void removeArrows();
	// 使item可使用qgraphicsitem_cast
    int type() const override;

	CorrectDataHelper* correctDataHelper() {
		return &m_correctHelper;
	}

protected:
    void focusOutEvent(QFocusEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
	QRectF relativeRect();
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
private:
	QMenu* myContextMenu;
	QList<Arrow *> arrows;
	QRectF m_absoluteRect;
	QPolygonF myPolygon;
	QPointF m_centerPoint;
	int m_port = -1;
    int m_correctIndex = -1;
	int m_moduleIndex = -1;
	Order m_moduleOrder = Order::O_Null;

    CorrectDataHelper m_correctHelper;

    QRectF m_test;
    bool m_center=false;
};
