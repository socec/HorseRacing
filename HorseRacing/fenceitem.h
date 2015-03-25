#ifndef FENCEITEM_H
#define FENCEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QVector>
#include <QPen>

#include "raceitem.h"

class FenceItem : public QGraphicsItem, public RaceItem
{
public:
    FenceItem(QVector3D worldPos, QSizeF worldSize, float scale, float postSpacing);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    void updateScenePos(QPointF newScenePos);
    void updateWorldPos(QVector3D newWorldPos);

    int getPostCount() { return postLines.size(); }

private:
    QVector<QLineF> postLines;
    QLineF barLine;
    QPen pen;
};

#endif // FENCEITEM_H
