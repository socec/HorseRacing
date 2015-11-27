#include "servermodel.h"

ServerModel::ServerModel(float trackLength, int horseCount, QObject *parent)
    : RaceModel(trackLength, horseCount, parent),
      server(4000)
{
    // nothing to do
}

void ServerModel::nextModelStep()
{
    // advance camera at constant speed
    cameraPosition += baseSpeed;

    // advance each horse at random speed
    for (int i = 0; i < horsePositions.size(); i++)
    {
        float newPosition = horsePositions.at(i) + (baseSpeed - 1) + (rand() % 3);
        horsePositions.replace(i, newPosition);
    }

    // notify clients about changed positions
    QByteArray positionsMessage = RaceMessage::createPositions(horsePositions, cameraPosition);
    server.sendDataToAllClients(positionsMessage);
}
