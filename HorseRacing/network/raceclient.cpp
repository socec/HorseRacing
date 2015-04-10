#include "raceclient.h"

#include "iostream"

RaceClient::RaceClient(QString hostName, quint16 port, QObject *parent)
    : QObject(parent)
{
    socket = new QTcpSocket(this);
    // server emits signal when sending data
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketRead()));
    // socket error emits signal
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));

    // connect to server
    socket->connectToHost(hostName, port);
    if (socket->waitForConnected())
        std::cerr << "Connected to server!";
    else
        std::cerr << "socket error: " << socket->errorString().toStdString();
}

RaceClient::~RaceClient()
{
    if (socket) {
        socket->close();
        delete socket;
    }
}

void RaceClient::socketRead()
{
    QByteArray msg = socket->readAll();
    QString msgString = QString::fromUtf8(msg);
    std::cerr << "server says: " << msgString.toStdString() << "\n";
    emit msgReceived(msg);
}

void RaceClient::socketError(QAbstractSocket::SocketError)
{
    std::cerr << "socket error: " << socket->errorString().toStdString();
}
