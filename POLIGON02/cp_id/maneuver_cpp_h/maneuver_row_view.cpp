#include "maneuver_row_view.h"

// конструктор
maneuver_row_view::maneuver_row_view()
{
    number = new cell_view_l_e(0, 0, true, "white", "pink");
    number->set_validator_par(1,INT_MAX);
    number->l_e_changed("");

    tStart = new cell_view_l_e(1, 1, true, "white", "pink");
    tStart->set_validator_par(0.0,INT_MAX,2);
    tStart->l_e_changed("");

    tFinish = new cell_view_l_e(1, 1, true, "white", "pink");
    tFinish->set_validator_par(0.0,INT_MAX,2);
    tFinish->l_e_changed("");

    a = new cell_view_l_e(1, 1, true, "white", "pink");
    a->set_validator_par(INT_MIN,INT_MAX,2);
    a->l_e_changed("");

    vh = new cell_view_l_e(1, 1, true, "white", "pink");
    vh->set_validator_par(INT_MIN,INT_MAX,2);
    vh->l_e_changed("");

    r = new cell_view_l_e(1, 1, true, "white", "pink");
    r->set_validator_par(INT_MIN,INT_MAX,2);
    r->l_e_changed("");

    p_b_delete = new QPushButton();
    p_b_delete->setText("x");

    next = NULL;
    prev = NULL;
}

// деструктор
maneuver_row_view::~maneuver_row_view()
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

    delete p_b_delete;
    p_b_delete = NULL;

    next = NULL;
    prev = NULL;
}

maneuver_row_view * maneuver_row_view::ret_next() // вернуть указатель на следующий элемент
{
    return next;
}

maneuver_row_view * maneuver_row_view::ret_prev() // вернуть указатель на предыдущий элемент
{
    return prev;
}

void maneuver_row_view::set_next(maneuver_row_view * _next) // установить указатель на следующий элемент
{
    next = _next;
}

void maneuver_row_view::set_prev(maneuver_row_view * _prev) // установить указатель на предыдущий элемент
{
    prev = _prev;
}

cell_view_l_e * maneuver_row_view::ret_number()
{
    return number;
}

cell_view_l_e * maneuver_row_view::ret_tStart()
{
    return tStart;
}

cell_view_l_e * maneuver_row_view::ret_tFinish()
{
    return tFinish;
}

cell_view_l_e * maneuver_row_view::ret_a()
{
    return a;
}

cell_view_l_e * maneuver_row_view::ret_vh()
{
    return vh;
}

cell_view_l_e * maneuver_row_view::ret_r()
{
    return r;
}

QPushButton * maneuver_row_view::ret_p_b_delete()
{
    return p_b_delete;
}

void maneuver_row_view::set_number(cell_view_l_e * _number)
{
    number = _number;
}

void maneuver_row_view::set_tStart(cell_view_l_e * _tStart)
{
    tStart = _tStart;
}

void maneuver_row_view::set_tFinish(cell_view_l_e * _tFinish)
{
    tFinish = _tFinish;
}

void maneuver_row_view::set_a(cell_view_l_e * _a)
{
    a = _a;
}

void maneuver_row_view::set_vh(cell_view_l_e * _vh)
{
    vh = _vh;
}

void maneuver_row_view::set_r(cell_view_l_e * _r)
{
    r = _r;
}

void maneuver_row_view::set_p_b_delete(QPushButton * _p_b_delete)
{
    p_b_delete = _p_b_delete;
}
