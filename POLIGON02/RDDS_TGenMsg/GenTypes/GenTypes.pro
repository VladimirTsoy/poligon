#-------------------------------------------------
#
# Project created by QtCreator 2020-11-25T19:36:13
#
#-------------------------------------------------

QT       += xml

TARGET = GenTypes
TEMPLATE = lib
CONFIG += staticlib warn_on

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
        gentypes.cpp

HEADERS += \
        gentypes.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(../../app.pri)
include(../../gen_defs.pri)

CONFIG(debug, debug|release) {
    DESTDIR = $${PROJECT_PATH}/RDDS_TGenMsg/bin/debug
    OBJECTS_DIR = $${PROJECT_PATH}/RDDS_TGenMsg/build/debug/obj
    MOC_DIR = $${PROJECT_PATH}/RDDS_TGenMsg/build/debug/moc
    UI_DIR = $${PROJECT_PATH}/RDDS_TGenMsg/build/debug/ui
    RCC_DIR = $${PROJECT_PATH}/RDDS_TGenMsg/build/debug/rcc
} else {
    DESTDIR = $${PROJECT_PATH}/RDDS_TGenMsg/bin/release
    OBJECTS_DIR = $${PROJECT_PATH}/RDDS_TGenMsg/build/release/obj
    MOC_DIR = $${PROJECT_PATH}/RDDS_TGenMsg/build/release/moc
    UI_DIR = $${PROJECT_PATH}/RDDS_TGenMsg/build/release/ui
    RCC_DIR = $${PROJECT_PATH}/RDDS_TGenMsg/build/release/rcc
}

xmlgen.commands = $${XML_PRECOMPILER_COMMAND} $${XMLFILE} $${XMLDIR}
QMAKE_EXTRA_TARGETS += xmlgen
PRE_TARGETDEPS += xmlgen

SOURCES += $${XMLDIR}/$${XMLNAME}_DDS/src/$${XMLNAME}.cpp \
           $${XMLDIR}/$${XMLNAME}_DDS/src/$${XMLNAME}_DCPS_Pack.cpp

HEADERS += $${XMLDIR}/$${XMLNAME}_DDS/include/$${XMLNAME}.h \
           $${XMLDIR}/$${XMLNAME}_DDS/include/$${XMLNAME}_DCPS.h \
           $${XMLDIR}/$${XMLNAME}_DDS/include/$${XMLNAME}_DCPS.hpp \
           $${XMLDIR}/$${XMLNAME}_DDS/include/$${XMLNAME}_DCPS_Pack.h

QMAKE_CLEAN += $$files($${XMLDIR}/*)

DISTFILES += ../import/xml/$${XMLNAME}.xml
