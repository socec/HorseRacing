#include "racescene.h"

RaceScene::RaceScene(QWidget *parent)
    : QGraphicsScene(parent),
      spritesheet("muybridge_spritesheet.png", 4, 4)
{
    // adding items to the scene is delegated to the build() method
}

void RaceScene::build(QSizeF viewSize, float trackLength, int horseCount)
{
    // trim view size from parent to avoid scroll bars
    viewSize.setWidth(viewSize.width() - 2);
    viewSize.setHeight(viewSize.height() - 2);

    // initalize scene parameters
    initParameters(viewSize, trackLength, horseCount);
    // set scene rectangle and backgroud
    setSceneRect(0, 0, viewSize.width(), viewSize.height());
    setBackgroundBrush(Qt::gray);

    // do not use item indexing since items are moving
    setItemIndexMethod(ItemIndexMethod::NoIndex);

    // set camera
    cameraPosition = QVector3D(params.cameraShiftX, params.cameraShiftY, 0);

    // start adding items, set initial item position
    QVector3D itemPosition(0, 0, 0);

    // add back fence
    backFence.setWorldPosition(itemPosition);
    backFence.setWorldSize(params.fenceSize);
    backFence.setScale(depthScale(itemPosition.z()));
    backFence.setPostSpacing(params.postSpacing);
    addItem(&backFence);

    // add horses and starting gates
    itemPosition.setX(params.startPosition);
    for (int i = 0; i < horseCount; i++)
    {
        itemPosition += QVector3D(0, 0, 1);
        // horse
        QSharedPointer<HorseItem> horse(new HorseItem(itemPosition, params.horseSize));
        horse->setScale(depthScale(itemPosition.z()));
        horse->updateSprite(spritesheet);
        horses.append(horse);
        addItem(horse.data());
        // starting gate
        QSharedPointer<GateItem> gate(new GateItem(itemPosition, params.horseSize));
        gate->setScale(depthScale(itemPosition.z()));
        gates.append(gate);
        addItem(gate.data());
    }

    // add front fence
    itemPosition.setX(0);
    itemPosition += QVector3D(0, 0, 1);
    frontFence.setWorldPosition(itemPosition);
    frontFence.setWorldSize(params.fenceSize);
    frontFence.setScale(depthScale(itemPosition.z()));
    frontFence.setPostSpacing(params.postSpacing);
    addItem(&frontFence);

    // display items on the scene
    refreshScene();
}

void RaceScene::updatePositions(const QVector<float>& horsePositions,
                                const float& cameraPosition)
{
    // updated positions are related to X coordinate in world position of the item

    // camera is moving but stops on the finish line
    if (this->cameraPosition.x() < (params.startPosition + params.trackLength))
    {
        this->cameraPosition.setX(params.cameraShiftX + cameraPosition * params.positionAdjust);
    }

    // horses are moving
    for (int i = 0; i < horses.size(); i++)
    {
        QVector3D oldPosition = horses[i]->getWorldPosition();
        QVector3D newPosition(oldPosition);
        float offset = horsePositions.at(i) * params.positionAdjust;
        newPosition.setX(params.startPosition + offset);
        horses[i]->setWorldPosition(newPosition);
        if (oldPosition != newPosition)
        {
            horses[i]->updateSprite(spritesheet);
        }
    }

    // refresh the scene
    refreshScene();
}

void RaceScene::cameraVerticalChange(int newPositionY)
{
    // directly propagate new coordinate and refresh the scene
    cameraPosition.setY(newPositionY);
    refreshScene();
}

void RaceScene::initParameters(QSizeF viewSize, float trackLength, int horseCount)
{
    // adjust horse size to view size but keep horse sprite aspect ratio
    float horseHeight = viewSize.height() / (horseCount + 2);
    float horseWidth = spritesheet.getSpriteWidth() * horseHeight / spritesheet.getSpriteHeight();
    params.horseSize = QSizeF(horseWidth, horseHeight);

    // adjust post spacing to horse size
    params.postSpacing = (int) horseHeight;

    // adjust requested track length to keep proper track marks
    int trackUnit = params.postSpacing * params.postsPerMark;
    params.trackLength = firstMultiple(trackUnit, trackLength);
    params.positionAdjust = params.trackLength / trackLength;

    // put the starting line in the middle of the view, keep a post on the start line
    params.startPosition = firstMultiple(params.postSpacing, viewSize.width() / 2);
    params.startPostIndex = (int) params.startPosition / params.postSpacing;

    // set initial camera shift
    params.cameraShiftX = (viewSize.width() / 8) + params.startPosition;

    // adjust fence size
    float fenceHeight = horseHeight / 2;
    float fenceWidth = params.trackLength + 2 * params.startPosition;
    params.fenceSize = QSizeF(fenceWidth, fenceHeight);
}

QPointF RaceScene::worldToScene(const QVector3D& worldPosition)
{
    QVector3D correctedPos = worldPosition - cameraPosition;

    // set projection origin, empirically derived factors
    float projectionOriginX = sceneRect().width() / 2;
    float projectionOriginY = sceneRect().height() / 2 - 8 * cameraPosition.y();

    // calculate projection offset and create coordinates
    float scale = depthScale(correctedPos.z());
    float projectionX = projectionOriginX + scale * correctedPos.x();
    float projectionY = projectionOriginY - scale * correctedPos.y() * correctedPos.z();

    return QPointF(projectionX, projectionY);
}

void RaceScene::refreshScene()
{
    // update world items
    backFence.setScenePosition(worldToScene(backFence.getWorldPosition()));
    frontFence.setScenePosition(worldToScene(frontFence.getWorldPosition()));
    for (int i = 0; i < horses.size(); i++)
    {
        horses[i]->setScenePosition(worldToScene(horses[i]->getWorldPosition()));
        gates.at(i)->setScenePosition(worldToScene(gates.at(i)->getWorldPosition()));
    }

    // update track marks
    updateTrackMarks();

    // redraw scene rectangle
    update(sceneRect());
}

void RaceScene::updateTrackMarks()
{
    // set track marks on first run
    if (trackMarks.empty())
    {
        int finishPostIdx= params.startPostIndex + (params.trackLength / params.postSpacing);
        // pin track marks to posts
        for (int i = params.startPostIndex; i <= finishPostIdx; i += params.postsPerMark)
        {
            // mark is multiple of post spacing
            QVector3D markOffset(i * params.postSpacing, 0, 0);
            // project mark to scene
            QPointF backFenceMark(worldToScene(backFence.getWorldPosition() + markOffset));
            QPointF frontFenceMark(worldToScene(frontFence.getWorldPosition() + markOffset));
            QSharedPointer<QGraphicsLineItem> mark(addLine(QLineF(backFenceMark, frontFenceMark)));
            trackMarks.append(mark);
        }
        // set pen for start and finish line
        QPen pen(Qt::black);
        pen.setWidth(4);
        pen.setCapStyle(Qt::FlatCap);
        trackMarks.first()->setPen(pen);
        trackMarks.last()->setPen(pen);
    }
    // otherwise update track marks
    else
    {
        for (int i = 0; i < trackMarks.size(); i++)
        {
            // find mark pinned to post
            float postOffset = (params.startPostIndex + i * params.postsPerMark);
            QVector3D markOffset(postOffset * params.postSpacing, 0, 0);
            // project mark to scene
            QPointF backFenceMark(worldToScene(backFence.getWorldPosition() + markOffset));
            QPointF frontFenceMark(worldToScene(frontFence.getWorldPosition() + markOffset));
            trackMarks[i]->setLine(QLineF(backFenceMark, frontFenceMark));
        }
    }
}
