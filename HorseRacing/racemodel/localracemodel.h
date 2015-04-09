#ifndef LOCALRACEMODEL_H
#define LOCALRACEMODEL_H

#include <QTimer>

#include "racemodel.h"

class LocalRaceModel : public RaceModel
{
    Q_OBJECT
public:
    LocalRaceModel(float trackLength, int horseCount, QObject *parent = 0);

public slots:
    void startRace();

private:
    float baseSpeed = 5.0;
    QTimer timer;
    int fps = 25;

    void nextModelStep();

private slots:
    void timerHandler();
    void delayedStart();
    void delayedStop();
};

#endif // LOCALRACEMODEL_H
