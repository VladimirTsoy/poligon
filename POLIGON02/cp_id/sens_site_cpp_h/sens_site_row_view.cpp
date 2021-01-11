#include "sens_site_row_view.h"

// конструктор
sens_site_row_view::sens_site_row_view()
{
    number = new cell_view_l_e  (0, 0,                           true,  "white", "pink");
    charSens = new cell_view_l_e(0, 0,                           true,  "white", "pink");
    x = new cell_view_l_e       (1, 1,                           false, "white", "pink");
    y = new cell_view_l_e       (1, 1,                           false, "white", "pink");

    number->set_validator_par  (1,       INT_MAX);
    charSens->set_validator_par(1,       INT_MAX);
    x->set_validator_par       (INT_MIN, INT_MAX, 2);
    y->set_validator_par       (INT_MIN, INT_MAX, 2);

    number->l_e_changed("");
    charSens->l_e_changed("");
    x->l_e_changed("");
    y->l_e_changed("");

    p_b_delete = new QPushButton();
    p_b_delete->setText("x");

    next = NULL;
    prev = NULL;
}

// деструктор
sens_site_row_view::~sens_site_row_view()
{
    delete number;
    number = NULL;

    delete charSens;
    charSens = NULL;

    delete x;
    x = NULL;

    delete y;
    y = NULL;

    delete p_b_delete;
    p_b_delete = NULL;

    next = NULL;
    prev = NULL;
}

sens_site_row_view * sens_site_row_view::ret_next() // вернуть указатель на следующий элемент
{
    return next;
}

sens_site_row_view * sens_site_row_view::ret_prev() // вернуть указатель на предыдущий элемент
{
    return prev;
}

void sens_site_row_view::set_next(sens_site_row_view * _next) // установить указатель на следующий элемент
{
    next = _next;
}

void sens_site_row_view::set_prev(sens_site_row_view * _prev) // установить указатель на предыдущий элемент
{
    prev = _prev;
}

cell_view_l_e * sens_site_row_view::ret_number()
{
    return number;
}

cell_view_l_e * sens_site_row_view::ret_charSens()
{
    return charSens;
}

cell_view_l_e * sens_site_row_view::ret_x()
{
    return x;
}

cell_view_l_e * sens_site_row_view::ret_y()
{
    return y;
}

QPushButton * sens_site_row_view::ret_p_b_delete()
{
    return p_b_delete;
}

void sens_site_row_view::set_number(cell_view_l_e * _number)
{
    number = _number;
}

void sens_site_row_view::set_charSens(cell_view_l_e * _charSens)
{
    charSens = _charSens;
}

void sens_site_row_view::set_x(cell_view_l_e * _x)
{
    x = _x;
}

void sens_site_row_view::set_y(cell_view_l_e * _y)
{
    y = _y;
}

void sens_site_row_view::set_p_b_delete(QPushButton * _p_b_delete)
{
    p_b_delete = _p_b_delete;
}
