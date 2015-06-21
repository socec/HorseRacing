#ifndef CLIENTRACEMODEL_H
#define CLIENTRACEMODEL_H

#include "racemodel.h"
#include "network/raceclient.h"

/**
 * @brief Client side race model.
 */
class ClientRaceModel : public RaceModel {
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Class constructor.
     * @param trackLength - Length of the race track.
     * @param horseCount - Number of horses in the race.
     * @param parent - Parent object used for hierarchy.
     */
    ClientRaceModel(float trackLength, int horseCount, QObject *parent = 0);

    // inherited from RaceModel
    void startRace();

private:
    // communication client
    RaceClient client;

    // inherited from RaceModel
    /**
     * @brief Receives updated positions from server race model.
     */
    void nextModelStep();

private slots:
    /**
     * @brief Handles received message with updated horse and camera positions.
     * @param msg - Message received from server.
     */
    void receivePositionsMessage(QByteArray msg);

    /**
     * @brief Stops the model.
     */
    void delayedStop();
};

#endif // CLIENTRACEMODEL_H
