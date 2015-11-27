#ifndef FENCEITEM_H
#define FENCEITEM_H

#include <QVector>
#include <QLineF>

#include "raceitem.h"

/**
 * @brief Item representing a fence on the race track.
 */
class FenceItem : public RaceItem
{
public:
    /**
     * @brief Default constructor.
     */
    FenceItem();

    /**
     * @brief Constructor with initial parameters.
     * @param worldPosition - Initial item position as a 3D coordinate in world units.
     * @param worldSize - Initial item width and heigth in world units.
     * @param postSpacing - Spacing between the fence posts in world units.
     */
    FenceItem(QVector3D worldPosition, QSizeF worldSize, float postSpacing);

    /**
     * @brief Sets spacing between fence posts.
     * @param postSpacing - Spacing between the fence posts in world units.
     */
    void setPostSpacing(const float& postSpacing);

    /**
     * @brief Returns the number of fence posts.
     * @return Number of posts.
     */
    int getPostCount() const { return postLines.size(); }

    // inherited from RaceItem
    void setScenePosition(const QPointF& newScenePosition);
    void onPaint(QPainter *painter);

private:
    float postSpacing;
    QVector<QLineF> postLines;
    QLineF barLine;

    /**
     * @brief Constructs the item details based on current parameters.
     */
    void construct();
};

#endif // FENCEITEM_H
