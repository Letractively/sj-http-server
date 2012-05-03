QT       += testlib
QT       += network

QT       -= gui

TARGET = tst_mocks
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
    tcpsocketmock.h

SOURCES += \
    tst_mocks.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
