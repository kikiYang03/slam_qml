/****************************************************************************
** Meta object code from reading C++ file 'ProtocolParser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../protocol/ProtocolParser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProtocolParser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ProtocolParser_t {
    QByteArrayData data[16];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProtocolParser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProtocolParser_t qt_meta_stringdata_ProtocolParser = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ProtocolParser"
QT_MOC_LITERAL(1, 15, 17), // "laserScanReceived"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 12), // "LaserScanMsg"
QT_MOC_LITERAL(4, 47, 4), // "scan"
QT_MOC_LITERAL(5, 52, 10), // "tfReceived"
QT_MOC_LITERAL(6, 63, 5), // "TFMsg"
QT_MOC_LITERAL(7, 69, 2), // "tf"
QT_MOC_LITERAL(8, 72, 18), // "pointCloudReceived"
QT_MOC_LITERAL(9, 91, 13), // "PointCloudMsg"
QT_MOC_LITERAL(10, 105, 5), // "cloud"
QT_MOC_LITERAL(11, 111, 17), // "parameterResponse"
QT_MOC_LITERAL(12, 129, 3), // "key"
QT_MOC_LITERAL(13, 133, 5), // "value"
QT_MOC_LITERAL(14, 139, 10), // "parseError"
QT_MOC_LITERAL(15, 150, 5) // "error"

    },
    "ProtocolParser\0laserScanReceived\0\0"
    "LaserScanMsg\0scan\0tfReceived\0TFMsg\0"
    "tf\0pointCloudReceived\0PointCloudMsg\0"
    "cloud\0parameterResponse\0key\0value\0"
    "parseError\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProtocolParser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       8,    1,   45,    2, 0x06 /* Public */,
      11,    2,   48,    2, 0x06 /* Public */,
      14,    1,   53,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariant,   12,   13,
    QMetaType::Void, QMetaType::QString,   15,

       0        // eod
};

void ProtocolParser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProtocolParser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->laserScanReceived((*reinterpret_cast< const LaserScanMsg(*)>(_a[1]))); break;
        case 1: _t->tfReceived((*reinterpret_cast< const TFMsg(*)>(_a[1]))); break;
        case 2: _t->pointCloudReceived((*reinterpret_cast< const PointCloudMsg(*)>(_a[1]))); break;
        case 3: _t->parameterResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 4: _t->parseError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< LaserScanMsg >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TFMsg >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PointCloudMsg >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ProtocolParser::*)(const LaserScanMsg & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProtocolParser::laserScanReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(const TFMsg & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProtocolParser::tfReceived)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(const PointCloudMsg & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProtocolParser::pointCloudReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(const QString & , const QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProtocolParser::parameterResponse)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ProtocolParser::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ProtocolParser::parseError)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ProtocolParser::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ProtocolParser.data,
    qt_meta_data_ProtocolParser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ProtocolParser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProtocolParser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProtocolParser.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ProtocolParser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ProtocolParser::laserScanReceived(const LaserScanMsg & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ProtocolParser::tfReceived(const TFMsg & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ProtocolParser::pointCloudReceived(const PointCloudMsg & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ProtocolParser::parameterResponse(const QString & _t1, const QVariant & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ProtocolParser::parseError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
