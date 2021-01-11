/****************************************************************************
** Meta object code from reading C++ file 'kr_maneuver_form.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cp_id0/kr_maneuver_cpp_h/kr_maneuver_form.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kr_maneuver_form.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_kr_maneuver_form_t {
    QByteArrayData data[9];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_kr_maneuver_form_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_kr_maneuver_form_t qt_meta_stringdata_kr_maneuver_form = {
    {
QT_MOC_LITERAL(0, 0, 16), // "kr_maneuver_form"
QT_MOC_LITERAL(1, 17, 19), // "variant_l_e_changed"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 17), // "_variant_l_e_text"
QT_MOC_LITERAL(4, 56, 19), // "variant_c_b_changed"
QT_MOC_LITERAL(5, 76, 12), // "_variant_num"
QT_MOC_LITERAL(6, 89, 21), // "editor_p_b_save_click"
QT_MOC_LITERAL(7, 111, 20), // "table_p_b_save_click"
QT_MOC_LITERAL(8, 132, 23) // "table_p_b_add_row_click"

    },
    "kr_maneuver_form\0variant_l_e_changed\0"
    "\0_variant_l_e_text\0variant_c_b_changed\0"
    "_variant_num\0editor_p_b_save_click\0"
    "table_p_b_save_click\0table_p_b_add_row_click"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_kr_maneuver_form[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       6,    0,   45,    2, 0x0a /* Public */,
       7,    0,   46,    2, 0x0a /* Public */,
       8,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void kr_maneuver_form::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<kr_maneuver_form *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->variant_l_e_changed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->variant_c_b_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->editor_p_b_save_click(); break;
        case 3: _t->table_p_b_save_click(); break;
        case 4: _t->table_p_b_add_row_click(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject kr_maneuver_form::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_kr_maneuver_form.data,
    qt_meta_data_kr_maneuver_form,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *kr_maneuver_form::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *kr_maneuver_form::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_kr_maneuver_form.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int kr_maneuver_form::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
