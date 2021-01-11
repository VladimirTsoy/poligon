#include "char_sens_form.h"

// констуктор
char_sens_form::char_sens_form(QString _xml_full_dir_path, QString _xml_file_name,
                               QString _xsd_full_dir_path, QString _xsd_file_name,
                               QString _xsl_full_dir_path, QString _xsl_file_name,
                               QString _html_full_dir_path) : QWidget()
{
    // установка путей к xml-, xsd- и xsl-файлам ----------------------------------------------------------------------
    xml_full_dir_path = _xml_full_dir_path;
    xml_file_name = _xml_file_name;
    xsd_full_dir_path = _xsd_full_dir_path;
    xsd_file_name = _xsd_file_name;
    xsl_full_dir_path = _xsl_full_dir_path;
    xsl_file_name = _xsl_file_name;
    html_full_dir_path = _html_full_dir_path;
    // ----------------------------------------------------------------------------------------------------------------

    // создание виджетов формы ----------------------------------------------------------------------------------------
    // создание основного менеджера компановки
    main_lo = new QVBoxLayout();

    // создание менеджера компановки виджета xml-/xsd-/xsl-документов
    xml_xsd_xsl_lo = new QHBoxLayout();

    // создание заголовка формы
    QFont title_font;
    title_font.setBold(true);
    title_font.setPointSizeF(24);
    title_label = new QLabel();
    title_label->setText("Типы источников");
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setFont(title_font);

    // создание менеджера компановки выбора вариантов контрольной задачи
    variant_lo = new QHBoxLayout();
    variant_label = new QLabel();
    variant_label->setText("Выбор варианта контрольной задачи:");
    variant_s_l<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10";
    variant_c_b = new QComboBox();
    variant_c_b->addItems(variant_s_l);
    QFont task_font;
    task_font.setItalic(true);
    task_font.setPointSizeF(12);
    variant_l_e = new QLineEdit();
    variant_l_e->setText("");
    variant_l_e->setFont(task_font);
    variant_lo->addWidget(variant_label,0);
    variant_lo->addWidget(variant_c_b,0);
    variant_lo->addWidget(variant_l_e, 100);

    // создание менеджера компановки таблицы и панели инструментов
    work_lo = new QHBoxLayout();
    table_lo = new QVBoxLayout();
    tool_lo = new QVBoxLayout();
    p_b_save = new QPushButton();
    p_b_save->setText("Сохранить таблицу в файл");
    p_b_add_row = new QPushButton();
    p_b_add_row->setText("Добавить новую строку");
    work_lo->addLayout(table_lo);
    work_lo->addLayout(tool_lo);
    tool_lo->addWidget(p_b_save);
    tool_lo->addWidget(p_b_add_row);
    tool_lo->addStretch(100);
    // ----------------------------------------------------------------------------------------------------------------

    // размещение виджетов на главном менеджере компановки ------------------------------------------------------------
    main_lo->addWidget(title_label,0,Qt::AlignCenter);
    main_lo->addLayout(variant_lo,0);
    main_lo->addLayout(xml_xsd_xsl_lo,0);
    main_lo->addLayout(work_lo,100);
    // ----------------------------------------------------------------------------------------------------------------

    setLayout(main_lo);

    ptr_xml_xsd_xsl_frame = NULL;
    ptr_table_data = NULL;
    ptr_table_view = NULL;

    ptr_convertor = new char_sens_convertor();

    connect(variant_l_e, SIGNAL(textChanged(QString)), SLOT(variant_l_e_changed(QString)));
    connect(variant_c_b, SIGNAL(currentIndexChanged(int)), SLOT(variant_c_b_changed(int)));
    connect(p_b_save, SIGNAL(clicked()), SLOT(table_p_b_save_click()));
    connect(p_b_add_row, SIGNAL(clicked()), SLOT(table_p_b_add_row_click()));

    load();
}

// деструктор
char_sens_form::~char_sens_form()
{
    xml_full_dir_path = "";
    xml_file_name = "";
    xsd_full_dir_path = "";
    xsd_file_name = "";
    xsl_full_dir_path = "";
    xsl_file_name = "";

    delete title_label;
    title_label = NULL;

    delete variant_label;
    variant_label = NULL;

    delete variant_c_b;
    variant_c_b = NULL;

    variant_s_l.clear();

    delete variant_l_e;
    variant_l_e = NULL;

    delete variant_lo;
    variant_lo = NULL;

    delete p_b_save;
    p_b_save = NULL;

    delete p_b_add_row;
    p_b_add_row = NULL;

    delete tool_lo;
    tool_lo = NULL;

    delete ptr_xml_xsd_xsl_frame;
    ptr_xml_xsd_xsl_frame = NULL;

    delete table_lo;
    table_lo = NULL;

    delete_ptr_frame(false);

    delete_ptr_table(false);

    delete work_lo;
    work_lo = NULL;

    delete main_lo;
    main_lo = NULL;

    delete ptr_convertor;
    ptr_convertor = NULL;
}

