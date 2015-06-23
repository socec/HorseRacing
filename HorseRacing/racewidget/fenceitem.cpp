#include "fenceitem.h"

#include <QPen>

FenceItem::FenceItem(QVector3D worldPosition, QSizeF worldSize, float depthScale, float postSpacing)
    : RaceItem(worldPosition, worldSize, depthScale) {
    // set fence posts
    int numPosts = worldSize.width() / postSpacing + 1;
    for (int i = 0; i < numPosts; i++) {
        float postOffset = i * postSpacing;
        // set line for this post
        QPointF postLineBottom(worldPosition.x() + postOffset, worldPosition.y());
        QPointF postLineTop(worldPosition.x() + postOffset, worldPosition.y() - worldSize.height());
        postLines.append(QLineF(postLineBottom, postLineTop));
    }
    // set fence bar
    QPointF barStart(postLines.first().p2());
    QPointF barEnd(postLines.last().p2());
    barLine = QLineF(barStart, barEnd);
}

void FenceItem::updateScenePosition(const QPointF& newScenePosition) {
    // place item at requested scene postion
    setPos(newScenePosition);
}

void FenceItem::updateWorldPosition(const QVector3D& newWorldPosition) {
    // does not change world position
    Q_UNUSED(newWorldPosition);
    return;
}

void FenceItem::onPaint(QPainter *painter) {
    QPen pen(Qt::white);
    // draw posts
    pen.setWidthF(2.5);
    painter->setPen(pen);
    painter->drawLines(postLines);
    // draw bar
    pen.setWidthF(5.0);
    painter->setPen(pen);
    painter->drawLine(barLine);
}
