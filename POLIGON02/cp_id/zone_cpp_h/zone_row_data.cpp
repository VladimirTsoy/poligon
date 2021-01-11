#include "zone_row_data.h"

// конструктор
zone_row_data::zone_row_data()
{
    number     = new cell_data(0, true, "number");
    r          = new cell_data(1, true, "r");
    g          = new cell_data(1, true, "g");
    b          = new cell_data(1, true, "b");
    a          = new cell_data(1, true, "a");

    next = NULL;
    prev = NULL;

    first = NULL;
    last = NULL;
}

// деструктор
zone_row_data::~zone_row_data()
{
    delete number;
    number = NULL;

    delete r;
    r = NULL;

    delete g;
    g = NULL;

    delete b;
    b = NULL;

    delete a;
    a = NULL;

    next = NULL;
    prev = NULL;

    clear_list();

    first = NULL;
    last = NULL;
}

// добавление нового элемента в список точек
void zone_row_data::add_new_element()
{
    if(first == NULL)
    {
        last = new zone_point_row_data();
        first = last;
    }
    else
    {
        zone_point_row_data * ptr_new_element;
        ptr_new_element = new zone_point_row_data();
        last->set_next(ptr_new_element);
        ptr_new_element->set_prev(last);
        last = ptr_new_element;
    }
}

// очистка списка точек
void zone_row_data::clear_list()
{
    zone_point_row_data * iter;
    iter = first;
    zone_point_row_data * iter_delete;

    while(iter != NULL)
    {
        iter_delete = iter;
        iter = iter->ret_next();
        delete iter_delete;
    }
}

zone_row_data * zone_row_data::ret_next() // вернуть указатель на следующую зону
{
    return next;
}

zone_row_data * zone_row_data::ret_prev() // вернуть указатель на предыдущую зону
{
    return prev;
}

zone_point_row_data * zone_row_data::ret_first() // вернуть указатель на первую точку
{
    return first;
}

zone_point_row_data * zone_row_data::ret_last() // вернуть указатель на последнюю точку
{
    return last;
}

void zone_row_data::set_next(zone_row_data * _next) // установить указатель на следующую зону
{
    next = _next;
}

void zone_row_data::set_prev(zone_row_data * _prev) // установить указатель на предыдущую зону
{
    prev = _prev;
}

void zone_row_data::set_first(zone_point_row_data * _first) // установить указатель на первую точку
{
    first = _first;
}

void zone_row_data::set_last(zone_point_row_data * _last) // установить указатель на последнюю точку
{
    last = _last;
}

cell_data * zone_row_data::ret_number()
{
    return number;
}

cell_data * zone_row_data::ret_r()
{
    return r;
}

cell_data * zone_row_data::ret_g()
{
    return g;
}

cell_data * zone_row_data::ret_b()
{
    return b;
}

cell_data * zone_row_data::ret_a()
{
    return a;
}

void zone_row_data::set_number(cell_data * _number)
{
    number = _number;
}

void zone_row_data::set_r(cell_data * _r)
{
    r = _r;
}

void zone_row_data::set_g(cell_data * _g)
{
    g = _g;
}

void zone_row_data::set_b(cell_data * _b)
{
    b = _b;
}

void zone_row_data::set_a(cell_data * _a)
{
    a = _a;
}
