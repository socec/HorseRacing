#ifndef RACECONTROL_H
#define RACECONTROL_H

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include "racewidget/racewidget.h"
#include "racemodel/localracemodel.h"

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

    LocalRaceModel *model = nullptr;
    RaceWidget *view = nullptr;

private slots:
    void startButtonHandler();
    void modelHandler();
};

#endif // RACECONTROL_H
