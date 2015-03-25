#include "racewidget.h"

RaceWidget::RaceWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();

    raceScene = new RaceScene(500.0, 5, graphicsView);
    graphicsView->setScene(raceScene);
    connect(cameraSlider, SIGNAL(valueChanged(int)), raceScene, SLOT(cameraVerticalChange(int)));

    timer.setInterval(1000 / fps);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHandler()));
}

RaceWidget::~RaceWidget()
{
    delete gridLayout;
    delete graphicsView;
    delete controlButton;
    delete cameraSlider;
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

void RaceWidget::controlButtonHandler()
{
    // start timer to start the race
    timer.start();
}

void RaceWidget::timerHandler()
{
    static int x = 0;
    raceScene->worldUpdate(x, x);
    x += 5;
}
