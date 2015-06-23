#ifndef FENCEITEM_H
#define FENCEITEM_H

#include <QVector>

#include "raceitem.h"

/**
 * @brief Item representing a fence on the race track.
 */
class FenceItem : public RaceItem {
public:
    /**
     * @brief Class constructor.
     * @param worldPosition - Initial item position as a 3D coordinate in world units.
     * @param worldSize - Initial item width and heigth in world units.
     * @param depthScale - Projection scaling factor based on scene depth.
     * @param postSpacing - Spacing between the fence posts in world units.
     */
    FenceItem(QVector3D worldPosition, QSizeF worldSize, float depthScale, float postSpacing);

    /**
     * @brief Returns the number of posts the fence is standing on.
     * @return Number of posts.
     */
    int getPostCount() const { return postLines.size(); }

    // inherited from RaceItem
    void updateScenePosition(const QPointF& newScenePosition);
    void updateWorldPosition(const QVector3D& newWorldPosition);
    void onPaint(QPainter *painter);

private:
    QVector<QLineF> postLines;
    QLineF barLine;
};

#endif // FENCEITEM_H
