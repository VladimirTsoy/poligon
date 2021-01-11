#include "maneuver_form.h"

// конструктор
maneuver_form::maneuver_form()
{
    // создание главного менеджера компановки
    main_lo = new QVBoxLayout();

    // создание заголовка формы
    QFont title_font;
    title_font.setBold(true);
    title_font.setPointSizeF(24);
    title_label = new QLabel();
    title_label->setText("Маневры эталонов");
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setFont(title_font);

    // создание менеджера компановки формы
    table_lo = new QVBoxLayout();

    main_lo->addWidget(title_label,0);
    main_lo->addLayout(table_lo,100);
    setLayout(main_lo);
}

// деструктор
maneuver_form::~maneuver_form()
{
    delete title_label;
    title_label = NULL;

    delete table_lo;
    table_lo = NULL;

    delete main_lo;
    main_lo = NULL;
}

QVBoxLayout * maneuver_form::ret_main_lo() // вернуть главный менеджер компановки
{
    return main_lo;
}

QLabel * maneuver_form::ret_title_label() // вернуть заголовок формы
{
    return title_label;
}

QVBoxLayout *maneuver_form::ret_table_lo() // вернуть менеджер компановки таблицы
{
    return table_lo;
}

void maneuver_form::set_main_lo(QVBoxLayout * _main_lo) // установить главный менеджер компановки
{
    main_lo = _main_lo;
}

void maneuver_form::set_title_label(QLabel * _title_label) // установить заголовок формы
{
    title_label = _title_label;
}

void maneuver_form::set_table_lo(QVBoxLayout * _table_lo) // установить менеджер компановки таблицы
{
    table_lo = _table_lo;
}
