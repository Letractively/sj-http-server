#-------------------------------------------------
#
# Project created by QtCreator 2011-12-03T21:22:05
#
#-------------------------------------------------

QT       += network

TARGET = fortune-teller
TEMPLATE = lib
CONFIG += plugin


SOURCES += fortuneteller.cpp

HEADERS += fortuneteller.h
symbian {
# Load predefined include paths (e.g. QT_PLUGINS_BASE_DIR) to be used in the pro-files
    load(data_caging_paths)
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE12CB09F
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    pluginDeploy.sources = fortune-teller.dll
    pluginDeploy.path = $$QT_PLUGINS_BASE_DIR/fortune-teller
    DEPLOYMENT += pluginDeploy
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../httplib/ -lhttplib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../httplib/ -lhttplib
else:symbian: LIBS += -lhttplib
else:unix: LIBS += -L$$PWD/../httplib/ -lhttplib

INCLUDEPATH += $$PWD/../httplib
DEPENDPATH += $$PWD/../httplib
