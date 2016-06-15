#ifndef HORSEITEM_H
#define HORSEITEM_H

#include <raceitem.h>
#include <spritesheet.h>

/**
 * @brief Item representing a racing horse.
 */
class HorseItem : public RaceItem
{
public:
    /**
     * @brief Default constructor.
     */
    HorseItem();

    /**
     * @brief Constructor with initial parameters.
     * @param worldPosition - Initial item position in world units.
     * @param worldSize - Initial item width and heigth in world units.
     */
    HorseItem(QVector3D worldPosition, QSizeF worldSize);

    /**
     * @brief Updates current sprite for the horse.
     *        Should be called when world position is changed to provide animation.
     * @param spriteSheet - Sprite sheet used for horse animation.
     */
    void updateSprite(const SpriteSheet& spriteSheet);

    // inherited from RaceItem
    void setScenePosition(const QPointF& newScenePosition);
    void onPaint(QPainter *painter);

private:
    QPixmap sprite;
    int spriteIndex;
    bool onStartingLine;
};

#endif // HORSEITEM_H
