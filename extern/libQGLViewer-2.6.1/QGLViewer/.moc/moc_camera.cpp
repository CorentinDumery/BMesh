/****************************************************************************
** Meta object code from reading C++ file 'camera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../camera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qglviewer__Camera_t {
    QByteArrayData data[82];
    char stringdata0[1012];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qglviewer__Camera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qglviewer__Camera_t qt_meta_stringdata_qglviewer__Camera = {
    {
QT_MOC_LITERAL(0, 0, 17), // "qglviewer::Camera"
QT_MOC_LITERAL(1, 18, 11), // "setPosition"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 3), // "Vec"
QT_MOC_LITERAL(4, 35, 3), // "pos"
QT_MOC_LITERAL(5, 39, 14), // "setOrientation"
QT_MOC_LITERAL(6, 54, 10), // "Quaternion"
QT_MOC_LITERAL(7, 65, 1), // "q"
QT_MOC_LITERAL(8, 67, 5), // "theta"
QT_MOC_LITERAL(9, 73, 3), // "phi"
QT_MOC_LITERAL(10, 77, 11), // "setUpVector"
QT_MOC_LITERAL(11, 89, 2), // "up"
QT_MOC_LITERAL(12, 92, 6), // "noMove"
QT_MOC_LITERAL(13, 99, 16), // "setViewDirection"
QT_MOC_LITERAL(14, 116, 9), // "direction"
QT_MOC_LITERAL(15, 126, 6), // "lookAt"
QT_MOC_LITERAL(16, 133, 6), // "target"
QT_MOC_LITERAL(17, 140, 15), // "showEntireScene"
QT_MOC_LITERAL(18, 156, 9), // "fitSphere"
QT_MOC_LITERAL(19, 166, 6), // "center"
QT_MOC_LITERAL(20, 173, 6), // "radius"
QT_MOC_LITERAL(21, 180, 14), // "fitBoundingBox"
QT_MOC_LITERAL(22, 195, 3), // "min"
QT_MOC_LITERAL(23, 199, 3), // "max"
QT_MOC_LITERAL(24, 203, 15), // "fitScreenRegion"
QT_MOC_LITERAL(25, 219, 9), // "rectangle"
QT_MOC_LITERAL(26, 229, 11), // "centerScene"
QT_MOC_LITERAL(27, 241, 24), // "interpolateToZoomOnPixel"
QT_MOC_LITERAL(28, 266, 5), // "pixel"
QT_MOC_LITERAL(29, 272, 21), // "interpolateToFitScene"
QT_MOC_LITERAL(30, 294, 13), // "interpolateTo"
QT_MOC_LITERAL(31, 308, 5), // "Frame"
QT_MOC_LITERAL(32, 314, 2), // "fr"
QT_MOC_LITERAL(33, 317, 8), // "duration"
QT_MOC_LITERAL(34, 326, 7), // "setType"
QT_MOC_LITERAL(35, 334, 4), // "Type"
QT_MOC_LITERAL(36, 339, 4), // "type"
QT_MOC_LITERAL(37, 344, 14), // "setFieldOfView"
QT_MOC_LITERAL(38, 359, 3), // "fov"
QT_MOC_LITERAL(39, 363, 24), // "setHorizontalFieldOfView"
QT_MOC_LITERAL(40, 388, 4), // "hfov"
QT_MOC_LITERAL(41, 393, 16), // "setFOVToFitScene"
QT_MOC_LITERAL(42, 410, 14), // "setAspectRatio"
QT_MOC_LITERAL(43, 425, 6), // "aspect"
QT_MOC_LITERAL(44, 432, 23), // "setScreenWidthAndHeight"
QT_MOC_LITERAL(45, 456, 5), // "width"
QT_MOC_LITERAL(46, 462, 6), // "height"
QT_MOC_LITERAL(47, 469, 19), // "setZNearCoefficient"
QT_MOC_LITERAL(48, 489, 4), // "coef"
QT_MOC_LITERAL(49, 494, 23), // "setZClippingCoefficient"
QT_MOC_LITERAL(50, 518, 14), // "setSceneRadius"
QT_MOC_LITERAL(51, 533, 14), // "setSceneCenter"
QT_MOC_LITERAL(52, 548, 23), // "setSceneCenterFromPixel"
QT_MOC_LITERAL(53, 572, 19), // "setSceneBoundingBox"
QT_MOC_LITERAL(54, 592, 13), // "setPivotPoint"
QT_MOC_LITERAL(55, 606, 5), // "point"
QT_MOC_LITERAL(56, 612, 22), // "setPivotPointFromPixel"
QT_MOC_LITERAL(57, 635, 21), // "setRevolveAroundPoint"
QT_MOC_LITERAL(58, 657, 30), // "setRevolveAroundPointFromPixel"
QT_MOC_LITERAL(59, 688, 8), // "setFrame"
QT_MOC_LITERAL(60, 697, 28), // "ManipulatedCameraFrame*const"
QT_MOC_LITERAL(61, 726, 3), // "mcf"
QT_MOC_LITERAL(62, 730, 23), // "setKeyFrameInterpolator"
QT_MOC_LITERAL(63, 754, 1), // "i"
QT_MOC_LITERAL(64, 756, 26), // "KeyFrameInterpolator*const"
QT_MOC_LITERAL(65, 783, 3), // "kfi"
QT_MOC_LITERAL(66, 787, 17), // "addKeyFrameToPath"
QT_MOC_LITERAL(67, 805, 8), // "playPath"
QT_MOC_LITERAL(68, 814, 10), // "deletePath"
QT_MOC_LITERAL(69, 825, 9), // "resetPath"
QT_MOC_LITERAL(70, 835, 12), // "drawAllPaths"
QT_MOC_LITERAL(71, 848, 11), // "setFlySpeed"
QT_MOC_LITERAL(72, 860, 5), // "speed"
QT_MOC_LITERAL(73, 866, 13), // "setIODistance"
QT_MOC_LITERAL(74, 880, 8), // "distance"
QT_MOC_LITERAL(75, 889, 27), // "setPhysicalDistanceToScreen"
QT_MOC_LITERAL(76, 917, 22), // "setPhysicalScreenWidth"
QT_MOC_LITERAL(77, 940, 16), // "setFocusDistance"
QT_MOC_LITERAL(78, 957, 18), // "initFromDOMElement"
QT_MOC_LITERAL(79, 976, 11), // "QDomElement"
QT_MOC_LITERAL(80, 988, 7), // "element"
QT_MOC_LITERAL(81, 996, 15) // "onFrameModified"

    },
    "qglviewer::Camera\0setPosition\0\0Vec\0"
    "pos\0setOrientation\0Quaternion\0q\0theta\0"
    "phi\0setUpVector\0up\0noMove\0setViewDirection\0"
    "direction\0lookAt\0target\0showEntireScene\0"
    "fitSphere\0center\0radius\0fitBoundingBox\0"
    "min\0max\0fitScreenRegion\0rectangle\0"
    "centerScene\0interpolateToZoomOnPixel\0"
    "pixel\0interpolateToFitScene\0interpolateTo\0"
    "Frame\0fr\0duration\0setType\0Type\0type\0"
    "setFieldOfView\0fov\0setHorizontalFieldOfView\0"
    "hfov\0setFOVToFitScene\0setAspectRatio\0"
    "aspect\0setScreenWidthAndHeight\0width\0"
    "height\0setZNearCoefficient\0coef\0"
    "setZClippingCoefficient\0setSceneRadius\0"
    "setSceneCenter\0setSceneCenterFromPixel\0"
    "setSceneBoundingBox\0setPivotPoint\0"
    "point\0setPivotPointFromPixel\0"
    "setRevolveAroundPoint\0"
    "setRevolveAroundPointFromPixel\0setFrame\0"
    "ManipulatedCameraFrame*const\0mcf\0"
    "setKeyFrameInterpolator\0i\0"
    "KeyFrameInterpolator*const\0kfi\0"
    "addKeyFrameToPath\0playPath\0deletePath\0"
    "resetPath\0drawAllPaths\0setFlySpeed\0"
    "speed\0setIODistance\0distance\0"
    "setPhysicalDistanceToScreen\0"
    "setPhysicalScreenWidth\0setFocusDistance\0"
    "initFromDOMElement\0QDomElement\0element\0"
    "onFrameModified"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qglviewer__Camera[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  239,    2, 0x0a /* Public */,
       5,    1,  242,    2, 0x0a /* Public */,
       5,    2,  245,    2, 0x0a /* Public */,
      10,    2,  250,    2, 0x0a /* Public */,
      10,    1,  255,    2, 0x2a /* Public | MethodCloned */,
      13,    1,  258,    2, 0x0a /* Public */,
      15,    1,  261,    2, 0x0a /* Public */,
      17,    0,  264,    2, 0x0a /* Public */,
      18,    2,  265,    2, 0x0a /* Public */,
      21,    2,  270,    2, 0x0a /* Public */,
      24,    1,  275,    2, 0x0a /* Public */,
      26,    0,  278,    2, 0x0a /* Public */,
      27,    1,  279,    2, 0x0a /* Public */,
      29,    0,  282,    2, 0x0a /* Public */,
      30,    2,  283,    2, 0x0a /* Public */,
      34,    1,  288,    2, 0x0a /* Public */,
      37,    1,  291,    2, 0x0a /* Public */,
      39,    1,  294,    2, 0x0a /* Public */,
      41,    0,  297,    2, 0x0a /* Public */,
      42,    1,  298,    2, 0x0a /* Public */,
      44,    2,  301,    2, 0x0a /* Public */,
      47,    1,  306,    2, 0x0a /* Public */,
      49,    1,  309,    2, 0x0a /* Public */,
      50,    1,  312,    2, 0x0a /* Public */,
      51,    1,  315,    2, 0x0a /* Public */,
      52,    1,  318,    2, 0x0a /* Public */,
      53,    2,  321,    2, 0x0a /* Public */,
      54,    1,  326,    2, 0x0a /* Public */,
      56,    1,  329,    2, 0x0a /* Public */,
      57,    1,  332,    2, 0x0a /* Public */,
      58,    1,  335,    2, 0x0a /* Public */,
      59,    1,  338,    2, 0x0a /* Public */,
      62,    2,  341,    2, 0x0a /* Public */,
      66,    1,  346,    2, 0x0a /* Public */,
      67,    1,  349,    2, 0x0a /* Public */,
      68,    1,  352,    2, 0x0a /* Public */,
      69,    1,  355,    2, 0x0a /* Public */,
      70,    0,  358,    2, 0x0a /* Public */,
      71,    1,  359,    2, 0x0a /* Public */,
      73,    1,  362,    2, 0x0a /* Public */,
      75,    1,  365,    2, 0x0a /* Public */,
      76,    1,  368,    2, 0x0a /* Public */,
      77,    1,  371,    2, 0x0a /* Public */,
      78,    1,  374,    2, 0x0a /* Public */,
      81,    0,  377,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,    8,    9,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,   11,   12,
    QMetaType::Void, 0x80000000 | 3,   11,
    QMetaType::Void, 0x80000000 | 3,   14,
    QMetaType::Void, 0x80000000 | 3,   16,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QReal,   19,   20,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   22,   23,
    QMetaType::Void, QMetaType::QRect,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   28,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 31, QMetaType::QReal,   32,   33,
    QMetaType::Void, 0x80000000 | 35,   36,
    QMetaType::Void, QMetaType::QReal,   38,
    QMetaType::Void, QMetaType::QReal,   40,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   45,   46,
    QMetaType::Void, QMetaType::QReal,   48,
    QMetaType::Void, QMetaType::QReal,   48,
    QMetaType::Void, QMetaType::QReal,   20,
    QMetaType::Void, 0x80000000 | 3,   19,
    QMetaType::Bool, QMetaType::QPoint,   28,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,   22,   23,
    QMetaType::Void, 0x80000000 | 3,   55,
    QMetaType::Bool, QMetaType::QPoint,   28,
    QMetaType::Void, 0x80000000 | 3,   55,
    QMetaType::Bool, QMetaType::QPoint,   28,
    QMetaType::Void, 0x80000000 | 60,   61,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 64,   63,   65,
    QMetaType::Void, QMetaType::UInt,   63,
    QMetaType::Void, QMetaType::UInt,   63,
    QMetaType::Void, QMetaType::UInt,   63,
    QMetaType::Void, QMetaType::UInt,   63,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,   72,
    QMetaType::Void, QMetaType::QReal,   74,
    QMetaType::Void, QMetaType::QReal,   74,
    QMetaType::Void, QMetaType::QReal,   45,
    QMetaType::Void, QMetaType::QReal,   74,
    QMetaType::Void, 0x80000000 | 79,   80,
    QMetaType::Void,

       0        // eod
};

