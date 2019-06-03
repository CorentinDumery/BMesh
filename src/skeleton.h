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
  void clearInterpolation(){ interSpheres.clear() ; }
  void drawHull();
  void drawInterpolation() const;
  void generateRandom();
  void generateAnimal(int numSph=10);

  vector<Triplet> convexHull(vector<point3d> points);

private:
  void stitching(Node *node, Quadriplet motherQuad,
                 bool isRoot = false);
  void draw(Node *node, const uint selectedId,
            const bool withName = false) const;
  Node *find(Node *node, const uint selectedId) const;
  Node *root;
  void interpolate(Node *node, bool constantDistance = true,
                   int spheresPerEdge = 1, float spheresPerUnit = 1);
  vector<Sphere> interSpheres;
  vector<Quadriplet> hull;
  bool hullCalculated = false;
  Mesh toMesh(vector<Quadriplet> hull,float threshhold = 0.001);
};

#endif // SQUELETON_H
