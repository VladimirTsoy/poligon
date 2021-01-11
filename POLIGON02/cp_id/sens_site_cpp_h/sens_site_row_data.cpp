#include "sens_site_row_data.h"

// конструктор
sens_site_row_data::sens_site_row_data()
{
    number = new cell_data   (0, true,  "number");
    charSens = new cell_data (1, true,  "sensChar");
    x = new cell_data        (1, false, "x");
    y = new cell_data        (1, false, "y");

    next = NULL;
    prev = NULL;
}

// деструктор
sens_site_row_data::~sens_site_row_data()
{
    delete number;
    number = NULL;

    delete charSens;
    charSens = NULL;

    delete x;
    x = NULL;

    delete y;
    y = NULL;

    next = NULL;
    prev = NULL;
}

sens_site_row_data * sens_site_row_data::ret_next() // вернуть указатель на следующий элемент
{
    return next;
}

sens_site_row_data * sens_site_row_data::ret_prev() // вернуть указатель на предыдущий элемент
{
    return prev;
}

void sens_site_row_data::set_next(sens_site_row_data * _next) // установить указатель на следующий элемент
{
    next = _next;
}

void sens_site_row_data::set_prev(sens_site_row_data * _prev) // установить указатель на предыдущий элемент
{
    prev = _prev;
}

cell_data * sens_site_row_data::ret_number()
{
    return number;
}

cell_data * sens_site_row_data::ret_charSens()
{
    return charSens;
}

cell_data * sens_site_row_data::ret_x()
{
    return x;
}

cell_data * sens_site_row_data::ret_y()
{
    return y;
}

void sens_site_row_data::set_number(cell_data * _number)
{
    number = _number;
}

void sens_site_row_data::set_charSens(cell_data * _charSens)
{
    charSens = _charSens;
}

void sens_site_row_data::set_x(cell_data * _x)
{
    x = _x;
}

void sens_site_row_data::set_y(cell_data * _y)
{
    y = _y;
}
