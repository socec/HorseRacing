#ifndef FENCEITEM_H
#define FENCEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QVector>
#include <QPen>

#include "raceitem.h"

/**
 * @brief Item representing a fence on the race track.
 */
class FenceItem : public QGraphicsItem, public RaceItem {
public:
    /**
     * @brief Class constructor.
     * @param worldPosition - Initial item position as a 3D coordinate in world units.
     * @param worldSize - Initial item width and heigth in world units.
     * @param scale - Scale if the item in the scene.
     * @param postSpacing - Spacing between the fence posts in world units.
     */
    FenceItem(QVector3D worldPosition, QSizeF worldSize, float scale, float postSpacing);

    // inherited from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    // inherited from RaceItem
    void updateScenePosition(const QPointF& newScenePosition);
    void updateWorldPosition(const QVector3D& newWorldPosition);

    /**
     * @brief Returns the number of posts the fence is standing on.
     * @return Number of posts.
     */
    int getPostCount() const { return postLines.size(); }

private:
    QVector<QLineF> postLines;
    QLineF barLine;
};

#endif // FENCEITEM_H
