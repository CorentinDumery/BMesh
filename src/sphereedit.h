#ifndef SPHEREEDIT_H
#define SPHEREEDIT_H

#include "Mesh.h"
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

private slots:
  void handleAddButton() const;

signals:
  void addNewSphere(Sphere *sphere) const;
};

#endif // SPHEREEDIT_H
