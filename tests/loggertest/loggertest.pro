#-------------------------------------------------
#
# Project created by QtCreator 2012-05-11T20:41:05
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_loggertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../logger \
                ../common

SOURCES += tst_loggertest.cpp \
            $$files(../../logger/*.cpp)
DEFINES += SRCDIR=\\\"$$PWD/\\\"
