#include "racecontrol.h"

RaceControl::RaceControl(QWidget *parent) :
    QWidget(parent)
{
    uiSetup();

    timer.setInterval(1000 / fps);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHandler()));
}

RaceControl::~RaceControl()
{
    if (view) delete view;
    if (logic) delete logic;
    delete startButton;
    delete gridLayout;
}

void RaceControl::uiSetup()
{
    // set the main widget
    setMinimumSize(WIDGET_W, WIDGET_H);
    setMaximumSize(WIDGET_W, WIDGET_H);
    setGeometry(0, 0, WIDGET_W, WIDGET_H);

    // set grid layout
    gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(gridLayout);

    // set start button
    startButton = new QPushButton("start");
    connect(startButton, SIGNAL(clicked()), this, SLOT(startButtonHandler()));
    gridLayout->addWidget(startButton);
}

void RaceControl::startButtonHandler()
{
    // initialize race logic and view
    logic = new RaceLogic(TRACK_LENGTH, HORSE_COUNT);
    view = new RaceWidget(TRACK_LENGTH, HORSE_COUNT);
    gridLayout->addWidget(view);

    // remove start button and start the timer
    gridLayout->removeWidget(startButton);
    timer.start();
    state = R_START;
}

void RaceControl::timerHandler()
{
    switch(state) {
    case R_START:
        // wait for 1 second before starting the race
        if (++timerCounter == 1 * fps) {
            state = R_RUN;
            timerCounter = 0;
        }
        break;
    case R_RUN:
        // update race status
        logic->nexTick();
        view->raceUpdate(logic->getHorsePos(), logic->getCameraPos());
        // check if race finished
        if (logic->raceFinished()) {
            state = R_FINISH;
        }
        // show results if needed
        if (!logic->getResults().empty()) {
            view->showResults(logic->getResults());
        }
        break;
    case R_FINISH:
        // keep updating race status for 3 seconds after race finished
        if (++timerCounter < 3 * fps) {
            logic->nexTick();
            view->raceUpdate(logic->getHorsePos(), logic->getCameraPos());
        }
        // now reset
        else {
            state = R_INIT;
            timerCounter = 0;
            delete view;
            delete logic;
            view = nullptr;
            logic = nullptr;
            gridLayout->addWidget(startButton);
            timer.stop();
        }
        break;
    }
}
