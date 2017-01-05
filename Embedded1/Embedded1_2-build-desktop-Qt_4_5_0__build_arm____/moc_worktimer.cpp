/****************************************************************************
** Meta object code from reading C++ file 'worktimer.h'
**
** Created: Wed Apr 13 21:11:01 2016
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Embedded1_2/worktimer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'worktimer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WorkTimer[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      31,   10,   10,   10, 0x05,
      50,   10,   10,   10, 0x05,
      79,   10,   10,   10, 0x05,
     100,   10,   10,   10, 0x05,
     117,   10,   10,   10, 0x05,
     137,  135,   10,   10, 0x05,
     166,  135,   10,   10, 0x05,
     203,  194,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     223,   10,   10,   10, 0x0a,
     248,  237,   10,   10, 0x0a,
     270,  237,   10,   10, 0x0a,
     316,  312,  293,   10, 0x0a,
     355,   10,   10,   10, 0x0a,
     375,   10,   10,   10, 0x0a,
     392,   10,   10,   10, 0x0a,
     409,   10,   10,   10, 0x0a,
     426,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WorkTimer[] = {
    "WorkTimer\0\0MotorEnterPDO_cmd()\0"
    "MotorExitPDO_cmd()\0MotorSendTargetPos_cmd(int*)\0"
    "MotorEnablePPM_cmd()\0MotorCheck_cmd()\0"
    "MotorBootup_cmd()\0s\0SendToMaster_cmd(QByteArray)\0"
    "SendToState_cmd(QByteArray)\0Feedback\0"
    "SendFeedback(uchar)\0timerUpdate()\0"
    "MatrixData\0RecUdpMatrix(double*)\0"
    "RecManuelData(double*)\0Matrix<double,7,1>\0"
    "q_c\0CalcMetricPosition(Matrix<double,6,1>)\0"
    "CalcMotorPosition()\0InterpPosition()\0"
    "EnterTELE_STAT()\0EnterManl_STAT()\0"
    "StartStraightn()\0"
};

const QMetaObject WorkTimer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WorkTimer,
      qt_meta_data_WorkTimer, 0 }
};

const QMetaObject *WorkTimer::metaObject() const
{
    return &staticMetaObject;
}

void *WorkTimer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WorkTimer))
        return static_cast<void*>(const_cast< WorkTimer*>(this));
    return QObject::qt_metacast(_clname);
}

int WorkTimer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: MotorEnterPDO_cmd(); break;
        case 1: MotorExitPDO_cmd(); break;
        case 2: MotorSendTargetPos_cmd((*reinterpret_cast< int*(*)>(_a[1]))); break;
        case 3: MotorEnablePPM_cmd(); break;
        case 4: MotorCheck_cmd(); break;
        case 5: MotorBootup_cmd(); break;
        case 6: SendToMaster_cmd((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: SendToState_cmd((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: SendFeedback((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 9: timerUpdate(); break;
        case 10: RecUdpMatrix((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 11: RecManuelData((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 12: { Matrix<double,7,1> _r = CalcMetricPosition((*reinterpret_cast< Matrix<double,6,1>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Matrix<double,7,1>*>(_a[0]) = _r; }  break;
        case 13: CalcMotorPosition(); break;
        case 14: InterpPosition(); break;
        case 15: EnterTELE_STAT(); break;
        case 16: EnterManl_STAT(); break;
        case 17: StartStraightn(); break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void WorkTimer::MotorEnterPDO_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void WorkTimer::MotorExitPDO_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void WorkTimer::MotorSendTargetPos_cmd(int * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WorkTimer::MotorEnablePPM_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void WorkTimer::MotorCheck_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void WorkTimer::MotorBootup_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void WorkTimer::SendToMaster_cmd(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void WorkTimer::SendToState_cmd(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void WorkTimer::SendFeedback(uchar _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
