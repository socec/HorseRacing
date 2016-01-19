#include "horseitem.h"

HorseItem::HorseItem()
    : RaceItem()
{
    spriteIndex = 0;
    onStartingLine = true;
}

HorseItem::HorseItem(QVector3D worldPos, QSizeF worldSize)
    : RaceItem(worldPos, worldSize)
{
    // initial sprite sheet index
    spriteIndex = 0;
    // horse is initially on the starting line
    onStartingLine = true;
}

void HorseItem::updateSprite(const SpriteSheet& spriteSheet)
{
    // set random sprite index when starting the race for variety in horse gait
    if (onStartingLine)
    {
        spriteIndex = qrand() % spriteSheet.getSpriteCount();
        onStartingLine = false;
    }
    // otherwise increment sprite index with rollover
    else
    {
        spriteIndex = (spriteIndex + 1) % spriteSheet.getSpriteCount();
    }

    // update current sprite
    sprite = spriteSheet.getSpriteAt(spriteIndex);
}

void HorseItem::setScenePosition(const QPointF& newScenePosition)
{
    // place bottom right point at the requested scene postion so that the head of the horse
    // matches the requested position

    QPointF bottomRightOffset(boundingRect().width(), boundingRect().height());
    // setting position in parent coordinates, need to use item scale on the offset
    setPos(newScenePosition - bottomRightOffset * scale());
}

void HorseItem::onPaint(QPainter *painter)
{
    // draw current sprite
    painter->drawPixmap(boundingRect(), sprite, sprite.rect());
}
