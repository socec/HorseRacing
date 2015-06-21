#include "clientracemodel.h"

#include <QStringList>
#include <QTimer>

#include <iostream>

ClientRaceModel::ClientRaceModel(float trackLength, int horseCount, QObject *parent)
    : RaceModel(trackLength, horseCount, parent), client("127.0.0.1", 4000) {
    connect(&client, SIGNAL(msgReceived(QByteArray)), this, SLOT(receivePositionsMessage(QByteArray)));
}

void ClientRaceModel::startRace() {
}

void ClientRaceModel::nextModelStep() {
    // emit signal about changed positions
    emit positionsChanged(horsePositions, cameraPosition);
}

void ClientRaceModel::receivePositionsMessage(QByteArray msg) {
    // extract camera data
    QStringList split1 = QString::fromUtf8(msg).split("C@", QString::SkipEmptyParts);
    cameraPosition = split1.at(1).toFloat();
    // extract horses data
    QStringList split2 = split1.at(0).split("H@", QString::SkipEmptyParts);
    for (int i = 0; i < split2.size(); i++) {
        horsePositions.at(i) =  split2.at(i).toFloat();
    }

    // keep calculating next steps of the model
    nextModelStep();
    updateRaceStatus();

    // keep running for 3 seconds after the race is finished
    if (finished) {
        QTimer::singleShot(3000, this, SLOT(delayedStop()));
    }
}

void ClientRaceModel::delayedStop() {
    emit modelStopped();
}
