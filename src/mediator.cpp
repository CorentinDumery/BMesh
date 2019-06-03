#include "mediator.h"

Mediator *Mediator::instance = nullptr;

Mediator::Mediator() : QObject(nullptr) {}

Mediator *Mediator::getInstance() {
  if (!instance)
    instance = new Mediator;
  return instance;
}
