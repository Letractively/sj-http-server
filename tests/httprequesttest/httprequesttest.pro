QT       += testlib
QT       += network
QT       += xml

QT       -= gui

TARGET = tst_httprequest
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app

INCLUDEPATH += ../../server
INCLUDEPATH += ../../httplib
INCLUDEPATH += ../../logger
INCLUDEPATH += ../mocks
INCLUDEPATH += ../common

SOURCES += tst_httprequest.cpp \
          ../../server/httprequestimpl.cpp \
          ../../server/serverutils.cpp \
          $$files(../../httplib/*.cpp) \
          $$files(../../logger/*.cpp)

DEFINES += SRCDIR=\\\"$$PWD/\\\"
