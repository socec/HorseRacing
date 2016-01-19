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
    racemodel/clientmodel.cpp \
    racewidget/raceitems/fenceitem.cpp \
    racewidget/raceitems/gateitem.cpp \
    racewidget/raceitems/horseitem.cpp

HEADERS  += \
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
    racemodel/clientmodel.h \
    racewidget/raceitems/fenceitem.h \
    racewidget/raceitems/gateitem.h \
    racewidget/raceitems/horseitem.h

RESOURCES += \
    images.qrc
