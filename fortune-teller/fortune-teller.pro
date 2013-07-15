#-------------------------------------------------
#
# Project created by QtCreator 2011-12-03T21:22:05
#
#-------------------------------------------------

QT       -= gui
QT       += network

TARGET = fortune-teller
TEMPLATE = lib
VERSION = 0.3

CONFIG += plugin

QMAKE_CXXFLAGS += -std=c++0x


SOURCES += fortuneteller.cpp

HEADERS += fortuneteller.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../httplib/release/ -lhttplib0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../httplib/debug/ -lhttplib0
else:unix: LIBS += -L$$PWD/../httplib/ -lhttplib

INCLUDEPATH += $$PWD/../httplib
DEPENDPATH += $$PWD/../httplib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logger/release/ -llogger0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logger/debug/ -llogger0
else:unix: LIBS += -L$$OUT_PWD/../logger/ -llogger

INCLUDEPATH += $$PWD/../logger
DEPENDPATH += $$PWD/../logger

OTHER_FILES += \
    fortune-teller.json
