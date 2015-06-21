#include "racescene.h"

#define multiple_up(x, multiple) ((((int)x + (int)multiple - 1) / (int)multiple) * (int)multiple)

RaceScene::RaceScene(float trackLength, int horseCount, QWidget *parent)
    : QGraphicsScene(parent) {
    // inherit view size from parent, no scroll bars
    int viewWidth = parent->width() - 2;
    int viewHeight = parent->height() - 2;

    // initalize scene parameters
    initParameters(viewWidth, viewHeight, trackLength, horseCount);
    // set scene rectangle and backgroud
    setSceneRect(0, 0, viewWidth, viewHeight);
    setBackgroundBrush(Qt::gray);

    // set camera
    cameraPosition = QVector3D(cameraParam.shiftX, cameraParam.shiftY, 0);

    // start adding items, set initial item position and scaling
    QVector3D itemPosition(0, 0, 0);
    float itemScaling = depthScaling(itemPosition.z());

    // add back fence
    backFence = new FenceItem(itemPosition, trackParam.fenceSize,
                              depthScaling(itemPosition.z()), trackParam.postSpacing);
    addItem(backFence);

    // add horses and starting gates
    itemPosition.setX(trackParam.startPosition);
    for (int i = 0; i < horseCount; i++) {
        itemPosition += QVector3D(0, 0, 1);
        itemScaling = depthScaling(itemPosition.z());
        // horse
        HorseItem *horse = new HorseItem(itemPosition, trackParam.horseSize, itemScaling, horseSprites);
        horses.append(horse);
        addItem(horse);
        // starting gate
        GateItem *gate = new GateItem(itemPosition, trackParam.horseSize, itemScaling);
        gates.append(gate);
        addItem(gate);
    }

    // add front fence
    itemPosition.setX(0);
    itemPosition += QVector3D(0, 0, 1);
    itemScaling = depthScaling(itemPosition.z());
    frontFence = new FenceItem(itemPosition, trackParam.fenceSize, itemScaling, trackParam.postSpacing);
    addItem(frontFence);

    // display items on the scene
    refreshScene();
}

RaceScene::~RaceScene() {
    delete backFence;
    delete frontFence;
    for (int i = 0; i < horses.size(); i++) {
        delete horses.at(i);
        delete gates.at(i);
    }
    for (int i = 0; i < trackMarks.size(); i++) {
        delete trackMarks.at(i);
    }
}

void RaceScene::updatePositions(const std::vector<float>& horsePositions,
                                const float& cameraPosition) {
    // updated positions are related to X coordinate in item world position

    // camera is moving but stops on the finish line
    if (this->cameraPosition.x() < (trackParam.startPosition + trackParam.length)) {
        this->cameraPosition.setX(cameraParam.shiftX + cameraPosition * trackParam.adjustPos);
    }
    // horses are moving
    for (int i = 0; i < horses.size(); i++) {
        QVector3D position = horses.at(i)->getWorldPosition();
        position.setX(trackParam.startPosition + horsePositions.at(i) * trackParam.adjustPos);
        horses.at(i)->updateWorldPosition(position);
    }

    refreshScene();
}

void RaceScene::restartRace() {
    // reset camera
    cameraPosition = QVector3D(cameraParam.shiftX, cameraParam.shiftY, 0);
    // reset horses
    for (int i = 0; i < horses.size(); i++) {
        horses.at(i)->backToStartingLine();
    }

    refreshScene();
}

void RaceScene::cameraVerticalChange(int newPositionY) {
    // directly propagate new coordinate and refresh the scene
    cameraPosition.setY(newPositionY);
    refreshScene();
}

void RaceScene::initParameters(int viewWidth, int viewHeight, float trackLength, int horseCount) {
    // adjust horse size to view size but keep horse sprite aspect ratio
    float horseHeight = viewHeight / (horseCount + 2);
    float horseWidth = horseSprites.getSpriteWidth() * horseHeight / horseSprites.getSpriteHeight();
    trackParam.horseSize = QSizeF(horseWidth, horseHeight);

    // adjust post spacing to horse size
    trackParam.postSpacing = (int) horseHeight;

    // adjust requested track length to keep proper track marks
    int trackUnit = trackParam.postSpacing * trackParam.postsPerMark;
    trackParam.length = multiple_up(trackLength, trackUnit);
    trackParam.adjustPos = trackParam.length / trackLength;

    // put the starting line in the middle of the view, keep a post on the start line
    trackParam.startPosition = multiple_up(viewWidth / 2, trackParam.postSpacing);
    trackParam.startPostIndex = (int) trackParam.startPosition / trackParam.postSpacing;

    // set initial camera shift
    cameraParam.shiftX = (viewWidth / 8) + trackParam.startPosition;

    // calculate fence size
    trackParam.fenceSize = QSizeF(trackParam.length + 2 * trackParam.startPosition, horseHeight / 2);
}

QPointF RaceScene::worldToScene(QVector3D worldPosition) {
    QVector3D correctedPos = worldPosition - cameraPosition;
    float scale = depthScaling(correctedPos.z());

    // set projection origin, empirically derived factors
    float projectionOriginX = sceneRect().width() / 2;
    float projectionOriginY = sceneRect().height() / 2 - 8 * cameraPosition.y();

    // calculate projection offset and create coordinates
    float projectionX = projectionOriginX + scale * correctedPos.x();
    float projectionY = projectionOriginY - scale * correctedPos.y() * correctedPos.z();

    return QPointF(projectionX, projectionY);
}

void RaceScene::refreshScene() {
    // update world items
    backFence->updateScenePosition(worldToScene(backFence->getWorldPosition()));
    frontFence->updateScenePosition(worldToScene(frontFence->getWorldPosition()));
    for (int i = 0; i < horses.size(); i++) {
        horses.at(i)->updateScenePosition(worldToScene(horses.at(i)->getWorldPosition()));
        gates.at(i)->updateScenePosition(worldToScene(gates.at(i)->getWorldPosition()));
    }
    // update track marks
    updateTrackMarks();

    // redraw scene rectangle
    update(sceneRect());
}

void RaceScene::updateTrackMarks() {
    // set track marks on first run
    if (trackMarks.empty()) {
        int finishPostIdx= trackParam.startPostIndex + (trackParam.length / trackParam.postSpacing);
        // pin track marks to posts
        for (int i = trackParam.startPostIndex; i <= finishPostIdx; i += trackParam.postsPerMark) {
            // mark is multiple of post spacing
            QVector3D markOffset(i * trackParam.postSpacing, 0, 0);
            // project mark to scene
            QPointF backFenceMark(worldToScene(backFence->getWorldPosition() + markOffset));
            QPointF frontFenceMark(worldToScene(frontFence->getWorldPosition() + markOffset));
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
            QVector3D markOffset(postOffset * trackParam.postSpacing, 0, 0);
            // project mark to scene
            QPointF backFenceMark(worldToScene(backFence->getWorldPosition() + markOffset));
            QPointF frontFenceMark(worldToScene(frontFence->getWorldPosition() + markOffset));
            trackMarks.at(i)->setLine(QLineF(backFenceMark, frontFenceMark));
        }
    }
}
