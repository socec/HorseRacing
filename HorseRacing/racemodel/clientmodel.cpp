#include "clientmodel.h"

ClientModel::ClientModel(float trackLength, int horseCount, QObject *parent)
    : RaceModel(trackLength, horseCount, parent),
      client("127.0.0.1", 4000)
{
    // configure multicast, hardcoded for now
    client.configureMulticast("239.255.13.37", 51337);

    // handle position message datagram
    connect(&client, SIGNAL(datagramReceived(QByteArray)),
            this, SLOT(receivePositionsMessage(QByteArray)));
    // handle server responses
    connect(&client, SIGNAL(responseReceived(QByteArray)),
            this, SLOT(receiveResponse(QByteArray)));

    QByteArray data;
    data.append("hello ");
    data.append(QString::number(rand() % 10));
    client.sendDataToServer(data);
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

void ClientModel::receiveResponse(QByteArray message)
{
    qDebug() << "Server responded: " << message;
}
