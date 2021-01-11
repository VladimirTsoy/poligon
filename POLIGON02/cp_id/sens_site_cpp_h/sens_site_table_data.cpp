#include "sens_site_table_data.h"

// конструктор
sens_site_table_data::sens_site_table_data(QString _full_file_name,
                                           QString _table_tag_name,
                                           QString _row_tag_name)
{
    full_file_name = _full_file_name;
    file_data = "";

    comment = "";

    table_tag_name = _table_tag_name;
    row_tag_name = _row_tag_name;

    b_error = false;
    error_str = "";

    first = NULL;
    last = NULL;
}

// деструктор
sens_site_table_data::~sens_site_table_data()
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
void sens_site_table_data::add_new_element()
{
    if(first == NULL)
    {
        last = new sens_site_row_data();
        first = last;
    }
    else
    {
        sens_site_row_data * ptr_new_element;
        ptr_new_element = new sens_site_row_data();
        last->set_next(ptr_new_element);
        ptr_new_element->set_prev(last);
        last = ptr_new_element;
    }
}

// очистка списка
void sens_site_table_data::clear_list()
{
    sens_site_row_data * iter;
    iter = first;
    sens_site_row_data * iter_delete;

    while(iter != NULL)
    {
        iter_delete = iter;
        iter = iter->ret_next();
        delete iter_delete;
    }
}

// чтение файла
void sens_site_table_data::read_file()
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
void sens_site_table_data::check_file_exist()
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
void sens_site_table_data::read_file_data()
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
void sens_site_table_data::parsing_file_data()
{
    QXmlStreamReader * xml_reader;
    xml_reader = new QXmlStreamReader();

    xml_reader->addData(file_data);

    // признак нахождения первого комментария
    bool b_first_comment;
    b_first_comment = false;

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
            }
            else if(element_name == "sensChar")
            {
                last->ret_charSens()->set_value(xml_reader->readElementText());
            }
            else if(element_name == "x")
            {
                last->ret_x()->set_value(xml_reader->readElementText());
            }
            else if(element_name == "y")
            {
                last->ret_y()->set_value(xml_reader->readElementText());
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
void sens_site_table_data::create_file_data()
{
    file_data = "";
    file_data = QString("<!--%1-->%2").arg(comment).arg("\n");

    sens_site_row_data * iter;
    iter = first;

    while(iter != NULL)
    {
        iter->ret_number()->generate_text("\t\t");
        iter->ret_charSens()->generate_text("\t\t");
        iter->ret_x()->generate_text("\t\t");
        iter->ret_y()->generate_text("\t\t");

        iter = iter->ret_next();
    }

    iter = first;

    file_data = file_data + QString("<%1>%2").arg(table_tag_name).arg("\n");
    while(iter != NULL)
    {
        file_data = file_data + QString("%1<%2 %3>%7%4%5%6%1</%2>%7")
                                .arg("\t")
                                .arg(row_tag_name)
                                .arg(iter->ret_number()->ret_text())
                                .arg(iter->ret_charSens()->ret_text())
                                .arg(iter->ret_x()->ret_text())
                                .arg(iter->ret_y()->ret_text())
                                .arg("\n");

        iter = iter->ret_next();
    }

    file_data = file_data + QString("</%1>").arg(table_tag_name);
}

// запись в файл
void sens_site_table_data::write_file()
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

QString sens_site_table_data::ret_full_file_name() // вернуть полное имя xml-файла
{
    return full_file_name;
}

QString sens_site_table_data::ret_file_data() // вернуть содержимое xml-файла
{
    return file_data;
}

QString sens_site_table_data::ret_comment() // вернуть комментарий
{
    return comment;
}

QString sens_site_table_data::ret_table_tag_name() // вернуть название основного тега
{
    return table_tag_name;
}

QString sens_site_table_data::ret_row_tag_name() // вернуть название тега строки
{
    return row_tag_name;
}

bool sens_site_table_data::ret_b_error() // вернуть признак ошибки
{
    return b_error;
}

QString sens_site_table_data::ret_error_str() // вернуть текст ошибки
{
    return error_str;
}

sens_site_row_data * sens_site_table_data::ret_first() // вернуть указатель на первый элемент
{
    return first;
}

sens_site_row_data * sens_site_table_data::ret_last() // вернуть указатель на последний элемент
{
    return last;
}

void sens_site_table_data::set_full_file_name(QString _full_file_name) // установить полное имя xml-файла
{
    full_file_name = _full_file_name;
}

void sens_site_table_data::set_file_data(QString _file_data) // установить содержимое xml-файла
{
    file_data = _file_data;
}

void sens_site_table_data::set_comment(QString _comment) // установить комментарий
{
    comment = _comment;
}

void sens_site_table_data::set_table_tag_name(QString _table_tag_name) // установить название основного тега
{
    table_tag_name = _table_tag_name;
}

void sens_site_table_data::set_row_tag_name(QString _row_tag_name) // установить название тега строки
{
    row_tag_name = _row_tag_name;
}

void sens_site_table_data::set_b_error(bool _b_error) // установить признак ошибки
{
    b_error = _b_error;
}

void sens_site_table_data::set_error_str(QString _error_str) // установить текст ошибки
{
    error_str = _error_str;
}

void sens_site_table_data::set_first(sens_site_row_data * _first) // установить указатель на первый элемент
{
    first = _first;
}

void sens_site_table_data::set_last(sens_site_row_data * _last) // установить указатель на последний элемент
{
    last = _last;
}