// загрузка
void char_sens_form::load()
{
    delete_ptr_table(true);
    delete_ptr_frame(true);

    new_ptr_table();
    new_ptr_frame();

    connect(ptr_xml_xsd_xsl_frame->ret_ptr_xml_widget()->ret_editor()->ret_button_save(), SIGNAL(clicked()), SLOT(editor_p_b_save_click()));

    variant_l_e->setText("");

    read();
}

// перезагрузка
void char_sens_form::reload()
{
    delete_ptr_table(false);
    delete_ptr_frame(false);

    new_ptr_table();
    new_ptr_frame();

    connect(ptr_xml_xsd_xsl_frame->ret_ptr_xml_widget()->ret_editor()->ret_button_save(), SIGNAL(clicked()), SLOT(editor_p_b_save_click()));

    variant_l_e->setText("");

    read();
}

// чтение
void char_sens_form::read()
{
    ptr_table_data->read_file();

    if(ptr_table_data->ret_b_error() == false)
    {
        from_data_to_view();
        ptr_table_view->insert_list_in_table();
    }
}

// преобразование data->view
void char_sens_form::from_data_to_view()
{
    ptr_table_view->set_comment(ptr_table_data->ret_comment());

    char_sens_row_data * iter_data;
    iter_data = ptr_table_data->ret_first();

    while(iter_data != NULL)
    {
        ptr_table_view->add_new_element();

        char_sens_row_view * iter_view;
        iter_view = ptr_table_view->ret_last();

        iter_view->ret_number()->set_value(ptr_convertor->number_data_view(iter_data->ret_number()->ret_value()));
        iter_view->ret_number()->l_e_changed(iter_view->ret_number()->ret_value());
        iter_view->ret_number()->ret_l_e()->setText(iter_view->ret_number()->ret_value());

        iter_view->ret_hMax()->set_value(ptr_convertor->hMax_data_view(iter_data->ret_hMax()->ret_value()));
        iter_view->ret_hMax()->l_e_changed(iter_view->ret_hMax()->ret_value());
        iter_view->ret_hMax()->ret_l_e()->setText(iter_view->ret_hMax()->ret_value());

        iter_view->ret_hMin()->set_value(ptr_convertor->hMin_data_view(iter_data->ret_hMin()->ret_value()));
        iter_view->ret_hMin()->l_e_changed(iter_view->ret_hMin()->ret_value());
        iter_view->ret_hMin()->ret_l_e()->setText(iter_view->ret_hMin()->ret_value());

        iter_view->ret_maxCountTrc()->set_value(ptr_convertor->maxCountTrc_data_view(iter_data->ret_maxCountTrc()->ret_value()));
        iter_view->ret_maxCountTrc()->l_e_changed(iter_view->ret_maxCountTrc()->ret_value());
        iter_view->ret_maxCountTrc()->ret_l_e()->setText(iter_view->ret_maxCountTrc()->ret_value());

        iter_view->ret_rMax()->set_value(ptr_convertor->rMax_data_view(iter_data->ret_rMax()->ret_value()));
        iter_view->ret_rMax()->l_e_changed(iter_view->ret_rMax()->ret_value());
        iter_view->ret_rMax()->ret_l_e()->setText(iter_view->ret_rMax()->ret_value());

        iter_view->ret_rMin()->set_value(ptr_convertor->rMin_data_view(iter_data->ret_rMin()->ret_value()));
        iter_view->ret_rMin()->l_e_changed(iter_view->ret_rMin()->ret_value());
        iter_view->ret_rMin()->ret_l_e()->setText(iter_view->ret_rMin()->ret_value());

        iter_view->ret_trustXY()->set_value(ptr_convertor->trustXY_data_view(iter_data->ret_trustXY()->ret_value()));
        iter_view->ret_trustXY()->l_e_changed(iter_view->ret_trustXY()->ret_value());
        iter_view->ret_trustXY()->ret_l_e()->setText(iter_view->ret_trustXY()->ret_value());

        iter_view->ret_trustH()->set_value(ptr_convertor->trustH_data_view(iter_data->ret_trustH()->ret_value()));
        iter_view->ret_trustH()->l_e_changed(iter_view->ret_trustH()->ret_value());
        iter_view->ret_trustH()->ret_l_e()->setText(iter_view->ret_trustH()->ret_value());

        iter_data = iter_data->ret_next();
    }
}

