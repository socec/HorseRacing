#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
#include <QMainWindow>

#include <racewidget/racewidget.h>

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

private:
    Ui::ServerWindow *ui;
    QMainWindow *mainWindow;
    RaceWidget *raceWindow;
};

#endif // SERVERWINDOW_H
