#ifndef RACEITEM_H
#define RACEITEM_H

#include <QVector3D>
#include <QSizeF>

class RaceItem
{
public:
    RaceItem(QVector3D worldPos, QSizeF worldSize);

    QVector3D getWorldPos() { return worldPos; }
    void setWorldPos(QVector3D newPos) { worldPos = newPos; }
    QSizeF getWorldSize() const { return worldSize; }

    virtual void updateScenePos(QPointF newScenePos) = 0;
    virtual void updateWorldPos(QVector3D newWorldPos) = 0;

private:
    QVector3D worldPos;
    QSizeF worldSize;
};

#endif // RACEITEM_H
