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
    // when starting the race set random sprite index for variety in horse gait
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

void HorseItem::setScenePosition(const QPointF& scenePosition)
{
    // place bottom right point at requested scene postion
    // to match horse head with requested position
    QPointF offset(boundingRect().width(), boundingRect().height());

    // setting position in parent coordinates, need to use item scale on offset
    setPos(scenePosition - offset * scale());
}

void HorseItem::onPaint(QPainter *painter)
{
    // draw current sprite
    painter->drawPixmap(boundingRect(), sprite, sprite.rect());
}
