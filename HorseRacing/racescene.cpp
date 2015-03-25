#include "racescene.h"

RaceScene::RaceScene(float trackLength, int horseCount, QWidget *parent)
    : QGraphicsScene(parent)
{
    // inherit view size from parent, no scroll bars
    int viewWidth = parent->width() - 2;
    int viewHeight = parent->height() - 2;

    // initalize scene parameters
    initializeParameters(viewWidth, viewHeight, trackLength);

    // set scene rectangle
    setSceneRect(0, 0, viewWidth, viewHeight);
    // set scene background
    setBackgroundBrush(Qt::gray);

    // set camera
    cameraPos = QVector3D(cameraParam.shiftX, cameraParam.shiftY, 0.0);


    backFence = new FenceItem(QVector3D(0, 0, 1), QSizeF(200, 50), depthScaling(1), 50);
    backFence->updateScenePos(worldToScene(backFence->getWorldPos()));
    addItem(backFence);

    frontFence = new FenceItem(QVector3D(0, 0, 5), QSizeF(200, 50), depthScaling(5), 50);
    frontFence->updateScenePos(worldToScene(frontFence->getWorldPos()));
    addItem(frontFence);

    horseSprites = new SpriteSheet();
    horse = new HorseItem(QVector3D(0, 0, 3), QSizeF(horseSprites->spriteWidth(), horseSprites->spriteHeight()), depthScaling(3), horseSprites);
    horse->updateScenePos(worldToScene(horse->getWorldPos()));
    addItem(horse);


    // refresh scene
    refreshScene();
}

RaceScene::~RaceScene()
{
    delete backFence;
    delete frontFence;
    delete horseSprites;
    delete horse;
}

void RaceScene::worldUpdate(float horsePosX, float cameraPosX)
{
    // advance camera
    cameraPos.setX(cameraParam.shiftX + cameraPosX);

    // advance horse
    QVector3D horsePos = horse->getWorldPos();
    horsePos.setX(horsePosX);
    horse->updateWorldPos(horsePos);

    refreshScene();
}

void RaceScene::initializeParameters(int viewWidth, int viewHeight, float trackLength)
{
    trackParam.postSpacing = viewWidth/10;

    int trackUnit = trackParam.postSpacing;
    trackParam.length = 5 * trackUnit;

    cameraParam.shiftX = (viewWidth / 8);

    trackParam.fenceSize = QSizeF(trackParam.length, viewHeight/20);
}

QPointF RaceScene::worldToScene(QVector3D worldPos)
{
    QVector3D correctedPos = worldPos - cameraPos;
    float scale = depthScaling(correctedPos.z());

    // set projection origin
    float projectionOriginX = sceneRect().width() / 2;
    float projectionOriginY = sceneRect().height() / 2 - 8 * cameraPos.y();

    // calculate projection offset
    float pox = projectionOriginX + scale * correctedPos.x();
    float poy = projectionOriginY - scale * correctedPos.y() * correctedPos.z();
    return QPointF(pox, poy);
}

void RaceScene::refreshScene()
{
    backFence->updateScenePos(worldToScene(backFence->getWorldPos()));
    frontFence->updateScenePos(worldToScene(frontFence->getWorldPos()));
    horse->updateScenePos(worldToScene(horse->getWorldPos()));

    // redraw scene rectangle
    update(sceneRect());
}

void RaceScene::cameraVerticalChange(int newY)
{
    cameraPos.setY(newY);
    refreshScene();
}
