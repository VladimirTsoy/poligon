#include "input_file_parser.h"

// конструктор
input_file_parser::input_file_parser()
{
    CharSens = NULL;
    SensSite = NULL;
    ObjectContr = NULL;
    Zone = NULL;

    xml_char_sens_full_file_name = "";
    xsd_char_sens_full_file_name = "";
    xml_sens_site_full_file_name = "";
    xsd_sens_site_full_file_name = "";
    xml_object_contr_full_file_name = "";
    xsd_object_contr_full_file_name = "";
    xml_zone_full_file_name = "";
    xsd_zone_full_file_name = "";

    b_error = false;
    error_str = "";
}

// деструктор
input_file_parser::~input_file_parser()
{
    CharSens = NULL;
    SensSite = NULL;
    ObjectContr = NULL;
    Zone = NULL;

    xml_char_sens_full_file_name = "";
    xsd_char_sens_full_file_name = "";
    xml_sens_site_full_file_name = "";
    xsd_sens_site_full_file_name = "";
    xml_object_contr_full_file_name = "";
    xsd_object_contr_full_file_name = "";
    xml_zone_full_file_name = "";
    xsd_zone_full_file_name = "";

    b_error = false;
    error_str = "";
}

// основная функция
void input_file_parser::main_func(TCharSens * _CharSens,
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
                                  QString _xsd_zone_full_file_name)
{
    CharSens = _CharSens;
    SensSite = _SensSite;
    ObjectContr = _ObjectContr;
    Zone = _Zone;

    int record_size;

    record_size = sizeof(TCharSens) * SENS_CHAR_MAX;
    memset(CharSens, 0, record_size);

    record_size = sizeof(TSensSite) * SENS_MAX;
    memset(SensSite, 0, record_size);

    record_size = sizeof(TObjectContr) * TRACK_MAX;
    memset(ObjectContr, 0, record_size);

    for(int i=0; i<TRACK_MAX; i++)
    {
        ObjectContr[i].trackBZ = false;
    }

    record_size = sizeof(TZone) * ZONE_MAX;
    memset(Zone, 0, record_size);

    if(b_error == true)
    {
        return;
    }

    parse_sens_site(_xml_sens_site_full_file_name, _xsd_sens_site_full_file_name);

    if(b_error == true)
    {
        return;
    }

    parse_object_contr(_xml_object_contr_full_file_name, _xsd_object_contr_full_file_name);

    if(b_error == true)
    {
        return;
    }

    parse_char_sens(_xml_char_sens_full_file_name, _xsd_char_sens_full_file_name);

    if(b_error == true)
    {
        return;
    }

    parse_zone(_xml_zone_full_file_name, _xsd_zone_full_file_name);

    if(b_error == true)
    {
        return;
    }
}

// парсинг файла характеристики источников
void input_file_parser::parse_char_sens(QString _xml_full_file_name,
                                        QString _xsd_full_file_name)
{
    input_file_checker i_f_c;
    i_f_c.main_func(_xml_full_file_name,
                    _xsd_full_file_name);

    if(i_f_c.ret_b_error() == true)
    {
        b_error = true;
        return;
    }
    else
    {
        QXmlStreamReader xml_reader;
        xml_reader.addData(i_f_c.ret_xml_file_data());

        int char_sens_number;

        char_sens_number = 0;

        while(!xml_reader.atEnd())
        {
            if(xml_reader.isStartElement())
            {
                QString element_name;
                element_name = xml_reader.name().toString();

                if(element_name == "TCharSens")
                {
                }
                else if(element_name == "CharSens")
                {
                    QXmlStreamAttributes attributes;
                    attributes = xml_reader.attributes();

                    for(int i=0; i<attributes.size(); i++)
                    {
                        QXmlStreamAttribute & attr = attributes[i];

                        QString attr_name = attr.name().toString();
                        QString attr_value = attr.value().toString();

                        if(attr_name == "number")
                        {
                            char_sens_number = attr_value.toInt();
                        }
                    }
                }
                else if(element_name == "hMax")
                {
                    CharSens[char_sens_number].hMax = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "hMin")
                {
                    CharSens[char_sens_number].hMin = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "maxCountTrc")
                {
                    CharSens[char_sens_number].maxCountTrc = xml_reader.readElementText().toInt();
                }
                else if(element_name == "rMax")
                {
                    CharSens[char_sens_number].rMax = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "rMin")
                {
                    CharSens[char_sens_number].rMin = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "trustXY")
                {
                    CharSens[char_sens_number].trustXY = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "trustH")
                {
                    CharSens[char_sens_number].trustH = xml_reader.readElementText().toFloat();
                }
                else
                {
                    b_error = true;
                    error_str = QString("Error in parsing file %1").arg(_xml_full_file_name);
                    qDebug()<<error_str;
                    return;
                }
            }
            xml_reader.readNext();
        }
    }
}

