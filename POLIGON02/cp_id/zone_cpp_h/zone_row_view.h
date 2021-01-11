#ifndef ZONE_ROW_VIEW
#define ZONE_ROW_VIEW

#include <stddef.h>
#include <QString>
#include <QPushButton>
#include <QObject>

#include "cell_view_l_e.h"
#include "zone_point_row_view.h"

// представление строки таблицы
class zone_row_view : public QObject
{
    Q_OBJECT
public:
    // конструктор
    zone_row_view();

    // деструктор
    ~zone_row_view();

    // добавление нового элемента в список точек
    void add_new_element();

    // очистка списка точек
    void clear_list();

    zone_row_view * ret_next();                   // вернуть указатель на следующую зону
    zone_row_view * ret_prev();                   // вернуть указатель на предыдущую зону
    zone_point_row_view * ret_first();            // вернуть указатель на первую точку
    zone_point_row_view * ret_last();             // вернуть указатель на последнюю точку

    void set_next(zone_row_view * _next);         // установить указатель на следующую зону
    void set_prev(zone_row_view * _prev);         // установить указатель на предыдущую зону
    void set_first(zone_point_row_view * _first); // установить указатель на первую точку
    void set_last(zone_point_row_view * _last);   // установить указатель на последнюю точку

    // функции возврата и установки ячеек -----------------------------------------------------------------------------
    cell_view_l_e * ret_number();
    cell_view_l_e * ret_countPoint();
    cell_view_l_e * ret_r();
    cell_view_l_e * ret_g();
    cell_view_l_e * ret_b();
    cell_view_l_e * ret_a();
    cell_view_l_e * ret_color();
    QPushButton * ret_p_b_add();
    QPushButton * ret_p_b_delete();

    void set_number(cell_view_l_e * _number);
    void set_countPoint(cell_view_l_e * _countPoint);
    void set_r(cell_view_l_e * _r);
    void set_g(cell_view_l_e * _g);
    void set_b(cell_view_l_e * _b);
    void set_a(cell_view_l_e * _a);
    void set_color(cell_view_l_e * _color);
    void set_p_b_add(QPushButton * _p_b_add);
    void set_p_b_delete(QPushButton * _p_b_delete);
    // ----------------------------------------------------------------------------------------------------------------

private:
    zone_row_view * next;        // указатель на следующую зону
    zone_row_view * prev;        // указатель на предыдущую зону

    zone_point_row_view * first; // указатель на первую точку
    zone_point_row_view * last;  // указатель на последнюю точку

    // ячейки ---------------------------------------------------------------------------------------------------------
    cell_view_l_e * number;
    cell_view_l_e * countPoint;
    cell_view_l_e * r;
    cell_view_l_e * g;
    cell_view_l_e * b;
    cell_view_l_e * a;
    cell_view_l_e * color;
    QPushButton * p_b_add;
    QPushButton * p_b_delete;
    // ----------------------------------------------------------------------------------------------------------------

public slots:
    void fill_color(QString);
};

#endif // ZONE_ROW_VIEW
