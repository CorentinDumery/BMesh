TEMPLATE = app
TARGET = BmeshModeler
DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += ./src
QT += opengl xml
CONFIG += qt \
    release
MOC_DIR = ./tmp/moc
OBJECTS_DIR = ./tmp/obj

# Input
HEADERS += ./src/point3.h \
    ./src/Mesh.h \
    ./src/MyViewer.h \
    ./src/gl/GLUtilityMethods.h \
    ./src/gl/BasicColors.h \
    ./src/sphereedit.h \
    ./src/pipelinestep.h \
    src/node.h \
    src/skeleton.h \
    src/mediator.h \
    src/quickhull.h \
    src/catmullClark.h \
    src/utility.h
SOURCES += ./src/main.cpp \
    ./src/gl/GLUtilityMethods.cpp \
    ./src/gl/BasicColors.cpp \
    ./src/sphereedit.cpp \
    ./src/pipelinestep.cpp \
    src/skeleton.cpp \
    src/MyViewer.cpp \
    src/mediator.cpp \
    src/catmullClark.cpp

#QGLViewer
{
    unix:!macx: LIBS += -L$$PWD/libQGLViewer-2.7.2/QGLViewer/

    INCLUDEPATH += $$PWD/libQGLViewer-2.7.2/QGLViewer
    DEPENDPATH += $$PWD/libQGLViewer-2.7.2/QGLViewer
    INCLUDEPATH += /export/home/cordum/other/bmesh/libQGLViewer-2.7.2/QGLViewer
    DEPENDPATH += "/export/home/cordum/other/bmesh/libQGLViewer-2.7.2/QGLViewer"
    LIBS += -L~/other/bmesh/libQGLViewer-2.7.2/QGLViewer/
}

#GSL
{
    unix:!macx: LIBS += -L$$PWD/extern/gsl/lib/ -lgsl -lgslcblas -lQGLViewer-qt5

    INCLUDEPATH += $$PWD/extern/gsl/include
    DEPENDPATH += $$PWD/extern/gsl/include
}

LIBS += -lglut \
    -lGLU
LIBS += -lblas \
    -lgomp
release:QMAKE_CXXFLAGS_RELEASE += -O3 \
    -fopenmp
release:QMAKE_CFLAGS_RELEASE += -O3 \
    -fopenmp

RESOURCES += \
    icons.qrc

FORMS += \
    src/sphereedit.ui \
    src/pipelinestep.ui
