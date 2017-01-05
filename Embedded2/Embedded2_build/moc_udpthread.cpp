/****************************************************************************
** Meta object code from reading C++ file 'udpthread.h'
**
** Created: Tue Sep 22 16:09:16 2015
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Embedded1_2/udpthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_udpthread[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      13,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   10,   10,   10, 0x08,
      59,   11,   10,   10, 0x0a,
      85,   11,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_udpthread[] = {
    "udpthread\0\0s\0sendReceiveData(QByteArray)\0"
    "readPendingData()\0getMasterData(QByteArray)\0"
    "getStateData(QByteArray)\0"
};

const QMetaObject udpthread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_udpthread,
      qt_meta_data_udpthread, 0 }
};

const QMetaObject *udpthread::metaObject() const
{
    return &staticMetaObject;
}

void *udpthread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_udpthread))
        return static_cast<void*>(const_cast< udpthread*>(this));
    return QObject::qt_metacast(_clname);
}

int udpthread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendReceiveData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: readPendingData(); break;
        case 2: getMasterData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: getStateData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void udpthread::sendReceiveData(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
