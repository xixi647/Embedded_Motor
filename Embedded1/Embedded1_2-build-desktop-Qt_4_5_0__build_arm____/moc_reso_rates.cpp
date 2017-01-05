/****************************************************************************
** Meta object code from reading C++ file 'reso_rates.h'
**
** Created: Wed Apr 13 21:11:05 2016
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Embedded1_2/src/reso_rates.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reso_rates.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Reso_Rates[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_Reso_Rates[] = {
    "Reso_Rates\0"
};

const QMetaObject Reso_Rates::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Reso_Rates,
      qt_meta_data_Reso_Rates, 0 }
};

const QMetaObject *Reso_Rates::metaObject() const
{
    return &staticMetaObject;
}

void *Reso_Rates::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Reso_Rates))
        return static_cast<void*>(const_cast< Reso_Rates*>(this));
    return QObject::qt_metacast(_clname);
}

int Reso_Rates::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
