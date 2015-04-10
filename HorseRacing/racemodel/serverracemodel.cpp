#include "serverracemodel.h"

ServerRaceModel::ServerRaceModel(float trackLength, int horseCount, QObject *parent)
    : RaceModel(trackLength, horseCount, parent)
{
    timer.setInterval(1000 / fps);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHandler()));
}

void ServerRaceModel::startRace()
{
    // delay start for 1 second
    QTimer::singleShot(1000, this, SLOT(delayedStart()));
}

void ServerRaceModel::nextModelStep()
{
    // advance camera at constant speed
    cameraPosition += baseSpeed;

    // advance each horse at random speed
    for (unsigned int i = 0; i < horsePositions.size(); i++) {
        horsePositions.at(i) += (baseSpeed - 1) + rand() % 3;
    }

    emit positionsChanged(horsePositions, cameraPosition);

    server.sendDataToClients(createMsgPositions());
}

QByteArray ServerRaceModel::createMsgPositions()
{
    QByteArray msg;
    for (unsigned int i = 0; i < horsePositions.size(); i++) {
        msg.append("H@" + QString::number((double) horsePositions.at(i), 'f', 2));
    }
    msg.append("C@" + QString::number((double) cameraPosition, 'f', 2));
    return msg;
}

void ServerRaceModel::timerHandler()
{
    // keep calculating next steps of the model
    nextModelStep();
    checkRaceStatus();

    // keep running for 3 seconds after the race is finished
    if (finished) {
        QTimer::singleShot(3000, this, SLOT(delayedStop()));
    }
}

void ServerRaceModel::delayedStart()
{
    timer.start();
}

void ServerRaceModel::delayedStop()
{
    timer.stop();
    emit modelStopped();
}
