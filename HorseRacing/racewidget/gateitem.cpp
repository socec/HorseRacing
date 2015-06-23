#include "gateitem.h"

GateItem::GateItem(QVector3D worldPos, QSizeF worldSize, float depthScale)
    : RaceItem(worldPos, worldSize, depthScale) {
}

void GateItem::updateScenePosition(const QPointF& newScenePosition) {
    // place bottom right point at requested scene postion (match horse positioning)
    QPointF offset(boundingRect().width(), boundingRect().height());
    // setting position in parent coordinates, need to use item scale on offset
    setPos(newScenePosition - offset * scale());
}

void GateItem::updateWorldPosition(const QVector3D& newWorldPosition) {
    // does not change world position
    Q_UNUSED(newWorldPosition);
    return;
}

void GateItem::onPaint(QPainter *painter) {
    // separating top and bottom rectangles
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
}
