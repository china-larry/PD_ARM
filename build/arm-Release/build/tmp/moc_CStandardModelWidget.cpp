/****************************************************************************
** Meta object code from reading C++ file 'CStandardModelWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../CalibrationPage/CStandardModelWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CStandardModelWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CStandardModelWidget_t {
    QByteArrayData data[20];
    char stringdata0[435];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CStandardModelWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CStandardModelWidget_t qt_meta_stringdata_CStandardModelWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "CStandardModelWidget"
QT_MOC_LITERAL(1, 21, 20), // "SignalSetBrightValue"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 15), // "BrightnessValue"
QT_MOC_LITERAL(4, 59, 15), // "brightnessValue"
QT_MOC_LITERAL(5, 75, 23), // "SingalCheckDeriveButton"
QT_MOC_LITERAL(6, 99, 18), // "SlotGetPictureToUI"
QT_MOC_LITERAL(7, 118, 14), // "strPicturePath"
QT_MOC_LITERAL(8, 133, 10), // "QList<int>"
QT_MOC_LITERAL(9, 144, 19), // "iGreenComponuntList"
QT_MOC_LITERAL(10, 164, 23), // "_SlotCheckConfirmButton"
QT_MOC_LITERAL(11, 188, 22), // "_SlotCheckDeriveButton"
QT_MOC_LITERAL(12, 211, 27), // "_SlotNo1LineEditWidgetChage"
QT_MOC_LITERAL(13, 239, 27), // "_SlotNo2LineEditWidgetChage"
QT_MOC_LITERAL(14, 267, 27), // "_SlotNo3LineEditWidgetChage"
QT_MOC_LITERAL(15, 295, 27), // "_SlotNo4LineEditWidgetChage"
QT_MOC_LITERAL(16, 323, 27), // "_SlotNo5LineEditWidgetChage"
QT_MOC_LITERAL(17, 351, 27), // "_SlotNo6LineEditWidgetChage"
QT_MOC_LITERAL(18, 379, 27), // "_SlotNo7LineEditWidgetChage"
QT_MOC_LITERAL(19, 407, 27) // "_SlotNo8LineEditWidgetChage"

    },
    "CStandardModelWidget\0SignalSetBrightValue\0"
    "\0BrightnessValue\0brightnessValue\0"
    "SingalCheckDeriveButton\0SlotGetPictureToUI\0"
    "strPicturePath\0QList<int>\0iGreenComponuntList\0"
    "_SlotCheckConfirmButton\0_SlotCheckDeriveButton\0"
    "_SlotNo1LineEditWidgetChage\0"
    "_SlotNo2LineEditWidgetChage\0"
    "_SlotNo3LineEditWidgetChage\0"
    "_SlotNo4LineEditWidgetChage\0"
    "_SlotNo5LineEditWidgetChage\0"
    "_SlotNo6LineEditWidgetChage\0"
    "_SlotNo7LineEditWidgetChage\0"
    "_SlotNo8LineEditWidgetChage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CStandardModelWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       5,    0,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   83,    2, 0x0a /* Public */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,
      16,    0,   94,    2, 0x08 /* Private */,
      17,    0,   95,    2, 0x08 /* Private */,
      18,    0,   96,    2, 0x08 /* Private */,
      19,    0,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    7,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CStandardModelWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CStandardModelWidget *_t = static_cast<CStandardModelWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalSetBrightValue((*reinterpret_cast< BrightnessValue(*)>(_a[1]))); break;
        case 1: _t->SingalCheckDeriveButton(); break;
        case 2: _t->SlotGetPictureToUI((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QList<int>(*)>(_a[2]))); break;
        case 3: _t->_SlotCheckConfirmButton(); break;
        case 4: _t->_SlotCheckDeriveButton(); break;
        case 5: _t->_SlotNo1LineEditWidgetChage(); break;
        case 6: _t->_SlotNo2LineEditWidgetChage(); break;
        case 7: _t->_SlotNo3LineEditWidgetChage(); break;
        case 8: _t->_SlotNo4LineEditWidgetChage(); break;
        case 9: _t->_SlotNo5LineEditWidgetChage(); break;
        case 10: _t->_SlotNo6LineEditWidgetChage(); break;
        case 11: _t->_SlotNo7LineEditWidgetChage(); break;
        case 12: _t->_SlotNo8LineEditWidgetChage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BrightnessValue >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CStandardModelWidget::*_t)(BrightnessValue );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CStandardModelWidget::SignalSetBrightValue)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CStandardModelWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CStandardModelWidget::SingalCheckDeriveButton)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CStandardModelWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CStandardModelWidget.data,
      qt_meta_data_CStandardModelWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CStandardModelWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CStandardModelWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CStandardModelWidget.stringdata0))
        return static_cast<void*>(const_cast< CStandardModelWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CStandardModelWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CStandardModelWidget::SignalSetBrightValue(BrightnessValue _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CStandardModelWidget::SingalCheckDeriveButton()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
