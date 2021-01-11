#include "etalon_row_view.h"

// конструктор
etalon_row_view::etalon_row_view()
{
    number = new cell_view_l_e         (0, 0,                           true,  "white", "pink");
    ObjClass = new cell_view_c_b       (ret_etalon_s_l_ObjClass_view(), true,  "white", "pink");
    TO = new cell_view_c_b             (ret_etalon_s_l_TO_Air_view(),   true,  "white", "pink");
    IO = new cell_view_c_b             (ret_etalon_s_l_IO_view(),       true,  "white", "pink");
    OGP = new cell_view_c_b            (ret_etalon_s_l_OGP_view(),      true,  "white", "pink");
    tStart = new cell_view_l_e         (1, 1,                           true,  "white", "pink");
    tFinish = new cell_view_l_e        (1, 1,                           true,  "white", "pink");
    x = new cell_view_l_e              (1, 1,                           true,  "white", "pink");
    y = new cell_view_l_e              (1, 1,                           true,  "white", "pink");
    h = new cell_view_l_e              (1, 1,                           true,  "white", "pink");
    psi = new cell_view_l_e            (1, 1,                           true,  "white", "pink");
    v = new cell_view_l_e              (1, 1,                           true,  "white", "pink");
    vh = new cell_view_l_e             (1, 1,                           true,  "white", "pink");
    etalon_number = new cell_view_l_e  (0, 0,                           true,  "white", "pink");
    countManevr = new cell_view_l_e    (0, 0,                           true,  "white", "pink");

    number->set_validator_par         (1,       INT_MAX);
    tStart->set_validator_par         (0.0,     INT_MAX, 2);
    tFinish->set_validator_par        (0.0,     INT_MAX, 2);
    x->set_validator_par              (INT_MIN, INT_MAX, 2);
    y->set_validator_par              (INT_MIN, INT_MAX, 2);
    h->set_validator_par              (0.0,     INT_MAX, 2);
    psi->set_validator_par            (0.0,     360.0,   2);
    v->set_validator_par              (0.0,     INT_MAX, 2);
    vh->set_validator_par             (INT_MIN, INT_MAX, 2);
    etalon_number->set_validator_par  (1,       INT_MAX);
    countManevr->set_validator_par    (0,       INT_MAX);

    number->l_e_changed("");
    ObjClass->c_b_changed(ObjClass->ret_s_l().at(0));
    TO->c_b_changed(TO->ret_s_l().at(0));
    IO->c_b_changed(IO->ret_s_l().at(0));
    OGP->c_b_changed(OGP->ret_s_l().at(0));
    tStart->l_e_changed("");
    tFinish->l_e_changed("");
    x->l_e_changed("");
    y->l_e_changed("");
    h->l_e_changed("");
    psi->l_e_changed("");
    v->l_e_changed("");
    vh->l_e_changed("");
    etalon_number->l_e_changed("");
    countManevr->l_e_changed("");

    etalon_number->ret_l_e()->setReadOnly(true);
    countManevr->ret_l_e()->setReadOnly(true);

    p_b_delete = new QPushButton();
    p_b_delete->setText("x");

    p_b_add_maneuver = new QPushButton();
    p_b_add_maneuver->setText("+");

    next = NULL;
    prev = NULL;

    first = NULL;
    last = NULL;

    connect(ObjClass->ret_c_b(), SIGNAL(currentTextChanged(QString)), this, SLOT(obj_class_c_b_changed(QString)));
    connect(number->ret_l_e(), SIGNAL(textChanged(QString)), this, SLOT(number_changed(QString)));
}

// деструктор
etalon_row_view::~etalon_row_view()
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

    delete countManevr;
    countManevr = NULL;

    delete p_b_add_maneuver;
    p_b_add_maneuver = NULL;

    delete p_b_delete;
    p_b_delete = NULL;

    next = NULL;
    prev = NULL;

    clear_list();

    first = NULL;
    last = NULL;
}

// добавление нового элемента в список
void etalon_row_view::add_new_element()
{
    if(first == NULL)
    {
        last = new maneuver_row_view();
        first = last;
    }
    else
    {
        maneuver_row_view * ptr_new_element;
        ptr_new_element = new maneuver_row_view();
        last->set_next(ptr_new_element);
        ptr_new_element->set_prev(last);
        last = ptr_new_element;
    }

    countManevr->set_value(QString("%1").arg(countManevr->ret_value().toInt()+1));
    countManevr->l_e_changed(countManevr->ret_value());
    countManevr->ret_l_e()->setText(countManevr->ret_value());
}

// очистка списка
void etalon_row_view::clear_list()
{
    maneuver_row_view * iter;
    iter = first;
    maneuver_row_view * iter_delete;

    while(iter != NULL)
    {
        iter_delete = iter;
        iter = iter->ret_next();
        delete iter_delete;
    }
}

etalon_row_view * etalon_row_view::ret_next() // вернуть указатель на следующий элемент
{
    return next;
}

etalon_row_view * etalon_row_view::ret_prev() // вернуть указатель на предыдущий элемент
{
    return prev;
}

maneuver_row_view * etalon_row_view::ret_first() // вернуть указатель на первый маневр
{
    return first;
}

maneuver_row_view * etalon_row_view::ret_last() // вернуть указатель на последний маневр
{
    return last;
}

