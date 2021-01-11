#include "sens_site_table_view.h"

// конструктор
sens_site_table_view::sens_site_table_view(QVBoxLayout * _table_lo,
                                           QPushButton * _p_b_save,
                                           QPushButton * _p_b_add_row,
                                           QLineEdit * _variant_l_e)
{
    table_lo = _table_lo;
    table_s_a = new QScrollArea();

    // установка информации о таблице
    set_table_info();

    ptr_table->setRowCount(row_count);
    ptr_table->setColumnCount(col_count);
    ptr_table->setHorizontalHeaderLabels(table_header_s_l);
    ptr_table->setTabKeyNavigation(false);
    for(int i=0; i<col_count; i++)
    {
        ptr_table->setColumnWidth(i, 140);
    }
    table_s_a->setWidget(ptr_table);
    table_s_a->setWidgetResizable(true);
    table_lo->addWidget(table_s_a);

    b_g_delete = new QButtonGroup(NULL);
    connect(b_g_delete, SIGNAL(buttonClicked(int)), SLOT(p_b_delete_click(int)));

    p_b_save = _p_b_save;
    p_b_add_row = _p_b_add_row;

    comment = "";
    variant_l_e = _variant_l_e;

    first = NULL;
    last = NULL;
}

// деструктор
sens_site_table_view::~sens_site_table_view()
{
    comment = "";
    variant_l_e = NULL;

    p_b_save = NULL;
    p_b_add_row = NULL;

    clear_list();

    first = NULL;
    last = NULL;

    delete b_g_delete;
    b_g_delete = NULL;

    table_header_s_l.clear();

    col_count = 0;
    row_count = 0;

    delete ptr_table;
    ptr_table = NULL;

    delete  table_s_a;
    table_s_a = NULL;

    table_lo = NULL;
}

// установка информации о таблице
void sens_site_table_view::set_table_info()
{
    row_count = 0;
    col_count = 5;
    ptr_table = new QTableWidget();
    table_header_s_l << "number"
                     << "sensChar"
                     << "x"
                     << "y"
                     << "Удалить элемент";
}

