#include "racewidget.h"

RaceWidget::RaceWidget(float trackLength, int horseCount, QWidget *parent)
    : QWidget(parent)
{
    // prepare UI
    uiSetup();
    uiAdjust();

    // set scene to view
    scene = new RaceScene(trackLength, horseCount, graphicsView);
    graphicsView->setScene(scene);
    // connect camera slider to scene
    connect(cameraSlider, SIGNAL(valueChanged(int)), scene, SLOT(cameraVerticalChange(int)));
    cameraSlider->setValue(CAMERA_SHIFT_Y);
}

RaceWidget::~RaceWidget()
{
    delete scene;
    delete resultDisplay;
    delete cameraSlider;
    delete graphicsView;
    delete gridLayout;
}

void RaceWidget::resizeEvent(QResizeEvent *event)
{
    graphicsView->resize(event->size());
    uiAdjust();
}

void RaceWidget::raceUpdate(const std::vector<float>& horsePosX, const float &cameraPosX)
{
    scene->worldUpdate(horsePosX, cameraPosX);
}

void RaceWidget::showResults(const std::vector<int>& results)
{
    // do not show results if they are empty
    if (results.empty()) return;

    resultDisplay->hide();
    // construct display text from results vector
    QString displayText("Results:\n");
    for (int i = 0; i < results.size(); i++) {
        displayText.append("    " + QString::number(i + 1) + ". ");
        displayText.append("track " + QString::number(results.at(i) + 1) + "\n");
    }
    // show results on display and widget
    resultDisplay->setText(displayText);
    resultDisplay->show();
    uiAdjust();
}

void RaceWidget::restartRace()
{
    // restart scene
    scene->restartRace();
    // reset UI
    cameraSlider->setValue(CAMERA_SHIFT_Y);
    resultDisplay->setText("");
    resultDisplay->hide();
}

void RaceWidget::uiSetup()
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

    // set camera slider
    cameraSlider = new QSlider(Qt::Vertical, this);
    cameraSlider->setMinimumSize(SLIDER_W, SLIDER_H);
    cameraSlider->setMaximumSize(SLIDER_W, SLIDER_H);
    cameraSlider->setGeometry(0, 0, SLIDER_W, SLIDER_H);
    cameraSlider->setMinimum(2);
    cameraSlider->setMaximum(CAMERA_SHIFT_Y);
    gridLayout->addWidget(cameraSlider);

    // set result display, but don't show it until requested
    resultDisplay = new QLabel(this);
    resultDisplay->setFont(QFont("Arial", 12, QFont::Bold));
    resultDisplay->setStyleSheet("QLabel { background-color : rgb(230, 230, 230); }");
    resultDisplay->setMargin(10);
    resultDisplay->hide();
    gridLayout->addWidget(resultDisplay);
}

void RaceWidget::uiAdjust()
{
    QPoint topLeft = graphicsView->geometry().topLeft();
    cameraSlider->move(topLeft + QPoint(10, 10));
    resultDisplay->move(topLeft + QPoint(cameraSlider->width() + 10, 10));
    resultDisplay->adjustSize();
}
