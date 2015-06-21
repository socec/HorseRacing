#ifndef RACECLIENT_H
#define RACECLIENT_H

#include <QObject>
#include <QTcpSocket>

/**
 * @brief Client for race data.
 */
class RaceClient : public QObject {
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Class constructor.
     * @param hostName - Server host name.
     * @param port - Server port number.
     * @param parent - Parent object used for hierarchy.
     */
    explicit RaceClient(QString hostName, quint16 port, QObject *parent = 0);

    /**
     * @brief Class destructor.
     */
    ~RaceClient();

signals:
    /**
     * @brief Data was received from the server.
     * @param data - Received data.
     */
    void dataReceived(QByteArray data);

private:
    QTcpSocket *socket = nullptr;

private slots:
    /**
     * @brief Reads data received on the socket.
     */
    void socketRead();

    /**
     * @brief Handles socket error.
     */
    void socketError(QAbstractSocket::SocketError);
};

#endif // RACECLIENT_H
