#-------------------------------------------------
#
# Project created by QtCreator 2012-05-11T13:47:37
#
#-------------------------------------------------

QT       -= core gui

TARGET = common
TEMPLATE = lib

DEFINES += COMMON_LIBRARY
QMAKE_CXXFLAGS += -std=c++0x


SOURCES +=

HEADERS += testcommon.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEE5FFFB2
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = common.dll
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
