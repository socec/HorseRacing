#include "horseitem.h"

HorseItem::HorseItem(QVector3D worldPos, QSizeF worldSize, float scale, const SpriteSheet& spriteSheet)
    : RaceItem(worldPos, worldSize), spriteSheet(spriteSheet)
{
    // scene positioning
    setPos(worldPos.x(), worldPos.y());
    setZValue(worldPos.z());
    setScale(scale);

    // initial sprite sheet index
    spriteIndex = 0;
    // horse is initially on the starting line
    onStartingLine = true;
}

QRectF HorseItem::boundingRect() const
{
    return QRectF(0, 0, worldSize.width(), worldSize.height());
}

void HorseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // draw current sprite
    QPixmap sprite = spriteSheet.getSpriteAt(spriteIndex);
    painter->drawPixmap(boundingRect(), sprite, sprite.rect());

    update(boundingRect());
}

void HorseItem::updateScenePos(const QPointF& newScenePos)
{
    // place bottom right point at requested scene postion (match position with horse head)
    QPointF offset(boundingRect().width(), boundingRect().height());
    // setting position in parent coordinates, need to use item scale on offset
    setPos(newScenePos - offset * scale());
}

void HorseItem::updateWorldPos(const QVector3D& newWorldPos)
{
    // allow only horizontal movement
    if (newWorldPos.x() != worldPos.x()) {
        // when starting the race set random sprite index for variety in horse gait
        if (onStartingLine) {
            spriteIndex = qrand() % spriteSheet.spriteCount();
            onStartingLine = false;
        }
        // otherwise increment sprite index with rollover
        else {
            spriteIndex = (spriteIndex + 1) % spriteSheet.spriteCount();
        }
        // change horse world position
        worldPos.setX(newWorldPos.x());
    }
}

void HorseItem::backToStartingLine(float startingLineX)
{
    spriteIndex = 0;
    onStartingLine = true;
    worldPos.setX(startingLineX);
}
