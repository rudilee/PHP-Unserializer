#-------------------------------------------------
#
# Project created by QtCreator 2016-01-20T15:00:28
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = phpunserializertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    phpunserializertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix:!macx: LIBS += -L$$OUT_PWD/../src/ -lphpunserializer

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../src/libphpunserializer.a
