/****************************************************************************
** Meta object code from reading C++ file 'SimulationMainWindow1D.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Application/SimulationMainWindow1D.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SimulationMainWindow1D.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SimulationMainWindow1D[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
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
     110,   23,   23,   23, 0x08,
     125,   23,   23,   23, 0x08,
     139,   23,   23,   23, 0x08,
     150,   23,   23,   23, 0x08,
     162,   23,   23,   23, 0x08,
     178,   23,   23,   23, 0x08,
     193,   23,   23,   23, 0x08,
     215,   23,   23,   23, 0x08,
     239,   23,   23,   23, 0x08,
     264,   23,   23,   23, 0x08,
     294,   23,   23,   23, 0x08,
     327,   23,   23,   23, 0x08,
     365,   23,   23,   23, 0x08,
     383,   23,   23,   23, 0x08,
     415,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SimulationMainWindow1D[] = {
    "SimulationMainWindow1D\0\0about()\0"
    "aboutQt()\0runSimulation()\0pauseSimulation()\0"
    "restartSimulation()\0setGridSize()\0"
    "setTolerance()\0setDelaySec()\0setICSin()\0"
    "setICStep()\0setICRndNoise()\0setRK4Scheme()\0"
    "setMacCormackScheme()\0setForwardEulerScheme()\0"
    "setLaxFriedrichsScheme()\0"
    "setKurganovTadmor2000Scheme()\0"
    "setRK4KurganovTadmor2000Scheme()\0"
    "setKurganovTadmor2ndOrder2000Scheme()\0"
    "setMUSCLSScheme()\0setLinearReconstructionScheme()\0"
    "setPiecewiseParabolicReconstructionScheme()\0"
};

void SimulationMainWindow1D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SimulationMainWindow1D *_t = static_cast<SimulationMainWindow1D *>(_o);
        switch (_id) {
        case 0: _t->about(); break;
        case 1: _t->aboutQt(); break;
        case 2: _t->runSimulation(); break;
        case 3: _t->pauseSimulation(); break;
        case 4: _t->restartSimulation(); break;
        case 5: _t->setGridSize(); break;
        case 6: _t->setTolerance(); break;
        case 7: _t->setDelaySec(); break;
        case 8: _t->setICSin(); break;
        case 9: _t->setICStep(); break;
        case 10: _t->setICRndNoise(); break;
        case 11: _t->setRK4Scheme(); break;
        case 12: _t->setMacCormackScheme(); break;
        case 13: _t->setForwardEulerScheme(); break;
        case 14: _t->setLaxFriedrichsScheme(); break;
        case 15: _t->setKurganovTadmor2000Scheme(); break;
        case 16: _t->setRK4KurganovTadmor2000Scheme(); break;
        case 17: _t->setKurganovTadmor2ndOrder2000Scheme(); break;
        case 18: _t->setMUSCLSScheme(); break;
        case 19: _t->setLinearReconstructionScheme(); break;
        case 20: _t->setPiecewiseParabolicReconstructionScheme(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SimulationMainWindow1D::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SimulationMainWindow1D::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SimulationMainWindow1D,
      qt_meta_data_SimulationMainWindow1D, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SimulationMainWindow1D::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SimulationMainWindow1D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SimulationMainWindow1D::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimulationMainWindow1D))
        return static_cast<void*>(const_cast< SimulationMainWindow1D*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SimulationMainWindow1D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
