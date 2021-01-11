#ifndef CELL_VIEW_C_B_H
#define CELL_VIEW_C_B_H

#include <QObject>
#include <stddef.h>
#include <QString>
#include <QStringList>
#include <QComboBox>
#include <QPalette>

// отображение ячейки таблицы в виде выпадающего списка
class cell_view_c_b : public QObject
{
    Q_OBJECT
public:
    // конструктор
    cell_view_c_b(QStringList _s_l,
                  bool _b_require,
                  QString _col_valid,
                  QString _col_error);

    // деструктор
    ~cell_view_c_b();

    // очистить элементы выбора выпадающего списка
    void clear_c_b_variant();

    // покраска выпадающего списка
    void fill_color(bool _b_correct);

    QString ret_value();                    // вернуть значение
    bool ret_b_require();                   // вернуть признак обязательности
    bool ret_b_correct();                   // вернуть признак корректности
    QString ret_col_valid();                // вернуть цвет корректного поля
    QString ret_col_error();                // вернуть цвет ошибочного поля
    QStringList ret_s_l();                  // вернуть список строк возможных значений элементов выпадающего списка
    QComboBox * ret_c_b();                  // вернуть выпадающий список

    void set_value(QString _value);         // установить значение
    void set_b_require(bool _b_require);    // установить признак обязательности
    void set_b_correct(bool _b_correct);    // установить признак корректности
    void set_col_valid(QString _col_valid); // установить цвет корректного поля
    void set_col_error(QString _col_error); // установить цвет ошибочного поля
    void set_s_l(QStringList _s_l);         // установить список строк возможных значений элементов выпадающего списка
    void set_c_b(QComboBox * _c_b);         // установить выпадающий список

private:
    QString value;     // значение
    bool b_require;    // признак обязательности
    bool b_correct;    // признак корректности
    QString col_valid; // цвет корректного поля
    QString col_error; // цвет ошибочного поля
    QStringList s_l;   // список строк возможных значений элементов выпадающего списка
    QComboBox * c_b;   // выпадающий список

public slots:

    // вызывается при изменении элемента в выпадающем списке
    void c_b_changed(QString _value);
};

#endif // CELL_VIEW_C_B_H
