#ifndef QBRUSHDISK_H
#define QBRUSHDISK_H



#include <QGLViewer/mouseGrabber.h>

#include <QGLViewer/qglviewer.h>
#include "GLUtilityMethods.h"
class GLVWidget;
#include <QtGui>




class QBrushDisk : public QObject , public qglviewer::MouseGrabber
{
    Q_OBJECT

    int xCenter , yCenter;
    float diskRadius;

    bool m_is_active;
    bool m_mouse_is_released;
    bool m_is_selecting; // either selecting or unselecting

    // extra:
    int m_brush_mode;

public:
    QBrushDisk() : xCenter(0) , yCenter(0) , diskRadius(10.f) , m_is_active(false) , m_mouse_is_released(true) , m_is_selecting(true) , m_brush_mode(0) {}

    bool isActive() const { return m_is_active; }

    void activate( bool toggleActivation )
    {
        m_is_active = toggleActivation;
    }

    void setBrushMode(int m)
    {
        m_brush_mode = m;
    }
    int getBrushMode() const { return m_brush_mode; }

    void checkIfGrabsMouse(int , int ,const qglviewer::Camera* const )
    {
        setGrabsMouse(m_is_active);
    }

    void mousePressEvent( QMouseEvent* const event  , qglviewer::Camera* const  )
    {
        m_mouse_is_released = false;

        xCenter = event->x();
        yCenter = event->y();
        m_is_selecting = ( event->buttons() & Qt::LeftButton );

        if( m_is_selecting )
            emit selectInDisk( xCenter , yCenter , diskRadius , event->modifiers()  );
        else
            emit unselectInDisk( xCenter , yCenter , diskRadius , event->modifiers()  );
    }
    void mouseMoveEvent( QMouseEvent* const event  , qglviewer::Camera* const  )
    {
        xCenter = event->x();
        yCenter = event->y();
        m_is_selecting = ( event->buttons() & Qt::LeftButton );

        if(!m_mouse_is_released)
        {
            if( m_is_selecting )
                emit selectInDisk( xCenter , yCenter , diskRadius , event->modifiers() );
            else
                emit unselectInDisk( xCenter , yCenter , diskRadius , event->modifiers()  );
        }
    }
    void mouseReleaseEvent( QMouseEvent* const event  , qglviewer::Camera* const  )
    {
        m_mouse_is_released = true;
        xCenter = event->x();
        yCenter = event->y();
    }
    void wheelEvent(QWheelEvent* const event , qglviewer::Camera* const  )
    {
        int numDegrees = abs(event->delta()) / 8;
        int numSteps = numDegrees / 15;
        if( event->delta() > 0 )
            for( int i = 0 ; i < numSteps ; ++i )
                diskRadius *= 1.1f;
        else
            for( int i = 0 ; i < numSteps ; ++i )
                diskRadius /= 1.1f;
    }


    void draw()
    {
        float viewport[4];
        glGetFloatv( GL_VIEWPORT , viewport );

        float x = viewport[0] , y = viewport[1];
        float w = viewport[2] , h = viewport[3];

        float rectangle_left = xCenter-diskRadius;
        float rectangle_right = xCenter+diskRadius;
        float rectangle_top = yCenter+diskRadius;
        float rectangle_bottom = yCenter-diskRadius;

        float left = (float)(rectangle_left - x) / w;
        float right = (float)(rectangle_right - x) / w;
        float top = 1.f - (float)(rectangle_top - y) / h;
        float bottom = 1.f - (float)(rectangle_bottom - y) / h;

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);

        glPolygonMode( GL_FRONT_AND_BACK , GL_FILL );

        glMatrixMode( GL_PROJECTION );
        glPushMatrix();
        glLoadIdentity();
        glOrtho( 0.f , 1.f , 0.f , 1.f , -1.f , 1.f );
        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
        glLoadIdentity();


        // draw rectangle:
        glColor4f( 1.0 , 1.0 , 1.0 , 1.0 );
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex2f( left , top );
        glTexCoord2f(0,1);
        glVertex2f( left , bottom );
        glTexCoord2f(1,1);
        glVertex2f( right , bottom );
        glTexCoord2f(1,0);
        glVertex2f( right , top );
        glEnd();



        glPopMatrix();
        glMatrixMode( GL_PROJECTION );
        glPopMatrix();
        glMatrixMode( GL_MODELVIEW );


        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
    }



signals:
    void selectInDisk( int , int , float , Qt::KeyboardModifiers );
    void unselectInDisk( int , int , float , Qt::KeyboardModifiers );
    void selectInDisk( int , int , float );
    void unselectInDisk( int , int , float );
};



#endif // QBRUSHDISK_H
