#ifndef CLIENTRACEMODEL_H
#define CLIENTRACEMODEL_H

#include "racemodel.h"
#include "network/raceclient.h"

class ClientRaceModel : public RaceModel
{
    Q_OBJECT
public:
    ClientRaceModel(float trackLength, int horseCount, QObject *parent = 0);

    void startRace();

private:
    RaceClient client;

    void nextModelStep();

private slots:
    void getServerMsg(QByteArray msg);
    void delayedStop();
};

#endif // CLIENTRACEMODEL_H
