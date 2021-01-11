#ifndef INPUT_FILE_CHECKER_H
#define INPUT_FILE_CHECKER_H

#include <stddef.h>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlSchema>
#include <QXmlSchemaValidator>

// класс обеспечивает проверку существования xml- и xsd-файлов,
// прав доступа к ним, корретность и валидность файлов
class input_file_checker
{
public:
    // конструктор
    input_file_checker();

    // деструктор
    ~input_file_checker();

    // основная функция
    void main_func(QString _xml_full_file_name,
                   QString _xsd_full_file_name);

    // проверка файла в части существования, прав доступа и корректности (одинакова и для xml- и для xsd-файлов)
    void check_file_exist_access_well_formed(QString _full_file_name, QString * _file_data);

    // проверка существования файла
    void check_file_exist(QString _full_file_name);

    // проверка прав доступа к файлу
    void check_file_access(QString _full_file_name);

    // проверка корректности файла
    void check_file_well_formed(QString _full_file_name, QString * _file_data);

    // дополнительная проверка корректности xsd-файла
    void check_xsd_file_well_formed();

    // проверка валидности xml-файла xsd-схеме
    void check_xml_file_valid();

    // вывод на консоль текста ошибки
    void print_error_str();

    QString ret_xml_full_file_name();                         // вернуть полное имя xml-файла
    QString ret_xsd_full_file_name();                         // вернуть полное имя xsd-файла
    QString ret_xml_file_data();                              // вернуть содержимое xml-файла
    QString ret_xsd_file_data();                              // вернуть содержимое xsd-файла
    bool ret_b_error();                                       // вернуть признак наличия ошибки
    QString ret_error_str();                                  // вернуть текст ошибки

    void set_xml_full_file_name(QString _xml_full_file_name); // установить полное имя xml-файла
    void set_xsd_full_file_name(QString _xsd_full_file_name); // установить полное имя xsd-файла
    void set_xml_file_data(QString _xml_file_data);           // установить содержимое xml-файла
    void set_xsd_file_data(QString _xsd_file_data);           // установить содержимое xsd-файла
    void set_b_error(bool _b_error);                          // установить признак наличия ошибки
    void set_error_str(QString _error_str);                   // установить текст ошибки

private:
    QString xml_full_file_name; // полное имя xml-файла
    QString xsd_full_file_name; // полное имя xsd-файла

    QString xml_file_data;      // содержимое xml-файла
    QString xsd_file_data;      // содержимое xsd-файла

    bool b_error;               // признак наличия ошибки
    QString error_str;          // текст ошибки
};

#endif // INPUT_FILE_CHECKER_H
