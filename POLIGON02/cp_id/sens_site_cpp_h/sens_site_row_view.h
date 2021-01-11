#ifndef SENS_SITE_ROW_VIEW
#define SENS_SITE_ROW_VIEW

#include <stddef.h>
#include <QString>
#include <QStringList>
#include <QPushButton>

#include "cell_view_l_e.h"
#include "cell_view_c_b.h"
#include "sens_site_convertor.h"

// представление строки таблицы
class sens_site_row_view
{
public:
    // конструктор
    sens_site_row_view();

    // деструктор
    ~sens_site_row_view();

    sens_site_row_view * ret_next();           // вернуть указатель на следующий элемент
    sens_site_row_view * ret_prev();           // вернуть указатель на предыдущий элемент

    void set_next(sens_site_row_view * _next); // установить указатель на следующий элемент
    void set_prev(sens_site_row_view * _prev); // установить указатель на предыдущий элемент

    // функции возврата и установки ячеек -----------------------------------------------------------------------------
    cell_view_l_e * ret_number();
    cell_view_l_e * ret_charSens();
    cell_view_l_e * ret_x();
    cell_view_l_e * ret_y();
    QPushButton * ret_p_b_delete();

    void set_number(cell_view_l_e * _number);
    void set_charSens(cell_view_l_e * _charSens);
    void set_x(cell_view_l_e * _x);
    void set_y(cell_view_l_e * _y);
    void set_p_b_delete(QPushButton * _p_b_delete);
    // ----------------------------------------------------------------------------------------------------------------

private:
    sens_site_row_view * next;  // указатель на следующий элемент
    sens_site_row_view * prev;  // указатель на предыдущий элемент

    // ячейки ---------------------------------------------------------------------------------------------------------
    cell_view_l_e * number;
    cell_view_l_e * charSens;
    cell_view_l_e * x;
    cell_view_l_e * y;
    QPushButton * p_b_delete;
    // ----------------------------------------------------------------------------------------------------------------
};

#endif // SENS_SITE_ROW_VIEW
