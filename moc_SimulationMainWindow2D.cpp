/****************************************************************************
** Meta object code from reading C++ file 'SimulationMainWindow2D.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Application/SimulationMainWindow2D.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SimulationMainWindow2D.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SimulationMainWindow2D[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      32,   23,   23,   23, 0x08,
      42,   23,   23,   23, 0x08,
      58,   23,   23,   23, 0x08,
      76,   23,   23,   23, 0x08,
      96,   23,   23,   23, 0x08,
     111,   23,   23,   23, 0x08,
     125,   23,   23,   23, 0x08,
     140,   23,   23,   23, 0x08,
     164,   23,   23,   23, 0x08,
     189,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SimulationMainWindow2D[] = {
    "SimulationMainWindow2D\0\0about()\0"
    "aboutQt()\0runSimulation()\0pauseSimulation()\0"
    "restartSimulation()\0setTolerance()\0"
    "setDelaySec()\0setRK4Scheme()\0"
    "setForwardEulerScheme()\0"
    "setLaxFriedrichsScheme()\0"
    "setLinearReconstructionScheme()\0"
};

void SimulationMainWindow2D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SimulationMainWindow2D *_t = static_cast<SimulationMainWindow2D *>(_o);
        switch (_id) {
        case 0: _t->about(); break;
        case 1: _t->aboutQt(); break;
        case 2: _t->runSimulation(); break;
        case 3: _t->pauseSimulation(); break;
        case 4: _t->restartSimulation(); break;
        case 5: _t->setTolerance(); break;
        case 6: _t->setDelaySec(); break;
        case 7: _t->setRK4Scheme(); break;
        case 8: _t->setForwardEulerScheme(); break;
        case 9: _t->setLaxFriedrichsScheme(); break;
        case 10: _t->setLinearReconstructionScheme(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SimulationMainWindow2D::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SimulationMainWindow2D::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SimulationMainWindow2D,
      qt_meta_data_SimulationMainWindow2D, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SimulationMainWindow2D::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SimulationMainWindow2D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SimulationMainWindow2D::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimulationMainWindow2D))
        return static_cast<void*>(const_cast< SimulationMainWindow2D*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SimulationMainWindow2D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
