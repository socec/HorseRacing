#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QMainWindow window;

    window.show();

    return a.exec();
}

