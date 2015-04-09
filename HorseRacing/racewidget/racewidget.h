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

// widget size is 16:9, qHD
#define WIDGET_W (960)
#define WIDGET_H (540)

#define VIEW_W (WIDGET_W)
#define VIEW_H (WIDGET_H)

#define SLIDER_W (30)
#define SLIDER_H (100)

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
    QGridLayout *gridLayout = nullptr;
    QGraphicsView *graphicsView = nullptr;
    QSlider *cameraSlider = nullptr;
    QLabel *resultDisplay = nullptr;
    void uiSetup();
    void uiAdjust();

    RaceScene *scene = nullptr;
};

#endif // RACEWIDGET_H
