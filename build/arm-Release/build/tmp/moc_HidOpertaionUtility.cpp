/****************************************************************************
** Meta object code from reading C++ file 'HidOpertaionUtility.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../AdjustLight/HidOpertaionUtility.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HidOpertaionUtility.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HIDReadThread_t {
    QByteArrayData data[4];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HIDReadThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HIDReadThread_t qt_meta_stringdata_HIDReadThread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "HIDReadThread"
QT_MOC_LITERAL(1, 14, 19), // "SignalReceiveNewCmd"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 14) // "qDataByteArray"

    },
    "HIDReadThread\0SignalReceiveNewCmd\0\0"
    "qDataByteArray"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HIDReadThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       1,    0,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,

       0        // eod
};

void HIDReadThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HIDReadThread *_t = static_cast<HIDReadThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalReceiveNewCmd((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->SignalReceiveNewCmd(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HIDReadThread::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDReadThread::SignalReceiveNewCmd)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (HIDReadThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDReadThread::SignalReceiveNewCmd)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject HIDReadThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_HIDReadThread.data,
      qt_meta_data_HIDReadThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HIDReadThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HIDReadThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HIDReadThread.stringdata0))
        return static_cast<void*>(const_cast< HIDReadThread*>(this));
    return QThread::qt_metacast(_clname);
}

int HIDReadThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void HIDReadThread::SignalReceiveNewCmd(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HIDReadThread::SignalReceiveNewCmd()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
struct qt_meta_stringdata_HIDOpertaionUtility_t {
    QByteArrayData data[38];
    char stringdata0[624];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HIDOpertaionUtility_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HIDOpertaionUtility_t qt_meta_stringdata_HIDOpertaionUtility = {
    {
QT_MOC_LITERAL(0, 0, 19), // "HIDOpertaionUtility"
QT_MOC_LITERAL(1, 20, 13), // "SignalHIDOpen"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 14), // "SignalHIDClose"
QT_MOC_LITERAL(4, 50, 14), // "SignalHIDWrite"
QT_MOC_LITERAL(5, 65, 14), // "writeByteArray"
QT_MOC_LITERAL(6, 80, 23), // "SignalReceiveDevVersion"
QT_MOC_LITERAL(7, 104, 13), // "strDevVersion"
QT_MOC_LITERAL(8, 118, 19), // "SignalReadDevParams"
QT_MOC_LITERAL(9, 138, 20), // "SignalWriteDevParams"
QT_MOC_LITERAL(10, 159, 15), // "DevConfigParams"
QT_MOC_LITERAL(11, 175, 15), // "devConfigParams"
QT_MOC_LITERAL(12, 191, 22), // "SignalReceiveDevParams"
QT_MOC_LITERAL(13, 214, 23), // "SignalOperationComplete"
QT_MOC_LITERAL(14, 238, 8), // "iCmdType"
QT_MOC_LITERAL(15, 247, 7), // "bResult"
QT_MOC_LITERAL(16, 255, 22), // "SignalReceiveTestCount"
QT_MOC_LITERAL(17, 278, 10), // "iTestCount"
QT_MOC_LITERAL(18, 289, 26), // "SignalHIDUpgradeSubControl"
QT_MOC_LITERAL(19, 316, 11), // "strFilePath"
QT_MOC_LITERAL(20, 328, 19), // "SignalUpgradeFinish"
QT_MOC_LITERAL(21, 348, 18), // "SignalUpgradeValue"
QT_MOC_LITERAL(22, 367, 18), // "SignalUpgradeError"
QT_MOC_LITERAL(23, 386, 14), // "strErrorMsgStr"
QT_MOC_LITERAL(24, 401, 13), // "SignalErrInfo"
QT_MOC_LITERAL(25, 415, 11), // "EnumTypeErr"
QT_MOC_LITERAL(26, 427, 9), // "qErrorMsg"
QT_MOC_LITERAL(27, 437, 28), // "SignalReceiveDevSerialNumber"
QT_MOC_LITERAL(28, 466, 15), // "strSerialNumner"
QT_MOC_LITERAL(29, 482, 19), // "SignalMotorLocation"
QT_MOC_LITERAL(30, 502, 12), // "_SlotLoadDll"
QT_MOC_LITERAL(31, 515, 14), // "_SlotUnloadDll"
QT_MOC_LITERAL(32, 530, 9), // "_SlotOpen"
QT_MOC_LITERAL(33, 540, 10), // "_SlotClose"
QT_MOC_LITERAL(34, 551, 10), // "_SlotWrite"
QT_MOC_LITERAL(35, 562, 18), // "_SlotReadDevParams"
QT_MOC_LITERAL(36, 581, 19), // "_SlotWriteDevParams"
QT_MOC_LITERAL(37, 601, 22) // "_SlotUpgradeSubControl"

    },
    "HIDOpertaionUtility\0SignalHIDOpen\0\0"
    "SignalHIDClose\0SignalHIDWrite\0"
    "writeByteArray\0SignalReceiveDevVersion\0"
    "strDevVersion\0SignalReadDevParams\0"
    "SignalWriteDevParams\0DevConfigParams\0"
    "devConfigParams\0SignalReceiveDevParams\0"
    "SignalOperationComplete\0iCmdType\0"
    "bResult\0SignalReceiveTestCount\0"
    "iTestCount\0SignalHIDUpgradeSubControl\0"
    "strFilePath\0SignalUpgradeFinish\0"
    "SignalUpgradeValue\0SignalUpgradeError\0"
    "strErrorMsgStr\0SignalErrInfo\0EnumTypeErr\0"
    "qErrorMsg\0SignalReceiveDevSerialNumber\0"
    "strSerialNumner\0SignalMotorLocation\0"
    "_SlotLoadDll\0_SlotUnloadDll\0_SlotOpen\0"
    "_SlotClose\0_SlotWrite\0_SlotReadDevParams\0"
    "_SlotWriteDevParams\0_SlotUpgradeSubControl"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HIDOpertaionUtility[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  134,    2, 0x06 /* Public */,
       3,    0,  135,    2, 0x06 /* Public */,
       4,    1,  136,    2, 0x06 /* Public */,
       6,    1,  139,    2, 0x06 /* Public */,
       8,    0,  142,    2, 0x06 /* Public */,
       9,    1,  143,    2, 0x06 /* Public */,
      12,    1,  146,    2, 0x06 /* Public */,
      13,    2,  149,    2, 0x06 /* Public */,
      16,    1,  154,    2, 0x06 /* Public */,
      18,    1,  157,    2, 0x06 /* Public */,
      20,    0,  160,    2, 0x06 /* Public */,
      21,    1,  161,    2, 0x06 /* Public */,
      22,    1,  164,    2, 0x06 /* Public */,
      24,    1,  167,    2, 0x06 /* Public */,
      27,    1,  170,    2, 0x06 /* Public */,
      29,    0,  173,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      30,    0,  174,    2, 0x08 /* Private */,
      31,    0,  175,    2, 0x08 /* Private */,
      32,    0,  176,    2, 0x08 /* Private */,
      33,    0,  177,    2, 0x08 /* Private */,
      34,    1,  178,    2, 0x08 /* Private */,
      35,    0,  181,    2, 0x08 /* Private */,
      36,    1,  182,    2, 0x08 /* Private */,
      37,    1,  185,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::UShort, QMetaType::Bool,   14,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QByteArray,    5,
    QMetaType::Bool,
    QMetaType::Bool, 0x80000000 | 10,   11,
    QMetaType::Bool, QMetaType::QString,   19,

       0        // eod
};

