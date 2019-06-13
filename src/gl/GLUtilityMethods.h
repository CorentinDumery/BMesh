#ifndef GLUTILITYMETHODS_H
#define GLUTILITYMETHODS_H

#include <QGLViewer/qglviewer.h>

#include "BasicColors.h"
#include "point3.h"

namespace RGB {
void calc_RGB(float val, float val_min, float val_max, float &r, float &g,
              float &b);
void get_RGB_from_HSV(float &r, float &g, float &b, float H, float S, float V);
void get_random_RGB_from_HSV(float &r, float &g, float &b);
void get_random_RGB_from_HSV(float &r, float &g, float &b, float H);
void fromLightGrayToRed(float &r, float &g, float &b, float val,
                        float greyValue = 0.75f, float maxSat = 0.8f);
void fromLightGrayToBlue(float &r, float &g, float &b, float val,
                         float greyValue = 0.75f, float maxSat = 0.8f);
} // namespace RGB

namespace TriangleCoverage {
extern float weights15[15][3];
extern float weights45[45][3];
void coutBasisFunctions(unsigned int subdiv);

unsigned int nElements(unsigned int N_splits_on_each_edge);
void getBarycentricCoordinates(unsigned int N_splits_on_each_edge,
                               unsigned int e, float &x, float &y, float &z);
} // namespace TriangleCoverage

namespace BasicGL {
void drawLine(const point3d &initPoint, const point3d &finalPoint);
void drawSphere(float x, float y, float z, float radius, int slices,
                int stacks);

int optimalSlices(float radius, float referenceRadius);
int optimalStacks(float radius, float referenceRadius);

template <class point_t>
void glBox(point_t const &b0, point_t const &b1, point_t const &b2,
           point_t const &b3, point_t const &b4, point_t const &b5,
           point_t const &b6, point_t const &b7) {
  // bottom :
  glVertex(b0);
  glVertex(b1);
  glVertex(b2);
  glVertex(b3);

  // top:
  glVertex(b4);
  glVertex(b5);
  glVertex(b6);
  glVertex(b7);

  // front:
  glVertex(b0);
  glVertex(b1);
  glVertex(b5);
  glVertex(b4);

  // back:
  glVertex(b2);
  glVertex(b3);
  glVertex(b7);
  glVertex(b6);

  // left:
  glVertex(b0);
  glVertex(b4);
  glVertex(b7);
  glVertex(b3);

  // right:
  glVertex(b1);
  glVertex(b2);
  glVertex(b6);
  glVertex(b5);
}
} // namespace BasicGL

namespace GLTools {
void initLights();
void setSunsetLight();
void setSunriseLight();
void setSingleSpotLight();
void setDefaultMaterial();
void setInverseDefaultMaterial();
void SetDiffuse(float r, float g, float b, float alpha);
void SetAmbient(float r, float g, float b, float alpha);
void setDefaultColor();
void setSelectedColor();

void color4(unsigned int c_id);
} // namespace GLTools

namespace GLCheck {
int checkErrors(std::string const &szFile, int iLine);
}

#endif // GLUTILITYMETHODS_H
