#ifndef PROJECTMESH_H
#define PROJECTMESH_H

#include "point3.h"
#include "utility.h"
#include <cmath>
#include <gl/GLUtilityMethods.h>
#include <queue>
#include <vector>

using namespace std;

struct Vertex {
  point3d p;
  Vertex() {}
  Vertex(double x, double y, double z) : p(x, y, z) {}
  Vertex(point3d p) : p(p) {}
  double &operator[](unsigned int c) { return p[c]; }
  double operator[](unsigned int c) const { return p[c]; }
  bool operator==(const Vertex &v) const {
    const double EPSILON = 0.00001;
    return (abs(this->p.x() - v.p.x()) < EPSILON) &&
           (abs(this->p.y() - v.p.y()) < EPSILON) &&
           (abs(this->p.z() - v.p.z()) < EPSILON);
  }
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
class Mesh {
public:
  static Mesh generateCube(double edgeLength) {
    Mesh cube;
    cube.vertices = {
        // Front
        Vertex(-edgeLength, edgeLength, edgeLength),
        Vertex(edgeLength, edgeLength, edgeLength),
        Vertex(edgeLength, -edgeLength, edgeLength),
        Vertex(-edgeLength, -edgeLength, edgeLength),

        // Back
        Vertex(-edgeLength, edgeLength, -edgeLength),
        Vertex(edgeLength, edgeLength, -edgeLength),
        Vertex(edgeLength, -edgeLength, -edgeLength),
        Vertex(-edgeLength, -edgeLength, -edgeLength),
    };
    cube.quadrangles = {{0, 3, 2, 1}, {4, 5, 6, 7}, {1, 2, 6, 5},
                        {0, 4, 7, 3}, {0, 1, 5, 4}, {3, 7, 6, 2}};
    return cube;
  }

  std::vector<Vertex> vertices;
  std::vector<Triplet> triangles;
  vector<Quadruplet> quadrangles;
  vector<point3d> normals;
  vector<vector<int>> neighborsId;
  vector<map<int, float>> cotangentWeights;
  vector<float> curvatures;
  vector<float> surroundingAreas;
  bool showCurvature = false;

  void clear() {
    vertices.clear();
    triangles.clear();
    quadrangles.clear();
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
      if (showCurvature)
        glColor3f(curvatures[quadrangles[t][0]], 0.5,
                  curvatures[quadrangles[t][0]]);
      glVertex3f(p0[0], p0[1], p0[2]);
      if (showCurvature)
        glColor3f(curvatures[quadrangles[t][1]], 0.5,
                  curvatures[quadrangles[t][1]]);
      glVertex3f(p1[0], p1[1], p1[2]);
      if (showCurvature)
        glColor3f(curvatures[quadrangles[t][2]], 0.5,
                  curvatures[quadrangles[t][2]]);
      glVertex3f(p2[0], p2[1], p2[2]);
      if (showCurvature)
        glColor3f(curvatures[quadrangles[t][3]], 0.5,
                  curvatures[quadrangles[t][3]]);
      glVertex3f(p3[0], p3[1], p3[2]);
    }
    glEnd();
  }

  void computeNormals() {
    // TODO improve accuracy of this function
    normals.resize(vertices.size(), point3d(0, 0, 0));
    for (auto tri : triangles) {
      point3d n = point3<float>::cross(
          vertices[tri.corners[0]].p - vertices[tri.corners[1]].p,
          vertices[tri.corners[0]].p - vertices[tri.corners[2]].p);
      n.normalize();
      for (auto i : tri.corners) {
        normals[i] += n;
      }
    }
    for (auto quad : quadrangles) {
      point3d n = point3<float>::cross(
          vertices[quad.corners[0]].p - vertices[quad.corners[1]].p,
          vertices[quad.corners[0]].p - vertices[quad.corners[2]].p);
      n.normalize();
      for (auto i : quad.corners) {
        normals[i] += n;
      }
    }
    for (int i = 0; i < normals.size(); i++) {
      normals[i].normalize();
    }
  }