// парсинг файла расположение источников
void input_file_parser::parse_sens_site(QString _xml_full_file_name,
                                        QString _xsd_full_file_name)
{
    input_file_checker i_f_c;
    i_f_c.main_func(_xml_full_file_name,
                    _xsd_full_file_name);

    if(i_f_c.ret_b_error() == true)
    {
        b_error = true;
        return;
    }
    else
    {
        QXmlStreamReader xml_reader;
        xml_reader.addData(i_f_c.ret_xml_file_data());

        int sens_site_number;

        sens_site_number = 0;

        while(!xml_reader.atEnd())
        {
            if(xml_reader.isStartElement())
            {
                QString element_name;
                element_name = xml_reader.name().toString();

                if(element_name == "TSensSite")
                {
                }
                else if(element_name == "SensSite")
                {
                    QXmlStreamAttributes attributes;
                    attributes = xml_reader.attributes();

                    for(int i=0; i<attributes.size(); i++)
                    {
                        QXmlStreamAttribute & attr = attributes[i];

                        QString attr_name = attr.name().toString();
                        QString attr_value = attr.value().toString();

                        if(attr_name == "number")
                        {
                            sens_site_number = attr_value.toInt();
                        }
                    }
                }
                else if(element_name == "sensChar")
                {
                    SensSite[sens_site_number].sensChar = xml_reader.readElementText().toInt();

//                    qDebug()<<"sens_char = "<<SensSite[sens_site_number].sensChar<<" "<<sens_site_number;
                }
                else if(element_name == "x")
                {
                    SensSite[sens_site_number].x = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "y")
                {
                    SensSite[sens_site_number].y = xml_reader.readElementText().toFloat();
                }
                else
                {
                    b_error = true;
                    error_str = QString("Error in parsing file %1").arg(_xml_full_file_name);
                    qDebug()<<error_str;
                    return;
                }
            }
            xml_reader.readNext();
        }
    }
}

// парсинг файла эталонов
void input_file_parser::parse_object_contr(QString _xml_full_file_name,
                                           QString _xsd_full_file_name)
{
    input_file_checker i_f_c;
    i_f_c.main_func(_xml_full_file_name,
                    _xsd_full_file_name);

    if(i_f_c.ret_b_error() == true)
    {
        b_error = true;
        return;
    }
    else
    {
        QXmlStreamReader xml_reader;
        xml_reader.addData(i_f_c.ret_xml_file_data());

        int object_contr_number;
        int manevr_number;
        bool b_manevr;

        object_contr_number = 0;
        manevr_number = 0;
        b_manevr = false;

        while(!xml_reader.atEnd())
        {
            if(xml_reader.isStartElement())
            {
                QString element_name;
                element_name = xml_reader.name().toString();

                if(element_name == "TObjectContr")
                {
                }
                else if(element_name == "ObjectContr")
                {
                    QXmlStreamAttributes attributes;
                    attributes = xml_reader.attributes();

                    for(int i=0; i<attributes.size(); i++)
                    {
                        QXmlStreamAttribute & attr = attributes[i];

                        QString attr_name = attr.name().toString();
                        QString attr_value = attr.value().toString();

                        if(attr_name == "number")
                        {
                            object_contr_number = attr_value.toInt();
                        }
                    }

                    ObjectContr[object_contr_number].countManevr = 0;
                    ObjectContr[object_contr_number].trackBZ = true;
                    b_manevr = false;
                }
                else if(element_name == "Manevr")
                {
                    QXmlStreamAttributes attributes;
                    attributes = xml_reader.attributes();

                    for(int i=0; i<attributes.size(); i++)
                    {
                        QXmlStreamAttribute & attr = attributes[i];

                        QString attr_name = attr.name().toString();
                        QString attr_value = attr.value().toString();

                        if(attr_name == "number")
                        {
                            manevr_number = attr_value.toInt();
                        }
                    }
                    ObjectContr[object_contr_number].countManevr++;
                    b_manevr = true;
                }
                else if(element_name == "ObjClass")
                {
                    ObjectContr[object_contr_number].ObjClass = (EUObjClass) xml_reader.readElementText().toInt();
                }
                else if(element_name == "TO")
                {
                    ObjectContr[object_contr_number].TO = xml_reader.readElementText().toInt();
                }
                else if(element_name == "IO")
                {
                    ObjectContr[object_contr_number].IO = xml_reader.readElementText().toInt();
                }
                else if(element_name == "OGP")
                {
                    ObjectContr[object_contr_number].OGP = (EUOGP) xml_reader.readElementText().toInt();
                }
                else if(element_name == "tStart" && b_manevr == false)
                {
                    ObjectContr[object_contr_number].tStart = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "tFinish" && b_manevr == false)
                {
                    ObjectContr[object_contr_number].tFinish = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "x")
                {
                    ObjectContr[object_contr_number].x = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "y")
                {
                    ObjectContr[object_contr_number].y = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "h")
                {
                    ObjectContr[object_contr_number].h = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "psi")
                {
                    ObjectContr[object_contr_number].psi = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "v")
                {
                    ObjectContr[object_contr_number].v = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "vh" && b_manevr == false)
                {
                    ObjectContr[object_contr_number].vh = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "tStart" && b_manevr == true)
                {
                    ObjectContr[object_contr_number].Manevr[manevr_number].tStart = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "tFinish" && b_manevr == true)
                {
                    ObjectContr[object_contr_number].Manevr[manevr_number].tFinish = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "a" && b_manevr == true)
                {
                    ObjectContr[object_contr_number].Manevr[manevr_number].a = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "vh" && b_manevr == true)
                {
                    ObjectContr[object_contr_number].Manevr[manevr_number].vh = xml_reader.readElementText().toFloat();
                }
                else if(element_name == "r" && b_manevr == true)
                {
                    ObjectContr[object_contr_number].Manevr[manevr_number].r = xml_reader.readElementText().toFloat();
                }
                else
                {
                    b_error = true;
                    error_str = QString("Error in parsing file %1").arg(_xml_full_file_name);
                    qDebug()<<error_str;
                    return;
                }
            }
            xml_reader.readNext();
        }
    }
}

