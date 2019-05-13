#ifndef QSMARTCOLORPICKER_H
#define QSMARTCOLORPICKER_H

//#include <QtGui>
#include <QToolButton>
#include <QColorDialog>


class QSmartColorPicker : public QToolButton
{
    Q_OBJECT

private:
    QColor bgdColor;
    QWidget * m_parent;
    void changeBackgroundColor( QColor c )
    {
        bgdColor = c;
        setStyleSheet(QString("background-color: rgb(%1, %2, %3); color: rgb(255,255,255)").arg(c.red()).arg(c.green()).arg(c.blue()));
    }

public:
    QSmartColorPicker (QWidget * p = NULL) : QToolButton (p) , m_parent(p){
        setAutoFillBackground(true);
        connect( this, SIGNAL(clicked()) , this , SLOT(openColorDialog()) );
        setText("  ");
        changeBackgroundColor( QColor( 255,255,255 ) );
    }
    QSmartColorPicker ( QColor c ,QWidget * p = NULL) : QToolButton (p) , m_parent(p){
        setAutoFillBackground(true);
        connect( this, SIGNAL(clicked()) , this , SLOT(openColorDialog()) );
        setText("  ");
        changeBackgroundColor(c);
    }

signals:
    void colorChanged( QColor c );

public slots:
    void openColorDialog(  )
    {
        QColor color = QColorDialog::getColor( bgdColor , m_parent);
        if( color.isValid() )
        {
            changeBackgroundColor(color);
            emit colorChanged(color);
        }
    }
};







#endif // QSMARTCOLORPICKER_H
