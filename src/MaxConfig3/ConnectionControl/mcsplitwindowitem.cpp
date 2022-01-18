#include "mcsplitwindowitem.h"

#include <QPen>
#include <QDebug>
#include <QGraphicsScene>

#define PI 3.14159265358979

QImage MCSplitWindowItem::m_closeIcon;
QImage MCSplitWindowItem::m_resizeIcon;
QImage MCSplitWindowItem::m_rotateIcon;

MCSplitWindowItem::MCSplitWindowItem(const QString& source,const QColor& color,  QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
    ,m_cPenColor(255, 255, 255)
    ,m_cBrushColor(color)
    ,m_sourceName(source)
    ,m_channel(LAPI::UI::EHDMIChannel::EHC_All)
{
    setAcceptHoverEvents(true);

    // 可选择、可移动
    setFlags(QGraphicsItem::ItemIsSelectable /*| QGraphicsItem::ItemIsMovable */| QGraphicsItem::ItemSendsGeometryChanges);

    m_SaveItemAction = new QAction(QIcon(":/Defaluat/Resources/Default/Menu/save.png"), tr("Save Item"), this);
    connect(m_SaveItemAction, &QAction::triggered, this, &MCSplitWindowItem::slot_saveItemInfo);
    m_SaveAllItemAction = new QAction(QIcon(":/Defaluat/Resources/Default/Menu/save.png"), tr("Save All Item"), this);
    connect(m_SaveAllItemAction, &QAction::triggered, this, &MCSplitWindowItem::slot_saveAllItemInfo);

    myContextMenu.addAction(m_SaveItemAction);
    myContextMenu.addAction(m_SaveAllItemAction);
    myContextMenu.setWindowFlag(Qt::FramelessWindowHint);        //重要
    myContextMenu.setWindowFlag(Qt::NoDropShadowWindowHint);     //重要
    myContextMenu.setAttribute(Qt::WA_TranslucentBackground);
}

MCSplitWindowItem::~MCSplitWindowItem()
{

}

void MCSplitWindowItem::setSourceName(const QString &str)
{
    m_sourceName=str;
    setChannel(this->channel());
}

void MCSplitWindowItem::setChannel(LAPI::UI::EHDMIChannel channel)
{
    m_channel=channel;
    m_titleName=tr("Screen %1:").arg((int)this->channel())+m_sourceName;
    adjustFrontSize();
}

void MCSplitWindowItem::externalChangeSize(const QSizeF& size)
{
    QSizeF tempSize = verificationSize(size);
    this->setRect(QRectF(this->rect().topLeft(),tempSize));
    if(this->isSelected()){
        emit sig_WindowRectChanged(QRectF(this->scenePos(),this->rect().size()));
    }
    this->update();
}

int MCSplitWindowItem::type() const
{
    return Type;
}

void MCSplitWindowItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    // 获取场景坐标和本地坐标
    if(this->flags()&QGraphicsItem::ItemIsSelectable){
        QPointF scenePos = event->scenePos();
        QPointF pos = event->pos();

        QRectF itemRect = this->rect();
        QRectF outLintRect = itemRect.adjusted(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);
        if (QLineF(pos, outLintRect.bottomRight()).length() <= m_nEllipseWidth){
            this->setCursor(Qt::SizeFDiagCursor);
        }
        else{
            this->setCursor(Qt::ArrowCursor);
        }
    }
    QGraphicsRectItem::hoverMoveEvent(event);
}

void MCSplitWindowItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
    QGraphicsRectItem::hoverLeaveEvent(event);
}

void MCSplitWindowItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem *> list1 = this->scene()->items();
    for(auto item:list1){
        if(item->type()==Type){
            item->stackBefore(this);
            item->setSelected(false);
        }
    }

    if (event->button() == Qt::LeftButton) {
        QRectF itemRect = this->rect();
        QRectF outLintRect = itemRect.adjusted(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);

        // 获取当前模式
        QPointF pos = event->pos();
        QPointF scenePos = event->scenePos();
        if (itemRect.contains(pos))
            m_itemOper = t_move;
        else if (QLineF(pos, outLintRect.topRight()).length() <= m_nEllipseWidth)
            m_itemOper = t_resize;
        else if (QLineF(pos, outLintRect.bottomLeft()).length() <= m_nEllipseWidth)
            m_itemOper = t_resize;
        else if (QLineF(pos, outLintRect.bottomRight()).length() <= m_nEllipseWidth)
            m_itemOper = t_resize;

        // 保存当前的一些信息
        m_pos = pos;
        m_pressedPos = scenePos;
        m_startPos = this->pos();
        setSelected(true);
    }
    else if (event->button() == Qt::RightButton) {
        setSelected(true);
    }
    if(this->isSelected()){
        emit sig_WindowRectChanged(QRectF(this->scenePos(),this->rect().size()));
    }
    //return QGraphicsItem::mousePressEvent(event);
}

void MCSplitWindowItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // 获取场景坐标和本地坐标
    QPointF scenePos = event->scenePos();
    QPointF pos = event->pos();

    if (m_itemOper == t_resize)
    {
        // 处理更改大小
        mouseMoveResizeOperator(scenePos, pos);
    }
    else if (m_itemOper == t_move)
    {
        if(this->isSelected()){
            // 处理移动
            mouseMoveMoveOperator(scenePos, pos);
        }
    }
    return QGraphicsItem::mouseMoveEvent(event);
}
#include <QPainter>
#include <QTextOption>
void MCSplitWindowItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_itemOper==t_resize||m_itemOper==t_move){
        adjustFrontSize();
    }
    m_itemOper = t_none;
    return QGraphicsItem::mouseReleaseEvent(event);
}

void MCSplitWindowItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (this->isSelected()) {
        myContextMenu.exec(event->screenPos());
    }
    //return QGraphicsItem::contextMenuEvent(event);
}

QVariant MCSplitWindowItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) // 控件发生移动
    {
        QPointF newPos = value.toPointF(); //即将要移动的位置
        QPointF newRightPos = newPos+QPointF(this->rect().bottomRight());
        QRectF rect(0, 0, scene()->width(), scene()->height()); // 你要限制的区域
        if (!rect.contains(newPos)||!rect.contains(newRightPos)) // 是否在区域内
        {
            newPos.setX(qMin(rect.right()-this->rect().width(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom()-this->rect().height(), qMax(newPos.y(), rect.top())));
            return newPos;
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void MCSplitWindowItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    return QGraphicsRectItem::mouseDoubleClickEvent(event);
}

QRectF MCSplitWindowItem::boundingRect() const
{
    QRectF rectF = this->rect();
//    if (!this->isSelected())
//        return rectF;

    rectF.adjust(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);
    rectF.adjust(-m_nEllipseWidth, -m_nEllipseWidth, m_nEllipseWidth, m_nEllipseWidth);

    return rectF;

}

QPainterPath MCSplitWindowItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}

#include <QPainter>
void MCSplitWindowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QGraphicsRectItem::paint(painter,option,widget);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    if(this->isSelected()){
        // 设置画笔
        QPen pen;
        pen.setWidth(m_nPenWidth);
        pen.setColor(m_cPenColor);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);

        QRectF itemRect = this->rect();

        // 绘制轮廓线
        QRectF outLintRect = itemRect.adjusted(-m_nInterval, -m_nInterval, m_nInterval, m_nInterval);
        painter->drawRect(outLintRect);

        painter->setPen(Qt::NoPen);
        painter->setBrush(m_cBrushColor);

        // 绘制控制点
//        painter->drawEllipse(outLintRect.topLeft(), m_nEllipseWidth, m_nEllipseWidth);
//        if (!m_closePixmap.isNull())
//            painter->drawPixmap(QRect(outLintRect.topRight().x() - m_nEllipseWidth / 2, \
//                                      outLintRect.topRight().y() - m_nEllipseWidth / 2, \
//                                      m_nEllipseWidth, m_nEllipseWidth), m_closePixmap);

//        painter->drawEllipse(outLintRect.topRight(), m_nEllipseWidth, m_nEllipseWidth);
//        if (!m_closePixmap.isNull())
//            painter->drawPixmap(QRect(outLintRect.topRight().x() - m_nEllipseWidth / 2, \
//                                      outLintRect.topRight().y() - m_nEllipseWidth / 2, \
//                                      m_nEllipseWidth, m_nEllipseWidth), m_closePixmap);

//        painter->drawEllipse(outLintRect.bottomLeft(), m_nEllipseWidth, m_nEllipseWidth);
//        if (!m_rotatePixmap.isNull())
//            painter->drawPixmap(QRect(outLintRect.bottomLeft().x() - m_nEllipseWidth / 2, \
//                                      outLintRect.bottomLeft().y() - m_nEllipseWidth / 2, \
//                                      m_nEllipseWidth, m_nEllipseWidth), m_rotatePixmap);

        painter->drawEllipse(outLintRect.bottomRight(), m_nEllipseWidth, m_nEllipseWidth);
        if (!m_resizePixmap.isNull())
            painter->drawPixmap(QRect(outLintRect.bottomRight().x() - m_nEllipseWidth / 2, \
                                      outLintRect.bottomRight().y() - m_nEllipseWidth / 2, \
                                      m_nEllipseWidth, m_nEllipseWidth), m_resizePixmap);
    }

    // 自定义绘制
    customPaint(painter, option, widget);

}

