#ifndef RACECLIENT_H
#define RACECLIENT_H

#include <QObject>
#include <QTcpSocket>

class RaceClient : public QObject
{
    Q_OBJECT
public:
    explicit RaceClient(QObject *parent = 0);
    ~RaceClient();

private:
    QTcpSocket *socket;

private slots:
    void socketRead();
    void socketError(QAbstractSocket::SocketError);
};

#endif // RACECLIENT_H
