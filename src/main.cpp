#include "MyViewer.h"
#include "node.h"
#include "skeleton.h"
#include "sphereedit.h"
#include "pipelinestep.h"
#include "mediator.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>

uint Shape::idsCounter = 0;
std::queue<uint> Shape::avaibleIds;

int main(int argc, char **argv) {
    std::cout << "kk" << std::endl;
  QApplication app(argc, argv);
  std::cout << "kk" << std::endl;

  MyViewer *viewer = new MyViewer;

  std::cout << "kk" << std::endl;
  QObject::connect(Mediator::getInstance(), SIGNAL(updateViewer()), viewer,
                   SLOT(update()));

  std::cout << "1" << std::endl;
  QMainWindow *mainWindow = new QMainWindow;
  std::cout << "2" << std::endl;
  QWidget *mainWidget = new QWidget;
  QGridLayout *mainLayout = new QGridLayout;
  std::cout << "3" << std::endl;
  //SphereEdit *sphereEdit = new SphereEdit;
  std::cout << "4" << std::endl;
  PipelineStep *pipelineStep = new PipelineStep;

  std::cout << "5" << std::endl;
  mainWidget->setLayout(mainLayout);

  std::cout << "kk" << std::endl;
  QToolBar *toolBar = new QToolBar;
  toolBar->setIconSize(QSize(35, 35));
  toolBar->setAutoFillBackground(true);
  toolBar->setStyleSheet("QToolBar { background: white; }");
  viewer->add_actions_to_toolBar(toolBar);

  mainLayout->addWidget(viewer, 0, 0);
  mainLayout->addWidget(pipelineStep, 0,1);
  //mainLayout->addWidget(sphereEdit, 1,0, 1,1);
  mainWindow->addToolBar(toolBar);
  mainWindow->setCentralWidget(mainWidget);
  mainWindow->resize(640, 525);

  // Connect viewer slection to ui sphere editing
  //QObject::connect(viewer, &MyViewer::nodeSelected, sphereEdit,
  //                 &SphereEdit::updateSelection);

  // Connect viewer and pipelinestep
  QObject::connect(pipelineStep, &PipelineStep::interpolate, viewer,
                   &MyViewer::interpolate);
  QObject::connect(pipelineStep, &PipelineStep::stitch, viewer,
                   &MyViewer::stitch);
  QObject::connect(pipelineStep, &PipelineStep::catmull, viewer,
                   &MyViewer::catmull);
  QObject::connect(pipelineStep, &PipelineStep::evolve, viewer,
                   &MyViewer::evolve);
  QObject::connect(pipelineStep, &PipelineStep::fairing, viewer,
                   &MyViewer::fairing);

  QObject::connect(viewer, SIGNAL(windowTitleUpdated(QString)), mainWindow,
                   SLOT(setWindowTitle(QString)));
  viewer->updateTitle("B-mesh");

  mainWindow->setWindowIcon(QIcon("img/icons/icon.png"));
  mainWindow->show();

  return app.exec();
}
