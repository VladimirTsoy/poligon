#include "etalon_table_view.h"

// конструктор
etalon_table_view::etalon_table_view(QVBoxLayout * _table_lo,
                                     QPushButton * _p_b_save,
                                     QPushButton * _p_b_add_row,
                                     QLineEdit * _variant_l_e,
                                     QVBoxLayout * _sub_table_lo)
{
    b_g_delete = new QButtonGroup(NULL);
    connect(b_g_delete, SIGNAL(buttonClicked(int)), SLOT(p_b_delete_click(int)));

    b_g_sub_delete = new QButtonGroup(NULL);
    connect(b_g_sub_delete, SIGNAL(buttonClicked(int)), SLOT(p_b_sub_delete_click(int)));

    b_g_sub_add = new QButtonGroup(NULL);
    connect(b_g_sub_add, SIGNAL(buttonClicked(int)), SLOT(p_b_sub_add_click(int)));

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
        ptr_table->setColumnWidth(i, 119);
    }
    table_s_a->setWidget(ptr_table);
    table_s_a->setWidgetResizable(true);
    table_lo->addWidget(table_s_a);

    sub_table_lo = _sub_table_lo;
    sub_table_s_a = new QScrollArea();

    // установка информации о подтаблице
    set_sub_table_info();

    ptr_sub_table->setRowCount(sub_row_count);
    ptr_sub_table->setColumnCount(sub_col_count);
    ptr_sub_table->setHorizontalHeaderLabels(sub_table_header_s_l);
    ptr_sub_table->setTabKeyNavigation(false);
    for(int i=0; i<sub_col_count; i++)
    {
        ptr_sub_table->setColumnWidth(i, 140);
    }
    sub_table_s_a->setWidget(ptr_sub_table);
    sub_table_s_a->setWidgetResizable(true);
    sub_table_lo->addWidget(sub_table_s_a);
}

// деструктор
etalon_table_view::~etalon_table_view()
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

    delete b_g_sub_delete;
    b_g_sub_delete = NULL;

    delete b_g_sub_add;
    b_g_sub_add = NULL;

    table_header_s_l.clear();

    col_count = 0;
    row_count = 0;

    delete ptr_table;
    ptr_table = NULL;

    delete  table_s_a;
    table_s_a = NULL;

    table_lo = NULL;

    sub_table_header_s_l.clear();

    sub_col_count = 0;
    sub_row_count = 0;

    delete ptr_sub_table;
    ptr_sub_table = NULL;

    delete  sub_table_s_a;
    sub_table_s_a = NULL;

    sub_table_lo = NULL;
}

// установка информации о таблице
void etalon_table_view::set_table_info()
{
    row_count = 0;
    col_count = 14;
    ptr_table = new QTableWidget();
    table_header_s_l << "number"
                     << "ObjClass"
                     << "TO"
                     << "IO"
                     << "OGP"
                     << "tStart"
                     << "tFinish"
                     << "x"
                     << "y"
                     << "h"
                     << "psi"
                     << "v"
                     << "vh"
                     << "Удалить элемент";
}

// установка информации о подтаблице
void etalon_table_view::set_sub_table_info()
{
    sub_row_count = 0;
    sub_col_count = 10;
    ptr_sub_table = new QTableWidget();
    sub_table_header_s_l << "etalon_number"
                         << "maneuver_count"
                         << "add_maneuver"
                         << "number"
                         << "tStart"
                         << "tFinish"
                         << "a"
                         << "vh"
                         << "r"
                         << "Удалить элемент";
}


