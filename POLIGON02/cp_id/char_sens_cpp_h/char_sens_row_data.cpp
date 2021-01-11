#include "char_sens_row_data.h"

// конструктор
char_sens_row_data::char_sens_row_data()
{
    number = new cell_data     (0, true,  "number"     );
    hMax = new cell_data       (1, true,  "hMax"       );
    hMin = new cell_data       (1, false, "hMin"       );
    maxCountTrc = new cell_data(1, true,  "maxCountTrc");
    rMax = new cell_data       (1, true,  "rMax"       );
    rMin = new cell_data       (1, true,  "rMin"       );
    trustXY = new cell_data    (1, true,  "trustXY"    );
    trustH = new cell_data     (1, true,  "trustH"     );

    next = NULL;
    prev = NULL;
}

// деструктор
char_sens_row_data::~char_sens_row_data()
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

    next = NULL;
    prev = NULL;
}

char_sens_row_data * char_sens_row_data::ret_next() // вернуть указатель на следующий элемент
{
    return next;
}

char_sens_row_data * char_sens_row_data::ret_prev() // вернуть указатель на предыдущий элемент
{
    return prev;
}

void char_sens_row_data::set_next(char_sens_row_data * _next) // установить указатель на следующий элемент
{
    next = _next;
}

void char_sens_row_data::set_prev(char_sens_row_data * _prev) // установить указатель на предыдущий элемент
{
    prev = _prev;
}

cell_data * char_sens_row_data::ret_number()
{
    return number;
}

cell_data * char_sens_row_data::ret_hMax()
{
    return hMax;
}

cell_data * char_sens_row_data::ret_hMin()
{
    return hMin;
}

cell_data * char_sens_row_data::ret_maxCountTrc()
{
    return maxCountTrc;
}

cell_data * char_sens_row_data::ret_rMax()
{
    return rMax;
}

cell_data * char_sens_row_data::ret_rMin()
{
    return rMin;
}

cell_data * char_sens_row_data::ret_trustXY()
{
    return trustXY;
}

cell_data * char_sens_row_data::ret_trustH()
{
    return trustH;
}

void char_sens_row_data::set_number(cell_data * _number)
{
    number = _number;
}

void char_sens_row_data::set_hMax(cell_data * _hMax)
{
    hMax = _hMax;
}

void char_sens_row_data::set_hMin(cell_data * _hMin)
{
    hMin = _hMin;
}

void char_sens_row_data::set_maxCountTrc(cell_data * _maxCountTrc)
{
    maxCountTrc = _maxCountTrc;
}

void char_sens_row_data::set_rMax(cell_data * _rMax)
{
    rMax = _rMax;
}

void char_sens_row_data::set_rMin(cell_data * _rMin)
{
    rMin = _rMin;
}

void char_sens_row_data::set_trustXY(cell_data * _trustXY)
{
    trustXY = _trustXY;
}

void char_sens_row_data::set_trustH(cell_data * _trustH)
{
    trustH = _trustH;
}
