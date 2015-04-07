#include "raceclient.h"

#include "iostream"

RaceClient::RaceClient(QObject *parent) :
    QObject(parent)
{
    socket = new QTcpSocket(this);
    // available data emits signal
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketRead()));
    // error emits signal
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));

    // connect to server
    socket->connectToHost("127.0.0.1", 4000);
    if (socket->waitForConnected())
        std::cerr << "Connected to server!";
    else
        std::cerr << "socket error: " << socket->errorString().toStdString();
}

RaceClient::~RaceClient()
{
    socket->close();
    delete socket;
}

void RaceClient::socketRead()
{
    QString msg = QString::fromUtf8(socket->readAll());
    std::cerr << "server says: " << msg.toStdString();
}

void RaceClient::socketError(QAbstractSocket::SocketError)
{
    std::cerr << "socket error: " << socket->errorString().toStdString();
}
