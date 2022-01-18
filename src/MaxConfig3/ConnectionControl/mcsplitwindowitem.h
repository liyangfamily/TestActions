#ifndef MCSPLITWINDOWITEM_H
#define MCSPLITWINDOWITEM_H

#include "LBL_Core/LAPIDefUI.h"

#include <QMenu>
#include <QColor>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

class MCSplitWindowItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    enum ItemOperator
        {
            t_none,
            t_move,
            t_resize,
            t_rotate
        };
    enum { Type = UserType + 16 };
    explicit MCSplitWindowItem(const QString& source,const QColor& color, QGraphicsItem *parent = 0);
    ~MCSplitWindowItem();
    void setSourceName(const QString& str);
    QString sourceName(){
        return m_sourceName;
    }
    void setChannel(LAPI::UI::EHDMIChannel channel);
    LAPI::UI::EHDMIChannel channel(){
        return m_channel;
    }
    void externalChangeSize(const QSizeF& size);
    // 使item可使用qgraphicsitem_cast
    int type() const override;

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;


    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;


protected:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    void customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QSizeF verificationSize(const QSizeF& size);
    int adjustFrontSize();
protected:
    // 处理Item上的类型
    virtual void mouseMoveMoveOperator(const QPointF& scenePos, const QPointF& loacalPos);
    virtual void mouseMoveResizeOperator(const QPointF& scenePos, const QPointF& loacalPos);
    //virtual void mouseMoveRotateOperator(const QPointF& scenePos, const QPointF& loacalPos);

signals:
    void sig_WindowRectChanged(QRectF rt);
public slots:
    void slot_saveItemInfo();
    void slot_saveAllItemInfo();
private:
    static QImage m_closeIcon;
    static QImage m_resizeIcon;
    static QImage m_rotateIcon;

    QPixmap m_closePixmap;
    QPixmap m_resizePixmap;
    QPixmap m_rotatePixmap;

    ItemOperator m_itemOper = t_none;

    QPointF m_pos;              // 本地所坐标点击的点
    QPointF m_pressedPos;       // 场景坐标点击的点
    QPointF m_startPos;         // Item再场景坐标的起始坐标

    int m_nInterval = 10;
    int m_nEllipseWidth = 20;    // 半径

    // 画笔设置
    QColor m_cPenColor;
    int m_nPenWidth = 5;
    // 画刷设置
    QColor m_cBrushColor;
    //推荐字体大小
    int m_frontSize=90;

    //Window Title Name
    QString m_titleName;
    QString m_sourceName;
    LAPI::UI::EHDMIChannel m_channel;

    QMenu myContextMenu;
    QAction *m_SaveItemAction=nullptr;
    QAction *m_SaveAllItemAction=nullptr;
};

#endif // MCSPLITWINDOWITEM_H
