#ifndef HORSEITEM_H
#define HORSEITEM_H

#include "raceitem.h"
#include "spritesheet.h"

/**
 * @brief Item representing a race horse.
 */
class HorseItem : public RaceItem {
public:
    /**
     * @brief Class constructor.
     * @param worldPosition - Initial item position as a 3D coordinate in world units.
     * @param worldSize - Initial item width and heigth in world units.
     * @param depthScale - Projection scaling factor based on scene depth.
     * @param spriteSheet - Sprite sheet used for horse animation.
     */
    HorseItem(QVector3D worldPosition, QSizeF worldSize, float depthScale, const SpriteSheet& spriteSheet);

    /**
     * @brief Positions the horse back on the starting line.
     */
    void backToStartingLine();

    // inherited from RaceItem
    void updateScenePosition(const QPointF& newScenePosition);
    void updateWorldPosition(const QVector3D& newWorldPosition);
    void onPaint(QPainter *painter);

private:
    const SpriteSheet& spriteSheet;
    int spriteIndex;
    bool onStartingLine;
    float startingPositionX;
};

#endif // HORSEITEM_H
