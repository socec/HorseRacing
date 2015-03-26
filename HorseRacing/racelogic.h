#ifndef RACELOGIC_H
#define RACELOGIC_H

#include <vector>
#include <algorithm>

#define BASE_SPEED (5.0)

class RaceLogic
{
public:
    RaceLogic(float trackLength, int horseCount);

    float getTrackLength() { return trackLength; }
    std::vector<float> getHorsePos() { return horsePos; }
    int getHorseCount() { return horsePos.size(); }
    float getCameraPos() { return cameraPos; }
    std::vector<int> getStandings() { return standings; }
    std::vector<int> getResults() { return results; }

    bool raceFinished() { return finished; }
    void nexTick();
    void restartRace();

private:
    float trackLength;
    std::vector<float> horsePos;
    float cameraPos;
    std::vector<int> standings, results;
    bool finished;
    float baseSpeed = BASE_SPEED;

    void updateStandings();
};

#endif // RACELOGIC_H
