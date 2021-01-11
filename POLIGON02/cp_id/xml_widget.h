#ifndef XML_WIDGET_H
#define XML_WIDGET_H

#include <QFile>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlSchema>
#include <QXmlSchemaValidator>

#include "message_handler.h"
#include "xml_editor.h"
#include "xml_checker.h"

class xml_checker;
class xml_editor;

class xml_widget : public QWidget // класс виджет xml-/xsd-/xsl-документов
{
    Q_OBJECT
public:
    xml_widget(QString _file_name, QString _dir_path); // конструктор
    ~xml_widget();                                     // деструктор

    void check_exist_file();                          // проверка существования файла
    void check_well_formed();                         // проверка корректности xml-/xsd-/xsl-документа
    void check_well_formed_xsd();                     // проверка корректности xsd-схемы
    void check_valid(xml_widget * _xsd_scheme_layout); // проверка валидности xml-документа xsd-схеме, которая находится в объекте класса мененджер компановки _xsd_scheme_lo
    void set_palette_for_status_label(QString col);   // покраска надписи со статусом нужным цветом

    QFile * ret_file_xml();              // вернуть xml-/xsd-/xsl-файл
    QString ret_file_name();             // вернуть имя файла
    QString ret_full_file_name();        // вернуть полное имя файла
    int ret_check_status();              // вернуть статус
    QHBoxLayout * ret_main_lo();         // вернуть менеджер компановки приложения
    QLabel * ret_label_name();           // вернуть надпись с именем файла
    QLabel * ret_label_status();         // вернуть надпись со статусом (существование, корректность, валидность)
    QPushButton * ret_edit_button();     // вернуть кнопку Редактировать
    xml_editor * ret_editor();           // вернуть указатель на редактор xml-/xsd-/xsl-документов
    xml_checker * ret_ptr_xml_checker(); // вернуть указатель на объект, отвечающий за проверку корректности, валидности и правильности XSLT-преобразования

    void set_file_xml(QString _full_file_name);               // установить xml-/xsd-/xsl-файл
    void set_file_name(QString _file_name);                   // установить имя файла
    void set_full_file_name(QString _full_file_name);         // установить полное имя файла
    void set_check_status(int _check_status);                 // установить статус
    void set_main_lo(QHBoxLayout * _main_lo);                  // установить менеджер компановки приложения
    void set_label_name(QLabel * _label_name);                // установить надпись с именем файла
    void set_label_status(QLabel * _label_status);            // установить надпись со статусом (существование, корректность, валидность)
    void set_edit_button(QPushButton * _edit_button);         // установить кнопку Редактировать
    void set_editor(xml_editor * _editor);                    // установить указатель на редактор xml-/xsd-/xsl-документов
    void set_ptr_xml_checker(xml_checker * _ptr_xml_checker); // установить указатель на объект, отвечающий за проверку корректности, валидности и правильности XSLT-преобразования

private:
    QFile file_xml;                // файл с  xml-/xsd-/xsl-документом
    QString file_name;             // имя файла
    QString full_file_name;        // полное имя файла (путь+имя_файла)
    int check_status;              // статус (существование, корректность, валидность), 0 - хорошо

    QHBoxLayout * main_lo;         // главный менеджер компановки
    QLabel * label_name;           // надпись с именем файла
    QLabel * label_status;         // надпись со статусом (существование, корректность, валидность)
    QPushButton * edit_button;     // кнопка Редактировать

    xml_editor * editor;           // указатель на редактор xml-/xsd-/xsl-документов

    xml_checker * ptr_xml_checker; // указатель на объект, отвечающий за проверку корректности, валидности и правильности XSLT-преобразования

public slots:
    void edit_button_clicked(); // вызывается при нажатии на кнопку Редактировать
};

#endif // XML_WIDGET_H
