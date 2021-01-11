#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T18:21:28
#
#-------------------------------------------------

QT       -= core gui
QT       -= xml

INCLUDEPATH += $$PWD/../CSCommon/include/
INCLUDEPATH += $$PWD/../OperatingEnvironment/
INCLUDEPATH += $$PWD/../my/
INCLUDEPATH += $$PWD/../point_in_zone_checker/

TARGET = Surface
TEMPLATE = lib

CONFIG += dll

DESTDIR = $$PWD/../App

SOURCES += \
    TGeneralTrackSea.cpp \
    TSea.cpp \
    TTrcProcSea.cpp \
    TPrognProcSea.cpp \
    TZoneProcSea.cpp \
    NUM/DispatcherNUM.cpp \
    TMsgsFormSea.cpp \
    $$PWD/../my/mathd.cpp \
    $$PWD/../point_in_zone_checker/point_in_zone_checker.cpp

HEADERS += \
    DefSea.h \
    ESea.h \
    HSea.h \
    HSeaFAL.h \
    TGenTrcSSea.h \
    TGeneralTrackSea.h \
    TSea.h \
    TTrcProcSea.h \
    TPrognProcSea.h \
    TZoneProcSea.h \
    NUM/DispatcherNUM.h \
    TMsgsFormSea.h \
    $$PWD/../my/mathd.h \
    $$PWD/../point_in_zone_checker/point_in_zone_checker.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