// запись
void char_sens_form::write()
{
    from_view_to_data();

    ptr_table_data->create_file_data();
    ptr_table_data->write_file();
}

// преобразование view->data
void char_sens_form::from_view_to_data()
{
    ptr_table_data->set_comment(ptr_table_view->ret_comment());

    char_sens_row_view * iter_view;
    iter_view = ptr_table_view->ret_first();

    while(iter_view != NULL)
    {
        ptr_table_data->add_new_element();

        char_sens_row_data * iter_data;
        iter_data = ptr_table_data->ret_last();

        iter_data->ret_number()->set_value(ptr_convertor->number_view_data(iter_view->ret_number()->ret_value()));

        iter_data->ret_hMax()->set_value(ptr_convertor->hMax_view_data(iter_view->ret_hMax()->ret_value()));
        iter_data->ret_hMin()->set_value(ptr_convertor->hMin_view_data(iter_view->ret_hMin()->ret_value()));
        iter_data->ret_maxCountTrc()->set_value(ptr_convertor->maxCountTrc_view_data(iter_view->ret_maxCountTrc()->ret_value()));
        iter_data->ret_rMax()->set_value(ptr_convertor->rMax_view_data(iter_view->ret_rMax()->ret_value()));
        iter_data->ret_rMin()->set_value(ptr_convertor->rMin_view_data(iter_view->ret_rMin()->ret_value()));
        iter_data->ret_trustXY()->set_value(ptr_convertor->trustXY_view_data(iter_view->ret_trustXY()->ret_value()));
        iter_data->ret_trustH()->set_value(ptr_convertor->trustH_view_data(iter_view->ret_trustH()->ret_value()));

        iter_view = iter_view->ret_next();
    }
}

// выделение памяти под указатели на данные таблицы и представление таблицы
void char_sens_form::new_ptr_table()
{
    new_ptr_table_data();
    new_ptr_table_view();
}

// выделение памяти под указатель на данные таблицы
void char_sens_form::new_ptr_table_data()
{
    ptr_table_data = new char_sens_table_data(xml_full_dir_path + "/" + xml_file_name + ".xml", "TCharSens", "CharSens");
}

// выделение памяти под указатель на представление таблицы
void char_sens_form::new_ptr_table_view()
{
    ptr_table_view = new char_sens_table_view(table_lo, p_b_save, p_b_add_row, variant_l_e);
}

// выделение памяти под указатель на фрейм xml-/xsd-/xsl-документов
void char_sens_form::new_ptr_frame()
{
    ptr_xml_xsd_xsl_frame = new xml_xsd_xsl_frame(xml_full_dir_path, xml_file_name,
                                                  xsd_full_dir_path, xsd_file_name,
                                                  xsl_full_dir_path, xsl_file_name,
                                                  html_full_dir_path,
                                                  xml_xsd_xsl_lo);
}

// освобождение памяти под указатели на данные таблицы и представление таблицы
void char_sens_form::delete_ptr_table(bool _b_check_null)
{
    delete_ptr_table_data(_b_check_null);
    delete_ptr_table_view(_b_check_null);
}

// освобождение памяти под указателем на данные таблицы
void char_sens_form::delete_ptr_table_data(bool _b_check_null)
{
    if(_b_check_null == true)
    {
        if(ptr_table_data != NULL)
        {
            delete ptr_table_data;
            ptr_table_data = NULL;
        }
    }
    else
    {
        delete ptr_table_data;
        ptr_table_data = NULL;
    }
}

// освобождение памяти под указатель на представление таблицы
void char_sens_form::delete_ptr_table_view(bool _b_check_null)
{
    if(_b_check_null == true)
    {
        if(ptr_table_view != NULL)
        {
            delete ptr_table_view;
            ptr_table_view = NULL;
        }
    }
    else
    {
        delete ptr_table_view;
        ptr_table_view = NULL;
    }
}

// освобождение памяти под указатель на фрейм xml-/xsd-/xsl-документов
void char_sens_form::delete_ptr_frame(bool _b_check_null)
{
    if(_b_check_null == true)
    {
        if(ptr_xml_xsd_xsl_frame != NULL)
        {
            delete ptr_xml_xsd_xsl_frame;
            ptr_xml_xsd_xsl_frame = NULL;
        }
    }
    else
    {
        delete ptr_xml_xsd_xsl_frame;
        ptr_xml_xsd_xsl_frame = NULL;
    }
}

