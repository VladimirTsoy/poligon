#ifndef ZONE_POINT_ROW_DATA
#define ZONE_POINT_ROW_DATA

#include <stddef.h>

#include "cell_data.h"

// данные строки таблицы
class zone_point_row_data
{
public:
    // конструктор
    zone_point_row_data();

    // деструктор
    ~zone_point_row_data();

    zone_point_row_data * ret_next();           // вернуть указатель на следующий элемент
    zone_point_row_data * ret_prev();           // вернуть указатель на предыдущий элемент

    void set_next(zone_point_row_data * _next); // установить указатель на следующий элемент
    void set_prev(zone_point_row_data * _prev); // установить указатель на предыдущий элемент

    // функции возврата и установки ячеек -----------------------------------------------------------------------------
    cell_data * ret_number();
    cell_data * ret_x();
    cell_data * ret_y();

    void set_number(cell_data * _number);
    void set_x(cell_data * _x);
    void set_y(cell_data * _y);
    // ----------------------------------------------------------------------------------------------------------------

private:
    zone_point_row_data * next; // указатель на следующий элемент
    zone_point_row_data * prev; // указатель на предыдущий элемент

    // ячейки ---------------------------------------------------------------------------------------------------------
    cell_data * number;
    cell_data * x;
    cell_data * y;
    // ----------------------------------------------------------------------------------------------------------------
};

#endif // ZONE_POINT_ROW_DATA
