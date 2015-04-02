#ifndef RACECONTROL_H
#define RACECONTROL_H

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>

#include "racelogic/racelogic.h"
#include "racewidget/racewidget.h"

#define TRACK_LENGTH (1000.0)
#define HORSE_COUNT (5)
#define FPS (25)

// widget size is 16:9, qHD
#define WIDGET_W (960)
#define WIDGET_H (540)

class RaceControl : public QWidget
{
    Q_OBJECT

public:
    explicit RaceControl(QWidget *parent = 0);
    ~RaceControl();

private:
    QGridLayout *gridLayout = nullptr;
    QPushButton *startButton = nullptr;
    void uiSetup();

    RaceLogic *logic = nullptr;
    RaceWidget *view = nullptr;

    QTimer timer;
    int fps = FPS;
    int timerCounter = 0;

    enum RaceState {R_INIT, R_START, R_RUN, R_FINISH};
    RaceState state = R_INIT;

private slots:
    void startButtonHandler();
    void timerHandler();
};

#endif // RACECONTROL_H
