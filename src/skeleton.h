#ifndef SQUELETON_H
#define SQUELETON_H

#include "Mesh.h"
#include "node.h"
#include <vector>

struct DVect {
  double val;
  point3d vect;
  DVect() : val(0), vect(point3d(0.0f, 0.0f, 0.0f)) {}
  DVect(double d, point3d p) : val(d), vect(p) {}
};

class Skeleton {
public:
  Mesh hullMesh;

  Skeleton(Sphere *sphere = new Sphere());
  ~Skeleton();

  void stitching();
  inline Node *getRoot() const { return root; }
  inline int getSubdivisionLevel() const { return subdivisionLevel; }

  void draw(const uint selectedId) const;
  void drawWithNames() const;
  void interpolate(bool constantDistance = true, int spheresPerEdge = 1,
                   float spheresPerUnit = 0.5);
  Node *find(const uint selectedId) const;

  void drawHull();
  void drawInterpolation() const;
  void generateRandom();
  void generateStar();
  void generateAnimal(int numSph = 10);

  vector<Triangle> convexHull(vector<point3d> points);
  DVect getScalarField(point3d pt, float T = 0.3, float alpha = 1.5);
  double F(point3d xt, double k1, double k2, double Itarget, float T = 0.3,
           float alpha = 1.5);
  void evolve(double Itarget, float T = 0.3, float alpha = 1.5,
              float errorThreshold = 1);

  int countNode(Node *node, int nb = 0);
  double getMinRadius(Node *node,
                      double rad); // typically initialize with root and the
                                   // radius of root's sphere
  void clear();                    // clear everything to start from scratch
  void init(); // get a (very) simple skeleton, with one sphere, to begin with

private:
  Node *root;
  int subdivisionLevel = 0; // useful for the evolve process
  vector<Sphere> interSpheres;
  vector<Quadrangle> hull;

  void stitching(Node *node, Quadrangle motherQuad, bool isRoot = false);
  void draw(Node *node, const uint selectedId,
            const bool withName = false) const;
  Node *find(Node *node, const uint selectedId) const;
  void interpolate(Node *node, bool constantDistance = true,
                   int spheresPerEdge = 1, float spheresPerUnit = 1);

  Mesh toMesh(vector<Quadrangle> hull, float threshhold = 0.1);
  DVect getScalarFieldComponent(Node *node, point3d pt, DVect I,
                                float alpha = 1.5);
  DVect calcValGradI(DVect I, point3d pt, Sphere sphere, float alpha);
  void clearHull() {
    hull.clear();
    hullMesh.clear();
    subdivisionLevel = 0;
  }
  void clearInterpolation() { interSpheres.clear(); }

};

#endif // SQUELETON_H
