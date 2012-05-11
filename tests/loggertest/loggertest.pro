#-------------------------------------------------
#
# Project created by QtCreator 2012-05-11T20:41:05
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_loggertesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../logger \
                ../common

SOURCES += tst_loggertesttest.cpp \
            $$files(../../logger/*.cpp)
DEFINES += SRCDIR=\\\"$$PWD/\\\"
