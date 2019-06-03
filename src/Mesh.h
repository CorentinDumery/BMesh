#ifndef PROJECTMESH_H
#define PROJECTMESH_H

#include "point3.h"
#include "utility.h"
#include <gl/GLUtilityMethods.h>
#include <queue>
#include <vector>

using namespace std;

struct Vertex {
  point3d p;
  Vertex() {}
  Vertex(double x, double y, double z) : p(x, y, z) {}
  double &operator[](unsigned int c) { return p[c]; }
  double operator[](unsigned int c) const { return p[c]; }
};
struct Triplet {
  unsigned int corners[3];
  unsigned int &operator[](unsigned int c) { return corners[c]; }
  unsigned int operator[](unsigned int c) const { return corners[c]; }
  unsigned int size() const { return 3; }
};
struct Quadruplet {
    unsigned int corners[4];
    unsigned int &operator[](unsigned int c) { return corners[c]; }
    unsigned int operator[](unsigned int c) const { return corners[c]; }
    unsigned int size() const { return 4; }

};
struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<Triplet> triangles;
  vector<Quadruplet> quadrangles;
  void clear() {
    vertices.clear();
    triangles.clear();
  }
  void draw() {
    glBegin(GL_TRIANGLES);
    for (unsigned int t = 0; t < triangles.size(); ++t) {
      point3d const &p0 = vertices[triangles[t][0]].p;
      point3d const &p1 = vertices[triangles[t][1]].p;
      point3d const &p2 = vertices[triangles[t][2]].p;
      point3d const &n = point3d::cross(p1 - p0, p2 - p0).direction();
      glNormal3f(n[0], n[1], n[2]);
      glVertex3f(p0[0], p0[1], p0[2]);
      glVertex3f(p1[0], p1[1], p1[2]);
      glVertex3f(p2[0], p2[1], p2[2]);
    }
    glEnd();
  }
};

class Quadrangle {
public:
  point3d a,b,c,d;
  Quadrangle(point3d a, point3d b, point3d c, point3d d)
      : a(a), b(b), c(c), d(d) {}
};
class Triangle { //triplet of point3d, 3D triangle
public:
  point3d a,b,c;
  Triangle(point3d a, point3d b, point3d c)
      : a(a), b(b), c(c) {}
};

class Shape {
public:
  static uint idsCounter;

  Shape() {
    if (avaibleIds.empty()) {
      id = idsCounter;
      idsCounter++;
    } else {
      id = avaibleIds.front();
      avaibleIds.pop();
    }
  }

  void draw(const bool selected = false) const {
    if (selected)
      setSelectedColor();
    else
      setDefaultColor();
  }

  Shape(const Shape &) : Shape() {}
  uint getId() const { return id; }
  ~Shape() { avaibleIds.push(id); }

protected:
  uint id;

private:
  static queue<uint> avaibleIds;
};

class Sphere : public Shape {
public:
  Sphere(point3d center = point3d(0, 0, 0), double radius = 1.0)
      : center(center), radius(radius) {}

  void draw(const bool selected = false) const {
    Shape::draw(selected);

    // TODO: aptimal slice, what is exactly ?
    BasicGL::drawSphere(center.x(), center.y(), center.z(), radius,
                        BasicGL::optimalSlices(radius, 0.5f),
                        BasicGL::optimalStacks(radius, 0.5f));
  }

  void drawWithName() const {
    glPushName(id);
    draw();
    glPopName();
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
