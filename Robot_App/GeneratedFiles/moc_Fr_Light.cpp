/****************************************************************************
** Meta object code from reading C++ file 'Fr_Light.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Fr_Light.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Fr_Light.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_c_Fr_Light_t {
    QByteArrayData data[14];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_c_Fr_Light_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_c_Fr_Light_t qt_meta_stringdata_c_Fr_Light = {
    {
QT_MOC_LITERAL(0, 0, 10), // "c_Fr_Light"
QT_MOC_LITERAL(1, 11, 13), // "Working_State"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "state"
QT_MOC_LITERAL(4, 32, 13), // "Default_State"
QT_MOC_LITERAL(5, 46, 11), // "Error_State"
QT_MOC_LITERAL(6, 58, 11), // "Set_Working"
QT_MOC_LITERAL(7, 70, 11), // "Set_Default"
QT_MOC_LITERAL(8, 82, 9), // "Set_Error"
QT_MOC_LITERAL(9, 92, 8), // "Set_Null"
QT_MOC_LITERAL(10, 101, 9), // "Set_State"
QT_MOC_LITERAL(11, 111, 10), // "Set_Radius"
QT_MOC_LITERAL(12, 122, 5), // "value"
QT_MOC_LITERAL(13, 128, 9) // "Get_State"

    },
    "c_Fr_Light\0Working_State\0\0state\0"
    "Default_State\0Error_State\0Set_Working\0"
    "Set_Default\0Set_Error\0Set_Null\0Set_State\0"
    "Set_Radius\0value\0Get_State"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_c_Fr_Light[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       5,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    0,   76,    2, 0x0a /* Public */,
      10,    1,   77,    2, 0x0a /* Public */,
      11,    1,   80,    2, 0x0a /* Public */,
      13,    0,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Bool,

       0        // eod
};

void c_Fr_Light::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<c_Fr_Light *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Working_State((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->Default_State((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->Error_State((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->Set_Working(); break;
        case 4: _t->Set_Default(); break;
        case 5: _t->Set_Error(); break;
        case 6: _t->Set_Null(); break;
        case 7: _t->Set_State((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 8: _t->Set_Radius((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: { bool _r = _t->Get_State();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (c_Fr_Light::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Fr_Light::Working_State)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (c_Fr_Light::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Fr_Light::Default_State)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (c_Fr_Light::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&c_Fr_Light::Error_State)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject c_Fr_Light::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_c_Fr_Light.data,
    qt_meta_data_c_Fr_Light,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *c_Fr_Light::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *c_Fr_Light::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_c_Fr_Light.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int c_Fr_Light::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void c_Fr_Light::Working_State(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void c_Fr_Light::Default_State(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void c_Fr_Light::Error_State(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
