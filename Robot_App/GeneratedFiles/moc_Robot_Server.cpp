/****************************************************************************
** Meta object code from reading C++ file 'Robot_Server.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Robot_Server.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Robot_Server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c_Robot_Server_t {
    QByteArrayData data[29];
    char stringdata0[324];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c_Robot_Server_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c_Robot_Server_t qt_meta_stringdata_c_Robot_Server = {
    {
QT_MOC_LITERAL(0, 0, 14), // "c_Robot_Server"
QT_MOC_LITERAL(1, 15, 11), // "Listen_Done"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "Connect_Done"
QT_MOC_LITERAL(4, 41, 12), // "Connect_Loop"
QT_MOC_LITERAL(5, 54, 15), // "Disconnect_Done"
QT_MOC_LITERAL(6, 70, 15), // "Write_Json_Done"
QT_MOC_LITERAL(7, 86, 16), // "Write_Json_Error"
QT_MOC_LITERAL(8, 103, 17), // "Write_String_Done"
QT_MOC_LITERAL(9, 121, 18), // "Write_String_Error"
QT_MOC_LITERAL(10, 140, 15), // "Write_Byte_Done"
QT_MOC_LITERAL(11, 156, 16), // "Write_Byte_Error"
QT_MOC_LITERAL(12, 173, 9), // "Read_Done"
QT_MOC_LITERAL(13, 183, 6), // "buffer"
QT_MOC_LITERAL(14, 190, 10), // "Read_Error"
QT_MOC_LITERAL(15, 201, 6), // "Status"
QT_MOC_LITERAL(16, 208, 5), // "state"
QT_MOC_LITERAL(17, 214, 4), // "Init"
QT_MOC_LITERAL(18, 219, 14), // "Connect_Device"
QT_MOC_LITERAL(19, 234, 2), // "ip"
QT_MOC_LITERAL(20, 237, 4), // "port"
QT_MOC_LITERAL(21, 242, 17), // "Disconnect_Device"
QT_MOC_LITERAL(22, 260, 10), // "Write_Json"
QT_MOC_LITERAL(23, 271, 4), // "json"
QT_MOC_LITERAL(24, 276, 12), // "Write_String"
QT_MOC_LITERAL(25, 289, 3), // "str"
QT_MOC_LITERAL(26, 293, 10), // "Write_Byte"
QT_MOC_LITERAL(27, 304, 4), // "arry"
QT_MOC_LITERAL(28, 309, 14) // "New_Connection"

    },
    "c_Robot_Server\0Listen_Done\0\0Connect_Done\0"
    "Connect_Loop\0Disconnect_Done\0"
    "Write_Json_Done\0Write_Json_Error\0"
    "Write_String_Done\0Write_String_Error\0"
    "Write_Byte_Done\0Write_Byte_Error\0"
    "Read_Done\0buffer\0Read_Error\0Status\0"
    "state\0Init\0Connect_Device\0ip\0port\0"
    "Disconnect_Device\0Write_Json\0json\0"
    "Write_String\0str\0Write_Byte\0arry\0"
    "New_Connection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c_Robot_Server[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x06 /* Public */,
       3,    0,  115,    2, 0x06 /* Public */,
       4,    0,  116,    2, 0x06 /* Public */,
       5,    0,  117,    2, 0x06 /* Public */,
       6,    0,  118,    2, 0x06 /* Public */,
       7,    0,  119,    2, 0x06 /* Public */,
       8,    0,  120,    2, 0x06 /* Public */,
       9,    0,  121,    2, 0x06 /* Public */,
      10,    0,  122,    2, 0x06 /* Public */,
      11,    0,  123,    2, 0x06 /* Public */,
      12,    1,  124,    2, 0x06 /* Public */,
      14,    0,  127,    2, 0x06 /* Public */,
      15,    1,  128,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,  131,    2, 0x0a /* Public */,
      18,    2,  132,    2, 0x0a /* Public */,
      21,    0,  137,    2, 0x0a /* Public */,
      22,    1,  138,    2, 0x0a /* Public */,
      24,    1,  141,    2, 0x0a /* Public */,
      26,    1,  144,    2, 0x0a /* Public */,
      28,    0,  147,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   19,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,   23,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void, QMetaType::QByteArray,   27,
    QMetaType::Void,

       0        // eod
};

void c_Robot_Server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c_Robot_Server *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Listen_Done(); break;
        case 1: _t->Connect_Done(); break;
        case 2: _t->Connect_Loop(); break;
        case 3: _t->Disconnect_Done(); break;
        case 4: _t->Write_Json_Done(); break;
        case 5: _t->Write_Json_Error(); break;
        case 6: _t->Write_String_Done(); break;
        case 7: _t->Write_String_Error(); break;
        case 8: _t->Write_Byte_Done(); break;
        case 9: _t->Write_Byte_Error(); break;
        case 10: _t->Read_Done((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 11: _t->Read_Error(); break;
        case 12: _t->Status((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->Init(); break;
        case 14: _t->Connect_Device((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->Disconnect_Device(); break;
        case 16: _t->Write_Json((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 17: _t->Write_String((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->Write_Byte((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 19: _t->New_Connection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c_Robot_Server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Listen_Done)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (c_Robot_Server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Connect_Done)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (c_Robot_Server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Connect_Loop)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (c_Robot_Server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Disconnect_Done)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (c_Robot_Server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Write_Json_Done)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (c_Robot_Server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Write_Json_Error)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (c_Robot_Server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Write_String_Done)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (c_Robot_Server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Write_String_Error)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (c_Robot_Server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Write_Byte_Done)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (c_Robot_Server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Write_Byte_Error)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (c_Robot_Server::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Read_Done)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (c_Robot_Server::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Read_Error)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (c_Robot_Server::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Robot_Server::Status)) {
                *result = 12;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c_Robot_Server::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_c_Robot_Server.data,
    qt_meta_data_c_Robot_Server,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c_Robot_Server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c_Robot_Server::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c_Robot_Server.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int c_Robot_Server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void c_Robot_Server::Listen_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void c_Robot_Server::Connect_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void c_Robot_Server::Connect_Loop()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void c_Robot_Server::Disconnect_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void c_Robot_Server::Write_Json_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void c_Robot_Server::Write_Json_Error()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void c_Robot_Server::Write_String_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void c_Robot_Server::Write_String_Error()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void c_Robot_Server::Write_Byte_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void c_Robot_Server::Write_Byte_Error()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void c_Robot_Server::Read_Done(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void c_Robot_Server::Read_Error()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void c_Robot_Server::Status(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
