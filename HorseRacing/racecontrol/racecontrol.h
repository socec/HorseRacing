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

/**
 * @brief Race controller responsible for connecting the race model with
 *        race view and handling user input.
 */
class RaceControl : public QWidget {
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Class constructor.
     * @param parent - Parent object used for hierarchy.
     */
    explicit RaceControl(QWidget *parent = 0);

    /**
     * @brief Class destructor.
     */
    ~RaceControl();

private:
    // UI elements
    QGridLayout *gridLayout = nullptr;
    QPushButton *startButton = nullptr;
    QPushButton *serverButton = nullptr;
    QPushButton *clientButton = nullptr;
    // model and view
    RaceModel *model = nullptr;
    RaceWidget *view = nullptr;

    /**
     * @brief Sets up the UI.
     */
    void uiSetup();

    /**
     * @brief Initializes the race view.
     */
    void initRaceView();

private slots:
    void startButtonHandler();
    void serverButtonHandler();
    void clientButtonHandler();
    void modelHandler();
};

#endif // RACECONTROL_H
