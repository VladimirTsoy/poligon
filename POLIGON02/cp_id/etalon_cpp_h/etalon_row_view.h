#ifndef ETALON_ROW_VIEW
#define ETALON_ROW_VIEW

#include <stddef.h>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QPushButton>

#include "cell_view_l_e.h"
#include "cell_view_c_b.h"
#include "maneuver_row_view.h"
#include "etalon_convertor.h"

// представление строки таблицы
class etalon_row_view : public QObject
{
    Q_OBJECT
public:
    // конструктор
    etalon_row_view();

    // деструктор
    ~etalon_row_view();

    // добавление нового элемента в список
    void add_new_element();

    // очистка списка
    void clear_list();

    etalon_row_view * ret_next();               // вернуть указатель на следующий элемент
    etalon_row_view * ret_prev();               // вернуть указатель на предыдущий элемент
    maneuver_row_view * ret_first();            // вернуть указатель на первый маневр
    maneuver_row_view * ret_last();             // вернуть указатель на последний маневр

    void set_next(etalon_row_view * _next);     // установить указатель на следующий элемент
    void set_prev(etalon_row_view * _prev);     // установить указатель на предыдущий элемент
    void set_first(maneuver_row_view * _first); // установить указатель на первый маневр
    void set_last(maneuver_row_view * _last);   // установить указатель на последний маневр

    // функции возврата и установки ячеек -----------------------------------------------------------------------------
    cell_view_l_e * ret_number();
    cell_view_c_b * ret_ObjClass();
    cell_view_c_b * ret_TO();
    cell_view_c_b * ret_IO();
    cell_view_c_b * ret_OGP();
    cell_view_l_e * ret_tStart();
    cell_view_l_e * ret_tFinish();
    cell_view_l_e * ret_x();
    cell_view_l_e * ret_y();
    cell_view_l_e * ret_h();
    cell_view_l_e * ret_psi();
    cell_view_l_e * ret_v();
    cell_view_l_e * ret_vh();
    QPushButton * ret_p_b_delete();
    cell_view_l_e * ret_etalon_number();
    cell_view_l_e * ret_countManevr();
    QPushButton * ret_p_b_add_maneuver();

    void set_number(cell_view_l_e * _number);
    void set_ObjClass(cell_view_c_b * _ObjClass);
    void set_TO(cell_view_c_b * _TO);
    void set_IO(cell_view_c_b * _IO);
    void set_OGP(cell_view_c_b * _OGP);
    void set_tStart(cell_view_l_e * _tStart);
    void set_tFinish(cell_view_l_e * _tFinish);
    void set_x(cell_view_l_e * _x);
    void set_y(cell_view_l_e * _y);
    void set_h(cell_view_l_e * _h);
    void set_psi(cell_view_l_e * _psi);
    void set_v(cell_view_l_e * _v);
    void set_vh(cell_view_l_e * _vh);
    void set_p_b_delete(QPushButton * _p_b_delete);
    void set_etalon_number(cell_view_l_e * _etalon_number);
    void set_countManevr(cell_view_l_e * _countManevr);
    void set_p_b_add_maneuver(QPushButton * _p_b_add_maneuver);
    // ----------------------------------------------------------------------------------------------------------------

private:
    etalon_row_view * next;    // указатель на следующий элемент
    etalon_row_view * prev;    // указатель на предыдущий элемент

    maneuver_row_view * first; // указатель на первый маневр
    maneuver_row_view * last;  // указатель на последний маневр

    // ячейки ---------------------------------------------------------------------------------------------------------
    cell_view_l_e * number;
    cell_view_c_b * ObjClass;
    cell_view_c_b * TO;
    cell_view_c_b * IO;
    cell_view_c_b * OGP;
    cell_view_l_e * tStart;
    cell_view_l_e * tFinish;
    cell_view_l_e * x;
    cell_view_l_e * y;
    cell_view_l_e * h;
    cell_view_l_e * psi;
    cell_view_l_e * v;
    cell_view_l_e * vh;
    QPushButton * p_b_delete;
    // ----------------------------------------------------------------------------------------------------------------

    // ячейки подтаблицы ----------------------------------------------------------------------------------------------
    cell_view_l_e * etalon_number;
    cell_view_l_e * countManevr;
    QPushButton * p_b_add_maneuver;
    // ----------------------------------------------------------------------------------------------------------------

public slots:
    void obj_class_c_b_changed(QString _value); // вызывается при изменении класса объекта
    void number_changed(QString _value);        // вызывается при изменении номера
};

#endif // ETALON_ROW_VIEW