QString char_sens_form::ret_xml_full_dir_path() // вернуть полный путь к каталогу с xml-файлами
{
    return xml_full_dir_path;
}

QString char_sens_form::ret_xml_file_name() // вернуть имя xml-файла
{
    return xml_file_name;
}

QString char_sens_form::ret_xsd_full_dir_path() // вернуть полный путь к каталогу с xsd-файлами
{
    return xsd_full_dir_path;
}

QString char_sens_form::ret_xsd_file_name() // вернуть имя xsd-файла
{
    return xsd_file_name;
}

QString char_sens_form::ret_xsl_full_dir_path() // вернуть полный путь к каталогу с xsl-файлами
{
    return xsl_full_dir_path;
}

QString char_sens_form::ret_xsl_file_name() // вернуть имя xsl-файла
{
    return xsl_file_name;
}

QString char_sens_form::ret_html_full_dir_path() // вернуть полный путь к каталогу с html-файлами
{
    return html_full_dir_path;
}

QVBoxLayout * char_sens_form::ret_main_lo() // вернуть главный менеджер компановки
{
    return main_lo;
}

QLabel * char_sens_form::ret_title_label() // вернуть заголовок формы
{
    return title_label;
}

QHBoxLayout * char_sens_form::ret_variant_lo() // вернуть менеджер компановки варианта контрольной задачи
{
    return variant_lo;
}

QLabel * char_sens_form::ret_variant_label()   // вернуть надпись Выбор варианта контрольной задачи
{
    return variant_label;
}

QComboBox * char_sens_form::ret_variant_c_b()  // вернуть выпадающий список с номером варианта контрольной задачи
{
    return variant_c_b;
}

QLineEdit * char_sens_form::ret_variant_l_e() // вернуть редактируемое поле с описанием контрольной задачи
{
    return variant_l_e;
}

QHBoxLayout * char_sens_form::ret_xml_xsd_xsl_lo() // вернуть менеджер компановки виджета xml-/xsd-/xsl-документов
{
    return xml_xsd_xsl_lo;
}

QHBoxLayout * char_sens_form::ret_work_lo() // вернуть менеджер компановки таблицы и панели инструментов
{
    return work_lo;
}

QVBoxLayout * char_sens_form::ret_table_lo() // вернуть менеджер компановки таблицы
{
    return table_lo;
}

QVBoxLayout * char_sens_form::ret_tool_lo() // вернуть менеджер компановки панели инструментов
{
    return tool_lo;
}

QPushButton * char_sens_form::ret_p_b_save() // вернуть кнопку Сохранить
{
    return p_b_save;
}

QPushButton * char_sens_form::ret_p_b_add_row() // вернуть кнопку Добавить строку
{
    return p_b_add_row;
}

xml_xsd_xsl_frame * char_sens_form::ret_ptr_xml_xsd_xsl_frame() // вернуть фрейм xml-/xsd-/xsl-документов
{
    return ptr_xml_xsd_xsl_frame;
}

char_sens_table_data * char_sens_form::ret_ptr_table_data() // вернуть данные таблицы
{
    return ptr_table_data;
}

char_sens_table_view * char_sens_form::ret_ptr_table_view() // вернуть представление таблицы
{
    return ptr_table_view;
}

char_sens_convertor * char_sens_form::ret_ptr_convertor() // вернуть конвертор
{
    return ptr_convertor;
}

void char_sens_form::set_xml_full_dir_path(QString _xml_full_dir_path) // установить полный путь к каталогу с xml-файлами
{
    xml_full_dir_path = _xml_full_dir_path;
}

void char_sens_form::set_xml_file_name(QString _xml_file_name) // установить имя xml-файла
{
    xml_file_name = _xml_file_name;
}

void char_sens_form::set_xsd_full_dir_path(QString _xsd_full_dir_path) // установить полный путь к каталогу с xsd-файлами
{
    xsd_full_dir_path = _xsd_full_dir_path;
}

void char_sens_form::set_xsd_file_name(QString _xsd_file_name) // установить имя xsd-файла
{
    xsd_file_name = _xsd_file_name;
}

void char_sens_form::set_xsl_full_dir_path(QString _xsl_full_dir_path) // установить полный путь к каталогу с xsl-файлами
{
    xsl_full_dir_path = _xsl_full_dir_path;
}

void char_sens_form::set_xsl_file_name(QString _xsl_file_name) // установить имя xsl-файла
{
    xsl_file_name = _xsl_file_name;
}

