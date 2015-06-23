#ifndef RACESERVER_H
#define RACESERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

/**
 * @brief Server for race data.
 */
class RaceServer : public QObject {
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Class constructor.
     * @param parent - Parent object used for hierarchy.
     */
    explicit RaceServer(QObject *parent = 0);

    /**
     * @brief Class destructor.
     */
    ~RaceServer();

    /**
     * @brief Sends data to connected clients.
     * @param data - Data to send.
     */
    void sendDataToClients(const QByteArray data);

private:
    QTcpServer *server = nullptr;
    QTcpSocket *clientSocket = nullptr;

private slots:
    /**
     * @brief Handles new client connections.
     */
    void newClientConnection();

    /**
     * @brief Reads incoming data from a client.
     */
    void clientRead();
};

#endif // RACESERVER_H
