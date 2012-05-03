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

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE6BBCC87
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = weblib.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../httplib/release/ -lhttplib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../httplib/debug/ -lhttplib
else:symbian: LIBS += -lhttplib
else:unix: LIBS += -L$$OUT_PWD/../httplib/ -lhttplib

INCLUDEPATH += $$PWD/../httplib
DEPENDPATH += $$PWD/../httplib