void HIDOpertaionUtility::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HIDOpertaionUtility *_t = static_cast<HIDOpertaionUtility *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalHIDOpen(); break;
        case 1: _t->SignalHIDClose(); break;
        case 2: _t->SignalHIDWrite((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->SignalReceiveDevVersion((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->SignalReadDevParams(); break;
        case 5: _t->SignalWriteDevParams((*reinterpret_cast< DevConfigParams(*)>(_a[1]))); break;
        case 6: _t->SignalReceiveDevParams((*reinterpret_cast< DevConfigParams(*)>(_a[1]))); break;
        case 7: _t->SignalOperationComplete((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->SignalReceiveTestCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->SignalHIDUpgradeSubControl((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->SignalUpgradeFinish(); break;
        case 11: _t->SignalUpgradeValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->SignalUpgradeError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->SignalErrInfo((*reinterpret_cast< EnumTypeErr(*)>(_a[1]))); break;
        case 14: _t->SignalReceiveDevSerialNumber((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->SignalMotorLocation(); break;
        case 16: _t->_SlotLoadDll(); break;
        case 17: _t->_SlotUnloadDll(); break;
        case 18: { bool _r = _t->_SlotOpen();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 19: { bool _r = _t->_SlotClose();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 20: { bool _r = _t->_SlotWrite((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 21: { bool _r = _t->_SlotReadDevParams();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 22: { bool _r = _t->_SlotWriteDevParams((*reinterpret_cast< DevConfigParams(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 23: { bool _r = _t->_SlotUpgradeSubControl((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HIDOpertaionUtility::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalHIDOpen)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalHIDClose)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalHIDWrite)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalReceiveDevVersion)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalReadDevParams)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)(DevConfigParams );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalWriteDevParams)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)(DevConfigParams );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalReceiveDevParams)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)(quint16 , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalOperationComplete)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalReceiveTestCount)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalHIDUpgradeSubControl)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalUpgradeFinish)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalUpgradeValue)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalUpgradeError)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)(EnumTypeErr );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalErrInfo)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalReceiveDevSerialNumber)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (HIDOpertaionUtility::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HIDOpertaionUtility::SignalMotorLocation)) {
                *result = 15;
                return;
            }
        }
    }
}

const QMetaObject HIDOpertaionUtility::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HIDOpertaionUtility.data,
      qt_meta_data_HIDOpertaionUtility,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HIDOpertaionUtility::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HIDOpertaionUtility::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HIDOpertaionUtility.stringdata0))
        return static_cast<void*>(const_cast< HIDOpertaionUtility*>(this));
    return QObject::qt_metacast(_clname);
}

int HIDOpertaionUtility::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void HIDOpertaionUtility::SignalHIDOpen()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void HIDOpertaionUtility::SignalHIDClose()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void HIDOpertaionUtility::SignalHIDWrite(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void HIDOpertaionUtility::SignalReceiveDevVersion(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void HIDOpertaionUtility::SignalReadDevParams()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void HIDOpertaionUtility::SignalWriteDevParams(DevConfigParams _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void HIDOpertaionUtility::SignalReceiveDevParams(DevConfigParams _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void HIDOpertaionUtility::SignalOperationComplete(quint16 _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void HIDOpertaionUtility::SignalReceiveTestCount(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void HIDOpertaionUtility::SignalHIDUpgradeSubControl(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void HIDOpertaionUtility::SignalUpgradeFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 10, Q_NULLPTR);
}

// SIGNAL 11
void HIDOpertaionUtility::SignalUpgradeValue(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void HIDOpertaionUtility::SignalUpgradeError(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void HIDOpertaionUtility::SignalErrInfo(EnumTypeErr _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void HIDOpertaionUtility::SignalReceiveDevSerialNumber(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void HIDOpertaionUtility::SignalMotorLocation()
{
    QMetaObject::activate(this, &staticMetaObject, 15, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
