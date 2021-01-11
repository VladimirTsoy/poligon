#ifndef ZONE_TABLE_VIEW
#define ZONE_TABLE_VIEW

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

#include "zone_row_view.h"

// представление таблицы
class zone_table_view : public QObject
{
    Q_OBJECT
public:
    // конструктор
    zone_table_view(QVBoxLayout * _table_lo,
                    QPushButton * _p_b_save,
                    QPushButton * _p_b_add_row,
                    QLineEdit * _variant_l_e);

    // деструктор
    ~zone_table_view();

    // установка информации о таблице
    void set_table_info();

    // установка сигнально-слотового соединения изменения ячеек КР таблицы и возможностью нажатия на кнопку сохранить
    void set_zone_signal_slot_connection_cell_change_p_b_save_enable(zone_row_view * _iter);

    // установка сигнально-слотового соединения изменения ячеек маневра таблицы и возможностью нажатия на кнопку сохранить
    void set_maneuver_signal_slot_connection_cell_change_p_b_save_enable(zone_point_row_view * _iter);

    // вспомогательные функции ----------------------------------------------------------------------------------------
    // вернуть индекс КР по указателю на КР
    int ret_index_by_zone(zone_row_view * _zone);

    // вернуть указатель на КР по индексу КР
    zone_row_view * ret_zone_by_index(int _index);

    // вернуть указатель на КР по указателю на маневр
    zone_row_view * ret_zone_by_maneuver(zone_point_row_view * _maneuver);

    // вернуть указатель на КР по номеру строки маневра
    zone_row_view * ret_zone_by_row_num_maneuver(int _row_num);

    // вернуть указатель на маневр по номеру строки таблицы
    zone_point_row_view * ret_maneuver_by_row_num_maneuver(int _row_num);

    // вернуть номер строки таблицы, которую должен занять формуляр КР
    int ret_row_num_by_zone(zone_row_view * _zone);

    // вернуть номер строки таблицы, которую должен занять формуляр маневра
    int ret_row_num_by_maneuver(zone_point_row_view * _maneuver);

    // вернуть признак добавления новой строки в таблицу по указателю на маневр
    int ret_b_add_row_by_maneuver(zone_point_row_view * _maneuver);

    // вернуть признак удаления строки таблицы по указателю на маневр
    bool ret_b_delete_row_by_maneuver(zone_point_row_view * _maneuver);
    // ----------------------------------------------------------------------------------------------------------------

    // добавление нового основного элемента в список
    void add_new_major_element();

    // добавление нового второстепенного элемента в список
    void add_new_minor_element();

    // очистка списка
    void clear_list();

    // вставка списка в таблицу
    void insert_list_in_table();

    // добавление новой основной строки в таблицу
    void insert_major_row_in_table(zone_row_view * _iter);

    // добавление новой дополнительной строки в таблицу
    void insert_minor_row_in_table(zone_point_row_view * _iter);

    // переименование кнопок удалить маневр (+1), находящихся в таблице после маневра
    void rename_plus_p_b_delete_after_maneuver(zone_row_view * _zone,
                                               zone_point_row_view * _maneuver);

    // переименование кнопок удалить маневр (-1), находящихся в подтаблице после маневра
    void rename_minus_b_g_delete_after_maneuver(zone_row_view * _zone,
                                                zone_point_row_view * _maneuver,
                                                bool _b_delete);

    // изменение таблицы перед удалением КР
    void table_change_before_delete_zone(zone_row_view * _zone_delete);


    // изъятие маневра из списка (без удаления)
    void withdrawal_maneuver_from_list(zone_row_view * _zone,
                                       zone_point_row_view * _maneuver);

    QVBoxLayout * ret_table_lo();                                // вернуть указатель на менеджер компановки таблицы
    QScrollArea * ret_table_s_a();                               // вернуть область прокрутки с таблицей
    int ret_row_count();                                         // вернуть число строк таблицы
    int ret_col_count();                                         // вернуть число столбцов таблицы
    QTableWidget * ret_ptr_table();                              // вернуть таблицу
    QStringList ret_table_header_s_l();                          // вернуть список строк с названиями столбцов таблицы
    QButtonGroup * ret_b_g_major_delete();                       // вернуть основную группу кнопок удаления строки
    QButtonGroup * ret_b_g_minor_delete();                       // вернуть дополнительную группу кнопок удаления строки
    QButtonGroup * ret_b_g_add();                                // вернуть группу кнопок добавления маневра
    QPushButton * ret_p_b_save();                                // вернуть указатель на кнопку Cохранить таблицу
    QPushButton * ret_p_b_add_row();                             // вернуть указатель на кнопку Добавить новую строку
    QString ret_comment();                                       // вернуть комментарий
    QLineEdit * ret_variant_l_e();                               // вернуть указатель на редактируемое поле с описанием контрольной задачи
    zone_row_view * ret_first();                                   // вернуть указатель на первый элемент
    zone_row_view * ret_last();                                    // вернуть указатель на последний элемент

