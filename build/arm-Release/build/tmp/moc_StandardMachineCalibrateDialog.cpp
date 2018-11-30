/****************************************************************************
** Meta object code from reading C++ file 'StandardMachineCalibrateDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../AdjustLight/StandardMachineCalibrateDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StandardMachineCalibrateDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StandardMachineCalibrateDialog_t {
    QByteArrayData data[7];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StandardMachineCalibrateDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StandardMachineCalibrateDialog_t qt_meta_stringdata_StandardMachineCalibrateDialog = {
    {
QT_MOC_LITERAL(0, 0, 30), // "StandardMachineCalibrateDialog"
QT_MOC_LITERAL(1, 31, 12), // "_SlotConfirm"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 14), // "_SlotGetZvalue"
QT_MOC_LITERAL(4, 60, 7), // "dZvalue"
QT_MOC_LITERAL(5, 68, 9), // "_SlotStop"
QT_MOC_LITERAL(6, 78, 26) // "on_ConfirmButton_2_clicked"

    },
    "StandardMachineCalibrateDialog\0"
    "_SlotConfirm\0\0_SlotGetZvalue\0dZvalue\0"
    "_SlotStop\0on_ConfirmButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StandardMachineCalibrateDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    1,   35,    2, 0x08 /* Private */,
       5,    0,   38,    2, 0x08 /* Private */,
       6,    0,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StandardMachineCalibrateDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StandardMachineCalibrateDialog *_t = static_cast<StandardMachineCalibrateDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->_SlotConfirm(); break;
        case 1: _t->_SlotGetZvalue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->_SlotStop(); break;
        case 3: _t->on_ConfirmButton_2_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject StandardMachineCalibrateDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_StandardMachineCalibrateDialog.data,
      qt_meta_data_StandardMachineCalibrateDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StandardMachineCalibrateDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StandardMachineCalibrateDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StandardMachineCalibrateDialog.stringdata0))
        return static_cast<void*>(const_cast< StandardMachineCalibrateDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int StandardMachineCalibrateDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
