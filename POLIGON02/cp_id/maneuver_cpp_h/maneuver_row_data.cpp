#include "maneuver_row_data.h"

// конструктор
maneuver_row_data::maneuver_row_data()
{
    number = new cell_data  (0, true, "number");
    tStart = new cell_data  (1, true, "tStart");
    tFinish = new cell_data (1, true, "tFinish");
    a = new cell_data       (1, true, "a");
    vh = new cell_data      (1, true, "vh");
    r = new cell_data       (1, true, "r");

    next = NULL;
    prev = NULL;
}

// деструктор
maneuver_row_data::~maneuver_row_data()
{
    delete number;
    number = NULL;

    delete tStart;
    tStart = NULL;

    delete tFinish;
    tFinish = NULL;

    delete a;
    a = NULL;

    delete vh;
    vh = NULL;

    delete r;
    r = NULL;

    next = NULL;
    prev = NULL;
}

maneuver_row_data * maneuver_row_data::ret_next() // вернуть указатель на следующий элемент
{
    return next;
}

maneuver_row_data * maneuver_row_data::ret_prev() // вернуть указатель на предыдущий элемент
{
    return prev;
}

void maneuver_row_data::set_next(maneuver_row_data * _next) // установить указатель на следующий элемент
{
    next = _next;
}

void maneuver_row_data::set_prev(maneuver_row_data * _prev) // установить указатель на предыдущий элемент
{
    prev = _prev;
}

cell_data * maneuver_row_data::ret_number()
{
    return number;
}

cell_data * maneuver_row_data::ret_tStart()
{
    return tStart;
}

cell_data * maneuver_row_data::ret_tFinish()
{
    return tFinish;
}

cell_data * maneuver_row_data::ret_a()
{
    return a;
}

cell_data * maneuver_row_data::ret_vh()
{
    return vh;
}

cell_data * maneuver_row_data::ret_r()
{
    return r;
}

void maneuver_row_data::set_number(cell_data * _number)
{
    number = _number;
}

void maneuver_row_data::set_tStart(cell_data * _tStart)
{
    tStart = _tStart;
}

void maneuver_row_data::set_tFinish(cell_data * _tFinish)
{
    tFinish = _tFinish;
}

void maneuver_row_data::set_a(cell_data * _a)
{
    a = _a;
}

void maneuver_row_data::set_vh(cell_data * _vh)
{
    vh = _vh;
}

void maneuver_row_data::set_r(cell_data * _r)
{
    r = _r;
}
