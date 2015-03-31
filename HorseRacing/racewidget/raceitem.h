#ifndef RACEITEM_H
#define RACEITEM_H

#include <QVector3D>
#include <QSizeF>

class RaceItem
{
public:
    RaceItem(QVector3D worldPos, QSizeF worldSize);

    QVector3D getWorldPos() const { return worldPos; }
    QSizeF getWorldSize() const { return worldSize; }

    virtual void updateScenePos(const QPointF& newScenePos) = 0;
    virtual void updateWorldPos(const QVector3D& newWorldPos) = 0;

protected:
    QVector3D worldPos;
    QSizeF worldSize;
};

#endif // RACEITEM_H
