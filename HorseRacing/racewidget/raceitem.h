#ifndef RACEITEM_H
#define RACEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QVector3D>
#include <QSizeF>

/**
 * @brief Base class for a graphics item used in the race scene.
 *
 * Items are meant to be displayed in 2.5D perspective,
 * so they use 3D world position and 2D size.
 *
 * Item world coordinate defines the top left point of the item.
 * Item size grows from left to right, top to bottom:
 *
 * (0,0)----(w,0)
 *   |        |
 * (0,h)----(w,h)
 */
class RaceItem : public QGraphicsItem
{
public:
    /**
     * @brief Default constructor.
     */
    RaceItem();

    /**
     * @brief Constructor with initial parameters.
     * @param worldPosition - Initial item position as a 3D coordinate in world units.
     * @param worldSize - Initial item width and heigth in world units.
     */
    RaceItem(QVector3D worldPosition, QSizeF worldSize);

    /**
     * @brief Returns the item size.
     * @return Item size in world units.
     */
    QSizeF getWorldSize() const { return worldSize; }

    /**
     * @brief Sets the item size.
     * @param worldSize - Item size in world units.
     */
    void setWorldSize(const QSizeF& worldSize) { this->worldSize = worldSize; }

    /**
     * @brief Returns the current world position of the item.
     * @return 3D coordinate of the item's world position.
     */
    QVector3D getWorldPosition() const { return worldPosition; }

    /**
     * @brief Sets the current world position of the item.
     * @param worldPosition - 3D coordinate of the item's world position.
     */
    void setWorldPosition(const QVector3D& worldPosition);

    /**
     * @brief Sets the current scene position of the item while handling visual details.
     *        Called by race animation framework after calculating the item's projected position.
     *        Specific implementation needs to be provided by a subclass.
     * @param scenePosition - New item position in the scene.
     */
    virtual void setScenePosition(const QPointF& scenePosition) = 0;

    // inherited from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    QVector3D worldPosition;
    QSizeF worldSize;

    /**
     * @brief Handles details of painting this item.
     *        Called by QGraphicsItem::paint().
     *        Specific implementation needs to be provided by a subclass.
     * @param painter - Painter object performing the actual painting.
     */
    virtual void onPaint(QPainter *painter) = 0;
};

#endif // RACEITEM_H
