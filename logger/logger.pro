#-------------------------------------------------
#
# Project created by QtCreator 2012-05-11T20:15:36
#
#-------------------------------------------------

QT       -= gui
QT       += xml

TARGET = logger
TEMPLATE = lib

DEFINES += LOGGER_LIBRARY

SOURCES += logger.cpp \
    logginglevel.cpp \
    logbuilder.cpp \
    consoleappender.cpp \
    loggerfactory.cpp \
    loggerconffileparsehandler.cpp \
    fileappender.cpp

HEADERS += logger.h\
    logginglevel.h \
    logbuilder.h \
    abstractappender.h \
    consoleappender.h \
    loggerfactory.h \
    loggerconffileparsehandler.h \
    fileappender.h \
    loggerall.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE6796C09
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = logger.dll
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
