#include <QApplication>
#include "racelogic/racelogic.h"
#include "racewidget/racewidget.h"

#define TRACK_LENGTH (1000.0)
#define HORSE_COUNT (5)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;
    window.show();

    RaceLogic logic(TRACK_LENGTH, HORSE_COUNT);

    RaceWidget race(logic, &window);
    race.show();

    window.setGeometry(50, 50, race.width(), race.height());
    window.updateGeometry();

    return a.exec();
}
