/****************************************************************************
** Meta object code from reading C++ file 'QrcodeDetector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../AdjustLight/QrcodeDetector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QrcodeDetector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QRCodeDetector_t {
    QByteArrayData data[12];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QRCodeDetector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QRCodeDetector_t qt_meta_stringdata_QRCodeDetector = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QRCodeDetector"
QT_MOC_LITERAL(1, 15, 20), // "SignalQRCodeLocation"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 10), // "strPathPic"
QT_MOC_LITERAL(4, 48, 16), // "SignalQRCodeInfo"
QT_MOC_LITERAL(5, 65, 10), // "QRCodeInfo"
QT_MOC_LITERAL(6, 76, 5), // "sInfo"
QT_MOC_LITERAL(7, 82, 13), // "SignalErrInfo"
QT_MOC_LITERAL(8, 96, 11), // "EnumTypeErr"
QT_MOC_LITERAL(9, 108, 4), // "eErr"
QT_MOC_LITERAL(10, 113, 15), // "SignalGetQRCode"
QT_MOC_LITERAL(11, 129, 14) // "_SlotGetQRcode"

    },
    "QRCodeDetector\0SignalQRCodeLocation\0"
    "\0strPathPic\0SignalQRCodeInfo\0QRCodeInfo\0"
    "sInfo\0SignalErrInfo\0EnumTypeErr\0eErr\0"
    "SignalGetQRCode\0_SlotGetQRcode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QRCodeDetector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       7,    1,   45,    2, 0x06 /* Public */,
      10,    0,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void QRCodeDetector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QRCodeDetector *_t = static_cast<QRCodeDetector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalQRCodeLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->SignalQRCodeInfo((*reinterpret_cast< QRCodeInfo(*)>(_a[1]))); break;
        case 2: _t->SignalErrInfo((*reinterpret_cast< EnumTypeErr(*)>(_a[1]))); break;
        case 3: _t->SignalGetQRCode(); break;
        case 4: _t->_SlotGetQRcode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QRCodeDetector::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QRCodeDetector::SignalQRCodeLocation)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QRCodeDetector::*_t)(QRCodeInfo );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QRCodeDetector::SignalQRCodeInfo)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QRCodeDetector::*_t)(EnumTypeErr );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QRCodeDetector::SignalErrInfo)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QRCodeDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QRCodeDetector::SignalGetQRCode)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject QRCodeDetector::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_QRCodeDetector.data,
      qt_meta_data_QRCodeDetector,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QRCodeDetector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QRCodeDetector::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QRCodeDetector.stringdata0))
        return static_cast<void*>(const_cast< QRCodeDetector*>(this));
    return QThread::qt_metacast(_clname);
}

int QRCodeDetector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QRCodeDetector::SignalQRCodeLocation(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QRCodeDetector::SignalQRCodeInfo(QRCodeInfo _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QRCodeDetector::SignalErrInfo(EnumTypeErr _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QRCodeDetector::SignalGetQRCode()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
