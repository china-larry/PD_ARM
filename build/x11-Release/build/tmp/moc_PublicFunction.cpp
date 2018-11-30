/****************************************************************************
** Meta object code from reading C++ file 'PublicFunction.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../PublicFunction.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PublicFunction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CFuseImageThread_t {
    QByteArrayData data[3];
    char stringdata0[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CFuseImageThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CFuseImageThread_t qt_meta_stringdata_CFuseImageThread = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CFuseImageThread"
QT_MOC_LITERAL(1, 17, 12), // "SignalFuseOk"
QT_MOC_LITERAL(2, 30, 0) // ""

    },
    "CFuseImageThread\0SignalFuseOk\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CFuseImageThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void CFuseImageThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CFuseImageThread *_t = static_cast<CFuseImageThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalFuseOk(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CFuseImageThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CFuseImageThread::SignalFuseOk)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CFuseImageThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CFuseImageThread.data,
      qt_meta_data_CFuseImageThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CFuseImageThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CFuseImageThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CFuseImageThread.stringdata0))
        return static_cast<void*>(const_cast< CFuseImageThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CFuseImageThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CFuseImageThread::SignalFuseOk()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_CDeleteImageThread_t {
    QByteArrayData data[3];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CDeleteImageThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CDeleteImageThread_t qt_meta_stringdata_CDeleteImageThread = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CDeleteImageThread"
QT_MOC_LITERAL(1, 19, 14), // "SignalDeleteOk"
QT_MOC_LITERAL(2, 34, 0) // ""

    },
    "CDeleteImageThread\0SignalDeleteOk\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CDeleteImageThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void CDeleteImageThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CDeleteImageThread *_t = static_cast<CDeleteImageThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalDeleteOk(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CDeleteImageThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDeleteImageThread::SignalDeleteOk)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CDeleteImageThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CDeleteImageThread.data,
      qt_meta_data_CDeleteImageThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CDeleteImageThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CDeleteImageThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CDeleteImageThread.stringdata0))
        return static_cast<void*>(const_cast< CDeleteImageThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CDeleteImageThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CDeleteImageThread::SignalDeleteOk()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
