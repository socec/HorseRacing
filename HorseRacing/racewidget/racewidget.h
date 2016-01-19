#ifndef RACEWIDGET_H
#define RACEWIDGET_H

#include <racewidget/racescene.h>

#include <QWidget>
#include <QGraphicsView>
#include <QSlider>
#include <QLabel>

// widget size is 16:9, qHD
#define RACEWIDGET_WIDTH (960)
#define RACEWIDGET_HEIGHT (540)
// slider size
#define SLIDER_WIDTH (40)
#define SLIDER_HEIGHT (100)

/**
 * @brief Widget displaying the race.
 *
 * Public functions and slots provide an interface to visualize a race
 * that is generated using a separated race model.
 * Uses predefined resolution and size, no scaling on resize events.
 */
class RaceWidget : public QWidget
{
    // using signals and slots
    Q_OBJECT

public:
    /**
     * @brief Constructor with initial parameters.
     * @param trackLength - Length of the race track.
     * @param horseCount - Number of horses in the race.
     * @param parent - Parent widget used for widget hierarchy.
     */
    explicit RaceWidget(float trackLength, int horseCount, QWidget *parent = 0);

    // inherited from QWidget
    void resizeEvent(QResizeEvent *event);

public slots:
    /**
     * @brief Updates horse and camera positions for this race.
     * @param horsePositions - List of updated horse positions.
     * @param cameraPosition - Updated camera position.
     */
    void updatePositions(const QVector<float>& horsePositions, const float& cameraPosition);

    /**
     * @brief Displays current race results on the widget.
     * @param results - Current race results to display.
     */
    void showResults(const QVector<int>& results);

private:
    // UI elements
    QGraphicsView graphicsView;
    RaceScene graphicsScene;
    QSlider cameraSlider;
    QLabel resultDisplay;

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
