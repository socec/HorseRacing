#include "gateitem.h"

GateItem::GateItem(QVector3D worldPos, QSizeF worldSize, float scale)
    : RaceItem(worldPos, worldSize)
{
    // scene positioning
    setPos(worldPos.x(), worldPos.y());
    setZValue(worldPos.z());
    setScale(scale);
}

QRectF GateItem::boundingRect() const
{
    return QRectF(0, 0, worldSize.width(), worldSize.height());
}

void GateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // separating top and bottom
    float topHeight = boundingRect().height() / 2;
    float bottomHeight = boundingRect().height() - topHeight;
    QRectF topRect(0, 0, boundingRect().width(), topHeight);
    QRectF botRect(0, topHeight, boundingRect().width(), bottomHeight);
    // border pen
    QPen pen(Qt::black);
    pen.setWidthF(1.0);
    painter->setPen(pen);
    // draw top rectangle with less dense pattern
    painter->setBrush(QBrush(Qt::white, Qt::Dense4Pattern));
    painter->drawRect(topRect);
    // draw bottom rectangle with more dense pattern
    painter->setBrush(QBrush(Qt::white, Qt::Dense1Pattern));
    painter->drawRect(botRect);

    update(boundingRect());
}

void GateItem::updateScenePos(const QPointF& newScenePos)
{
    // place bottom right point at requested scene postion (match horse positioning)
    QPointF offset(boundingRect().width(), boundingRect().height());
    // setting position in parent coordinates, need to use item scale on offset
    setPos(newScenePos - offset * scale());
}

void GateItem::updateWorldPos(const QVector3D& newWorldPos)
{
    // does not change world position
    Q_UNUSED(newWorldPos);
    return;
}
