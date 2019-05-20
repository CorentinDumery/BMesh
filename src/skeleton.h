#ifndef SQUELETON_H
#define SQUELETON_H

#include "Mesh.h"
#include "node.h"
#include <vector>

class Skeleton {
public:
  Skeleton(Sphere *sphere = new Sphere());
  ~Skeleton();

  inline Node *getRoot() const { return root; }
  void draw(const uint selectedId) const;
  void drawWithNames() const;
  void interpolate(bool constantDistance = false, int spheresPerEdge = 1,
                   float spheresPerUnit = 1);
  Node *find(const uint selectedId) const;

  void clearHull() { hull.clear(); }
  void drawHull();

private:
  void draw(Node *node, const uint selectedId,
            const bool withName = false) const;
  Node *find(Node *node, const uint selectedId) const;
  Node *root;
  vector<Quadrangle> hull;
  bool hullCalculated=false;
};

#endif // SQUELETON_H
