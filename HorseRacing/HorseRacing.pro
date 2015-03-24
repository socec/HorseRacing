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
    racescene.cpp

HEADERS  += racewidget.h \
    racescene.h
