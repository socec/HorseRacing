#ifndef RACEMODEL_H
#define RACEMODEL_H

#include <QObject>
#include <QVector>
#include <QTimer>

#define FPS (25)
#define FINISH_DELAY (3000)

/**
 * @brief Base class for modeling a race.
 *
 * Race model is responsible for updating horse and camera positions,
 * providing race results and signaling the start and finish of the race.
 */
class RaceModel : public QObject
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
    explicit RaceModel(float trackLength, int horseCount, QObject *parent = 0);

    /**
     * @brief Returns length of the race track.
     * @return Length of the race track.
     */
    float getTrackLength() const { return trackLength; }

    /**
     * @brief Returns current horse positions.
     * @return Vector holding the current position of each horse.
     */
    QVector<float> getHorsePositions() const { return horsePositions; }

    /**
     * @brief Returns current camera position.
     * @return Position of the camera.
     */
    float getCameraPosition() const { return cameraPosition; }

    /**
     * @brief Returns current race results in a form of sorted lane numbers.
     *        Updated as each horse crosses the finish line.
     * @return Vector of lane numbers sorted by final race position.
     */
    QVector<int> getResults() const { return results; }

public slots:
    /**
     * @brief Starts the race model.
     */
    void startRace();

signals:
    /**
     * @brief The model changed horse and camera positions.
     * @param horsePositions - Updated horse positions.
     * @param cameraPosition- Updated camera position.
     */
    void positionsChanged(const QVector<float>& horsePositions, const float& cameraPosition);

    /**
     * @brief Race results are available to display.
     * @param currentResults - Current race results.
     */
    void resultsAvailable(const QVector<int>& currentResults);

    /**
     * @brief The race running on this model is finished.
     *        The model will keep runnning for some time to avoid sudden stop.
     */
    void raceFinished();

    /**
     * @brief The model is no longer running.
     */
    void modelStopped();

protected:
    // race essentials
    float trackLength;
    QVector<float> horsePositions;
    float cameraPosition;
    QVector<int> results;

    // flag available to subclasses
    bool finished = false;

    // timing
    QTimer timer;
    struct
    {
        // update interval of the model, frames per second used in animation
        int fps = FPS;
        // miliseconds to keep the model running after the race is finished
        float finishDelay = FINISH_DELAY;
    } timing;

    /**
     * @brief Updates the race status and emits signals for special events.
     */
    void updateRaceStatus();

    /**
     * @brief Calculates horse and camera positions for the next step in the model.
     *        Called at regular intervals to allow race animation.
     *        Specific implementation needs to be provided by a subclass.
     */
    virtual void nextModelStep() = 0;

private slots:
    /**
     * @brief Advances the model on timer tick.
     */
    void timerHandler();

    /**
     * @brief Stops the race model.
     */
    void stopRace();
};

#endif // RACEMODEL_H
