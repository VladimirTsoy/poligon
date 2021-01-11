#ifndef CHAR_SENS_TABLE_VIEW
#define CHAR_SENS_TABLE_VIEW

#include <stddef.h>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QScrollArea>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QButtonGroup>

#include "char_sens_row_view.h"

// представление таблицы
class char_sens_table_view : public QObject
{
    Q_OBJECT
public:
    // конструктор
    char_sens_table_view(QVBoxLayout * _table_lo,
                         QPushButton * _p_b_save,
                         QPushButton * _p_b_add_row,
                         QLineEdit * _variant_l_e);

    // деструктор
    ~char_sens_table_view();

    // установка информации о таблице
    void set_table_info();

    // установка сигнально-слотового соединения изменения ячеек таблицы и возможностью нажатия на кнопку сохранить
    void set_signal_slot_connection_cell_change_p_b_save_enable(char_sens_row_view * _iter);

    // добавление нового элемента в список
    void add_new_element();

    // очистка списка
    void clear_list();

    // вставка списка в таблицу
    void insert_list_in_table();

    // добавление новой строки в таблицу
    void insert_row_in_table(char_sens_row_view * _iter);

    QVBoxLayout * ret_table_lo();                             // вернуть указатель на менеджер компановки таблицы
    QScrollArea * ret_table_s_a();                            // вернуть область прокрутки с таблицей
    int ret_row_count();                                      // вернуть число строк таблицы
    int ret_col_count();                                      // вернуть число столбцов таблицы
    QTableWidget * ret_ptr_table();                           // вернуть таблицу
    QStringList ret_table_header_s_l();                       // вернуть список строк с названиями столбцов таблицы
    QButtonGroup * ret_b_g_delete();                          // вернуть группу кнопок удаления строки
    QPushButton * ret_p_b_save();                             // вернуть указатель на кнопку Cохранить таблицу
    QPushButton * ret_p_b_add_row();                          // вернуть указатель на кнопку Добавить новую строку
    QString ret_comment();                                    // вернуть комментарий
    QLineEdit * ret_variant_l_e();                            // вернуть указатель на редактируемое поле с описанием контрольной задачи
    char_sens_row_view * ret_first();                         // вернуть указатель на первый элемент
    char_sens_row_view * ret_last();                          // вернуть указатель на последний элемент

    void set_table_lo(QVBoxLayout * _table_lo);               // установить указатель на менеджер компановки таблицы
    void set_table_s_a(QScrollArea * _table_s_a);             // установить область прокрутки с таблицей
    void set_row_count(int _row_count);                       // установить число строк таблицы
    void set_col_count(int _col_count);                       // установить число столбцов таблицы
    void set_ptr_table(QTableWidget * _ptr_table);            // установить таблицу
    void set_table_header_s_l(QStringList _table_header_s_l); // установить список строк с названиями столбцов таблицы
    void set_b_g_delete(QButtonGroup * _b_g_delete);          // установить группу кнопок удаления строки
    void set_p_b_save(QPushButton * _p_b_save);               // установить указатель на кнопку Cохранить таблицу
    void set_p_b_add_row(QPushButton * _p_b_add_row);         // установить указатель на кнопку Добавить новую строку
    void set_comment(QString _comment);                       // установить комментарий
    void set_variant_l_e(QLineEdit * _variant_l_e);           // установить указатель на редактируемое поле с описанием контрольной задачи
    void set_first(char_sens_row_view * _first);              // установить указатель на первый элемент
    void set_last(char_sens_row_view * _last);                // установить указатель на последний элемент

private:
    // таблица --------------------------------------------------------------------------------------------------------
    QVBoxLayout * table_lo;       // указатель на менеджер компановки таблицы
    QScrollArea * table_s_a;      // область прокрутки с таблицей
    int row_count;                // число строк таблицы
    int col_count;                // число столбцов таблицы
    QTableWidget * ptr_table;     // таблица
    QStringList table_header_s_l; // список строк с названиями столбцов таблицы
    // ----------------------------------------------------------------------------------------------------------------

    // группа кнопок удаления строки ----------------------------------------------------------------------------------
    QButtonGroup * b_g_delete;
    // ----------------------------------------------------------------------------------------------------------------

    // кнопки формы ---------------------------------------------------------------------------------------------------
    QPushButton * p_b_save;       // указатель на кнопку Cохранить таблицу
    QPushButton * p_b_add_row;    // указатель на кнопку Добавить новую строку
    // ----------------------------------------------------------------------------------------------------------------

    // комментарий ----------------------------------------------------------------------------------------------------
    QString comment;              // строка с текстом комментария
    QLineEdit * variant_l_e;      // указатель на редактируемое поле с описанием контрольной задачи
    // ----------------------------------------------------------------------------------------------------------------

    // список элементов -----------------------------------------------------------------------------------------------
    char_sens_row_view * first;   // указатель на первый элемент
    char_sens_row_view * last;    // указатель на последний элемент
    // ----------------------------------------------------------------------------------------------------------------

public slots:
    // вызывается при нажатии кнопки Удалить строку (сигнал от _row_num строки таблицы)
    void p_b_delete_click(int _row_num);

    // вызывается для проверки допустимости нажатия на кнопку Сохранить
    void table_p_b_save_enable(QString);
};

#endif // CHAR_SENS_TABLE_VIEW
