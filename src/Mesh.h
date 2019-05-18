#ifndef PROJECTMESH_H
#define PROJECTMESH_H

#include "point3.h"
#include <gl/GLUtilityMethods.h>
#include <vector>

using namespace std;

struct Vertex {
  point3d p;
  Vertex() {}
  Vertex(double x, double y, double z) : p(x, y, z) {}
  double &operator[](unsigned int c) { return p[c]; }
  double operator[](unsigned int c) const { return p[c]; }
};
struct Triangle {
  unsigned int corners[3];
  unsigned int &operator[](unsigned int c) { return corners[c]; }
  unsigned int operator[](unsigned int c) const { return corners[c]; }
  unsigned int size() const { return 3; }
};
struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<Triangle> triangles;
  void clear() {
    vertices.clear();
    triangles.clear();
  }
};

class Sphere {
public:
  Sphere(point3d center = point3d(0, 0, 0), double radius = 1.0)
      : center(center), radius(radius) {}

  void draw() const {
    // TODO: aptimal slice, what is exactly ?
    BasicGL::drawSphere(center.x(), center.y(), center.z(), radius,
                        BasicGL::optimalSlices(radius, 0.5f),
                        BasicGL::optimalStacks(radius, 0.5f));
  }

  point3d center;
  double radius;

  friend ostream &operator<<(ostream &os, const Sphere &sphere) {
    return os << "{ centre: (" << sphere.center.x() << " , "
              << sphere.center.y() << " , " << sphere.center.z() << ")    "
              << "radius: " << sphere.radius << " }";
  }
};

#endif // PROJECTMESH_H
