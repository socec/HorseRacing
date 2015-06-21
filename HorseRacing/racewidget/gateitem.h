#ifndef GATEITEM_H
#define GATEITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include "raceitem.h"

/**
 * @brief Item representing the starting gate.
 */
class GateItem : public QGraphicsItem, public RaceItem {
public:
    /**
     * @brief Class constructor.
     * @param worldPosition - Initial item position as a 3D coordinate in world units.
     * @param worldSize - Initial item width and heigth in world units.
     * @param scale - Scale if the item in the scene.
     */
    GateItem(QVector3D worldPosition, QSizeF worldSize, float scale);

    // inherited from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    // inherited from RaceItem
    void updateScenePosition(const QPointF& newScenePosition);
    void updateWorldPosition(const QVector3D& newWorldPosition);
};

#endif // GATEITEM_H
