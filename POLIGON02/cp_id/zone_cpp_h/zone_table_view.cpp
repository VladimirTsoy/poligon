#include "zone_table_view.h"

// конструктор
zone_table_view::zone_table_view(QVBoxLayout * _table_lo,
                                 QPushButton * _p_b_save,
                                 QPushButton * _p_b_add_row,
                                 QLineEdit * _variant_l_e)
{
    b_g_major_delete = new QButtonGroup(NULL);
    connect(b_g_major_delete, SIGNAL(buttonClicked(int)), SLOT(p_b_major_delete_click(int)));

    b_g_minor_delete = new QButtonGroup(NULL);
    connect(b_g_minor_delete, SIGNAL(buttonClicked(int)), SLOT(p_b_minor_delete_click(int)));

    b_g_add = new QButtonGroup(NULL);
    connect(b_g_add, SIGNAL(buttonClicked(int)), SLOT(p_b_add_click(int)));

    comment = "";
    variant_l_e = _variant_l_e;

    first = NULL;
    last = NULL;

    p_b_save = _p_b_save;
    p_b_add_row = _p_b_add_row;

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
        ptr_table->setColumnWidth(i, 125);
    }
    table_s_a->setWidget(ptr_table);
    table_s_a->setWidgetResizable(true);
    table_lo->addWidget(table_s_a);
}

// деструктор
zone_table_view::~zone_table_view()
{
    comment = "";
    variant_l_e = NULL;

    p_b_save = NULL;
    p_b_add_row = NULL;

    clear_list();

    first = NULL;
    last = NULL;

    delete b_g_major_delete;
    b_g_major_delete = NULL;

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
void zone_table_view::set_table_info()
{
    row_count = 0;
    col_count = 13;
    ptr_table = new QTableWidget();
    table_header_s_l << "number"
                     << "r"
                     << "g"
                     << "b"
                     << "a"
                     << "color"
                     << "countPoint"
                     << "Добавить точку"
                     << "number_point"
                     << "x"
                     << "y"
                     << "Удалить точку"
                     << "Удалить элемент";
}

// установка сигнально-слотового соединения изменения ячеек КР таблицы и возможностью нажатия на кнопку сохранить
void zone_table_view::set_zone_signal_slot_connection_cell_change_p_b_save_enable(zone_row_view * _iter)
{
    connect(_iter->ret_number()->ret_l_e(),     SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_iter->ret_r()->ret_l_e(),          SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_iter->ret_g()->ret_l_e(),          SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_iter->ret_b()->ret_l_e(),          SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_iter->ret_a()->ret_l_e(),          SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_iter->ret_countPoint()->ret_l_e(), SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
}

// установка сигнально-слотового соединения изменения ячеек маневра таблицы и возможностью нажатия на кнопку сохранить
void zone_table_view::set_maneuver_signal_slot_connection_cell_change_p_b_save_enable(zone_point_row_view * _iter)
{
    connect(_iter->ret_number()->ret_l_e(), SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_iter->ret_x()->ret_l_e(),      SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_iter->ret_y()->ret_l_e(),      SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
}

// вернуть индекс КР по указателю на КР
int zone_table_view::ret_index_by_zone(zone_row_view * _zone)
{
    int index;
    index = 0;

    zone_row_view * iter_zone;
    iter_zone = first;

    while(iter_zone != _zone)
    {
        index++;
        iter_zone = iter_zone->ret_next();
    }

    return index;
}

// вернуть указатель на КР по индексу КР
zone_row_view * zone_table_view::ret_zone_by_index(int _index)
{
    int cur_index;
    cur_index = 0;

    zone_row_view * iter_zone;
    iter_zone = first;

    while(cur_index != _index)
    {
        iter_zone = iter_zone->ret_next();
        cur_index++;
    }

    return iter_zone;
}

// вернуть указатель на КР по указателю на маневр
zone_row_view * zone_table_view::ret_zone_by_maneuver(zone_point_row_view * _maneuver)
{
    zone_row_view * iter_zone;
    zone_point_row_view * iter_maneuver;
    iter_zone = first;

    while(iter_zone != NULL)
    {
        iter_maneuver = iter_zone->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_maneuver == _maneuver)
            {
                return iter_zone;
            }
            iter_maneuver = iter_maneuver->ret_next();
        }
        iter_zone = iter_zone->ret_next();
    }

    return NULL;
}

// вернуть указатель на КР по номеру строки маневра
zone_row_view * zone_table_view::ret_zone_by_row_num_maneuver(int _row_num)
{
    int cur_row_num;
    cur_row_num = 0;

    zone_row_view * iter_zone;
    zone_point_row_view * iter_maneuver;

    iter_zone = first;

    while(iter_zone != NULL)
    {
        iter_maneuver = iter_zone->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_zone->ret_first() != iter_maneuver)
            {
                cur_row_num++;
            }
            if(_row_num == cur_row_num)
            {
                return iter_zone;
            }
            iter_maneuver = iter_maneuver->ret_next();
        }
        cur_row_num++;
        iter_zone = iter_zone->ret_next();
    }

    return NULL;
}

