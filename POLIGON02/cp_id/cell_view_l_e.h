#ifndef CELL_VIEW_L_E_H
#define CELL_VIEW_L_E_H

#include <stddef.h>
#include <QObject>
#include <QString>
#include <QLineEdit>
#include <QIntValidator>
#include <QDoubleValidator>

// отображение ячейки таблицы в виде редактируемого поля
class cell_view_l_e : public QObject
{
    Q_OBJECT
public:
    // конструктор
    cell_view_l_e(int _data_type,
                  int _validator_type,
                  bool _b_require,
                  QString _col_valid,
                  QString _col_error);

    // деструктор
    ~cell_view_l_e();

    // установка параметров валидатора --------------------------------------------------------------------------------
    void set_validator_par();
    void set_validator_par(int _validator_min, int _validator_max);
    void set_validator_par(double _validator_min, double _validator_max, int _decimals);
    // ----------------------------------------------------------------------------------------------------------------

    // покраска редактируемого поля
    void fill_color(bool _b_correct);

    int ret_data_type();                          // вернуть тип данных
    int ret_validator_type();                     // вернуть тип валидатора
    QString ret_value();                          // вернуть значение
    bool ret_b_correct();                         // вернуть признак корректности
    bool ret_b_require();                         // вернуть признак обязательности
    QString ret_col_valid();                      // вернуть цвет корректного поля
    QString ret_col_error();                      // вернуть цвет ошибочного поля
    QIntValidator * ret_i_v();                    // вернуть контрольное устройство проверки целых чисел
    QDoubleValidator * ret_d_v();                 // вернуть контрольное устройство проверки нецелых чисел
    QLineEdit * ret_l_e();                        // вернуть редактируемое поле

    void set_data_type(int _data_type);           // установить тип данных
    void set_validator_type(int _validator_type); // установить тип валидатора
    void set_value(QString _value);               // установить значение
    void set_b_correct(bool _b_correct);          // установить признак корректности
    void set_b_require(bool _b_require);          // установить признак обязательности
    void set_col_valid(QString _col_valid);       // установить цвет корректного поля
    void set_col_error(QString _col_error);       // установить цвет ошибочного поля
    void set_i_v(QIntValidator * _i_v);           // установить контрольное устройство проверки целых чисел
    void set_d_v(QDoubleValidator * _d_v);        // установить контрольное устройство проверки нецелых чисел
    void set_l_e(QLineEdit * _l_e);               // установить редактируемое поле

private:
    int data_type;          // тип данных (0 - int, 1 - double, 2 - QString)
    int validator_type;     // тип используемого валидатора (0 - QIntValidator, 1 - QDoubleValidator, 2 - без валидатора)
    QString value;          // значение
    bool b_correct;         // признак корректности
    bool b_require;         // признак обязательности
    QString col_valid;      // цвет корректного поля
    QString col_error;      // цвет ошибочного поля
    QIntValidator * i_v;    // контрольное устройство проверки целых чисел
    QDoubleValidator * d_v; // контрольное устройство проверки нецелых чисел
    QLineEdit * l_e;        // редактируемое поле

public slots:

    // вызывается при изменении текста редактируемого поля
    void l_e_changed(QString _value);
};

#endif // CELL_VIEW_L_E_H
