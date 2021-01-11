#ifndef SENS_SITE_ROW_DATA
#define SENS_SITE_ROW_DATA

#include <stddef.h>
#include <QString>

#include "cell_data.h"

// данные строки таблицы
class sens_site_row_data
{
public:
    // конструктор
    sens_site_row_data();

    // деструктор
    ~sens_site_row_data();

    sens_site_row_data * ret_next();           // вернуть указатель на следующий элемент
    sens_site_row_data * ret_prev();           // вернуть указатель на предыдущий элемент

    void set_next(sens_site_row_data * _next); // установить указатель на следующий элемент
    void set_prev(sens_site_row_data * _prev); // установить указатель на предыдущий элемент

    // функции возврата и установки ячеек -----------------------------------------------------------------------------
    cell_data * ret_number();
    cell_data * ret_charSens();
    cell_data * ret_x();
    cell_data * ret_y();

    void set_number(cell_data * _number);
    void set_charSens(cell_data * _charSens);
    void set_x(cell_data * _x);
    void set_y(cell_data * _y);
    // ----------------------------------------------------------------------------------------------------------------

private:
    sens_site_row_data * next; // указатель на следующий элемент
    sens_site_row_data * prev; // указатель на предыдущий элемент

    // ячейки ---------------------------------------------------------------------------------------------------------
    cell_data * number;
    cell_data * charSens;
    cell_data * x;
    cell_data * y;
    // ----------------------------------------------------------------------------------------------------------------
};

#endif // SENS_SITE_ROW_DATA
