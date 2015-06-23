#include "horseitem.h"

HorseItem::HorseItem(QVector3D worldPos, QSizeF worldSize, float depthScale, const SpriteSheet& spriteSheet)
    : RaceItem(worldPos, worldSize, depthScale), spriteSheet(spriteSheet) {
    // initial sprite sheet index
    spriteIndex = 0;
    // horse is initially on the starting line
    onStartingLine = true;
    // store starting line position
    startingPositionX = worldPos.x();
}

void HorseItem::backToStartingLine() {
    // reset sprite sheet index
    spriteIndex = 0;
    // move back to the starting line
    onStartingLine = true;
    worldPosition.setX(startingPositionX);
}

void HorseItem::updateScenePosition(const QPointF& newScenePosition) {
    // place bottom right point at requested scene postion (match position with horse head)
    QPointF offset(boundingRect().width(), boundingRect().height());
    // setting position in parent coordinates, need to use item scale on offset
    setPos(newScenePosition - offset * scale());
}

void HorseItem::updateWorldPosition(const QVector3D& newWorldPosition) {
    // allow only horizontal movement
    if (newWorldPosition.x() != worldPosition.x()) {
        // when starting the race set random sprite index for variety in horse gait
        if (onStartingLine) {
            spriteIndex = qrand() % spriteSheet.getSpriteCount();
            onStartingLine = false;
        }
        // otherwise increment sprite index with rollover
        else {
            spriteIndex = (spriteIndex + 1) % spriteSheet.getSpriteCount();
        }
        // change horse world position
        worldPosition.setX(newWorldPosition.x());
    }
}

void HorseItem::onPaint(QPainter *painter) {
    // draw current sprite
    QPixmap sprite = spriteSheet.getSpriteAt(spriteIndex);
    painter->drawPixmap(boundingRect(), sprite, sprite.rect());
}
