#ifndef UTILITY_H
#define UTILITY_H

#include "point3.h"
#include <QGLViewer/qglviewer.h>
#include <iostream>
using namespace std;

inline void setDefaultColor() { glColor3f(0, 0.5, 0); }

inline void setSelectedColor() { glColor3f(1.0, 0.5, 0); }

inline float computeAngle(point3d p1, point3d p2) {
  if (p1.norm()==0 || p2.norm()==0 ) {
      cout << "Error : angle cannot be computed" <<endl;
      return 0;
  }
  return acos(point3d::dot(p1, p2) / (p1.norm() * p2.norm()));
}

#endif // UTILITY_H
