#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T17:56:12
#
#-------------------------------------------------

QT       += core gui

# adding custom flags
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HorseRacing
TEMPLATE = app


SOURCES += main.cpp\
    racewidget/fenceitem.cpp \
    racewidget/gateitem.cpp \
    racewidget/horseitem.cpp \
    racewidget/raceitem.cpp \
    racewidget/racescene.cpp \
    racewidget/spritesheet.cpp \
    racewidget/racewidget.cpp \
    racelogic/racelogic.cpp

HEADERS  += \
    racewidget/fenceitem.h \
    racewidget/gateitem.h \
    racewidget/horseitem.h \
    racewidget/raceitem.h \
    racewidget/racescene.h \
    racewidget/racewidget.h \
    racewidget/spritesheet.h \
    racelogic/racelogic.h

RESOURCES += \
    images.qrc
