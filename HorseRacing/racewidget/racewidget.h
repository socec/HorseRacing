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

/**
 * @brief Widget used to display the race.
 */
class RaceWidget : public QWidget {
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Class constructor.
     * @param trackLength - Length of the race track.
     * @param horseCount - Number of horses in the race.
     * @param parent - Parent widget used for widget hierarchy.
     */
    explicit RaceWidget(float trackLength, int horseCount, QWidget *parent = 0);

    /**
     * @brief Class destructor.
     */
    ~RaceWidget();

    // inherited from QWidget
    void resizeEvent(QResizeEvent *event);

    /**
     * @brief Restarts the race displayed by the widget.
     */
    void restartRace();

public slots:
    /**
     * @brief Updates horse and camera positions for this race.
     * @param horsePositions - List of updated horse positions.
     * @param cameraPosition - Updated camera position.
     */
    void updatePositions(const std::vector<float>& horsePositions, const float& cameraPosition);

    /**
     * @brief Displays race results on the widget.
     * @param currentResults - Current race results to display.
     */
    void showResults(const std::vector<int>& currentResults);

private:
    // widget size is 16:9, qHD
    const int WIDGET_WIDTH = 960;
    const int WIDGET_HEIGHT = 540;
    // slider size
    const int SLIDER_WIDTH = 30;
    const int SLIDER_HEIGHT = 100;

    // UI elements
    QGridLayout *gridLayout = nullptr;
    QGraphicsView *graphicsView = nullptr;
    QSlider *cameraSlider = nullptr;
    QLabel *resultDisplay = nullptr;
    RaceScene *scene = nullptr;

    /**
     * @brief Sets up the UI.
     */
    void uiSetup();

    /**
     * @brief Adjusts the UI after a change.
     */
    void uiAdjust();
};

#endif // RACEWIDGET_H
