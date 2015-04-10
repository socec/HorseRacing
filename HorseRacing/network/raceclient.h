#ifndef RACECLIENT_H
#define RACECLIENT_H

#include <QObject>
#include <QTcpSocket>

class RaceClient : public QObject
{
    Q_OBJECT
public:
    explicit RaceClient(QString hostName, quint16 port, QObject *parent = 0);
    ~RaceClient();

signals:
    void msgReceived(QByteArray msg);

private:
    QTcpSocket *socket = nullptr;

private slots:
    void socketRead();
    void socketError(QAbstractSocket::SocketError);
};

#endif // RACECLIENT_H
