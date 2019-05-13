TEMPLATE = app
TARGET = myProject
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
    ./src/gl/BasicColors.h
SOURCES += ./src/main.cpp \
    ./src/gl/GLUtilityMethods.cpp\
    ./src/gl/BasicColors.cpp

#QGLViewer
{
    unix:!macx: LIBS += -L$$PWD/extern/libQGLViewer-2.7.1/lib/ -lQGLViewer-qt5

    INCLUDEPATH += $$PWD/extern/libQGLViewer-2.7.1/include
    DEPENDPATH += $$PWD/extern/libQGLViewer-2.7.1/include
}

#GSL
{
    unix:!macx: LIBS += -L$$PWD/extern/gsl/lib/ -lgsl

    INCLUDEPATH += $$PWD/extern/gsl/include
    DEPENDPATH += $$PWD/extern/gsl/include

    unix:!macx: LIBS += -L$$PWD/extern/gsl/lib/ -lgslcblas

    INCLUDEPATH += $$PWD/extern/gsl/include
    DEPENDPATH += $$PWD/extern/gsl/include

    unix:!macx: PRE_TARGETDEPS += $$PWD/extern/gsl/lib/libgslcblas.a
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
