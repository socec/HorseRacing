#include "raceclient.h"

#include <QDebug>

RaceClient::RaceClient(QString hostName, quint16 port, QObject *parent)
    : QObject(parent),
      socket(this)
{
    // server emits signal when it has data ready to read
    connect(&socket, SIGNAL(readyRead()), this, SLOT(incomingDataHandler()));

    // connect to server
    socket.connectToHost(hostName, port);
    if (socket.waitForConnected() == false)
    {
        qDebug() << "Could not connect to server: " << socket.errorString();
    }
}

void RaceClient::incomingDataHandler()
{
    QByteArray msg = socket.readAll();
    qDebug() << "server says: " << QString::fromUtf8(msg) << "\n";
    emit dataReceived(msg);
}
