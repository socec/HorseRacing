#ifndef HORSEITEM_H
#define HORSEITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include "raceitem.h"
#include "spritesheet.h"

class HorseItem : public QGraphicsItem, public RaceItem
{
public:
    HorseItem(QVector3D worldPos, QSizeF worldSize, float scale, SpriteSheet *spriteSheet);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    void updateScenePos(QPointF newScenePos);
    void updateWorldPos(QVector3D newWorldPos);

    void backToStartingLine(float startingLineX);

private:
    SpriteSheet *spriteSheet; // points to external object, don't delete in destructor
    int spriteIndex;
    bool onStartingLine;
};

#endif // HORSEITEM_H
