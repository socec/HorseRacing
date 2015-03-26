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
    // draw rectangle with dense pattern
    QBrush brush(Qt::white, Qt::Dense1Pattern);
    painter->setBrush(brush);
    painter->drawRect(boundingRect());

    update(boundingRect());
}

void GateItem::updateScenePos(QPointF newScenePos)
{
    // place bottom right point at requested scene postion (match horse positioning)
    QPointF offset(boundingRect().width(), boundingRect().height());
    // setting position in parent coordinates, need to use item scale on offset
    setPos(newScenePos - offset * scale());
}

void GateItem::updateWorldPos(QVector3D newWorldPos)
{
    // does not change world position
    return;
}
