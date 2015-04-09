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
    return QRectF(0, 0, worldSize.width(), worldSize.height());
}

void FenceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen(Qt::white);
    // draw posts
    pen.setWidthF(2.5);
    painter->setPen(pen);
    painter->drawLines(postLines);
    // draw bar
    pen.setWidthF(5.0);
    painter->setPen(pen);
    painter->drawLine(barLine);

    update(boundingRect());
}

void FenceItem::updateScenePos(const QPointF& newScenePos)
{
    // place item at requested scene postion
    setPos(newScenePos);
}

void FenceItem::updateWorldPos(const QVector3D& newWorldPos)
{
    // does not change world position
    Q_UNUSED(newWorldPos);
    return;
}
