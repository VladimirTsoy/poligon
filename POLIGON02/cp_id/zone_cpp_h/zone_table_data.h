#ifndef ZONE_TABLE_DATA
#define ZONE_TABLE_DATA

#include <stddef.h>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

#include "zone_row_data.h"

// данные таблицы
class zone_table_data
{
public:
    // конструктор
    zone_table_data(QString _full_file_name,
                    QString _table_tag_name,
                    QString _row_tag_name,
                    QString _sub_row_tag_name);
    // деструктор
    ~zone_table_data();

    // добавление нового элемента в список
    void add_new_element();

    // очистка списка
    void clear_list();

    // чтение файла
    void read_file();

    // проверка существования файла
    void check_file_exist();

    // считывание содержимого файла
    void read_file_data();

    // парсинг содержимого файла
    void parsing_file_data();

    // создание содержимого файла
    void create_file_data();

    // запись в файл
    void write_file();

    QString ret_full_file_name();                         // вернуть полное имя xml-файла
    QString ret_file_data();                              // вернуть содержимое xml-файла
    QString ret_comment();                                // вернуть комментарий
    QString ret_table_tag_name();                         // вернуть название основного тега
    QString ret_row_tag_name();                           // вернуть название тега строки
    QString ret_sub_row_tag_name();                       // вернуть название тега подстроки
    bool ret_b_error();                                   // вернуть признак ошибки
    QString ret_error_str();                              // вернуть текст ошибки
    zone_row_data * ret_first();                            // вернуть указатель на первый элемент
    zone_row_data * ret_last();                             // вернуть указатель на последний элемент

    void set_full_file_name(QString _full_file_name);     // установить полное имя xml-файла
    void set_file_data(QString _file_data);               // установить содержимое xml-файла
    void set_comment(QString _comment);                   // установить комментарий
    void set_table_tag_name(QString _table_tag_name);     // установить название основного тега
    void set_row_tag_name(QString _row_tag_name);         // установить название тега строки
    void set_sub_row_tag_name(QString _sub_row_tag_name); // установить название тега подстроки
    void set_b_error(bool _b_error);                      // установить признак ошибки
    void set_error_str(QString _error_str);               // установить текст ошибки
    void set_first(zone_row_data * _first);                 // установить указатель на первый элемент
    void set_last(zone_row_data * _last);                   // установить указатель на последний элемент

private:
    // xml-файл -------------------------------------------------------------------------------------------------------
    QString full_file_name;   // полное имя xml-файла
    QString file_data;        // содержимое xml-файла
    // ----------------------------------------------------------------------------------------------------------------

    // комментарий ----------------------------------------------------------------------------------------------------
    QString comment;
    // ----------------------------------------------------------------------------------------------------------------

    // содержимое xml-документа ---------------------------------------------------------------------------------------
    QString table_tag_name;   // название основного тега
    QString row_tag_name;     // название тега строки
    QString sub_row_tag_name; // название тега подстроки
    // ----------------------------------------------------------------------------------------------------------------

    // проверка корректности работы объекта ---------------------------------------------------------------------------
    bool b_error;             // признак ошибки
    QString error_str;        // текст ошибки
    // ----------------------------------------------------------------------------------------------------------------

    // список элементов -----------------------------------------------------------------------------------------------
    zone_row_data * first;    // указатель на первый элемент
    zone_row_data * last;     // указатель на последний элемент
    // ----------------------------------------------------------------------------------------------------------------
};

#endif // ZONE_TABLE_DATA
