#ifndef QTEXTINFOMODALWINDOW_H
#define QTEXTINFOMODALWINDOW_H



#include <QWidget>
#include <QColor>
//#include <QtGui>
#include <QTextEdit>
#include <QToolBar>

#include "QSmartAction.h"




class QTextInfoModalWindow : public QTextEdit{
    Q_OBJECT

    QString firstLinesText;

public:
    QTextInfoModalWindow(
            std::string const & textEraseIcon = "./icons/textErase.png",
            std::string const & textInsertHLineIcon = "./icons/textInsertHLine.png",
            double windowOpacity = 0.7,
            int minWidth = 300,
            int minHeight = 40,
            QWidget * parent = NULL ) : QTextEdit(parent)
    {
        // window options:
        this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
        this->setWindowTitle( "Text Info Box" );
        this->setFocusPolicy( Qt::ClickFocus );

        // first lines to avoid messing up everything with the toolbar:
        firstLinesText = QString("\n\n");
        this->setPlainText( firstLinesText );

        // window opacity:
        setWindowOpacity(windowOpacity);

        // window minimum size:
        setMinimumSize(minWidth,minHeight);

        // set read only:
        setReadOnly(true);

        // toolbar:
        QToolBar *toolBar = new QToolBar(this);
        DetailedAction * eraseTextAction = new DetailedAction( QIcon(textEraseIcon.c_str()) , "Erase Text" , "Erase Text" , this , this , SLOT(clearText()) );
        DetailedAction * insertHorizontalLineAction = new DetailedAction( QIcon(textInsertHLineIcon.c_str()) , "Insert HLine" , "Insert HLine" , this , this , SLOT(insertHorizontalLine()) );
        toolBar->addAction(eraseTextAction);
        toolBar->addAction(insertHorizontalLineAction);

        // initial position:
        setGeometry( 200 , 200 , width() , 400 );
    }


signals:

public slots:
    void clearText()
    {
        setPlainText( firstLinesText );
    }

    void appendText( const QString & textToAppend )
    {
        append( textToAppend );
    }

    void insertHorizontalLine()
    {
        append( QString("<hr style='width:80%; height:1px; color:black:'>") );
    }

    void setText( const QString & textToSet )
    {
        setPlainText( firstLinesText + textToSet );
    }
};




//class QTextInfoModalWindow : public QWidget{
//    Q_OBJECT


//    QLabel * text;
//    QString firstLinesText;


//    QVBoxLayout * mainLayout;

//public:
//    QTextInfoModalWindow( QWidget * parent = NULL ) : QWidget(parent)
//    {
//        mainLayout = new QVBoxLayout;
//        this->setLayout( mainLayout );
//        this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
//        this->setWindowTitle( "Text Info Box" );
//        this->setFocusPolicy( Qt::ClickFocus );

//        firstLinesText = QString("\n\n");
//        text = new QLabel(firstLinesText);
//        mainLayout->addWidget( text );

//        setWindowOpacity(0.7);

//        setMinimumSize(300,40);

//        QToolBar *toolBar = new QToolBar(this);
//        DetailedAction * eraseTextAction = new DetailedAction( QIcon("./icons/eraseText.png") , "Erase Text" , "Erase Text" , this , this , SLOT(clearText()) );
//        toolBar->addAction(eraseTextAction);


//    }


//signals:


//public slots:

//    void clearText()
//    {
//        text->setText(firstLinesText);
//    }

//    void appendText( const QString & textToAppend )
//    {
//        text->setText(text->text().append( textToAppend ));
//    }

//    void setText( const QString & textToSet )
//    {
//        text->setText( firstLinesText + textToSet );
//    }
//};






#endif // QTEXTINFOMODALWINDOW_H
