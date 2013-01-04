#-------------------------------------------------
#
# Project created by QtCreator 2011-12-03T20:43:17
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = httplib
TEMPLATE = lib
VERSION = 0.2

DEFINES += HTTPLIB_LIBRARY

SOURCES +=\
        httpheader.cpp\
        httprequestbinaryfile.cpp\
    settingsitem.cpp

HEADERS += abstractrequesthandler.h\
        httpheader.h\
        httprequest.h\
        httprequestbinaryfile.h\
        httpresponse.h\
    settingsitem.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logger/release/ -llogger0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logger/debug/ -llogger0
else:unix: LIBS += -L$$OUT_PWD/../logger/ -llogger

INCLUDEPATH += $$PWD/../logger
DEPENDPATH += $$PWD/../logger
