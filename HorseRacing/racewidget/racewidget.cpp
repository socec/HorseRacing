#include "racewidget.h"

RaceWidget::RaceWidget(float trackLength, int horseCount, QWidget *parent)
    : QWidget(parent) {
    // prepare UI
    uiSetup();
    uiAdjust();

    // set scene to view
    scene = new RaceScene(trackLength, horseCount, graphicsView);
    graphicsView->setScene(scene);

    // connect camera slider to scene to adjust vertical camera position
    connect(cameraSlider, SIGNAL(valueChanged(int)), scene, SLOT(cameraVerticalChange(int)));
}

RaceWidget::~RaceWidget() {
    delete scene;
    delete resultDisplay;
    delete cameraSlider;
    delete graphicsView;
    delete gridLayout;
}

void RaceWidget::resizeEvent(QResizeEvent *event) {
    graphicsView->resize(event->size());
    uiAdjust();
}

void RaceWidget::restartRace() {
    // restart scene
    scene->restartRace();
    // reset UI
    cameraSlider->setValue(cameraSlider->maximum());
    resultDisplay->setText("");
    resultDisplay->hide();
}

void RaceWidget::updatePositions(const std::vector<float>& horsePositions,
                                 const float &cameraPosition) {
    scene->updatePositions(horsePositions, cameraPosition);
}

void RaceWidget::showResults(const std::vector<int>& currentResults) {
    // do not show results if they are empty
    if (currentResults.empty()) return;

    // hide display on the widget
    resultDisplay->hide();
    // construct display text from results vector
    QString displayText("Results:\n");
    for (unsigned int i = 0; i < currentResults.size(); i++) {
        displayText.append("    " + QString::number(i + 1) + ". ");
        // current result is track index, add 1 to create track number
        displayText.append("track " + QString::number(currentResults.at(i) + 1) + "\n");
    }
    // show results on display and widget
    resultDisplay->setText(displayText);
    resultDisplay->show();
    uiAdjust();
}

void RaceWidget::uiSetup() {
    // set the main widget
    setMinimumSize(WIDGET_WIDTH, WIDGET_HEIGHT);
    setMaximumSize(WIDGET_WIDTH, WIDGET_HEIGHT);
    setGeometry(0, 0, WIDGET_WIDTH, WIDGET_HEIGHT);

    // set grid layout
    gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(gridLayout);

    // set view
    graphicsView = new QGraphicsView(this);
    graphicsView->setMinimumSize(WIDGET_WIDTH, WIDGET_HEIGHT);
    graphicsView->setMaximumSize(WIDGET_WIDTH, WIDGET_HEIGHT);
    graphicsView->setGeometry(0, 0, WIDGET_WIDTH, WIDGET_HEIGHT);
    graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    gridLayout->addWidget(graphicsView);

    // set camera slider
    int sliderMin = 2;
    int sliderMax = 20;
    cameraSlider = new QSlider(Qt::Vertical, this);
    cameraSlider->setMinimumSize(SLIDER_WIDTH, SLIDER_HEIGHT);
    cameraSlider->setMaximumSize(SLIDER_WIDTH, SLIDER_HEIGHT);
    cameraSlider->setGeometry(0, 0, SLIDER_WIDTH, SLIDER_HEIGHT);
    cameraSlider->setMinimum(sliderMin);
    cameraSlider->setMaximum(sliderMax);
    cameraSlider->setValue(cameraSlider->maximum());
    gridLayout->addWidget(cameraSlider);

    // set result display, but don't show it until requested
    int displayFontSize = 12;
    int displayMargin = 10;
    resultDisplay = new QLabel(this);
    resultDisplay->setFont(QFont("Arial", displayFontSize, QFont::Bold));
    resultDisplay->setStyleSheet("QLabel { background-color : rgb(230, 230, 230); }");
    resultDisplay->setMargin(displayMargin);
    resultDisplay->hide();
    gridLayout->addWidget(resultDisplay);
}

void RaceWidget::uiAdjust() {
    int offset = 10;
    // get reference point
    QPoint topLeft = graphicsView->geometry().topLeft();
    // adjust elements
    cameraSlider->move(topLeft + QPoint(offset, offset));
    resultDisplay->move(topLeft + QPoint(cameraSlider->width() + offset, offset));
    resultDisplay->adjustSize();
}
