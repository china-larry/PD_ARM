/****************************************************************************
** Meta object code from reading C++ file 'CDetectorPage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../DetectorPage/CDetectorPage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CDetectorPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CDetectorPage_t {
    QByteArrayData data[41];
    char stringdata0[689];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CDetectorPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CDetectorPage_t qt_meta_stringdata_CDetectorPage = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CDetectorPage"
QT_MOC_LITERAL(1, 14, 15), // "SignalStartTest"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14), // "iTestDelayTime"
QT_MOC_LITERAL(4, 46, 17), // "SignalStartQRCode"
QT_MOC_LITERAL(5, 64, 20), // "SignalHaveQRCodeInfo"
QT_MOC_LITERAL(6, 85, 13), // "iProgramCount"
QT_MOC_LITERAL(7, 99, 22), // "SignalTestProgramIndex"
QT_MOC_LITERAL(8, 122, 13), // "iProgramIndex"
QT_MOC_LITERAL(9, 136, 13), // "SignalEndTest"
QT_MOC_LITERAL(10, 150, 14), // "SignalStopTest"
QT_MOC_LITERAL(11, 165, 15), // "SlotStartQRCode"
QT_MOC_LITERAL(12, 181, 22), // "SlotReceiveQRCodeImage"
QT_MOC_LITERAL(13, 204, 12), // "strImagePath"
QT_MOC_LITERAL(14, 217, 21), // "SlotReceiveQRCodeInfo"
QT_MOC_LITERAL(15, 239, 10), // "QRCodeInfo"
QT_MOC_LITERAL(16, 250, 17), // "sQRCodeInfoStruct"
QT_MOC_LITERAL(17, 268, 25), // "SlotReceiveTestResultData"
QT_MOC_LITERAL(18, 294, 14), // "TestResultData"
QT_MOC_LITERAL(19, 309, 21), // "sTestResultDataStruct"
QT_MOC_LITERAL(20, 331, 24), // "SlotReceiveSCupImagePath"
QT_MOC_LITERAL(21, 356, 11), // "SlotEndTest"
QT_MOC_LITERAL(22, 368, 20), // "SlotReceiveTestError"
QT_MOC_LITERAL(23, 389, 8), // "ENUM_ERR"
QT_MOC_LITERAL(24, 398, 10), // "eTestError"
QT_MOC_LITERAL(25, 409, 15), // "SlotFuseImageOK"
QT_MOC_LITERAL(26, 425, 17), // "SlotDeleteImageOK"
QT_MOC_LITERAL(27, 443, 13), // "SlotStopBegin"
QT_MOC_LITERAL(28, 457, 11), // "SlotStopEnd"
QT_MOC_LITERAL(29, 469, 22), // "SlotReceiveProjectName"
QT_MOC_LITERAL(30, 492, 10), // "strCupType"
QT_MOC_LITERAL(31, 503, 14), // "strProjectName"
QT_MOC_LITERAL(32, 518, 24), // "_SlotOpenDonorDetailsDlg"
QT_MOC_LITERAL(33, 543, 26), // "_SlotOpenProduceDetailsDlg"
QT_MOC_LITERAL(34, 570, 24), // "_SlotCheckReadTestDevice"
QT_MOC_LITERAL(35, 595, 13), // "_SlotStopTest"
QT_MOC_LITERAL(36, 609, 14), // "_SlotClearData"
QT_MOC_LITERAL(37, 624, 22), // "_SlotOtherReasonChange"
QT_MOC_LITERAL(38, 647, 6), // "iIndex"
QT_MOC_LITERAL(39, 654, 15), // "_SlotPrintToPDF"
QT_MOC_LITERAL(40, 670, 18) // "_SlotManualSetData"

    },
    "CDetectorPage\0SignalStartTest\0\0"
    "iTestDelayTime\0SignalStartQRCode\0"
    "SignalHaveQRCodeInfo\0iProgramCount\0"
    "SignalTestProgramIndex\0iProgramIndex\0"
    "SignalEndTest\0SignalStopTest\0"
    "SlotStartQRCode\0SlotReceiveQRCodeImage\0"
    "strImagePath\0SlotReceiveQRCodeInfo\0"
    "QRCodeInfo\0sQRCodeInfoStruct\0"
    "SlotReceiveTestResultData\0TestResultData\0"
    "sTestResultDataStruct\0SlotReceiveSCupImagePath\0"
    "SlotEndTest\0SlotReceiveTestError\0"
    "ENUM_ERR\0eTestError\0SlotFuseImageOK\0"
    "SlotDeleteImageOK\0SlotStopBegin\0"
    "SlotStopEnd\0SlotReceiveProjectName\0"
    "strCupType\0strProjectName\0"
    "_SlotOpenDonorDetailsDlg\0"
    "_SlotOpenProduceDetailsDlg\0"
    "_SlotCheckReadTestDevice\0_SlotStopTest\0"
    "_SlotClearData\0_SlotOtherReasonChange\0"
    "iIndex\0_SlotPrintToPDF\0_SlotManualSetData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CDetectorPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  144,    2, 0x06 /* Public */,
       4,    0,  147,    2, 0x06 /* Public */,
       5,    2,  148,    2, 0x06 /* Public */,
       7,    1,  153,    2, 0x06 /* Public */,
       9,    0,  156,    2, 0x06 /* Public */,
      10,    0,  157,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,  158,    2, 0x0a /* Public */,
      12,    1,  159,    2, 0x0a /* Public */,
      14,    1,  162,    2, 0x0a /* Public */,
      17,    1,  165,    2, 0x0a /* Public */,
      20,    1,  168,    2, 0x0a /* Public */,
      21,    0,  171,    2, 0x0a /* Public */,
      22,    1,  172,    2, 0x0a /* Public */,
      25,    0,  175,    2, 0x0a /* Public */,
      26,    0,  176,    2, 0x0a /* Public */,
      27,    0,  177,    2, 0x0a /* Public */,
      28,    0,  178,    2, 0x0a /* Public */,
      29,    2,  179,    2, 0x0a /* Public */,
      32,    0,  184,    2, 0x08 /* Private */,
      33,    0,  185,    2, 0x08 /* Private */,
      34,    0,  186,    2, 0x08 /* Private */,
      35,    0,  187,    2, 0x08 /* Private */,
      36,    0,  188,    2, 0x08 /* Private */,
      37,    1,  189,    2, 0x08 /* Private */,
      39,    0,  192,    2, 0x08 /* Private */,
      40,    0,  193,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    3,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   30,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CDetectorPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CDetectorPage *_t = static_cast<CDetectorPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalStartTest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SignalStartQRCode(); break;
        case 2: _t->SignalHaveQRCodeInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->SignalTestProgramIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SignalEndTest(); break;
        case 5: _t->SignalStopTest(); break;
        case 6: _t->SlotStartQRCode(); break;
        case 7: _t->SlotReceiveQRCodeImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->SlotReceiveQRCodeInfo((*reinterpret_cast< QRCodeInfo(*)>(_a[1]))); break;
        case 9: _t->SlotReceiveTestResultData((*reinterpret_cast< TestResultData(*)>(_a[1]))); break;
        case 10: _t->SlotReceiveSCupImagePath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->SlotEndTest(); break;
        case 12: _t->SlotReceiveTestError((*reinterpret_cast< ENUM_ERR(*)>(_a[1]))); break;
        case 13: _t->SlotFuseImageOK(); break;
        case 14: _t->SlotDeleteImageOK(); break;
        case 15: _t->SlotStopBegin(); break;
        case 16: _t->SlotStopEnd(); break;
        case 17: _t->SlotReceiveProjectName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 18: _t->_SlotOpenDonorDetailsDlg(); break;
        case 19: _t->_SlotOpenProduceDetailsDlg(); break;
        case 20: _t->_SlotCheckReadTestDevice(); break;
        case 21: _t->_SlotStopTest(); break;
        case 22: _t->_SlotClearData(); break;
        case 23: _t->_SlotOtherReasonChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->_SlotPrintToPDF(); break;
        case 25: _t->_SlotManualSetData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CDetectorPage::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDetectorPage::SignalStartTest)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CDetectorPage::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDetectorPage::SignalStartQRCode)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CDetectorPage::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDetectorPage::SignalHaveQRCodeInfo)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CDetectorPage::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDetectorPage::SignalTestProgramIndex)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (CDetectorPage::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDetectorPage::SignalEndTest)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (CDetectorPage::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDetectorPage::SignalStopTest)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject CDetectorPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CDetectorPage.data,
      qt_meta_data_CDetectorPage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CDetectorPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CDetectorPage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CDetectorPage.stringdata0))
        return static_cast<void*>(const_cast< CDetectorPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int CDetectorPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void CDetectorPage::SignalStartTest(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CDetectorPage::SignalStartQRCode()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void CDetectorPage::SignalHaveQRCodeInfo(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CDetectorPage::SignalTestProgramIndex(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CDetectorPage::SignalEndTest()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void CDetectorPage::SignalStopTest()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
