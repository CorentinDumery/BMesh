#ifndef SQUELETON_H
#define SQUELETON_H

#include "Mesh.h"
#include "node.h"

class Skeleton {
public:
  Skeleton(const Sphere &sphere = Sphere());
  ~Skeleton();

  Node<Sphere> *getRoot() const { return root; }
  void draw(const uint selectedId) const;
  void drawWithNames() const;
  void interpolate(bool constantDistance = false, int spheresPerEdge = 1,
                   float spheresPerUnit = 1);

private:
  void draw(Node<Sphere> *node, const uint selectedId,
            const bool withName = false) const;
  Node<Sphere> *root;
};

#endif // SQUELETON_H
