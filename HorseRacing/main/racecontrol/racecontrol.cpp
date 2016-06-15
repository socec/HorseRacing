#include <racecontrol.h>

RaceControl::RaceControl(QWidget *parent)
    : QWidget(parent),
      gridLayout(this),
      startButton(this),
      serverButton(this),
      clientButton(this)
{
    uiSetup();
}

void RaceControl::uiSetup()
{
    // set the main widget
    setMinimumSize(WIDGET_WIDTH, WIDGET_HEIGHT + BUTTON_HEIGHT);
    //setMaximumSize(WIDGET_WIDTH, WIDGET_HEIGHT);

    // set grid layout
    gridLayout.setContentsMargins(0, 0, 0, 0);
    setLayout(&gridLayout);

    // set start button
    startButton.setText("start");
    startButton.setMinimumSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    startButton.setMaximumSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    connect(&startButton, SIGNAL(clicked()), this, SLOT(startButtonHandler()));
    gridLayout.addWidget(&startButton, 1, 1);
    startButton.hide();

    // set server button
    serverButton.setText("server");
    serverButton.setMinimumSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    serverButton.setMaximumSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    connect(&serverButton, SIGNAL(clicked()), this, SLOT(serverButtonHandler()));
    gridLayout.addWidget(&serverButton, 1, 1);

    // set client button
    clientButton.setText("client");
    clientButton.setMinimumSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    clientButton.setMaximumSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    connect(&clientButton, SIGNAL(clicked()), this, SLOT(clientButtonHandler()));
    gridLayout.addWidget(&clientButton, 1, 2);
}

void RaceControl::initRaceView()
{
    // initialize race view
    view = QSharedPointer<RaceWidget>(new RaceWidget(TRACK_LENGTH, HORSE_COUNT));
    gridLayout.addWidget(view.data(), 2, 1);
    connect(model.data(), SIGNAL(positionsChanged(QVector<float>,float)),
            view.data(), SLOT(updatePositions(QVector<float>,float)));
    connect(model.data(), SIGNAL(resultsAvailable(QVector<int>)),
            view.data(), SLOT(showResults(QVector<int>)));
    connect(model.data(), SIGNAL(modelStopped()),
            this, SLOT(modelHandler()));
}

void RaceControl::startButtonHandler()
{
    model->startRace();
    startButton.hide();
}

void RaceControl::serverButtonHandler()
{
    model = QSharedPointer<RaceModel>(new ServerModel(TRACK_LENGTH, HORSE_COUNT));
    initRaceView();

    // handle buttons
    serverButton.hide();
    clientButton.hide();
    startButton.show();
}

void RaceControl::clientButtonHandler()
{
    model = QSharedPointer<RaceModel>(new ClientModel(TRACK_LENGTH, HORSE_COUNT));
    initRaceView();
    model->startRace();

    // handle buttons
    serverButton.hide();
    clientButton.hide();
}

void RaceControl::modelHandler()
{
    view.clear();
    model.clear();

    // handle buttons
    serverButton.show();
    clientButton.show();
    startButton.hide();
}
