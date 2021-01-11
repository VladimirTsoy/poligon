#ifndef INPUT_FILE_PARSER_H
#define INPUT_FILE_PARSER_H

#include <stddef.h>
#include <QString>
#include <QDebug>
#include <QXmlStreamReader>

#include "input_file_checker.h"

#include "../CSCommon/include/UZone.h"
#include "../CSCommon/include/_IMIT_.h"

using namespace COMMON;
using namespace COMMON::_IMIT_;
using namespace COMMON::_ZONE_;

// класс обеспечивает заполнение переданныго ряда
// массивов обобщенных структур, обеспечивая контроль
// корректности входных данных
class input_file_parser
{
public:
    // конструктор
    input_file_parser();

    // деструктор
    ~input_file_parser();

    // основная функция
    void main_func(TCharSens * _CharSens,
                   TSensSite * _SensSite,
                   TObjectContr * _ObjectContr,
                   TZone * _Zone,
                   QString _xml_char_sens_full_file_name,
                   QString _xsd_char_sens_full_file_name,
                   QString _xml_sens_site_full_file_name,
                   QString _xsd_sens_site_full_file_name,
                   QString _xml_object_contr_full_file_name,
                   QString _xsd_object_contr_full_file_name,
                   QString _xml_zone_full_file_name,
                   QString _xsd_zone_full_file_name);

    // парсинг файла характеристики источников
    void parse_char_sens(QString _xml_full_file_name,
                         QString _xsd_full_file_name);

    // парсинг файла расположение источников
    void parse_sens_site(QString _xml_full_file_name,
                         QString _xsd_full_file_name);

    // парсинг файла эталонов
    void parse_object_contr(QString _xml_full_file_name,
                            QString _xsd_full_file_name);

    // парсинг файла зон
    void parse_zone(QString _xml_full_file_name,
                    QString _xsd_full_file_name);


    TCharSens * ret_CharSens();                                                         // вернуть указатель на массив характеристики источников
    TSensSite * ret_SensSite();                                                         // вернуть указатель на массив расположение источников
    TObjectContr * ret_ObjectContr();                                                   // вернуть указатель на массив эталоны
    TZone * ret_Zone();                                                                 // вернуть указатель на массив зоны
    QString ret_xml_char_sens_full_file_name();                                         // вернуть полное имя xml-файла характеристики источников
    QString ret_xsd_char_sens_full_file_name();                                         // вернуть полное имя xsd-файла характеристики источников
    QString ret_xml_sens_site_full_file_name();                                         // вернуть полное имя xml-файла расположение источников
    QString ret_xsd_sens_site_full_file_name();                                         // вернуть полное имя xsd-файла расположение источников
    QString ret_xml_object_contr_full_file_name();                                      // вернуть полное имя xml-файла эталоны
    QString ret_xsd_object_contr_full_file_name();                                      // вернуть полное имя xsd-файла эталоны
    QString ret_xml_zone_full_file_name();                                              // вернуть полное имя xml-файла зоны
    QString ret_xsd_zone_full_file_name();                                              // вернуть полное имя xsd-файла зоны
    bool ret_b_error();                                                                 // вернуть признак наличия ошибки
    QString ret_error_str();                                                            // вернуть текст ошибки

    void set_CharSens(TCharSens * _CharSens);                                           // установить указатель на массив характеристики источников
    void set_SensSite(TSensSite * _SensSite);                                           // установить указатель на массив расположение источников
    void set_ObjectContr(TObjectContr * _ObjectContr);                                  // установить указатель на массив эталоны
    void set_Zone(TZone * _Zone);                                                       // установить указатель на массив зоны
    void set_xml_char_sens_full_file_name(QString _xml_char_sens_full_file_name);       // установить полное имя xml-файла характеристики источников
    void set_xsd_char_sens_full_file_name(QString _xsd_char_sens_full_file_name);       // установить полное имя xsd-файла характеристики источников
    void set_xml_sens_site_full_file_name(QString _xml_sens_site_full_file_name);       // установить полное имя xml-файла расположение источников
    void set_xsd_sens_site_full_file_name(QString _xsd_sens_site_full_file_name);       // установить полное имя xsd-файла расположение источников
    void set_xml_object_contr_full_file_name(QString _xml_object_contr_full_file_name); // установить полное имя xml-файла эталоны
    void set_xsd_object_contr_full_file_name(QString _xsd_object_contr_full_file_name); // установить полное имя xsd-файла эталоны
    void set_xml_zone_full_file_name(QString _xml_zone_full_file_name);                 // установить полное имя xml-файла зоны
    void set_xsd_zone_full_file_name(QString _xsd_zone_full_file_name);                 // установить полное имя xsd-файла зоны
    void set_b_error(bool _b_error);                                                    // установить признак наличия ошибки
    void set_error_str(QString _error_str);                                             // установить текст ошибки

private:
    TCharSens * CharSens;                    // указатель на массив характеристики источников
    TSensSite * SensSite;                    // указатель на массив расположение источников
    TObjectContr * ObjectContr;              // указатель на массив эталоны
    TZone * Zone;                            // указатель на массив зоны

    QString xml_char_sens_full_file_name;    // полное имя xml-файла характеристики источников
    QString xsd_char_sens_full_file_name;    // полное имя xsd-файла характеристики источников
    QString xml_sens_site_full_file_name;    // полное имя xml-файла расположение источников
    QString xsd_sens_site_full_file_name;    // полное имя xsd-файла расположение источников
    QString xml_object_contr_full_file_name; // полное имя xml-файла эталоны
    QString xsd_object_contr_full_file_name; // полное имя xsd-файла эталоны
    QString xml_zone_full_file_name;         // полное имя xml-файла зоны
    QString xsd_zone_full_file_name;         // полное имя xsd-файла зоны

    bool b_error;                            // признак наличия ошибки
    QString error_str;                       // текст ошибки
};

#endif // INPUT_FILE_PARSER_H
