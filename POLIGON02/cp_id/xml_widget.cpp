#include "xml_widget.h"

xml_widget::xml_widget(QString _file_name, QString _dir_path):QWidget() // конструктор
{
    file_name = _file_name;
    full_file_name = _dir_path + "/" + _file_name;
    file_xml.setFileName(full_file_name);
    check_status = 0;

    main_lo = new QHBoxLayout();
    label_name = new QLabel();
    label_name->setText(file_name);
    label_name->setFrameStyle(1);
    label_status = new QLabel();
    label_status->setAlignment(Qt::AlignCenter);
    label_status->setFrameStyle(1);
    edit_button = new QPushButton();
    edit_button->setText("Редактировать");
    main_lo->addWidget(label_name,1);
    main_lo->addWidget(label_status,5);
    main_lo->addWidget(edit_button,1);
    setLayout(main_lo);

    connect(edit_button,SIGNAL(clicked()),this,SLOT(edit_button_clicked()));

    editor = new xml_editor(this);
}

xml_widget::~xml_widget() // деструктор
{
    delete label_name;
    delete label_status;
    delete edit_button;
    delete editor;
    delete main_lo;
}

void xml_widget::check_exist_file() // проверка существования файла
{
    if(file_xml.exists() == false) // файл не существует
    {
        label_status->setText("Файл не найден");
        set_palette_for_status_label("red");
        check_status = -1;
    }
    else
    {
        check_status = 0;
    }
}

void xml_widget::check_well_formed() // проверка корректности xml-/xsd-/xsl-документа
{
    if(check_status == 0)
    {
        QTextStream stream_read(&file_xml);
        QString file_data;
        QXmlStreamReader xml_reader;
        bool errorOccurred;

        errorOccurred = false;

        if (!file_xml.open(QIODevice::ReadOnly | QIODevice::Text)) // не удается открыть файл
        {
            label_status->setText("не удается открыть файл");
            set_palette_for_status_label("red");
            check_status = -1;
            return;
        }

        file_data = stream_read.readAll();

        xml_reader.addData(file_data);

        while(!xml_reader.atEnd())
        {
            xml_reader.readNext();
            if(xml_reader.hasError())
            {
                errorOccurred = true;
                label_status->setText(QString("Cтрока %1 %2").arg(xml_reader.lineNumber()).arg(xml_reader.errorString()));
            }
            else
            {
                label_status->setText("Файл корректен");
            }
        }

        file_xml.close();

        if(errorOccurred == true) //  найдена ошибка
        {
            set_palette_for_status_label("red");
            check_status = -1;
        }
        else
        {
            set_palette_for_status_label("green");
            check_status = 0;
        }
    }
}

void xml_widget::check_well_formed_xsd() // проверка корректности xsd-схемы
{
    if(check_status == 0)
    {
        QByteArray file_data_xsd;
        QXmlSchema xsd_schema;
        message_handler m_h;

        bool errorOccurred;
        errorOccurred = false;

        file_xml.open(QIODevice::ReadOnly | QIODevice::Text);
        file_data_xsd = file_xml.readAll();
        file_xml.close();

        xsd_schema.setMessageHandler(&m_h);

        if(xsd_schema.load(file_data_xsd) == true)
        {

        }
        else
        {
            check_status = -1;
            errorOccurred = true;
        }

        if(errorOccurred == true) // ошибка найдена
        {
            label_status->setText(QString("Строка %1 столбец %2 %3").arg(m_h.line()).arg(m_h.column()).arg(m_h.statusMessage()));
            set_palette_for_status_label("red");
        }
        else // ошибок нет
        {
            label_status->setText("Файл корректен");
            set_palette_for_status_label("green");
        }
    }
}

