/****************************************************************************
** Meta object code from reading C++ file 'CHistoryPage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../HistoryPage/CHistoryPage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CHistoryPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CHistoryPage_t {
    QByteArrayData data[18];
    char stringdata0[288];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CHistoryPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CHistoryPage_t qt_meta_stringdata_CHistoryPage = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CHistoryPage"
QT_MOC_LITERAL(1, 13, 15), // "_SlotCheckQuery"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 19), // "_SlotCheckSelectAll"
QT_MOC_LITERAL(4, 50, 21), // "_SlotCheckDeselectAll"
QT_MOC_LITERAL(5, 72, 16), // "_SlotCheckDelete"
QT_MOC_LITERAL(6, 89, 16), // "_SlotCheckExport"
QT_MOC_LITERAL(7, 106, 15), // "_SlotCheckPrint"
QT_MOC_LITERAL(8, 122, 14), // "_SlotCheckPoct"
QT_MOC_LITERAL(9, 137, 28), // "_SlotHistoryDataSelectChange"
QT_MOC_LITERAL(10, 166, 11), // "iCurrentRow"
QT_MOC_LITERAL(11, 178, 14), // "iCurrentColumn"
QT_MOC_LITERAL(12, 193, 12), // "iPreviousRow"
QT_MOC_LITERAL(13, 206, 15), // "iPreviousColumn"
QT_MOC_LITERAL(14, 222, 21), // "_SlotPisConnectStates"
QT_MOC_LITERAL(15, 244, 9), // "isConnect"
QT_MOC_LITERAL(16, 254, 18), // "_SlotPisReviceDate"
QT_MOC_LITERAL(17, 273, 14) // "qByteArrayData"

    },
    "CHistoryPage\0_SlotCheckQuery\0\0"
    "_SlotCheckSelectAll\0_SlotCheckDeselectAll\0"
    "_SlotCheckDelete\0_SlotCheckExport\0"
    "_SlotCheckPrint\0_SlotCheckPoct\0"
    "_SlotHistoryDataSelectChange\0iCurrentRow\0"
    "iCurrentColumn\0iPreviousRow\0iPreviousColumn\0"
    "_SlotPisConnectStates\0isConnect\0"
    "_SlotPisReviceDate\0qByteArrayData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CHistoryPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    4,   71,    2, 0x08 /* Private */,
      14,    1,   80,    2, 0x08 /* Private */,
      16,    1,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   11,   12,   13,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::QByteArray,   17,

       0        // eod
};

void CHistoryPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CHistoryPage *_t = static_cast<CHistoryPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->_SlotCheckQuery(); break;
        case 1: _t->_SlotCheckSelectAll(); break;
        case 2: _t->_SlotCheckDeselectAll(); break;
        case 3: _t->_SlotCheckDelete(); break;
        case 4: _t->_SlotCheckExport(); break;
        case 5: _t->_SlotCheckPrint(); break;
        case 6: _t->_SlotCheckPoct(); break;
        case 7: _t->_SlotHistoryDataSelectChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 8: _t->_SlotPisConnectStates((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->_SlotPisReviceDate((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CHistoryPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CHistoryPage.data,
      qt_meta_data_CHistoryPage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CHistoryPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CHistoryPage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CHistoryPage.stringdata0))
        return static_cast<void*>(const_cast< CHistoryPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int CHistoryPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
