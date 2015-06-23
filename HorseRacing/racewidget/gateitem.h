#ifndef GATEITEM_H
#define GATEITEM_H

#include "raceitem.h"

/**
 * @brief Item representing the starting gate.
 */
class GateItem : public RaceItem {
public:
    /**
     * @brief Class constructor.
     * @param worldPosition - Initial item position as a 3D coordinate in world units.
     * @param worldSize - Initial item width and heigth in world units.
     * @param depthScale - Projection scaling factor based on scene depth.
     */
    GateItem(QVector3D worldPosition, QSizeF worldSize, float depthScale);

    // inherited from RaceItem
    void updateScenePosition(const QPointF& newScenePosition);
    void updateWorldPosition(const QVector3D& newWorldPosition);
    void onPaint(QPainter *painter);
};

#endif // GATEITEM_H
