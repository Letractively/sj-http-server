#-------------------------------------------------
#
# Project created by QtCreator 2011-12-03T20:43:17
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = httplib
TEMPLATE = lib
VERSION = 0.3

DEFINES += HTTPLIB_LIBRARY

QMAKE_CXXFLAGS += -std=c++0x


SOURCES += abstractrequesthandler.cpp\
        httpheader.cpp\
        httprequestbinaryfile.cpp

HEADERS += abstractrequesthandler.h\
        httpheader.h\
        httprequest.h\
        httprequestbinaryfile.h\
        httpresponse.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logger/release/ -llogger0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logger/debug/ -llogger0
else:unix: LIBS += -L$$OUT_PWD/../logger/ -llogger

INCLUDEPATH += $$PWD/../logger
DEPENDPATH += $$PWD/../logger
