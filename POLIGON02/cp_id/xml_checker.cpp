#include "xml_checker.h"

xml_checker::xml_checker(xml_widget * _ptr_xml_widget,
                         xml_widget * _ptr_xsd_widget,
                         xml_widget * _ptr_xsl_widget,
                         QString _relative_path_to_res_file,
                         QString _res_file_html_name) // конструктор
{
    ptr_xml_widget = _ptr_xml_widget;
    ptr_xsd_widget = _ptr_xsd_widget;
    ptr_xsl_widget = _ptr_xsl_widget;
    xslt_out = "";

    relative_path_to_res_file = _relative_path_to_res_file;
    res_file_html_name = _res_file_html_name;

    check();
}

xml_checker::~xml_checker() // деструктор
{
    ptr_xml_widget = NULL;
    ptr_xsd_widget = NULL;
    ptr_xsl_widget = NULL;
}

xml_widget * xml_checker::ret_ptr_xml_widget() // вернуть указатель на виджет xml-документа
{
    return ptr_xml_widget;
}

xml_widget * xml_checker::ret_ptr_xsd_widget() // вернуть указатель на виджет xsd-документа
{
    return ptr_xsd_widget;
}

xml_widget * xml_checker::ret_ptr_xsl_widget() // вернуть указатель на виджет xsl-документа
{
    return ptr_xsl_widget;
}

QString xml_checker::ret_xslt_out() // вернуть результат XSLT-преобразования
{
    return xslt_out;
}

QString xml_checker::ret_relative_path_to_res_file() // вернуть относительный путь к результирующему файлу
{
    return relative_path_to_res_file;
}

QString xml_checker::ret_res_file_html_name() // вернуть имя файла с результатом XSLT-преобразования
{
    return res_file_html_name;
}

void xml_checker::set_ptr_xml_widget(xml_widget * _ptr_xml_widget) // установить указатель на виджет xml-документа
{
    ptr_xml_widget = _ptr_xml_widget;
}

void xml_checker::set_ptr_xsd_widget(xml_widget * _ptr_xsd_widget) // установить указатель на виджет xsd-документа
{
    ptr_xsd_widget = _ptr_xsd_widget;
}


void xml_checker::set_ptr_xsl_widget(xml_widget * _ptr_xsl_widget) // установить указатель на виджет xsl-документа
{
    ptr_xsl_widget = _ptr_xsl_widget;
}

void xml_checker::set_relative_path_to_res_file(QString _relative_path_to_res_file) // установить относительный путь к результирующему файлу
{
    relative_path_to_res_file = _relative_path_to_res_file;
}

void xml_checker::set_res_file_html_name(QString _res_file_html_name) // установить имя файла с результатом XSLT-преобразования
{
    res_file_html_name = _res_file_html_name;
}

void xml_checker::check() // проверка корректности, валидности и правильности XSLT-преобразования
{
    ptr_xml_widget->check_exist_file();
    ptr_xsd_widget->check_exist_file();
    ptr_xsl_widget->check_exist_file();

    ptr_xml_widget->check_well_formed();
    ptr_xsd_widget->check_well_formed();
    ptr_xsl_widget->check_well_formed();

    ptr_xsd_widget->check_well_formed_xsd();

    ptr_xml_widget->check_valid(ptr_xsd_widget);

    xslt_transform();
}

void xml_checker::xslt_transform() // XSLT-преобразование
{
    if(ptr_xml_widget->ret_check_status() == 0 && ptr_xsl_widget->ret_check_status() == 0) // правильные входные данные для XSLT-преобразования
    {
        QXmlQuery query(QXmlQuery::XSLT20);
        QString xml_file_data;
        QString xsl_file_data;

        if (!ptr_xml_widget->ret_file_xml()->open(QIODevice::ReadOnly | QIODevice::Text)) // не удается открыть файл
        {
            return;
        }
        else
        {
            QTextStream xml_stream_read(ptr_xml_widget->ret_file_xml());
            xml_file_data = xml_stream_read.readAll();
            ptr_xml_widget->ret_file_xml()->close();
        }

        if (!ptr_xsl_widget->ret_file_xml()->open(QIODevice::ReadOnly | QIODevice::Text)) // не удается открыть файл
        {
            return;
        }
        else
        {
            QTextStream xsl_stream_read(ptr_xsl_widget->ret_file_xml());
            xsl_file_data = xsl_stream_read.readAll();
            ptr_xsl_widget->ret_file_xml()->close();
        }

        query.setFocus(xml_file_data);
        query.setQuery(xsl_file_data);
        query.evaluateTo(&xslt_out);
    }

    QFile res_file_html(QString("%1/%2").arg(relative_path_to_res_file).arg(res_file_html_name));
    if (!res_file_html.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    else
    {
        QTextStream out(& res_file_html);
        out<<xslt_out;
        res_file_html.close();
    }
}
