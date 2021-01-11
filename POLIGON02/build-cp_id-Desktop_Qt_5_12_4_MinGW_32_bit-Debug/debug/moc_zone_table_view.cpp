/****************************************************************************
** Meta object code from reading C++ file 'zone_table_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cp_id0/zone_cpp_h/zone_table_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zone_table_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_zone_table_view_t {
    QByteArrayData data[8];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_zone_table_view_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_zone_table_view_t qt_meta_stringdata_zone_table_view = {
    {
QT_MOC_LITERAL(0, 0, 15), // "zone_table_view"
QT_MOC_LITERAL(1, 16, 22), // "p_b_major_delete_click"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 6), // "_index"
QT_MOC_LITERAL(4, 47, 22), // "p_b_minor_delete_click"
QT_MOC_LITERAL(5, 70, 8), // "_row_num"
QT_MOC_LITERAL(6, 79, 13), // "p_b_add_click"
QT_MOC_LITERAL(7, 93, 21) // "table_p_b_save_enable"

    },
    "zone_table_view\0p_b_major_delete_click\0"
    "\0_index\0p_b_minor_delete_click\0_row_num\0"
    "p_b_add_click\0table_p_b_save_enable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_zone_table_view[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x0a /* Public */,
       7,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void zone_table_view::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<zone_table_view *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->p_b_major_delete_click((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->p_b_minor_delete_click((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->p_b_add_click((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->table_p_b_save_enable((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject zone_table_view::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_zone_table_view.data,
    qt_meta_data_zone_table_view,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *zone_table_view::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *zone_table_view::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_zone_table_view.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int zone_table_view::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
