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
    delete serverButton;
    delete clientButton;
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
    startButton->hide();

    // set server button
    serverButton = new QPushButton("server");
    connect(serverButton, SIGNAL(clicked()), this, SLOT(serverButtonHandler()));
    gridLayout->addWidget(serverButton);

    // set client button
    clientButton = new QPushButton("client");
    connect(clientButton, SIGNAL(clicked()), this, SLOT(clientButtonHandler()));
    gridLayout->addWidget(clientButton);
}

void RaceControl::initRaceView()
{
    // initialize race view
    view = new RaceWidget(TRACK_LENGTH, HORSE_COUNT);
    gridLayout->addWidget(view);
    connect(model, SIGNAL(positionsChanged(std::vector<float>,float)),
            view, SLOT(updatePositions(std::vector<float>,float)));
    connect(model, SIGNAL(resultsAvailable(std::vector<int>)),
            view, SLOT(showResults(std::vector<int>)));
    connect(model, SIGNAL(modelStopped()),
            this, SLOT(modelHandler()));
}

void RaceControl::startButtonHandler()
{
    model->startRace();
    startButton->hide();
}

void RaceControl::serverButtonHandler()
{
    model = new ServerRaceModel(TRACK_LENGTH, HORSE_COUNT);
    initRaceView();

    serverButton->hide();
    clientButton->hide();

    startButton->show();
}

void RaceControl::clientButtonHandler()
{
    model = new ClientRaceModel(TRACK_LENGTH, HORSE_COUNT);
    initRaceView();

    serverButton->hide();
    clientButton->hide();
}

void RaceControl::modelHandler()
{
    delete view;
    delete model;
    view = nullptr;
    model = nullptr;

    serverButton->show();
    clientButton->show();
    startButton->hide();
}
