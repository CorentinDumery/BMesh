#ifndef UTILITY_H
#define UTILITY_H

#include "point3.h"
#include <QGLViewer/qglviewer.h>
#include <iostream>
using namespace std;

inline float computeAngle(point3d p1, point3d p2) {
  if (p1.norm() == 0 || p2.norm() == 0) {
    cout << "Error : angle cannot be computed" << endl;
    return 0;
  }
  return acos(point3d::dot(p1, p2) / (p1.norm() * p2.norm()));
}

inline point3d projectOntoPlane(point3d vertex, point3d origin,
                                point3d normal) {
  // returns projection of vertex on the plane defined by origin and normal
  point3d vec = vertex - origin;
  float dist = point3d::dot(vec, normal);
  return vertex - dist * normal;
}

#endif // UTILITY_H
