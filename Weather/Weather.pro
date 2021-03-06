#-------------------------------------------------
#
# Project created by QtCreator 2016-02-09T20:57:56
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Weather
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    downloadmanager.cpp \
    databasewidget.cpp \
    stationinfowidget.cpp \
    timerwidget.cpp

HEADERS  += mainwindow.h \
    stationinfo.h \
    downloadmanager.h \
    databasewidget.h \
    stationinfowidget.h \
    timerwidget.h

RESOURCES += \
    images.qrc