  void drawNormals() {
    for (int i = 0; i < normals.size(); i++) {
      point3d z = point3d::cross(normals[i], point3d(1, 2.2, 3.1));
      z.normalize();
      z = (z - normals[i]) / 2;
      point3d zp = (-z - normals[i]) / 2;
      z.normalize();
      zp.normalize();
      point3d a = vertices[i].p, b = vertices[i].p + normals[i];
      point3d c = b + z / 5, d = b + zp / 5;
      BasicGL::drawLine(a, b);
      BasicGL::drawLine(c, b);
      BasicGL::drawLine(d, b);
    }
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

    while (bestScore > stopThreshold && triangles.size() > 1) {
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
            for (int z = 0; z < 3; z++) { // finding the counter-clockwise order
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

  void computeSurroundingAreas() {
    surroundingAreas.clear();
    surroundingAreas.resize(vertices.size(), 0);
    for (int i = 0; i < triangles.size(); i++) {
      float a, b, c;
      a = (vertices[triangles[i][0]].p - vertices[triangles[i][1]].p).norm();
      b = (vertices[triangles[i][0]].p - vertices[triangles[i][2]].p).norm();
      c = (vertices[triangles[i][1]].p - vertices[triangles[i][2]].p).norm();
      // Heron's formula
      float s = (a + b + c) / 2;
      float area = sqrt(s * (s - a) * (s - b) * (s - c));
      // This is an approximation of Voronoi's area.
      surroundingAreas[triangles[i][0]] += area / 3;
      surroundingAreas[triangles[i][1]] += area / 3;
      surroundingAreas[triangles[i][2]] += area / 3;
    }
    for (int i = 0; i < quadrangles.size(); i++) {
      // Also an approximation
      float area =
          (vertices[quadrangles[i][0]].p - vertices[quadrangles[i][1]].p)
              .norm() *
          (vertices[quadrangles[i][0]].p - vertices[quadrangles[i][3]].p)
              .norm();
      surroundingAreas[quadrangles[i][0]] += area / 4;
      surroundingAreas[quadrangles[i][1]] += area / 4;
      surroundingAreas[quadrangles[i][2]] += area / 4;
      surroundingAreas[quadrangles[i][3]] += area / 4;
    }
  }

  float computeAngle(point3d p1, point3d p2) {
    if (p1.norm() == 0 || p2.norm() == 0) {
      cout << "Error : angle cannot be computed" << endl;
      return 0;
    }
    return acos(point3d::dot(p1, p2) / (p1.norm() * p2.norm()));
  }

  void computeCurvaturesNorm() {
    // This function computes k1^2 + k2^2 and stores it in "curvatures"

    // "How ?" will you ask me.
    // We will compute :
    //   - the mean curvature H
    //   - the gaussian curvature G
    // Then we will use k1^2 + k2^2 = (2H)^2 - 2G

    if (vertices.size() == 0)
      return;

    computeSurroundingAreas();
    curvatures.clear();
    curvatures.resize(vertices.size(), 0);

    // Gaussian curvature : angle deficit
    // We will temporarily store the angles' sum in curvature

    /* // TODO check : are there still triangles ?
    for (int i = 0; i < triangles.size(); i++) {
      point3d p0 = vertices[triangles[i][0]].p;
      point3d p1 = vertices[triangles[i][1]].p;
      point3d p2 = vertices[triangles[i][2]].p;
      curvatures[triangles[i][0]] += computeAngle(p0 - p1, p0 - p2);
      curvatures[triangles[i][1]] += computeAngle(p1 - p0, p1 - p2);
      curvatures[triangles[i][2]] += computeAngle(p2 - p0, p2 - p1);
    }*/

    for (int i = 0; i < quadrangles.size(); i++) {
      point3d p0 = vertices[quadrangles[i][0]].p;
      point3d p1 = vertices[quadrangles[i][1]].p;
      point3d p2 = vertices[quadrangles[i][2]].p;
      point3d p3 = vertices[quadrangles[i][3]].p;
      curvatures[quadrangles[i][0]] += computeAngle(p0 - p1, p0 - p3);
      curvatures[quadrangles[i][1]] += computeAngle(p1 - p0, p1 - p2);
      curvatures[quadrangles[i][2]] += computeAngle(p2 - p1, p2 - p3);
      curvatures[quadrangles[i][3]] += computeAngle(p3 - p0, p3 - p2);
    }

    for (int i = 0; i < curvatures.size(); i++) {
      curvatures[i] = (2 * 3.1416 - curvatures[i]) / surroundingAreas[i];
    }

    // Mean curvature : cotangeant weigths

    computeNormals();
    cotangentWeightsComputation();
    double H;
    for (int i = 0; i < curvatures.size(); i++) {
      H = vertexMeanCurvatureComputation(i, true);
      curvatures[i] =
          pow(2 * H, 2) - 2 * curvatures[i]; // before this line, curvatures[i]
                                             // is the gaussian curvature
    }
  }

  void cotangentWeightsComputation() {

    cotangentWeights.resize(vertices.size());

    for (int i = 0; i < quadrangles.size(); i++) {

      Quadruplet quad = quadrangles[i];
      Triplet t1 = {quad[0], quad[1], quad[3]};
      Triplet t2 = {quad[1], quad[2], quad[3]};

      cotangentWeightComputationForATriangle(t1);
      cotangentWeightComputationForATriangle(t2);
    }

    // TODO check : are there still triangles ?
    //    for (int i = 0; i < triangles.size(); i++) {
    //        cotangentWeightComputationForATriangle(triangles[i]);
    //    }
  }

  void computeNeighbors() {
    neighborsId.clear();
    neighborsId.resize(vertices.size());
    for (int i = 0; i < quadrangles.size(); i++) {
      neighborsId[quadrangles[i][0]].push_back(quadrangles[i][1]);
      neighborsId[quadrangles[i][0]].push_back(quadrangles[i][3]);
      neighborsId[quadrangles[i][1]].push_back(quadrangles[i][0]);
      neighborsId[quadrangles[i][1]].push_back(quadrangles[i][2]);
      neighborsId[quadrangles[i][2]].push_back(quadrangles[i][1]);
      neighborsId[quadrangles[i][2]].push_back(quadrangles[i][3]);
      neighborsId[quadrangles[i][3]].push_back(quadrangles[i][0]);
      neighborsId[quadrangles[i][3]].push_back(quadrangles[i][2]);
    }
    for (int i = 0; i < triangles.size(); i++) {
      neighborsId[triangles[i][0]].push_back(triangles[i][1]);
      neighborsId[triangles[i][0]].push_back(triangles[i][2]);
      neighborsId[triangles[i][1]].push_back(triangles[i][0]);
      neighborsId[triangles[i][1]].push_back(triangles[i][2]);
      neighborsId[triangles[i][2]].push_back(triangles[i][0]);
      neighborsId[triangles[i][2]].push_back(triangles[i][1]);
    }

    for (int i=0;i<neighborsId.size();i++){
        sort( neighborsId[i].begin(), neighborsId[i].end() );
        neighborsId[i].erase( unique( neighborsId[i].begin(), neighborsId[i].end() ), neighborsId[i].end() );
    }
  }

  void fairing() {

    cout << "Fairing" << endl;

    vector<Vertex> newVertices;

    // Replacing all vertices that appear in four quadrangles/triangles

    computeNeighbors();
    computeNormals(); // TODO remove ?
    for (int index = 0; index < vertices.size(); index++) {
      point3d x = vertices[index].p;
      int neighborsCount = neighborsId[index].size();
      cout << neighborsCount << endl;
      if (neighborsCount != 4) {
        newVertices.push_back(vertices[index]);
        continue;
      }
      point3d voisin1 = vertices[neighborsId[index][0]].p,
              voisin2 = vertices[neighborsId[index][1]].p,
              voisin3 = vertices[neighborsId[index][2]].p,
              voisin4 = vertices[neighborsId[index][3]].p;

      float k1 = 0; // TODO
      float k2 = 1;
      point3d ev; // TODO, attention ev doit correspondre à a et c !!
      point3d eu;

      if (k1 != k2 && neighborsCount == 4) {
        point3d a = projectOntoPlane(voisin1, x, normals[index]);
        point3d b = projectOntoPlane(voisin2, x, normals[index]);
        point3d c = projectOntoPlane(voisin3, x, normals[index]);
        point3d d = projectOntoPlane(voisin4, x, normals[index]);

        /*
        float value;
        value = pow(point3d::dot((a - x), ev), 2) +
                pow(point3d::dot((b - x), eu), 2) +
                pow(point3d::dot((c - x), ev), 2) +
                pow(point3d::dot((d - x), eu), 2);
         */

        Vertex v;
        v.p = (a + c) / 4 + (b + d) / 4;
        //v.p = (voisin1+voisin3)
        newVertices.push_back(v);

      } else {
        // TODO try something for these vertices
        newVertices.push_back(vertices[index]);
      }
    }
    vertices = newVertices;
  }

private:
  float cot(point3d u, point3d v) {
    float a = computeAngle(u, v); // gets the angle
    a = 1 / tan(a);               // computes the cotangent
    return a;
  }

  void cotangentWeightComputationForATriangle(Triplet t) {
    point3d x = vertices[t[0]];
    point3d y = vertices[t[1]];
    point3d z = vertices[t[2]];

    // alphas
    cotangentWeights[t[0]][t[1]] += 0.5f * cot(z - x, z - y);
    cotangentWeights[t[1]][t[2]] += 0.5f * cot(x - y, x - z);
    cotangentWeights[t[2]][t[0]] += 0.5f * cot(y - z, y - x);

    // betas
    cotangentWeights[t[0]][t[2]] += 0.5f * cot(y - z, y - x);
    cotangentWeights[t[1]][t[0]] += 0.5f * cot(z - x, z - y);
    cotangentWeights[t[2]][t[1]] += 0.5f * cot(x - y, x - z);
  }

  double vertexMeanCurvatureComputation(int i, bool approx) {

    double m_i = 0;
    float sum_w_ij = 0.f; // sum of the coefficient : useful to reduce noise,
                          // if approximation is wanted.
    for (std::map<int, float>::iterator it = cotangentWeights[i].begin();
         it != cotangentWeights[i].end(); ++it) {
      int j = it->first;       // index of the neighbor of i
      float w_ij = it->second; // weight w_ij
      m_i += w_ij * point3d::dot(vertices[j].p - vertices[i].p, normals[i]);
      sum_w_ij += w_ij;
    }

    if (approx) {
      m_i /= 4 * sum_w_ij;
    } else {
      m_i /= 4 * surroundingAreas[i];
    }

    return m_i;
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
      GLTools::setSelectedColor();
    else
      GLTools::setDefaultColor();
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
  void setCenter(point3d c) { center = c; }

  point3d center;
  double radius;

  friend ostream &operator<<(ostream &os, const Sphere &sphere) {
    return os << "{ centre: (" << sphere.center.x() << " , "
              << sphere.center.y() << " , " << sphere.center.z() << ")    "
              << "radius: " << sphere.radius << " }";
  }
};

#endif // PROJECTMESH_H
