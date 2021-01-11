#-------------------------------------------------
#
# Project created by QtCreator 2019-05-22T16:07:25
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simply_scheduller
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    ../point_in_zone_checker/point_in_zone_checker.cpp \
    ../input_file_parser/input_file_checker.cpp \
    ../input_file_parser/input_file_parser.cpp

HEADERS += \
    ../point_in_zone_checker/point_in_zone_checker.h \
    ../input_file_parser/input_file_checker.h \
    ../input_file_parser/input_file_parser.h \
    ../common_struct/common_struct.h
