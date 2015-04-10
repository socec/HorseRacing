#ifndef RACESERVER_H
#define RACESERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class RaceServer : public QObject
{
    Q_OBJECT
public:
    explicit RaceServer(QObject *parent = 0);
    ~RaceServer();

    void sendDataToClients(const char *data);

private:
    QTcpServer *server = nullptr;
    QTcpSocket *clientSocket = nullptr;

private slots:
    void newClientConnection();
    void clientRead();
};

#endif // RACESERVER_H
