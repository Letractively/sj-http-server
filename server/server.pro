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
    httpserver.cpp \
    requestprocessingthread.cpp \
    settingsdialog.cpp \
    requesthandler.cpp \
    handlermanager.cpp \
    handlerdata.cpp \
    handlersdialog.cpp \
    settingwidgetsfactory.cpp \
    httprequestimpl.cpp

HEADERS  += maindialog.h \
    logger.h \
    httpserver.h \
    requestprocessingthread.h \
    settingsconstants.h \
    settingsdialog.h \
    requesthandler.h \
    handlermanager.h \
    handlerdata.h \
    handlersdialog.h \
    settingwidgetsfactory.h \
    httprequestimpl.h

FORMS    += maindialog.ui

RESOURCES +=


symbian: LIBS += -lhttplib
else:unix|win32: LIBS += -L$$PWD/../httplib/ -lhttplib

INCLUDEPATH += $$PWD/../httplib
DEPENDPATH += $$PWD/../httplib



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../weblib/release/ -lweblib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../weblib/debug/ -lweblib
else:symbian: LIBS += -lweblib
else:unix: LIBS += -L$$OUT_PWD/../weblib/ -lweblib

INCLUDEPATH += $$PWD/../weblib
DEPENDPATH += $$PWD/../weblib
