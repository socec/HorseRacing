#include "raceserver.h"

#include "iostream"

RaceServer::RaceServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);
    // new client connections emit signal
    connect(server, SIGNAL(newConnection()), this, SLOT(newClientConnection()));

    // start server
    if (!server->listen(QHostAddress::Any, 4000)) {
        std::cerr << "Server could not start\n" << server->errorString().toStdString();
    }
    else {
        std::cerr << "Server started!\n";
    }
}

RaceServer::~RaceServer()
{
    if (clientSocket) {
        clientSocket->close();
        delete clientSocket;
    }
    if (server) {
        server->close();
        delete server;
    }
}

void RaceServer::newClientConnection()
{
    // accept new connection
    clientSocket = server->nextPendingConnection();
    std::cerr << "new client connected!\n";

    // clients with available data emit signal
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(clientRead()));

    // send welcome message to client
    clientSocket->write("Hello client!\n");
    clientSocket->flush();
    clientSocket->waitForBytesWritten(3000);
}

void RaceServer::clientRead()
{
    QString msg = QString::fromUtf8(clientSocket->readAll());
    std::cerr << "client says: " << msg.toStdString();

}