// вернуть указатель на маневр по номеру строки таблицы
zone_point_row_view * zone_table_view::ret_maneuver_by_row_num_maneuver(int _row_num)
{
    int cur_row_num;
    cur_row_num = 0;

    zone_row_view * iter_zone;
    zone_point_row_view * iter_maneuver;
    iter_zone = first;

    while(iter_zone != NULL)
    {
        iter_maneuver = iter_zone->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_zone->ret_first() != iter_maneuver)
            {
                cur_row_num++;
            }
            if(_row_num == cur_row_num)
            {
                return iter_maneuver;
            }
            iter_maneuver = iter_maneuver->ret_next();
        }
        cur_row_num++;
        iter_zone = iter_zone->ret_next();
    }

    return NULL;
}

// вернуть номер строки таблицы, которую должен занять формуляр КР
int zone_table_view::ret_row_num_by_zone(zone_row_view * _zone)
{
    int row_num;
    row_num = 0;

    zone_row_view * iter_zone;
    zone_point_row_view * iter_maneuver;
    iter_zone = first;

    while(iter_zone != _zone)
    {
        iter_maneuver = iter_zone->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_maneuver != iter_zone->ret_first())
            {
                row_num++;
            }
            iter_maneuver = iter_maneuver->ret_next();
        }
        row_num++;
        iter_zone = iter_zone->ret_next();
    }

    return row_num;
}

// вернуть номер строки таблицы, которую должен занять формуляр маневра
int zone_table_view::ret_row_num_by_maneuver(zone_point_row_view * _maneuver)
{
    int row_num;
    row_num = 0;

    bool b_break;
    b_break = false;

    zone_row_view * iter_zone;
    zone_point_row_view * iter_maneuver;
    iter_zone = first;

    while(iter_zone != NULL)
    {
        iter_maneuver = iter_zone->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_maneuver != iter_zone->ret_first())
            {
                row_num++;
            }
            if(iter_maneuver == _maneuver)
            {
                b_break = true;
                break;
            }
            iter_maneuver = iter_maneuver->ret_next();
        }
        if(b_break == true)
        {
            break;
        }
        row_num++;
        iter_zone = iter_zone->ret_next();
    }

    return row_num;
}

// вернуть признак добавления новой строки в таблицу по указателю на маневр
int zone_table_view::ret_b_add_row_by_maneuver(zone_point_row_view * _maneuver)
{
    bool b_add_new_row;
    b_add_new_row = true;

    bool b_break;
    b_break = false;

    zone_row_view * iter_zone;
    zone_point_row_view * iter_maneuver;
    iter_zone = first;

    while(iter_zone != NULL)
    {
        iter_maneuver = iter_zone->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_maneuver == _maneuver)
            {
                if(iter_zone->ret_first() == _maneuver)
                {
                    b_add_new_row = false;
                }
                b_break = true;
                break;
            }
            iter_maneuver = iter_maneuver->ret_next();
        }
        if(b_break == true)
        {
            break;
        }
        iter_zone = iter_zone->ret_next();
    }

    return b_add_new_row;
}

