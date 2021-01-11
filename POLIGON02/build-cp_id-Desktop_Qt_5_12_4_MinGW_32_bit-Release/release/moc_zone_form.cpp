/****************************************************************************
** Meta object code from reading C++ file 'zone_form.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cp_id/zone_cpp_h/zone_form.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zone_form.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_zone_form_t {
    QByteArrayData data[10];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_zone_form_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_zone_form_t qt_meta_stringdata_zone_form = {
    {
QT_MOC_LITERAL(0, 0, 9), // "zone_form"
QT_MOC_LITERAL(1, 10, 19), // "variant_l_e_changed"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 17), // "_variant_l_e_text"
QT_MOC_LITERAL(4, 49, 19), // "variant_c_b_changed"
QT_MOC_LITERAL(5, 69, 12), // "_variant_num"
QT_MOC_LITERAL(6, 82, 21), // "editor_p_b_save_click"
QT_MOC_LITERAL(7, 104, 20), // "table_p_b_save_click"
QT_MOC_LITERAL(8, 125, 23), // "table_p_b_add_row_click"
QT_MOC_LITERAL(9, 149, 24) // "table_p_b_show_map_click"

    },
    "zone_form\0variant_l_e_changed\0\0"
    "_variant_l_e_text\0variant_c_b_changed\0"
    "_variant_num\0editor_p_b_save_click\0"
    "table_p_b_save_click\0table_p_b_add_row_click\0"
    "table_p_b_show_map_click"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_zone_form[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       4,    1,   47,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,
       8,    0,   52,    2, 0x0a /* Public */,
       9,    0,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void zone_form::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<zone_form *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->variant_l_e_changed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->variant_c_b_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->editor_p_b_save_click(); break;
        case 3: _t->table_p_b_save_click(); break;
        case 4: _t->table_p_b_add_row_click(); break;
        case 5: _t->table_p_b_show_map_click(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject zone_form::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_zone_form.data,
    qt_meta_data_zone_form,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *zone_form::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *zone_form::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_zone_form.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int zone_form::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
