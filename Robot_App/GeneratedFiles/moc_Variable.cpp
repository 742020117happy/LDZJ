/****************************************************************************
** Meta object code from reading C++ file 'Variable.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Variable.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Variable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c_Object_t {
    QByteArrayData data[27];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c_Object_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c_Object_t qt_meta_stringdata_c_Object = {
    {
QT_MOC_LITERAL(0, 0, 8), // "c_Object"
QT_MOC_LITERAL(1, 9, 6), // "Status"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 5), // "state"
QT_MOC_LITERAL(4, 23, 10), // "BitToFloat"
QT_MOC_LITERAL(5, 34, 6), // "float&"
QT_MOC_LITERAL(6, 41, 10), // "floatValue"
QT_MOC_LITERAL(7, 52, 11), // "first16Bits"
QT_MOC_LITERAL(8, 64, 12), // "second16Bits"
QT_MOC_LITERAL(9, 77, 10), // "FloatToBit"
QT_MOC_LITERAL(10, 88, 8), // "quint16&"
QT_MOC_LITERAL(11, 97, 8), // "IntToBit"
QT_MOC_LITERAL(12, 106, 8), // "intValue"
QT_MOC_LITERAL(13, 115, 10), // "high16Bits"
QT_MOC_LITERAL(14, 126, 9), // "low16Bits"
QT_MOC_LITERAL(15, 136, 8), // "BitToInt"
QT_MOC_LITERAL(16, 145, 8), // "quint32&"
QT_MOC_LITERAL(17, 154, 10), // "TCP_Status"
QT_MOC_LITERAL(18, 165, 5), // "State"
QT_MOC_LITERAL(19, 171, 13), // "Modbus_Status"
QT_MOC_LITERAL(20, 185, 11), // "CGXi_Status"
QT_MOC_LITERAL(21, 197, 9), // "CGXi_Mode"
QT_MOC_LITERAL(22, 207, 15), // "CGXi_Joint_Mode"
QT_MOC_LITERAL(23, 223, 6), // "QtPing"
QT_MOC_LITERAL(24, 230, 2), // "ip"
QT_MOC_LITERAL(25, 233, 6), // "msleep"
QT_MOC_LITERAL(26, 240, 4) // "mSec"

    },
    "c_Object\0Status\0\0state\0BitToFloat\0"
    "float&\0floatValue\0first16Bits\0"
    "second16Bits\0FloatToBit\0quint16&\0"
    "IntToBit\0intValue\0high16Bits\0low16Bits\0"
    "BitToInt\0quint32&\0TCP_Status\0State\0"
    "Modbus_Status\0CGXi_Status\0CGXi_Mode\0"
    "CGXi_Joint_Mode\0QtPing\0ip\0msleep\0mSec"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c_Object[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    3,   77,    2, 0x0a /* Public */,
       9,    3,   84,    2, 0x0a /* Public */,
      11,    3,   91,    2, 0x0a /* Public */,
      15,    3,   98,    2, 0x0a /* Public */,
      17,    1,  105,    2, 0x0a /* Public */,
      19,    1,  108,    2, 0x0a /* Public */,
      20,    1,  111,    2, 0x0a /* Public */,
      21,    1,  114,    2, 0x0a /* Public */,
      22,    1,  117,    2, 0x0a /* Public */,
      23,    1,  120,    2, 0x0a /* Public */,
      25,    1,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, QMetaType::UShort, QMetaType::UShort,    6,    7,    8,
    QMetaType::Void, QMetaType::Float, 0x80000000 | 10, 0x80000000 | 10,    6,    7,    8,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 10, 0x80000000 | 10,   12,   13,   14,
    QMetaType::Void, 0x80000000 | 16, QMetaType::UShort, QMetaType::UShort,   12,   13,   14,
    QMetaType::QString, QMetaType::Int,   18,
    QMetaType::QString, QMetaType::Int,   18,
    QMetaType::QString, QMetaType::Int,   18,
    QMetaType::QString, QMetaType::Int,   18,
    QMetaType::QString, QMetaType::Int,   18,
    QMetaType::Bool, QMetaType::QString,   24,
    QMetaType::Bool, QMetaType::Int,   26,

       0        // eod
};

void c_Object::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c_Object *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Status((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->BitToFloat((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 2: _t->FloatToBit((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 3: _t->IntToBit((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 4: _t->BitToInt((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 5: { QString _r = _t->TCP_Status((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 6: { QString _r = _t->Modbus_Status((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 7: { QString _r = _t->CGXi_Status((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 8: { QString _r = _t->CGXi_Mode((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 9: { QString _r = _t->CGXi_Joint_Mode((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->QtPing((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->msleep((*reinterpret_cast< const int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c_Object::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Object::Status)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c_Object::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_c_Object.data,
    qt_meta_data_c_Object,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c_Object::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c_Object::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c_Object.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int c_Object::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void c_Object::Status(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_c_Variable_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c_Variable_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c_Variable_t qt_meta_stringdata_c_Variable = {
    {
QT_MOC_LITERAL(0, 0, 10) // "c_Variable"

    },
    "c_Variable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c_Variable[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void c_Variable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject c_Variable::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_c_Variable.data,
    qt_meta_data_c_Variable,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c_Variable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c_Variable::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c_Variable.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int c_Variable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
