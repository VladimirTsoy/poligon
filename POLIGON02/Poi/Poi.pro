#-------------------------------------------------
#
# Project created by QtCreator 2015-11-24T16:19:35
#
#-------------------------------------------------

QT       += core
QT       -= gui

INCLUDEPATH += $$PWD/../CSCommon/include/

TARGET = Poi
TEMPLATE = lib

CONFIG += dll

DESTDIR = $$PWD/../App

SOURCES += Poi.cpp

HEADERS  += Poi.h \
    $$PWD/../CSCommon/include/_IMIT_.h \
    $$PWD/../CSCommon/include/U_PTPV_.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
