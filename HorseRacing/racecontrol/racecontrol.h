#ifndef RACECONTROL_H
#define RACECONTROL_H

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include "racewidget/racewidget.h"
#include "racemodel/serverracemodel.h"
#include "racemodel/clientracemodel.h"

#define TRACK_LENGTH (1000.0)
#define HORSE_COUNT (5)

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
    QPushButton *serverButton = nullptr;
    QPushButton *clientButton = nullptr;
    void uiSetup();

    RaceModel *model = nullptr;
    RaceWidget *view = nullptr;
    void initRaceView();

private slots:
    void startButtonHandler();
    void serverButtonHandler();
    void clientButtonHandler();
    void modelHandler();
};

#endif // RACECONTROL_H