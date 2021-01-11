#include "cell_data.h"

// конструктор
cell_data::cell_data(int _type,
                     bool _b_require,
                     QString _name)
{
    type = _type;
    value = "";
    b_require = _b_require;
    name = _name;
    text = "";
}

// деструктор
cell_data::~cell_data()
{
    type = 0;
    value = "";
    b_require = false;
    name = "";
    text = "";
}

// сгенерировать текст
void cell_data::generate_text(QString _indention)
{
    if(value == "")
    {
        text = "";
    }
    else
    {
        if(type == 0)
        {
            text = QString("%1 = '%2'").arg(name).arg(value);
        }
        else
        {
            text = QString("%1<%2>%3</%2>%4").arg(_indention).arg(name).arg(value).arg("\n");
        }
    }
}


int cell_data::ret_type() // вернуть вариант хранения данных
{
    return type;
}

QString cell_data::ret_value() // вернуть значение
{
    return value;
}

bool cell_data::ret_b_require() // вернуть признак обязательности
{
    return b_require;
}

QString cell_data::ret_name() // вернуть имя
{
    return name;
}

QString cell_data::ret_text() // вернуть текст
{
    return text;
}

void cell_data::set_type(int _type) // установить вариант хранения данных
{
    type = _type;
}

void cell_data::set_value(QString _value) // установить значение
{
    value = _value;
}

void cell_data::set_b_require(bool _b_require) // установить признак обязательности
{
    b_require = _b_require;
}

void cell_data::set_name(QString _name) // установить имя
{
    name = _name;
}

void cell_data::set_text(QString _text) // установить текст
{
    text = _text;
}
