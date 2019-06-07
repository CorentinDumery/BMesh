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
    glBegin(GL_QUADS);
    for (unsigned int t = 0; t < quadrangles.size(); ++t) {
      point3d const &p0 = vertices[quadrangles[t][0]].p;
      point3d const &p1 = vertices[quadrangles[t][1]].p;
      point3d const &p2 = vertices[quadrangles[t][2]].p;
      point3d const &p3 = vertices[quadrangles[t][3]].p;
      point3d const &n = point3d::cross(p1 - p0, p2 - p0).direction();
      glNormal3f(n[0], n[1], n[2]);
      glVertex3f(p0[0], p0[1], p0[2]);
      glVertex3f(p1[0], p1[1], p1[2]);
      glVertex3f(p2[0], p2[1], p2[2]);
      glVertex3f(p3[0], p3[1], p3[2]);
    }
    glEnd();
  }

  void mergeTriangles(float stopThreshold = 1) {
    // In order to have as many quadrangles as possible,
    // we will merge similar triangles.

    // Similar triangles :
    //   - have similar normal vectors
    //   - adjacent angles are close to 90 degrees (i.e if we merged the
    //   triangles it would look like a rectangle)
    //   - the union of the triangles is quite big
    //
    // We will assign each couple of triangles a scored based on these criteria.

    // parameters
    float normalImportance = 1;
    float angleImportance = 1;
    float areaImportance = 1;

    float maxArea = 0, area; // Computing the maximum area of a triangle so as
                             // to properly compute union size score
    for (int i1 = 0; i1 < triangles.size(); i1++) {
      Triplet t1 = triangles[i1];
      area = ((float)1 / 2) *
             fabs(point3<float>::cross(
                      vertices[t1.corners[0]].p - vertices[t1.corners[1]].p,
                      vertices[t1.corners[0]].p - vertices[t1.corners[2]].p)
                      .norm());
      if (area > maxArea)
        maxArea = area;
    }

    float bestScore = pow(2, 15);

    while (bestScore > stopThreshold && !triangles.empty()) {
      int best1 = -1, best2 = -1;
      Quadruplet futureQuad;
      bestScore = 0;
      for (int i1 = 0; i1 < triangles.size() - 1; i1++) {
        Triplet t1 = triangles[i1];
        for (int i2 = i1 + 1; i2 < triangles.size(); i2++) {
          Triplet t2 = triangles[i2];
          // Are these two triangles neighbors ?

          int v1, v2, diff1, diff2;
          int common = 0;
          for (auto i : t1.corners) {
            bool matched = false;
            for (auto j : t2.corners) {
              if (i == j) {
                if (common == 0) {
                  v1 = i;
                  common++;
                  matched = true;
                }
                if (common == 1 && i != v1) {
                  v2 = i;
                  common++;
                  matched = true;
                }
              }
            }
            if (!matched)
              diff1 = i;
          }

          if (common < 2) {
            continue;
          }
          if (common > 2) {
            cout << "Warning : mergeTriangles was given the same triangle twice"
                 << endl;
            continue;
          }

          for (auto i : t2.corners)
            if (i != v1 && i != v2)
              diff2 = i;

          float score = 0;
          point3d x1 = vertices[t1.corners[0]].p;
          point3d y1 = vertices[t1.corners[1]].p;
          point3d z1 = vertices[t1.corners[2]].p;

          point3d x2 = vertices[t2.corners[0]].p;
          point3d y2 = vertices[t2.corners[1]].p;
          point3d z2 = vertices[t2.corners[2]].p;

          point3d normal1 = point3<float>::cross(x1 - y1, x1 - z1);
          point3d normal2 = point3<float>::cross(x2 - y2, x2 - z2);
          normal1.normalize();
          normal2.normalize();
          score += fabs(point3d::dot(normal1, normal2)) * normalImportance;
          // Remark : this may favor merging triangles with opposite
          // normals

          float angle1 = acos(point3d::dot(vertices[v1].p - vertices[diff1].p,
                                           vertices[v1].p - vertices[diff2].p) /
                              ((vertices[v1].p - vertices[diff1].p).norm() *
                               (vertices[v1].p - vertices[diff2].p).norm()));
          float angle2 = acos(point3d::dot(vertices[v2].p - vertices[diff1].p,
                                           vertices[v2].p - vertices[diff2].p) /
                              ((vertices[v2].p - vertices[diff1].p).norm() *
                               (vertices[v2].p - vertices[diff2].p).norm()));
          score += angleImportance * (1 - fabs((angle1 + angle2 - 3.1415)));

          area = ((float)1 / 4) *
                 fabs(point3<float>::cross(x1 - y1, x1 - z1).norm()) *
                 fabs(point3<float>::cross(x1 - y1, x1 - z1).norm());
          score += areaImportance * area / (maxArea * maxArea);

          if (score > bestScore) {
            bestScore = score;
            best1 = i1;
            best2 = i2;
            for (int z = 0; z < 3; z++) { //finding the counter-clockwise order
              if ((triangles[i1][z] == v1 || triangles[i1][z] == v2) &&
                  (triangles[i1][(z + 1) % 3] == v1 ||
                   triangles[i1][(z + 1) % 3] == v2))
                futureQuad = {triangles[i1][z], diff2,
                              triangles[i1][(z + 1) % 3], diff1};
            }
          }
        }
      }
      if (bestScore < stopThreshold)
        break;
      quadrangles.push_back(futureQuad);

      triangles.erase(triangles.begin() + best2);
      triangles.erase(triangles.begin() + best1);

    } // end of while (bestScore > threshold)
  }
};

class Quadrangle {
public:
  point3d a, b, c, d;
  Quadrangle(point3d a, point3d b, point3d c, point3d d)
      : a(a), b(b), c(c), d(d) {}
};
class Triangle { // triplet of point3d, 3D triangle
public:
  point3d a, b, c;
  Triangle(point3d a, point3d b, point3d c) : a(a), b(b), c(c) {}
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

  point3d getCenter() const { return center; }

  point3d center;
  double radius;

  friend ostream &operator<<(ostream &os, const Sphere &sphere) {
    return os << "{ centre: (" << sphere.center.x() << " , "
              << sphere.center.y() << " , " << sphere.center.z() << ")    "
              << "radius: " << sphere.radius << " }";
  }
};

#endif // PROJECTMESH_H
