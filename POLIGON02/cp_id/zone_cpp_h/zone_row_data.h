#ifndef ZONE_ROW_DATA
#define ZONE_ROW_DATA

#include <stddef.h>

#include "cell_data.h"
#include "zone_point_row_data.h"

// данные строки таблицы
class zone_row_data
{
public:
    // конструктор
    zone_row_data();

    // деструктор
    ~zone_row_data();

    // добавление нового элемента в список точек
    void add_new_element();

    // очистка списка точек
    void clear_list();

    zone_row_data * ret_next();                   // вернуть указатель на следующую зону
    zone_row_data * ret_prev();                   // вернуть указатель на предыдущую зону
    zone_point_row_data * ret_first();            // вернуть указатель на первую точку
    zone_point_row_data * ret_last();             // вернуть указатель на последнюю точку

    void set_next(zone_row_data * _next);         // установить указатель на следующую зону
    void set_prev(zone_row_data * _prev);         // установить указатель на предыдущую зону
    void set_first(zone_point_row_data * _first); // установить указатель на первую точку
    void set_last(zone_point_row_data * _last);   // установить указатель на последнюю точку

    // функции возврата и установки ячеек -----------------------------------------------------------------------------
    cell_data * ret_number();
    cell_data * ret_r();
    cell_data * ret_g();
    cell_data * ret_b();
    cell_data * ret_a();

    void set_number(cell_data * _number);
    void set_r(cell_data * _r);
    void set_g(cell_data * _g);
    void set_b(cell_data * _b);
    void set_a(cell_data * _a);
    // ----------------------------------------------------------------------------------------------------------------

private:
    zone_row_data * next;        // указатель на следующую зону
    zone_row_data * prev;        // указатель на предыдущую зону

    zone_point_row_data * first; // указатель на первую точку
    zone_point_row_data * last;  // указатель на последнюю точку

    // ячейки ---------------------------------------------------------------------------------------------------------
    cell_data * number;
    cell_data * r;
    cell_data * g;
    cell_data * b;
    cell_data * a;
    // ----------------------------------------------------------------------------------------------------------------
};

#endif // ZONE_ROW_DATA
