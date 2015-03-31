#ifndef RACELOGIC_H
#define RACELOGIC_H

#include <vector>
#include <algorithm>

#define BASE_SPEED (5.0)

class RaceLogic
{
public:
    RaceLogic(float trackLength, int horseCount);

    float getTrackLength() const { return trackLength; }
    std::vector<float> getHorsePos() const { return horsePos; }
    int getHorseCount() const { return horsePos.size(); }
    float getCameraPos() const { return cameraPos; }
    std::vector<int> getStandings() const { return standings; }
    std::vector<int> getResults() const { return results; }

    bool raceFinished() const { return finished; }
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
