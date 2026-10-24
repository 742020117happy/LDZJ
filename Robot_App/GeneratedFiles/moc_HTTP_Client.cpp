/****************************************************************************
** Meta object code from reading C++ file 'HTTP_Client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HTTP_Client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HTTP_Client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c_HTTP_Client_t {
    QByteArrayData data[32];
    char stringdata0[339];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c_HTTP_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c_HTTP_Client_t qt_meta_stringdata_c_HTTP_Client = {
    {
QT_MOC_LITERAL(0, 0, 13), // "c_HTTP_Client"
QT_MOC_LITERAL(1, 14, 12), // "Connect_Done"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 3), // "url"
QT_MOC_LITERAL(4, 32, 15), // "Disconnect_Done"
QT_MOC_LITERAL(5, 48, 14), // "Set_Token_Done"
QT_MOC_LITERAL(6, 63, 5), // "token"
QT_MOC_LITERAL(7, 69, 13), // "Response_Done"
QT_MOC_LITERAL(8, 83, 3), // "api"
QT_MOC_LITERAL(9, 87, 4), // "body"
QT_MOC_LITERAL(10, 92, 17), // "Response_Raw_Done"
QT_MOC_LITERAL(11, 110, 4), // "data"
QT_MOC_LITERAL(12, 115, 14), // "Response_Error"
QT_MOC_LITERAL(13, 130, 9), // "error_msg"
QT_MOC_LITERAL(14, 140, 6), // "Status"
QT_MOC_LITERAL(15, 147, 3), // "val"
QT_MOC_LITERAL(16, 151, 4), // "Init"
QT_MOC_LITERAL(17, 156, 14), // "Connect_Device"
QT_MOC_LITERAL(18, 171, 2), // "ip"
QT_MOC_LITERAL(19, 174, 4), // "port"
QT_MOC_LITERAL(20, 179, 17), // "Disconnect_Device"
QT_MOC_LITERAL(21, 197, 9), // "Set_Token"
QT_MOC_LITERAL(22, 207, 16), // "Send_GET_Request"
QT_MOC_LITERAL(23, 224, 6), // "params"
QT_MOC_LITERAL(24, 231, 7), // "headers"
QT_MOC_LITERAL(25, 239, 17), // "Send_POST_Request"
QT_MOC_LITERAL(26, 257, 16), // "Send_PUT_Request"
QT_MOC_LITERAL(27, 274, 19), // "Send_DELETE_Request"
QT_MOC_LITERAL(28, 294, 12), // "Send_GET_Raw"
QT_MOC_LITERAL(29, 307, 10), // "Read_Ready"
QT_MOC_LITERAL(30, 318, 14), // "QNetworkReply*"
QT_MOC_LITERAL(31, 333, 5) // "reply"

    },
    "c_HTTP_Client\0Connect_Done\0\0url\0"
    "Disconnect_Done\0Set_Token_Done\0token\0"
    "Response_Done\0api\0body\0Response_Raw_Done\0"
    "data\0Response_Error\0error_msg\0Status\0"
    "val\0Init\0Connect_Device\0ip\0port\0"
    "Disconnect_Device\0Set_Token\0"
    "Send_GET_Request\0params\0headers\0"
    "Send_POST_Request\0Send_PUT_Request\0"
    "Send_DELETE_Request\0Send_GET_Raw\0"
    "Read_Ready\0QNetworkReply*\0reply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c_HTTP_Client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    0,  102,    2, 0x06 /* Public */,
       5,    1,  103,    2, 0x06 /* Public */,
       7,    2,  106,    2, 0x06 /* Public */,
      10,    2,  111,    2, 0x06 /* Public */,
      12,    2,  116,    2, 0x06 /* Public */,
      14,    1,  121,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,  124,    2, 0x0a /* Public */,
      17,    3,  125,    2, 0x0a /* Public */,
      20,    0,  132,    2, 0x0a /* Public */,
      21,    1,  133,    2, 0x0a /* Public */,
      22,    3,  136,    2, 0x0a /* Public */,
      25,    3,  143,    2, 0x0a /* Public */,
      26,    3,  150,    2, 0x0a /* Public */,
      27,    3,  157,    2, 0x0a /* Public */,
      28,    3,  164,    2, 0x0a /* Public */,
      29,    1,  171,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    8,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,   13,
    QMetaType::Void, QMetaType::QString,   15,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::UShort, QMetaType::QString,   18,   19,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject, QMetaType::QJsonObject,    8,   23,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject, QMetaType::QJsonObject,    8,    9,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject, QMetaType::QJsonObject,    8,    9,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject, QMetaType::QJsonObject,    8,   23,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::QJsonObject, QMetaType::QJsonObject,    8,   23,   24,
    QMetaType::Void, 0x80000000 | 30,   31,

       0        // eod
};

void c_HTTP_Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c_HTTP_Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Connect_Done((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->Disconnect_Done(); break;
        case 2: _t->Set_Token_Done((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->Response_Done((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2]))); break;
        case 4: _t->Response_Raw_Done((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 5: _t->Response_Error((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->Status((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->Init(); break;
        case 8: _t->Connect_Device((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 9: _t->Disconnect_Device(); break;
        case 10: _t->Set_Token((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->Send_GET_Request((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< QJsonObject(*)>(_a[3]))); break;
        case 12: _t->Send_POST_Request((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< QJsonObject(*)>(_a[3]))); break;
        case 13: _t->Send_PUT_Request((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< QJsonObject(*)>(_a[3]))); break;
        case 14: _t->Send_DELETE_Request((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< QJsonObject(*)>(_a[3]))); break;
        case 15: _t->Send_GET_Raw((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2])),(*reinterpret_cast< QJsonObject(*)>(_a[3]))); break;
        case 16: _t->Read_Ready((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c_HTTP_Client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_HTTP_Client::Connect_Done)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (c_HTTP_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_HTTP_Client::Disconnect_Done)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (c_HTTP_Client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_HTTP_Client::Set_Token_Done)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (c_HTTP_Client::*)(QString , QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_HTTP_Client::Response_Done)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (c_HTTP_Client::*)(QString , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_HTTP_Client::Response_Raw_Done)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (c_HTTP_Client::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_HTTP_Client::Response_Error)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (c_HTTP_Client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_HTTP_Client::Status)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c_HTTP_Client::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_c_HTTP_Client.data,
    qt_meta_data_c_HTTP_Client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c_HTTP_Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c_HTTP_Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c_HTTP_Client.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int c_HTTP_Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void c_HTTP_Client::Connect_Done(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void c_HTTP_Client::Disconnect_Done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void c_HTTP_Client::Set_Token_Done(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void c_HTTP_Client::Response_Done(QString _t1, QJsonObject _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void c_HTTP_Client::Response_Raw_Done(QString _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void c_HTTP_Client::Response_Error(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void c_HTTP_Client::Status(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
