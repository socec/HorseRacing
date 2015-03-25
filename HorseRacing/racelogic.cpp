#include "racelogic.h"

RaceLogic::RaceLogic(float trackLength, int horseCount)
{
    this->trackLength = trackLength;
    finished = false;
    // initial camera position
    cameraPos = 0.0;
    // initial horse positions
    for (int i = 0; i < horseCount; i++) {
        horsePos.insert(horsePos.end(), 0.0);
    }
}

void RaceLogic::nexTick()
{
    // advance camera at constant speed
    cameraPos += baseSpeed;
    // advance each horse at random speed
    for (int i = 0; i < horsePos.size(); i++) {
        horsePos.at(i) += (baseSpeed - 1) + rand() % 3;
    }

    // check if race is finished
    int finishedCount = 0;
    for (int i = 0; i < horsePos.size(); i++) {
        if (horsePos.at(i) >= trackLength) finishedCount++;
    }
    finished = (finishedCount == horsePos.size());
}
