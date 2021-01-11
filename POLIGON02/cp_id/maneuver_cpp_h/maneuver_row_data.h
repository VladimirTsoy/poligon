#ifndef MANEUVER_ROW_DATA
#define MANEUVER_ROW_DATA

#include <stddef.h>

#include "cell_data.h"

// данные строки таблицы
class maneuver_row_data
{
public:
    // конструктор
    maneuver_row_data();

    // деструктор
    ~maneuver_row_data();

    maneuver_row_data * ret_next();           // вернуть указатель на следующий элемент
    maneuver_row_data * ret_prev();           // вернуть указатель на предыдущий элемент

    void set_next(maneuver_row_data * _next); // установить указатель на следующий элемент
    void set_prev(maneuver_row_data * _prev); // установить указатель на предыдущий элемент

    // функции возврата и установки ячеек -----------------------------------------------------------------------------
    cell_data * ret_number();
    cell_data * ret_tStart();
    cell_data * ret_tFinish();
    cell_data * ret_a();
    cell_data * ret_vh();
    cell_data * ret_r();

    void set_number(cell_data * _number);
    void set_tStart(cell_data * _tStart);
    void set_tFinish(cell_data * _tFinish);
    void set_a(cell_data * _a);
    void set_vh(cell_data * _vh);
    void set_r(cell_data * _r);
    // ----------------------------------------------------------------------------------------------------------------

private:
    maneuver_row_data * next; // указатель на следующий элемент
    maneuver_row_data * prev; // указатель на предыдущий элемент

    // ячейки ---------------------------------------------------------------------------------------------------------
    cell_data * number;
    cell_data * tStart;
    cell_data * tFinish;
    cell_data * a;
    cell_data * vh;
    cell_data * r;
    // ----------------------------------------------------------------------------------------------------------------
};

#endif // MANEUVER_ROW_DATA
