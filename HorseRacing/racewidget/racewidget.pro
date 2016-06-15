QT += core gui widgets

TEMPLATE = lib
CONFIG += static create_prl

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += \
    raceitems \

SOURCES += \
    raceitem.cpp \
    racescene.cpp \
    racewidget.cpp \
    spritesheet.cpp \
    raceitems/fenceitem.cpp \
    raceitems/gateitem.cpp \
    raceitems/horseitem.cpp \

HEADERS += \
    raceitem.h \
    racescene.h \
    racewidget.h \
    spritesheet.h \
    raceitems/fenceitem.h \
    raceitems/gateitem.h \
    raceitems/horseitem.h \

RESOURCES += \
    images.qrc \

