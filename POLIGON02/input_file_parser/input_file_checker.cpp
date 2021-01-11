#include "input_file_checker.h"

// конструктор
input_file_checker::input_file_checker()
{
    xml_full_file_name = "";
    xsd_full_file_name = "";
    xml_file_data = "";
    xsd_file_data = "";
    b_error = false;
    error_str = "";
}

// деструктор
input_file_checker::~input_file_checker()
{
    xml_full_file_name = "";
    xsd_full_file_name = "";
    xml_file_data = "";
    xsd_file_data = "";
    b_error = false;
    error_str = "";
}

// основная функция
void input_file_checker::main_func(QString _xml_full_file_name,
                                   QString _xsd_full_file_name)
{
    xml_full_file_name = _xml_full_file_name;
    xsd_full_file_name = _xsd_full_file_name;

    check_file_exist_access_well_formed(xml_full_file_name, &xml_file_data);
    if(b_error == true)
    {
        print_error_str();
        return;
    }
    else
    {
        check_file_exist_access_well_formed(xsd_full_file_name, &xsd_file_data);
        if(b_error == true)
        {
            print_error_str();
            return;
        }
        else
        {
            check_xsd_file_well_formed();
            if(b_error == true)
            {
                print_error_str();
                return;
            }
            else
            {
                check_xml_file_valid();
                if(b_error == true)
                {
                    print_error_str();
                    return;
                }
            }
        }
    }
}

// проверка файла в части существования, прав доступа и корректности (одинакова и для xml- и для xsd-файлов)
void input_file_checker::check_file_exist_access_well_formed(QString _full_file_name, QString * _file_data)
{
    check_file_exist(_full_file_name);
    if(b_error == true)
    {
        return;
    }
    else
    {
        check_file_access(_full_file_name);
        if(b_error == true)
        {
            return;
        }
        else
        {
            check_file_well_formed(_full_file_name, _file_data);
        }
    }
}

// проверка существования файла
void input_file_checker::check_file_exist(QString _full_file_name)
{
    QFile file(_full_file_name);

    if(file.exists() == false)
    {
        b_error = true;
        error_str = QString("File %1 not found").arg(_full_file_name);
    }
}

// проверка прав доступа к файлу
void input_file_checker::check_file_access(QString _full_file_name)
{
    QFile file(_full_file_name);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        b_error = true;
        error_str = QString("Can't open file %1").arg(_full_file_name);
    }
    else
    {
        file.close();
    }
}

// проверка корректности файла
void input_file_checker::check_file_well_formed(QString _full_file_name, QString * _file_data)
{
    QFile file;
    QTextStream text_stream_reader;
    QXmlStreamReader xml_stream_reader;
    bool b_well_formed_error;

    file.setFileName(_full_file_name);
    text_stream_reader.setDevice(&file);
    b_well_formed_error = false;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    _file_data[0] = text_stream_reader.readAll();
    file.close();
    xml_stream_reader.addData(_file_data[0]);

    while(!xml_stream_reader.atEnd())
    {
        xml_stream_reader.readNext();
        if(xml_stream_reader.hasError())
        {
            b_well_formed_error = true;
        }
    }

    if(b_well_formed_error == true)
    {
        b_error = true;
        error_str = QString("File %1 is not well-formed").arg(_full_file_name);
    }
}

// дополнительная проверка корректности xsd-файла
void input_file_checker::check_xsd_file_well_formed()
{
    QXmlSchema xsd_schema;
    bool b_xsd_well_formed_error;

    b_xsd_well_formed_error = false;

    if(xsd_schema.load(xsd_file_data.toLocal8Bit()) == false)
    {
        b_xsd_well_formed_error = true;
    }

    if(b_xsd_well_formed_error == true)
    {
        b_error = true;
        error_str = QString("File %1 is not xsd-well-formed").arg(xsd_full_file_name);
    }
}

// проверка валидности xml-файла xsd-схеме
void input_file_checker::check_xml_file_valid()
{
    bool b_valid_error;
    QXmlSchema xsd_schema;
    QXmlSchemaValidator validator;

    b_valid_error = false;

    xsd_schema.load(xsd_file_data.toLocal8Bit());
    validator.setSchema(xsd_schema);
    if(validator.validate(xml_file_data.toLocal8Bit()) == false)
    {
        b_valid_error = true;
    }

    if(b_valid_error == true)
    {
        b_error = true;
        error_str = QString("File %1 is not valid").arg(xml_full_file_name);
    }
}

// вывод на консоль текста ошибки
void input_file_checker::print_error_str()
{
    qDebug()<<error_str;
}

QString input_file_checker::ret_xml_full_file_name() // вернуть полное имя xml-файла
{
    return xml_full_file_name;
}

QString input_file_checker::ret_xsd_full_file_name() // вернуть полное имя xsd-файла
{
    return xsd_full_file_name;
}

QString input_file_checker::ret_xml_file_data() // вернуть содержимое xml-файла
{
    return xml_file_data;
}

QString input_file_checker::ret_xsd_file_data() // вернуть содержимое xsd-файла
{
    return xsd_file_data;
}

bool input_file_checker::ret_b_error() // вернуть признак наличия ошибки
{
    return b_error;
}

QString input_file_checker::ret_error_str() // вернуть текст ошибки
{
    return error_str;
}

void input_file_checker::set_xml_full_file_name(QString _xml_full_file_name) // установить полное имя xml-файла
{
    xml_full_file_name = _xml_full_file_name;
}

void input_file_checker::set_xsd_full_file_name(QString _xsd_full_file_name) // установить полное имя xsd-файла
{
    xsd_full_file_name = _xsd_full_file_name;
}

void input_file_checker::set_xml_file_data(QString _xml_file_data) // установить содержимое xml-файла
{
    xml_file_data = _xml_file_data;
}

void input_file_checker::set_xsd_file_data(QString _xsd_file_data) // установить содержимое xsd-файла
{
    xsd_file_data = _xsd_file_data;
}

void input_file_checker::set_b_error(bool _b_error) // установить признак наличия ошибки
{
    b_error = _b_error;
}

void input_file_checker::set_error_str(QString _error_str) // установить текст ошибки
{
    error_str = _error_str;
}
