#ifndef RACEITEM_H
#define RACEITEM_H

#include <QVector3D>
#include <QSizeF>

/**
 * @brief Interface for an item used in the race scene.
 *
 * Items are meant to be displayed in 2.5D perspective,
 * so they use 3D world position and 2D size.
 */
class RaceItem {
public:
    /**
     * @brief Class constructor.
     * @param worldPosition - Initial item position as a 3D coordinate in world units.
     * @param worldSize - Initial item width and heigth in world units.
     */
    RaceItem(QVector3D worldPosition, QSizeF worldSize);

    /**
     * @brief Returns the current world position of the item.
     * @return 3D coordinate of the item's world position.
     */
    QVector3D getWorldPosition() const { return worldPosition; }

    /**
     * @brief Returns the item size.
     * @return Item size in world units.
     */
    QSizeF getWorldSize() const { return worldSize; }

    /**
     * @brief Updates the item's position in the scene.
     *        Specific implementation needs to be provided by a subclass.
     * @param newScenePosition - New item position in the scene.
     */
    virtual void updateScenePosition(const QPointF& newScenePosition) = 0;

    /**
     * @brief Updates the item's world position.
     *        Specific implementation needs to be provided by a subclass.
     * @param newWorldPosition - 3D coordinate of the new item world position.
     */
    virtual void updateWorldPosition(const QVector3D& newWorldPosition) = 0;

protected:
    QVector3D worldPosition;
    QSizeF worldSize;
};

#endif // RACEITEM_H
