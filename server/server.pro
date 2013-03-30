#-------------------------------------------------
#
# Project created by QtCreator 2011-10-18T14:59:21
#
#-------------------------------------------------

QT += core network xml
QT -= widgets gui
VERSION = 0.3
TARGET = sj-http-server
TEMPLATE = app

SOURCES += main.cpp\
    httpserver.cpp \
    requestprocessingthread.cpp \
    requesthandler.cpp \
    handlermanager.cpp \
    handlerdata.cpp \
    httprequestimpl.cpp \
        serverutils.cpp \
    httpresponseimpl.cpp \
    configurationprovider.cpp \
    handlerconfiguration.cpp \
    mockconfigurationprovider.cpp \
    xmlconfigurationprovider.cpp

HEADERS  += \
    httpserver.h \
    requestprocessingthread.h \
    settingsconstants.h \
    requesthandler.h \
    handlermanager.h \
    handlerdata.h \
    httprequestimpl.h \
        serverutils.h \
    httpresponseimpl.h \
    configurationprovider.h \
    handlerconfiguration.h \
    mockconfigurationprovider.h \
    xmlconfigurationprovider.h

OTHER_FILES += \
    sjlog.xml \
    images.xml \
    sj-http-server.xml


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../httplib/release/ -lhttplib0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../httplib/debug/ -lhttplib0
else:unix: LIBS += -L$$PWD/../httplib/ -lhttplib

INCLUDEPATH += $$PWD/../httplib
DEPENDPATH += $$PWD/../httplib


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../weblib/release/ -lweblib0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../weblib/debug/ -lweblib0
else:unix: LIBS += -L$$OUT_PWD/../weblib/ -lweblib

INCLUDEPATH += $$PWD/../weblib
DEPENDPATH += $$PWD/../weblib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logger/release/ -llogger0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logger/debug/ -llogger0
else:unix: LIBS += -L$$OUT_PWD/../logger/ -llogger

INCLUDEPATH += $$PWD/../logger
DEPENDPATH += $$PWD/../logger
