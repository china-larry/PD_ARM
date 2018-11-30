/****************************************************************************
** Meta object code from reading C++ file 'COrdinaryModelWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../CalibrationPage/COrdinaryModelWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'COrdinaryModelWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_COrdinaryModelWidget_t {
    QByteArrayData data[18];
    char stringdata0[312];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_COrdinaryModelWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_COrdinaryModelWidget_t qt_meta_stringdata_COrdinaryModelWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "COrdinaryModelWidget"
QT_MOC_LITERAL(1, 21, 18), // "SlotGetImportValue"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 23), // "BrightnessOrdinaryValue"
QT_MOC_LITERAL(4, 65, 22), // "sBrightnessValueStruct"
QT_MOC_LITERAL(5, 88, 23), // "SlotGetCalibrationValue"
QT_MOC_LITERAL(6, 112, 10), // "bIsSeccess"
QT_MOC_LITERAL(7, 123, 16), // "SlotGetReadValue"
QT_MOC_LITERAL(8, 140, 23), // "sBbrightnessValueStruct"
QT_MOC_LITERAL(9, 164, 17), // "SlotGetErrorValue"
QT_MOC_LITERAL(10, 182, 11), // "EnumTypeErr"
QT_MOC_LITERAL(11, 194, 10), // "eTypeError"
QT_MOC_LITERAL(12, 205, 21), // "SlotCalibrationButton"
QT_MOC_LITERAL(13, 227, 23), // "SlotWriteParamsComplete"
QT_MOC_LITERAL(14, 251, 8), // "iCmdType"
QT_MOC_LITERAL(15, 260, 7), // "bResult"
QT_MOC_LITERAL(16, 268, 24), // "SlotSaveDeviceParamsData"
QT_MOC_LITERAL(17, 293, 18) // "SlotProgressFinish"

    },
    "COrdinaryModelWidget\0SlotGetImportValue\0"
    "\0BrightnessOrdinaryValue\0"
    "sBrightnessValueStruct\0SlotGetCalibrationValue\0"
    "bIsSeccess\0SlotGetReadValue\0"
    "sBbrightnessValueStruct\0SlotGetErrorValue\0"
    "EnumTypeErr\0eTypeError\0SlotCalibrationButton\0"
    "SlotWriteParamsComplete\0iCmdType\0"
    "bResult\0SlotSaveDeviceParamsData\0"
    "SlotProgressFinish"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_COrdinaryModelWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       5,    2,   57,    2, 0x0a /* Public */,
       7,    1,   62,    2, 0x0a /* Public */,
       9,    1,   65,    2, 0x0a /* Public */,
      12,    0,   68,    2, 0x0a /* Public */,
      13,    2,   69,    2, 0x0a /* Public */,
      16,    0,   74,    2, 0x0a /* Public */,
      17,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 3,    6,    4,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, QMetaType::Bool,   14,   15,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void COrdinaryModelWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        COrdinaryModelWidget *_t = static_cast<COrdinaryModelWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SlotGetImportValue((*reinterpret_cast< BrightnessOrdinaryValue(*)>(_a[1]))); break;
        case 1: _t->SlotGetCalibrationValue((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< BrightnessOrdinaryValue(*)>(_a[2]))); break;
        case 2: _t->SlotGetReadValue((*reinterpret_cast< BrightnessOrdinaryValue(*)>(_a[1]))); break;
        case 3: _t->SlotGetErrorValue((*reinterpret_cast< EnumTypeErr(*)>(_a[1]))); break;
        case 4: _t->SlotCalibrationButton(); break;
        case 5: _t->SlotWriteParamsComplete((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->SlotSaveDeviceParamsData(); break;
        case 7: _t->SlotProgressFinish(); break;
        default: ;
        }
    }
}

const QMetaObject COrdinaryModelWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_COrdinaryModelWidget.data,
      qt_meta_data_COrdinaryModelWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *COrdinaryModelWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *COrdinaryModelWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_COrdinaryModelWidget.stringdata0))
        return static_cast<void*>(const_cast< COrdinaryModelWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int COrdinaryModelWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
