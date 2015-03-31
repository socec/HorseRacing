#ifndef HORSEITEM_H
#define HORSEITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include "raceitem.h"
#include "spritesheet.h"

class HorseItem : public QGraphicsItem, public RaceItem
{
public:
    HorseItem(QVector3D worldPos, QSizeF worldSize, float scale, const SpriteSheet& spriteSheet);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    void updateScenePos(const QPointF& newScenePos);
    void updateWorldPos(const QVector3D& newWorldPos);

    void backToStartingLine(float startingLineX);

private:
    const SpriteSheet& spriteSheet;
    int spriteIndex;
    bool onStartingLine;
};

#endif // HORSEITEM_H