void MCSplitWindowItem::customPaint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QPen p;
    p.setWidth(2);
    p.setColor(m_cBrushColor);
    painter->setPen(p);
    painter->setBrush(m_cBrushColor);
    painter->drawRect(this->rect());

    p.setColor(Qt::white);
    painter->setPen(p);

    QFont ft;
    ft.setFamily("Microsoft YaHei");
    ft.setPointSize(m_frontSize);
    painter->setFont(ft);
    //Window Title
    QFontMetrics fm(ft);
    int pixelsWide = fm.width(m_titleName);
    int pixelsHigh = fm.height();
    pixelsWide=pixelsWide>this->rect().width()?this->rect().width():pixelsWide;
    QPointF pt=this->rect().topLeft()+QPointF(m_nInterval*3,m_nInterval);
    QRectF textRt=QRectF(QPointF(0,0),QSize(pixelsWide,pixelsHigh));
    textRt.moveTo(pt);

    painter->drawText(textRt,Qt::TextWordWrap,m_titleName);

    QString posStr=QString("(%1,%2),(%3,%4)").arg(this->scenePos().toPoint().x())
            .arg(this->scenePos().toPoint().y())
            .arg(this->rect().toRect().width())
            .arg(this->rect().toRect().height());

    this->setToolTip(posStr);
    painter->restore();
}

QSizeF MCSplitWindowItem::verificationSize(const QSizeF& size)
{
    qreal itemWidth = size.width();
    qreal itemHeight = size.height();

    QRectF sceneRt=scene()->sceneRect();
    if(sceneRt.isEmpty()||sceneRt.isNull()){
        return size;
    }
    QPointF scenePos=this->scenePos()+QPointF(itemWidth,itemHeight);
    if(scenePos.x()>=sceneRt.width()){
        itemWidth=sceneRt.width()-this->scenePos().x();
    }
    if(scenePos.y()>=sceneRt.height()){
        itemHeight=sceneRt.height()-this->scenePos().y();
    }

    // 设置图片的最小大小为10
    if (itemWidth < 1){
        itemWidth=1;
    }
    if (itemHeight < 1){
        itemHeight=1;
    }
    qreal sceneWidth=this->scene()->sceneRect().width();
    qreal sceneHeight=this->scene()->sceneRect().height();

    if(itemWidth>sceneWidth){
        itemWidth=sceneWidth;
    }
    if(itemHeight>sceneHeight){
        itemHeight=sceneHeight;
    }
    //处理吸附
    int adsorptionWidth=sceneWidth/2;
    int adsorptionHeight=sceneHeight/2;
    int adsorptionThreshold=20;
    //吸附宽
    int mod=(int)itemWidth%adsorptionWidth;
    int quot=(int)(itemWidth/adsorptionWidth);
    if(mod>0){
        if(mod<adsorptionThreshold){
        itemWidth=quot*adsorptionWidth;
        }
    }
    if(quot==0){
        if(abs(adsorptionWidth-itemWidth)<adsorptionThreshold){
            itemWidth=adsorptionWidth;
        }
    }
    //吸附高
    mod=(int)itemHeight%adsorptionHeight;
    quot=(int)(itemHeight/adsorptionHeight);
    if(mod>0){
        if(mod<adsorptionThreshold){
        itemHeight=quot*adsorptionHeight;
        }
    }
    if(quot==0){
        if(abs(adsorptionHeight-itemHeight)<adsorptionThreshold){
            itemHeight=adsorptionHeight;
        }
    }
    return QSizeF(itemWidth,itemHeight);
}

