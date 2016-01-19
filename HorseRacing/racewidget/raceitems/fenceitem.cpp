#include "fenceitem.h"

FenceItem::FenceItem()
    : RaceItem(),
      postSpacing(0)
{
    // not ready to handle visual details in a default constructor
}

FenceItem::FenceItem(QVector3D worldPosition, QSizeF worldSize, float postSpacing)
    : RaceItem(worldPosition, worldSize),
      postSpacing(postSpacing)
{
    // construct visual details
    construct();
}

void FenceItem::setPostSpacing(const float& postSpacing)
{
    // set the parameter and reconstruct visual details
    this->postSpacing = postSpacing;
    construct();
}

void FenceItem::setScenePosition(const QPointF& newScenePosition)
{
    // place item at the requested scene postion
    setPos(newScenePosition);
}

void FenceItem::onPaint(QPainter *painter)
{
    QPen pen(Qt::white);

    // draw the posts
    pen.setWidthF(2.5);
    painter->setPen(pen);
    painter->drawLines(postLines);

    // draw the bar
    pen.setWidthF(5.0);
    painter->setPen(pen);
    painter->drawLine(barLine);
}

void FenceItem::construct()
{
    // set fence posts
    int numPosts = (worldSize.width() / postSpacing) + 1;
    for (int i = 0; i < numPosts; i++)
    {
        float postOffset = i * postSpacing;
        // set line for this post
        QPointF postLineBottom(worldPosition.x() + postOffset,
                               worldPosition.y());
        QPointF postLineTop(worldPosition.x() + postOffset,
                            worldPosition.y() - worldSize.height());
        postLines.append(QLineF(postLineBottom, postLineTop));
    }

    // set fence bar
    QPointF barStart(postLines.first().p2());
    QPointF barEnd(postLines.last().p2());
    barLine = QLineF(barStart, barEnd);
}
