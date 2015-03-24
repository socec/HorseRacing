#include "racescene.h"

#include <QGraphicsRectItem>

RaceScene::RaceScene(float trackLength, int horseCount, QWidget *parent)
    : QGraphicsScene(parent)
{
    // inherit view size from parent, no scroll bars
    int viewWidth = parent->width() - 2;
    int viewHeight = parent->height() - 2;

    // set scene rectangle
    setSceneRect(0, 0, viewWidth, viewHeight);
    // set scene background
    setBackgroundBrush(Qt::gray);

    // set camera
    cameraPos = QVector3D(cameraParam.shiftX, cameraParam.shiftY, 0.0);


    QGraphicsRectItem *ri = new QGraphicsRectItem(50,50,100,100);
    ri->setPos(worldToScene(QVector3D(10, 10, 10)));
    addItem(ri);


    // refresh scene
    refreshScene();
}

RaceScene::~RaceScene()
{
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
    QGraphicsRectItem *ri = new QGraphicsRectItem(50,50,100,100);
    ri->setPos(worldToScene(QVector3D(10, 10, 10)));
    addItem(ri);

    // redraw scene rectangle
    update(sceneRect());
}

void RaceScene::cameraVerticalChange(int newY)
{
    cameraPos.setY(newY);
    refreshScene();
}
