#include "zone_point_row_data.h"

// конструктор
zone_point_row_data::zone_point_row_data()
{
    number = new cell_data(0, true, "number");
    x      = new cell_data(1, true, "x");
    y      = new cell_data(1, true, "y");

    next = NULL;
    prev = NULL;
}

// деструктор
zone_point_row_data::~zone_point_row_data()
{
    delete number;
    number = NULL;

    delete x;
    x = NULL;

    delete y;
    y = NULL;

    next = NULL;
    prev = NULL;
}

zone_point_row_data * zone_point_row_data::ret_next() // вернуть указатель на следующий элемент
{
    return next;
}

zone_point_row_data * zone_point_row_data::ret_prev() // вернуть указатель на предыдущий элемент
{
    return prev;
}

void zone_point_row_data::set_next(zone_point_row_data * _next) // установить указатель на следующий элемент
{
    next = _next;
}

void zone_point_row_data::set_prev(zone_point_row_data * _prev) // установить указатель на предыдущий элемент
{
    prev = _prev;
}

cell_data * zone_point_row_data::ret_number()
{
    return number;
}

cell_data * zone_point_row_data::ret_x()
{
    return x;
}

cell_data * zone_point_row_data::ret_y()
{
    return y;
}

void zone_point_row_data::set_number(cell_data * _number)
{
    number = _number;
}

void zone_point_row_data::set_x(cell_data * _x)
{
    x = _x;
}

void zone_point_row_data::set_y(cell_data * _y)
{
    y = _y;
}