void etalon_row_view::set_next(etalon_row_view * _next) // установить указатель на следующий элемент
{
    next = _next;
}

void etalon_row_view::set_prev(etalon_row_view * _prev) // установить указатель на предыдущий элемент
{
    prev = _prev;
}

void etalon_row_view::set_first(maneuver_row_view * _first) // установить указатель на первый маневр
{
    first = _first;
}

void etalon_row_view::set_last(maneuver_row_view * _last) // установить указатель на последний маневр
{
    last = _last;
}

cell_view_l_e * etalon_row_view::ret_number()
{
    return number;
}

cell_view_c_b * etalon_row_view::ret_ObjClass()
{
    return ObjClass;
}

cell_view_c_b * etalon_row_view::ret_TO()
{
    return TO;
}

cell_view_c_b * etalon_row_view::ret_IO()
{
    return IO;
}

cell_view_c_b * etalon_row_view::ret_OGP()
{
    return OGP;
}

cell_view_l_e * etalon_row_view::ret_tStart()
{
    return tStart;
}

cell_view_l_e * etalon_row_view::ret_tFinish()
{
    return tFinish;
}

cell_view_l_e * etalon_row_view::ret_x()
{
    return x;
}

cell_view_l_e * etalon_row_view::ret_y()
{
    return y;
}

cell_view_l_e * etalon_row_view::ret_h()
{
    return h;
}

cell_view_l_e * etalon_row_view::ret_psi()
{
    return psi;
}

cell_view_l_e * etalon_row_view::ret_v()
{
    return v;
}

cell_view_l_e * etalon_row_view::ret_vh()
{
    return vh;
}

QPushButton * etalon_row_view::ret_p_b_delete()
{
    return p_b_delete;
}

cell_view_l_e * etalon_row_view::ret_etalon_number()
{
    return etalon_number;
}

cell_view_l_e * etalon_row_view::ret_countManevr()
{
    return countManevr;
}

QPushButton * etalon_row_view::ret_p_b_add_maneuver()
{
    return p_b_add_maneuver;
}

void etalon_row_view::set_number(cell_view_l_e * _number)
{
    number = _number;
}

void etalon_row_view::set_ObjClass(cell_view_c_b * _ObjClass)
{
    ObjClass = _ObjClass;
}

void etalon_row_view::set_TO(cell_view_c_b * _TO)
{
    TO = _TO;
}

void etalon_row_view::set_IO(cell_view_c_b * _IO)
{
    IO = _IO;
}

void etalon_row_view::set_OGP(cell_view_c_b * _OGP)
{
    OGP = _OGP;
}

void etalon_row_view::set_tStart(cell_view_l_e * _tStart)
{
    tStart = _tStart;
}

void etalon_row_view::set_tFinish(cell_view_l_e * _tFinish)
{
    tFinish = _tFinish;
}

void etalon_row_view::set_x(cell_view_l_e * _x)
{
    x = _x;
}

void etalon_row_view::set_y(cell_view_l_e * _y)
{
    y = _y;
}

void etalon_row_view::set_h(cell_view_l_e * _h)
{
    h = _h;
}

void etalon_row_view::set_psi(cell_view_l_e * _psi)
{
    psi = _psi;
}

void etalon_row_view::set_v(cell_view_l_e * _v)
{
    v = _v;
}

void etalon_row_view::set_vh(cell_view_l_e * _vh)
{
    vh = _vh;
}

void etalon_row_view::set_p_b_delete(QPushButton * _p_b_delete)
{
    p_b_delete = _p_b_delete;
}

void etalon_row_view::set_etalon_number(cell_view_l_e * _etalon_number)
{
    etalon_number = _etalon_number;
}

void etalon_row_view::set_countManevr(cell_view_l_e * _countManevr)
{
    countManevr = _countManevr;
}

void etalon_row_view::set_p_b_add_maneuver(QPushButton * _p_b_add_maneuver)
{
    p_b_add_maneuver = _p_b_add_maneuver;
}

void etalon_row_view::obj_class_c_b_changed(QString _value) // вызывается при изменении класса объекта
{
    QStringList s_l_major;
    s_l_major = ret_etalon_s_l_ObjClass_view();
    QStringList s_l_minor;

    int pos;
    pos = -1;

    for(int i=0; i<s_l_major.size(); i++)
    {
        if(s_l_major[i] == _value)
        {
            pos = i;
            break;
        }
    }

    TO->clear_c_b_variant();

    if(pos == -1)
    {
        s_l_minor = ret_etalon_s_l_empty();
    }
    else if(pos == 0)
    {
        // air
        s_l_minor = ret_etalon_s_l_TO_Air_view();
    }
    else if(pos == 1)
    {
        // sea
        s_l_minor = ret_etalon_s_l_TO_Sea_view();
    }
    else if(pos == 2)
    {
        // ground
        s_l_minor = ret_etalon_s_l_TO_Ground_view();
    }
    else if(pos == 3)
    {
        // surface
        s_l_minor = ret_etalon_s_l_TO_Surface_view();
    }

    TO->set_s_l(s_l_minor);
    TO->ret_c_b()->addItems(TO->ret_s_l());
    TO->c_b_changed(TO->ret_value());
}

void etalon_row_view::number_changed(QString _value) // вызывается при изменении номера
{
    etalon_number->l_e_changed(_value);
    etalon_number->ret_l_e()->setText(etalon_number->ret_value());
}
