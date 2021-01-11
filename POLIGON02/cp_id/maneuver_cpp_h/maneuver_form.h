#ifndef MANEUVER_FORM_H
#define MANEUVER_FORM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

class maneuver_form : public QWidget
{
public:
    // конструктор
    maneuver_form();

    // деструктор
    ~maneuver_form();

    QVBoxLayout * ret_main_lo();  // вернуть главный менеджер компановки
    QLabel * ret_title_label();   // вернуть заголовок формы
    QVBoxLayout * ret_table_lo(); // вернуть менеджер компановки таблицы

    void set_main_lo(QVBoxLayout * _main_lo);    // установить главный менеджер компановки
    void set_title_label(QLabel * _title_label); // установить заголовок формы
    void set_table_lo(QVBoxLayout * _table_lo);  // установить менеджер компановки таблицы

private:
    QVBoxLayout * main_lo;  // главный менеджер компановки
    QLabel * title_label;   // заголовок формы
    QVBoxLayout * table_lo; // менеджер компановки таблицы
};

#endif // MANEUVER_FORM_H
