#ifndef ETALON_TABLE_VIEW
#define ETALON_TABLE_VIEW

#include <stddef.h>
#include <QString>
#include <QStringList>
#include <QScrollArea>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QButtonGroup>
#include <QObject>

#include "etalon_row_view.h"

// представление таблицы
class etalon_table_view : public QObject
{
    Q_OBJECT
public:
    // конструктор
    etalon_table_view(QVBoxLayout * _table_lo,
                      QPushButton * _p_b_save,
                      QPushButton * _p_b_add_row,
                      QLineEdit * _variant_l_e,
                      QVBoxLayout * _sub_table_lo);

    // деструктор
    ~etalon_table_view();

    // установка информации о таблице
    void set_table_info();

    // установка информации о подтаблице
    void set_sub_table_info();

    // установка сигнально-слотового соединения изменения ячеек таблицы и возможностью нажатия на кнопку сохранить
    void set_etalon_signal_slot_connection_cell_change_p_b_save_enable(etalon_row_view * _etalon);

    // установка сигнально-слотового соединения изменения ячеек таблицы и возможностью нажатия на кнопку сохранить
    void set_maneuver_signal_slot_connection_cell_change_p_b_save_enable(maneuver_row_view * _maneuver);

    // вспомогательные функции ----------------------------------------------------------------------------------------
    // вернуть индекс эталона по указателю на эталон
    int ret_index_by_etalon(etalon_row_view * _etalon);

    // вернуть указатель на эталон по индексу эталона
    etalon_row_view * ret_etalon_by_index(int _index);

    // вернуть указатель на эталон по указателю на маневр
    etalon_row_view * ret_etalon_by_maneuver(maneuver_row_view * _maneuver);

    // вернуть указатель на эталон по номеру строки подтаблицы маневра
    etalon_row_view * ret_etalon_by_sub_row_num_maneuver(int _sub_row_num);

    // вернуть указатель на маневр по номеру строки подтаблицы маневра
    maneuver_row_view * ret_maneuver_by_sub_row_num_maneuver(int _sub_row_num);

    // вернуть номер строки подтаблицы, которую должен занять формуляр эталона
    int ret_num_major_sub_row_by_etalon(etalon_row_view * _etalon);

    // вернуть номер строки подтаблицы, которую должен занять формуляр маневра
    int ret_num_minor_sub_row_by_maneuver(maneuver_row_view * _maneuver);

    // вернуть признак добавления новой строки в подтаблицу по указателю на маневр
    int ret_b_add_minor_row_by_maneuver(maneuver_row_view * _maneuver);

    // вернуть признак удаления строки подтаблицы по указателю на маневр
    bool ret_b_delete_row_by_maneuver(maneuver_row_view * _maneuver);
    // ----------------------------------------------------------------------------------------------------------------

    // добавление нового элемента в список
    void add_new_element();

    // очистка списка
    void clear_list();

    // вставка списка в таблицу
    void insert_list_in_table();

    // добавление новой строки в таблицу
    void insert_row_in_table(etalon_row_view * _iter);

    // добавление основной строки в подтаблицу
    void insert_major_row_in_sub_table(etalon_row_view * _etalon);

    // добавление второстепенной строки в подтаблицу
    void insert_minor_row_in_sub_table(maneuver_row_view * _maneuver);

    // переименование кнопок удалить маневр (-1), находящихся в подтаблице после маневра
    void rename_minus_b_g_delete_after_maneuver(etalon_row_view * _etalon,
                                                maneuver_row_view * _maneuver,
                                                bool _b_delete);

    // переименование кнопок удалить маневр (+1), находящихся в подтаблице после маневра
    void rename_plus_p_b_delete_after_maneuver(etalon_row_view * _etalon, maneuver_row_view * _maneuver);

    // изъятие маневра из списка (без удаления)
    void withdrawal_maneuver_from_list(etalon_row_view * _etalon,
                                       maneuver_row_view * _maneuver);

    // очистка подтаблицы после удаления эталона
    void sub_table_clear_after_delete_etalon(etalon_row_view * _etalon_delete);

    bool check_fill(cell_view_l_e * _fill_1, cell_view_l_e * _fill_2);

    QVBoxLayout * ret_table_lo();                                     // вернуть указатель на менеджер компановки таблицы
    QScrollArea * ret_table_s_a();                                    // вернуть область прокрутки с таблицей
    int ret_row_count();                                              // вернуть число строк таблицы
    int ret_col_count();                                              // вернуть число столбцов таблицы
    QTableWidget * ret_ptr_table();                                   // вернуть таблицу
    QStringList ret_table_header_s_l();                               // вернуть список строк с названиями столбцов таблицы
    QVBoxLayout * ret_sub_table_lo();                                 // вернуть указатель на менеджер компановки подтаблицы
    QScrollArea * ret_sub_table_s_a();                                // вернуть область прокрутки с подтаблицей
    int ret_sub_row_count();                                          // вернуть число строк подтаблицы
    int ret_sub_col_count();                                          // вернуть число столбцов подтаблицы
    QTableWidget * ret_ptr_sub_table();                               // вернуть подтаблицу
    QStringList ret_sub_table_header_s_l();                           // вернуть список строк с названиями столбцов подтаблицы
    QButtonGroup * ret_b_g_delete();                                  // вернуть группу кнопок удаления строки таблицы
    QButtonGroup * ret_b_g_sub_delete();                              // вернуть группу кнопок удаления строки подтаблицы
    QButtonGroup * ret_b_g_sub_add();                                 // вернуть группу кнопок добавления строки подтаблицы
    QPushButton * ret_p_b_save();                                     // вернуть указатель на кнопку Cохранить таблицу
    QPushButton * ret_p_b_add_row();                                  // вернуть указатель на кнопку Добавить новую строку
    QString ret_comment();                                            // вернуть комментарий
    QLineEdit * ret_variant_l_e();                                    // вернуть указатель на редактируемое поле с описанием контрольной задачи
    etalon_row_view * ret_first();                                    // вернуть указатель на первый элемент
    etalon_row_view * ret_last();                                     // вернуть указатель на последний элемент

