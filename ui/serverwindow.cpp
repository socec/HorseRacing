#include "serverwindow.h"
#include "ui_serverwindow.h"

#include <QDebug>

ServerWindow::ServerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWindow),
    mainWindow(static_cast<QMainWindow*>(parent))
{
    ui->setupUi(this);
    raceWindow = new RaceWidget(1000, 4, mainWindow);
    raceWindow->show();
    qDebug() << "main " << mainWindow->centralWidget();
    mainWindow->setCentralWidget(raceWindow);
    qDebug() << "main " << mainWindow->centralWidget();
}

ServerWindow::~ServerWindow()
{
    delete ui;
}
