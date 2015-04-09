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

class RaceScene : public QGraphicsScene
{
    Q_OBJECT
public:
    RaceScene(float trackLength, int horseCount, QWidget *parent);
    ~RaceScene();

    void updatePositions(const std::vector<float>& horsePosX, const float& cameraPosX);
    void restartRace();

public slots:
    void cameraVerticalChange(int newY);

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
        int postsPerMark = 5; // number of fence posts between track marks
        QSizeF fenceSize;
        QSizeF horseSize;
    } trackParam;
    // camera parameters
    struct {
        float shiftX = 0.0;
        float shiftY = 20.0; // initial camera Y axis shift in world units
    } cameraParam;

    // scene 2.5D visualisation
    float depthScaling(float z) const { return 1.0 + (z * 0.2); } // scale factor for scene depth
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
};

#endif // RACESCENE_H
