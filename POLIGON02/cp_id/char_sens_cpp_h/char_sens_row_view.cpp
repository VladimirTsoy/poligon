#include "char_sens_row_view.h"

// конструктор
char_sens_row_view::char_sens_row_view()
{
    number = new cell_view_l_e     (0, 0, true,  "white", "pink");
    hMax = new cell_view_l_e       (1, 1, true,  "white", "pink");
    hMin = new cell_view_l_e       (1, 1, false, "white", "pink");
    maxCountTrc = new cell_view_l_e(0, 0, true,  "white", "pink");
    rMax = new cell_view_l_e       (1, 1, true,  "white", "pink");
    rMin = new cell_view_l_e       (1, 1, true,  "white", "pink");
    trustXY = new cell_view_l_e    (1, 1, true,  "white", "pink");
    trustH = new cell_view_l_e     (1, 1, true,  "white", "pink");

    number->set_validator_par     (1, INT_MAX   );
    hMax->set_validator_par       (0, INT_MAX, 2);
    hMin->set_validator_par       (0, INT_MAX, 2);
    maxCountTrc->set_validator_par(1, INT_MAX   );
    rMax->set_validator_par       (0, INT_MAX, 2);
    rMin->set_validator_par       (0, INT_MAX, 2);
    trustXY->set_validator_par    (0, INT_MAX, 2);
    trustH->set_validator_par     (0, INT_MAX, 2);

    number     ->l_e_changed("");
    hMax       ->l_e_changed("");
    hMin       ->l_e_changed("");
    maxCountTrc->l_e_changed("");
    rMax       ->l_e_changed("");
    rMin       ->l_e_changed("");
    trustXY    ->l_e_changed("");
    trustH     ->l_e_changed("");

    p_b_delete = new QPushButton();
    p_b_delete->setText("x");

    next = NULL;
    prev = NULL;
}

// деструктор
char_sens_row_view::~char_sens_row_view()
{
    delete number;
    number = NULL;

    delete hMax;
    hMax = NULL;

    delete hMin;
    hMin = NULL;

    delete maxCountTrc;
    maxCountTrc = NULL;

    delete rMax;
    rMax = NULL;

    delete rMin;
    rMin = NULL;

    delete trustXY;
    trustXY = NULL;

    delete trustH;
    trustH = NULL;

    delete p_b_delete;
    p_b_delete = NULL;

    next = NULL;
    prev = NULL;
}

char_sens_row_view * char_sens_row_view::ret_next() // вернуть указатель на следующий элемент
{
    return next;
}

char_sens_row_view * char_sens_row_view::ret_prev() // вернуть указатель на предыдущий элемент
{
    return prev;
}

void char_sens_row_view::set_next(char_sens_row_view * _next) // установить указатель на следующий элемент
{
    next = _next;
}

void char_sens_row_view::set_prev(char_sens_row_view * _prev) // установить указатель на предыдущий элемент
{
    prev = _prev;
}

cell_view_l_e * char_sens_row_view::ret_number()
{
    return number;
}

cell_view_l_e * char_sens_row_view::ret_hMax()
{
    return hMax;
}

cell_view_l_e * char_sens_row_view::ret_hMin()
{
    return hMin;
}

cell_view_l_e * char_sens_row_view::ret_maxCountTrc()
{
    return maxCountTrc;
}

cell_view_l_e * char_sens_row_view::ret_rMax()
{
    return rMax;
}

cell_view_l_e * char_sens_row_view::ret_rMin()
{
    return rMin;
}

cell_view_l_e * char_sens_row_view::ret_trustXY()
{
    return trustXY;
}

cell_view_l_e * char_sens_row_view::ret_trustH()
{
    return trustH;
}

QPushButton * char_sens_row_view::ret_p_b_delete()
{
    return p_b_delete;
}

void char_sens_row_view::set_number(cell_view_l_e * _number)
{
    number = _number;
}

void char_sens_row_view::set_hMax(cell_view_l_e * _hMax)
{
    hMax = _hMax;
}

void char_sens_row_view::set_hMin(cell_view_l_e * _hMin)
{
    hMin = _hMin;
}

void char_sens_row_view::set_maxCountTrc(cell_view_l_e * _maxCountTrc)
{
    maxCountTrc  = _maxCountTrc;
}

void char_sens_row_view::set_rMax(cell_view_l_e * _rMax)
{
    rMax = _rMax;
}

void char_sens_row_view::set_rMin(cell_view_l_e * _rMin)
{
    rMin = _rMin;
}

void char_sens_row_view::set_trustXY(cell_view_l_e * _trustXY)
{
    trustXY = _trustXY;
}

void char_sens_row_view::set_trustH(cell_view_l_e * _trustH)
{
    trustH = _trustH;
}

void char_sens_row_view::set_p_b_delete(QPushButton * _p_b_delete)
{
    p_b_delete = _p_b_delete;
}
