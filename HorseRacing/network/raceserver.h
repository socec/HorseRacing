#ifndef RACESERVER_H
#define RACESERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QSharedPointer>

/**
 * @brief Server for race data exchange.
 */
class RaceServer : public QObject
{
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Constructor with initial parameters.
     * @param multicastAddress - Address used for sending multicast data.
     * @param multicastPort - Port used for sending multicast data.
     * @param port - TCP port for incoming client connections.
     * @param parent - Parent object used for hierarchy.
     */
    explicit RaceServer(QString multicastAddress, quint16 multicastPort, quint16 tcpPort,
                        QObject *parent = 0);

    /**
     * @brief Returns multicast address of the server.
     * @return String representation of multicast address.
     */
    QString getMulticastAddress() { return multicastAddress.toString(); }

    /**
     * @brief Returns multicast port of the server.
     * @return Multicast port.
     */
    quint16 getMulticastPort() { return multicastPort; }

    /**
     * @brief Sends data to all clients listening.
     * @param data - Byte array of data to send.
     */
    void sendMulticastData(const QByteArray& data);

    /**
     * @brief Returns TCP port of the server.
     * @return TCP port of the server if server is listening for connections, 0 otherwise.
     */
    unsigned int getTcpPort() { return tcpServer.serverPort(); }

    /**
     * @brief Sends data to a connected client.
     * @param id - ID of the connected client.
     * @param data - Byte array of data to send.
     */
    void sendDataToClient(const unsigned int id, const QByteArray& data);

    /**
     * @brief Returns IDs of connected clients with incoming data to read.
     * @return Vector of client IDs with available data to read.
     */
     QVector<unsigned int> clientsWithIncomingData();

    /**
     * @brief Reads data from a connected client.
     * @param id - ID of the connected client.
     * @return Byte array of data from the client.
     */
    QByteArray readDataFromClient(const unsigned int id);

signals:
    /**
     * @brief There is incoming data to read from connected clients.
     */
    void incomingClientData();

private:
    QUdpSocket multicastSocket;
    QHostAddress multicastAddress;
    quint16 multicastPort;
    QTcpServer tcpServer;
    QVector<QSharedPointer<QTcpSocket>> clients;

private slots:
    /**
     * @brief Handles new client connections.
     */
    void newConnectionHandler();

    /**
     * @brief Handles notifications about incoming data from connected clients.
     */
    void incomingDataHandler();
};

#endif // RACESERVER_H
