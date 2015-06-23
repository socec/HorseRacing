#include "raceserver.h"

#include "iostream"

RaceServer::RaceServer(QObject *parent)
    : QObject(parent) {
    // initialize server
    server = new QTcpServer(this);

    // new client connections emit signal
    connect(server, SIGNAL(newConnection()), this, SLOT(newClientConnection()));

    // start the server
    if (!server->listen(QHostAddress::Any, 4000)) {
        std::cerr << "Server could not start\n" << server->errorString().toStdString();
    }
    else {
        std::cerr << "Server started!\n";
    }
}

RaceServer::~RaceServer() {
    for (int i = 0; i < clientSockets.size(); i++) {
        clientSockets.at(i)->close();
        delete clientSockets.at(i);
    }
    if (server) {
        server->close();
        delete server;
    }
}

void RaceServer::sendDataToClients(const QByteArray data) {
    for (int i = 0; i < clientSockets.size(); i++) {
        QTcpSocket *clientSocket = clientSockets.at(i);
        // drop disconnected clients
        if (clientSocket->state() == QAbstractSocket::UnconnectedState) {
            clientSockets.remove(i);
        }
        // otherwise send data
        else {
            clientSocket->write(data);
            clientSocket->flush();
            clientSocket->waitForBytesWritten();
        }
    }
}

void RaceServer::newClientConnection() {
    // accept new connection
    QTcpSocket *clientSocket = server->nextPendingConnection();
    // clients emit signal when they send data
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(clientRead()));
    // add new socket to the client list
    clientSockets.append(clientSocket);

    std::cerr << "new client connected!\n";
}

void RaceServer::clientRead() {
    for (int i = 0; i < clientSockets.size(); i++) {
        QTcpSocket *clientSocket = clientSockets.at(i);
        if (clientSocket->bytesAvailable()) {
            QString msg = QString::fromUtf8(clientSocket->readAll());
            std::cerr << "client " << i << ": " << msg.toStdString();
        }
    }
}
