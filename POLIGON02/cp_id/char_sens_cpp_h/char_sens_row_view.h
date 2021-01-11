#ifndef CHAR_SENS_ROW_VIEW
#define CHAR_SENS_ROW_VIEW

#include <stddef.h>
#include <QString>
#include <QPushButton>

#include "cell_view_l_e.h"
#include "cell_view_c_b.h"

// представление строки таблицы
class char_sens_row_view
{
public:
    // конструктор
    char_sens_row_view();

    // деструктор
    ~char_sens_row_view();

    char_sens_row_view * ret_next();           // вернуть указатель на следующий элемент
    char_sens_row_view * ret_prev();           // вернуть указатель на предыдущий элемент

    void set_next(char_sens_row_view * _next); // установить указатель на следующий элемент
    void set_prev(char_sens_row_view * _prev); // установить указатель на предыдущий элемент

    // функции возврата и установки ячеек -----------------------------------------------------------------------------
    cell_view_l_e * ret_number();
    cell_view_l_e * ret_hMax();
    cell_view_l_e * ret_hMin();
    cell_view_l_e * ret_maxCountTrc();
    cell_view_l_e * ret_rMax();
    cell_view_l_e * ret_rMin();
    cell_view_l_e * ret_trustXY();
    cell_view_l_e * ret_trustH();
    QPushButton * ret_p_b_delete();

    void set_number(cell_view_l_e * _number);
    void set_hMax(cell_view_l_e * _hMax);
    void set_hMin(cell_view_l_e * _hMin);
    void set_maxCountTrc(cell_view_l_e * _maxCountTrc);
    void set_rMax(cell_view_l_e * _rMax);
    void set_rMin(cell_view_l_e * _rMin);
    void set_trustXY(cell_view_l_e * _trustXY);
    void set_trustH(cell_view_l_e * _trustH);
    void set_p_b_delete(QPushButton * _p_b_delete);
    // ----------------------------------------------------------------------------------------------------------------

private:
    char_sens_row_view * next;  // указатель на следующий элемент
    char_sens_row_view * prev;  // указатель на предыдущий элемент

    // ячейки ---------------------------------------------------------------------------------------------------------
    cell_view_l_e * number;
    cell_view_l_e * hMax;
    cell_view_l_e * hMin;
    cell_view_l_e * maxCountTrc;
    cell_view_l_e * rMax;
    cell_view_l_e * rMin;
    cell_view_l_e * trustXY;
    cell_view_l_e * trustH;
    QPushButton * p_b_delete;
    // ----------------------------------------------------------------------------------------------------------------
};

#endif // CHAR_SENS_ROW_VIEW
