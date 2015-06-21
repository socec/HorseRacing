#include "raceclient.h"

#include "iostream"

RaceClient::RaceClient(QString hostName, quint16 port, QObject *parent)
    : QObject(parent) {
    // initialize socket
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

RaceClient::~RaceClient() {
    if (socket) {
        socket->close();
        delete socket;
        socket = nullptr;
    }
}

void RaceClient::socketRead() {
    QByteArray msg = socket->readAll();
    QString msgString = QString::fromUtf8(msg);
    std::cerr << "server says: " << msgString.toStdString() << "\n";
    emit dataReceived(msg);
}

void RaceClient::socketError(QAbstractSocket::SocketError) {
    std::cerr << "socket error: " << socket->errorString().toStdString();
}