int MCSplitWindowItem::adjustFrontSize()
{
    QTextOption o;
    o.setWrapMode(QTextOption::WrapAnywhere);
    o.setAlignment(Qt::AlignLeft);

    QRectF rectangle=this->rect();
    rectangle.setWidth(rectangle.width()/4*3);
    QFont ft;
    //QPainter painter;
    ft.setFamily("Microsoft YaHei");
    for(int i = 90; i > 10; i=i-5)
    {
        ft.setPointSize(i);
        QFontMetrics fontMetrics(ft);
        int pixelsWide = fontMetrics.width(m_titleName);
        //int nFontWidth = fontMetrics.horizontalAdvance(m_titleName);
        //qDebug()<<"StrWidth:"<<nFontWidth<<" RectWidth:"<<rectangle.width()<<" i:"<<i;
        if(pixelsWide<rectangle.width())
        {
            m_frontSize=i;
            this->update();
            return m_frontSize;
        }
    }
    return m_frontSize;
}

void MCSplitWindowItem::mouseMoveMoveOperator(const QPointF &scenePos, const QPointF &loacalPos)
{
    qreal xInterval = scenePos.x() - m_pressedPos.x();
    qreal yInterval = scenePos.y() - m_pressedPos.y();

    this->setPos(m_startPos + QPointF(xInterval, yInterval));
    if(this->isSelected()){
        emit sig_WindowRectChanged(QRectF(this->scenePos(),this->rect().size()));
    }
    this->update();
}

void MCSplitWindowItem::mouseMoveResizeOperator(const QPointF &scenePos, const QPointF &loacalPos)
{
    if(!(this->flags()&QGraphicsItem::ItemIsSelectable)){
        return;
    }
    qreal itemWidth = (loacalPos.x())- m_nInterval;
    qreal itemHeight = (loacalPos.y())- m_nInterval;

    QSizeF size = verificationSize(QSizeF(itemWidth,itemHeight));
    this->setRect(QRectF(this->rect().topLeft(),size));
    if(this->isSelected()){
        emit sig_WindowRectChanged(QRectF(this->scenePos(),this->rect().size()));
    }
    adjustFrontSize();
    this->update();
}

#include <LAPI_Control/LAPIControl>
void MCSplitWindowItem::slot_saveItemInfo()
{
    QRectF(this->scenePos(),this->rect().size());
    LAPI::WriteHDIMIWindowPos(this->scenePos().toPoint(), channel(),false);
    LAPI::WriteHDIMIWindowSize(this->rect().toRect().size(), channel(),false);
}

void MCSplitWindowItem::slot_saveAllItemInfo()
{
    QList<QGraphicsItem *> list1 = this->scene()->items();
    for(auto&& item:list1){
        if(item->type()==Type){
            MCSplitWindowItem* windowItem=qgraphicsitem_cast<MCSplitWindowItem*>(item);
            if(windowItem){
                LAPI::WriteHDIMIWindowPos(windowItem->scenePos().toPoint(),windowItem->channel(),false);
                LAPI::WriteHDIMIWindowSize(windowItem->rect().toRect().size(), windowItem->channel(),false);
            }
        }
    }
}

