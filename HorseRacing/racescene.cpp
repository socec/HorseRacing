#include "racescene.h"

#define multiple_up(x, multiple) ((((int)x + (int)multiple - 1) / (int)multiple) * (int)multiple)

RaceScene::RaceScene(float trackLength, int horseCount, QWidget *parent)
    : QGraphicsScene(parent)
{
    // inherit view size from parent, no scroll bars
    int viewWidth = parent->width() - 2;
    int viewHeight = parent->height() - 2;

    // initalize scene parameters
    initializeParameters(viewWidth, viewHeight, trackLength, horseCount);

    // set scene rectangle
    setSceneRect(0, 0, viewWidth, viewHeight);
    // set scene background
    setBackgroundBrush(Qt::gray);

    // set camera
    cameraPos = QVector3D(cameraParam.shiftX, cameraParam.shiftY, 0.0);


    backFence = new FenceItem(QVector3D(0, 0, 1), trackParam.fenceSize, depthScaling(1), trackParam.postSpacing);
    backFence->updateScenePos(worldToScene(backFence->getWorldPos()));
    addItem(backFence);

    frontFence = new FenceItem(QVector3D(0, 0, 5), trackParam.fenceSize, depthScaling(5), trackParam.postSpacing);
    frontFence->updateScenePos(worldToScene(frontFence->getWorldPos()));
    addItem(frontFence);

    horse = new HorseItem(QVector3D(trackParam.startShift, 0, 3), trackParam.horseSize, depthScaling(3), &horseSprites);
    horse->updateScenePos(worldToScene(horse->getWorldPos()));
    addItem(horse);


    // refresh scene
    refreshScene();
}

RaceScene::~RaceScene()
{
    delete backFence;
    delete frontFence;
    delete horse;
}

void RaceScene::worldUpdate(float horsePosX, float cameraPosX)
{
    // advance camera
    cameraPos.setX(cameraParam.shiftX + cameraPosX);

    // advance horse
    QVector3D horsePos = horse->getWorldPos();
    horsePos.setX(trackParam.startShift + horsePosX);
    horse->updateWorldPos(horsePos);

    refreshScene();
}

void RaceScene::initializeParameters(int viewWidth, int viewHeight, float trackLength, int horseCount)
{
    // adjust horse size to view size but keep horse sprite aspect ratio
    float horseHeight = viewHeight / (horseCount + 2);
    float horseWidth = horseSprites.spriteWidth() * horseHeight / horseSprites.spriteHeight();
    trackParam.horseSize = QSizeF(horseWidth, horseHeight);

    // adjust post spacing to horse size
    trackParam.postSpacing = (int) horseHeight;

    // adjust requested track length to keep proper track marks
    int trackUnit = trackParam.postSpacing * trackParam.postsPerMark;
    trackParam.length = multiple_up(trackLength, trackUnit);

    // put the starting line in the middle of the view, keep a post on the start line
    trackParam.startShift = multiple_up(viewWidth / 2, trackParam.postSpacing);
    trackParam.startPostIndex = (int) trackParam.startShift / trackParam.postSpacing;

    // set initial camera shift
    cameraParam.shiftX = (viewWidth / 8) + trackParam.startShift;

    // calculate fence size
    trackParam.fenceSize = QSizeF(trackParam.length + 2 * trackParam.startShift, horseHeight / 2);
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

    updateTrackMarks();

    // redraw scene rectangle
    update(sceneRect());
}

void RaceScene::updateTrackMarks()
{
    // set track marks on first run
    if (trackMarks.empty()) {
        int finishPostInd= trackParam.startPostIndex + (trackParam.length / trackParam.postSpacing);
        // pin track marks to posts
        for (int i = trackParam.startPostIndex; i <= finishPostInd; i += trackParam.postsPerMark) {
            // mark is multiple of post spacing
            QVector3D markOffset(i * trackParam.postSpacing, 0.0, 0.0);
            // project mark to scene
            QPointF backFenceMark(worldToScene(backFence->getWorldPos() + markOffset));
            QPointF frontFenceMark(worldToScene(frontFence->getWorldPos() + markOffset));
            trackMarks.append(addLine(QLineF(backFenceMark, frontFenceMark)));
        }
        // set pen for start and finish line
        QPen pen(Qt::black);
        pen.setWidth(4);
        pen.setCapStyle(Qt::FlatCap);
        trackMarks.first()->setPen(pen);
        trackMarks.last()->setPen(pen);
    }
    // otherwise update track marks
    else {
        for (int i = 0; i < trackMarks.size(); i++) {
            // find mark pinned to post
            float postOffset = (trackParam.startPostIndex + i * trackParam.postsPerMark);
            QVector3D markOffset(postOffset * trackParam.postSpacing, 0.0, 0.0);
            // project mark to scene
            QPointF backFenceMark(worldToScene(backFence->getWorldPos() + markOffset));
            QPointF frontFenceMark(worldToScene(frontFence->getWorldPos() + markOffset));
            trackMarks.at(i)->setLine(QLineF(backFenceMark, frontFenceMark));
        }
    }
}

void RaceScene::cameraVerticalChange(int newY)
{
    // directly propagate new coordinate and refresh the scene
    cameraPos.setY(newY);
    refreshScene();
}
