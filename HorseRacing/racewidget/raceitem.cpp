#include "raceitem.h"

RaceItem::RaceItem()
{
    worldPosition = QVector3D(0, 0, 0);
    worldSize = QSizeF(0, 0);
    // scene positioning
    setPos(0, 0);
    setZValue(0);
}

RaceItem::RaceItem(QVector3D worldPosition, QSizeF worldSize)
{
    this->worldPosition = worldPosition;
    this->worldSize = worldSize;
    // scene positioning
    setPos(worldPosition.x(), worldPosition.y());
    setZValue(worldPosition.z());
}

void RaceItem::setWorldPosition(const QVector3D& worldPosition)
{
    // set new world position
    this->worldPosition = worldPosition;

    // check for change in Z value
    if (zValue() != worldPosition.z())
    {
        setZValue(worldPosition.z());
    }
}

QRectF RaceItem::boundingRect() const
{
    return QRectF(0, 0, worldSize.width(), worldSize.height());
}

void RaceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // paint item contents
    onPaint(painter);

    // redraw item
    update(boundingRect());
}
