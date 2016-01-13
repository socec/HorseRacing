#include "raceserver.h"

#include <QDebug>

RaceServer::RaceServer(QString multicastAddress, quint16 multicastPort, quint16 tcpPort,
                       QObject *parent)
    : QObject(parent),
      multicastSocket(this),
      multicastAddress(QHostAddress(multicastAddress)),
      multicastPort(multicastPort),
      tcpServer(this)
{
    // new client connections emit signal
    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(newConnectionHandler()));

    // start the server
    if (tcpServer.listen(QHostAddress::Any, tcpPort) == false)
    {
        qDebug() << "Server could not start: " << tcpServer.errorString();
    }
}

void RaceServer::sendMulticastData(const QByteArray& data)
{
    multicastSocket.writeDatagram(data, multicastAddress, multicastPort);
    multicastSocket.flush();
}

void RaceServer::sendDataToClient(const uint id, const QByteArray& data)
{
    clients.at(id)->write(data);
    clients.at(id)->flush();
}

QByteArray RaceServer::readDataFromClient(const uint id)
{
    return clients.at(id)->readAll();
}

uint RaceServer::clientSocketToId(const QTcpSocket *client)
{
    uint id = -1;
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients.at(i).data() == client)
        {
            id = i;
            break;
        }
    }
    return id;
}

void RaceServer::newConnectionHandler()
{
    // add new client socket to the client list
    QSharedPointer<QTcpSocket> client(tcpServer.nextPendingConnection());
    clients.append(client);
    // clients emit signal when they have data ready to read
    connect(client.data(), SIGNAL(readyRead()),
            this, SLOT(clientDataHandler()));
    // clients emit signal when they disconnect
    connect(client.data(), SIGNAL(disconnected()),
            this, SLOT(clientDisconnectHandler()));

    qDebug() << QString("New client connected: %1\n").arg(client.data()->peerAddress().toString());
}

void RaceServer::clientDataHandler()
{
    // emit signal with the client ID
    uint id = clientSocketToId(qobject_cast<QTcpSocket*>(sender()));
    emit pendingClientData(id);

    qDebug() << "Client == " << id << " == sent data";
}

void RaceServer::clientDisconnectHandler()
{
    uint id = clientSocketToId(qobject_cast<QTcpSocket*>(sender()));
    clients.remove(id);

    qDebug() << "Client == " << id << " == disconnected";
}
