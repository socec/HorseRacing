#ifndef RACESERVER_H
#define RACESERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class RaceServer : public QObject
{
    Q_OBJECT
public:
    explicit RaceServer(QObject *parent = 0);
    ~RaceServer();

private:
    QTcpServer *server = nullptr;
    QTcpSocket *clientSocket = nullptr;

private slots:
    void newClientConnection();
    void clientRead();
};

#endif // RACESERVER_H
