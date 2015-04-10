#ifndef SERVERRACEMODEL_H
#define SERVERRACEMODEL_H

#include <QTimer>

#include "racemodel.h"
#include "network/raceserver.h"

class ServerRaceModel : public RaceModel
{
    Q_OBJECT
public:
    ServerRaceModel(float trackLength, int horseCount, QObject *parent = 0);

    void startRace();

private:
    RaceServer server;

    float baseSpeed = 5.0;
    QTimer timer;
    int fps = 25;

    void nextModelStep();

    QByteArray createMsgPositions();

private slots:
    void timerHandler();
    void delayedStart();
    void delayedStop();
};

#endif // SERVERRACEMODEL_H
