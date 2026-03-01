/****************************************************************************
** Meta object code from reading C++ file 'ICommunicationService.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../services/ICommunicationService.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ICommunicationService.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ICommunicationService_t {
    QByteArrayData data[17];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ICommunicationService_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ICommunicationService_t qt_meta_stringdata_ICommunicationService = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ICommunicationService"
QT_MOC_LITERAL(1, 22, 12), // "dataReceived"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 4), // "data"
QT_MOC_LITERAL(4, 41, 22), // "connectionStateChanged"
QT_MOC_LITERAL(5, 64, 15), // "ConnectionState"
QT_MOC_LITERAL(6, 80, 5), // "state"
QT_MOC_LITERAL(7, 86, 13), // "errorOccurred"
QT_MOC_LITERAL(8, 100, 5), // "error"
QT_MOC_LITERAL(9, 106, 14), // "ConnectionType"
QT_MOC_LITERAL(10, 121, 6), // "Serial"
QT_MOC_LITERAL(11, 128, 3), // "TCP"
QT_MOC_LITERAL(12, 132, 3), // "UDP"
QT_MOC_LITERAL(13, 136, 12), // "Disconnected"
QT_MOC_LITERAL(14, 149, 10), // "Connecting"
QT_MOC_LITERAL(15, 160, 9), // "Connected"
QT_MOC_LITERAL(16, 170, 5) // "Error"

    },
    "ICommunicationService\0dataReceived\0\0"
    "data\0connectionStateChanged\0ConnectionState\0"
    "state\0errorOccurred\0error\0ConnectionType\0"
    "Serial\0TCP\0UDP\0Disconnected\0Connecting\0"
    "Connected\0Error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ICommunicationService[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       2,   38, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,
       7,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::QString,    8,

 // enums: name, alias, flags, count, data
       9,    9, 0x2,    3,   48,
       5,    5, 0x2,    4,   54,

 // enum data: key, value
      10, uint(ICommunicationService::ConnectionType::Serial),
      11, uint(ICommunicationService::ConnectionType::TCP),
      12, uint(ICommunicationService::ConnectionType::UDP),
      13, uint(ICommunicationService::ConnectionState::Disconnected),
      14, uint(ICommunicationService::ConnectionState::Connecting),
      15, uint(ICommunicationService::ConnectionState::Connected),
      16, uint(ICommunicationService::ConnectionState::Error),

       0        // eod
};

void ICommunicationService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ICommunicationService *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: _t->connectionStateChanged((*reinterpret_cast< ConnectionState(*)>(_a[1]))); break;
        case 2: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ICommunicationService::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ICommunicationService::dataReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ICommunicationService::*)(ConnectionState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ICommunicationService::connectionStateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ICommunicationService::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ICommunicationService::errorOccurred)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ICommunicationService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ICommunicationService.data,
    qt_meta_data_ICommunicationService,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ICommunicationService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ICommunicationService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ICommunicationService.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ICommunicationService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ICommunicationService::dataReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ICommunicationService::connectionStateChanged(ConnectionState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ICommunicationService::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
