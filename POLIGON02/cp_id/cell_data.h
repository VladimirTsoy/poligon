#ifndef CELL_DATA_H
#define CELL_DATA_H

#include <stddef.h>
#include <QString>

// данные ячейки таблицы
class cell_data
{
public:
    // конструктор
    cell_data(int _type,
              bool _b_require,
              QString _name);

    // деструктор
    ~cell_data();

    // сгенерировать текст
    void generate_text(QString _indention);

    int ret_type();                      // вернуть вариант хранения данных
    QString ret_value();                 // вернуть значение
    bool ret_b_require();                // вернуть признак обязательности
    QString ret_name();                  // вернуть имя
    QString ret_text();                  // вернуть текст

    void set_type(int _type);            // установить вариант хранения данных
    void set_value(QString _value);      // установить значение
    void set_b_require(bool _b_require); // установить признак обязательности
    void set_name(QString _name);        // установить имя
    void set_text(QString _text);        // установить текст

private:
    int type;       // вариант хранения данных (0 - атрибут, 1 - элемент)
    QString value;  // значение
    bool b_require; // признак обязательности
    QString name;   // имя
    QString text;   // текст
};

#endif // CELL_DATA_H
