#include "cell_view_l_e.h"

#include <QDebug>

// конструктор
cell_view_l_e::cell_view_l_e(int _data_type,
                             int _validator_type,
                             bool _b_require,
                             QString _col_valid,
                             QString _col_error)
{
    data_type = _data_type;
    validator_type = _validator_type;
    value = "";
    b_require = _b_require;
    b_correct = false;
    col_valid = _col_valid;
    col_error = _col_error;
    i_v = NULL;
    d_v = NULL;

    l_e = new QLineEdit();
}

cell_view_l_e::~cell_view_l_e() // деструктор
{
    if(validator_type == 0)
    {
        delete i_v;
        i_v = NULL;
    }
    else if(validator_type == 1)
    {
        delete d_v;
        d_v = NULL;
    }

    delete l_e;
    l_e = NULL;

    data_type = 0;
    validator_type = 0;
    value = "";
    b_correct = false;
    b_require = false;
    col_valid = "";
    col_error = "";
}

void cell_view_l_e::set_validator_par()
{
    i_v = NULL;
    d_v = NULL;

    connect(l_e, SIGNAL(textChanged(QString)), SLOT(l_e_changed(QString)));
}

void cell_view_l_e::set_validator_par(int _validator_min, int _validator_max)
{
    i_v = new QIntValidator(_validator_min, _validator_max);
    i_v->setLocale(QLocale::English);
    l_e->setValidator(i_v);

    d_v = NULL;

    connect(l_e, SIGNAL(textChanged(QString)), SLOT(l_e_changed(QString)));
}

void cell_view_l_e::set_validator_par(double _validator_min, double _validator_max, int _decimals)
{
    i_v = NULL;

    d_v = new QDoubleValidator(_validator_min, _validator_max, _decimals);
    d_v->setNotation(QDoubleValidator::StandardNotation);
    d_v->setLocale(QLocale::English);
    l_e->setValidator(d_v);

    connect(l_e, SIGNAL(textChanged(QString)), SLOT(l_e_changed(QString)));
}

// покраска редактируемого поля
void cell_view_l_e::fill_color(bool _b_correct)
{
    QString str_stylesheet;

    if(_b_correct == true)
    {
        str_stylesheet = QString("QLineEdit{background-color:%1}").arg(col_valid);
    }
    else
    {
        str_stylesheet = QString("QLineEdit{background-color:%1}").arg(col_error);
    }

    l_e->setStyleSheet(str_stylesheet);
}

int cell_view_l_e::ret_data_type() // вернуть тип данных
{
    return data_type;
}

int cell_view_l_e::ret_validator_type() // вернуть тип валидатора
{
    return validator_type;
}

QString cell_view_l_e::ret_value() // вернуть значение
{
    return value;
}

bool cell_view_l_e::ret_b_correct() // вернуть признак корректности
{
    return b_correct;
}

bool cell_view_l_e::ret_b_require() // вернуть признак обязательности
{
    return b_require;
}

QString cell_view_l_e::ret_col_valid() // вернуть цвет корректного поля
{
    return col_valid;
}

QString cell_view_l_e::ret_col_error() // вернуть цвет ошибочного поля
{
    return col_error;
}

QIntValidator * cell_view_l_e::ret_i_v() // вернуть контрольное устройство проверки целых чисел

{
    return i_v;
}

QDoubleValidator * cell_view_l_e::ret_d_v() // вернуть контрольное устройство проверки нецелых чисел
{
    return d_v;
}

QLineEdit * cell_view_l_e::ret_l_e()// вернуть редактируемое поле
{
    return l_e;
}

void cell_view_l_e::set_data_type(int _data_type) // установить тип данных
{
    data_type = _data_type;
}

void cell_view_l_e::set_validator_type(int _validator_type) // установить тип валидатора
{
    validator_type = _validator_type;
}

void cell_view_l_e::set_value(QString _value) // установить значение
{
    value = _value;
}

void cell_view_l_e::set_b_correct(bool _b_correct) // установить признак корректности
{
    b_correct = _b_correct;
}

void cell_view_l_e::set_b_require(bool _b_require) // установить признак обязательности
{
    b_require = _b_require;
}

void cell_view_l_e::set_col_valid(QString _col_valid) // установить цвет корректного поля
{
    col_valid = _col_valid;
}

void cell_view_l_e::set_col_error(QString _col_error) // установить цвет ошибочного поля
{
    col_error = _col_error;
}

void cell_view_l_e::set_i_v(QIntValidator * _i_v) // установить контрольное устройство проверки целых чисел
{
    i_v = _i_v;
}

void cell_view_l_e::set_d_v(QDoubleValidator * _d_v) // установить контрольное устройство проверки нецелых чисел
{
    d_v = _d_v;
}

void cell_view_l_e::set_l_e(QLineEdit * _l_e) // установить редактируемое поле
{
    l_e = _l_e;
}

// вызывается при изменении текста редактируемого поля
void cell_view_l_e::l_e_changed(QString _value)
{
    value = _value;
//    l_e->setText(value);

    if(value == "" && b_require == false)
    {
        fill_color(true);
        b_correct = true;
        return;
    }
    else
    {
        if(l_e->hasAcceptableInput() == true)
        {
            fill_color(true);
            b_correct = true;
            return;
        }
        else
        {
            fill_color(false);
            b_correct = false;
            return;
        }
    }
}
