#ifndef RACEMODEL_H
#define RACEMODEL_H

#include <QObject>

#include <vector>

/**
 * @brief Base class for modeling a race.
 *
 * Race model is responsible for updating horse and camera positions,
 * providing race results and signaling the start and finish of the race.
 */
class RaceModel : public QObject {
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Class constructor.
     * @param trackLength - Length of the race track.
     * @param horseCount - Number of horses in the race.
     * @param parent - Parent object used for hierarchy.
     */
    explicit RaceModel(float trackLength, int horseCount, QObject *parent = 0);

    /**
     * @brief Class destructor.
     */
    virtual ~RaceModel();

    /**
     * @brief Returns length of the race track.
     * @return Length of the race track.
     */
    float getTrackLength() const { return trackLength; }

    /**
     * @brief Returns current horse positions.
     * @return Vector with position of each horse.
     */
    std::vector<float> getHorsePositions() const { return horsePositions; }

    /**
     * @brief Returns current camera position.
     * @return Position of the camera.
     */
    float getCameraPosition() const { return cameraPosition; }

    /**
     * @brief Returns current race results.
     *        Updated as horses cross the finish line.
     * @return Vector of horse track indexes sorted by final race position.
     */
    std::vector<int> getResults() const { return results; }

public slots:
    /**
     * @brief Starts the race model.
     *        Specific implementation needs to be provided by a subclass.
     */
    virtual void startRace() = 0;

signals:
    /**
     * @brief The model changed horse and camera positions.
     * @param horsePositions - Updated horse positions.
     * @param cameraPosition- Updated camera position.
     */
    void positionsChanged(const std::vector<float>& horsePositions, const float& cameraPosition);

    /**
     * @brief Race results are available to display.
     * @param currentResults - Current race results.
     */
    void resultsAvailable(const std::vector<int>& currentResults);

    /**
     * @brief The model finished the race.
     */
    void raceFinished();

    /**
     * @brief The model is no longer running.
     */
    void modelStopped();

protected:
    float trackLength;
    std::vector<float> horsePositions;
    float cameraPosition;
    std::vector<int> results;
    bool finished = false;

    /**
     * @brief Updates the race status and emits signals for special events.
     */
    void updateRaceStatus();

    /**
     * @brief Calculates horse and camera positions for the next step in the model.
     *        Should be called at regular intervals to allow race animation.
     *        Specific implementation needs to be provided by a subclass.
     */
    virtual void nextModelStep() = 0;
};

#endif // RACEMODEL_H
