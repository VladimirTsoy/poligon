#ifndef MANEUVER_ROW_VIEW
#define MANEUVER_ROW_VIEW

#include <stddef.h>
#include <QString>
#include <QStringList>
#include <QPushButton>
#include <QDebug>

#include "cell_view_l_e.h"
#include "cell_view_c_b.h"

// представление строки таблицы
class maneuver_row_view
{
public:
    // конструктор
    maneuver_row_view();

    // деструктор
    ~maneuver_row_view();

    maneuver_row_view * ret_next();           // вернуть указатель на следующий элемент
    maneuver_row_view * ret_prev();           // вернуть указатель на предыдущий элемент

    void set_next(maneuver_row_view * _next); // установить указатель на следующий элемент
    void set_prev(maneuver_row_view * _prev); // установить указатель на предыдущий элемент

    // функции возврата и установки ячеек -----------------------------------------------------------------------------
    cell_view_l_e * ret_number();
    cell_view_l_e * ret_tStart();
    cell_view_l_e * ret_tFinish();
    cell_view_l_e * ret_a();
    cell_view_l_e * ret_vh();
    cell_view_l_e * ret_r();
    QPushButton * ret_p_b_delete();

    void set_number(cell_view_l_e * _number);
    void set_tStart(cell_view_l_e * _tStart);
    void set_tFinish(cell_view_l_e * _tFinish);
    void set_a(cell_view_l_e * _a);
    void set_vh(cell_view_l_e * _vh);
    void set_r(cell_view_l_e * _r);
    void set_p_b_delete(QPushButton * _p_b_delete);
    // ----------------------------------------------------------------------------------------------------------------

private:
    maneuver_row_view * next;  // указатель на следующий элемент
    maneuver_row_view * prev;  // указатель на предыдущий элемент

    // ячейки ---------------------------------------------------------------------------------------------------------
    cell_view_l_e * number;
    cell_view_l_e * tStart;
    cell_view_l_e * tFinish;
    cell_view_l_e * a;
    cell_view_l_e * vh;
    cell_view_l_e * r;
    QPushButton * p_b_delete;
    // ----------------------------------------------------------------------------------------------------------------
};

#endif // MANEUVER_ROW_VIEW
