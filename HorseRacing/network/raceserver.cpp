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
    if (clientSocket) {
        clientSocket->close();
        delete clientSocket;
    }
    if (server) {
        server->close();
        delete server;
    }
}

void RaceServer::sendDataToClients(const char *data) {
    if (!clientSocket) return;
    if (clientSocket->state() == QAbstractSocket::UnconnectedState) return;

    clientSocket->write(data);
    clientSocket->flush();
    clientSocket->waitForBytesWritten();
}

void RaceServer::newClientConnection() {
    // accept new connection
    clientSocket = server->nextPendingConnection();
    std::cerr << "new client connected!\n";

    // clients emit signal when they send data
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(clientRead()));
}

void RaceServer::clientRead() {
    QString msg = QString::fromUtf8(clientSocket->readAll());
    std::cerr << "client says: " << msg.toStdString();

}
