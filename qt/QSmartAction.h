#ifndef QSMARTACTION_H
#define QSMARTACTION_H


#include <QAction>
#include <QIcon>



class DetailedAction : public QAction
{
public :
    DetailedAction( const QIcon &icon, const QString &text, const QString &statusTip, QObject* parent , QObject * plugin , const char * connectedToTriggered) :  QAction( icon, text, parent )
    {
        this->setStatusTip(statusTip);
        connect(this, SIGNAL(triggered()), plugin, connectedToTriggered);
    }
};

class DetailedCheckableAction : public QAction
{
public :
    DetailedCheckableAction( const QIcon &icon, const QString &text, const QString &statusTip, QObject* parent , QObject * plugin , const char * connectedToTriggered) :  QAction( icon, text, parent )
    {
        this->setStatusTip(statusTip);
        this->setCheckable(true);
        connect(this, SIGNAL(toggled(bool)), plugin, connectedToTriggered);
    }
};

//DetailedAction( QIcon("./icons/open.png") , "Open OFF Mesh" , "Open OFF Mesh" , parent , this , SLOT(open_OFF_mesh()) );






#endif // QSMARTACTION_H
