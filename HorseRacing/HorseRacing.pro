#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T17:56:12
#
#-------------------------------------------------

QT       += core gui network

# adding custom flags
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HorseRacing.run
TEMPLATE = app


SOURCES += main.cpp\
    racewidget/fenceitem.cpp \
    racewidget/gateitem.cpp \
    racewidget/horseitem.cpp \
    racewidget/raceitem.cpp \
    racewidget/racescene.cpp \
    racewidget/spritesheet.cpp \
    racewidget/racewidget.cpp \
    racecontrol/racecontrol.cpp \
    network/raceserver.cpp \
    network/raceclient.cpp \
    network/racemessage.cpp \
    racemodel/racemodel.cpp \
    racemodel/servermodel.cpp \
    racemodel/clientmodel.cpp

HEADERS  += \
    racewidget/fenceitem.h \
    racewidget/gateitem.h \
    racewidget/horseitem.h \
    racewidget/raceitem.h \
    racewidget/racescene.h \
    racewidget/racewidget.h \
    racewidget/spritesheet.h \
    racecontrol/racecontrol.h \
    network/raceserver.h \
    network/raceclient.h \
    network/racemessage.h \
    racemodel/racemodel.h \
    racemodel/servermodel.h \
    racemodel/clientmodel.h

RESOURCES += \
    images.qrc
