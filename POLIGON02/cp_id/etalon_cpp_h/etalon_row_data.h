#ifndef ETALON_ROW_DATA
#define ETALON_ROW_DATA

#include <stddef.h>
#include <QString>

#include "cell_data.h"
#include "maneuver_row_data.h"

// данные строки таблицы
class etalon_row_data
{
public:
    // конструктор
    etalon_row_data();

    // деструктор
    ~etalon_row_data();

    // добавление нового элемента в список
    void add_new_element();

    // очистка списка
    void clear_list();

    etalon_row_data * ret_next();               // вернуть указатель на следующий элемент
    etalon_row_data * ret_prev();               // вернуть указатель на предыдущий элемент
    maneuver_row_data * ret_first();            // вернуть указатель на первый маневр
    maneuver_row_data * ret_last();             // вернуть указатель на последний маневр

    void set_next(etalon_row_data * _next);     // установить указатель на следующий элемент
    void set_prev(etalon_row_data * _prev);     // установить указатель на предыдущий элемент
    void set_first(maneuver_row_data * _first); // установить указатель на первый маневр
    void set_last(maneuver_row_data * _last);   // установить указатель на последний маневр

    // функции возврата и установки ячеек -----------------------------------------------------------------------------
    cell_data * ret_number();
    cell_data * ret_ObjClass();
    cell_data * ret_TO();
    cell_data * ret_IO();
    cell_data * ret_OGP();
    cell_data * ret_tStart();
    cell_data * ret_tFinish();
    cell_data * ret_x();
    cell_data * ret_y();
    cell_data * ret_h();
    cell_data * ret_psi();
    cell_data * ret_v();
    cell_data * ret_vh();

    void set_number(cell_data * _number);
    void set_ObjClass(cell_data * _ObjClass);
    void set_TO(cell_data * _TO);
    void set_IO(cell_data * _IO);
    void set_OGP(cell_data * _OGP);
    void set_tStart(cell_data * _tStart);
    void set_tFinish(cell_data * _tFinish);
    void set_x(cell_data * _x);
    void set_y(cell_data * _y);
    void set_h(cell_data * _h);
    void set_psi(cell_data * _psi);
    void set_v(cell_data * _v);
    void set_vh(cell_data * _vh);
    // ----------------------------------------------------------------------------------------------------------------

private:
    etalon_row_data * next;    // указатель на следующий элемент
    etalon_row_data * prev;    // указатель на предыдущий элемент

    maneuver_row_data * first; // указатель на первый маневр
    maneuver_row_data * last;  // указатель на последний маневр

    // ячейки ---------------------------------------------------------------------------------------------------------
    cell_data * number;
    cell_data * ObjClass;
    cell_data * TO;
    cell_data * IO;
    cell_data * OGP;
    cell_data * tStart;
    cell_data * tFinish;
    cell_data * x;
    cell_data * y;
    cell_data * h;
    cell_data * psi;
    cell_data * v;
    cell_data * vh;
    // ----------------------------------------------------------------------------------------------------------------
};

#endif // ETALON_ROW_DATA
