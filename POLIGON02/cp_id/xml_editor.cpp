#include "xml_editor.h"

xml_editor::xml_editor(xml_widget * _ptr_xml_widget) // конструктор
{
    ptr_xml_widget = _ptr_xml_widget;

    QByteArray file_data_xml;

    ptr_xml_widget->ret_file_xml()->open(QIODevice::ReadOnly | QIODevice::Text);
    file_data_xml = ptr_xml_widget->ret_file_xml()->readAll();
    ptr_xml_widget->ret_file_xml()->close();

    old_data = file_data_xml;

    setWindowTitle(QString("Редактирование документа %1").arg(ptr_xml_widget->ret_file_name()));

    setLayout(&main_lo);
    text_edit.setText(file_data_xml);
    text_edit.moveCursor(QTextCursor::Start);

    QFont font;
    font.setPointSize(13);
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);

    const int tabStop = 4;
    QFontMetrics metrics(font);

    text_edit.setFont(font);
    text_edit.setTabStopWidth(tabStop * metrics.width(' '));

    XmlSyntaxHighlighter * highlighter;
//    highlighter = new XmlSyntaxHighlighter(text_edit.document());
    highlighter = new XmlSyntaxHighlighter();
    highlighter->setDocument(text_edit.document());

    main_lo.addWidget(&text_edit);
    button_save.setText("Сохранить");
    main_lo.addWidget(&label_num_row_col);
    label_num_row_col.setText(QString("Номер строки: %1 Номер столбца: %2").arg(text_edit.textCursor().blockNumber()+1).arg(text_edit.textCursor().columnNumber()+1));
    main_lo.addWidget(&button_save);
    button_exit.setText("Выход");
    main_lo.addWidget(&button_exit);

    connect(&button_save,SIGNAL(clicked()),this,SLOT(button_save_clicked()));
    connect(&button_exit,SIGNAL(clicked()),this,SLOT(button_exit_clicked()));
    connect(&text_edit,SIGNAL(cursorPositionChanged()),this,SLOT(change_cur_pos()));
}

xml_editor::~xml_editor() // деструктор
{

}

QPushButton * xml_editor::ret_button_save() // вернуть кнопку Сохранить
{
    return &button_save;
}

void xml_editor::update_file() // обновить файл по измененной таблице
{
    QByteArray file_data_xml;
    ptr_xml_widget->ret_file_xml()->open(QIODevice::ReadOnly | QIODevice::Text);
    file_data_xml = ptr_xml_widget->ret_file_xml()->readAll();
    ptr_xml_widget->ret_file_xml()->close();
    old_data = file_data_xml;

    text_edit.setText(file_data_xml);
    text_edit.moveCursor(QTextCursor::Start);
}

void xml_editor::button_save_clicked() // вызывается при нажатии на кнопку Сохранить
{
    old_data = text_edit.toPlainText();

    ptr_xml_widget->ret_file_xml()->open(QIODevice::WriteOnly | QIODevice::Text);
    ptr_xml_widget->ret_file_xml()->write(text_edit.toPlainText().toLocal8Bit());
    ptr_xml_widget->ret_file_xml()->close();

    ptr_xml_widget->ret_ptr_xml_checker()->check();
    update();
}

void xml_editor::button_exit_clicked() // вызывается при нажатии на кнопку Выход
{
    text_edit.setText(old_data);
    this->hide();

    ptr_xml_widget->ret_ptr_xml_checker()->check();
    update();
}

void xml_editor::change_cur_pos() // вызывается при изменении позиции курсора редактора
{
    label_num_row_col.setText(QString("Номер строки: %1 Номер столбца: %2").arg(text_edit.textCursor().blockNumber()+1).arg(text_edit.textCursor().columnNumber()+1));
}
