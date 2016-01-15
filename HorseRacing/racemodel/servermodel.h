#ifndef SERVERMODEL_H
#define SERVERMODEL_H

#include "racemodel.h"
#include "network/raceserver.h"
#include "network/racemessage.h"

#define BASE_SPEED (5.0)

/**
 * @brief Server side race model.
 */
class ServerModel : public RaceModel
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
    ServerModel(float trackLength, int horseCount, QObject *parent = 0);

private:
    // communication server
    RaceServer server;

    // base speed in world coordinates per second
    float baseSpeed = BASE_SPEED;

    // inherited from RaceModel
    /**
     * @brief Advances the horses at random speed and camera at constant speed.
     *        Notifies connected clients about the updates.
     */
    void nextModelStep();

private slots:
    /**
     * @brief Handles client request.
     * @param id - ID of the connected client with the request.
     */
    void receiveRequest(int id);
};

#endif // SERVERMODEL_H
