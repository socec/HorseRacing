#ifndef CLIENTMODEL_H
#define CLIENTMODEL_H

#include <QQueue>

#include "racemodel.h"
#include "network/raceclient.h"
#include "network/racemessage.h"

/**
 * @brief Client side race model.
 */
class ClientModel : public RaceModel
{
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Constructor with initial parameters.
     * @param trackLength - Length of the race track.
     * @param horseCount - Number of horses in the race.
     * @param parent - Parent object used for hierarchy.
     */
    ClientModel(float trackLength, int horseCount, QObject *parent = 0);

private:
    // communication client
    RaceClient client;
    QQueue<QByteArray> messageQueue;

    // inherited from RaceModel
    /**
     * @brief Receives updated positions from server race model.
     */
    void nextModelStep();

private slots:
    /**
     * @brief Handles message with updated horse and camera positions.
     * @param message - Message received from server.
     */
    void receivePositionsMessage(QByteArray message);

    /**
     * @brief Handles server response.
     * @param message - Message received from server.
     */
    void receiveResponse(QByteArray message);
};

#endif // CLIENTMODEL_H
