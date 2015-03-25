#include "racewidget.h"

RaceWidget::RaceWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();

    setRaceLogic();
    setRaceScene();

    timer.setInterval(1000 / fps);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHandler()));
}

RaceWidget::~RaceWidget()
{
    delete gridLayout;
    delete graphicsView;
    delete controlButton;
    delete cameraSlider;
    delete raceLogic;
    delete raceScene;
}

void RaceWidget::resizeEvent(QResizeEvent *event)
{
    graphicsView->resize(event->size());
    adjustUiControls();
}

void RaceWidget::setupUi()
{
    // set the main widget
    setMinimumSize(WIDGET_W, WIDGET_H);
    setMaximumSize(WIDGET_W, WIDGET_H);
    setGeometry(0, 0, WIDGET_W, WIDGET_H);

    // set grid layout
    gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(gridLayout);

    // set view
    graphicsView = new QGraphicsView(this);
    graphicsView->setMinimumSize(VIEW_W, VIEW_H);
    graphicsView->setMaximumSize(VIEW_W, VIEW_H);
    graphicsView->setGeometry(0, 0, VIEW_W, VIEW_H);
    graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    gridLayout->addWidget(graphicsView);

    // set control button
    controlButton = new QPushButton("start", graphicsView);
    controlButton->setMinimumSize(BUTTON_W, BUTTON_H);
    controlButton->setMaximumSize(BUTTON_W, BUTTON_H);
    controlButton->setGeometry(0, 0, BUTTON_W, BUTTON_H);
    connect(controlButton, SIGNAL(clicked()), this, SLOT(controlButtonHandler()));
    gridLayout->addWidget(controlButton);

    // set camera slider
    cameraSlider = new QSlider(Qt::Vertical, graphicsView);
    cameraSlider->setMinimumSize(SLIDER_W, SLIDER_H);
    cameraSlider->setMaximumSize(SLIDER_W, SLIDER_H);
    cameraSlider->setGeometry(0, 0, SLIDER_W, SLIDER_H);
    cameraSlider->setMinimum(2);
    cameraSlider->setMaximum(CAMERA_SHIFT_Y);
    cameraSlider->setValue(CAMERA_SHIFT_Y);
    gridLayout->addWidget(cameraSlider);

    // correctly adjust UI controls
    adjustUiControls();
}

void RaceWidget::adjustUiControls()
{
    // align controls to bottom left corner of the view
    QPoint viewBottomLeft = graphicsView->geometry().bottomLeft();

    // adjust control button
    QPoint buttonTopLeft = viewBottomLeft - QPoint(0, controlButton->height());
    controlButton->move(buttonTopLeft);

    // adjust camera slider
    QPoint sliderTopLeft = buttonTopLeft - QPoint(0, cameraSlider->height());
    cameraSlider->move(sliderTopLeft);
}

void RaceWidget::setRaceLogic()
{
    if (raceLogic) delete raceLogic;
    raceLogic = new RaceLogic(TRACK_LENGTH, HORSE_COUNT);
}

void RaceWidget::setRaceScene()
{
    // don't set race scene without race logic
    if (!raceLogic) setRaceLogic();

    if (raceScene) delete raceScene;
    raceScene = new RaceScene(raceLogic->getTrackLength(), raceLogic->getHorseCount(), graphicsView);

    // set scene to view
    graphicsView->setScene(raceScene);
    // connect camera slider to scene
    connect(cameraSlider, SIGNAL(valueChanged(int)), raceScene, SLOT(cameraVerticalChange(int)));
    cameraSlider->setValue(CAMERA_SHIFT_Y);
}

void RaceWidget::controlButtonHandler()
{
    // if race is finished control button allows restart
    if (raceLogic->raceFinished()) {
        // stop timer to stop the race
        timer.stop();
        // repeat race setup
        setRaceLogic();
        setRaceScene();
        // control button now allows start
        controlButton->setText("start");
    }
    // otherwise control button allows start
    else {
        // start timer to start the race
        timer.start();
        // disable control button during the race
        controlButton->setEnabled(false);
    }
}

void RaceWidget::timerHandler()
{
    raceLogic->nexTick();
    raceScene->worldUpdate(raceLogic->getHorsePos(), raceLogic->getCameraPos());

    // show race results if needed
    if (!raceLogic->getResults().empty()) {
        raceScene->showResults(raceLogic->getResults());
    }

    // if race is finished control button allows restart
    if (raceLogic->raceFinished()) {
        // enable control button after the race
        controlButton->setEnabled(true);
        // control button now allows restart
        controlButton->setText("restart");
    }
}
