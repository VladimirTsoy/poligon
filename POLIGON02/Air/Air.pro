#-------------------------------------------------
#
# Project created by QtCreator 2015-12-17T11:34:28
#
#-------------------------------------------------

QT       -= gui
QT       += core xml

INCLUDEPATH += $$PWD/../CSCommon/include/
INCLUDEPATH += $$PWD/../OperatingEnvironment/
INCLUDEPATH += $$PWD/../my/
INCLUDEPATH += $$PWD/../point_in_zone_checker/

TARGET = Air
TEMPLATE = lib

CONFIG += dll

DESTDIR = $$PWD/../App

SOURCES += \
    TAir.cpp \
    TGeneralTrackAir.cpp \
    TMsgsFormAir.cpp \
    TTrcProcAir.cpp \
    TPrognProcAir.cpp \
    TZoneProcAir.cpp \
    NUM/DispatcherNe.cpp \
    NUM/DispatcherTable.cpp \
    NUM/GenTrack.cpp \
    NUM/Msg.cpp \
    NUM/Num.cpp \
    NUM/Task.cpp \
    NUM/TrackNum.cpp \
    NUM/TrcNum.cpp \
    $$PWD/../my/mathd.cpp \
    $$PWD/../point_in_zone_checker/point_in_zone_checker.cpp

HEADERS += \
    DefAir.h \
    EAir.h \
    HAir.h \
    HAirFAL.h \
    TAir.h \
    TGeneralTrackAir.h \
    TGenTrcSAir.h \
    TMsgsFormAir.h \
    TTrcProcAir.h \
    TPrognProcAir.h \
    TZoneProcAir.h \
    NUM/DispatcherNe.h \
    NUM/DispatcherTable.h \
    NUM/GenTrack.h \
    NUM/Msg.h \
    NUM/Num.h \
    NUM/S_E_Num.h \
    NUM/Task.h \
    NUM/TrackNum.h \
    NUM/TrcNum.h \
    $$PWD/../my/mathd.h \
    $$PWD/../point_in_zone_checker/point_in_zone_checker.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    #$$PWD/NUM/xml_num/res.qrc \
#    NUM/xml_num/res.qrc \
    NUM/xml_num/rsrses.qrc
