/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../lab05-yuv-viewer-student/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "slot_exit",
    "",
    "slot_about",
    "slot_open_file",
    "slot_open_recent_file",
    "slot_load_yuv_image",
    "slot_load_checker_image",
    "slot_load_triangle_image",
    "slot_zoom_in",
    "slot_zoom_out",
    "slot_thread_changed",
    "slot_full_screen",
    "slot_normal_size",
    "slot_fit_to_window"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[30];
    char stringdata0[11];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[15];
    char stringdata5[22];
    char stringdata6[20];
    char stringdata7[24];
    char stringdata8[25];
    char stringdata9[13];
    char stringdata10[14];
    char stringdata11[20];
    char stringdata12[17];
    char stringdata13[17];
    char stringdata14[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 9),  // "slot_exit"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 10),  // "slot_about"
        QT_MOC_LITERAL(33, 14),  // "slot_open_file"
        QT_MOC_LITERAL(48, 21),  // "slot_open_recent_file"
        QT_MOC_LITERAL(70, 19),  // "slot_load_yuv_image"
        QT_MOC_LITERAL(90, 23),  // "slot_load_checker_image"
        QT_MOC_LITERAL(114, 24),  // "slot_load_triangle_image"
        QT_MOC_LITERAL(139, 12),  // "slot_zoom_in"
        QT_MOC_LITERAL(152, 13),  // "slot_zoom_out"
        QT_MOC_LITERAL(166, 19),  // "slot_thread_changed"
        QT_MOC_LITERAL(186, 16),  // "slot_full_screen"
        QT_MOC_LITERAL(203, 16),  // "slot_normal_size"
        QT_MOC_LITERAL(220, 18)   // "slot_fit_to_window"
    },
    "MainWindow",
    "slot_exit",
    "",
    "slot_about",
    "slot_open_file",
    "slot_open_recent_file",
    "slot_load_yuv_image",
    "slot_load_checker_image",
    "slot_load_triangle_image",
    "slot_zoom_in",
    "slot_zoom_out",
    "slot_thread_changed",
    "slot_full_screen",
    "slot_normal_size",
    "slot_fit_to_window"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x08,    1 /* Private */,
       3,    0,   93,    2, 0x08,    2 /* Private */,
       4,    0,   94,    2, 0x08,    3 /* Private */,
       5,    0,   95,    2, 0x08,    4 /* Private */,
       6,    0,   96,    2, 0x08,    5 /* Private */,
       7,    0,   97,    2, 0x08,    6 /* Private */,
       8,    0,   98,    2, 0x08,    7 /* Private */,
       9,    0,   99,    2, 0x08,    8 /* Private */,
      10,    0,  100,    2, 0x08,    9 /* Private */,
      11,    0,  101,    2, 0x08,   10 /* Private */,
      12,    0,  102,    2, 0x08,   11 /* Private */,
      13,    0,  103,    2, 0x08,   12 /* Private */,
      14,    0,  104,    2, 0x08,   13 /* Private */,

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

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'slot_exit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_about'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_open_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_open_recent_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_load_yuv_image'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_load_checker_image'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_load_triangle_image'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_zoom_in'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_zoom_out'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_thread_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_full_screen'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_normal_size'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_fit_to_window'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slot_exit(); break;
        case 1: _t->slot_about(); break;
        case 2: _t->slot_open_file(); break;
        case 3: _t->slot_open_recent_file(); break;
        case 4: _t->slot_load_yuv_image(); break;
        case 5: _t->slot_load_checker_image(); break;
        case 6: _t->slot_load_triangle_image(); break;
        case 7: _t->slot_zoom_in(); break;
        case 8: _t->slot_zoom_out(); break;
        case 9: _t->slot_thread_changed(); break;
        case 10: _t->slot_full_screen(); break;
        case 11: _t->slot_normal_size(); break;
        case 12: _t->slot_fit_to_window(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
