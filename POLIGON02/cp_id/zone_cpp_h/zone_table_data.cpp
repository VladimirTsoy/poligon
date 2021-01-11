#include "zone_table_data.h"

// конструктор
zone_table_data::zone_table_data(QString _full_file_name,
                                 QString _table_tag_name,
                                 QString _row_tag_name,
                                 QString _sub_row_tag_name)
{
    full_file_name = _full_file_name;
    file_data = "";

    comment = "";

    table_tag_name = _table_tag_name;
    row_tag_name = _row_tag_name;
    sub_row_tag_name = _sub_row_tag_name;

    b_error = false;
    error_str = "";

    first = NULL;
    last = NULL;
}

// деструктор
zone_table_data::~zone_table_data()
{
    full_file_name = "";
    file_data = "";

    comment = "";

    table_tag_name = "";
    row_tag_name = "";

    b_error = false;
    error_str = "";

    clear_list();

    first = NULL;
    last = NULL;
}

// добавление нового элемента в список
void zone_table_data::add_new_element()
{
    if(first == NULL)
    {
        last = new zone_row_data();
        first = last;
    }
    else
    {
        zone_row_data * ptr_new_element;
        ptr_new_element = new zone_row_data();
        last->set_next(ptr_new_element);
        ptr_new_element->set_prev(last);
        last = ptr_new_element;
    }
}

// очистка списка
void zone_table_data::clear_list()
{
    zone_row_data * iter;
    iter = first;
    zone_row_data * iter_delete;

    while(iter != NULL)
    {
        iter_delete = iter;
        iter = iter->ret_next();
        delete iter_delete;
    }
}

// чтение файла
void zone_table_data::read_file()
{
    // проверка существования файла
    check_file_exist();

    // проверка существования файла выдала ошибку
    if(b_error == true)
    {
        qDebug()<<error_str;
        return;
    }

    // считывание содержимого файла
    read_file_data();

    // считывание содержимого файла выдало ошибку
    if(b_error == true)
    {
        qDebug()<<error_str;
        return;
    }

    // парсинг содержимого файла
    parsing_file_data();

    // парсинг файла выдал ошибку
    if(b_error == true)
    {
        qDebug()<<error_str;
        return;
    }
}

// проверка существования файла
void zone_table_data::check_file_exist()
{
    QFile file(full_file_name);

    if(file.exists() == false)
    {
        b_error = true;
        error_str = QString("File %1 not found").arg(full_file_name);
        return;
    }
    else
    {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            b_error = true;
            error_str = QString("Can't open file %1").arg(full_file_name);
            return;
        }
        else
        {
            file.close();
        }
    }
}

// считывание содержимого файла
void zone_table_data::read_file_data()
{
    QFile file(full_file_name);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        b_error = true;
        error_str = QString("Can't open file %1").arg(full_file_name);
        return;
    }
    else
    {
        file_data = file.readAll();
        file.close();
    }
}

