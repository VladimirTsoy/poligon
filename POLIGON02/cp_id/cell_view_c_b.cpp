#include "cell_view_c_b.h"

// конструктор
cell_view_c_b::cell_view_c_b(QStringList _s_l,
                             bool _b_require,
                             QString _col_valid,
                             QString _col_error)
{
    value = "";
    b_require = _b_require;
    b_correct = false;
    col_valid = _col_valid;
    col_error = _col_error;
    s_l = _s_l;
    c_b = new QComboBox();
    c_b->addItems(s_l);
    connect(c_b, SIGNAL(currentTextChanged(QString)), SLOT(c_b_changed(QString)));
}

cell_view_c_b::~cell_view_c_b() // деструктор
{
    value = "";
    b_require = false;
    b_correct = false;
    col_valid = "";
    col_error = "";
    s_l.clear();
    delete c_b;
    c_b = NULL;
}

// очистить элементы выбора выпадающего списка
void cell_view_c_b::clear_c_b_variant()
{
    c_b->clear();
}

// покраска выпадающего списка
void cell_view_c_b::fill_color(bool _b_correct)
{
    QString str_stylesheet;

    if(_b_correct == true)
    {
        str_stylesheet = QString("QComboBox{background:%1; selection-background-color: green;}").arg(col_valid);
    }
    else
    {
        str_stylesheet = QString("QComboBox{background:%1; selection-background-color: green;}").arg(col_error);
    }

    c_b->setStyleSheet(str_stylesheet);
}

QString cell_view_c_b::ret_value() // вернуть значение
{
    return value;
}

bool cell_view_c_b::ret_b_require() // вернуть признак обязательности
{
    return b_require;
}

bool cell_view_c_b::ret_b_correct() // вернуть признак корректности
{
    return b_correct;
}

QString cell_view_c_b::ret_col_valid() // вернуть цвет корректного поля
{
    return col_valid;
}

QString cell_view_c_b::ret_col_error() // вернуть цвет ошибочного поля
{
    return col_error;
}

QStringList cell_view_c_b::ret_s_l() // вернуть список строк возможных значений элементов выпадающего списка
{
    return s_l;
}

QComboBox * cell_view_c_b::ret_c_b() // вернуть выпадающий список
{
    return c_b;
}

void cell_view_c_b::set_value(QString _value) // установить значение
{
    value = _value;
}

void cell_view_c_b::set_b_require(bool _b_require) // установить признак обязательности
{
    b_require = _b_require;
}

void cell_view_c_b::set_b_correct(bool _b_correct) // установить признак корректности
{
    b_correct = _b_correct;
}

void cell_view_c_b::set_col_valid(QString _col_valid) // установить цвет корректного поля
{
    col_valid = _col_valid;
}

void cell_view_c_b::set_col_error(QString _col_error) // установить цвет ошибочного поля
{
    col_error = _col_error;
}

void cell_view_c_b::set_s_l(QStringList _s_l) // установить список строк возможных значений элементов выпадающего списка
{
    s_l = _s_l;
}

void cell_view_c_b::set_c_b(QComboBox * _c_b) // установить выпадающий список
{
    c_b = _c_b;
}

// вызывается при изменении элемента в выпадающем списке
void cell_view_c_b::c_b_changed(QString _value)
{
    value = _value;

    fill_color(false);
    b_correct = false;

    for(int i=0; i<s_l.size(); i++)
    {
        if(s_l[i] == _value)
        {
            fill_color(true);
            c_b->setEditable(true);
            c_b->setEditText(value);
            b_correct = true;
            break;
        }
    }

    if(b_correct == false)
    {
        c_b->setEditable(true);
        c_b->setEditText("Ошибка");
    }
    else
    {
        c_b->setEditable(false);
    }
}
