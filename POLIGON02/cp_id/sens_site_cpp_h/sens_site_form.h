#ifndef SENS_SITE_FORM
#define SENS_SITE_FORM

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

#include "xml_xsd_xsl_frame.h"
#include "sens_site_table_data.h"
#include "sens_site_table_view.h"
#include "sens_site_convertor.h"

// форма
class sens_site_form : public QWidget
{
    Q_OBJECT
public:
    // констуктор
    sens_site_form(QString _xml_full_dir_path, QString _xml_file_name,
                   QString _xsd_full_dir_path, QString _xsd_file_name,
                   QString _xsl_full_dir_path, QString _xsl_file_name,
                   QString _html_full_dir_path);

    // деструктор
    ~sens_site_form();

    // загрузка
    void load();

    // перезагрузка
    void reload();

    // чтение
    void read();

    // преобразование data->view
    void from_data_to_view();

    // запись
    void write();

    // преобразование view->data
    void from_view_to_data();

    // выделение памяти под указатели на данные таблицы и представление таблицы
    void new_ptr_table();

    // выделение памяти под указатель на данные таблицы
    void new_ptr_table_data();

    // выделение памяти под указатель на представление таблицы
    void new_ptr_table_view();

    // выделение памяти под указатель на фрейм xml-/xsd-/xsl-документов
    void new_ptr_frame();

    // освобождение памяти под указатели на данные таблицы и представление таблицы
    void delete_ptr_table(bool _b_check_null);

    // освобождение памяти под указателем на данные таблицы
    void delete_ptr_table_data(bool _b_check_null);

    // освобождение памяти под указатель на представление таблицы
    void delete_ptr_table_view(bool _b_check_null);

    // освобождение памяти под указатель на фрейм xml-/xsd-/xsl-документов
    void delete_ptr_frame(bool _b_check_null);

    QString ret_xml_full_dir_path();                                            // вернуть полный путь к каталогу с xml-файлами
    QString ret_xml_file_name();                                                // вернуть имя xml-файла
    QString ret_xsd_full_dir_path();                                            // вернуть полный путь к каталогу с xsd-файлами
    QString ret_xsd_file_name();                                                // вернуть имя xsd-файла
    QString ret_xsl_full_dir_path();                                            // вернуть полный путь к каталогу с xsl-файлами
    QString ret_xsl_file_name();                                                // вернуть имя xsl-файла
    QString ret_html_full_dir_path();                                           // вернуть полный путь к каталогу с html-файлами
    QVBoxLayout * ret_main_lo();                                                // вернуть главный менеджер компановки
    QLabel * ret_title_label();                                                 // вернуть заголовок формы
    QHBoxLayout * ret_variant_lo();                                             // вернуть менеджер компановки варианта контрольной задачи
    QLabel * ret_variant_label();                                               // вернуть надпись Выбор варианта контрольной задачи
    QComboBox * ret_variant_c_b();                                              // вернуть выпадающий список с номером варианта контрольной задачи
    QLineEdit * ret_variant_l_e();                                              // вернуть редактируемое поле с описанием контрольной задачи
    QHBoxLayout * ret_xml_xsd_xsl_lo();                                         // вернуть менеджер компановки виджета xml-/xsd-/xsl-документов
    QHBoxLayout *ret_work_lo();                                                 // вернуть менеджер компановки таблицы и панели инструментов
    QVBoxLayout * ret_table_lo();                                               // вернуть менеджер компановки таблицы
    QVBoxLayout * ret_tool_lo();                                                // вернуть менеджер компановки панели инструментов
    QPushButton * ret_p_b_save();                                               // вернуть кнопку Сохранить
    QPushButton * ret_p_b_add_row();                                            // вернуть кнопку Добавить строку
    xml_xsd_xsl_frame * ret_ptr_xml_xsd_xsl_frame();                            // вернуть фрейм xml-/xsd-/xsl-документов
    sens_site_table_data * ret_ptr_table_data();                                // вернуть данные таблицы
    sens_site_table_view * ret_ptr_table_view();                                // вернуть представление таблицы
    sens_site_convertor * ret_ptr_convertor();                                  // вернуть конвертор

