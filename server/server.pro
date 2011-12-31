#-------------------------------------------------
#
# Project created by QtCreator 2011-10-18T14:59:21
#
#-------------------------------------------------

QT       += core gui network

TARGET = sj-http-server
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    logger.cpp \
    imageserver.cpp \
    requestprocessingthread.cpp \
    settingsdialog.cpp \
    requesthandler.cpp \
    handlermanager.cpp \
    handlerdata.cpp

HEADERS  += maindialog.h \
    logger.h \
    imageserver.h \
    requestprocessingthread.h \
    settingsconstants.h \
    settingsdialog.h \
    requesthandler.h \
    handlermanager.h \
    handlerdata.h

FORMS    += maindialog.ui

RESOURCES +=


symbian: LIBS += -lhttplib
else:unix|win32: LIBS += -L$$PWD/../httplib/ -lhttplib

INCLUDEPATH += $$PWD/../httplib
DEPENDPATH += $$PWD/../httplib






