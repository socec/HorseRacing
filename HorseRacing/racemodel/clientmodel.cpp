#include "clientmodel.h"

ClientModel::ClientModel(float trackLength, int horseCount, QObject *parent)
    : RaceModel(trackLength, horseCount, parent),
      client("127.0.0.1", 4000)
{
    // set network communication
    connect(&client, SIGNAL(dataReceived(QByteArray)),
            this, SLOT(receivePositionsMessage(QByteArray)));
}

void ClientModel::nextModelStep()
{
    // start going through position messages if they arrived
    if (!messageQueue.isEmpty())
    {
        // parse positions message
        QByteArray message = messageQueue.dequeue();
        RaceMessage::parsePositions(message, horsePositions, cameraPosition);
    }
}

void ClientModel::receivePositionsMessage(QByteArray message)
{
    // add message to queue
    messageQueue.enqueue(message);
}
