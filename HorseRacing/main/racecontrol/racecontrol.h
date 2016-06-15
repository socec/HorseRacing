#ifndef RACECONTROL_H
#define RACECONTROL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSharedPointer>

#include <racewidget.h>
#include <servermodel.h>
#include <clientmodel.h>

// race parameters
#define TRACK_LENGTH (1000.0)
#define HORSE_COUNT (5)
// widget size is 16:9, qHD
#define WIDGET_WIDTH (960)
#define WIDGET_HEIGHT (540)
// button size
#define BUTTON_WIDTH (100)
#define BUTTON_HEIGHT (30)

/**
 * @brief Race controller responsible for connecting the race model with
 *        race view and handling user input.
 */
class RaceControl : public QWidget
{
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Default constructor.
     * @param parent - Parent object used for hierarchy.
     */
    explicit RaceControl(QWidget *parent = 0);

private:
    // UI elements
    QGridLayout gridLayout;
    QPushButton startButton;
    QPushButton serverButton;
    QPushButton clientButton;
    // model and view
    QSharedPointer<RaceModel> model;
    QSharedPointer<RaceWidget> view;

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
