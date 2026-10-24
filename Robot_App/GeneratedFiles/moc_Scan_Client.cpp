/****************************************************************************
** Meta object code from reading C++ file 'Scan_Client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Scan_Client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Scan_Client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c_Scan_Client_t {
    QByteArrayData data[22];
    char stringdata0[236];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c_Scan_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c_Scan_Client_t qt_meta_stringdata_c_Scan_Client = {
    {
QT_MOC_LITERAL(0, 0, 13), // "c_Scan_Client"
QT_MOC_LITERAL(1, 14, 12), // "Connect_Done"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 15), // "Disconnect_Done"
QT_MOC_LITERAL(4, 44, 16), // "Read_String_Done"
QT_MOC_LITERAL(5, 61, 3), // "msg"
QT_MOC_LITERAL(6, 65, 17), // "Write_String_Done"
QT_MOC_LITERAL(7, 83, 17), // "Read_String_Error"
QT_MOC_LITERAL(8, 101, 18), // "Write_String_Error"
QT_MOC_LITERAL(9, 120, 6), // "Status"
QT_MOC_LITERAL(10, 127, 5), // "state"
QT_MOC_LITERAL(11, 133, 7), // "Collect"
QT_MOC_LITERAL(12, 141, 3), // "num"
QT_MOC_LITERAL(13, 145, 4), // "Init"
QT_MOC_LITERAL(14, 150, 14), // "Connect_Device"
QT_MOC_LITERAL(15, 165, 2), // "ip"
QT_MOC_LITERAL(16, 168, 4), // "port"
QT_MOC_LITERAL(17, 173, 17), // "Disconnect_Device"
QT_MOC_LITERAL(18, 191, 11), // "Read_String"
QT_MOC_LITERAL(19, 203, 12), // "Write_String"
QT_MOC_LITERAL(20, 216, 5), // "value"
QT_MOC_LITERAL(21, 222, 13) // "State_Changed"

    },
    "c_Scan_Client\0Connect_Done\0\0Disconnect_Done\0"
    "Read_String_Done\0msg\0Write_String_Done\0"
    "Read_String_Error\0Write_String_Error\0"
    "Status\0state\0Collect\0num\0Init\0"
    "Connect_Device\0ip\0port\0Disconnect_Device\0"
    "Read_String\0Write_String\0value\0"
    "State_Changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c_Scan_Client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    1,   86,    2, 0x06 /* Public */,
       6,    0,   89,    2, 0x06 /* Public */,
       7,    0,   90,    2, 0x06 /* Public */,
       8,    0,   91,    2, 0x06 /* Public */,
       9,    1,   92,    2, 0x06 /* Public */,
      11,    1,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   98,    2, 0x0a /* Public */,
      14,    2,   99,    2, 0x0a /* Public */,
      17,    0,  104,    2, 0x0a /* Public */,
      18,    0,  105,    2, 0x0a /* Public */,
      19,    3,  106,    2, 0x0a /* Public */,
      21,    0,  113,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   15,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,   15,   16,   20,
    QMetaType::Void,

       0        // eod
};

void c_Scan_Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c_Scan_Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Connect_Done(); break;
        case 1: _t->Disconnect_Done(); break;
        case 2: _t->Read_String_Done((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->Write_String_Done(); break;
        case 4: _t->Read_String_Error(); break;
        case 5: _t->Write_String_Error(); break;
        case 6: _t->Status((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->Collect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->Init(); break;
        case 9: _t->Connect_Device((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->Disconnect_Device(); break;
        case 11: _t->Read_String(); break;
        case 12: _t->Write_String((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 13: _t->State_Changed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c_Scan_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Scan_Client::Connect_Done)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (c_Scan_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Scan_Client::Disconnect_Done)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (c_Scan_Client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Scan_Client::Read_String_Done)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (c_Scan_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Scan_Client::Write_String_Done)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (c_Scan_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Scan_Client::Read_String_Error)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (c_Scan_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Scan_Client::Write_String_Error)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (c_Scan_Client::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Scan_Client::Status)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (c_Scan_Client::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Scan_Client::Collect)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c_Scan_Client::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_c_Scan_Client.data,
    qt_meta_data_c_Scan_Client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c_Scan_Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c_Scan_Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c_Scan_Client.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int c_Scan_Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void c_Scan_Client::Connect_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void c_Scan_Client::Disconnect_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void c_Scan_Client::Read_String_Done(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void c_Scan_Client::Write_String_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void c_Scan_Client::Read_String_Error()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void c_Scan_Client::Write_String_Error()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void c_Scan_Client::Status(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void c_Scan_Client::Collect(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
