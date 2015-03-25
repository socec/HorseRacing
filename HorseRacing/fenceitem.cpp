#include "fenceitem.h"

FenceItem::FenceItem(QVector3D worldPos, QSizeF worldSize, float scale, float postSpacing)
    : RaceItem(worldPos, worldSize)
{
    // scene positioning
    setPos(worldPos.x(), worldPos.y());
    setZValue(worldPos.z());
    setScale(scale);

    // set fence posts
    int numPosts = worldSize.width() / postSpacing + 1;
    for (int i = 0; i < numPosts; i++) {
        float postOffset = i * postSpacing;
        // set post line
        QPointF postLineBottom(worldPos.x() + postOffset, worldPos.y());
        QPointF postLineTop(worldPos.x() + postOffset, worldPos.y() - worldSize.height());
        postLines.append(QLineF(postLineBottom, postLineTop));
    }
    // set fence bar
    QPointF barStart(postLines.first().p2());
    QPointF barEnd(postLines.last().p2());
    barLine = QLineF(barStart, barEnd);
}

QRectF FenceItem::boundingRect() const
{
    return QRectF(0, 0, getWorldSize().width(), getWorldSize().height());
}

void FenceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    pen.setColor(Qt::white);

    pen.setWidthF(2.5);
    painter->setPen(pen);
    painter->drawLines(postLines);

    pen.setWidthF(5.0);
    painter->setPen(pen);
    painter->drawLine(barLine);

    update(boundingRect());
}

void FenceItem::updateScenePos(QPointF newScenePos)
{
    // place item at requested scene postion
    setPos(newScenePos);
}

void FenceItem::updateWorldPos(QVector3D newWorldPos)
{
    // fence does not move in world coordinates
    return;
}
