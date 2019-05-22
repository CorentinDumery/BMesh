#include "MyViewer.h"
#include "node.h"
#include "skeleton.h"
#include "sphereedit.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>

uint Shape::idsCounter = 0;
std::queue<uint> Shape::avaibleIds;

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

  // Connect ui sphere editing to the skeleton
  QObject::connect(sphereEdit, &SphereEdit::addNewSphere, viewer,
                   &MyViewer::addSphereToSkeleton);

  QObject::connect(viewer, SIGNAL(windowTitleUpdated(QString)), mainWindow,
                   SLOT(setWindowTitle(QString)));
  viewer->updateTitle("myProject");

  mainWindow->setWindowIcon(QIcon("img/icons/icon.png"));
  mainWindow->show();

  return app.exec();
}
