/****************************************************************************
** Meta object code from reading C++ file 'MotorLocationCalibration.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../AdjustLight/MotorLocationCalibration.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MotorLocationCalibration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MotorLocationCalibration_t {
    QByteArrayData data[12];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MotorLocationCalibration_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MotorLocationCalibration_t qt_meta_stringdata_MotorLocationCalibration = {
    {
QT_MOC_LITERAL(0, 0, 24), // "MotorLocationCalibration"
QT_MOC_LITERAL(1, 25, 18), // "_SlotPreviewBotton"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 15), // "_SlotStopBotton"
QT_MOC_LITERAL(4, 61, 11), // "_SlotResect"
QT_MOC_LITERAL(5, 73, 24), // "_SlotAntiClockwiseButton"
QT_MOC_LITERAL(6, 98, 20), // "_SlotClockwiseButton"
QT_MOC_LITERAL(7, 119, 15), // "_SlotSaveButton"
QT_MOC_LITERAL(8, 135, 25), // "_SlotMotorLocationSuccess"
QT_MOC_LITERAL(9, 161, 13), // "_SlotOKButton"
QT_MOC_LITERAL(10, 175, 32), // "on_horizontalSlider_valueChanged"
QT_MOC_LITERAL(11, 208, 5) // "value"

    },
    "MotorLocationCalibration\0_SlotPreviewBotton\0"
    "\0_SlotStopBotton\0_SlotResect\0"
    "_SlotAntiClockwiseButton\0_SlotClockwiseButton\0"
    "_SlotSaveButton\0_SlotMotorLocationSuccess\0"
    "_SlotOKButton\0on_horizontalSlider_valueChanged\0"
    "value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MotorLocationCalibration[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    1,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void MotorLocationCalibration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MotorLocationCalibration *_t = static_cast<MotorLocationCalibration *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->_SlotPreviewBotton(); break;
        case 1: _t->_SlotStopBotton(); break;
        case 2: _t->_SlotResect(); break;
        case 3: _t->_SlotAntiClockwiseButton(); break;
        case 4: _t->_SlotClockwiseButton(); break;
        case 5: _t->_SlotSaveButton(); break;
        case 6: _t->_SlotMotorLocationSuccess(); break;
        case 7: _t->_SlotOKButton(); break;
        case 8: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MotorLocationCalibration::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MotorLocationCalibration.data,
      qt_meta_data_MotorLocationCalibration,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MotorLocationCalibration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MotorLocationCalibration::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MotorLocationCalibration.stringdata0))
        return static_cast<void*>(const_cast< MotorLocationCalibration*>(this));
    return QWidget::qt_metacast(_clname);
}

int MotorLocationCalibration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
