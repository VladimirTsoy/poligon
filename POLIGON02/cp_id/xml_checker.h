#ifndef XML_CHECKER_H
#define XML_CHECKER_H

#include <stddef.h>
#include <QXmlQuery>

#include "xml_widget.h"

class xml_widget;

class xml_checker // объект, отвечающий за проверку корректности, валидности и правильности XSLT-преобразования
{
public:
    xml_checker(xml_widget * _ptr_xml_widget,
                xml_widget * _ptr_xsd_widget,
                xml_widget * _ptr_xsl_widget,
                QString _relative_path_to_res_file,
                QString _res_file_html_name);              // конструктор
    ~xml_checker();                                        // деструктор

    xml_widget * ret_ptr_xml_widget();                     // вернуть указатель на виджет xml-документа
    xml_widget * ret_ptr_xsd_widget();                     // вернуть указатель на виджет xsd-документа
    xml_widget * ret_ptr_xsl_widget();                     // вернуть указатель на виджет xsl-документа
    QString ret_xslt_out();                                // вернуть результат XSLT-преобразования
    QString ret_relative_path_to_res_file();               // вернуть относительный путь к результирующему файлу
    QString ret_res_file_html_name();                      // вернуть имя файла с результатом XSLT-преобразования


    void set_ptr_xml_widget(xml_widget * _ptr_xml_widget); // установить указатель на виджет xml-документа
    void set_ptr_xsd_widget(xml_widget * _ptr_xsd_widget); // установить указатель на виджет xsd-документа
    void set_ptr_xsl_widget(xml_widget * _ptr_xsl_widget); // установить указатель на виджет xsl-документа
    void set_relative_path_to_res_file(QString _relative_path_to_res_file); // установить относительный путь к результирующему файлу
    void set_res_file_html_name(QString _res_file_html_name); // установить имя файла с результатом XSLT-преобразования

    void check();                                          // проверка корректности, валидности и правильности XSLT-преобразования

    void xslt_transform();                                 // XSLT-преобразование

private:
    xml_widget * ptr_xml_widget;                           // указатель на виджет xml-документа
    xml_widget * ptr_xsd_widget;                           // указатель на виджет xml-документа
    xml_widget * ptr_xsl_widget;                           // указатель на виджет xml-документа

    QString xslt_out;                                      // результат XSLT-преобразования
    QString relative_path_to_res_file;                     // относительный путь к результирующему файлу
    QString res_file_html_name;                            // имя файла с результатом XSLT-преобразования
};

#endif // XML_CHECKER_H
