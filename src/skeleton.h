#ifndef SQUELETON_H
#define SQUELETON_H

#include "Mesh.h"
#include "node.h"

class Skeleton {
public:
  Skeleton(const Sphere &sphere = Sphere());
  ~Skeleton();

  Node<Sphere> *getRoot() const { return root; }
  void draw() const;

private:
  Node<Sphere> *root;
};

#endif // SQUELETON_H
