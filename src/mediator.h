#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QObject>

class Mediator : public QObject {
  Q_OBJECT

public:
  static Mediator *getInstance();

signals:
  void updateViewer();

private:
  static Mediator *instance;
  Mediator();
};

#endif // MEDIATOR_H
