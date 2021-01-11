#ifndef XML_EDITOR
#define XML_EDITOR

#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>

#include "xml_widget.h"
#include "xmlsyntaxhighlighter.h"

class xml_widget;

class xml_editor : public QWidget // редактор xml-/xsd-/xsl-документов
{
    Q_OBJECT
public:
    xml_editor(xml_widget * _ptr_xml_widget);  // конструктор
    ~xml_editor();                             // деструктор

    void update_file(); // обновить файл по измененной таблице

    QPushButton * ret_button_save(); // вернуть кнопку Сохранить

private:
    xml_widget * ptr_xml_widget; // указатель на виджет xml-/xsd-/xsl-документа

    QVBoxLayout main_lo;         // указатель на главный виджет компановки текстового редактора
    QTextEdit text_edit;         // текстовый редактор
    QLabel label_num_row_col;    // надпись с номером строки и столбца, на котором находится курсор редактора
    QPushButton button_save;     // кнопка Сохранить
    QPushButton button_exit;     // кнопка Выход

    QString old_data;            // содержимое xml-/xsd-/xsl-документа

public slots:
    void button_save_clicked();  // вызывается при нажатии на кнопку Сохранить
    void button_exit_clicked();  // вызывается при нажатии на кнопку Выход
    void change_cur_pos();       // вызывается при изменении позиции курсора редактора
};

#endif // XML_EDITOR
