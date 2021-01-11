#include "xml_xsd_xsl_frame.h"

xml_xsd_xsl_frame::xml_xsd_xsl_frame(QString _full_dir_path_xml, QString _file_xml_name,
                                     QString _full_dir_path_xsd, QString _file_xsd_name,
                                     QString _full_dir_path_xsl, QString _file_xsl_name,
                                     QString _full_dir_path_html,
                                     QHBoxLayout * _xml_xsd_xsl_lo) : QFrame() // конструктор
{
    xml_xsd_xsl_lo = _xml_xsd_xsl_lo;

    main_lo = new QVBoxLayout();
    setLayout(main_lo);

    QString xslt_res;
    xslt_res = _file_xml_name + ".html";

    ptr_xml_widget = new xml_widget(_file_xml_name + ".xml", _full_dir_path_xml);
    ptr_xsd_widget = new xml_widget(_file_xsd_name + ".xsd", _full_dir_path_xsd);
    ptr_xsl_widget = new xml_widget(_file_xsl_name + ".xsl", _full_dir_path_xsl);

    ptr_xml_checker = new xml_checker(ptr_xml_widget, ptr_xsd_widget, ptr_xsl_widget, _full_dir_path_html, xslt_res);

    ptr_xml_widget->set_ptr_xml_checker(ptr_xml_checker);
    ptr_xsd_widget->set_ptr_xml_checker(ptr_xml_checker);
    ptr_xsl_widget->set_ptr_xml_checker(ptr_xml_checker);

    xslt_button = new QPushButton();
    xslt_button->setText("Показать результат XSLT-преобразования");
    connect(xslt_button, SIGNAL(clicked()), this, SLOT(xslt_button_click()));

    main_lo->addWidget(ptr_xml_widget);
    main_lo->addWidget(ptr_xsd_widget);
    main_lo->addWidget(ptr_xsl_widget);
    main_lo->addWidget(xslt_button);
    main_lo->setSpacing(0);

    this->setFrameStyle(QFrame::Box);

    xml_xsd_xsl_lo->addWidget(this);
}

xml_xsd_xsl_frame::~xml_xsd_xsl_frame() // деструктор
{
    delete ptr_xml_widget;
    ptr_xml_widget = NULL;

    delete ptr_xsd_widget;
    ptr_xsd_widget = NULL;

    delete ptr_xsl_widget;
    ptr_xsl_widget = NULL;

    delete xslt_button;
    xslt_button = NULL;

    delete main_lo;
    main_lo = NULL;

    delete ptr_xml_checker;
    ptr_xml_checker = NULL;

    xml_xsd_xsl_lo = NULL;
}

// перезагрузка xml-файла
void xml_xsd_xsl_frame::reload_xml_file()
{
    ptr_xml_checker->check();
    ptr_xml_widget->ret_editor()->update_file();
}

QVBoxLayout * xml_xsd_xsl_frame::ret_main_lo() // вернуть главный менеджер компановки
{
    return main_lo;
}

xml_widget * xml_xsd_xsl_frame::ret_ptr_xml_widget() // вернуть виджет xml-документа
{
    return ptr_xml_widget;
}

xml_widget * xml_xsd_xsl_frame::ret_ptr_xsd_widget() // вернуть виджет xsd-документа
{
    return ptr_xsd_widget;
}

xml_widget * xml_xsd_xsl_frame::ret_ptr_xsl_widget() // вернуть виджет xsl-документа
{
    return ptr_xsl_widget;
}

QPushButton * xml_xsd_xsl_frame::ret_xslt_button() // вернуть кнопку Показать результат XSLT-преобразования
{
    return xslt_button;
}

xml_checker * xml_xsd_xsl_frame::ret_ptr_xml_checker() // вернуть указатель на объект, отвечающий за проверку корректности, валидности и правильности XSLT-преобразования
{
    return ptr_xml_checker;
}

QHBoxLayout * xml_xsd_xsl_frame::ret_xml_xsd_xsl_lo() // вернуть менеджер компановки фрейма xml-, xsd- и xsl-документов
{
    return xml_xsd_xsl_lo;
}

void xml_xsd_xsl_frame::set_main_lo(QVBoxLayout * _main_lo) // установить главный менеджер компановки
{
    main_lo = _main_lo;
}

void xml_xsd_xsl_frame::set_ptr_xml_widget(xml_widget * _ptr_xml_widget) // установить виджет xml-документа
{
    ptr_xml_widget = _ptr_xml_widget;
}

void xml_xsd_xsl_frame::set_ptr_xsd_widget(xml_widget * _ptr_xsd_widget) // установить виджет xsd-документа
{
    ptr_xsd_widget = _ptr_xsd_widget;
}

void xml_xsd_xsl_frame::set_ptr_xsl_widget(xml_widget * _ptr_xsl_widget) // установить виджет xsl-документа
{
    ptr_xsl_widget = _ptr_xsl_widget;
}

void xml_xsd_xsl_frame::set_xslt_button(QPushButton * _xslt_button) // установить кнопку Показать результат XSLT-преобразования
{
    xslt_button = _xslt_button;
}

void xml_xsd_xsl_frame::set_ptr_xml_checker(xml_checker * _ptr_xml_checker) // установить указатель на объект, отвечающий за проверку корректности, валидности и правильности XSLT-преобразования
{
    ptr_xml_checker = _ptr_xml_checker;
}

void xml_xsd_xsl_frame::set_xml_xsd_xsl_lo(QHBoxLayout * _xml_xsd_xsl_lo) // установить менеджер компановки фрейма xml-, xsd- и xsl-документов
{
    xml_xsd_xsl_lo = _xml_xsd_xsl_lo;
}

void xml_xsd_xsl_frame::xslt_button_click() // вызывается при нажатии на кнопку Показать результат XSLT-преобразования
{
    ptr_xml_checker->xslt_transform();

    QString file_url_str;
    QFileInfo file_info(QString("%1/%2").arg(ptr_xml_checker->ret_relative_path_to_res_file()).arg(ptr_xml_checker->ret_res_file_html_name()));
    file_url_str = QString("%1").arg(file_info.absoluteFilePath());
    QDesktopServices::openUrl(QUrl(file_url_str, QUrl::TolerantMode));
}

void xml_xsd_xsl_frame::reload_xml_file_slot() // вызывается при нажатии на кнопку Сохранить таблицу в файл
{
    reload_xml_file();
}
