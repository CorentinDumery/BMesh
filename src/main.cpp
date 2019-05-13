
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include "MyViewer.h"



int main( int argc , char** argv )
{
    QApplication app( argc , argv );

    MyViewer * viewer = new MyViewer;

    QMainWindow * mainWindow = new QMainWindow;
    QToolBar * toolBar = new QToolBar;
    toolBar->setIconSize(QSize(35,35));
    toolBar->setAutoFillBackground(true);
    toolBar->setStyleSheet("QToolBar { background: white; }");
    viewer->add_actions_to_toolBar(toolBar);

    mainWindow->addToolBar(toolBar);

    mainWindow->setCentralWidget(viewer);

    QObject::connect( viewer , SIGNAL(windowTitleUpdated(QString)) , mainWindow , SLOT(setWindowTitle(QString)) );
    viewer->updateTitle("myProject");

    mainWindow->setWindowIcon(QIcon("img/icons/icon.png"));
    mainWindow->show();

    return app.exec();
}
