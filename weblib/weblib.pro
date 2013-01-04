#-------------------------------------------------
#
# Project created by QtCreator 2012-02-25T20:04:22
#
#-------------------------------------------------

QT       -= gui
QT       += network

TARGET = weblib
TEMPLATE = lib
VERSION = 0.2

DEFINES += WEBLIB_LIBRARY

SOURCES += abstractdispatcher.cpp \
    contextpathdispatcher.cpp \
    abstractwebhandler.cpp \
    errorwebhandler.cpp

HEADERS += abstractdispatcher.h\
    contextpathdispatcher.h \
    abstractwebhandler.h \
    errorwebhandler.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../httplib/release/ -lhttplib0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../httplib/debug/ -lhttplib0
else:unix: LIBS += -L$$OUT_PWD/../httplib/ -lhttplib

INCLUDEPATH += $$PWD/../httplib
DEPENDPATH += $$PWD/../httplib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logger/release/ -llogger0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logger/debug/ -llogger0
else:unix: LIBS += -L$$OUT_PWD/../logger/ -llogger

INCLUDEPATH += $$PWD/../logger
DEPENDPATH += $$PWD/../logger
