#ifndef SERVERRACEMODEL_H
#define SERVERRACEMODEL_H

#include <QTimer>

#include "racemodel.h"
#include "network/raceserver.h"

#define BASE_SPEED (5.0)
#define FPS (25)

/**
 * @brief Server side race model.
 */
class ServerRaceModel : public RaceModel {
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Class constructor.
     * @param trackLength - Length of the race track.
     * @param horseCount - Number of horses in the race.
     * @param parent - Parent object used for hierarchy.
     */
    ServerRaceModel(float trackLength, int horseCount, QObject *parent = 0);

    // inherited from RaceModel
    void startRace();

private:
    // communication server
    RaceServer server;

    // timing
    float baseSpeed = BASE_SPEED;
    QTimer timer;
    int fps = FPS;

    // inherited from RaceModel
    /**
     * @brief Advances the horses at random speed and camera at constant speed.
     */
    void nextModelStep();

    /**
     * @brief Creates a message for clients with updated horse and camera positions.
     * @return Message with updated positions.
     */
    QByteArray createPositionsMessage();

private slots:
    /**
     * @brief Advances the model on timer tick.
     */
    void timerHandler();

    /**
     * @brief Starts the model.
     */
    void delayedStart();

    /**
     * @brief Stops the model.
     */
    void delayedStop();
};

#endif // SERVERRACEMODEL_H