    void set_table_lo(QVBoxLayout * _table_lo);                  // установить указатель на менеджер компановки таблицы
    void set_table_s_a(QScrollArea * _table_s_a);                // установить область прокрутки с таблицей
    void set_row_count(int _row_count);                          // установить число строк таблицы
    void set_col_count(int _col_count);                          // установить число столбцов таблицы
    void set_ptr_table(QTableWidget * _ptr_table);               // установить таблицу
    void set_table_header_s_l(QStringList _table_header_s_l);    // установить список строк с названиями столбцов таблицы
    void set_b_g_major_delete(QButtonGroup * _b_g_major_delete); // установить основную группу кнопок удаления строки
    void set_b_g_minor_delete(QButtonGroup * _b_g_minor_delete); // установить дополнительную группу кнопок удаления строки
    void set_b_g_add(QButtonGroup * _b_g_add);                   // установить группу кнопок добавления маневра
    void set_p_b_save(QPushButton * _p_b_save);                  // установить указатель на кнопку Cохранить таблицу
    void set_p_b_add_row(QPushButton * _p_b_add_row);            // установить указатель на кнопку Добавить новую строку
    void set_comment(QString _comment);                          // установить комментарий
    void set_variant_l_e(QLineEdit * _variant_l_e);              // установить указатель на редактируемое поле с описанием контрольной задачи
    void set_first(zone_row_view * _first);                        // установить указатель на первый элемент
    void set_last(zone_row_view * _last);                          // установить указатель на последний элемент

private:
    // таблица --------------------------------------------------------------------------------------------------------
    QVBoxLayout * table_lo;          // указатель на менеджер компановки таблицы
    QScrollArea * table_s_a;         // область прокрутки с таблицей
    int row_count;                   // число строк таблицы
    int col_count;                   // число столбцов таблицы
    QTableWidget * ptr_table;        // таблица
    QStringList table_header_s_l;    // список строк с названиями столбцов таблицы
    // ----------------------------------------------------------------------------------------------------------------

    // группа кнопок удаления строки ----------------------------------------------------------------------------------
    QButtonGroup * b_g_major_delete; // основная группа кнопок
    QButtonGroup * b_g_minor_delete; // дополнительная группа кнопок
    // ----------------------------------------------------------------------------------------------------------------

    // группа кнопок добавления маневра -------------------------------------------------------------------------------
    QButtonGroup * b_g_add;
    // ----------------------------------------------------------------------------------------------------------------

    // кнопки формы ---------------------------------------------------------------------------------------------------
    QPushButton * p_b_save;          // указатель на кнопку Cохранить таблицу
    QPushButton * p_b_add_row;       // указатель на кнопку Добавить новую строку
    // ----------------------------------------------------------------------------------------------------------------

    // комментарий ----------------------------------------------------------------------------------------------------
    QString comment;                 // строка с текстом комментария
    QLineEdit * variant_l_e;         // указатель на редактируемое поле с описанием контрольной задачи
    // ----------------------------------------------------------------------------------------------------------------

    // список элементов -----------------------------------------------------------------------------------------------
    zone_row_view * first;             // указатель на первый элемент
    zone_row_view * last;              // указатель на последний элемент
    // ----------------------------------------------------------------------------------------------------------------

public slots:
    // вызывается при нажатии кнопки Удалить строку (сигнал от _index положения КР в списке)
    void p_b_major_delete_click(int _index);

    // вызывается при нажатии кнопки Удалить строку (сигнал от _row_num строки таблицы)
    void p_b_minor_delete_click(int _row_num);

    // вызывается при нажатии на кнопку +
    void p_b_add_click(int _index);

    // вызывается для проверки допустимости нажатия на кнопку Сохранить
    void table_p_b_save_enable(QString);
};

#endif // ZONE_TABLE_VIEW
