#include "raceserver.h"

#include <QDebug>

RaceServer::RaceServer(quint16 port, QObject *parent)
    : QObject(parent),
      server(this)
{
    // new client connections emit signal
    connect(&server, SIGNAL(newConnection()), this, SLOT(newConnectionHandler()));

    // start the server
    if (server.listen(QHostAddress::Any, port) == false)
    {
        qDebug() << "Server could not start: " << server.errorString();
    }
}

void RaceServer::sendDataToClient(const unsigned int id, const QByteArray& data)
{
    // drop disconnected clients
    if (clients.at(id)->state() == QAbstractSocket::UnconnectedState)
    {
        clients.remove(id);
    }
    // otherwise send data
    else
    {
        clients.at(id)->write(data);
        clients.at(id)->flush();
        clients.at(id)->waitForBytesWritten();
    }
}

void RaceServer::sendDataToAllClients(const QByteArray& data)
{
    for (int i = 0; i < clients.size(); i++)
    {
        sendDataToClient(i, data);
    }
}

QVector<unsigned int> RaceServer::clientsWithIncomingData()
{
    QVector<unsigned int> readyClients;
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients.at(i)->bytesAvailable())
        {
            readyClients.append(i);
        }
    }
    return readyClients;
}

QByteArray RaceServer::readDataFromClient(const unsigned int id)
{
    return clients.at(id)->readAll();
}

void RaceServer::newConnectionHandler()
{
    // add new socket to the client list
    QSharedPointer<QTcpSocket> client(server.nextPendingConnection());
    clients.append(client);
    // clients emit signal when they have data ready to read
    connect(clients.last().data(), SIGNAL(readyRead()), this, SLOT(incomingDataHandler()));

    qDebug() << QString("new client connected: %1\n").arg(client.data()->peerAddress().toString());
}

void RaceServer::incomingDataHandler()
{
    emit incomingClientData();
}
