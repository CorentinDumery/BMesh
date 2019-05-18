#include "skeleton.h"

Skeleton::Skeleton(const Sphere &sphere) : root(new Node<Sphere>(sphere)) {
  // TODO: attention hardoceded
  root->addChild(Sphere(point3d(0, 6, 0), 2.5));
}

Skeleton::~Skeleton() { delete root; }

void Skeleton::draw() const {
  // TODO : draw the full tree not only root and its children
  root->getValue().draw();
  for (auto child : root->getChildren())
    child->getValue().draw();
}
