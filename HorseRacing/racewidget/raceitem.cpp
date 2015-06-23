#include "raceitem.h"

RaceItem::RaceItem(QVector3D worldPosition, QSizeF worldSize, float depthScale) {
    this->worldPosition = worldPosition;
    this->worldSize = worldSize;
    this->depthScale = depthScale;
    // scene positioning
    setPos(worldPosition.x(), worldPosition.y());
    setZValue(worldPosition.z());
    setScale(depthScale);
}

QRectF RaceItem::boundingRect() const {
    return QRectF(0, 0, worldSize.width(), worldSize.height());
}

void RaceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // paint item contents
    onPaint(painter);
    // redraw item
    update(boundingRect());
}
