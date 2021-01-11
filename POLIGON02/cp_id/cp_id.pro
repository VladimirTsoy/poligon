#-------------------------------------------------
#
# Project created by QtCreator 2018-07-06T11:40:32
#
#-------------------------------------------------

QT       += core \
            gui \
            xml \
            xmlpatterns \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cp_id
TEMPLATE = app

INCLUDEPATH += char_sens_cpp_h \
               sens_site_cpp_h \
               etalon_cpp_h \
               maneuver_cpp_h \
               zone_cpp_h \
               zone_point_cpp_h \

SOURCES += \
    main.cpp \
    message_handler.cpp \
    xml_checker.cpp \
    xml_editor.cpp \
    xml_widget.cpp \
    xml_xsd_xsl_frame.cpp \
    xmlsyntaxhighlighter.cpp \
    cell_data.cpp \
    cell_view_l_e.cpp \
    cell_view_c_b.cpp \
    char_sens_cpp_h/char_sens_convertor.cpp \
    char_sens_cpp_h/char_sens_form.cpp \
    char_sens_cpp_h/char_sens_row_data.cpp \
    char_sens_cpp_h/char_sens_row_view.cpp \
    char_sens_cpp_h/char_sens_table_data.cpp \
    char_sens_cpp_h/char_sens_table_view.cpp \
    sens_site_cpp_h/sens_site_convertor.cpp \
    sens_site_cpp_h/sens_site_form.cpp \
    sens_site_cpp_h/sens_site_row_data.cpp \
    sens_site_cpp_h/sens_site_row_view.cpp \
    sens_site_cpp_h/sens_site_table_data.cpp \
    sens_site_cpp_h/sens_site_table_view.cpp \
    etalon_cpp_h/etalon_convertor.cpp \
    etalon_cpp_h/etalon_form.cpp \
    etalon_cpp_h/etalon_row_data.cpp \
    etalon_cpp_h/etalon_row_view.cpp \
    etalon_cpp_h/etalon_table_data.cpp \
    etalon_cpp_h/etalon_table_view.cpp \
    maneuver_cpp_h/maneuver_row_data.cpp \
    maneuver_cpp_h/maneuver_row_view.cpp \
    maneuver_cpp_h/maneuver_form.cpp \
    zone_cpp_h/zone_convertor.cpp \
    zone_cpp_h/zone_form.cpp \
    zone_cpp_h/zone_row_data.cpp \
    zone_cpp_h/zone_row_view.cpp \
    zone_cpp_h/zone_table_data.cpp \
    zone_cpp_h/zone_table_view.cpp \
    zone_cpp_h/zone_painter.cpp \
    zone_point_cpp_h/zone_point_row_data.cpp \
    zone_point_cpp_h/zone_point_row_view.cpp \

HEADERS += \
    message_handler.h \
    xml_checker.h \
    xml_editor.h \
    xml_widget.h \
    xml_xsd_xsl_frame.h \
    xmlsyntaxhighlighter.h \
    cell_data.h \
    cell_view_l_e.h \
    cell_view_c_b.h \
    char_sens_cpp_h/char_sens_convertor.h \
    char_sens_cpp_h/char_sens_form.h \
    char_sens_cpp_h/char_sens_row_data.h \
    char_sens_cpp_h/char_sens_row_view.h \
    char_sens_cpp_h/char_sens_table_data.h \
    char_sens_cpp_h/char_sens_table_view.h \
    sens_site_cpp_h/sens_site_convertor.h \
    sens_site_cpp_h/sens_site_form.h \
    sens_site_cpp_h/sens_site_row_data.h \
    sens_site_cpp_h/sens_site_row_view.h \
    sens_site_cpp_h/sens_site_table_data.h \
    sens_site_cpp_h/sens_site_table_view.h \
    etalon_cpp_h/etalon_convertor.h \
    etalon_cpp_h/etalon_form.h \
    etalon_cpp_h/etalon_row_data.h \
    etalon_cpp_h/etalon_row_view.h \
    etalon_cpp_h/etalon_table_data.h \
    etalon_cpp_h/etalon_table_view.h \
    maneuver_cpp_h/maneuver_row_data.h \
    maneuver_cpp_h/maneuver_row_view.h \
    maneuver_cpp_h/maneuver_form.h \
    zone_cpp_h/zone_convertor.h \
    zone_cpp_h/zone_form.h \
    zone_cpp_h/zone_row_data.h \
    zone_cpp_h/zone_row_view.h \
    zone_cpp_h/zone_table_data.h \
    zone_cpp_h/zone_table_view.h \
    zone_cpp_h/zone_painter.h \
    zone_point_cpp_h/zone_point_row_data.h \
    zone_point_cpp_h/zone_point_row_view.h \

