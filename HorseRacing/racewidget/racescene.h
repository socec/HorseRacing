#ifndef RACESCENE_H
#define RACESCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include <QVector3D>
#include <QGraphicsLineItem>

#include "fenceitem.h"
#include "spritesheet.h"
#include "horseitem.h"
#include "gateitem.h"

#define POSTS_PER_MARK (5)
#define CAMERA_SHIFT_X (0.0)
#define CAMERA_SHIFT_Y (20.0)
#define DEPTH_SCALE_FACTOR (0.2)

/**
 * @brief Scene that animates the race.
 */
class RaceScene : public QGraphicsScene {
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Class constructor.
     * @param trackLength - Length of the race track.
     * @param horseCount - Number of horses in the race.
     * @param parent - Parent widget used for widget hierarchy.
     */
    RaceScene(float trackLength, int horseCount, QWidget *parent);

    /**
     * @brief Class destructor.
     */
    ~RaceScene();

    /**
     * @brief Updates horse and camera positions for this race.
     * @param horsePositions - List of updated horse positions.
     * @param cameraPosition - Updated camera position.
     */
    void updatePositions(const std::vector<float>& horsePositions, const float& cameraPosition);

    /**
     * @brief Restarts the race animated by the scene.
     */
    void restartRace();

public slots:
    /**
     * @brief Changes vertical camera position.
     * @param newPositionY - New Y coordinate of the camera.
     */
    void cameraVerticalChange(int newPositionY);

private:
    // track parameters
    struct {
        float length;
        float adjustPos; // adjustment factor for positions to match the true track length
        float startPosition;
        float postSpacing;
        int startPostIndex;
        int postsPerMark = POSTS_PER_MARK; // number of fence posts between track marks
        QSizeF fenceSize;
        QSizeF horseSize;
    } trackParam;

    // camera parameters
    struct {
        // initial camera axis shifts in world units
        float shiftX = CAMERA_SHIFT_X;
        float shiftY = CAMERA_SHIFT_Y;
    } cameraParam;

    // world items
    QVector3D cameraPosition;
    FenceItem *backFence, *frontFence;
    SpriteSheet horseSprites;
    QVector<HorseItem*> horses;
    QVector<GateItem*> gates;
    QVector<QGraphicsLineItem*> trackMarks;

    /**
     * @brief Returns scale factor for scene depth based on the Z coordinate.
     * @param z - Z coordinate of the position.
     * @return Depth scale factor.
     */
    float depthScaling(float z) const { return 1.0 + (z * DEPTH_SCALE_FACTOR); }

    /**
     * @brief Initializes scene parameters.
     * @param viewWidth - Width of the scene view.
     * @param viewHeight - Height of the scene view.
     * @param trackLength - Length of the race track.
     * @param horseCount - Number of horses in the race.
     */
    void initParameters(int viewWidth, int viewHeight, float trackLength, int horseCount);

    /**
     * @brief Converts world 3D coordinates to scene projection 2D coordinates.
     * @param worldPosition - World coordinates.
     * @return Scene projection coordinates.
     */
    QPointF worldToScene(QVector3D worldPosition);

    /**
     * @brief Refreshes and redraws the scene.
     */
    void refreshScene();

    /**
     * @brief Updates the track marks to match scene perspective.
     */
    void updateTrackMarks();
};

#endif // RACESCENE_H