void xml_widget::check_valid(xml_widget * _xsd_scheme_lo) // проверка валидности xml-документа xsd-схеме, которая находится в объекте класса мененджер компановки _xsd_scheme_lo
{
    if(check_status == 0 && _xsd_scheme_lo->ret_check_status() == 0)
    {
        QByteArray file_data_xml;
        QByteArray file_data_xsd;
        QXmlSchema xsd_schema;
        QXmlSchemaValidator validator;
        message_handler m_h;

        bool errorOccurred;
        errorOccurred = false;

        file_xml.open(QIODevice::ReadOnly | QIODevice::Text);
        file_data_xml = file_xml.readAll();
        file_xml.close();

        _xsd_scheme_lo->ret_file_xml()->open(QIODevice::ReadOnly | QIODevice::Text);
        file_data_xsd = _xsd_scheme_lo->ret_file_xml()->readAll();
        xsd_schema.load(file_data_xsd);
        _xsd_scheme_lo->ret_file_xml()->close();

        validator.setSchema(xsd_schema);
        validator.setMessageHandler(&m_h);

        if(validator.validate(file_data_xml))
        {
        }
        else
        {
            errorOccurred = true;
        }

        if (errorOccurred == true) // ошибка найдена
        {
            label_status->setText(QString("Строка %1 столбец %2 %3").arg(m_h.line()).arg(m_h.column()).arg(m_h.statusMessage()));
            set_palette_for_status_label("red");
            check_status = -1;
        }
        else // ошибок нет
        {
            label_status->setText("Файл валиден");
            set_palette_for_status_label("green");
        }
    }
}

void xml_widget::set_palette_for_status_label(QString col) // покраска надписи со статусом нужным цветом
{
    QPalette pal;
    pal.setColor(QPalette::Window, QColor(col).lighter(150).name());
    label_status->setAutoFillBackground(true);
    label_status->setPalette(pal);
}

QFile * xml_widget::ret_file_xml() // вернуть xml-/xsd-/xsl-файл
{
    return &file_xml;
}

QString xml_widget::ret_file_name() // вернуть имя файла
{
    return file_name;
}

QString xml_widget::ret_full_file_name() // вернуть полное имя файла
{
    return full_file_name;
}

int xml_widget::ret_check_status() // вернуть статус
{
    return check_status;
}

QHBoxLayout * xml_widget::ret_main_lo() // вернуть менеджер компановки приложения
{
    return main_lo;
}

QLabel * xml_widget::ret_label_name() // вернуть надпись с именем файла
{
    return label_name;
}

QLabel * xml_widget::ret_label_status() // вернуть надпись со статусом (существование, корректность, валидность)
{
    return label_status;
}

QPushButton * xml_widget::ret_edit_button() // вернуть кнопку Редактировать
{
    return edit_button;
}

xml_editor * xml_widget::ret_editor() // вернуть указатель на редактор xml-/xsd-/xsl-документов
{
    return editor;
}

xml_checker * xml_widget::ret_ptr_xml_checker() // вернуть указатель на объект, отвечающий за проверку корректности, валидности и правильности XSLT-преобразования
{
    return ptr_xml_checker;
}

void xml_widget::set_file_xml(QString _full_file_name) // установить xml-/xsd-/xsl-файл
{
    file_xml.setFileName(_full_file_name);
}

void xml_widget::set_file_name(QString _file_name) // установить имя файла
{
    file_name = _file_name;
}

void xml_widget::set_full_file_name(QString _full_file_name) // установить полное имя файла
{
    full_file_name = _full_file_name;
}

void xml_widget::set_check_status(int _check_status) // установить статус
{
    check_status = _check_status;
}

void xml_widget::set_main_lo(QHBoxLayout * _main_lo) // установить менеджер компановки приложения
{
    main_lo = _main_lo;
}

void xml_widget::set_label_name(QLabel * _label_name) // установить надпись с именем файла
{
    label_name = _label_name;
}

void xml_widget::set_label_status(QLabel * _label_status) // установить надпись со статусом (существование, корректность, валидность)
{
    label_status = _label_status;
}

void xml_widget::set_edit_button(QPushButton * _edit_button) // установить кнопку Редактировать
{
    edit_button = _edit_button;
}

void xml_widget::set_editor(xml_editor * _editor) // установить указатель на редактор xml-/xsd-/xsl-документов
{
    editor = _editor;
}

void xml_widget::set_ptr_xml_checker(xml_checker * _ptr_xml_checker) // установить указатель на объект, отвечающий за проверку корректности, валидности и правильности XSLT-преобразования
{
    ptr_xml_checker = _ptr_xml_checker;
}

void xml_widget::edit_button_clicked() // вызывается при нажатии на кнопку Редактировать
{
    editor->showMaximized();
}
