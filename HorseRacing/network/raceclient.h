#ifndef RACECLIENT_H
#define RACECLIENT_H

#include <QObject>
#include <QTcpSocket>

/**
 * @brief Client for race data exchange.
 */
class RaceClient : public QObject
{
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Constructor with initial parameters.
     * @param hostName - Server host name.
     * @param port - Server port number.
     * @param parent - Parent object used for hierarchy.
     */
    explicit RaceClient(QString hostName, quint16 port, QObject *parent = 0);

signals:
    /**
     * @brief Data was received from the server.
     * @param data - Received data.
     */
    void dataReceived(QByteArray data);

private:
    QTcpSocket socket;

private slots:
    /**
     * @brief Handles notifications about incoming data from server.
     */
    void incomingDataHandler();
};

#endif // RACECLIENT_H
