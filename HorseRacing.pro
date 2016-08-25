QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = HorseRacing.run
TEMPLATE = app

SOURCES += \
    main.cpp

HEADERS += \

RESOURCES += \
    #images.qrc

FORMS +=