// парсинг содержимого файла
void zone_table_data::parsing_file_data()
{
    QXmlStreamReader * xml_reader;
    xml_reader = new QXmlStreamReader();

    xml_reader->addData(file_data);

    // признак нахождения первого комментария
    bool b_first_comment;
    b_first_comment = false;

    // признак маневра
    bool b_point;
    b_point = false;

    while(!xml_reader->atEnd())
    {
        // если парсер наткнулся на первый комментарий
        if(xml_reader->isComment() == true && b_first_comment == false)
        {
            comment = xml_reader->text().toString();
            b_first_comment = true;
        }
        // если парсер наткнулся на открывающийся элемент
        if(xml_reader->isStartElement())
        {
            QString element_name;
            element_name = xml_reader->name().toString();

            // если парсер наткнулся на основной тег
            if(element_name == table_tag_name)
            {
            }
            // если парсер наткнулся на тег строки
            else if(element_name == row_tag_name)
            {
                // добавление нового элемента в список
                add_new_element();

                QXmlStreamAttributes attributes;
                attributes = xml_reader->attributes();

                for(int i=0; i<attributes.size(); i++)
                {
                    QXmlStreamAttribute & attr = attributes[i];

                    QString attr_name = attr.name().toString();
                    QString attr_value = attr.value().toString();

                    if(attr_name == "number")
                    {
                        last->ret_number()->set_value(attr_value);
                    }
                    else
                    {
                        b_error = true;
                        error_str = QString("Error in parsing file %1").arg(full_file_name);

                        delete xml_reader;
                        xml_reader = NULL;

                        return;
                    }
                }

                b_point = false;
            }
            // если парсер наткнулся на тег подстроки
            else if(element_name == sub_row_tag_name)
            {
                // добавление нового элемента в список
                last->add_new_element();

                QXmlStreamAttributes attributes;
                attributes = xml_reader->attributes();

                for(int i=0; i<attributes.size(); i++)
                {
                    QXmlStreamAttribute & attr = attributes[i];

                    QString attr_name = attr.name().toString();
                    QString attr_value = attr.value().toString();

                    if(attr_name == "number")
                    {
                        last->ret_last()->ret_number()->set_value(attr_value);
                    }
                    else
                    {
                        b_error = true;
                        error_str = QString("Error in parsing file %1").arg(full_file_name);

                        delete xml_reader;
                        xml_reader = NULL;

                        return;
                    }
                }

                b_point = true;
            }

            else if(element_name == "r" && b_point == false)
            {
                last->ret_r()->set_value(xml_reader->readElementText());
            }
            else if(element_name == "g" && b_point == false)
            {
                last->ret_g()->set_value(xml_reader->readElementText());
            }
            else if(element_name == "b" && b_point == false)
            {
                last->ret_b()->set_value(xml_reader->readElementText());
            }
            else if(element_name == "a" && b_point == false)
            {
                last->ret_a()->set_value(xml_reader->readElementText());
            }
            else if(element_name == "x" && b_point == true)
            {
                last->ret_last()->ret_x()->set_value(xml_reader->readElementText());
            }
            else if(element_name == "y" && b_point == true)
            {
                last->ret_last()->ret_y()->set_value(xml_reader->readElementText());
            }
            else
            {
                b_error = true;
                error_str = QString("Error in parsing file %1").arg(full_file_name);

                delete xml_reader;
                xml_reader = NULL;

                return;
            }
        }
        xml_reader->readNext();
    }

    delete xml_reader;
    xml_reader = NULL;
}

// создание содержимого файла
void zone_table_data::create_file_data()
{
    file_data = "";
    file_data = QString("<!--%1-->%2").arg(comment).arg("\n");

    zone_row_data * iter_zone;
    iter_zone = first;

    while(iter_zone != NULL)
    {
        iter_zone->ret_number()->generate_text("\t\t");
        iter_zone->ret_r()->generate_text("\t\t");
        iter_zone->ret_g()->generate_text("\t\t");
        iter_zone->ret_b()->generate_text("\t\t");
        iter_zone->ret_a()->generate_text("\t\t");

        zone_point_row_data * iter_point;
        iter_point = iter_zone->ret_first();

        while(iter_point != NULL)
        {
            iter_point->ret_number()->generate_text("\t\t\t");
            iter_point->ret_x()->generate_text("\t\t\t");
            iter_point->ret_y()->generate_text("\t\t\t");

            iter_point = iter_point->ret_next();
        }

        iter_zone = iter_zone->ret_next();
    }

    iter_zone = first;

    file_data = file_data + QString("<%1>%2").arg(table_tag_name).arg("\n");
    while(iter_zone != NULL)
    {
        file_data = file_data + QString("%1<%2 %3>%8%4%5%6%7")
                                .arg("\t")
                                .arg(row_tag_name)
                                .arg(iter_zone->ret_number()->ret_text())
                                .arg(iter_zone->ret_r()->ret_text())
                                .arg(iter_zone->ret_g()->ret_text())
                                .arg(iter_zone->ret_b()->ret_text())
                                .arg(iter_zone->ret_a()->ret_text())
                                .arg("\n");

        zone_point_row_data * iter_point;
        iter_point = iter_zone->ret_first();

        while(iter_point != NULL)
        {
            file_data = file_data + QString("%1<%2 %3>%6%4%5%1</%2>%6")
                                    .arg("\t\t")
                                    .arg(sub_row_tag_name)
                                    .arg(iter_point->ret_number()->ret_text())
                                    .arg(iter_point->ret_x()->ret_text())
                                    .arg(iter_point->ret_y()->ret_text())
                                    .arg("\n");

            iter_point = iter_point->ret_next();
        }

        file_data = file_data + QString("%1</%2>%3")
                                .arg("\t")
                                .arg(row_tag_name)
                                .arg("\n");

        iter_zone = iter_zone->ret_next();
    }

    file_data = file_data + QString("</%1>").arg(table_tag_name);
}

