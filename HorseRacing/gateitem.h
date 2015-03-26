#ifndef GATEITEM_H
#define GATEITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include "raceitem.h"

class GateItem : public QGraphicsItem, public RaceItem
{
public:
    GateItem(QVector3D worldPos, QSizeF worldSize, float scale);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    void updateScenePos(QPointF newScenePos);
    void updateWorldPos(QVector3D newWorldPos);
};

#endif // GATEITEM_H
