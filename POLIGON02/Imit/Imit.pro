#-------------------------------------------------
#
# Project created by QtCreator 2015-09-11T15:15:27
#
#-------------------------------------------------

QT       -= gui
QT       += core xml

INCLUDEPATH += $$PWD/../CSCommon/include/

TARGET = Imit
TEMPLATE = lib

CONFIG += dll

DESTDIR = $$PWD/../App

SOURCES += \
    TImit.cpp \
    Sens.cpp \
    Init.cpp

HEADERS += \
    DefImit.h \
    HImit.h \
    TImit.h \
    Sens.h \
    Init.h \
    $$PWD/../CSCommon/include/_IMIT_.h \
    $$PWD/../CSCommon/include/U.h

RESOURCES += \
    $$PWD/xml/res.qrc

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