// парсинг файла зон
void input_file_parser::parse_zone(QString _xml_full_file_name,
                                   QString _xsd_full_file_name)
{
    input_file_checker i_f_c;
    i_f_c.main_func(_xml_full_file_name,
                    _xsd_full_file_name);

    if(i_f_c.ret_b_error() == true)
    {
        b_error = true;
        return;
    }
    else
    {
        QXmlStreamReader xml_reader;
        xml_reader.addData(i_f_c.ret_xml_file_data());

        int zone_number;
        int point_number;

        zone_number = 0;
        point_number = 0;

        while(!xml_reader.atEnd())
        {
            if(xml_reader.isStartElement())
            {
                QString element_name;
                element_name = xml_reader.name().toString();

                if(element_name == "zones")
                {
                }
                else if(element_name == "zone")
                {
                    QXmlStreamAttributes attributes;
                    attributes = xml_reader.attributes();

                    for(int i=0; i<attributes.size(); i++)
                    {
                        QXmlStreamAttribute & attr = attributes[i];

                        QString attr_name = attr.name().toString();
                        QString attr_value = attr.value().toString();

                        if(attr_name == "number")
                        {
                            zone_number = attr_value.toInt()-1;
                        }
                    }

                    Zone[zone_number].countPoint = 0;
                }
                else if(element_name == "point")
                {
                    QXmlStreamAttributes attributes;
                    attributes = xml_reader.attributes();

                    for(int i=0; i<attributes.size(); i++)
                    {
                        QXmlStreamAttribute & attr = attributes[i];

                        QString attr_name = attr.name().toString();
                        QString attr_value = attr.value().toString();

                        if(attr_name == "number")
                        {
                            point_number = attr_value.toInt()-1;
                        }
                    }
                    Zone[zone_number].countPoint++;
                }
                else if(element_name == "r")
                {
                    Zone[zone_number].r = xml_reader.readElementText().toInt();
                }
                else if(element_name == "g")
                {
                    Zone[zone_number].g = xml_reader.readElementText().toInt();
                }
                else if(element_name == "b")
                {
                    Zone[zone_number].b = xml_reader.readElementText().toInt();
                }
                else if(element_name == "a")
                {
                    Zone[zone_number].a = xml_reader.readElementText().toInt();
                }
                else if(element_name == "x")
                {
                    Zone[zone_number].Point[point_number].x = xml_reader.readElementText().toInt();
                }
                else if(element_name == "y")
                {
                    Zone[zone_number].Point[point_number].y = xml_reader.readElementText().toInt();
                }
                else
                {
                    b_error = true;
                    error_str = QString("Error in parsing file %1").arg(_xml_full_file_name);
//                    qDebug()<<error_str;
                    return;
                }
            }
            xml_reader.readNext();
        }
    }
}

TCharSens * input_file_parser::ret_CharSens() // вернуть указатель на массив характеристики источников
{
    return CharSens;
}

