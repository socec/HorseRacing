#ifndef RACECLIENT_H
#define RACECLIENT_H

#include <QObject>
#include <QUdpSocket>
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

    /**
     * @brief Sends data to server.
     * @param data - Byte array of data to send.
     */
    void sendDataToServer(const QByteArray& data);

    /**
     * @brief Configures multicast connection to receive datagrams from server.
     * @param multicastAddress - Address used for receiving multicast data.
     * @param multicastPort - Port used for receiving multicast data.
     */
    void configureMulticast(QString multicastAddress, quint16 multicastPort);

signals:
    /**
     * @brief Datagram was received from the server.
     * @param data - Received datagram.
     */
    void datagramReceived(QByteArray datagram);

    /**
     * @brief Response was received from the server.
     * @param data - Server response.
     */
    void responseReceived(QByteArray datagram);

private:
    QUdpSocket multicastSocket;
    QTcpSocket tcpSocket;

private slots:
    /**
     * @brief Handles multicast datagrams from server.
     */
    void datagramHandler();

    /**
     * @brief Handles incoming data from server.
     */
    void serverDataHandler();
};

#endif // RACECLIENT_H
