#-------------------------------------------------
#
# Project created by QtCreator 2016-02-11T16:10:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui_metronome
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pa_metronome.cpp

HEADERS  += mainwindow.h \
    pa_metronome.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -L$$PWD/portaudio-bin/ -lportaudio_x86

INCLUDEPATH += $$PWD/portaudio-bin
DEPENDPATH += $$PWD/portaudio-bin

CONFIG += c++11

DISTFILES +=
