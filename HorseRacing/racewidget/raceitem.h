#ifndef RACEITEM_H
#define RACEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QVector3D>
#include <QSizeF>

/**
 * @brief Base class for a QGraphicsItem used in the QGraphicsScene of the race.
 *
 * Items are displayed in 2.5D perspective so they have 3D world position and 2D world size.
 *
 * The X and Y components of the world position vector define the top left point of the item
 * when displayed in the scene. The Z component defines the depth of the item when displayed
 * in the scene.
 *
 * World size defines the item bounds starting from the world position going from left to right,
 * top to bottom:

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
     * @param worldPosition - Initial item position in world units.
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
     * @brief Returns the current position of the item.
     * @return Curent world position vector of the item.
     */
    QVector3D getWorldPosition() const { return worldPosition; }

    /**
     * @brief Sets the current world position of the item.
     * @param worldPosition - New world position vector of the item.
     */
    void setWorldPosition(const QVector3D& worldPosition);

    /**
     * @brief Sets the current position of the item in the scene while taking into account the
     *        specific visual details of the item.
     *        Called by the scene after calculating the item's new position in the scene.
     *        Specific implementation needs to be provided by a subclass.
     * @param newScenePosition - New item position in the scene.
     */
    virtual void setScenePosition(const QPointF& newScenePosition) = 0;

    // inherited from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    QVector3D worldPosition;
    QSizeF worldSize;

    /**
     * @brief Handles the specific details of painting this item.
     *        Called by QGraphicsItem::paint().
     *        Specific implementation needs to be provided by a subclass.
     * @param painter - Painter object that performs the actual painting.
     */
    virtual void onPaint(QPainter *painter) = 0;
};

#endif // RACEITEM_H
