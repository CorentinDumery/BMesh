#include "sphereedit.h"
#include "mediator.h"
#include "point3.h"
#include "ui_sphereedit.h"

SphereEdit::SphereEdit(QWidget *parent)
    : QWidget(parent), ui(new Ui::SphereEdit) {
  const double MAX_COORDINATE = 10.0;
  /*QDoubleValidator *validator =
      new QDoubleValidator(-MAX_COORDINATE, MAX_COORDINATE, 1, this);
  ui->setupUi(this);
  ui->xEditLine->setValidator(validator);
  ui->yEditLine->setValidator(validator);
  ui->zEditLine->setValidator(validator);
  ui->radiusEditLine->setValidator(validator);*/

  connect(ui->addButton, SIGNAL(released()), this, SLOT(handleAddButton()));
  connect(ui->editButton, SIGNAL(released()), this, SLOT(handleEditButton()));
}

SphereEdit::~SphereEdit() { delete ui; }

point3d SphereEdit::getPoint3d() const {
  // TODO : add validation
  double x = ui->xEditLine->text().toDouble();
  double y = ui->yEditLine->text().toDouble();
  double z = ui->zEditLine->text().toDouble();
  return point3d(x, y, z);
}

double SphereEdit::getRadius() const {
  // TODO : add validation
  return ui->radiusEditLine->text().toDouble();
}

void SphereEdit::handleAddButton() const {
  Sphere *sphere = new Sphere(getPoint3d(), getRadius());
  node->addChild(sphere);
  Mediator::getInstance()->updateViewer();
}

void SphereEdit::handleEditButton() const {
  node->editSphere(getPoint3d(), getRadius());
  Mediator::getInstance()->updateViewer();
}

void SphereEdit::updateSelection(Node *node) {
  // No selected sphere
  if (node == nullptr) {
    ui->editButton->setEnabled(false);
    ui->addButton->setEnabled(false);
    ui->xEditLine->clear();
    ui->yEditLine->clear();
    ui->zEditLine->clear();
    ui->radiusEditLine->clear();
    return;
  }

  // A sphere is selected
  const Sphere *sphere = node->getValue();
  this->node = node;
  ui->editButton->setEnabled(true);
  ui->addButton->setEnabled(true);
  ui->xEditLine->setText(QString::number(sphere->center.x()));
  ui->yEditLine->setText(QString::number(sphere->center.y()));
  ui->zEditLine->setText(QString::number(sphere->center.z()));
  ui->radiusEditLine->setText(QString::number(sphere->radius));
}
