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

#define CAMERA_SHIFT_Y (20.0) // initial camera Y axis shift in world units
#define DEPTH_SCALE (0.2)     // scale factor for scene depth
#define POSTS_PER_MARK (5)    // number of fence posts between track marks

class RaceScene : public QGraphicsScene
{
    Q_OBJECT
public:
    RaceScene(float trackLength, int horseCount, QWidget *parent);
    ~RaceScene();

    void worldUpdate(const std::vector<float>& horsePosX, const float& cameraPosX);
    void restartRace();

private:
    // scene parameters
    void initParameters(int viewWidth, int viewHeight, float trackLength, int horseCount);
    // track parameters
    struct {
        float length;
        float adjustPos;
        float startShift;
        float postSpacing;
        int startPostIndex;
        int postsPerMark = POSTS_PER_MARK;
        QSizeF fenceSize;
        QSizeF horseSize;
    } trackParam;
    // camera parameters
    struct {
        float shiftX = 0.0;
        float shiftY = CAMERA_SHIFT_Y;
    } cameraParam;

    // scene 2.5D visualisation
    float depthScaling(float z) const { return 1.0 + (z * DEPTH_SCALE); }
    QPointF worldToScene(QVector3D worldPos);
    void refreshScene();

    // world items
    QVector3D cameraPos;
    FenceItem *backFence, *frontFence;
    SpriteSheet horseSprites;
    QVector<HorseItem*> horses;
    QVector<GateItem*> gates;

    // track marks
    QVector<QGraphicsLineItem*> trackMarks;
    void updateTrackMarks();

public slots:
    void cameraVerticalChange(int newY);
};

#endif // RACESCENE_H
