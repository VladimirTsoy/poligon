/****************************************************************************
** Meta object code from reading C++ file 'kr_maneuver_table_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cp_id0/kr_maneuver_cpp_h/kr_maneuver_table_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kr_maneuver_table_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_kr_maneuver_table_view_t {
    QByteArrayData data[5];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_kr_maneuver_table_view_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_kr_maneuver_table_view_t qt_meta_stringdata_kr_maneuver_table_view = {
    {
QT_MOC_LITERAL(0, 0, 22), // "kr_maneuver_table_view"
QT_MOC_LITERAL(1, 23, 16), // "p_b_delete_click"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 8), // "_row_num"
QT_MOC_LITERAL(4, 50, 21) // "table_p_b_save_enable"

    },
    "kr_maneuver_table_view\0p_b_delete_click\0"
    "\0_row_num\0table_p_b_save_enable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_kr_maneuver_table_view[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       4,    1,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void kr_maneuver_table_view::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<kr_maneuver_table_view *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->p_b_delete_click((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->table_p_b_save_enable((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject kr_maneuver_table_view::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_kr_maneuver_table_view.data,
    qt_meta_data_kr_maneuver_table_view,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *kr_maneuver_table_view::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *kr_maneuver_table_view::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_kr_maneuver_table_view.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int kr_maneuver_table_view::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
