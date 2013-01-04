#-------------------------------------------------
#
# Project created by QtCreator 2012-05-11T20:15:36
#
#-------------------------------------------------

QT       -= gui
QT       += xml

TARGET = logger
TEMPLATE = lib
VERSION = 0.2


DEFINES += LOGGER_LIBRARY

SOURCES += logger.cpp \
    logginglevel.cpp \
    logbuilder.cpp \
    consoleappender.cpp \
    loggerfactory.cpp \
    loggerconffileparsehandler.cpp \
    fileappender.cpp \
    fileappenderinternal.cpp \
    fileappenderinternalholder.cpp

HEADERS += logger.h\
    logginglevel.h \
    logbuilder.h \
    abstractappender.h \
    consoleappender.h \
    loggerfactory.h \
    loggerconffileparsehandler.h \
    fileappender.h \
    loggerall.h \
    fileappenderinternal.h \
    fileappenderinternalholder.h


