#ifndef RACESERVER_H
#define RACESERVER_H

#include <QObject>
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
     * @param port - TCP port for incoming client connections.
     * @param parent - Parent object used for hierarchy.
     */
    explicit RaceServer(quint16 port, QObject *parent = 0);

    /**
     * @brief Returns TCP port of the server.
     * @return TCP port of the server if server is listening for connections, 0 otherwise.
     */
    unsigned int getPort() { return server.serverPort(); }

    /**
     * @brief Sends data to a connected client.
     * @param id - ID of the connected client.
     * @param data - Byte array of data to send.
     */
    void sendDataToClient(const unsigned int id, const QByteArray& data);

    /**
     * @brief Sends data to all connected clients.
     * @param data - Byte array of data to send.
     */
    void sendDataToAllClients(const QByteArray& data);

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
    QTcpServer server;
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
