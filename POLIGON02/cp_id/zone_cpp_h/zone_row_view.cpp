#include "zone_row_view.h"

// конструктор
zone_row_view::zone_row_view()
{
    number     = new cell_view_l_e(0, 0, true,  "white", "pink");
    countPoint = new cell_view_l_e(0, 0, true,  "white", "pink");
    r          = new cell_view_l_e(0, 0, true,  "white", "pink");
    g          = new cell_view_l_e(0, 0, true,  "white", "pink");
    b          = new cell_view_l_e(0, 0, true,  "white", "pink");
    a          = new cell_view_l_e(0, 0, true,  "white", "pink");
    color      = new cell_view_l_e(0, 0, false, "white", "pink");

    number->set_validator_par    (1, INT_MAX);
    countPoint->set_validator_par(3, INT_MAX);
    r->set_validator_par         (0, 255);
    g->set_validator_par         (0, 255);
    b->set_validator_par         (0, 255);
    a->set_validator_par         (0, 255);
    color->set_validator_par     ();

    number->l_e_changed("");
    countPoint->l_e_changed("");
    r->l_e_changed("");
    g->l_e_changed("");
    b->l_e_changed("");
    a->l_e_changed("");
    color->l_e_changed("");

    countPoint->ret_l_e()->setReadOnly(true);
    color->ret_l_e()->setReadOnly(true);

    p_b_add = new QPushButton();
    p_b_add->setText("+");

    p_b_delete = new QPushButton();
    p_b_delete->setText("x");

    next = NULL;
    prev = NULL;

    first = NULL;
    last = NULL;

    connect(r->ret_l_e(), SIGNAL(textChanged(QString)), SLOT(fill_color(QString)));
    connect(g->ret_l_e(), SIGNAL(textChanged(QString)), SLOT(fill_color(QString)));
    connect(b->ret_l_e(), SIGNAL(textChanged(QString)), SLOT(fill_color(QString)));
    connect(a->ret_l_e(), SIGNAL(textChanged(QString)), SLOT(fill_color(QString)));
}

// деструктор
zone_row_view::~zone_row_view()
{
    delete number;
    number = NULL;

    delete countPoint;
    countPoint = NULL;

    delete r;
    r = NULL;

    delete g;
    g = NULL;

    delete b;
    b = NULL;

    delete a;
    a = NULL;

    delete color;
    color = NULL;

    delete p_b_add;
    p_b_add = NULL;

    delete p_b_delete;
    p_b_delete = NULL;

    next = NULL;
    prev = NULL;

    clear_list();

    first = NULL;
    last = NULL;
}

// добавление нового элемента в список точек
void zone_row_view::add_new_element()
{
    if(first == NULL)
    {
        last = new zone_point_row_view();
        first = last;
    }
    else
    {
        zone_point_row_view * ptr_new_element;
        ptr_new_element = new zone_point_row_view();
        last->set_next(ptr_new_element);
        ptr_new_element->set_prev(last);
        last = ptr_new_element;
    }

    countPoint->set_value(QString("%1").arg(countPoint->ret_value().toInt()+1));
    countPoint->l_e_changed(countPoint->ret_value());
    countPoint->ret_l_e()->setText(countPoint->ret_value());
}

// очистка списка точек
void zone_row_view::clear_list()
{
    zone_point_row_view * iter;
    iter = first;
    zone_point_row_view * iter_delete;

    while(iter != NULL)
    {
        iter_delete = iter;
        iter = iter->ret_next();
        delete iter_delete;
    }
}

zone_row_view * zone_row_view::ret_next() // вернуть указатель на следующую зону
{
    return next;
}

zone_row_view * zone_row_view::ret_prev() // вернуть указатель на предыдущую зону
{
    return prev;
}

zone_point_row_view * zone_row_view::ret_first() // вернуть указатель на первую точку
{
    return first;
}

zone_point_row_view * zone_row_view::ret_last() // вернуть указатель на последнюю точку
{
    return last;
}

void zone_row_view::set_next(zone_row_view * _next) // установить указатель на следующую зону
{
    next = _next;
}

void zone_row_view::set_prev(zone_row_view * _prev) // установить указатель на предыдущую зону
{
    prev = _prev;
}

void zone_row_view::set_first(zone_point_row_view * _first) // установить указатель на первую точку
{
    first = _first;
}

void zone_row_view::set_last(zone_point_row_view * _last) // установить указатель на последнюю точку
{
    last = _last;
}

cell_view_l_e * zone_row_view::ret_number()
{
    return number;
}

cell_view_l_e * zone_row_view::ret_countPoint()
{
    return countPoint;
}

cell_view_l_e * zone_row_view::ret_r()
{
    return r;
}

cell_view_l_e * zone_row_view::ret_g()
{
    return g;
}

cell_view_l_e * zone_row_view::ret_b()
{
    return b;
}

cell_view_l_e * zone_row_view::ret_a()
{
    return a;
}

cell_view_l_e * zone_row_view::ret_color()
{
    return color;
}

QPushButton * zone_row_view::ret_p_b_add()
{
    return p_b_add;
}

QPushButton * zone_row_view::ret_p_b_delete()
{
    return p_b_delete;
}

void zone_row_view::set_number(cell_view_l_e * _number)
{
    number = _number;
}

void zone_row_view::set_countPoint(cell_view_l_e * _countPoint)
{
    countPoint = _countPoint;
}

void zone_row_view::set_r(cell_view_l_e * _r)
{
    r = _r;
}

void zone_row_view::set_g(cell_view_l_e * _g)
{
    g = _g;
}

void zone_row_view::set_b(cell_view_l_e * _b)
{
    b = _b;
}

void zone_row_view::set_a(cell_view_l_e * _a)
{
    a = _a;
}

void zone_row_view::set_color(cell_view_l_e * _color)
{
    color = _color;
}

void zone_row_view::set_p_b_add(QPushButton * _p_b_add)
{
    p_b_add = _p_b_add;
}

void zone_row_view::set_p_b_delete(QPushButton * _p_b_delete)
{
    p_b_delete = _p_b_delete;
}

void zone_row_view::fill_color(QString)
{
    if(r->ret_l_e()->text() != "" &&
       g->ret_l_e()->text() != "" &&
       b->ret_l_e()->text() != "" &&
       a->ret_l_e()->text() != "")
    {
        QString str_color_stylesheet;
        str_color_stylesheet = QString("QLineEdit{background-color: rgba(%1,%2,%3,%4)}").arg(r->ret_value())
                                                                                        .arg(g->ret_value())
                                                                                        .arg(b->ret_value())
                                                                                        .arg(a->ret_value());
        color->ret_l_e()->setStyleSheet(str_color_stylesheet);
    }
}
