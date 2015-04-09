#include "racemodel.h"

#include <algorithm>

RaceModel::RaceModel(float trackLength, int horseCount, QObject *parent)
    : trackLength(trackLength)
{
    Q_UNUSED(parent);
    // initial camera position
    cameraPosition = 0.0;
    // initial horse positions
    for (int i = 0; i < horseCount; i++) {
        horsePositions.insert(horsePositions.end(), 0.0);
    }
}

RaceModel::~RaceModel()
{
}

void RaceModel::checkRaceStatus()
{
    if (horsePositions.empty()) return;

    // check if a horse crossed the finish line
    for (unsigned int i = 0; i < horsePositions.size(); i++) {
        if (horsePositions.at(i) >= trackLength)
            // append horses to results array as they finish the race
            if (std::find(results.begin(), results.end(), i) == results.end()) {
                results.insert(results.end(), i);
            }
    }
    // notify about available results
    if (!results.empty()) {
        emit resultsAvailable(results);
    }
    // race is finished when all horses finish the race
    if (results.size() == horsePositions.size()) {
        finished = true;
        emit raceFinished();
    }
}
