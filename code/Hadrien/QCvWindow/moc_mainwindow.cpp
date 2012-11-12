/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Nov 12 10:16:04 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/UI/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      37,   11,   11,   11, 0x08,
      63,   11,   11,   11, 0x08,
      89,   11,   11,   11, 0x08,
     118,   11,   11,   11, 0x08,
     148,   11,   11,   11, 0x08,
     176,   11,   11,   11, 0x08,
     210,   11,   11,   11, 0x08,
     241,   11,   11,   11, 0x08,
     275,   11,   11,   11, 0x08,
     310,  304,   11,   11, 0x08,
     351,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_actionNew_triggered()\0"
    "on_actionOpen_triggered()\0"
    "on_actionSave_triggered()\0"
    "on_actionSave_As_triggered()\0"
    "on_actionAbout_Qt_triggered()\0"
    "on_pushButton_run_clicked()\0"
    "on_pushButton_configure_pressed()\0"
    "on_pushButton_delete_clicked()\0"
    "on_pushButton_deleteAll_clicked()\0"
    "on_pushButton_edit_clicked()\0index\0"
    "on_comboBox_tab_currentIndexChanged(int)\0"
    "on_actionAbout_MDMA_triggered()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_actionNew_triggered(); break;
        case 1: _t->on_actionOpen_triggered(); break;
        case 2: _t->on_actionSave_triggered(); break;
        case 3: _t->on_actionSave_As_triggered(); break;
        case 4: _t->on_actionAbout_Qt_triggered(); break;
        case 5: _t->on_pushButton_run_clicked(); break;
        case 6: _t->on_pushButton_configure_pressed(); break;
        case 7: _t->on_pushButton_delete_clicked(); break;
        case 8: _t->on_pushButton_deleteAll_clicked(); break;
        case 9: _t->on_pushButton_edit_clicked(); break;
        case 10: _t->on_comboBox_tab_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_actionAbout_MDMA_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
