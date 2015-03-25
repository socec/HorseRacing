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
        racewidget.cpp \
    racescene.cpp \
    fenceitem.cpp \
    raceitem.cpp \
    spritesheet.cpp \
    horseitem.cpp \
    racelogic.cpp

HEADERS  += racewidget.h \
    racescene.h \
    fenceitem.h \
    raceitem.h \
    spritesheet.h \
    horseitem.h \
    racelogic.h

RESOURCES += \
    images.qrc
