/****************************************************************************
** Meta object code from reading C++ file 'CSettingSetupWindowWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../SettingPage/CSettingSetupWindowWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CSettingSetupWindowWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CSettingSetupWindowWidget_t {
    QByteArrayData data[18];
    char stringdata0[321];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CSettingSetupWindowWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CSettingSetupWindowWidget_t qt_meta_stringdata_CSettingSetupWindowWidget = {
    {
QT_MOC_LITERAL(0, 0, 25), // "CSettingSetupWindowWidget"
QT_MOC_LITERAL(1, 26, 25), // "SignalReadFirmwareVersion"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 19), // "SignalReadUserTimes"
QT_MOC_LITERAL(4, 73, 19), // "SignalAutoConnetPis"
QT_MOC_LITERAL(5, 93, 5), // "bAuto"
QT_MOC_LITERAL(6, 99, 20), // "SignalAutoConnetPoct"
QT_MOC_LITERAL(7, 120, 22), // "SlotGetFirmwareVersion"
QT_MOC_LITERAL(8, 143, 16), // "SlotGetUserTimes"
QT_MOC_LITERAL(9, 160, 9), // "showEvent"
QT_MOC_LITERAL(10, 170, 11), // "QShowEvent*"
QT_MOC_LITERAL(11, 182, 19), // "_PoctIP01TextChange"
QT_MOC_LITERAL(12, 202, 19), // "_PoctIP02TextChange"
QT_MOC_LITERAL(13, 222, 19), // "_PoctIP03TextChange"
QT_MOC_LITERAL(14, 242, 19), // "_PoctIP04TextChange"
QT_MOC_LITERAL(15, 262, 32), // "_SlotPoctServerPortLineEditChage"
QT_MOC_LITERAL(16, 295, 13), // "_SlotOKButton"
QT_MOC_LITERAL(17, 309, 11) // "_SlotCancel"

    },
    "CSettingSetupWindowWidget\0"
    "SignalReadFirmwareVersion\0\0"
    "SignalReadUserTimes\0SignalAutoConnetPis\0"
    "bAuto\0SignalAutoConnetPoct\0"
    "SlotGetFirmwareVersion\0SlotGetUserTimes\0"
    "showEvent\0QShowEvent*\0_PoctIP01TextChange\0"
    "_PoctIP02TextChange\0_PoctIP03TextChange\0"
    "_PoctIP04TextChange\0"
    "_SlotPoctServerPortLineEditChage\0"
    "_SlotOKButton\0_SlotCancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CSettingSetupWindowWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    1,   86,    2, 0x06 /* Public */,
       6,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   92,    2, 0x0a /* Public */,
       8,    1,   95,    2, 0x0a /* Public */,
       9,    1,   98,    2, 0x09 /* Protected */,
      11,    0,  101,    2, 0x08 /* Private */,
      12,    0,  102,    2, 0x08 /* Private */,
      13,    0,  103,    2, 0x08 /* Private */,
      14,    0,  104,    2, 0x08 /* Private */,
      15,    0,  105,    2, 0x08 /* Private */,
      16,    0,  106,    2, 0x08 /* Private */,
      17,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CSettingSetupWindowWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CSettingSetupWindowWidget *_t = static_cast<CSettingSetupWindowWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalReadFirmwareVersion(); break;
        case 1: _t->SignalReadUserTimes(); break;
        case 2: _t->SignalAutoConnetPis((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->SignalAutoConnetPoct((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->SlotGetFirmwareVersion((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->SlotGetUserTimes((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        case 7: _t->_PoctIP01TextChange(); break;
        case 8: _t->_PoctIP02TextChange(); break;
        case 9: _t->_PoctIP03TextChange(); break;
        case 10: _t->_PoctIP04TextChange(); break;
        case 11: _t->_SlotPoctServerPortLineEditChage(); break;
        case 12: _t->_SlotOKButton(); break;
        case 13: _t->_SlotCancel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CSettingSetupWindowWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CSettingSetupWindowWidget::SignalReadFirmwareVersion)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CSettingSetupWindowWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CSettingSetupWindowWidget::SignalReadUserTimes)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CSettingSetupWindowWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CSettingSetupWindowWidget::SignalAutoConnetPis)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CSettingSetupWindowWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CSettingSetupWindowWidget::SignalAutoConnetPoct)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject CSettingSetupWindowWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CSettingSetupWindowWidget.data,
      qt_meta_data_CSettingSetupWindowWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CSettingSetupWindowWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CSettingSetupWindowWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CSettingSetupWindowWidget.stringdata0))
        return static_cast<void*>(const_cast< CSettingSetupWindowWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CSettingSetupWindowWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void CSettingSetupWindowWidget::SignalReadFirmwareVersion()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void CSettingSetupWindowWidget::SignalReadUserTimes()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void CSettingSetupWindowWidget::SignalAutoConnetPis(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CSettingSetupWindowWidget::SignalAutoConnetPoct(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
