#include <racemodel.h>

RaceModel::RaceModel(float trackLength, int horseCount, QObject *parent)
    : trackLength(trackLength)
{
    Q_UNUSED(parent);

    // initial camera position
    cameraPosition = 0.0;

    // initial horse positions
    for (int i = 0; i < horseCount; i++)
    {
        horsePositions.append(0.0);
    }

    // set timer
    timer.setInterval(1000 / timing.fps);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHandler()));
}

void RaceModel::startRace()
{
    timer.start();
}

void RaceModel::updateRaceStatus()
{
    // sanity check
    if (horsePositions.empty()) return;

    // notify about changed positions
    emit positionsChanged(horsePositions, cameraPosition);

    // check if a horse crossed the finish line
    for (int i = 0; i < horsePositions.size(); i++)
    {
        // append lane number (index + 1) of a horse that finished the race to results array
        int lane = i + 1;
        if ((horsePositions.at(i) >= trackLength) && (results.contains(lane) == false))
        {
            results.append(lane);
        }
    }

    // notify about available results
    if (!results.empty())
    {
        emit resultsAvailable(results);
    }

    // race is finished when all horses finish the race
    if (results.size() == horsePositions.size())
    {
        finished = true;
        emit raceFinished();
    }
}

void RaceModel::timerHandler()
{
    // keep calculating next steps of the model
    nextModelStep();
    updateRaceStatus();

    // keep running for some time after the race is finished
    if (finished)
    {
        QTimer::singleShot(timing.finishDelay, this, SLOT(stopRace()));
    }
}

void RaceModel::stopRace()
{
    timer.stop();
    emit modelStopped();
}
