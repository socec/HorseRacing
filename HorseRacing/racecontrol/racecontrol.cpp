#include "racecontrol.h"

RaceControl::RaceControl(QWidget *parent) :
    QWidget(parent)
{
    uiSetup();
}

RaceControl::~RaceControl()
{
    if (view) delete view;
    if (model) delete model;
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
    // initialize race model and view
    model = new LocalRaceModel(TRACK_LENGTH, HORSE_COUNT);
    view = new RaceWidget(TRACK_LENGTH, HORSE_COUNT);
    gridLayout->addWidget(view);
    connect(model, SIGNAL(positionsChanged(std::vector<float>,float)),
            view, SLOT(updatePositions(std::vector<float>,float)));
    connect(model, SIGNAL(resultsAvailable(std::vector<int>)),
            view, SLOT(showResults(std::vector<int>)));
    connect(model, SIGNAL(modelStopped()),
            this, SLOT(modelHandler()));

    // remove start button and start the race
    gridLayout->removeWidget(startButton);
    model->startRace();
}

void RaceControl::modelHandler()
{
    delete view;
    delete model;
    view = nullptr;
    model = nullptr;
    gridLayout->addWidget(startButton);
}