// запись в файл
void zone_table_data::write_file()
{
    QFile file(full_file_name);
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
         b_error = true;
         error_str = QString("Can't write data in file %1").arg(full_file_name);
     }
     else
     {
         QTextStream out(& file);
         out<<file_data;
         file.close();
     }

     if(b_error == true)
     {
         qDebug()<<error_str;
         return;
     }
}

QString zone_table_data::ret_full_file_name() // вернуть полное имя xml-файла
{
    return full_file_name;
}

QString zone_table_data::ret_file_data() // вернуть содержимое xml-файла
{
    return file_data;
}

QString zone_table_data::ret_comment() // вернуть комментарий
{
    return comment;
}

QString zone_table_data::ret_table_tag_name() // вернуть название основного тега
{
    return table_tag_name;
}

QString zone_table_data::ret_row_tag_name() // вернуть название тега строки
{
    return row_tag_name;
}

QString zone_table_data::ret_sub_row_tag_name() // вернуть название тега подстроки
{
    return sub_row_tag_name;
}

bool zone_table_data::ret_b_error() // вернуть признак ошибки
{
    return b_error;
}

QString zone_table_data::ret_error_str() // вернуть текст ошибки
{
    return error_str;
}

zone_row_data * zone_table_data::ret_first() // вернуть указатель на первый элемент
{
    return first;
}

zone_row_data * zone_table_data::ret_last() // вернуть указатель на последний элемент
{
    return last;
}

void zone_table_data::set_full_file_name(QString _full_file_name) // установить полное имя xml-файла
{
    full_file_name = _full_file_name;
}

void zone_table_data::set_file_data(QString _file_data) // установить содержимое xml-файла
{
    file_data = _file_data;
}

void zone_table_data::set_comment(QString _comment) // установить комментарий
{
    comment = _comment;
}

void zone_table_data::set_table_tag_name(QString _table_tag_name) // установить название основного тега
{
    table_tag_name = _table_tag_name;
}

void zone_table_data::set_row_tag_name(QString _row_tag_name) // установить название тега строки
{
    row_tag_name = _row_tag_name;
}

void zone_table_data::set_sub_row_tag_name(QString _sub_row_tag_name) // установить название тега подстроки
{
    sub_row_tag_name = _sub_row_tag_name;
}

void zone_table_data::set_b_error(bool _b_error) // установить признак ошибки
{
    b_error = _b_error;
}

void zone_table_data::set_error_str(QString _error_str) // установить текст ошибки
{
    error_str = _error_str;
}

void zone_table_data::set_first(zone_row_data * _first) // установить указатель на первый элемент
{
    first = _first;
}

void zone_table_data::set_last(zone_row_data * _last) // установить указатель на последний элемент
{
    last = _last;
}
