#include "sphereedit.h"
#include "point3.h"
#include "ui_sphereedit.h"

SphereEdit::SphereEdit(QWidget *parent)
    : QWidget(parent), ui(new Ui::SphereEdit) {
  const double MAX_COORDINATE = 10.0;
  QDoubleValidator *validator =
      new QDoubleValidator(-MAX_COORDINATE, MAX_COORDINATE, 1, this);
  ui->setupUi(this);
  ui->xEditLine->setValidator(validator);
  ui->yEditLine->setValidator(validator);
  ui->zEditLine->setValidator(validator);
  ui->radiusEditLine->setValidator(validator);

  connect(ui->addButton, SIGNAL(released()), this, SLOT(handleAddButton()));
}

SphereEdit::~SphereEdit() { delete ui; }

void SphereEdit::handleAddButton() const {
  double x = ui->xEditLine->text().toDouble();
  double y = ui->yEditLine->text().toDouble();
  double z = ui->zEditLine->text().toDouble();
  double radius = ui->radiusEditLine->text().toDouble();
  // TODO : add validation

  Sphere* sphere = new Sphere(point3d(x, y, z), radius);

  emit addNewSphere(sphere);
}
