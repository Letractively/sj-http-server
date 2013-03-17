#-------------------------------------------------
#
# Project created by QtCreator 2012-02-25T19:22:05
#
#-------------------------------------------------

QT       += network

TARGET = image-gallery
TEMPLATE = lib
VERSION = 0.3
CONFIG += plugin

HEADERS += \
    imagegallery.h \
    mainpagewebhandler.h \
    uploadwebhandler.h \
    imagegalleryconstants.h \
    imageviewwebhandler.h \
    imagemetadata.h \
    imagemetadataprovider.h \
    imagemetadatamemoryprovider.h \
    imagemetadataxmlprovider.h

SOURCES += \
    imagegallery.cpp \
    mainpagewebhandler.cpp \
    uploadwebhandler.cpp \
    imageviewwebhandler.cpp \
    imagemetadata.cpp \
    imagemetadataprovider.cpp \
    imagemetadatamemoryprovider.cpp \
    imagemetadataxmlprovider.cpp


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

OTHER_FILES += \
    image-gallery.json
