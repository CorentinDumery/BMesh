#ifndef SPHEREEDIT_H
#define SPHEREEDIT_H

#include "Mesh.h"
#include "node.h"
#include <QWidget>

namespace Ui {
class SphereEdit;
}

class SphereEdit : public QWidget {
  Q_OBJECT

public:
  explicit SphereEdit(QWidget *parent = 0);
  ~SphereEdit();

private:
  Ui::SphereEdit *ui;
  Node *node = nullptr;
  point3d getPoint3d() const;
  double getRadius() const;

private slots:
  void handleAddButton() const;
  void handleEditButton() const;

public slots:
  void updateSelection(Node *node);
};

#endif // SPHEREEDIT_H
