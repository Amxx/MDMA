/****************************************************************************
** Meta object code from reading C++ file 'zoneeditor.h'
**
** Created: Mon Nov 12 10:16:05 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/UI/zoneeditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zoneeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_zoneEditor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      42,   36,   11,   11, 0x08,
      86,   36,   11,   11, 0x08,
     130,   36,   11,   11, 0x08,
     173,   36,   11,   11, 0x08,
     215,   36,   11,   11, 0x08,
     257,   36,   11,   11, 0x08,
     300,   36,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_zoneEditor[] = {
    "zoneEditor\0\0on_buttonBox_accepted()\0"
    "index\0on_comboBox_axex_0_currentIndexChanged(int)\0"
    "on_comboBox_axey_0_currentIndexChanged(int)\0"
    "on_comboBox_enter_currentIndexChanged(int)\0"
    "on_comboBox_exit_currentIndexChanged(int)\0"
    "on_comboBox_open_currentIndexChanged(int)\0"
    "on_comboBox_close_currentIndexChanged(int)\0"
    "on_comboBox_shock_currentIndexChanged(int)\0"
};

void zoneEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        zoneEditor *_t = static_cast<zoneEditor *>(_o);
        switch (_id) {
        case 0: _t->on_buttonBox_accepted(); break;
        case 1: _t->on_comboBox_axex_0_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_comboBox_axey_0_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_comboBox_enter_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_comboBox_exit_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_comboBox_open_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_comboBox_close_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_comboBox_shock_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData zoneEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject zoneEditor::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_zoneEditor,
      qt_meta_data_zoneEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &zoneEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *zoneEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *zoneEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_zoneEditor))
        return static_cast<void*>(const_cast< zoneEditor*>(this));
    return QDialog::qt_metacast(_clname);
}

int zoneEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
