#ifndef CHAR_SENS_ROW_DATA
#define CHAR_SENS_ROW_DATA

#include <stddef.h>
#include <QString>

#include "cell_data.h"

// данные строки таблицы
class char_sens_row_data
{
public:
    // конструктор
    char_sens_row_data();

    // деструктор
    ~char_sens_row_data();

    char_sens_row_data * ret_next();           // вернуть указатель на следующий элемент
    char_sens_row_data * ret_prev();           // вернуть указатель на предыдущий элемент

    void set_next(char_sens_row_data * _next); // установить указатель на следующий элемент
    void set_prev(char_sens_row_data * _prev); // установить указатель на предыдущий элемент

    // функции возврата и установки ячеек -----------------------------------------------------------------------------
    cell_data * ret_number();
    cell_data * ret_hMax();
    cell_data * ret_hMin();
    cell_data * ret_maxCountTrc();
    cell_data * ret_rMax();
    cell_data * ret_rMin();
    cell_data * ret_trustXY();
    cell_data * ret_trustH();

    void set_number(cell_data * _number);
    void set_hMax(cell_data * _hMax);
    void set_hMin(cell_data * _hMin);
    void set_maxCountTrc(cell_data * _maxCountTrc);
    void set_rMax(cell_data * _rMax);
    void set_rMin(cell_data * _rMin);
    void set_trustXY(cell_data * _trustXY);
    void set_trustH(cell_data * _trustH);
    // ----------------------------------------------------------------------------------------------------------------

private:
    char_sens_row_data * next; // указатель на следующий элемент
    char_sens_row_data * prev; // указатель на предыдущий элемент

    // ячейки ---------------------------------------------------------------------------------------------------------
    cell_data * number;
    cell_data * hMax;
    cell_data * hMin;
    cell_data * maxCountTrc;
    cell_data * rMax;
    cell_data * rMin;
    cell_data * trustXY;
    cell_data * trustH;
    // ----------------------------------------------------------------------------------------------------------------
};

#endif // CHAR_SENS_ROW_DATA
