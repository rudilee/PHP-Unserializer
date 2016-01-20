#-------------------------------------------------
#
# Project created by QtCreator 2016-01-20T14:58:57
#
#-------------------------------------------------

QT       -= gui

TARGET = phpunserializer
TEMPLATE = lib
CONFIG += staticlib

SOURCES += phpunserializer.cpp

HEADERS += phpunserializer.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
