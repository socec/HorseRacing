#ifndef HORSEITEM_H
#define HORSEITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include "raceitem.h"
#include "spritesheet.h"

/**
 * @brief Item representing a race horse.
 */
class HorseItem : public QGraphicsItem, public RaceItem {
public:
    /**
     * @brief Class constructor.
     * @param worldPosition - Initial item position as a 3D coordinate in world units.
     * @param worldSize - Initial item width and heigth in world units.
     * @param scale - Scale of the item in the scene.
     * @param spriteSheet - Sprite sheet used for horse animation.
     */
    HorseItem(QVector3D worldPosition, QSizeF worldSize, float scale, const SpriteSheet& spriteSheet);

    // inherited from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    // inherited from RaceItem
    void updateScenePosition(const QPointF& newScenePosition);
    void updateWorldPosition(const QVector3D& newWorldPosition);

    /**
     * @brief Positions the horse back on the starting line.
     */
    void backToStartingLine();

private:
    const SpriteSheet& spriteSheet;
    int spriteIndex;
    bool onStartingLine;
    float startingPositionX;
};

#endif // HORSEITEM_H
