#include "clientracemodel.h"

ClientRaceModel::ClientRaceModel(float trackLength, int horseCount, QObject *parent)
    : RaceModel(trackLength, horseCount, parent), client("127.0.0.1", 4000) {
    connect(&client, SIGNAL(dataReceived(QByteArray)), this, SLOT(receivePositionsMessage(QByteArray)));
}

void ClientRaceModel::startRace() {
}

void ClientRaceModel::nextModelStep() {
    // emit signal about changed positions
    emit positionsChanged(horsePositions, cameraPosition);
}

void ClientRaceModel::receivePositionsMessage(QByteArray message) {
    // parse positions message
    RaceMessage::parsePositions(message, horsePositions, cameraPosition);

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
