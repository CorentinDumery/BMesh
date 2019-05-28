#ifndef SQUELETON_H
#define SQUELETON_H

#include "Mesh.h"
#include "node.h"
#include <vector>

class Skeleton {
public:
  Skeleton(Sphere *sphere = new Sphere());
  ~Skeleton();

  void stitching();
  inline Node *getRoot() const { return root; }
  void draw(const uint selectedId) const;
  void drawWithNames() const;
  void interpolate(bool constantDistance = false, int spheresPerEdge = 1,
                   float spheresPerUnit = 1);
  Node *find(const uint selectedId) const;

  void clearHull() {
    hull.clear();
    hullCalculated = false;
  }
  void drawHull();
  void drawInterpolation() const;

  vector<Triplet> convexHull(vector<point3d> points);

private:
  void stitching(Node<Sphere> *node, Quadrangle motherQuad,
                 bool isRoot = false);
  void draw(Node *node, const uint selectedId,
            const bool withName = false) const;
  Node *find(Node *node, const uint selectedId) const;
  Node *root;
  void interpolate(Node<Sphere> *node, bool constantDistance = true,
                   int spheresPerEdge = 1, float spheresPerUnit = 1);
  vector<Sphere> interSpheres;
  vector<Quadrangle> hull;
  bool hullCalculated = false;
};

#endif // SQUELETON_H
