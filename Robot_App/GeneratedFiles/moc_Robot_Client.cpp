/****************************************************************************
** Meta object code from reading C++ file 'Robot_Client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Robot_Client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Robot_Client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c_TCP_Client_t {
    QByteArrayData data[20];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c_TCP_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c_TCP_Client_t qt_meta_stringdata_c_TCP_Client = {
    {
QT_MOC_LITERAL(0, 0, 12), // "c_TCP_Client"
QT_MOC_LITERAL(1, 13, 12), // "Connect_Done"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "Disconnect_Done"
QT_MOC_LITERAL(4, 43, 12), // "Connect_Loop"
QT_MOC_LITERAL(5, 56, 14), // "Read_Json_Done"
QT_MOC_LITERAL(6, 71, 5), // "value"
QT_MOC_LITERAL(7, 77, 15), // "Write_Json_Done"
QT_MOC_LITERAL(8, 93, 15), // "Read_Json_Error"
QT_MOC_LITERAL(9, 109, 16), // "Write_Json_Error"
QT_MOC_LITERAL(10, 126, 6), // "Status"
QT_MOC_LITERAL(11, 133, 5), // "state"
QT_MOC_LITERAL(12, 139, 4), // "Init"
QT_MOC_LITERAL(13, 144, 14), // "Connect_Device"
QT_MOC_LITERAL(14, 159, 2), // "ip"
QT_MOC_LITERAL(15, 162, 4), // "port"
QT_MOC_LITERAL(16, 167, 17), // "Disconnect_Device"
QT_MOC_LITERAL(17, 185, 10), // "Write_Json"
QT_MOC_LITERAL(18, 196, 9), // "Read_Json"
QT_MOC_LITERAL(19, 206, 13) // "State_Changed"

    },
    "c_TCP_Client\0Connect_Done\0\0Disconnect_Done\0"
    "Connect_Loop\0Read_Json_Done\0value\0"
    "Write_Json_Done\0Read_Json_Error\0"
    "Write_Json_Error\0Status\0state\0Init\0"
    "Connect_Device\0ip\0port\0Disconnect_Device\0"
    "Write_Json\0Read_Json\0State_Changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c_TCP_Client[] = {

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
       4,    0,   86,    2, 0x06 /* Public */,
       5,    1,   87,    2, 0x06 /* Public */,
       7,    0,   90,    2, 0x06 /* Public */,
       8,    0,   91,    2, 0x06 /* Public */,
       9,    0,   92,    2, 0x06 /* Public */,
      10,    1,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   96,    2, 0x0a /* Public */,
      13,    2,   97,    2, 0x0a /* Public */,
      16,    0,  102,    2, 0x0a /* Public */,
      17,    1,  103,    2, 0x0a /* Public */,
      18,    0,  106,    2, 0x08 /* Private */,
      19,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   14,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void c_TCP_Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c_TCP_Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Connect_Done(); break;
        case 1: _t->Disconnect_Done(); break;
        case 2: _t->Connect_Loop(); break;
        case 3: _t->Read_Json_Done((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 4: _t->Write_Json_Done(); break;
        case 5: _t->Read_Json_Error(); break;
        case 6: _t->Write_Json_Error(); break;
        case 7: _t->Status((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->Init(); break;
        case 9: _t->Connect_Device((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->Disconnect_Device(); break;
        case 11: _t->Write_Json((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 12: _t->Read_Json(); break;
        case 13: _t->State_Changed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c_TCP_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_TCP_Client::Connect_Done)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (c_TCP_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_TCP_Client::Disconnect_Done)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (c_TCP_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_TCP_Client::Connect_Loop)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (c_TCP_Client::*)(QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_TCP_Client::Read_Json_Done)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (c_TCP_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_TCP_Client::Write_Json_Done)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (c_TCP_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_TCP_Client::Read_Json_Error)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (c_TCP_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_TCP_Client::Write_Json_Error)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (c_TCP_Client::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_TCP_Client::Status)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c_TCP_Client::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_c_TCP_Client.data,
    qt_meta_data_c_TCP_Client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c_TCP_Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c_TCP_Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c_TCP_Client.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int c_TCP_Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void c_TCP_Client::Connect_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void c_TCP_Client::Disconnect_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void c_TCP_Client::Connect_Loop()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void c_TCP_Client::Read_Json_Done(QJsonObject _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void c_TCP_Client::Write_Json_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void c_TCP_Client::Read_Json_Error()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void c_TCP_Client::Write_Json_Error()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void c_TCP_Client::Status(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
