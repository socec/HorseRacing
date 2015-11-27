#ifndef RACESCENE_H
#define RACESCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsLineItem>
#include <QSharedPointer>

#include "fenceitem.h"
#include "gateitem.h"
#include "spritesheet.h"
#include "horseitem.h"

#define POSTS_PER_MARK (5)
#define CAMERA_SHIFT_X (0.0)
#define CAMERA_SHIFT_Y (20.0)
#define DEPTH_SCALE_FACTOR (0.2)

/**
 * @brief Race scene animation framework.
 *
 * Distributes items on the scene, handles updates to item positions and
 * projects them correctly to the screen in a 2.5D perspective.
 * Uses a parent QGraphiscView to display the scene and determine it's size.
 */
class RaceScene : public QGraphicsScene
{
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Default constructor.
     * @param parent - Parent widget used for widget hierarchy.
     */
    RaceScene(QWidget *parent);

    /**
     * @brief Builds the race scene by distributing items.
     * @param viewSize - Size of the QGraphicsView diplaying the race.
     * @param trackLength - Length of the race track.
     * @param horseCount - Number of horses in the race.
     */
    void build(QSizeF viewSize,float trackLength, int horseCount);

    /**
     * @brief Updates horse and camera positions for this race.
     * @param horsePositions - List of updated horse positions.
     * @param cameraPosition - Updated camera position.
     */
    void updatePositions(const QVector<float>& horsePositions, const float& cameraPosition);

public slots:
    /**
     * @brief Changes vertical camera position.
     * @param newPositionY - New Y coordinate of the camera.
     */
    void cameraVerticalChange(int newPositionY);

private:
    // scene parameters
    struct
    {
        // length of the track
        float trackLength;
        // adjustment factor for positions to match the animated track length
        float positionAdjust;
        // starting line
        float startPosition;
        // space between fence posts
        float postSpacing;
        // number of fence posts between track marks
        int postsPerMark = POSTS_PER_MARK;
        // index of the post located on the starting line
        int startPostIndex;
        // item size
        QSizeF fenceSize;
        QSizeF horseSize;
        // initial camera shifts in world units
        float cameraShiftX = CAMERA_SHIFT_X;
        float cameraShiftY = CAMERA_SHIFT_Y;
    } params;

    // world items
    SpriteSheet spritesheet;
    QVector3D cameraPosition;
    FenceItem backFence, frontFence;
    QVector<QSharedPointer<HorseItem>> horses;
    QVector<QSharedPointer<GateItem>> gates;
    QVector<QSharedPointer<QGraphicsLineItem>> trackMarks;

    /**
     * @brief Initializes scene parameters.
     * @param viewSize - Size of the QGraphicsView diplaying the race.
     * @param trackLength - Length of the race track.
     * @param horseCount - Number of horses in the race.
     */
    void initParameters(QSizeF viewSize, float trackLength, int horseCount);

    /**
     * @brief Converts 3D world coordinates of an item to 2D projection coordinates of the scene.
     * @param worldPosition - World coordinates.
     * @return Scene projection coordinates.
     */
    QPointF worldToScene(const QVector3D& worldPosition);

    /**
     * @brief Updates and redraws the scene.
     */
    void refreshScene();

    /**
     * @brief Updates the track marks to match scene perspective.
     */
    void updateTrackMarks();

    /**
     * @brief Returns scale factor for scene depth based on the Z coordinate.
     * @param z - Z coordinate of the position.
     * @return Depth scale factor.
     */
    float depthScale(float z) const
    {
        return 1.0 + (z * DEPTH_SCALE_FACTOR);
    }

    /**
     * @brief Returns the first multiple of a number that is bigger or equal to the given limit.
     * @param number - Number to find multiple of.
     * @param limit - Minimal limit for the multiple of the given number.
     * @return First multiple of the number equal to or bigger than the limit.
     */
    int firstMultiple(int number, int limit) const
    {
        return ((limit + number - 1) / number) * number;
    }
};

#endif // RACESCENE_H
