/****************************************************************************
** Meta object code from reading C++ file 'TcpSocketThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../HistoryPage/TcpSocketThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TcpSocketThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TcpSocketThread_t {
    QByteArrayData data[13];
    char stringdata0[231];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpSocketThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpSocketThread_t qt_meta_stringdata_TcpSocketThread = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TcpSocketThread"
QT_MOC_LITERAL(1, 16, 27), // "SignalSendConnectStatesToUI"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 9), // "isConnect"
QT_MOC_LITERAL(4, 55, 18), // "SignalSendDateToUI"
QT_MOC_LITERAL(5, 74, 14), // "qByteArrayDate"
QT_MOC_LITERAL(6, 89, 17), // "_SlotPoctReadMesg"
QT_MOC_LITERAL(7, 107, 21), // "_SlotPoctConnectError"
QT_MOC_LITERAL(8, 129, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(9, 158, 11), // "socketError"
QT_MOC_LITERAL(10, 170, 21), // "_SlotConnectPisServer"
QT_MOC_LITERAL(11, 192, 22), // "_SlotConnectPoctServer"
QT_MOC_LITERAL(12, 215, 15) // "_SlotThreadQuit"

    },
    "TcpSocketThread\0SignalSendConnectStatesToUI\0"
    "\0isConnect\0SignalSendDateToUI\0"
    "qByteArrayDate\0_SlotPoctReadMesg\0"
    "_SlotPoctConnectError\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "_SlotConnectPisServer\0_SlotConnectPoctServer\0"
    "_SlotThreadQuit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpSocketThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   55,    2, 0x08 /* Private */,
       7,    1,   56,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,
      11,    0,   60,    2, 0x08 /* Private */,
      12,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TcpSocketThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpSocketThread *_t = static_cast<TcpSocketThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalSendConnectStatesToUI((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->SignalSendDateToUI((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->_SlotPoctReadMesg(); break;
        case 3: _t->_SlotPoctConnectError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->_SlotConnectPisServer(); break;
        case 5: _t->_SlotConnectPoctServer(); break;
        case 6: _t->_SlotThreadQuit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TcpSocketThread::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpSocketThread::SignalSendConnectStatesToUI)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TcpSocketThread::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpSocketThread::SignalSendDateToUI)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject TcpSocketThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TcpSocketThread.data,
      qt_meta_data_TcpSocketThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TcpSocketThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpSocketThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TcpSocketThread.stringdata0))
        return static_cast<void*>(const_cast< TcpSocketThread*>(this));
    return QObject::qt_metacast(_clname);
}

int TcpSocketThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TcpSocketThread::SignalSendConnectStatesToUI(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpSocketThread::SignalSendDateToUI(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
