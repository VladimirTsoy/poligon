#ifndef XML_XSD_XSL_FRAME_H
#define XML_XSD_XSL_FRAME_H

#include <QFrame>
#include <QWidget>
#include <QHBoxLayout>
#include <QString>
#include <QPushButton>
#include <QDesktopServices>
#include <QFile>
#include <QFileInfo>

#include "xml_widget.h"
#include "xml_checker.h"

class xml_checker;

class xml_xsd_xsl_frame : public QFrame // фрейм xml-/xsd-/xsl-документов
{
    Q_OBJECT

public:
    xml_xsd_xsl_frame(QString _full_dir_path_xml, QString _file_xml_name,
                      QString _full_dir_path_xsd, QString _file_xsd_name,
                      QString _full_dir_path_xsl, QString _file_xsl_name,
                      QString _full_dir_path_html,
                      QHBoxLayout * _xml_xsd_xsl_lo); // конструктор
    ~xml_xsd_xsl_frame();                                  // деструктор

    // перезагрузка xml-файла
    void reload_xml_file();

    QVBoxLayout * ret_main_lo();         // вернуть главный менеджер компановки
    xml_widget * ret_ptr_xml_widget();   // вернуть виджет xml-документа
    xml_widget * ret_ptr_xsd_widget();   // вернуть виджет xsd-документа
    xml_widget * ret_ptr_xsl_widget();   // вернуть виджет xsl-документа
    QPushButton * ret_xslt_button();     // вернуть кнопку Показать результат XSLT-преобразования
    xml_checker * ret_ptr_xml_checker(); // вернуть указатель на объект, отвечающий за проверку корректности, валидности и правильности XSLT-преобразования
    QHBoxLayout * ret_xml_xsd_xsl_lo();  // вернуть менеджер компановки фрейма xml-, xsd- и xsl-документов

    void set_main_lo(QVBoxLayout * _main_lo);                 // установить главный менеджер компановки
    void set_ptr_xml_widget(xml_widget * _ptr_xml_widget);    // установить виджет xml-документа
    void set_ptr_xsd_widget(xml_widget * _ptr_xsd_widget);    // установить виджет xsd-документа
    void set_ptr_xsl_widget(xml_widget * _ptr_xsl_widget);    // установить виджет xsl-документа
    void set_xslt_button(QPushButton * _xslt_button);         // установить кнопку Показать результат XSLT-преобразования
    void set_ptr_xml_checker(xml_checker * _ptr_xml_checker); // установить указатель на объект, отвечающий за проверку корректности, валидности и правильности XSLT-преобразования
    void set_xml_xsd_xsl_lo(QHBoxLayout * _xml_xsd_xsl_lo);   // установить менеджер компановки фрейма xml-, xsd- и xsl-документов

private:
    QVBoxLayout * main_lo;         // главный менеджер компановки

    xml_widget * ptr_xml_widget;   // виджет xml-документа
    xml_widget * ptr_xsd_widget;   // виджет xsd-документа
    xml_widget * ptr_xsl_widget;   // виджет xsl-документа

    QPushButton * xslt_button;     // кнопка Показать результат XSLT-преобразования

    xml_checker * ptr_xml_checker; // указатель на объект, отвечающий за проверку корректности, валидности и правильности XSLT-преобразования

    QHBoxLayout * xml_xsd_xsl_lo;  // менеджер компановки фрейма xml-, xsd- и xsl-документов

public slots:
    void xslt_button_click();    // вызывается при нажатии на кнопку Показать результат XSLT-преобразования
    void reload_xml_file_slot(); // вызывается при нажатии на кнопку Сохранить таблицу в файл
};

#endif // XML_XSD_XSL_FRAME_H
