/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../DTM/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    const uint offsetsAndSize[32];
    char stringdata0[453];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 6), // "Widget"
QT_MOC_LITERAL(7, 33), // "on_pushButton_clearPoints_cli..."
QT_MOC_LITERAL(41, 0), // ""
QT_MOC_LITERAL(42, 29), // "on_pushButton_cleardt_clicked"
QT_MOC_LITERAL(72, 27), // "on_lineEdit_editingFinished"
QT_MOC_LITERAL(100, 29), // "on_lineEdit_2_editingFinished"
QT_MOC_LITERAL(130, 29), // "on_lineEdit_3_editingFinished"
QT_MOC_LITERAL(160, 34), // "on_pushButton_drawContours_cl..."
QT_MOC_LITERAL(195, 31), // "on_pushButton_drawSlope_clicked"
QT_MOC_LITERAL(227, 30), // "on_pushButton_ClearAll_clicked"
QT_MOC_LITERAL(258, 32), // "on_pushButton_Exposition_clicked"
QT_MOC_LITERAL(291, 32), // "on_pushButton_LoadPoints_clicked"
QT_MOC_LITERAL(324, 30), // "on_pushButton_mcLabels_clicked"
QT_MOC_LITERAL(355, 30), // "on_pushButton_Generate_clicked"
QT_MOC_LITERAL(386, 35), // "on_pushButton_clearContours_c..."
QT_MOC_LITERAL(422, 30) // "on_pushButton_createDT_clicked"

    },
    "Widget\0on_pushButton_clearPoints_clicked\0"
    "\0on_pushButton_cleardt_clicked\0"
    "on_lineEdit_editingFinished\0"
    "on_lineEdit_2_editingFinished\0"
    "on_lineEdit_3_editingFinished\0"
    "on_pushButton_drawContours_clicked\0"
    "on_pushButton_drawSlope_clicked\0"
    "on_pushButton_ClearAll_clicked\0"
    "on_pushButton_Exposition_clicked\0"
    "on_pushButton_LoadPoints_clicked\0"
    "on_pushButton_mcLabels_clicked\0"
    "on_pushButton_Generate_clicked\0"
    "on_pushButton_clearContours_clicked\0"
    "on_pushButton_createDT_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x08,    1 /* Private */,
       3,    0,   99,    2, 0x08,    2 /* Private */,
       4,    0,  100,    2, 0x08,    3 /* Private */,
       5,    0,  101,    2, 0x08,    4 /* Private */,
       6,    0,  102,    2, 0x08,    5 /* Private */,
       7,    0,  103,    2, 0x08,    6 /* Private */,
       8,    0,  104,    2, 0x08,    7 /* Private */,
       9,    0,  105,    2, 0x08,    8 /* Private */,
      10,    0,  106,    2, 0x08,    9 /* Private */,
      11,    0,  107,    2, 0x08,   10 /* Private */,
      12,    0,  108,    2, 0x08,   11 /* Private */,
      13,    0,  109,    2, 0x08,   12 /* Private */,
      14,    0,  110,    2, 0x08,   13 /* Private */,
      15,    0,  111,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_clearPoints_clicked(); break;
        case 1: _t->on_pushButton_cleardt_clicked(); break;
        case 2: _t->on_lineEdit_editingFinished(); break;
        case 3: _t->on_lineEdit_2_editingFinished(); break;
        case 4: _t->on_lineEdit_3_editingFinished(); break;
        case 5: _t->on_pushButton_drawContours_clicked(); break;
        case 6: _t->on_pushButton_drawSlope_clicked(); break;
        case 7: _t->on_pushButton_ClearAll_clicked(); break;
        case 8: _t->on_pushButton_Exposition_clicked(); break;
        case 9: _t->on_pushButton_LoadPoints_clicked(); break;
        case 10: _t->on_pushButton_mcLabels_clicked(); break;
        case 11: _t->on_pushButton_Generate_clicked(); break;
        case 12: _t->on_pushButton_clearContours_clicked(); break;
        case 13: _t->on_pushButton_createDT_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Widget.offsetsAndSize,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Widget_t
, QtPrivate::TypeAndForceComplete<Widget, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
