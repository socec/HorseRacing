#ifndef GATEITEM_H
#define GATEITEM_H

#include <raceitem.h>

/**
 * @brief Item representing the starting gate.
 */
class GateItem : public RaceItem
{
public:
    /**
     * @brief Default constructor.
     */
    GateItem();

    /**
     * @brief Constructor with initial parameters.
     * @param worldPosition - Initial item position in world units.
     * @param worldSize - Initial item width and heigth in world units.
     */
    GateItem(QVector3D worldPosition, QSizeF worldSize);

    // inherited from RaceItem
    void setScenePosition(const QPointF& scenePosition);
    void onPaint(QPainter *painter);

private:
    // separating top and bottom rectangles with different structure
    float topHeight, bottomHeight;
    QRectF topRect, bottomRect;
};

#endif // GATEITEM_H
