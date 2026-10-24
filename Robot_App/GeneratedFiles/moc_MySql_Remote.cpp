/****************************************************************************
** Meta object code from reading C++ file 'MySql_Remote.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MySql_Remote.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MySql_Remote.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c_Sql_Remote_t {
    QByteArrayData data[8];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c_Sql_Remote_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c_Sql_Remote_t qt_meta_stringdata_c_Sql_Remote = {
    {
QT_MOC_LITERAL(0, 0, 12), // "c_Sql_Remote"
QT_MOC_LITERAL(1, 13, 12), // "Connect_Done"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "init"
QT_MOC_LITERAL(4, 32, 12), // "connectMysql"
QT_MOC_LITERAL(5, 45, 22), // "updateActualReturnTime"
QT_MOC_LITERAL(6, 68, 18), // "On_Photo_Completed"
QT_MOC_LITERAL(7, 87, 5) // "fname"

    },
    "c_Sql_Remote\0Connect_Done\0\0init\0"
    "connectMysql\0updateActualReturnTime\0"
    "On_Photo_Completed\0fname"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c_Sql_Remote[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void c_Sql_Remote::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c_Sql_Remote *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Connect_Done(); break;
        case 1: _t->init(); break;
        case 2: _t->connectMysql(); break;
        case 3: _t->updateActualReturnTime(); break;
        case 4: _t->On_Photo_Completed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c_Sql_Remote::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Sql_Remote::Connect_Done)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c_Sql_Remote::staticMetaObject = { {
    &c_Object::staticMetaObject,
    qt_meta_stringdata_c_Sql_Remote.data,
    qt_meta_data_c_Sql_Remote,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c_Sql_Remote::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c_Sql_Remote::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c_Sql_Remote.stringdata0))
        return static_cast<void*>(this);
    return c_Object::qt_metacast(_clname);
}

int c_Sql_Remote::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = c_Object::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void c_Sql_Remote::Connect_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
