/****************************************************************************
** Meta object code from reading C++ file 'gui.h'
**
** Created: Thu Dec 17 13:30:55 2015
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Embedded1_2/gui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Gui[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      16,    5,    4,    4, 0x05,
      40,    4,    4,    4, 0x05,
      61,    4,    4,    4, 0x05,
      81,    4,    4,    4, 0x05,
     100,    4,    4,    4, 0x05,
     129,    4,    4,    4, 0x05,
     150,    4,    4,    4, 0x05,
     167,    4,    4,    4, 0x05,
     185,    4,    4,    4, 0x05,
     201,    4,    4,    4, 0x05,
     222,    4,    4,    4, 0x05,
     242,    4,    4,    4, 0x05,
     262,    4,    4,    4, 0x05,
     286,  284,    4,    4, 0x05,
     315,  284,    4,    4, 0x05,
     352,  343,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
     382,  372,    4,    4, 0x08,
     409,    4,    4,    4, 0x08,
     426,  343,    4,    4, 0x08,
     445,    4,    4,    4, 0x08,
     465,    4,    4,    4, 0x08,
     488,    4,    4,    4, 0x08,
     516,  510,    4,    4, 0x08,
     552,    4,    4,    4, 0x08,
     577,    4,    4,    4, 0x08,
     599,    4,    4,    4, 0x08,
     619,    4,    4,    4, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Gui[] = {
    "Gui\0\0MatrixData\0SendMatrixData(double*)\0"
    "StartStraightn_cmd()\0MotorEnterPDO_cmd()\0"
    "MotorExitPDO_cmd()\0MotorSendTargetPos_cmd(int*)\0"
    "MotorEnablePPM_cmd()\0MotorCheck_cmd()\0"
    "MotorBootup_cmd()\0MotorHome_cmd()\0"
    "MotorEnterBlad_cmd()\0MotorExitBlad_cmd()\0"
    "TimerEnterPDO_cmd()\0WorkerEnteManul_cmd()\0"
    "s\0SendToMaster_cmd(QByteArray)\0"
    "SendToState_cmd(QByteArray)\0feedback\0"
    "SendFeedback(uchar)\0datagrams\0"
    "getPendingData(QByteArray)\0SwitchToAction()\0"
    "recFeedBack(uchar)\0on_PPM_EN_clicked()\0"
    "on_Enter_PDO_clicked()\0on_Exit_PDO_clicked()\0"
    "value\0on_Positon_slider_valueChanged(int)\0"
    "on_Motor_Check_clicked()\0on_PDO_test_clicked()\0"
    "on_Bootup_clicked()\0on_Send_UDP_clicked()\0"
};

const QMetaObject Gui::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Gui,
      qt_meta_data_Gui, 0 }
};

const QMetaObject *Gui::metaObject() const
{
    return &staticMetaObject;
}

void *Gui::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Gui))
        return static_cast<void*>(const_cast< Gui*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Gui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SendMatrixData((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 1: StartStraightn_cmd(); break;
        case 2: MotorEnterPDO_cmd(); break;
        case 3: MotorExitPDO_cmd(); break;
        case 4: MotorSendTargetPos_cmd((*reinterpret_cast< int*(*)>(_a[1]))); break;
        case 5: MotorEnablePPM_cmd(); break;
        case 6: MotorCheck_cmd(); break;
        case 7: MotorBootup_cmd(); break;
        case 8: MotorHome_cmd(); break;
        case 9: MotorEnterBlad_cmd(); break;
        case 10: MotorExitBlad_cmd(); break;
        case 11: TimerEnterPDO_cmd(); break;
        case 12: WorkerEnteManul_cmd(); break;
        case 13: SendToMaster_cmd((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 14: SendToState_cmd((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 15: SendFeedback((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 16: getPendingData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 17: SwitchToAction(); break;
        case 18: recFeedBack((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 19: on_PPM_EN_clicked(); break;
        case 20: on_Enter_PDO_clicked(); break;
        case 21: on_Exit_PDO_clicked(); break;
        case 22: on_Positon_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: on_Motor_Check_clicked(); break;
        case 24: on_PDO_test_clicked(); break;
        case 25: on_Bootup_clicked(); break;
        case 26: on_Send_UDP_clicked(); break;
        default: ;
        }
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void Gui::SendMatrixData(double * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Gui::StartStraightn_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Gui::MotorEnterPDO_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Gui::MotorExitPDO_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Gui::MotorSendTargetPos_cmd(int * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Gui::MotorEnablePPM_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void Gui::MotorCheck_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void Gui::MotorBootup_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void Gui::MotorHome_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void Gui::MotorEnterBlad_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void Gui::MotorExitBlad_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void Gui::TimerEnterPDO_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void Gui::WorkerEnteManul_cmd()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}

// SIGNAL 13
void Gui::SendToMaster_cmd(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void Gui::SendToState_cmd(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void Gui::SendFeedback(uchar _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}
QT_END_MOC_NAMESPACE
