#ifndef MYVIEWER_H
#define MYVIEWER_H

// Mesh stuff:
#include "Mesh.h"

// Parsing:
#include "BasicIO.h"

// opengl and basic gl utilities:
#define GL_GLEXT_PROTOTYPES
#include <GL/glext.h>
#include <QGLViewer/qglviewer.h>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_0>
#include <gl/openglincludeQtComp.h>

#include <gl/GLUtilityMethods.h>

// Qt stuff:
#include <QColorDialog>
#include <QFileDialog>
#include <QFormLayout>
#include <QInputDialog>
#include <QKeyEvent>
#include <QLineEdit>
#include <QToolBar>

#include "node.h"
#include "qt/QSmartAction.h"
#include "skeleton.h"

class MyViewer : public QGLViewer, public QOpenGLFunctions_3_0 {
  Q_OBJECT

  Mesh mesh;
  Skeleton skeleton;
  Node *selectedNode = nullptr;
  bool fillMode = true;
  bool displaySpheres = true;
  bool displayNormals = false;
  bool displayHull = false;

  float Itarget = 0.1;
  float T = 0.1 ;

  int cursorT[2];

  QWidget *controls;

public:
  MyViewer(QGLWidget *parent = nullptr)
      : QGLViewer(parent), QOpenGLFunctions_3_0() {}
  void add_actions_to_toolBar(QToolBar *toolBar);
  void draw() override;
  void drawWithNames() override { skeleton.drawWithNames(); }
  void postSelection(const QPoint &point) override;
  void pickBackgroundColor();
  void adjustCamera(point3d const &bb, point3d const &BB);
  void init() override;
  QString helpString() const override;
  void updateTitle(QString text) {
    this->setWindowTitle(text);
    emit windowTitleUpdated(text);
  }
  void keyPressEvent(QKeyEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *e) override;
  void mousePressEvent(QMouseEvent *e) override {
    QGLViewer::mousePressEvent(e);
  }
  void mouseMoveEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override {
    QGLViewer::mouseReleaseEvent(e);
  }

signals:
  void windowTitleUpdated(const QString &);
  void nodeSelected(Node *node);

public slots:
  void addSphereToSkeleton(Sphere *sphere);
  void open_mesh();
  void save_mesh();
  void showControls();
  void saveCameraInFile(const QString &filename);
  void openCameraFromFile(const QString &filename);
  void openCamera();
  void saveCamera();
  void saveSnapShotPlusPlus();
  void pipeline();
  void generateRandom();
  void startFromScratch();
  void hideShowSpheres();
  void hideShowMesh();
  void hideShowHull();
  void interpolate();
  void stitch();
  void catmull();
  void evolve();
  void fairing();
};

#endif // MYVIEWER_H
