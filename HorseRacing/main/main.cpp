#include <QApplication>
#include <QMainWindow>

#include <racecontrol.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QMainWindow window;
    window.show();

    RaceControl control(&window);
    control.show();

    // make RaceControl the central widget to handle resize events
    window.setCentralWidget(&control);
    // set initial window size
    window.setGeometry(50, 50, control.width(), control.height());
    window.updateGeometry();

    return a.exec();
}