    void set_xml_full_dir_path(QString _xml_full_dir_path);                     // установить полный путь к каталогу с xml-файлами
    void set_xml_file_name(QString _xml_file_name);                             // установить имя xml-файла
    void set_xsd_full_dir_path(QString _xsd_full_dir_path);                     // установить полный путь к каталогу с xsd-файлами
    void set_xsd_file_name(QString _xsd_file_name);                             // установить имя xsd-файла
    void set_xsl_full_dir_path(QString _xsl_full_dir_path);                     // установить полный путь к каталогу с xsl-файлами
    void set_xsl_file_name(QString _xsl_file_name);                             // установить имя xsl-файла
    void set_html_full_dir_path(QString _html_full_dir_path);                   // установить полный путь к каталогу с html-файлами
    void set_main_lo(QVBoxLayout * _main_lo);                                   // установить главный менеджер компановки
    void set_title_label(QLabel * _title_label);                                // установить заголовок формы
    void set_xml_xsd_xsl_lo(QHBoxLayout * _xml_xsd_xsl_lo);                     // установить менеджер компановки виджета xml-/xsd-/xsl-документов
    void set_variant_lo(QHBoxLayout * _variant_lo);                             // установить менеджер компановки варианта контрольной задачи
    void set_variant_label(QLabel * _variant_label);                            // установить надпись Выбор варианта контрольной задачи
    void set_variant_c_b(QComboBox * _variant_c_b);                             // установить выпадающий список с номером варианта контрольной задачи
    void set_variant_l_e(QLineEdit * _variant_l_e);                             // установить редактируемое поле с описанием контрольной задачи
    void set_work_lo(QHBoxLayout * _work_lo);                                   // установить менеджер компановки таблицы и панели инструментов
    void set_table_lo(QVBoxLayout * _table_lo);                                 // установить менеджер компановки таблицы
    void set_tool_lo(QVBoxLayout * _tool_lo);                                   // установить менеджер компановки панели инструментов
    void set_p_b_save(QPushButton * _p_b_save);                                 // установить кнопку Сохранить
    void set_p_b_add_row(QPushButton * _p_b_add_row);                           // установить кнопку Добавить строку
    void set_ptr_xml_xsd_xsl_frame(xml_xsd_xsl_frame * _ptr_xml_xsd_xsl_frame); // установить фрейм xml-/xsd-/xsl-документов
    void set_ptr_table_data(sens_site_table_data * _ptr_table_data);            // установить данные таблицы
    void set_ptr_table_view(sens_site_table_view * _ptr_table_view);            // установить представление таблицы
    void set_ptr_convertor(sens_site_convertor * _ptr_convertor);               // установить конвертор

private:
    QString xml_full_dir_path;                 // полный путь к каталогу с xml-файлами
    QString xml_file_name;                     // имя xml-файла
    QString xsd_full_dir_path;                 // полный путь к каталогу с xsd-файлами
    QString xsd_file_name;                     // имя xsd-файла
    QString xsl_full_dir_path;                 // полный путь к каталогу с xsl-файлами
    QString xsl_file_name;                     // имя xsl-файла
    QString html_full_dir_path;                // полный путь к каталогу с html-файлами

    QVBoxLayout * main_lo;                     // главный менеджер компановки

    QLabel * title_label;                      // заголовок формы

    QHBoxLayout * variant_lo;                  // менеджер компановки варианта и описания контрольной задачи
    QLabel * variant_label;                    // надпись Выбор варианта контрольной задачи
    QComboBox * variant_c_b;                   // выпадающий список с номером варианта контрольной задачи
    QStringList variant_s_l;                   // список строк с вариантами выбора в выпадающем списке
    QLineEdit * variant_l_e;                   // редактируемое поле с описанием контрольной задачи

    QHBoxLayout * xml_xsd_xsl_lo;              // менеджер компановки виджета xml-/xsd-/xsl-документов

    QHBoxLayout * work_lo;                     // менеджер компановки таблицы и панели инструментов
    QVBoxLayout * table_lo;                    // менеджер компановки таблицы
    QVBoxLayout * tool_lo;                     // менеджер компановки панели инструментов
    QPushButton * p_b_save;                    // кнопка Сохранить
    QPushButton * p_b_add_row;                 // кнопка Добавить строку

    xml_xsd_xsl_frame * ptr_xml_xsd_xsl_frame; // фрейм xml-/xsd-/xsl-документов
    sens_site_table_data * ptr_table_data;     // данные таблицы
    sens_site_table_view * ptr_table_view;     // представление таблицы
    sens_site_convertor * ptr_convertor;       // конвертор

public slots:
    // вызывается при изменении редактируемого поля описания контрольной задачи
    void variant_l_e_changed(QString _variant_l_e_text);

    // вызывается при изменении элемента выпадающего списка номера варианта контрольной задачи
    void variant_c_b_changed(int _variant_num);

    // вызывается при нажатии на кнопку Сохранить из редактора xml-документов
    void editor_p_b_save_click();

    // вызывается при нажатии на кнопку Сохранить из таблицы
    void table_p_b_save_click();

    // вызывается при нажатии на кнопку Добавить новую строку
    void table_p_b_add_row_click();
};

#endif // SENS_SITE_FORM
