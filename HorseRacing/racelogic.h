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

    bool raceFinished() { return finished; }
    void nexTick();

private:
    float trackLength;
    std::vector<float> horsePos;
    float cameraPos;
    bool finished;
    float baseSpeed = BASE_SPEED;
};

#endif // RACELOGIC_H
