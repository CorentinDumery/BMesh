
#include "MyViewer.h"
#include "node.h"
#include "sphereedit.h"
#include "skeleton.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  MyViewer *viewer = new MyViewer;

  QMainWindow *mainWindow = new QMainWindow;
  QWidget *mainWidget = new QWidget;
  QVBoxLayout *mainLayout = new QVBoxLayout;
  SphereEdit *sphereEdit = new SphereEdit;

  mainWidget->setLayout(mainLayout);

  QToolBar *toolBar = new QToolBar;
  toolBar->setIconSize(QSize(35, 35));
  toolBar->setAutoFillBackground(true);
  toolBar->setStyleSheet("QToolBar { background: white; }");
  viewer->add_actions_to_toolBar(toolBar);

  mainLayout->addWidget(viewer);
  mainLayout->addWidget(sphereEdit);
  mainWindow->addToolBar(toolBar);
  mainWindow->setCentralWidget(mainWidget);
  mainWindow->resize(600, 525);

  //---------------TEST ZONE--------------
  Skeleton sq(Sphere(point3d(1, 2, 3), 1.2));

  auto lambda = [&](const Sphere &sphere) -> void {
    sq.getRoot()->addChild(sphere);
    viewer->update();
  };

  QObject::connect(sphereEdit, &SphereEdit::addNewSphere, lambda);
  //-------------------------------------

  QObject::connect(viewer, SIGNAL(windowTitleUpdated(QString)), mainWindow,
                   SLOT(setWindowTitle(QString)));
  viewer->updateTitle("myProject");

  mainWindow->setWindowIcon(QIcon("img/icons/icon.png"));
  mainWindow->show();

  return app.exec();
}