// вернуть признак удаления строки таблицы по указателю на маневр
bool zone_table_view::ret_b_delete_row_by_maneuver(zone_point_row_view * _maneuver)
{
    if(_maneuver->ret_next() == NULL && _maneuver->ret_prev() == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}


// добавление нового основного элемента в список
void zone_table_view::add_new_major_element()
{
    if(first == NULL) // список пуст
    {
        last = new zone_row_view();
        first = last;
    }
    else // в списке имеются элементы
    {
        zone_row_view * ptr_new_element;
        ptr_new_element = new zone_row_view();
        last->set_next(ptr_new_element);
        ptr_new_element->set_prev(last);
        last = ptr_new_element;
    }

    set_zone_signal_slot_connection_cell_change_p_b_save_enable(last);

    table_p_b_save_enable("");
}

// добавление нового второстепенного элемента в список
void zone_table_view::add_new_minor_element()
{
    last->add_new_element();
    table_p_b_save_enable("");
}

// очистка списка
void zone_table_view::clear_list()
{
    zone_row_view * iter;
    iter = first;
    zone_row_view * iter_delete;

    while(iter != NULL)
    {
        iter_delete = iter;
        iter = iter->ret_next();
        delete iter_delete;
    }
}

// вставка списка в таблицу
void zone_table_view::insert_list_in_table()
{
    variant_l_e->setText(comment);

    zone_row_view * zone_view;
    zone_view = first;

    zone_point_row_view * maneuver_view;

    while(zone_view != NULL)
    {
        insert_major_row_in_table(zone_view);

        maneuver_view = zone_view->ret_first();

        while(maneuver_view != NULL)
        {
            insert_minor_row_in_table(maneuver_view);

            maneuver_view = maneuver_view->ret_next();
        }

        zone_view = zone_view->ret_next();
    }
}

// добавление новой основной строки в таблицу
void zone_table_view::insert_major_row_in_table(zone_row_view * _iter)
{
    int row_num;
    row_num = 0;

    // вернуть номер строки таблицы, которую должен занять формуляр КР
    row_num = ret_row_num_by_zone(_iter);

    // вставка новой строки в подтаблицу
    row_count++;
    ptr_table->insertRow(row_num);

    // вставка виджетов КР в таблицу
    ptr_table->setCellWidget(row_num, 0,  _iter->ret_number()->ret_l_e());
    ptr_table->setCellWidget(row_num, 1,  _iter->ret_r()->ret_l_e());
    ptr_table->setCellWidget(row_num, 2,  _iter->ret_g()->ret_l_e());
    ptr_table->setCellWidget(row_num, 3,  _iter->ret_b()->ret_l_e());
    ptr_table->setCellWidget(row_num, 4,  _iter->ret_a()->ret_l_e());
    ptr_table->setCellWidget(row_num, 5,  _iter->ret_color()->ret_l_e());
    ptr_table->setCellWidget(row_num, 6,  _iter->ret_countPoint()->ret_l_e());
    ptr_table->setCellWidget(row_num, 7,  _iter->ret_p_b_add());
    ptr_table->setCellWidget(row_num, 12, _iter->ret_p_b_delete());

    b_g_major_delete->addButton(_iter->ret_p_b_delete(), ret_index_by_zone(_iter));
    b_g_add->addButton(_iter->ret_p_b_add(), ret_index_by_zone(_iter));
}

// добавление новой дополнительной строки в таблицу
void zone_table_view::insert_minor_row_in_table(zone_point_row_view * _iter)
{
    int row_num;
    bool b_add_new_row;

    // вернуть номер строки таблицы, которую должен занять формуляр маневра
    row_num = ret_row_num_by_maneuver(_iter);

    // вернуть признак добавления новой строки в таблицу по указателю на маневр
    b_add_new_row = ret_b_add_row_by_maneuver(_iter);

    // вставка новой строки в подтаблицу
    if(b_add_new_row == true)
    {
        row_count++;
        ptr_table->insertRow(row_num);
    }

    // вставка виджетов маневра в подтаблицу
    ptr_table->setCellWidget(row_num, 8,  _iter->ret_number()->ret_l_e());
    ptr_table->setCellWidget(row_num, 9,  _iter->ret_x()->ret_l_e());
    ptr_table->setCellWidget(row_num, 10, _iter->ret_y()->ret_l_e());
    ptr_table->setCellWidget(row_num, 11, _iter->ret_p_b_delete());

    // добавление кнопки Удалить маневр в группу кнопок
    b_g_minor_delete->addButton(_iter->ret_p_b_delete(), row_num);

    // вернуть указатель на эталон по указателю на маневр
    zone_row_view * iter_zone;
    iter_zone = ret_zone_by_maneuver(_iter);

    // переименование кнопок удалить маневр (+1), находящихся в таблице после маневра
    rename_plus_p_b_delete_after_maneuver(iter_zone, _iter);

    //////////////////////////////////////////////////////////////////////////////////////////////////
    if(b_add_new_row == true)
    {
        int major_row_num;
        major_row_num = ret_row_num_by_zone(iter_zone);
        ptr_table->setSpan(major_row_num, 0,  ptr_table->rowSpan(major_row_num, 0)  +1, 1);
        ptr_table->setSpan(major_row_num, 1,  ptr_table->rowSpan(major_row_num, 1)  +1, 1);
        ptr_table->setSpan(major_row_num, 2,  ptr_table->rowSpan(major_row_num, 2)  +1, 1);
        ptr_table->setSpan(major_row_num, 3,  ptr_table->rowSpan(major_row_num, 3)  +1, 1);
        ptr_table->setSpan(major_row_num, 4,  ptr_table->rowSpan(major_row_num, 4)  +1, 1);
        ptr_table->setSpan(major_row_num, 5,  ptr_table->rowSpan(major_row_num, 5)  +1, 1);
        ptr_table->setSpan(major_row_num, 6,  ptr_table->rowSpan(major_row_num, 6)  +1, 1);
        ptr_table->setSpan(major_row_num, 7,  ptr_table->rowSpan(major_row_num, 7)  +1, 1);
        ptr_table->setSpan(major_row_num, 12, ptr_table->rowSpan(major_row_num, 12) +1, 1);

        QString help_str;
        help_str = ptr_table->horizontalHeaderItem(0)->text();
        ptr_table->horizontalHeaderItem(0)->setText("");
        ptr_table->horizontalHeaderItem(0)->setText(help_str);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
}

// переименование кнопок удалить маневр (+1), находящихся в таблице после маневра
void zone_table_view::rename_plus_p_b_delete_after_maneuver(zone_row_view * _zone,
                                                          zone_point_row_view * _maneuver)
{
    if(_zone->ret_first() != _maneuver)
    {
        zone_row_view * iter_zone_rename;
        zone_point_row_view * iter_maneuver_rename;
        iter_zone_rename = _zone->ret_next();

        while(iter_zone_rename != NULL)
        {
            iter_maneuver_rename = iter_zone_rename->ret_first();
            while(iter_maneuver_rename != NULL)
            {
                int old_id;
                old_id = b_g_minor_delete->id(iter_maneuver_rename->ret_p_b_delete());
                b_g_minor_delete->setId(iter_maneuver_rename->ret_p_b_delete(), old_id+1);
                iter_maneuver_rename = iter_maneuver_rename->ret_next();
            }
            iter_zone_rename = iter_zone_rename->ret_next();
        }
    }
}

// переименование кнопок удалить маневр (-1), находящихся в подтаблице после маневра
void zone_table_view::rename_minus_b_g_delete_after_maneuver(zone_row_view * _zone,
                                                           zone_point_row_view * _maneuver,
                                                           bool _b_delete)
{
    if(_b_delete == true)
    {
        // переименование кнопок маневров, идущих после _maneuver
        zone_point_row_view * iter_maneuver_rename;
        iter_maneuver_rename = _maneuver->ret_next();

        while(iter_maneuver_rename != NULL)
        {
            int old_id;
            old_id = b_g_minor_delete->id(iter_maneuver_rename->ret_p_b_delete());
            b_g_minor_delete->setId(iter_maneuver_rename->ret_p_b_delete(), old_id-1);
            iter_maneuver_rename = iter_maneuver_rename->ret_next();
        }

        // переименование кнопок маневров, идущих после _zone
        zone_row_view * iter_zone_rename;
        iter_zone_rename = _zone->ret_next();

        while(iter_zone_rename != NULL)
        {
            iter_maneuver_rename = iter_zone_rename->ret_first();

            while(iter_maneuver_rename != NULL)
            {
                int old_id;
                old_id = b_g_minor_delete->id(iter_maneuver_rename->ret_p_b_delete());
                b_g_minor_delete->setId(iter_maneuver_rename->ret_p_b_delete(), old_id-1);
                iter_maneuver_rename = iter_maneuver_rename->ret_next();
            }

            iter_zone_rename = iter_zone_rename->ret_next();
        }
    }
}

// изменение таблицы перед удалением КР
void zone_table_view::table_change_before_delete_zone(zone_row_view * _zone_delete)
{
    // удаление маневров, принадлежащих КР ----------------------------------------------------------------------------
    zone_point_row_view * iter_maneuver;
    iter_maneuver = _zone_delete->ret_first();
    while(iter_maneuver != NULL)
    {
        zone_point_row_view * maneuver_delete;
        maneuver_delete = iter_maneuver;
        iter_maneuver = iter_maneuver->ret_next();

        int minor_row_delete;

        // вернуть номер строки таблицы, которую должен занять формуляр маневра
        minor_row_delete = ret_row_num_by_maneuver(maneuver_delete);

        // вызывается при нажатии кнопки Удалить строку (сигнал от minor_row_delete строки таблицы)
        p_b_minor_delete_click(minor_row_delete);
    }
    // ----------------------------------------------------------------------------------------------------------------

    // переименование кнопок Удалить маневр, находящихся после удаляемого КР ------------------------------------------
    zone_row_view * iter_zone_rename;
    iter_zone_rename = _zone_delete->ret_next();

    zone_point_row_view * iter_maneuver_rename;

    while(iter_zone_rename != NULL)
    {
        iter_maneuver_rename = iter_zone_rename->ret_first();

        while(iter_maneuver_rename != NULL)
        {
            int old_id;
            old_id = b_g_minor_delete->id(iter_maneuver_rename->ret_p_b_delete());
            b_g_minor_delete->setId(iter_maneuver_rename->ret_p_b_delete(), old_id-1);
            iter_maneuver_rename = iter_maneuver_rename->ret_next();
        }

        iter_zone_rename = iter_zone_rename->ret_next();
    }
    // ----------------------------------------------------------------------------------------------------------------
}

// изъятие маневра из списка (без удаления)
void zone_table_view::withdrawal_maneuver_from_list(zone_row_view * _zone,
                                                  zone_point_row_view * _maneuver)
{
    if(_maneuver == _zone->ret_first())
    {
        if(_maneuver->ret_next() == NULL)
        {
            _zone->set_first(NULL);
            _zone->set_last(NULL);
        }
        else
        {
            _zone->set_first(_maneuver->ret_next());
            _zone->ret_first()->set_prev(NULL);
        }
    }
    else if(_maneuver == _zone->ret_last())
    {
        _zone->set_last(_maneuver->ret_prev());
        _zone->ret_last()->set_next(NULL);
    }
    else
    {
        _maneuver->ret_next()->set_prev(_maneuver->ret_prev());
        _maneuver->ret_prev()->set_next(_maneuver->ret_next());
    }
}

QVBoxLayout * zone_table_view::ret_table_lo() // вернуть указатель на менеджер компановки таблицы
{
    return table_lo;
}

QScrollArea * zone_table_view::ret_table_s_a() // вернуть область прокрутки с таблицей
{
    return table_s_a;
}

int zone_table_view::ret_row_count() // вернуть число строк таблицы
{
    return row_count;
}

int zone_table_view::ret_col_count() // вернуть число столбцов таблицы
{
    return col_count;
}

QTableWidget * zone_table_view::ret_ptr_table() // вернуть таблицу
{
    return ptr_table;
}

QStringList zone_table_view::ret_table_header_s_l() // вернуть список строк с названиями столбцов таблицы
{
    return table_header_s_l;
}

QButtonGroup * zone_table_view::ret_b_g_major_delete() // вернуть основную группу кнопок удаления строки
{
    return b_g_major_delete;
}

QButtonGroup * zone_table_view::ret_b_g_minor_delete() // вернуть дополнительную группу кнопок удаления строки
{
    return b_g_minor_delete;
}

QButtonGroup * zone_table_view::ret_b_g_add() // вернуть группу кнопок добавления маневра
{
    return b_g_add;
}

QPushButton * zone_table_view::ret_p_b_save() // вернуть указатель на кнопку Cохранить таблицу
{
    return p_b_save;
}

QPushButton * zone_table_view::ret_p_b_add_row() // вернуть указатель на кнопку Добавить новую строку
{
    return p_b_add_row;
}

QString zone_table_view::ret_comment() // вернуть комментарий
{
    return comment;
}

QLineEdit * zone_table_view::ret_variant_l_e() // вернуть указатель на редактируемое поле с описанием контрольной задачи
{
    return variant_l_e;
}

zone_row_view * zone_table_view::ret_first() // вернуть указатель на первый элемент
{
    return first;
}

zone_row_view * zone_table_view::ret_last() // вернуть указатель на последний элемент
{
    return last;
}

void zone_table_view::set_table_lo(QVBoxLayout * _table_lo) // установить указатель на менеджер компановки таблицы
{
    table_lo = _table_lo;
}

void zone_table_view::set_table_s_a(QScrollArea * _table_s_a) // установить область прокрутки с таблицей
{
    table_s_a = _table_s_a;
}

void zone_table_view::set_row_count(int _row_count) // установить число строк таблицы
{
    row_count = _row_count;
}

void zone_table_view::set_col_count(int _col_count) // установить число столбцов таблицы
{
    col_count = _col_count;
}

void zone_table_view::set_ptr_table(QTableWidget * _ptr_table) // установить таблицу
{
    ptr_table = _ptr_table;
}

void zone_table_view::set_table_header_s_l(QStringList _table_header_s_l) // установить список строк с названиями столбцов таблицы
{
    table_header_s_l = _table_header_s_l;
}

void zone_table_view::set_b_g_major_delete(QButtonGroup * _b_g_major_delete) // установить основную группу кнопок удаления строки
{
    b_g_major_delete = _b_g_major_delete;
}

void zone_table_view::set_b_g_minor_delete(QButtonGroup * _b_g_minor_delete)  // установить дополнительную группу кнопок удаления строки
{
    b_g_minor_delete = _b_g_minor_delete;
}

void zone_table_view::set_b_g_add(QButtonGroup * _b_g_add) // установить группу кнопок добавления маневра
{
    b_g_add = _b_g_add;
}

void zone_table_view::set_p_b_save(QPushButton * _p_b_save) // установить указатель на кнопку Cохранить таблицу
{
    p_b_save = _p_b_save;
}

void zone_table_view::set_p_b_add_row(QPushButton * _p_b_add_row) // установить указатель на кнопку Добавить новую строку
{
    p_b_add_row = _p_b_add_row;
}

void zone_table_view::set_comment(QString _comment) // установить комментарий
{
    comment = _comment;
}

void zone_table_view::set_variant_l_e(QLineEdit * _variant_l_e) // установить указатель на редактируемое поле с описанием контрольной задачи
{
    variant_l_e = _variant_l_e;
}

void zone_table_view::set_first(zone_row_view * _first) // установить указатель на первый элемент
{
    first = _first;
}

void zone_table_view::set_last(zone_row_view * _last) // установить указатель на последний элемент
{
    last = _last;
}

// вызывается при нажатии кнопки Удалить строку (сигнал от _index положения КР в списке)
void zone_table_view::p_b_major_delete_click(int _index)
{
    zone_row_view * iter_delete;
    iter_delete = ret_zone_by_index(_index);

    // удаление кнопок Удалить КР и Добавить маневр из групп кнопок ---------------------------------------------------
    b_g_major_delete->removeButton(iter_delete->ret_p_b_delete());
    b_g_add->removeButton(iter_delete->ret_p_b_add());
    // ----------------------------------------------------------------------------------------------------------------

    // переименование кнопок Удалить КР и Добавить маневр, находящихся в списке после удаляемого КР -------------------
    zone_row_view * iter_rename;
    iter_rename = iter_delete->ret_next();

    while(iter_rename != NULL)
    {
        int old_id;
        old_id = b_g_major_delete->id(iter_rename->ret_p_b_delete());
        b_g_major_delete->setId(iter_rename->ret_p_b_delete(), old_id-1);
        b_g_add->setId(iter_rename->ret_p_b_add(), old_id-1);

        iter_rename = iter_rename->ret_next();
    }
    // ----------------------------------------------------------------------------------------------------------------

    // изменение таблицы перед удалением КР
    table_change_before_delete_zone(iter_delete);

    // номер строки в таблице, которую необходимо удалить
    int num_row_delete;
    num_row_delete = ret_row_num_by_zone(iter_delete);

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

    ptr_table->removeRow(num_row_delete);
    row_count--;
    ptr_table->setRowCount(row_count);

    table_p_b_save_enable("");
}

// вызывается при нажатии кнопки Удалить строку (сигнал от _row_num строки таблицы)
void zone_table_view::p_b_minor_delete_click(int _row_num)
{
    // указатель на эталон, маневр которого необходимо удалить
    zone_row_view * iter_zone;
    iter_zone = NULL;

    // указатель на маневр, который необходимо удалить
    zone_point_row_view * iter_delete;
    iter_delete = NULL;

    // признак удаления какой-нибудь строки подтаблицы
    bool b_delete;
    b_delete = true;

    // вернуть указатель на эталон по номеру строки подтаблицы маневра
    iter_zone = ret_zone_by_row_num_maneuver(_row_num);

    // вернуть указатель на маневр по номеру строки подтаблицы маневра
    iter_delete = ret_maneuver_by_row_num_maneuver(_row_num);

    // вернуть признак удаления строки подтаблицы по указателю на маневр
    b_delete = ret_b_delete_row_by_maneuver(iter_delete);

    // удаление маневра из группы кнопок
    b_g_minor_delete->removeButton(iter_delete->ret_p_b_delete());

    // переименование кнопок удалить маневр (-1), находящихся в подтаблице после маневра
    rename_minus_b_g_delete_after_maneuver(iter_zone, iter_delete, b_delete);

    // перемещение формуляра эталона
    if(b_delete == true)
    {
        if(iter_delete == iter_zone->ret_first()) // первый в списке маневров
        {
            ptr_table->setCellWidget(ret_row_num_by_zone(iter_zone)+1, 0 ,  iter_zone->ret_number()->ret_l_e());
            ptr_table->setCellWidget(ret_row_num_by_zone(iter_zone)+1, 1 ,  iter_zone->ret_r()->ret_l_e());
            ptr_table->setCellWidget(ret_row_num_by_zone(iter_zone)+1, 2 ,  iter_zone->ret_g()->ret_l_e());
            ptr_table->setCellWidget(ret_row_num_by_zone(iter_zone)+1, 3 ,  iter_zone->ret_b()->ret_l_e());
            ptr_table->setCellWidget(ret_row_num_by_zone(iter_zone)+1, 4 ,  iter_zone->ret_a()->ret_l_e());
            ptr_table->setCellWidget(ret_row_num_by_zone(iter_zone)+1, 5 ,  iter_zone->ret_color()->ret_l_e());
            ptr_table->setCellWidget(ret_row_num_by_zone(iter_zone)+1, 6 ,  iter_zone->ret_countPoint()->ret_l_e());
            ptr_table->setCellWidget(ret_row_num_by_zone(iter_zone)+1, 7 ,  iter_zone->ret_p_b_add());
            ptr_table->setCellWidget(ret_row_num_by_zone(iter_zone)+1, 12,  iter_zone->ret_p_b_delete());
        }
    }

    // изъятие маневра из списка (без удаления)
    withdrawal_maneuver_from_list(iter_zone, iter_delete);

    // удаление виджетов маневра
    if(b_delete == true)
    {
        row_count--;
        ptr_table->removeRow(_row_num);
    }
    else
    {
        for(int i=3; i<col_count-1; i++)
        {
            ptr_table->removeCellWidget(_row_num, i);
        }
    }

    delete iter_delete;
    iter_delete = NULL;

    iter_zone->ret_countPoint()->set_value(QString("%1").arg(iter_zone->ret_countPoint()->ret_value().toInt()-1));
    iter_zone->ret_countPoint()->l_e_changed(iter_zone->ret_countPoint()->ret_value());
    iter_zone->ret_countPoint()->ret_l_e()->setText(iter_zone->ret_countPoint()->ret_value());

    table_p_b_save_enable("");
}

// вызывается при нажатии на кнопку +
void zone_table_view::p_b_add_click(int _index)
{
    zone_row_view * iter_zone;
    iter_zone = ret_zone_by_index(_index);

    iter_zone->add_new_element();
    set_maneuver_signal_slot_connection_cell_change_p_b_save_enable(iter_zone->ret_last());
    insert_minor_row_in_table(iter_zone->ret_last());
}

// вызывается для проверки допустимости нажатия на кнопку Сохранить
void zone_table_view::table_p_b_save_enable(QString)
{
    bool b_enable;
    b_enable = true;

    zone_row_view * iter_zone;
    iter_zone = first;

    zone_point_row_view * iter_maneuver;

    while(iter_zone != NULL)
    {
        if(iter_zone->ret_number()->ret_b_correct() == false ||
           iter_zone->ret_countPoint()->ret_b_correct() == false ||
           iter_zone->ret_r()->ret_b_correct() == false ||
           iter_zone->ret_g()->ret_b_correct() == false ||
           iter_zone->ret_b()->ret_b_correct() == false ||
           iter_zone->ret_a()->ret_b_correct() == false)
        {
            b_enable = false;
            break;
        }
        iter_zone = iter_zone->ret_next();
    }

    iter_zone = first;
    while(iter_zone != NULL)
    {
        iter_maneuver = iter_zone->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_maneuver->ret_number()->ret_b_correct() == false ||
               iter_maneuver->ret_x()->ret_b_correct() == false ||
               iter_maneuver->ret_y()->ret_b_correct() == false)
            {
                b_enable = false;
                break;
            }
            iter_maneuver = iter_maneuver->ret_next();
        }
        iter_zone = iter_zone->ret_next();
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
