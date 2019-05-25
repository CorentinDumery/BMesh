#include "skeleton.h"

Skeleton::Skeleton(const Sphere &sphere) : root(new Node<Sphere>(sphere)) {
  // TODO: attention hardoceded
  root->addChild(Sphere(point3d(0, 6, 0), 1));
  root->getChildren()[0]->addChild(Sphere(point3d(3, 6, 0), 1.5));
  root->getChildren()[0]->addChild(Sphere(point3d(-3, 6, 0), 1.5));
}

Skeleton::~Skeleton() { delete root; }

void Skeleton::draw(const uint selectedId) const { draw(root, selectedId); }

void Skeleton::drawWithNames() const {
  // The selected id is 0, because drawing with names don't care about the color.
  draw(root, 0, true);
}

void Skeleton::draw(Node<Sphere> *node, const uint selectedId,
                    const bool withName) const {
  const Sphere *sphere = &node->getValue();

  if (withName) {
    sphere->drawWithName();
  } else
    sphere->draw(selectedId == sphere->getId());
  for (auto child : node->getChildren()) {
    // Draw the bone
    BasicGL::drawLine(sphere->center, child->getValue().center);
    draw(child, selectedId, withName);
  }
}

void Skeleton::interpolate(bool constantDistance, int spheresPerEdge,
                           float spheresPerUnit) {
  // TODO: not only root's children

  // When it comes to interpolation, we have different options.
  //  1) Constant number of new spheres between every linked spheres
  //  2) Constant number of new spheres on a given distance, i.e. number
  //     based on the distance between two given spheres

  int newspheres = 0;
  point3d p1 = root->getValue().center;
  for (auto child : root->getChildren()) {
    point3d p2 = child->getValue().center;
    int spheresToAdd;
    if (constantDistance) { // Mode 2)
      float distance = (p2 - p1).norm();
      spheresToAdd = (int)(distance / spheresPerUnit);
    } else
      spheresToAdd = spheresPerEdge; // Mode 1)
    for (int i = 1; i < spheresToAdd + 1; i++) {
      float lambda = (float)i / (spheresToAdd + 1);
      point3d newp = lambda * p1 + (1 - lambda) * p2;
      double newr = lambda * root->getValue().radius +
                    (1 - lambda) * child->getValue().radius;
      root->addChild(Sphere(newp, newr));
      newspheres++;
    }
  }
  cout << "Interpolation added " << newspheres << " new sphere(s)." << endl;
}
