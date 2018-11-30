/****************************************************************************
** Meta object code from reading C++ file 'CAccountManagementWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../SettingPage/CAccountManagementWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CAccountManagementWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CAccountManagementWidget_t {
    QByteArrayData data[11];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CAccountManagementWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CAccountManagementWidget_t qt_meta_stringdata_CAccountManagementWidget = {
    {
QT_MOC_LITERAL(0, 0, 24), // "CAccountManagementWidget"
QT_MOC_LITERAL(1, 25, 17), // "SlotAddUserWidget"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 11), // "strUserName"
QT_MOC_LITERAL(4, 56, 11), // "strPassWord"
QT_MOC_LITERAL(5, 68, 20), // "SlotDeleteUserWidget"
QT_MOC_LITERAL(6, 89, 20), // "SlotModifyUserWidget"
QT_MOC_LITERAL(7, 110, 3), // "iID"
QT_MOC_LITERAL(8, 114, 12), // "_SlotAddUser"
QT_MOC_LITERAL(9, 127, 15), // "_SlotDeleteUser"
QT_MOC_LITERAL(10, 143, 15) // "_SlotModifyUser"

    },
    "CAccountManagementWidget\0SlotAddUserWidget\0"
    "\0strUserName\0strPassWord\0SlotDeleteUserWidget\0"
    "SlotModifyUserWidget\0iID\0_SlotAddUser\0"
    "_SlotDeleteUser\0_SlotModifyUser"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CAccountManagementWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x0a /* Public */,
       5,    0,   49,    2, 0x0a /* Public */,
       6,    2,   50,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x08 /* Private */,
       9,    0,   56,    2, 0x08 /* Private */,
      10,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    7,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CAccountManagementWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CAccountManagementWidget *_t = static_cast<CAccountManagementWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SlotAddUserWidget((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->SlotDeleteUserWidget(); break;
        case 2: _t->SlotModifyUserWidget((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->_SlotAddUser(); break;
        case 4: _t->_SlotDeleteUser(); break;
        case 5: _t->_SlotModifyUser(); break;
        default: ;
        }
    }
}

const QMetaObject CAccountManagementWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CAccountManagementWidget.data,
      qt_meta_data_CAccountManagementWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CAccountManagementWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CAccountManagementWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CAccountManagementWidget.stringdata0))
        return static_cast<void*>(const_cast< CAccountManagementWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CAccountManagementWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
struct qt_meta_stringdata_CUserAddWidget_t {
    QByteArrayData data[7];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CUserAddWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CUserAddWidget_t qt_meta_stringdata_CUserAddWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CUserAddWidget"
QT_MOC_LITERAL(1, 15, 13), // "SignalAddUser"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11), // "strUserName"
QT_MOC_LITERAL(4, 42, 11), // "strPassWord"
QT_MOC_LITERAL(5, 54, 18), // "_SlotCheckOkButton"
QT_MOC_LITERAL(6, 73, 22) // "_SlotCheckCancleButton"

    },
    "CUserAddWidget\0SignalAddUser\0\0strUserName\0"
    "strPassWord\0_SlotCheckOkButton\0"
    "_SlotCheckCancleButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CUserAddWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   34,    2, 0x08 /* Private */,
       6,    0,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CUserAddWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CUserAddWidget *_t = static_cast<CUserAddWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalAddUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->_SlotCheckOkButton(); break;
        case 2: _t->_SlotCheckCancleButton(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CUserAddWidget::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CUserAddWidget::SignalAddUser)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CUserAddWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CUserAddWidget.data,
      qt_meta_data_CUserAddWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CUserAddWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CUserAddWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CUserAddWidget.stringdata0))
        return static_cast<void*>(const_cast< CUserAddWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CUserAddWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CUserAddWidget::SignalAddUser(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_CUserModifyWidget_t {
    QByteArrayData data[7];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CUserModifyWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CUserModifyWidget_t qt_meta_stringdata_CUserModifyWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CUserModifyWidget"
QT_MOC_LITERAL(1, 18, 16), // "SignalModifyUser"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 3), // "iID"
QT_MOC_LITERAL(4, 40, 11), // "strPassWord"
QT_MOC_LITERAL(5, 52, 18), // "_SlotCheckOkButton"
QT_MOC_LITERAL(6, 71, 22) // "_SlotCheckCancleButton"

    },
    "CUserModifyWidget\0SignalModifyUser\0\0"
    "iID\0strPassWord\0_SlotCheckOkButton\0"
    "_SlotCheckCancleButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CUserModifyWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   34,    2, 0x08 /* Private */,
       6,    0,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CUserModifyWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CUserModifyWidget *_t = static_cast<CUserModifyWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalModifyUser((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->_SlotCheckOkButton(); break;
        case 2: _t->_SlotCheckCancleButton(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CUserModifyWidget::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CUserModifyWidget::SignalModifyUser)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CUserModifyWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CUserModifyWidget.data,
      qt_meta_data_CUserModifyWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CUserModifyWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CUserModifyWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CUserModifyWidget.stringdata0))
        return static_cast<void*>(const_cast< CUserModifyWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CUserModifyWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CUserModifyWidget::SignalModifyUser(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_CUserDeleteWidget_t {
    QByteArrayData data[5];
    char stringdata0[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CUserDeleteWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CUserDeleteWidget_t qt_meta_stringdata_CUserDeleteWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CUserDeleteWidget"
QT_MOC_LITERAL(1, 18, 16), // "SignalDeleteUser"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 18), // "_SlotCheckOkButton"
QT_MOC_LITERAL(4, 55, 22) // "_SlotCheckCancleButton"

    },
    "CUserDeleteWidget\0SignalDeleteUser\0\0"
    "_SlotCheckOkButton\0_SlotCheckCancleButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CUserDeleteWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CUserDeleteWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CUserDeleteWidget *_t = static_cast<CUserDeleteWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalDeleteUser(); break;
        case 1: _t->_SlotCheckOkButton(); break;
        case 2: _t->_SlotCheckCancleButton(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CUserDeleteWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CUserDeleteWidget::SignalDeleteUser)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CUserDeleteWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CUserDeleteWidget.data,
      qt_meta_data_CUserDeleteWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CUserDeleteWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CUserDeleteWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CUserDeleteWidget.stringdata0))
        return static_cast<void*>(const_cast< CUserDeleteWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CUserDeleteWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CUserDeleteWidget::SignalDeleteUser()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
