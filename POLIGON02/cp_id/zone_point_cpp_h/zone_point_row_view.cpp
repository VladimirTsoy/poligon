#include "zone_point_row_view.h"

// конструктор
zone_point_row_view::zone_point_row_view()
{
    number = new cell_view_l_e(0, 0, true,  "white", "pink");
    x      = new cell_view_l_e(0, 0, true,  "white", "pink");
    y      = new cell_view_l_e(0, 0, true,  "white", "pink");

    number->set_validator_par(1,      INT_MAX);
    x->set_validator_par     (INT_MIN,INT_MAX);
    y->set_validator_par     (INT_MIN,INT_MAX);

    number->l_e_changed("");
    x->l_e_changed("");
    y->l_e_changed("");

    p_b_delete = new QPushButton();
    p_b_delete->setText("x");

    next = NULL;
    prev = NULL;
}

// деструктор
zone_point_row_view::~zone_point_row_view()
{
    delete number;
    number = NULL;

    delete x;
    x = NULL;

    delete y;
    y = NULL;

    delete p_b_delete;
    p_b_delete = NULL;

    next = NULL;
    prev = NULL;
}

zone_point_row_view * zone_point_row_view::ret_next() // вернуть указатель на следующий элемент
{
    return next;
}

zone_point_row_view * zone_point_row_view::ret_prev() // вернуть указатель на предыдущий элемент
{
    return prev;
}

void zone_point_row_view::set_next(zone_point_row_view * _next) // установить указатель на следующий элемент
{
    next = _next;
}

void zone_point_row_view::set_prev(zone_point_row_view * _prev) // установить указатель на предыдущий элемент
{
    prev = _prev;
}

cell_view_l_e * zone_point_row_view::ret_number()
{
    return number;
}

cell_view_l_e * zone_point_row_view::ret_x()
{
    return x;
}

cell_view_l_e * zone_point_row_view::ret_y()
{
    return y;
}

QPushButton * zone_point_row_view::ret_p_b_delete()
{
    return p_b_delete;
}

void zone_point_row_view::set_number(cell_view_l_e * _number)
{
    number = _number;
}

void zone_point_row_view::set_x(cell_view_l_e * _x)
{
    x = _x;
}

void zone_point_row_view::set_y(cell_view_l_e * _y)
{
    y = _y;
}

void zone_point_row_view::set_p_b_delete(QPushButton * _p_b_delete)
{
    p_b_delete = _p_b_delete;
}
