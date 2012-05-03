QT       += testlib
QT       += network

QT       -= gui

TARGET = tst_httprequest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../server
INCLUDEPATH += ../../httplib
INCLUDEPATH += ../mocks

SOURCES += tst_httprequest.cpp \
          ../../server/httprequestimpl.cpp \
          $$files(../../httplib/*.cpp)

DEFINES += SRCDIR=\\\"$$PWD/\\\"
