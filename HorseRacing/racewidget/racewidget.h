#ifndef RACEWIDGET_H
#define RACEWIDGET_H

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QGridLayout>
#include <QGraphicsView>
#include <QSlider>
#include <QLabel>

#include "racescene.h"

class RaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RaceWidget(float trackLength, int horseCount, QWidget *parent = 0);
    ~RaceWidget();

    void resizeEvent(QResizeEvent *event);

    void restartRace();

public slots:
    void updatePositions(const std::vector<float>& horsePosX, const float& cameraPosX);
    void showResults(const std::vector<int>& currentResults);

private:
    // widget size is 16:9, qHD
    const int widgetWidth = 960;
    const int widgetHeight = 540;
    const int sliderWidth = 30;
    const int sliderHeight = 100;

    QGridLayout *gridLayout = nullptr;
    QGraphicsView *graphicsView = nullptr;
    QSlider *cameraSlider = nullptr;
    QLabel *resultDisplay = nullptr;
    void uiSetup();
    void uiAdjust();

    RaceScene *scene = nullptr;
};

#endif // RACEWIDGET_H