// установка сигнально-слотового соединения изменения ячеек таблицы и возможностью нажатия на кнопку сохранить
void sens_site_table_view::set_signal_slot_connection_cell_change_p_b_save_enable(sens_site_row_view * _iter)
{
    connect(_iter->ret_number()->ret_l_e(),   SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
    connect(_iter->ret_charSens()->ret_l_e(), SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
    connect(_iter->ret_x()->ret_l_e(),        SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
    connect(_iter->ret_y()->ret_l_e(),        SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
}

// добавление нового элемента в список
void sens_site_table_view::add_new_element()
{
    if(first == NULL) // список пуст
    {
        last = new sens_site_row_view();
        first = last;
    }
    else // в списке имеются элементы
    {
        sens_site_row_view * ptr_new_element;
        ptr_new_element = new sens_site_row_view();
        last->set_next(ptr_new_element);
        ptr_new_element->set_prev(last);
        last = ptr_new_element;
    }

    set_signal_slot_connection_cell_change_p_b_save_enable(last);

    table_p_b_save_enable("");
}

// очистка списка
void sens_site_table_view::clear_list()
{
    sens_site_row_view * iter;
    iter = first;
    sens_site_row_view * iter_delete;

    while(iter != NULL)
    {
        iter_delete = iter;
        iter = iter->ret_next();
        delete iter_delete;
    }
}

// вставка списка в таблицу
void sens_site_table_view::insert_list_in_table()
{
    variant_l_e->setText(comment);

    sens_site_row_view * iter_view;
    iter_view = first;

    while(iter_view != NULL)
    {
        insert_row_in_table(iter_view);
        iter_view = iter_view->ret_next();
    }
}

// добавление новой строки в таблицу
void sens_site_table_view::insert_row_in_table(sens_site_row_view * _iter)
{
    row_count++;
    ptr_table->setRowCount(row_count);

    ptr_table->setCellWidget(row_count-1, 0,  _iter->ret_number()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 1,  _iter->ret_charSens()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 2,  _iter->ret_x()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 3,  _iter->ret_y()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 4,  _iter->ret_p_b_delete());

    b_g_delete->addButton(_iter->ret_p_b_delete(), row_count-1);
}

QVBoxLayout * sens_site_table_view::ret_table_lo() // вернуть указатель на менеджер компановки таблицы
{
    return table_lo;
}

QScrollArea * sens_site_table_view::ret_table_s_a() // вернуть область прокрутки с таблицей
{
    return table_s_a;
}

int sens_site_table_view::ret_row_count() // вернуть число строк таблицы
{
    return row_count;
}

int sens_site_table_view::ret_col_count() // вернуть число столбцов таблицы
{
    return col_count;
}

QTableWidget * sens_site_table_view::ret_ptr_table() // вернуть таблицу
{
    return ptr_table;
}

QStringList sens_site_table_view::ret_table_header_s_l() // вернуть список строк с названиями столбцов таблицы
{
    return table_header_s_l;
}

QButtonGroup * sens_site_table_view::ret_b_g_delete() // вернуть группу кнопок удаления строки
{
    return b_g_delete;
}

QPushButton * sens_site_table_view::ret_p_b_save() // вернуть указатель на кнопку Cохранить таблицу
{
    return p_b_save;
}

QPushButton * sens_site_table_view::ret_p_b_add_row() // вернуть указатель на кнопку Добавить новую строку
{
    return p_b_add_row;
}

QString sens_site_table_view::ret_comment() // вернуть комментарий
{
    return comment;
}

QLineEdit * sens_site_table_view::ret_variant_l_e() // вернуть указатель на редактируемое поле с описанием контрольной задачи
{
    return variant_l_e;
}

sens_site_row_view * sens_site_table_view::ret_first() // вернуть указатель на первый элемент
{
    return first;
}

sens_site_row_view * sens_site_table_view::ret_last() // вернуть указатель на последний элемент
{
    return last;
}

void sens_site_table_view::set_table_lo(QVBoxLayout * _table_lo) // установить указатель на менеджер компановки таблицы
{
    table_lo = _table_lo;
}

void sens_site_table_view::set_table_s_a(QScrollArea * _table_s_a) // установить область прокрутки с таблицей
{
    table_s_a = _table_s_a;
}

void sens_site_table_view::set_row_count(int _row_count) // установить число строк таблицы
{
    row_count = _row_count;
}

void sens_site_table_view::set_col_count(int _col_count) // установить число столбцов таблицы
{
    col_count = _col_count;
}

void sens_site_table_view::set_ptr_table(QTableWidget * _ptr_table) // установить таблицу
{
    ptr_table = _ptr_table;
}

void sens_site_table_view::set_table_header_s_l(QStringList _table_header_s_l) // установить список строк с названиями столбцов таблицы
{
    table_header_s_l = _table_header_s_l;
}

void sens_site_table_view::set_p_b_save(QPushButton * _p_b_save) // установить указатель на кнопку Cохранить таблицу
{
    p_b_save = _p_b_save;
}

void sens_site_table_view::set_p_b_add_row(QPushButton * _p_b_add_row) // установить указатель на кнопку Добавить новую строку
{
    p_b_add_row = _p_b_add_row;
}

void sens_site_table_view::set_comment(QString _comment) // установить комментарий
{
    comment = _comment;
}

void sens_site_table_view::set_b_g_delete(QButtonGroup * _b_g_delete) // установить группу кнопок удаления строки
{
    b_g_delete = _b_g_delete;
}

void sens_site_table_view::set_variant_l_e(QLineEdit * _variant_l_e) // установить указатель на редактируемое поле с описанием контрольной задачи
{
    variant_l_e = _variant_l_e;
}

void sens_site_table_view::set_first(sens_site_row_view * _first) // установить указатель на первый элемент
{
    first = _first;
}

void sens_site_table_view::set_last(sens_site_row_view * _last) // установить указатель на последний элемент
{
    last = _last;
}

// вызывается при нажатии кнопки Удалить строку (сигнал от _row_num строки таблицы)
void sens_site_table_view::p_b_delete_click(int _row_num)
{
    sens_site_row_view * iter_delete;
    iter_delete = first;

    for(int i=0; i<_row_num; i++)
    {
        iter_delete = iter_delete->ret_next();
    }

    b_g_delete->removeButton(iter_delete->ret_p_b_delete());

    sens_site_row_view * iter_rename;
    iter_rename = iter_delete->ret_next();

    while(iter_rename != NULL)
    {
        int old_id;
        old_id = b_g_delete->id(iter_rename->ret_p_b_delete());
        b_g_delete->setId(iter_rename->ret_p_b_delete(), old_id-1);

        iter_rename = iter_rename->ret_next();
    }

    if(iter_delete == first)
    {
        if(first->ret_next() == NULL)
        {
            first = NULL;
            last = NULL;
        }
        else
        {
            first = iter_delete->ret_next();
            first->set_prev(NULL);
        }
    }
    else if(iter_delete == last)
    {
        last = iter_delete->ret_prev();
        last->set_next(NULL);
    }
    else
    {
        iter_delete->ret_next()->set_prev(iter_delete->ret_prev());
        iter_delete->ret_prev()->set_next(iter_delete->ret_next());
    }

    delete iter_delete;

    ptr_table->removeRow(_row_num);
    row_count--;
    ptr_table->setRowCount(row_count);

    table_p_b_save_enable("");
}

// вызывается для проверки допустимости нажатия на кнопку Сохранить
void sens_site_table_view::table_p_b_save_enable(QString)
{
    bool b_enable;
    b_enable = true;

    sens_site_row_view * iter;
    iter = first;

    while(iter != NULL)
    {
        if(iter->ret_number()->ret_b_correct() == false ||
           iter->ret_charSens()->ret_b_correct() == false ||
           iter->ret_x()->ret_b_correct() == false ||
           iter->ret_y()->ret_b_correct() == false)
        {
            b_enable = false;
            break;
        }
        iter = iter->ret_next();
    }

    if(b_enable == true)
    {
        p_b_save->setEnabled(true);
    }
    else
    {
        p_b_save->setEnabled(false);
    }
}
