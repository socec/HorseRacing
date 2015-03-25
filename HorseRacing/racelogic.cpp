#include "racelogic.h"

RaceLogic::RaceLogic(float trackLength, int horseCount)
{
    this->trackLength = trackLength;
    finished = false;
    // initial camera position
    cameraPos = 0.0;
    // initial horse positions and standings
    for (int i = 0; i < horseCount; i++) {
        horsePos.insert(horsePos.end(), 0.0);
        standings.insert(standings.end(), 0);
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

    updateStandings();
    // check if race is finished
    if (!results.empty()) {
        finished = (results.size() == horsePos.size());
    }
}

void RaceLogic::updateStandings()
{
    // helping structure for sorting standings (sort indices based on current position)
    struct Info {
        int index;
        float position;
    };
    std::vector<Info> horseInfo;

    // collect information
    for (int i = 0; i < horsePos.size(); i++) {
        Info info = {i, horsePos.at(i)};
        horseInfo.insert(horseInfo.end(), info);
    }

    // sort standings, using lambda function to overload default sort operator
    std::sort(horseInfo.begin(), horseInfo.end(),
              [] (Info info1, Info info2) { return info1.position > info2.position; });

    // update current standings after sorting
    for (int i = 0; i < horseInfo.size(); i++) {
        Info info = horseInfo.at(i);
        standings.at(i) = info.index;
        // add the horse that finished the race to final results
        if (info.position >= trackLength)
            // add horse if not already in the final results
            if (std::find(results.begin(), results.end(), info.index) == results.end()) {
                results.insert(results.end(), info.index);
            }
    }
}
