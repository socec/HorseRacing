#include <QApplication>
#include "racewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RaceWidget w;
    w.show();

    return a.exec();
}
