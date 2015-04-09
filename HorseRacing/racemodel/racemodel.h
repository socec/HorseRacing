#ifndef RACEMODEL_H
#define RACEMODEL_H

#include <QObject>

#include <vector>

class RaceModel : public QObject
{
    Q_OBJECT
public:
    explicit RaceModel(float trackLength, int horseCount, QObject *parent = 0);
    virtual ~RaceModel();

    float getTrackLength() const { return trackLength; }
    std::vector<float> getHorsePositions() const { return horsePositions; }
    float getCameraPosition() const { return cameraPosition; }
    std::vector<int> getResults() const { return results; }

signals:
    void positionsChanged(const std::vector<float>& horsePosX, const float& cameraPosX);
    void resultsAvailable(const std::vector<int>& currentResults);
    void raceFinished();
    void modelStopped();

protected:
    float trackLength;
    std::vector<float> horsePositions;
    float cameraPosition;
    std::vector<int> results;
    bool finished = false;

    void checkRaceStatus();

    virtual void nextModelStep() = 0;
};

#endif // RACEMODEL_H