TSensSite * input_file_parser::ret_SensSite() // вернуть указатель на массив расположение источников
{
    return SensSite;
}

TObjectContr * input_file_parser::ret_ObjectContr() // вернуть указатель на массив эталоны
{
    return ObjectContr;
}

TZone * input_file_parser::ret_Zone() // вернуть указатель на массив зоны
{
    return Zone;
}

QString input_file_parser::ret_xml_char_sens_full_file_name() // вернуть полное имя xml-файла характеристики источников
{
    return xml_char_sens_full_file_name;
}

QString input_file_parser::ret_xsd_char_sens_full_file_name() // вернуть полное имя xsd-файла характеристики источников
{
    return xsd_char_sens_full_file_name;
}

QString input_file_parser::ret_xml_sens_site_full_file_name() // вернуть полное имя xml-файла расположение источников
{
    return xml_sens_site_full_file_name;
}

QString input_file_parser::ret_xsd_sens_site_full_file_name() // вернуть полное имя xsd-файла расположение источников
{
    return xsd_sens_site_full_file_name;
}

QString input_file_parser::ret_xml_object_contr_full_file_name() // вернуть полное имя xml-файла эталоны
{
    return xml_object_contr_full_file_name;
}

QString input_file_parser::ret_xsd_object_contr_full_file_name() // вернуть полное имя xsd-файла эталоны
{
    return xsd_object_contr_full_file_name;
}

QString input_file_parser::ret_xml_zone_full_file_name() // вернуть полное имя xml-файла зоны
{
    return xml_zone_full_file_name;
}

QString input_file_parser::ret_xsd_zone_full_file_name() // вернуть полное имя xsd-файла зоны
{
    return xsd_zone_full_file_name;
}

bool input_file_parser::ret_b_error() // вернуть признак наличия ошибки
{
    return b_error;
}

QString input_file_parser::ret_error_str() // вернуть текст ошибки
{
    return error_str;
}


void input_file_parser::set_CharSens(TCharSens * _CharSens) // установить указатель на массив характеристики источников
{
    CharSens = _CharSens;
}

void input_file_parser::set_SensSite(TSensSite * _SensSite) // установить указатель на массив расположение источников
{
    SensSite = _SensSite;
}

void input_file_parser::set_ObjectContr(TObjectContr * _ObjectContr) // установить указатель на массив эталоны
{
    ObjectContr = _ObjectContr;
}

void input_file_parser::set_Zone(TZone * _Zone) // установить указатель на массив зоны
{
    Zone = _Zone;
}

void input_file_parser::set_xml_char_sens_full_file_name(QString _xml_char_sens_full_file_name) // установить полное имя xml-файла характеристики источников
{
    xml_char_sens_full_file_name = _xml_char_sens_full_file_name;
}

void input_file_parser::set_xsd_char_sens_full_file_name(QString _xsd_char_sens_full_file_name) // установить полное имя xsd-файла характеристики источников
{
    xsd_char_sens_full_file_name = _xsd_char_sens_full_file_name;
}

void input_file_parser::set_xml_sens_site_full_file_name(QString _xml_sens_site_full_file_name) // установить полное имя xml-файла расположение источников
{
    xml_sens_site_full_file_name = _xml_sens_site_full_file_name;
}

void input_file_parser::set_xsd_sens_site_full_file_name(QString _xsd_sens_site_full_file_name) // установить полное имя xsd-файла расположение источников
{
    xsd_sens_site_full_file_name = _xsd_sens_site_full_file_name;
}

void input_file_parser::set_xml_object_contr_full_file_name(QString _xml_object_contr_full_file_name) // установить полное имя xml-файла эталоны
{
    xml_object_contr_full_file_name = _xml_object_contr_full_file_name;
}

void input_file_parser::set_xsd_object_contr_full_file_name(QString _xsd_object_contr_full_file_name) // установить полное имя xsd-файла эталоны
{
    xsd_object_contr_full_file_name = _xsd_object_contr_full_file_name;
}

void input_file_parser::set_xml_zone_full_file_name(QString _xml_zone_full_file_name) // установить полное имя xml-файла зоны
{
    xml_zone_full_file_name = _xml_zone_full_file_name;
}

void input_file_parser::set_xsd_zone_full_file_name(QString _xsd_zone_full_file_name) // установить полное имя xsd-файла зоны
{
    xsd_zone_full_file_name = _xsd_zone_full_file_name;
}

void input_file_parser::set_b_error(bool _b_error) // установить признак наличия ошибки
{
    b_error = _b_error;
}

void input_file_parser::set_error_str(QString _error_str) // установить текст ошибки
{
    error_str = _error_str;
}
