/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[309];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "SlotReceiveLogin"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "iUserPower"
QT_MOC_LITERAL(4, 40, 11), // "strUserName"
QT_MOC_LITERAL(5, 52, 25), // "SlotDetectorPageStartTest"
QT_MOC_LITERAL(6, 78, 14), // "iTestDelayTime"
QT_MOC_LITERAL(7, 93, 15), // "SlotStartQRCode"
QT_MOC_LITERAL(8, 109, 18), // "SlotHaveQRCodeInfo"
QT_MOC_LITERAL(9, 128, 13), // "iProgramCount"
QT_MOC_LITERAL(10, 142, 10), // "iDelayTime"
QT_MOC_LITERAL(11, 153, 20), // "SlotTestProgramIndex"
QT_MOC_LITERAL(12, 174, 13), // "iProgramIndex"
QT_MOC_LITERAL(13, 188, 24), // "SlotDetectorPageStopTest"
QT_MOC_LITERAL(14, 213, 23), // "SlotDetectorPageEndTest"
QT_MOC_LITERAL(15, 237, 19), // "SlotConfirmTestMode"
QT_MOC_LITERAL(16, 257, 19), // "SlotAutoConnectPoct"
QT_MOC_LITERAL(17, 277, 5), // "bAuto"
QT_MOC_LITERAL(18, 283, 18), // "_SlotTabPageChange"
QT_MOC_LITERAL(19, 302, 6) // "iIndex"

    },
    "MainWindow\0SlotReceiveLogin\0\0iUserPower\0"
    "strUserName\0SlotDetectorPageStartTest\0"
    "iTestDelayTime\0SlotStartQRCode\0"
    "SlotHaveQRCodeInfo\0iProgramCount\0"
    "iDelayTime\0SlotTestProgramIndex\0"
    "iProgramIndex\0SlotDetectorPageStopTest\0"
    "SlotDetectorPageEndTest\0SlotConfirmTestMode\0"
    "SlotAutoConnectPoct\0bAuto\0_SlotTabPageChange\0"
    "iIndex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

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
       1,    2,   64,    2, 0x0a /* Public */,
       5,    1,   69,    2, 0x0a /* Public */,
       7,    0,   72,    2, 0x0a /* Public */,
       8,    2,   73,    2, 0x0a /* Public */,
      11,    1,   78,    2, 0x0a /* Public */,
      13,    0,   81,    2, 0x0a /* Public */,
      14,    0,   82,    2, 0x0a /* Public */,
      15,    1,   83,    2, 0x0a /* Public */,
      16,    1,   86,    2, 0x0a /* Public */,
      18,    1,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, QMetaType::Int,   19,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SlotReceiveLogin((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->SlotDetectorPageStartTest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SlotStartQRCode(); break;
        case 3: _t->SlotHaveQRCodeInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->SlotTestProgramIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SlotDetectorPageStopTest(); break;
        case 6: _t->SlotDetectorPageEndTest(); break;
        case 7: _t->SlotConfirmTestMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->SlotAutoConnectPoct((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->_SlotTabPageChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
