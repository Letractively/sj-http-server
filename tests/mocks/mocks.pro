QT       += testlib
QT       += network

QT       -= gui

TARGET = tst_mocks
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app

HEADERS += \
    tcpsocketmock.h

SOURCES += \
    tst_mocks.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
