#include "servermodel.h"

ServerModel::ServerModel(float trackLength, int horseCount, QObject *parent)
    : RaceModel(trackLength, horseCount, parent),
      server("239.255.13.37", 51337, 4000)
{
    // listen to client messages
    connect(&server, SIGNAL(pendingClientData(uint)), this, SLOT(receiveRequest(uint)));
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
    server.sendMulticastData(positionsMessage);
}

void ServerModel::receiveRequest(uint id)
{
    QByteArray request = server.readDataFromClient(id);
    qDebug() << "Client " << id << " wants: " << request;
    server.sendDataToClient(id, request.append(" to " + QString::number(id)));
}
