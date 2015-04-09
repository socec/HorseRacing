#include "localracemodel.h"

#include <cstdlib> // rand()

LocalRaceModel::LocalRaceModel(float trackLength, int horseCount, QObject *parent)
    : RaceModel(trackLength, horseCount, parent)
{
    timer.setInterval(1000 / fps);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHandler()));
}

void LocalRaceModel::startRace()
{
    // delay start for 1 second
    QTimer::singleShot(1000, this, SLOT(delayedStart()));
}

void LocalRaceModel::nextModelStep()
{
    // advance camera at constant speed
    cameraPosition += baseSpeed;

    // advance each horse at random speed
    for (unsigned int i = 0; i < horsePositions.size(); i++) {
        horsePositions.at(i) += (baseSpeed - 1) + rand() % 3;
    }

    emit positionsChanged(horsePositions, cameraPosition);
}

void LocalRaceModel::timerHandler()
{
    // keep calculating next steps of the model
    nextModelStep();
    checkRaceStatus();

    // keep running for 3 seconds after the race is finished
    if (finished) {
        QTimer::singleShot(3000, this, SLOT(delayedStop()));
    }
}

void LocalRaceModel::delayedStart()
{
    timer.start();
}

void LocalRaceModel::delayedStop()
{
    timer.stop();
    emit modelStopped();
}
