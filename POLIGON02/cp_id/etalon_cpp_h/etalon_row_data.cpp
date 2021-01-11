#include "etalon_row_data.h"

// конструктор
etalon_row_data::etalon_row_data()
{
    number = new cell_data          (0, true,  "number");
    ObjClass = new cell_data        (1, true,  "ObjClass");
    TO = new cell_data              (1, true,  "TO");
    IO = new cell_data              (1, true,  "IO");
    OGP = new cell_data             (1, true,  "OGP");
    tStart = new cell_data          (1, true,  "tStart");
    tFinish = new cell_data         (1, true,  "tFinish");
    x = new cell_data               (1, true,  "x");
    y = new cell_data               (1, true,  "y");
    h = new cell_data               (1, true,  "h");
    psi = new cell_data             (1, true,  "psi");
    v = new cell_data               (1, true,  "v");
    vh = new cell_data              (1, true,  "vh");

    next = NULL;
    prev = NULL;

    first = NULL;
    last = NULL;
}

// деструктор
etalon_row_data::~etalon_row_data()
{
    delete number;
    number = NULL;

    delete ObjClass;
    ObjClass = NULL;

    delete TO;
    TO = NULL;

    delete IO;
    IO = NULL;

    delete OGP;
    OGP = NULL;

    delete tStart;
    tStart = NULL;

    delete tFinish;
    tFinish = NULL;

    delete x;
    x = NULL;

    delete y;
    y = NULL;

    delete h;
    h = NULL;

    delete psi;
    psi = NULL;

    delete v;
    v = NULL;

    delete vh;
    vh = NULL;

    next = NULL;
    prev = NULL;

    clear_list();

    first = NULL;
    last = NULL;
}

// добавление нового элемента в список
void etalon_row_data::add_new_element()
{
    if(first == NULL)
    {
        last = new maneuver_row_data();
        first = last;
    }
    else
    {
        maneuver_row_data * ptr_new_element;
        ptr_new_element = new maneuver_row_data();
        last->set_next(ptr_new_element);
        ptr_new_element->set_prev(last);
        last = ptr_new_element;
    }
}

// очистка списка
void etalon_row_data::clear_list()
{
    maneuver_row_data * iter;
    iter = first;
    maneuver_row_data * iter_delete;

    while(iter != NULL)
    {
        iter_delete = iter;
        iter = iter->ret_next();
        delete iter_delete;
    }
}

etalon_row_data * etalon_row_data::ret_next() // вернуть указатель на следующий элемент
{
    return next;
}

etalon_row_data * etalon_row_data::ret_prev() // вернуть указатель на предыдущий элемент
{
    return prev;
}

maneuver_row_data * etalon_row_data::ret_first() // вернуть указатель на первый маневр
{
    return first;
}

maneuver_row_data * etalon_row_data::ret_last() // вернуть указатель на последний маневр
{
    return last;
}

void etalon_row_data::set_next(etalon_row_data * _next) // установить указатель на следующий элемент
{
    next = _next;
}

void etalon_row_data::set_prev(etalon_row_data * _prev) // установить указатель на предыдущий элемент
{
    prev = _prev;
}

void etalon_row_data::set_first(maneuver_row_data * _first) // установить указатель на первый маневр
{
    first = _first;
}

void etalon_row_data::set_last(maneuver_row_data * _last) // установить указатель на последний маневр
{
    last = _last;
}

cell_data * etalon_row_data::ret_number()
{
    return number;
}

cell_data * etalon_row_data::ret_ObjClass()
{
    return ObjClass;
}

cell_data * etalon_row_data::ret_TO()
{
    return TO;
}

cell_data * etalon_row_data::ret_IO()
{
    return IO;
}

cell_data * etalon_row_data::ret_OGP()
{
    return OGP;
}

cell_data * etalon_row_data::ret_tStart()
{
    return tStart;
}

cell_data * etalon_row_data::ret_tFinish()
{
    return tFinish;
}

cell_data * etalon_row_data::ret_x()
{
    return x;
}

cell_data * etalon_row_data::ret_y()
{
    return y;
}

cell_data * etalon_row_data::ret_h()
{
    return h;
}

cell_data * etalon_row_data::ret_psi()
{
    return psi;
}

cell_data * etalon_row_data::ret_v()
{
    return v;
}

cell_data * etalon_row_data::ret_vh()
{
    return vh;
}

void etalon_row_data::set_ObjClass(cell_data * _ObjClass)
{
    ObjClass = _ObjClass;
}

void etalon_row_data::set_TO(cell_data * _TO)
{
    TO = _TO;
}

void etalon_row_data::set_IO(cell_data * _IO)
{
    IO = _IO;
}

void etalon_row_data::set_OGP(cell_data * _OGP)
{
    OGP = _OGP;
}

void etalon_row_data::set_tStart(cell_data * _tStart)
{
    tStart = _tStart;
}

void etalon_row_data::set_tFinish(cell_data * _tFinish)
{
    tFinish = _tFinish;
}

void etalon_row_data::set_x(cell_data * _x)
{
    x = _x;
}

void etalon_row_data::set_y(cell_data * _y)
{
    y = _y;
}

void etalon_row_data::set_h(cell_data * _h)
{
    h = _h;
}

void etalon_row_data::set_psi(cell_data * _psi)
{
    psi = _psi;
}

void etalon_row_data::set_v(cell_data * _v)
{
    v = _v;
}

void etalon_row_data::set_vh(cell_data * _vh)
{
    vh = _vh;
}
