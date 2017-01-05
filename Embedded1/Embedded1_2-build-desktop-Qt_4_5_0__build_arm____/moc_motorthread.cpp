/****************************************************************************
** Meta object code from reading C++ file 'motorthread.h'
**
** Created: Wed Apr 13 21:11:03 2016
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Embedded1_2/motorthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'motorthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MotorThread[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      22,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   12,   12,   12, 0x0a,
      65,   56,   12,   12, 0x0a,
      84,   12,   12,   12, 0x0a,
     100,   12,   12,   12, 0x0a,
     115,   12,   12,   12, 0x0a,
     129,   12,   12,   12, 0x0a,
     141,   12,   12,   12, 0x0a,
     155,   12,   12,   12, 0x0a,
     172,   12,   12,   12, 0x0a,
     188,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MotorThread[] = {
    "MotorThread\0\0Feedback\0SendFeedback(uchar)\0"
    "MotorsCheck()\0Position\0Rec_PosValue(int*)\0"
    "MotorEnterPDO()\0MotorExitPDO()\0"
    "MotorPPM_EN()\0MotorHome()\0MotorBootup()\0"
    "MotorEnterBlad()\0MotorExitBlad()\0"
    "HomeTimeout()\0"
};

const QMetaObject MotorThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MotorThread,
      qt_meta_data_MotorThread, 0 }
};

const QMetaObject *MotorThread::metaObject() const
{
    return &staticMetaObject;
}

void *MotorThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MotorThread))
        return static_cast<void*>(const_cast< MotorThread*>(this));
    return QObject::qt_metacast(_clname);
}

int MotorThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SendFeedback((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 1: MotorsCheck(); break;
        case 2: Rec_PosValue((*reinterpret_cast< int*(*)>(_a[1]))); break;
        case 3: MotorEnterPDO(); break;
        case 4: MotorExitPDO(); break;
        case 5: MotorPPM_EN(); break;
        case 6: MotorHome(); break;
        case 7: MotorBootup(); break;
        case 8: MotorEnterBlad(); break;
        case 9: MotorExitBlad(); break;
        case 10: HomeTimeout(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MotorThread::SendFeedback(uchar _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
