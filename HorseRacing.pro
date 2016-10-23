QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = HorseRacing.run
TEMPLATE = app

SOURCES += \
    main.cpp \
    ui/serverwindow.cpp \
    ui/clientwindow.cpp \
    racewidget/raceitem.cpp \
    racewidget/racescene.cpp \
    racewidget/spritesheet.cpp \
    racewidget/racewidget.cpp \
    racewidget/raceitems/fenceitem.cpp \
    racewidget/raceitems/gateitem.cpp \
    racewidget/raceitems/horseitem.cpp

HEADERS += \
    ui/serverwindow.h \
    ui/clientwindow.h \
    racewidget/raceitem.h \
    racewidget/racescene.h \
    racewidget/racewidget.h \
    racewidget/spritesheet.h \
    racewidget/raceitems/fenceitem.h \
    racewidget/raceitems/gateitem.h \
    racewidget/raceitems/horseitem.h

RESOURCES += \
    #images.qrc

FORMS += \
    ui/serverwindow.ui \
    ui/clientwindow.ui
