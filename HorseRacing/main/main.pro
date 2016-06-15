QT += core gui widgets network

TEMPLATE = app
CONFIG += link_prl

TARGET = HorseRacing.run

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += \
    ../racewidget \
    racecontrol \
    racemodel \
    racemodel/network \

LIBS += \
    -L../racewidget -lracewidget \

SOURCES += \
    main.cpp \
    racecontrol/racecontrol.cpp \
    racemodel/clientmodel.cpp \
    racemodel/racemodel.cpp \
    racemodel/servermodel.cpp \
    racemodel/network/raceclient.cpp \
    racemodel/network/racemessage.cpp \
    racemodel/network/raceserver.cpp \

HEADERS += \
    racecontrol/racecontrol.h \
    racemodel/clientmodel.h \
    racemodel/racemodel.h \
    racemodel/servermodel.h \
    racemodel/network/raceclient.h \
    racemodel/network/racemessage.h \
    racemodel/network/raceserver.h \