void qglviewer::Camera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Camera *_t = static_cast<Camera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setPosition((*reinterpret_cast< const Vec(*)>(_a[1]))); break;
        case 1: _t->setOrientation((*reinterpret_cast< const Quaternion(*)>(_a[1]))); break;
        case 2: _t->setOrientation((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 3: _t->setUpVector((*reinterpret_cast< const Vec(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->setUpVector((*reinterpret_cast< const Vec(*)>(_a[1]))); break;
        case 5: _t->setViewDirection((*reinterpret_cast< const Vec(*)>(_a[1]))); break;
        case 6: _t->lookAt((*reinterpret_cast< const Vec(*)>(_a[1]))); break;
        case 7: _t->showEntireScene(); break;
        case 8: _t->fitSphere((*reinterpret_cast< const Vec(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 9: _t->fitBoundingBox((*reinterpret_cast< const Vec(*)>(_a[1])),(*reinterpret_cast< const Vec(*)>(_a[2]))); break;
        case 10: _t->fitScreenRegion((*reinterpret_cast< const QRect(*)>(_a[1]))); break;
        case 11: _t->centerScene(); break;
        case 12: _t->interpolateToZoomOnPixel((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 13: _t->interpolateToFitScene(); break;
        case 14: _t->interpolateTo((*reinterpret_cast< const Frame(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 15: _t->setType((*reinterpret_cast< Type(*)>(_a[1]))); break;
        case 16: _t->setFieldOfView((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 17: _t->setHorizontalFieldOfView((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 18: _t->setFOVToFitScene(); break;
        case 19: _t->setAspectRatio((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 20: _t->setScreenWidthAndHeight((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 21: _t->setZNearCoefficient((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 22: _t->setZClippingCoefficient((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 23: _t->setSceneRadius((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 24: _t->setSceneCenter((*reinterpret_cast< const Vec(*)>(_a[1]))); break;
        case 25: { bool _r = _t->setSceneCenterFromPixel((*reinterpret_cast< const QPoint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->setSceneBoundingBox((*reinterpret_cast< const Vec(*)>(_a[1])),(*reinterpret_cast< const Vec(*)>(_a[2]))); break;
        case 27: _t->setPivotPoint((*reinterpret_cast< const Vec(*)>(_a[1]))); break;
        case 28: { bool _r = _t->setPivotPointFromPixel((*reinterpret_cast< const QPoint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 29: _t->setRevolveAroundPoint((*reinterpret_cast< const Vec(*)>(_a[1]))); break;
        case 30: { bool _r = _t->setRevolveAroundPointFromPixel((*reinterpret_cast< const QPoint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 31: _t->setFrame((*reinterpret_cast< ManipulatedCameraFrame*const(*)>(_a[1]))); break;
        case 32: _t->setKeyFrameInterpolator((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< KeyFrameInterpolator*const(*)>(_a[2]))); break;
        case 33: _t->addKeyFrameToPath((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 34: _t->playPath((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 35: _t->deletePath((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 36: _t->resetPath((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 37: _t->drawAllPaths(); break;
        case 38: _t->setFlySpeed((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 39: _t->setIODistance((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 40: _t->setPhysicalDistanceToScreen((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 41: _t->setPhysicalScreenWidth((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 42: _t->setFocusDistance((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 43: _t->initFromDOMElement((*reinterpret_cast< const QDomElement(*)>(_a[1]))); break;
        case 44: _t->onFrameModified(); break;
        default: ;
        }
    }
}

const QMetaObject qglviewer::Camera::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_qglviewer__Camera.data,
      qt_meta_data_qglviewer__Camera,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *qglviewer::Camera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qglviewer::Camera::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qglviewer__Camera.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int qglviewer::Camera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 45)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 45;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
