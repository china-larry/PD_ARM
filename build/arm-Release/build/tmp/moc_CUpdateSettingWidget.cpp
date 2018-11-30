/****************************************************************************
** Meta object code from reading C++ file 'CUpdateSettingWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../SettingPage/CUpdateSettingWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CUpdateSettingWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CUpdateSettingWidget_t {
    QByteArrayData data[10];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CUpdateSettingWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CUpdateSettingWidget_t qt_meta_stringdata_CUpdateSettingWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "CUpdateSettingWidget"
QT_MOC_LITERAL(1, 21, 18), // "_SlotMachineUpdate"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 17), // "_SlotSetSerialNum"
QT_MOC_LITERAL(4, 59, 18), // "_SlotReadSerialNum"
QT_MOC_LITERAL(5, 78, 20), // "SlotReceiveSerialNum"
QT_MOC_LITERAL(6, 99, 12), // "strSerialNum"
QT_MOC_LITERAL(7, 112, 17), // "_SlotSetDevParams"
QT_MOC_LITERAL(8, 130, 18), // "_SlotReadDevParams"
QT_MOC_LITERAL(9, 149, 19) // "_SLotClearTestCount"

    },
    "CUpdateSettingWidget\0_SlotMachineUpdate\0"
    "\0_SlotSetSerialNum\0_SlotReadSerialNum\0"
    "SlotReceiveSerialNum\0strSerialNum\0"
    "_SlotSetDevParams\0_SlotReadDevParams\0"
    "_SLotClearTestCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CUpdateSettingWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    1,   52,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,
       8,    0,   56,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CUpdateSettingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CUpdateSettingWidget *_t = static_cast<CUpdateSettingWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->_SlotMachineUpdate(); break;
        case 1: _t->_SlotSetSerialNum(); break;
        case 2: _t->_SlotReadSerialNum(); break;
        case 3: _t->SlotReceiveSerialNum((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->_SlotSetDevParams(); break;
        case 5: _t->_SlotReadDevParams(); break;
        case 6: _t->_SLotClearTestCount(); break;
        default: ;
        }
    }
}

const QMetaObject CUpdateSettingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CUpdateSettingWidget.data,
      qt_meta_data_CUpdateSettingWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CUpdateSettingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CUpdateSettingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CUpdateSettingWidget.stringdata0))
        return static_cast<void*>(const_cast< CUpdateSettingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CUpdateSettingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