    void set_table_lo(QVBoxLayout * _table_lo);                       // установить указатель на менеджер компановки таблицы
    void set_table_s_a(QScrollArea * _table_s_a);                     // установить область прокрутки с таблицей
    void set_row_count(int _row_count);                               // установить число строк таблицы
    void set_col_count(int _col_count);                               // установить число столбцов таблицы
    void set_ptr_table(QTableWidget * _ptr_table);                    // установить таблицу
    void set_table_header_s_l(QStringList _table_header_s_l);         // установить список строк с названиями столбцов таблицы
    void set_sub_table_lo(QVBoxLayout * _sub_table_lo);               // установить указатель на менеджер компановки подтаблицы
    void set_sub_table_s_a(QScrollArea * _sub_table_s_a);             // установить область прокрутки с подтаблицей
    void set_sub_row_count(int _sub_row_count);                       // установить число строк подтаблицы
    void set_sub_col_count(int _sub_col_count);                       // установить число столбцов подтаблицы
    void set_ptr_sub_table(QTableWidget * _ptr_sub_table);            // установить подтаблицу
    void set_sub_table_header_s_l(QStringList _sub_table_header_s_l); // установить список строк с названиями столбцов подтаблицы
    void set_b_g_delete(QButtonGroup * _b_g_delete);                  // установить группу кнопок удаления строки таблицы
    void set_b_g_sub_delete(QButtonGroup * _b_g_sub_delete);          // установить группу кнопок удаления строки подтаблицы
    void set_b_g_sub_add(QButtonGroup * _b_g_sub_add);                // установить группу кнопок добавления строки подтаблицы
    void set_p_b_save(QPushButton * _p_b_save);                       // установить указатель на кнопку Cохранить таблицу
    void set_p_b_add_row(QPushButton * _p_b_add_row);                 // установить указатель на кнопку Добавить новую строку
    void set_comment(QString _comment);                               // установить комментарий
    void set_variant_l_e(QLineEdit * _variant_l_e);                   // установить указатель на редактируемое поле с описанием контрольной задачи
    void set_first(etalon_row_view * _first);                         // установить указатель на первый элемент
    void set_last(etalon_row_view * _last);                           // установить указатель на последний элемент

private:
    // таблица --------------------------------------------------------------------------------------------------------
    QVBoxLayout * table_lo;           // указатель на менеджер компановки таблицы
    QScrollArea * table_s_a;          // область прокрутки с таблицей
    int row_count;                    // число строк таблицы
    int col_count;                    // число столбцов таблицы
    QTableWidget * ptr_table;         // таблица
    QStringList table_header_s_l;     // список строк с названиями столбцов таблицы
    // ----------------------------------------------------------------------------------------------------------------

    // подтаблица -----------------------------------------------------------------------------------------------------
    QVBoxLayout * sub_table_lo;       // указатель на менеджер компановки подтаблицы
    QScrollArea * sub_table_s_a;      // область прокрутки с подтаблицей
    int sub_row_count;                // число строк подтаблицы
    int sub_col_count;                // число столбцов подтаблицы
    QTableWidget * ptr_sub_table;     // подтаблица
    QStringList sub_table_header_s_l; // список строк с названиями столбцов подтаблицы
    // ----------------------------------------------------------------------------------------------------------------

    // группа кнопок строки -------------------------------------------------------------------------------------------
    QButtonGroup * b_g_delete;        // группа кнопок удаления строки таблицы
    // ----------------------------------------------------------------------------------------------------------------

    // группы кнопок подстроки ----------------------------------------------------------------------------------------
    QButtonGroup * b_g_sub_delete;    // группа кнопок удаления строки подтаблицы
    QButtonGroup * b_g_sub_add;       // группа кнопок добавления строки подтаблицы
    // ----------------------------------------------------------------------------------------------------------------

    // кнопки формы ---------------------------------------------------------------------------------------------------
    QPushButton * p_b_save;           // указатель на кнопку Cохранить таблицу
    QPushButton * p_b_add_row;        // указатель на кнопку Добавить новую строку
    // ----------------------------------------------------------------------------------------------------------------

    // комментарий ----------------------------------------------------------------------------------------------------
    QString comment;                  // строка с текстом комментария
    QLineEdit * variant_l_e;          // указатель на редактируемое поле с описанием контрольной задачи
    // ----------------------------------------------------------------------------------------------------------------

    // список элементов -----------------------------------------------------------------------------------------------
    etalon_row_view * first;          // указатель на первый элемент
    etalon_row_view * last;           // указатель на последний элемент
    // ----------------------------------------------------------------------------------------------------------------

public slots:
    // вызывается при нажатии кнопки Удалить строку (сигнал от _row_num строки таблицы)
    void p_b_delete_click(int _row_num);

    // вызывается при нажатии кнопки Удалить строку (сигнал от _row_num строки подтаблицы)
    void p_b_sub_delete_click(int _row_num);

    // вызывается при нажатии кнопки Добавить маневр (сигнал от _index индекса эталона в списке)
    void p_b_sub_add_click(int _index);

    // вызывается для проверки допустимости нажатия на кнопку Сохранить
    void table_p_b_save_enable(QString);
};

#endif // ETALON_TABLE_VIEW
