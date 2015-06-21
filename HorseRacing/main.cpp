#include <QApplication>
#include "racecontrol/racecontrol.h"

#include "network/raceserver.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QMainWindow window;
    window.show();

    RaceControl control(&window);
    control.show();

    window.setGeometry(50, 50, control.width(), control.height());
    window.updateGeometry();

    return a.exec();
}
