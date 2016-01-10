#include "raceclient.h"

#include <QDebug>

RaceClient::RaceClient(QString hostName, quint16 port, QObject *parent)
    : QObject(parent),
      multicastSocket(this),
      tcpSocket(this)
{
    // server emits signal when it has data ready to read
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(incomingDataHandler()));

    // connect to server
    tcpSocket.connectToHost(hostName, port);
    if (tcpSocket.waitForConnected() == false)
    {
        qDebug() << "Could not connect to server: " << tcpSocket.errorString();
    }

    // configure multicast, hardcoded for now
    configureMulticast("239.255.13.37", 51337);
}

void RaceClient::sendDataToServer(const QByteArray &data)
{
    if (tcpSocket.state() != QAbstractSocket::UnconnectedState)
    {
        tcpSocket.write(data);
        tcpSocket.flush();
    }
}

void RaceClient::configureMulticast(QString multicastAddress, quint16 multicastPort)
{
    // using IPv4, share address with other services in the system
    multicastSocket.bind(QHostAddress::AnyIPv4, multicastPort, QUdpSocket::ShareAddress);
    multicastSocket.joinMulticastGroup(QHostAddress(multicastAddress));
    connect(&multicastSocket, SIGNAL(readyRead()), this, SLOT(datagramHandler()));
}

void RaceClient::datagramHandler()
{
    while (multicastSocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        // prepare for datagram size to avoid losing data
        datagram.resize(multicastSocket.pendingDatagramSize());
        // read datagram
        multicastSocket.readDatagram(datagram.data(), datagram.size());
        // emit signal
        emit datagramReceived(datagram);

        qDebug() << "Received datagram: " << datagram.data();
    }
}

void RaceClient::incomingDataHandler()
{
    QByteArray msg = tcpSocket.readAll();
    qDebug() << "Server says: " << QString::fromUtf8(msg);
}