void char_sens_form::set_html_full_dir_path(QString _html_full_dir_path) // установить полный путь к каталогу с html-файлами
{
    html_full_dir_path = _html_full_dir_path;
}

void char_sens_form::set_main_lo(QVBoxLayout * _main_lo) // установить главный менеджер компановки
{
    main_lo = _main_lo;
}

void char_sens_form::set_title_label(QLabel * _title_label) // установить заголовок формы
{
    title_label = _title_label;
}

void char_sens_form::set_variant_lo(QHBoxLayout * _variant_lo)  // установить менеджер компановки варианта контрольной задачи
{
    variant_lo = _variant_lo;
}

void char_sens_form::set_variant_label(QLabel * _variant_label) // установить надпись Выбор варианта контрольной задачи
{
    variant_label = _variant_label;
}

void char_sens_form::set_variant_c_b(QComboBox * _variant_c_b)  // установить выпадающий список с номером варианта контрольной задачи
{
    variant_c_b = _variant_c_b;
}

void char_sens_form::set_variant_l_e(QLineEdit * _variant_l_e) // установить редактируемое поле с описанием контрольной задачи
{
    variant_l_e = _variant_l_e;
}

void char_sens_form::set_xml_xsd_xsl_lo(QHBoxLayout * _xml_xsd_xsl_lo) // установить менеджер компановки виджета xml-/xsd-/xsl-документов
{
    xml_xsd_xsl_lo = _xml_xsd_xsl_lo;
}

void char_sens_form::set_work_lo(QHBoxLayout * _work_lo) // установить менеджер компановки таблицы и панели инструментов
{
    work_lo = _work_lo;
}

void char_sens_form::set_table_lo(QVBoxLayout * _table_lo) // установить менеджер компановки таблицы
{
    table_lo = _table_lo;
}

void char_sens_form::set_tool_lo(QVBoxLayout * _tool_lo) // установить менеджер компановки панели инструментов
{
    tool_lo = _tool_lo;
}

void char_sens_form::set_p_b_save(QPushButton * _p_b_save) // установить кнопку Сохранить
{
    p_b_save = _p_b_save;
}

void char_sens_form::set_p_b_add_row(QPushButton * _p_b_add_row) // установить кнопку Добавить строку
{
    p_b_add_row = _p_b_add_row;
}

void char_sens_form::set_ptr_xml_xsd_xsl_frame(xml_xsd_xsl_frame * _ptr_xml_xsd_xsl_frame) // установить фрейм xml-/xsd-/xsl-документов
{
    ptr_xml_xsd_xsl_frame = _ptr_xml_xsd_xsl_frame;
}

void char_sens_form::set_ptr_table_data(char_sens_table_data * _ptr_table_data) // установить данные таблицы
{
    ptr_table_data = _ptr_table_data;
}

void char_sens_form::set_ptr_table_view(char_sens_table_view * _ptr_table_view) // установить представление таблицы
{
    ptr_table_view = _ptr_table_view;
}

void char_sens_form::set_ptr_convertor(char_sens_convertor * _ptr_convertor) // установить конвертор
{
    ptr_convertor = _ptr_convertor;
}

// вызывается при изменении редактируемого поля описания контрольной задачи
void char_sens_form::variant_l_e_changed(QString _variant_l_e_text)
{
    ptr_table_view->set_comment(_variant_l_e_text);
}

// вызывается при изменении элемента выпадающего списка номера варианта контрольной задачи
void char_sens_form::variant_c_b_changed(int _variant_num)
{
    xml_file_name = QString("%1").arg(_variant_num+1);
    reload();
}

// вызывается при нажатии на кнопку Сохранить из редактора xml-документов
void char_sens_form::editor_p_b_save_click()
{
    delete_ptr_table(false);

    new_ptr_table();

    read();
}

// вызывается при нажатии на кнопку Сохранить из таблицы
void char_sens_form::table_p_b_save_click()
{
    delete_ptr_frame(false);
    delete_ptr_table_data(false);

    new_ptr_table_data();

    write();

    new_ptr_frame();
    connect(ptr_xml_xsd_xsl_frame->ret_ptr_xml_widget()->ret_editor()->ret_button_save(), SIGNAL(clicked()), SLOT(editor_p_b_save_click()));
}

// вызывается при нажатии на кнопку Добавить новую строку
void char_sens_form::table_p_b_add_row_click()
{
    ptr_table_view->add_new_element();
    ptr_table_view->insert_row_in_table(ptr_table_view->ret_last());
}
