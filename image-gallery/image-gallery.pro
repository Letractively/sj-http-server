#-------------------------------------------------
#
# Project created by QtCreator 2012-02-25T19:22:05
#
#-------------------------------------------------

QT       += network

TARGET = image-gallery
TEMPLATE = lib
CONFIG += plugin


HEADERS += \
    imagegallery.h \
    mainpagewebhandler.h

SOURCES += \
    imagegallery.cpp \
    mainpagewebhandler.cpp



symbian {
# Load predefined include paths (e.g. QT_PLUGINS_BASE_DIR) to be used in the pro-files
    load(data_caging_paths)
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE12CB09F
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    pluginDeploy.sources = image-gallery.dll
    pluginDeploy.path = $$QT_PLUGINS_BASE_DIR/image-gallery
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


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../weblib/release/ -lweblib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../weblib/debug/ -lweblib
else:symbian: LIBS += -lweblib
else:unix: LIBS += -L$$OUT_PWD/../weblib/ -lweblib

INCLUDEPATH += $$PWD/../httplib
DEPENDPATH += $$PWD/../httplib

INCLUDEPATH += $$PWD/../weblib
DEPENDPATH += $$PWD/../weblib
