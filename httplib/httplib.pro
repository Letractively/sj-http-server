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

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE6BFEA03
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = httplib.dll
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




win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logger/release/ -llogger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logger/debug/ -llogger
else:symbian: LIBS += -llogger
else:unix: LIBS += -L$$OUT_PWD/../logger/ -llogger

INCLUDEPATH += $$PWD/../logger
DEPENDPATH += $$PWD/../logger
