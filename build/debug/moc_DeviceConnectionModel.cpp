/****************************************************************************
** Meta object code from reading C++ file 'DeviceConnectionModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../models/DeviceConnectionModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DeviceConnectionModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceConnectionModel_t {
    QByteArrayData data[23];
    char stringdata0[327];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceConnectionModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceConnectionModel_t qt_meta_stringdata_DeviceConnectionModel = {
    {
QT_MOC_LITERAL(0, 0, 21), // "DeviceConnectionModel"
QT_MOC_LITERAL(1, 22, 21), // "connectionTypeChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 22), // "connectionStateChanged"
QT_MOC_LITERAL(4, 68, 14), // "addressChanged"
QT_MOC_LITERAL(5, 83, 11), // "portChanged"
QT_MOC_LITERAL(6, 95, 19), // "errorMessageChanged"
QT_MOC_LITERAL(7, 115, 12), // "dataReceived"
QT_MOC_LITERAL(8, 128, 4), // "data"
QT_MOC_LITERAL(9, 133, 24), // "onConnectionStateChanged"
QT_MOC_LITERAL(10, 158, 38), // "ICommunicationService::Connec..."
QT_MOC_LITERAL(11, 197, 5), // "state"
QT_MOC_LITERAL(12, 203, 15), // "onErrorOccurred"
QT_MOC_LITERAL(13, 219, 5), // "error"
QT_MOC_LITERAL(14, 225, 13), // "connectDevice"
QT_MOC_LITERAL(15, 239, 4), // "type"
QT_MOC_LITERAL(16, 244, 16), // "disconnectDevice"
QT_MOC_LITERAL(17, 261, 8), // "sendData"
QT_MOC_LITERAL(18, 270, 14), // "connectionType"
QT_MOC_LITERAL(19, 285, 15), // "connectionState"
QT_MOC_LITERAL(20, 301, 7), // "address"
QT_MOC_LITERAL(21, 309, 4), // "port"
QT_MOC_LITERAL(22, 314, 12) // "errorMessage"

    },
    "DeviceConnectionModel\0connectionTypeChanged\0"
    "\0connectionStateChanged\0addressChanged\0"
    "portChanged\0errorMessageChanged\0"
    "dataReceived\0data\0onConnectionStateChanged\0"
    "ICommunicationService::ConnectionState\0"
    "state\0onErrorOccurred\0error\0connectDevice\0"
    "type\0disconnectDevice\0sendData\0"
    "connectionType\0connectionState\0address\0"
    "port\0errorMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceConnectionModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       5,   90, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,
       7,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   77,    2, 0x0a /* Public */,
      12,    1,   80,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      14,    1,   83,    2, 0x02 /* Public */,
      16,    0,   86,    2, 0x02 /* Public */,
      17,    1,   87,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QString,   13,

 // methods: parameters
    QMetaType::Bool, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    8,

 // properties: name, type, flags
      18, QMetaType::Int, 0x00495001,
      19, QMetaType::Int, 0x00495001,
      20, QMetaType::QString, 0x00495103,
      21, QMetaType::Int, 0x00495103,
      22, QMetaType::QString, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,

       0        // eod
};

void DeviceConnectionModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DeviceConnectionModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectionTypeChanged(); break;
        case 1: _t->connectionStateChanged(); break;
        case 2: _t->addressChanged(); break;
        case 3: _t->portChanged(); break;
        case 4: _t->errorMessageChanged(); break;
        case 5: _t->dataReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->onConnectionStateChanged((*reinterpret_cast< ICommunicationService::ConnectionState(*)>(_a[1]))); break;
        case 7: _t->onErrorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: { bool _r = _t->connectDevice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->disconnectDevice(); break;
        case 10: { bool _r = _t->sendData((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DeviceConnectionModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceConnectionModel::connectionTypeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DeviceConnectionModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceConnectionModel::connectionStateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DeviceConnectionModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceConnectionModel::addressChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DeviceConnectionModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceConnectionModel::portChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DeviceConnectionModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceConnectionModel::errorMessageChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DeviceConnectionModel::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceConnectionModel::dataReceived)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DeviceConnectionModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->connectionType(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->connectionState(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->address(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->port(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->errorMessage(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<DeviceConnectionModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setAddress(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setPort(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject DeviceConnectionModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DeviceConnectionModel.data,
    qt_meta_data_DeviceConnectionModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DeviceConnectionModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceConnectionModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceConnectionModel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DeviceConnectionModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DeviceConnectionModel::connectionTypeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DeviceConnectionModel::connectionStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DeviceConnectionModel::addressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DeviceConnectionModel::portChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void DeviceConnectionModel::errorMessageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void DeviceConnectionModel::dataReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