// установка сигнально-слотового соединения изменения ячеек таблицы и возможностью нажатия на кнопку сохранить
void etalon_table_view::set_etalon_signal_slot_connection_cell_change_p_b_save_enable(etalon_row_view * _etalon)
{
    connect(_etalon->ret_number()->ret_l_e(),          SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
    connect(_etalon->ret_ObjClass()->ret_c_b(),        SIGNAL(currentTextChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_etalon->ret_TO()->ret_c_b(),              SIGNAL(currentTextChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_etalon->ret_IO()->ret_c_b(),              SIGNAL(currentTextChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_etalon->ret_OGP()->ret_c_b(),             SIGNAL(currentTextChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_etalon->ret_tStart()->ret_l_e(),          SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
    connect(_etalon->ret_tFinish()->ret_l_e(),         SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
    connect(_etalon->ret_x()->ret_l_e(),               SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
    connect(_etalon->ret_y()->ret_l_e(),               SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
    connect(_etalon->ret_h()->ret_l_e(),               SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
    connect(_etalon->ret_psi()->ret_l_e(),             SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
    connect(_etalon->ret_v()->ret_l_e(),               SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
    connect(_etalon->ret_vh()->ret_l_e(),              SIGNAL(textChanged(QString)),        SLOT(table_p_b_save_enable(QString)));
}

// установка сигнально-слотового соединения изменения ячеек таблицы и возможностью нажатия на кнопку сохранить
void etalon_table_view::set_maneuver_signal_slot_connection_cell_change_p_b_save_enable(maneuver_row_view * _maneuver)
{
    connect(_maneuver->ret_number()->ret_l_e(),  SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_maneuver->ret_tStart()->ret_l_e(),  SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_maneuver->ret_tFinish()->ret_l_e(), SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_maneuver->ret_a()->ret_l_e(),       SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_maneuver->ret_vh()->ret_l_e(),      SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
    connect(_maneuver->ret_r()->ret_l_e(),       SIGNAL(textChanged(QString)), SLOT(table_p_b_save_enable(QString)));
}

// вернуть индекс эталона по указателю на эталон
int etalon_table_view::ret_index_by_etalon(etalon_row_view * _etalon)
{
    int index;
    index = 0;

    etalon_row_view * iter_etalon;
    iter_etalon = first;

    while(iter_etalon != _etalon)
    {
        index++;
        iter_etalon = iter_etalon->ret_next();
    }

    return index;
}

// вернуть указатель на эталон по индексу эталона
etalon_row_view * etalon_table_view::ret_etalon_by_index(int _index)
{
    int cur_index;
    cur_index = 0;

    etalon_row_view * iter_etalon;
    iter_etalon = first;

    while(cur_index != _index)
    {
        iter_etalon = iter_etalon->ret_next();
        cur_index++;
    }

    return iter_etalon;
}

// вернуть указатель на эталон по указателю на маневр
etalon_row_view * etalon_table_view::ret_etalon_by_maneuver(maneuver_row_view * _maneuver)
{
    etalon_row_view * iter_etalon;
    maneuver_row_view * iter_maneuver;
    iter_etalon = first;

    while(iter_etalon != NULL)
    {
        iter_maneuver = iter_etalon->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_maneuver == _maneuver)
            {
                return iter_etalon;
            }
            iter_maneuver = iter_maneuver->ret_next();
        }
        iter_etalon = iter_etalon->ret_next();
    }

    return NULL;
}

// вернуть указатель на эталон по номеру строки подтаблицы маневра
etalon_row_view * etalon_table_view::ret_etalon_by_sub_row_num_maneuver(int _sub_row_num)
{
    int cur_sub_row_num;
    cur_sub_row_num = 0;

    etalon_row_view * iter_etalon;
    maneuver_row_view * iter_maneuver;

    iter_etalon = first;

    while(iter_etalon != NULL)
    {
        iter_maneuver = iter_etalon->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_etalon->ret_first() != iter_maneuver)
            {
                cur_sub_row_num++;
            }
            if(_sub_row_num == cur_sub_row_num)
            {
                return iter_etalon;
            }
            iter_maneuver = iter_maneuver->ret_next();
        }
        cur_sub_row_num++;
        iter_etalon = iter_etalon->ret_next();
    }

    return NULL;
}

// вернуть указатель на маневр по номеру строки подтаблицы маневра
maneuver_row_view * etalon_table_view::ret_maneuver_by_sub_row_num_maneuver(int _sub_row_num)
{
    int cur_sub_row_num;
    cur_sub_row_num = 0;

    etalon_row_view * iter_etalon;
    maneuver_row_view * iter_maneuver;

    iter_etalon = first;

    while(iter_etalon != NULL)
    {
        iter_maneuver = iter_etalon->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_etalon->ret_first() != iter_maneuver)
            {
                cur_sub_row_num++;
            }
            if(_sub_row_num == cur_sub_row_num)
            {
                return iter_maneuver;
            }
            iter_maneuver = iter_maneuver->ret_next();
        }
        cur_sub_row_num++;
        iter_etalon = iter_etalon->ret_next();
    }

    return NULL;
}

// вернуть номер строки подтаблицы, которую должен занять формуляр эталона
int etalon_table_view::ret_num_major_sub_row_by_etalon(etalon_row_view * _etalon)
{
    int row_num;
    row_num = 0;

    etalon_row_view * iter_etalon;
    maneuver_row_view * iter_maneuver;
    iter_etalon = first;

    while(iter_etalon != _etalon)
    {
        iter_maneuver = iter_etalon->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_maneuver != iter_etalon->ret_first())
            {
                row_num++;
            }
            iter_maneuver = iter_maneuver->ret_next();
        }
        row_num++;
        iter_etalon = iter_etalon->ret_next();
    }

    return row_num;
}

// вернуть номер строки подтаблицы, которую должен занять формуляр маневра
int etalon_table_view::ret_num_minor_sub_row_by_maneuver(maneuver_row_view * _maneuver)
{
    int row_num;
    row_num = 0;

    bool b_break;
    b_break = false;

    etalon_row_view * iter_etalon;
    maneuver_row_view * iter_maneuver;
    iter_etalon = first;

    while(iter_etalon != NULL)
    {
        iter_maneuver = iter_etalon->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_maneuver != iter_etalon->ret_first())
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
        iter_etalon = iter_etalon->ret_next();
    }

    return row_num;
}

// вернуть признак добавления новой строки в подтаблицу по указателю на маневр
int etalon_table_view::ret_b_add_minor_row_by_maneuver(maneuver_row_view * _maneuver)
{
    bool b_add_new_row;
    b_add_new_row = true;

    bool b_break;
    b_break = false;

    etalon_row_view * iter_etalon;
    maneuver_row_view * iter_maneuver;
    iter_etalon = first;

    while(iter_etalon != NULL)
    {
        iter_maneuver = iter_etalon->ret_first();
        while(iter_maneuver != NULL)
        {
            if(iter_maneuver == _maneuver)
            {
                if(iter_etalon->ret_first() == _maneuver)
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
        iter_etalon = iter_etalon->ret_next();
    }

    return b_add_new_row;
}

// вернуть признак удаления строки подтаблицы по указателю на маневр
bool etalon_table_view::ret_b_delete_row_by_maneuver(maneuver_row_view * _maneuver)
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

// добавление нового элемента в список
void etalon_table_view::add_new_element()
{
    if(first == NULL) // список пуст
    {
        last = new etalon_row_view();
        first = last;
    }
    else // в списке имеются элементы
    {
        etalon_row_view * ptr_new_element;
        ptr_new_element = new etalon_row_view();
        last->set_next(ptr_new_element);
        ptr_new_element->set_prev(last);
        last = ptr_new_element;
    }

    set_etalon_signal_slot_connection_cell_change_p_b_save_enable(last);

    table_p_b_save_enable("");
}

// очистка списка
void etalon_table_view::clear_list()
{
    etalon_row_view * iter;
    iter = first;
    etalon_row_view * iter_delete;

    while(iter != NULL)
    {
        iter_delete = iter;
        iter = iter->ret_next();
        delete iter_delete;
    }
}

// вставка списка в таблицу
void etalon_table_view::insert_list_in_table()
{
    variant_l_e->setText(comment);

    etalon_row_view * iter_view;
    iter_view = first;

    while(iter_view != NULL)
    {
        maneuver_row_view * iter_maneuver_view;
        iter_maneuver_view = iter_view->ret_first();

        insert_major_row_in_sub_table(iter_view);

        while(iter_maneuver_view != NULL)
        {
            insert_minor_row_in_sub_table(iter_maneuver_view);

            iter_maneuver_view = iter_maneuver_view->ret_next();
        }

        insert_row_in_table(iter_view);
        iter_view = iter_view->ret_next();
    }
}

// добавление новой строки в таблицу
void etalon_table_view::insert_row_in_table(etalon_row_view * _iter)
{
    row_count++;
    ptr_table->setRowCount(row_count);

    ptr_table->setCellWidget(row_count-1, 0,   _iter->ret_number()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 1,   _iter->ret_ObjClass()->ret_c_b());
    ptr_table->setCellWidget(row_count-1, 2,   _iter->ret_TO()->ret_c_b());
    ptr_table->setCellWidget(row_count-1, 3,   _iter->ret_IO()->ret_c_b());
    ptr_table->setCellWidget(row_count-1, 4,   _iter->ret_OGP()->ret_c_b());
    ptr_table->setCellWidget(row_count-1, 5,   _iter->ret_tStart()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 6,   _iter->ret_tFinish()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 7,   _iter->ret_x()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 8,   _iter->ret_y()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 9,   _iter->ret_h()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 10,  _iter->ret_psi()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 11,  _iter->ret_v()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 12,  _iter->ret_vh()->ret_l_e());
    ptr_table->setCellWidget(row_count-1, 13,  _iter->ret_p_b_delete());

    b_g_delete->addButton(_iter->ret_p_b_delete(), row_count-1);
}

// добавление основной строки в подтаблицу
void etalon_table_view::insert_major_row_in_sub_table(etalon_row_view * _etalon)
{
    int row_num;
    row_num = 0;

    // вернуть номер строки подтаблицы, которую должен занять формуляр эталона
    row_num = ret_num_major_sub_row_by_etalon(_etalon);

    // вставка новой строки в подтаблицу
    sub_row_count++;
    ptr_sub_table->insertRow(row_num);

    // вставка виджетов эталона в подтаблицу
    ptr_sub_table->setCellWidget(row_num, 0, _etalon->ret_etalon_number()->ret_l_e());
    ptr_sub_table->setCellWidget(row_num, 1, _etalon->ret_countManevr()->ret_l_e());
    ptr_sub_table->setCellWidget(row_num, 2, _etalon->ret_p_b_add_maneuver());

    // добавление кнопки Добавить новый маневр в группу кнопок
    b_g_sub_add->addButton(_etalon->ret_p_b_add_maneuver(), ret_index_by_etalon(_etalon));
}

// добавление второстепенной строки в подтаблицу
void etalon_table_view::insert_minor_row_in_sub_table(maneuver_row_view * _maneuver)
{
    int row_num;
    bool b_add_new_row;

    // вернуть номер строки подтаблицы, которую должен занять формуляр маневра
    row_num = ret_num_minor_sub_row_by_maneuver(_maneuver);

    // вернуть признак добавления новой строки в подтаблицу по указателю на маневр
    b_add_new_row = ret_b_add_minor_row_by_maneuver(_maneuver);

    // вставка новой строки в подтаблицу
    if(b_add_new_row == true)
    {
        sub_row_count++;
        ptr_sub_table->insertRow(row_num);
    }

    // вставка виджетов маневра в подтаблицу
    ptr_sub_table->setCellWidget(row_num, 3,  _maneuver->ret_number()->ret_l_e());
    ptr_sub_table->setCellWidget(row_num, 4,  _maneuver->ret_tStart()->ret_l_e());
    ptr_sub_table->setCellWidget(row_num, 5,  _maneuver->ret_tFinish()->ret_l_e());
    ptr_sub_table->setCellWidget(row_num, 6,  _maneuver->ret_a()->ret_l_e());
    ptr_sub_table->setCellWidget(row_num, 7,  _maneuver->ret_vh()->ret_l_e());
    ptr_sub_table->setCellWidget(row_num, 8,  _maneuver->ret_r()->ret_l_e());
    ptr_sub_table->setCellWidget(row_num, 9,  _maneuver->ret_p_b_delete());

    // добавление кнопки Удалить маневр в группу кнопок
    b_g_sub_delete->addButton(_maneuver->ret_p_b_delete(), row_num);

    // вернуть указатель на эталон по указателю на маневр
    etalon_row_view * iter_etalon;
    iter_etalon = ret_etalon_by_maneuver(_maneuver);

    // переименование кнопок удалить маневр (+1), находящихся в таблице после маневра
    rename_plus_p_b_delete_after_maneuver(iter_etalon, _maneuver);

    //////////////////////////////////////////////////////////////////////////////////////////////////
    if(b_add_new_row == true)
    {
        int major_row_num;
        major_row_num = ret_num_major_sub_row_by_etalon(iter_etalon);
        ptr_sub_table->setSpan(major_row_num, 0, ptr_sub_table->rowSpan(major_row_num, 0)+1, 1);
        ptr_sub_table->setSpan(major_row_num, 1, ptr_sub_table->rowSpan(major_row_num, 1)+1, 1);
        ptr_sub_table->setSpan(major_row_num, 2, ptr_sub_table->rowSpan(major_row_num, 2)+1, 1);

        QString help_str;
        help_str = ptr_sub_table->horizontalHeaderItem(0)->text();
        ptr_sub_table->horizontalHeaderItem(0)->setText("");
        ptr_sub_table->horizontalHeaderItem(0)->setText(help_str);
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
}

// переименование кнопок удалить маневр (-1), находящихся в подтаблице после маневра
void etalon_table_view::rename_minus_b_g_delete_after_maneuver(etalon_row_view * _etalon,
                                                               maneuver_row_view * _maneuver,
                                                               bool _b_delete)
{
    if(_b_delete == true)
    {
        // переименование кнопок маневров, идущих после _maneuver
        maneuver_row_view * iter_maneuver_rename;
        iter_maneuver_rename = _maneuver->ret_next();

        while(iter_maneuver_rename != NULL)
        {
            int old_id;
            old_id = b_g_sub_delete->id(iter_maneuver_rename->ret_p_b_delete());
            b_g_sub_delete->setId(iter_maneuver_rename->ret_p_b_delete(), old_id-1);
            iter_maneuver_rename = iter_maneuver_rename->ret_next();
        }

        // переименование кнопок маневров, идущих после _etalon
        etalon_row_view * iter_etalon_rename;
        iter_etalon_rename = _etalon->ret_next();

        while(iter_etalon_rename != NULL)
        {
            iter_maneuver_rename = iter_etalon_rename->ret_first();

            while(iter_maneuver_rename != NULL)
            {
                int old_id;
                old_id = b_g_sub_delete->id(iter_maneuver_rename->ret_p_b_delete());
                b_g_sub_delete->setId(iter_maneuver_rename->ret_p_b_delete(), old_id-1);
                iter_maneuver_rename = iter_maneuver_rename->ret_next();
            }

            iter_etalon_rename = iter_etalon_rename->ret_next();
        }
    }
}

// переименование кнопок удалить маневр (+1), находящихся в подтаблице после маневра
void etalon_table_view::rename_plus_p_b_delete_after_maneuver(etalon_row_view * _etalon, maneuver_row_view * _maneuver)
{
    if(_etalon->ret_first() != _maneuver)
    {
        etalon_row_view * iter_etalon_rename;
        maneuver_row_view * iter_maneuver_rename;
        iter_etalon_rename = _etalon->ret_next();

        while(iter_etalon_rename != NULL)
        {
            iter_maneuver_rename = iter_etalon_rename->ret_first();
            while(iter_maneuver_rename != NULL)
            {
                int old_id;
                old_id = b_g_sub_delete->id(iter_maneuver_rename->ret_p_b_delete());
                b_g_sub_delete->setId(iter_maneuver_rename->ret_p_b_delete(), old_id+1);
                iter_maneuver_rename = iter_maneuver_rename->ret_next();
            }
            iter_etalon_rename = iter_etalon_rename->ret_next();
        }
    }
}

// изъятие маневра из списка (без удаления)
void etalon_table_view::withdrawal_maneuver_from_list(etalon_row_view * _etalon,
                                                      maneuver_row_view * _maneuver)
{
    if(_maneuver == _etalon->ret_first())
    {
        if(_maneuver->ret_next() == NULL)
        {
            _etalon->set_first(NULL);
            _etalon->set_last(NULL);
        }
        else
        {
            _etalon->set_first(_maneuver->ret_next());
            _etalon->ret_first()->set_prev(NULL);
        }
    }
    else if(_maneuver == _etalon->ret_last())
    {
        _etalon->set_last(_maneuver->ret_prev());
        _etalon->ret_last()->set_next(NULL);
    }
    else
    {
        _maneuver->ret_next()->set_prev(_maneuver->ret_prev());
        _maneuver->ret_prev()->set_next(_maneuver->ret_next());
    }
}

// очистка подтаблицы после удаления эталона
void etalon_table_view::sub_table_clear_after_delete_etalon(etalon_row_view * _etalon_delete)
{
    // удаление маневров, принадлежащих эталону -----------------------------------------------------------------------
    maneuver_row_view * iter_maneuver;
    iter_maneuver = _etalon_delete->ret_first();
    while(iter_maneuver != NULL)
    {
        maneuver_row_view * maneuver_delete;
        maneuver_delete = iter_maneuver;
        iter_maneuver = iter_maneuver->ret_next();
        int sub_minor_row_delete;

        // вернуть номер строки подтаблицы, которую занимает формуляр маневра
        sub_minor_row_delete = ret_num_minor_sub_row_by_maneuver(maneuver_delete);

        // вызывается при нажатии кнопки Удалить строку (сигнал от sub_minor_row_delete строки подтаблицы)
        p_b_sub_delete_click(sub_minor_row_delete);
    }
    // ----------------------------------------------------------------------------------------------------------------

    // переименование кнопок Удалить маневр, идущих после _etalon_delete ----------------------------------------------
    int sub_major_row_delete;

    // вернуть номер строки подтаблицы, которую занимает формуляр эталона
    sub_major_row_delete = ret_num_major_sub_row_by_etalon(_etalon_delete);

    etalon_row_view * iter_etalon_rename;
    iter_etalon_rename = _etalon_delete->ret_next();

    maneuver_row_view * iter_maneuver_rename;

    while(iter_etalon_rename != NULL)
    {
        iter_maneuver_rename = iter_etalon_rename->ret_first();

        while(iter_maneuver_rename != NULL)
        {
            int old_id;
            old_id = b_g_sub_delete->id(iter_maneuver_rename->ret_p_b_delete());
            b_g_sub_delete->setId(iter_maneuver_rename->ret_p_b_delete(), old_id-1);
            iter_maneuver_rename = iter_maneuver_rename->ret_next();
        }

        iter_etalon_rename = iter_etalon_rename->ret_next();
    }
    // ----------------------------------------------------------------------------------------------------------------

    // переименование кнопок Добавить маневр, идущих после _etalon_delete ---------------------------------------------
    iter_etalon_rename = _etalon_delete->ret_next();

    while(iter_etalon_rename != NULL)
    {
        int old_id;
        old_id = b_g_sub_add->id(iter_etalon_rename->ret_p_b_add_maneuver());
        b_g_sub_add->setId(iter_etalon_rename->ret_p_b_add_maneuver(), old_id-1);

        iter_etalon_rename = iter_etalon_rename->ret_next();
    }
    // ----------------------------------------------------------------------------------------------------------------

    // удаление основной строки подтаблицы ----------------------------------------------------------------------------
    sub_row_count--;
    ptr_sub_table->removeRow(sub_major_row_delete);
    // ----------------------------------------------------------------------------------------------------------------
}

QVBoxLayout * etalon_table_view::ret_table_lo() // вернуть указатель на менеджер компановки таблицы
{
    return table_lo;
}

QScrollArea * etalon_table_view::ret_table_s_a() // вернуть область прокрутки с таблицей
{
    return table_s_a;
}

int etalon_table_view::ret_row_count() // вернуть число строк таблицы
{
    return row_count;
}

int etalon_table_view::ret_col_count() // вернуть число столбцов таблицы
{
    return col_count;
}

QTableWidget * etalon_table_view::ret_ptr_table() // вернуть таблицу
{
    return ptr_table;
}

QStringList etalon_table_view::ret_table_header_s_l() // вернуть список строк с названиями столбцов таблицы
{
    return table_header_s_l;
}

QVBoxLayout * etalon_table_view::ret_sub_table_lo() // вернуть указатель на менеджер компановки подтаблицы
{
    return sub_table_lo;
}

QScrollArea * etalon_table_view::ret_sub_table_s_a() // вернуть область прокрутки с подтаблицей
{
    return sub_table_s_a;
}

int etalon_table_view::ret_sub_row_count() // вернуть число строк подтаблицы
{
    return sub_row_count;
}

int etalon_table_view::ret_sub_col_count() // вернуть число столбцов подтаблицы
{
    return sub_row_count;
}

QTableWidget * etalon_table_view::ret_ptr_sub_table() // вернуть подтаблицу
{
    return ptr_sub_table;
}

QStringList etalon_table_view::ret_sub_table_header_s_l() // вернуть список строк с названиями столбцов подтаблицы
{
    return sub_table_header_s_l;
}

QButtonGroup * etalon_table_view::ret_b_g_delete() // вернуть группу кнопок удаления строки таблицы
{
    return b_g_delete;
}

QButtonGroup * etalon_table_view::ret_b_g_sub_delete() // вернуть группу кнопок удаления строки подтаблицы
{
    return b_g_sub_delete;
}

QButtonGroup * etalon_table_view::ret_b_g_sub_add() // вернуть группу кнопок добавления строки подтаблицы
{
    return b_g_sub_add;
}

QPushButton * etalon_table_view::ret_p_b_save() // вернуть указатель на кнопку Cохранить таблицу
{
    return p_b_save;
}

QPushButton * etalon_table_view::ret_p_b_add_row() // вернуть указатель на кнопку Добавить новую строку
{
    return p_b_add_row;
}

QString etalon_table_view::ret_comment() // вернуть комментарий
{
    return comment;
}

QLineEdit * etalon_table_view::ret_variant_l_e() // вернуть указатель на редактируемое поле с описанием контрольной задачи
{
    return variant_l_e;
}

etalon_row_view * etalon_table_view::ret_first() // вернуть указатель на первый элемент
{
    return first;
}

etalon_row_view * etalon_table_view::ret_last() // вернуть указатель на последний элемент
{
    return last;
}

void etalon_table_view::set_table_lo(QVBoxLayout * _table_lo) // установить указатель на менеджер компановки таблицы
{
    table_lo = _table_lo;
}

void etalon_table_view::set_table_s_a(QScrollArea * _table_s_a) // установить область прокрутки с таблицей
{
    table_s_a = _table_s_a;
}

void etalon_table_view::set_row_count(int _row_count) // установить число строк таблицы
{
    row_count = _row_count;
}

void etalon_table_view::set_col_count(int _col_count) // установить число столбцов таблицы
{
    col_count = _col_count;
}

void etalon_table_view::set_ptr_table(QTableWidget * _ptr_table) // установить таблицу
{
    ptr_table = _ptr_table;
}

void etalon_table_view::set_table_header_s_l(QStringList _table_header_s_l) // установить список строк с названиями столбцов таблицы
{
    table_header_s_l = _table_header_s_l;
}

void etalon_table_view::set_sub_table_lo(QVBoxLayout * _sub_table_lo) // установить указатель на менеджер компановки подтаблицы
{
    sub_table_lo = _sub_table_lo;
}

void etalon_table_view::set_sub_table_s_a(QScrollArea * _sub_table_s_a) // установить область прокрутки с подтаблицей
{
    sub_table_s_a = _sub_table_s_a;
}

void etalon_table_view::set_sub_row_count(int _sub_row_count) // установить число строк подтаблицы
{
    sub_row_count = _sub_row_count;
}

void etalon_table_view::set_sub_col_count(int _sub_col_count) // установить число столбцов подтаблицы
{
    sub_col_count = _sub_col_count;
}

void etalon_table_view::set_ptr_sub_table(QTableWidget * _ptr_sub_table) // установить подтаблицу
{
    ptr_sub_table = _ptr_sub_table;
}

void etalon_table_view::set_sub_table_header_s_l(QStringList _sub_table_header_s_l) // установить список строк с названиями столбцов подтаблицы
{
    sub_table_header_s_l = _sub_table_header_s_l;
}

void etalon_table_view::set_b_g_delete(QButtonGroup * _b_g_delete) // установить группу кнопок удаления строки таблицы
{
    b_g_delete = _b_g_delete;
}

void etalon_table_view::set_b_g_sub_delete(QButtonGroup * _b_g_sub_delete) // установить группу кнопок удаления строки подтаблицы
{
    b_g_sub_delete = _b_g_sub_delete;
}

void etalon_table_view::set_b_g_sub_add(QButtonGroup * _b_g_sub_add) // установить группу кнопок добавления строки подтаблицы
{
    b_g_sub_add = _b_g_sub_add;
}

void etalon_table_view::set_p_b_save(QPushButton * _p_b_save) // установить указатель на кнопку Cохранить таблицу
{
    p_b_save = _p_b_save;
}

void etalon_table_view::set_p_b_add_row(QPushButton * _p_b_add_row) // установить указатель на кнопку Добавить новую строку
{
    p_b_add_row = _p_b_add_row;
}

void etalon_table_view::set_comment(QString _comment) // установить комментарий
{
    comment = _comment;
}

void etalon_table_view::set_variant_l_e(QLineEdit * _variant_l_e) // установить указатель на редактируемое поле с описанием контрольной задачи
{
    variant_l_e = _variant_l_e;
}

void etalon_table_view::set_first(etalon_row_view * _first) // установить указатель на первый элемент
{
    first = _first;
}

void etalon_table_view::set_last(etalon_row_view * _last) // установить указатель на последний элемент
{
    last = _last;
}

// вызывается при нажатии кнопки Удалить строку (сигнал от _row_num строки таблицы)
void etalon_table_view::p_b_delete_click(int _row_num)
{
    etalon_row_view * iter_delete;
    iter_delete = first;

    for(int i=0; i<_row_num; i++)
    {
        iter_delete = iter_delete->ret_next();
    }

    b_g_delete->removeButton(iter_delete->ret_p_b_delete());

    etalon_row_view * iter_rename;
    iter_rename = iter_delete->ret_next();

    while(iter_rename != NULL)
    {
        int old_id;
        old_id = b_g_delete->id(iter_rename->ret_p_b_delete());
        b_g_delete->setId(iter_rename->ret_p_b_delete(), old_id-1);

        iter_rename = iter_rename->ret_next();
    }

    // очистка подтаблицы после удаления эталона
    sub_table_clear_after_delete_etalon(iter_delete);

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

// вызывается при нажатии кнопки Удалить строку (сигнал от _row_num строки подтаблицы)
void etalon_table_view::p_b_sub_delete_click(int _row_num)
{
    // указатель на эталон, маневр которого необходимо удалить
    etalon_row_view * iter_etalon;
    iter_etalon = NULL;

    // указатель на маневр, который необходимо удалить
    maneuver_row_view * iter_delete;
    iter_delete = NULL;

    // признак удаления какой-нибудь строки подтаблицы
    bool b_delete;
    b_delete = true;

    // вернуть указатель на эталон по номеру строки подтаблицы маневра
    iter_etalon = ret_etalon_by_sub_row_num_maneuver(_row_num);

    // вернуть указатель на маневр по номеру строки подтаблицы маневра
    iter_delete = ret_maneuver_by_sub_row_num_maneuver(_row_num);

    // вернуть признак удаления строки подтаблицы по указателю на маневр
    b_delete = ret_b_delete_row_by_maneuver(iter_delete);

    // удаление маневра из группы кнопок
    b_g_sub_delete->removeButton(iter_delete->ret_p_b_delete());

    // переименование кнопок удалить маневр (-1), находящихся в подтаблице после маневра
    rename_minus_b_g_delete_after_maneuver(iter_etalon, iter_delete, b_delete);

    // перемещение формуляра эталона
    if(b_delete == true)
    {
        if(iter_delete == iter_etalon->ret_first()) // первый в списке маневров
        {
            ptr_sub_table->setCellWidget(ret_num_major_sub_row_by_etalon(iter_etalon)+1, 0,  iter_etalon->ret_etalon_number()->ret_l_e());
            ptr_sub_table->setCellWidget(ret_num_major_sub_row_by_etalon(iter_etalon)+1, 1,  iter_etalon->ret_countManevr()->ret_l_e());
            ptr_sub_table->setCellWidget(ret_num_major_sub_row_by_etalon(iter_etalon)+1, 2,  iter_etalon->ret_p_b_add_maneuver());
        }
    }

    // изъятие маневра из списка (без удаления)
    withdrawal_maneuver_from_list(iter_etalon, iter_delete);

    // удаление виджетов маневра
    if(b_delete == true)
    {
        sub_row_count--;
        ptr_sub_table->removeRow(_row_num);
    }
    else
    {
        for(int i=3; i<sub_col_count; i++)
        {
            ptr_sub_table->removeCellWidget(_row_num, i);
        }
    }

    delete iter_delete;
    iter_delete = NULL;

    iter_etalon->ret_countManevr()->set_value(QString("%1").arg(iter_etalon->ret_countManevr()->ret_value().toInt()-1));
    iter_etalon->ret_countManevr()->l_e_changed(iter_etalon->ret_countManevr()->ret_value());
    iter_etalon->ret_countManevr()->ret_l_e()->setText(iter_etalon->ret_countManevr()->ret_value());

    table_p_b_save_enable("");
}

// вызывается при нажатии кнопки Добавить маневр (сигнал от _index индекса эталона в списке)
void etalon_table_view::p_b_sub_add_click(int _index)
{
    etalon_row_view * etalon;

    // вернуть указатель на эталон по индексу эталона
    etalon = ret_etalon_by_index(_index);

    // добавление маневра в список
    etalon->add_new_element();

    // установка сигнально-слотового соединения изменения ячеек таблицы и возможностью нажатия на кнопку сохранить
    set_maneuver_signal_slot_connection_cell_change_p_b_save_enable(etalon->ret_last());

    // добавление второстепенной строки в подтаблицу
    insert_minor_row_in_sub_table(etalon->ret_last());

    table_p_b_save_enable("");
}

// вызывается для проверки допустимости нажатия на кнопку Сохранить
void etalon_table_view::table_p_b_save_enable(QString)
{
    bool b_enable;
    b_enable = true;

    etalon_row_view * iter_etalon;
    iter_etalon = first;

    maneuver_row_view * iter_maneuver;

    while(iter_etalon != NULL)
    {
        if(iter_etalon->ret_number()->ret_b_correct()          == false ||
           iter_etalon->ret_ObjClass()->ret_b_correct()        == false ||
           iter_etalon->ret_TO()->ret_b_correct()              == false ||
           iter_etalon->ret_IO()->ret_b_correct()              == false ||
           iter_etalon->ret_OGP()->ret_b_correct()             == false ||
           iter_etalon->ret_tStart()->ret_b_correct()          == false ||
           iter_etalon->ret_tFinish()->ret_b_correct()         == false ||
           iter_etalon->ret_x()->ret_b_correct()               == false ||
           iter_etalon->ret_y()->ret_b_correct()               == false ||
           iter_etalon->ret_h()->ret_b_correct()               == false ||
           iter_etalon->ret_psi()->ret_b_correct()             == false ||
           iter_etalon->ret_v()->ret_b_correct()               == false ||
           iter_etalon->ret_vh()->ret_b_correct()              == false)
        {
            b_enable = false;
            break;
        }

        iter_maneuver = iter_etalon->ret_first();

        while(iter_maneuver != NULL)
        {
            if(iter_maneuver->ret_number()->ret_b_correct()  == false ||
               iter_maneuver->ret_tStart()->ret_b_correct()  == false ||
               iter_maneuver->ret_tFinish()->ret_b_correct() == false ||
               iter_maneuver->ret_a()->ret_b_correct()       == false ||
               iter_maneuver->ret_vh()->ret_b_correct()      == false ||
               iter_maneuver->ret_r()->ret_b_correct()       == false)
            {
                b_enable = false;
                break;
            }
            iter_maneuver = iter_maneuver->ret_next();
        }

        iter_etalon = iter_etalon->ret_next();
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

bool etalon_table_view::check_fill(cell_view_l_e * _fill_1, cell_view_l_e * _fill_2)
{
    bool b_enable;

    b_enable = true;

    if(_fill_1->ret_value() != "" && _fill_2->ret_value() == "")
    {
        _fill_1->fill_color(false);
        _fill_2->fill_color(false);
        b_enable = false;
    }

    if(_fill_1->ret_value() == "" && _fill_2->ret_value() != "")
    {
        _fill_1->fill_color(false);
        _fill_2->fill_color(false);
        b_enable = false;
    }

    /*
    if(_fill_1->ret_value() == "" && _fill_2->ret_value() == "")
    {
        _fill_1->fill_color(true);
        _fill_2->fill_color(true);
    }

    if(_fill_1->ret_value() != "" && _fill_2->ret_value() != "")
    {
        if(_fill_1->ret_b_correct() == true)
        {
            _fill_1->fill_color(true);
        }
        if(_fill_2->ret_b_correct() == true)
        {
            _fill_2->fill_color(true);
        }
    }
    */

    return b_enable;
}
