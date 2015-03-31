#include "racewidget.h"

RaceWidget::RaceWidget(RaceLogic &logic, QWidget *parent)
    : logic(logic), QWidget(parent)
{
    setupUi();

    setRaceScene();

    timer.setInterval(1000 / fps);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHandler()));
}

RaceWidget::~RaceWidget()
{
    delete scene;
    delete cameraSlider;
    delete controlButton;
    delete view;
    delete gridLayout;
}

void RaceWidget::resizeEvent(QResizeEvent *event)
{
    view->resize(event->size());
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
    view = new QGraphicsView(this);
    view->setMinimumSize(VIEW_W, VIEW_H);
    view->setMaximumSize(VIEW_W, VIEW_H);
    view->setGeometry(0, 0, VIEW_W, VIEW_H);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    gridLayout->addWidget(view);

    // set control button
    controlButton = new QPushButton("start", view);
    controlButton->setMinimumSize(BUTTON_W, BUTTON_H);
    controlButton->setMaximumSize(BUTTON_W, BUTTON_H);
    controlButton->setGeometry(0, 0, BUTTON_W, BUTTON_H);
    connect(controlButton, SIGNAL(clicked()), this, SLOT(controlButtonHandler()));
    gridLayout->addWidget(controlButton);

    // set camera slider
    cameraSlider = new QSlider(Qt::Vertical, view);
    cameraSlider->setMinimumSize(SLIDER_W, SLIDER_H);
    cameraSlider->setMaximumSize(SLIDER_W, SLIDER_H);
    cameraSlider->setGeometry(0, 0, SLIDER_W, SLIDER_H);
    cameraSlider->setMinimum(2);
    cameraSlider->setMaximum(CAMERA_SHIFT_Y);
    gridLayout->addWidget(cameraSlider);

    // correctly adjust UI controls
    adjustUiControls();
}

void RaceWidget::adjustUiControls()
{
    // align controls to bottom left corner of the view
    QPoint viewBottomLeft = view->geometry().bottomLeft();

    // adjust control button
    QPoint buttonTopLeft = viewBottomLeft - QPoint(0, controlButton->height());
    controlButton->move(buttonTopLeft);

    // adjust camera slider
    QPoint sliderTopLeft = buttonTopLeft - QPoint(0, cameraSlider->height());
    cameraSlider->move(sliderTopLeft);
}

void RaceWidget::setRaceScene()
{
    if (scene) delete scene;
    scene = new RaceScene(logic.getTrackLength(), logic.getHorseCount(), view);

    // set scene to view
    view->setScene(scene);
    // connect camera slider to scene
    connect(cameraSlider, SIGNAL(valueChanged(int)), scene, SLOT(cameraVerticalChange(int)));
    cameraSlider->setValue(CAMERA_SHIFT_Y);
}

void RaceWidget::controlButtonHandler()
{
    // if race is finished control button allows restart
    if (logic.raceFinished()) {
        // stop timer to stop the race
        timer.stop();
        // restart race logic and scene
        logic.restartRace();
        scene->restartRace();
        cameraSlider->setValue(CAMERA_SHIFT_Y);
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
    logic.nexTick();
    scene->worldUpdate(logic.getHorsePos(), logic.getCameraPos());

    // show race results if needed
    if (!logic.getResults().empty()) {
        scene->showResults(logic.getResults());
    }

    // if race is finished control button allows restart
    if (logic.raceFinished()) {
        // enable control button after the race
        controlButton->setEnabled(true);
        // control button now allows restart
        controlButton->setText("restart");
    }
}
