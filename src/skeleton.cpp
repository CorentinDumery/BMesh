#include "skeleton.h"

Skeleton::Skeleton(Sphere *sphere) : root(new Node(sphere)) {
  // TODO: attention hardoceded
  root->addChild(Sphere(point3d(0, -2, -2), 0.75));
  root->addChild(Sphere(point3d(0, -2, 2), 0.75));
  root->getChildren()[0]->addChild(Sphere(point3d(0, -6, -2), 0.5));
  root->getChildren()[1]->addChild(Sphere(point3d(0, -6, +2), 0.5));
  root->addChild(Sphere(point3d(0, 4, 0), 1));
  root->getChildren()[2]->addChild(Sphere(point3d(0, 7, 0), 0.75));
  root->getChildren()[2]->addChild(Sphere(point3d(2, 6, -4), 0.5));
  root->getChildren()[2]->addChild(Sphere(point3d(2, 6, +4), 0.5));
}

Skeleton::~Skeleton() { delete root; }

void Skeleton::draw(const uint selectedId) const { draw(root, selectedId); }

void Skeleton::drawWithNames() const {
  // The selected id is 0, because drawing with names don't care about the
  // color.
  draw(root, 0, true);
}

void Skeleton::draw(Node *node, const uint selectedId,
                    const bool withName) const {
  const Sphere *sphere = node->getValue();

  if (withName) {
    sphere->drawWithName();
  } else
    sphere->draw(selectedId == sphere->getId());
  for (auto child : node->getChildren()) {
    // Draw the bone
    BasicGL::drawLine(sphere->center, child->getValue()->center);
    draw(child, selectedId, withName);
  }
}

void Skeleton::drawInterpolation() const {
  for (auto sphere : interSpheres)
    sphere.draw();
}

Node *Skeleton::find(const uint selectedId) const {
  return find(root, selectedId);
}

Node *Skeleton::find(Node *node, const uint selectedId) const {
  if (node->getValue()->getId() == selectedId)
    return node;
  for (auto child : node->getChildren()) {
    Node *tempNode = find(child, selectedId);
    if (tempNode->getValue()->getId() == selectedId)
      return tempNode;
  }
}

void Skeleton::interpolate(bool constantDistance, int spheresPerEdge,
                           float spheresPerUnit) {
  interSpheres.clear();
  interpolate(getRoot(), constantDistance, spheresPerEdge, spheresPerUnit);
}

void Skeleton::interpolate(Node<Sphere> *node, bool constantDistance,
                           int spheresPerEdge, float spheresPerUnit) {

  // When it comes to interpolation, we have different options.
  //  1) Constant number of new spheres between every linked spheres
  //  2) Constant number of new spheres on a given distance, i.e. number
  //     based on the distance between two given spheres

  int newspheres = 0;
  point3d p1 = root->getValue()->center;
  for (auto child : root->getChildren()) {
    point3d p2 = child->getValue()->center;
    int spheresToAdd;
    if (constantDistance) { // Mode 2)
      float distance = (p2 - p1).norm();
      spheresToAdd = (int)(distance / spheresPerUnit);
    } else
      spheresToAdd = spheresPerEdge; // Mode 1)
    for (int i = 1; i < spheresToAdd + 1; i++) {
      float lambda = (float)i / (spheresToAdd + 1);
      point3d newp = lambda * p1 + (1 - lambda) * p2;
      // TODO : When the interpolate spheres won't be a node make sure to delete
      // it to avoid memory leak
      double newr = lambda * root->getValue()->radius +
                    (1 - lambda) * child->getValue()->radius;
      interSpheres.push_back(Sphere(newp, newr));
      newspheres++;
    }

    interpolate(child, constantDistance, spheresPerEdge, spheresPerUnit);
  }
}

void Skeleton::sweeping() {
  interpolate();
  clearHull();
  sweeping(root);
  hullCalculated = true;
}

void Skeleton::sweeping(Node<Sphere> *node) {

  point3d p1 = node->getValue().center;
  double r1 = node->getValue().radius;
  int n = 0;
  int addedSections = 0;

  for (auto child : node->getChildren()) {

    point3d p2 = child->getValue().center;
    double r2 = child->getValue().radius;
    point3d boneVector = p2 - p1;
    point3d x = boneVector; // first axis parallel to the bone
    point3d y, z;
    if (fabs(x.x()) > 0.01 || fabs(x.y()) > 0.01) {
      y = point3<float>::cross(x, point3d(0, 0, 1));
    } else { // then x=(0,0,1)
      y = point3d(0, 1, 0);
    }
    z = point3<float>::cross(x, y);
    x.normalize();
    y.normalize();
    z.normalize();

    point3d a, b, c, d;

    a = p1 + r1 * y + r1 * z + r1 * x;
    b = p1 - r1 * y + r1 * z + r1 * x;
    c = p1 - r1 * y - r1 * z + r1 * x;
    d = p1 + r1 * y - r1 * z + r1 * x;

    point3d ap = p2 + r2 * y + r2 * z - r2 * x;
    point3d bp = p2 - r2 * y + r2 * z - r2 * x;
    point3d cp = p2 - r2 * y - r2 * z - r2 * x;
    point3d dp = p2 + r2 * y - r2 * z - r2 * x;

    // hull.push_back(Quadrangle(a, b, c, d));
    // hull.push_back(Quadrangle(ap, bp, cp, dp));
    hull.push_back(Quadrangle(a, ap, bp, b));
    hull.push_back(Quadrangle(b, bp, cp, c));
    hull.push_back(Quadrangle(c, cp, dp, d));
    hull.push_back(Quadrangle(d, dp, ap, a));

    addedSections++;
    Sphere s1 = node->getValue();
    s1.addNeighbor(Quadrangle(a, b, c, d));
    Sphere s2 = child->getValue();
    s2.neighborSquares.push_back(Quadrangle(ap, bp, cp, dp));

    sweeping(child);

    n++;
  }
}

void Skeleton::drawHull() {
  if (hullCalculated) {
    glBegin(GL_QUADS);
    for (unsigned int t = 0; t < hull.size(); ++t) {
      point3d const &p0 = hull[t].a;
      point3d const &p1 = hull[t].b;
      point3d const &p2 = hull[t].c;
      point3d const &p3 = hull[t].d;
      point3d const &n = point3d::cross(p1 - p0, p2 - p0).direction();
      glNormal3f(n[0], n[1], n[2]);
      glVertex3f(p0[0], p0[1], p0[2]);
      glVertex3f(p1[0], p1[1], p1[2]);
      glVertex3f(p2[0], p2[1], p2[2]);
      glVertex3f(p3[0], p3[1], p3[2]);
    }
    glEnd();
  }
}
