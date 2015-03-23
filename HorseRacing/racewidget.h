#ifndef RACEWIDGET_H
#define RACEWIDGET_H

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QGridLayout>
#include <QGraphicsView>
#include <QPushButton>
#include <QSlider>

// widget size is 16:9, qHD
#define WIDGET_W (960)
#define WIDGET_H (540)

#define VIEW_W (WIDGET_W)
#define VIEW_H (WIDGET_H)

#define BUTTON_W (100)
#define BUTTON_H (30)
#define SLIDER_W (30)
#define SLIDER_H (100)

class RaceWidget : public QWidget
{
    Q_OBJECT

public:
    RaceWidget(QWidget *parent = 0);
    ~RaceWidget();

    void resizeEvent(QResizeEvent *event);

private:
    // UI elements
    QGridLayout *gridLayout = nullptr;
    QGraphicsView *graphicsView = nullptr;
    QPushButton *controlButton = nullptr;
    QSlider *cameraSlider = nullptr;
    void setupUi();
    void adjustUiControls();

private slots:
    void controlButtonHandler();
};

#endif // RACEWIDGET_H
