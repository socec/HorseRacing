#ifndef RACESCENE_H
#define RACESCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include <QVector3D>

#include "fenceitem.h"

#define CAMERA_SHIFT_Y (20.0) // initial camera Y axis shift in world units
#define DEPTH_SCALE (0.2)     // scale factor for scene depth

class RaceScene : public QGraphicsScene
{
    Q_OBJECT // for signals and slots
public:
    RaceScene(float trackLength, int horseCount, QWidget *parent = 0);
    ~RaceScene();

private:
    // scene parameters
    struct cameraParam {
        float shiftX = 0.0;
        float shiftY = CAMERA_SHIFT_Y;
    } cameraParam;

    // scene 2.5D visualisation
    float depthScaling(float z) { return 1.0 + (z * DEPTH_SCALE); }
    QPointF worldToScene(QVector3D worldPos);
    void refreshScene();

    // world items
    QVector3D cameraPos;
    FenceItem *backFence, *frontFence;

public slots:
    void cameraVerticalChange(int newY);
};

#endif // RACESCENE_H
