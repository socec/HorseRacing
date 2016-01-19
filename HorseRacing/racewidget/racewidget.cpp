#include "racewidget.h"

RaceWidget::RaceWidget(float trackLength, int horseCount, QWidget *parent)
    : QWidget(parent),
      graphicsView(this),
      graphicsScene(&graphicsView),
      cameraSlider(Qt::Vertical, this),
      resultDisplay(this)
{
    // prepare UI
    uiSetup();

    // build scene
    graphicsScene.build(graphicsView.geometry().size(), trackLength, horseCount);

    // connect camera slider to scene to adjust vertical camera position
    connect(&cameraSlider, SIGNAL(valueChanged(int)),
            &graphicsScene, SLOT(cameraVerticalChange(int)));
}

void RaceWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    // resizing is ignored, but UI needs to be adjusted
    uiAdjust();
}

void RaceWidget::updatePositions(const QVector<float>& horsePositions,
                                 const float& cameraPosition)
{
    graphicsScene.updatePositions(horsePositions, cameraPosition);
}

void RaceWidget::showResults(const QVector<int>& results)
{
    // do not show results if they are empty
    if (results.empty()) return;

    // hide display on the widget
    resultDisplay.hide();

    // construct display text from results vector
    QString displayText("Results:\n");
    for (int i = 0; i < results.size(); i++)
    {
        QString position = QString::number(i + 1);
        QString name = QString("lane %1").arg(results.at(i));
        QString displayLine = QString("    %1. %2\n").arg(position).arg(name);
        displayText.append(displayLine);
    }

    // show results on display and widget
    resultDisplay.setText(displayText);
    resultDisplay.show();

    // adjust UI after update
    uiAdjust();
}

void RaceWidget::uiSetup()
{
    // set the main widget, no resize to keep predefined resolution
    setMinimumSize(RACEWIDGET_WIDTH, RACEWIDGET_HEIGHT);
    setMaximumSize(RACEWIDGET_WIDTH, RACEWIDGET_HEIGHT);

    // set view
    graphicsView.setMinimumSize(RACEWIDGET_WIDTH, RACEWIDGET_HEIGHT);
    graphicsView.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    graphicsView.setScene(&graphicsScene);

    // set camera slider
    int sliderMin = 2;
    int sliderMax = 20;
    cameraSlider.setMinimumSize(SLIDER_WIDTH, SLIDER_HEIGHT);
    cameraSlider.setMinimum(sliderMin);
    cameraSlider.setMaximum(sliderMax);
    cameraSlider.setValue(cameraSlider.maximum());

    // set result display, but don't show it until requested
    int displayFontSize = 12;
    int displayMargin = 10;
    resultDisplay.setFont(QFont("Arial", displayFontSize, QFont::Bold));
    resultDisplay.setStyleSheet("QLabel { background-color : rgb(230, 230, 230); }");
    resultDisplay.setMargin(displayMargin);
    resultDisplay.hide();

    // initial UI adjustment when all items are added
    uiAdjust();
}

void RaceWidget::uiAdjust()
{
    // tip: coordinates grow from left to right, top to bottom

    // define offset
    int offset = 10;
    // get reference point
    QPoint topLeft = graphicsView.geometry().topLeft();

    // adjust elements
    cameraSlider.move(topLeft + QPoint(offset, offset));
    resultDisplay.move(topLeft + QPoint(cameraSlider.width() + offset, offset));
    resultDisplay.adjustSize();
}
