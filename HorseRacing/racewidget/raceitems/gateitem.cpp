#include "gateitem.h"

GateItem::GateItem()
    : RaceItem()
{
    topHeight = 0;
    bottomHeight = 0;
}

GateItem::GateItem(QVector3D worldPos, QSizeF worldSize)
    : RaceItem(worldPos, worldSize)
{
    topHeight = boundingRect().height() / 2;
    bottomHeight = boundingRect().height() - topHeight;
    topRect = QRectF(0, 0, boundingRect().width(), topHeight);
    bottomRect = QRectF(0, topHeight, boundingRect().width(), bottomHeight);
}

void GateItem::setScenePosition(const QPointF& scenePosition)
{
    // place bottom right point at the requested scene postion
    // to match the way a horse item is positioned

    QPointF bottomRightOffset(boundingRect().width(), boundingRect().height());
    // setting position in parent coordinates, need to use item scale on offset
    setPos(scenePosition - bottomRightOffset * scale());
}

void GateItem::onPaint(QPainter *painter)
{
    // border pen
    QPen pen(Qt::black);
    pen.setWidthF(1.0);
    painter->setPen(pen);

    // draw top rectangle with less dense pattern
    painter->setBrush(QBrush(Qt::white, Qt::Dense4Pattern));
    painter->drawRect(topRect);

    // draw bottom rectangle with more dense pattern
    painter->setBrush(QBrush(Qt::white, Qt::Dense1Pattern));
    painter->drawRect(bottomRect);
}
