#include "skeleton.h"
#define QUICKHULL_IMPLEMENTATION
#include "quickhull.h" //implementation of quick hull
#include <math.h>
#include <random>
#include <stdio.h>

Skeleton::Skeleton(Sphere *sphere) : root(new Node(sphere)) {
  // TODO: attention hardoceded
  root->addChild(new Sphere(point3d(0, -2, -2), 0.75));
  root->addChild(new Sphere(point3d(0, -2, 2), 0.75));
  root->getChildren()[0]->addChild(new Sphere(point3d(0, -6, -2), 0.5));
  root->getChildren()[1]->addChild(new Sphere(point3d(0, -6, +2), 0.5));
  root->addChild(new Sphere(point3d(0, 4, 0), 1));
  root->getChildren()[2]->addChild(new Sphere(point3d(0, 7, 0), 0.75));
  root->getChildren()[2]->addChild(new Sphere(point3d(2, 6, -4), 0.5));
  root->getChildren()[2]->addChild(new Sphere(point3d(2, 6, +4), 0.5));
}

Skeleton::~Skeleton() { delete root; }

void Skeleton::draw(const uint selectedId) const { draw(root, selectedId); }
void Skeleton::generateRandom() {
  srand(time(NULL));

  clearHull();
  clearInterpolation();
  delete root;
  root = new Node(new Sphere(point3d(0, 0, 0), 1.5));

  auto genP = [](float c = 1, float offset = 0) {
    return c * ((float)(random() % 1800)) / 100 - c * 9;
  };

  for (int i = 0; i < 10; i++) {
    if (random() % 3 == 0) {
      root->addChild(new Sphere(point3d(genP(), genP(), genP()),
                                (random() % 200) / 100 + 0.4));
    }
    for (auto child : root->getChildren()) {
      if (random() % 15 == 0) {
        child->addChild(new Sphere(point3d(genP(0.5), genP(0.5), genP(0.5)) +
                                       child->getValue()->center,
                                   (random() % 200) / 100 + 0.4));
      }
      for (auto child2 : child->getChildren()) {
        if (random() % 15 == 0) {
          child2->addChild(
              new Sphere(point3d(genP(0.2, 5), genP(0.2, 5), genP(0.2, 5)) +
                             child2->getValue()->center,
                         (random() % 200) / 100 + 0.4));
        }
      }
    }
  }
}

void Skeleton::generateAnimal(int numSph) {
  srand(time(NULL));
  clearHull();
  clearInterpolation();
  delete root;
  root = new Node(new Sphere(point3d(0, 0, 0), 1.5));

  float theta = (float)(random() % 3100) / 1000;
  float phi = (float)(random() % 6200) / 1000;

  for (int i = 0; i < numSph; i++) {
    theta += 2 * 3.14 / numSph;
    phi += (float)(random() % 3100) / 1000 * 2 * 3.14 / numSph;
    if (random() % 2 == 0)
      root->addChild(new Sphere(
          point3d(2 * sin(theta), 2 * cos(phi), 2 * sin(phi)), 1.25));
  }
  for (auto child : root->getChildren()) {
    theta = (float)(random() % 3100) / 1000;
    phi = (float)(random() % 6200) / 1000;
    for (int i = 0; i < numSph; i++) {
      theta += 2 * 3.14 / numSph;
      phi += (float)(random() % 3100) / 1000 * 2 * 3.14 / numSph;
      if (random() % 5 == 0)
        child->addChild(
            new Sphere(point3d(1 * sin(theta), 1 * cos(phi), 1 * sin(phi)) +
                           child->getValue()->center * 2,
                       0.75));
    }

    for (auto child2 : child->getChildren()) {
      theta = (float)(random() % 3100) / 1000;
      phi = (float)(random() % 6200) / 1000;
      for (int i = 0; i < numSph; i++) {
        theta += 2 * 3.14 / numSph;
        phi += (float)(random() % 3100) / 1000 * 2 * 3.14 / numSph;
        if (random() % 10 == 0)
          child2->addChild(new Sphere(
              point3d(0.5 * sin(theta), 0.5 * cos(phi), 0.5 * sin(phi)) +
                  child2->getValue()->center * 1.5,
              0.5));
      }
    }
  }
}

void Skeleton::generateStar() {
  clearHull();
  clearInterpolation();
  delete root;
  root = new Node(new Sphere(point3d(0, 0, 0), 1.5));

  root->addChild(new Sphere(point3d(3, 0, 4)));
  root->addChild(new Sphere(point3d(3, 3, 4)));
  root->addChild(new Sphere(point3d(0, 3, 4)));
  root->addChild(new Sphere(point3d(0, 0, 4)));
  root->addChild(new Sphere(point3d(3, 0, -4)));
  root->addChild(new Sphere(point3d(3, 3, -4)));
  root->addChild(new Sphere(point3d(0, 3, -4)));
  root->addChild(new Sphere(point3d(0, 0, -4)));
}

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

  // When it comes to interpolation, we have different options.
  //  1) Constant number of new spheres between every linked spheres
  //  2) Constant number of new spheres on a given distance, i.e. number
  //     based on the distance between two given spheres

  interSpheres.clear();
  interpolate(getRoot(), constantDistance, spheresPerEdge, spheresPerUnit);

  // for the evolve process
  if (constantDistance) {
      // approximation of the level of subdivision
      int nbNode = countNode(getRoot());
      subdivisionLevel = (int)(interSpheres.size()/nbNode);
  }
  else {
      subdivisionLevel = spheresPerEdge;
  }

}

int Skeleton::countNode(Node *node, int nb) {

    nb += 1;

    for (auto child : node->getChildren()){
        nb = countNode(child, nb);
    }
    return nb;
}

void Skeleton::interpolate(Node *node, bool constantDistance,
                           int spheresPerEdge, float spheresPerUnit) {
  int newspheres = 0;
  point3d p1 = node->getValue()->center;
  for (auto child : node->getChildren()) {
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
      double newr = lambda * node->getValue()->radius +
                    (1 - lambda) * child->getValue()->radius;
      interSpheres.push_back(Sphere(newp, newr));
      newspheres++;
    }
    interpolate(child, constantDistance, spheresPerEdge, spheresPerUnit);
  }
}

void Skeleton::drawHull() {
  if (!hull.empty()) {
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

void Skeleton::stitching() {
  clearHull();
  point3d a = point3d(0, 0, 0);
  stitching(root, Quadrangle(a, a, a, a), true);
  myMesh = toMesh(hull);
  myMesh.mergeTriangles();
  hull.clear();
}

void Skeleton::stitching(Node *node, Quadrangle motherQuad, bool isRoot) {
  // Objective : complete the hull.
  //  If there is only one neighboring square, just build a cube around the
  //  sphere.
  //  If there are at least two, try to stitch them

  // On parcours l'arbre, et chaque fils ajoute le hull entre lui et sa mère.
  // La mère doit quand même add le hull autour de sa propre sphère

  double safetyFactor =
      0.8; // this makes the squares around joint nodes smaller so as to ensure
           // the hull computation is stable
  // typically safetyFactor should be between 0.5 and 1, but other values give
  // fun results.

  Sphere sphere = *node->getValue();

  double r = sphere.radius;
  // Quadrangle facingMom = Quadrangle(point3d(0, 0, 0), point3d(0, 0, 0),
  //                                  point3d(0, 0, 0), point3d(0, 0, 0));

  vector<Quadrangle> facingSons;
  // Convention : facingSons[0] représente celui vers la mère
  // Si c'est la root, c'est quelconque.
  if (isRoot)
    facingSons.push_back(Quadrangle(point3d(0, 0, 0), point3d(0, 0, 0),
                                    point3d(0, 0, 0), point3d(0, 0, 0)));

  vector<point3d> directions; // directions towards neighboring spheres
  if (!isRoot) {
    point3d motherPosition =
        (motherQuad.a + motherQuad.b + motherQuad.c + motherQuad.d) / 4;
    point3d vec = motherPosition - sphere.center;
    vec.normalize();
    directions.push_back(vec);
  }

  for (auto child : node->getChildren()) {
    point3d vec = child->getValue()->center - sphere.center;
    vec.normalize();
    directions.push_back(vec);
  }

  if (directions.size() == 0) {
    cout << "Stitching failed : a sphere has no neighboring sphere." << endl;
  }

  if (directions.size() == 1) {
    point3d x = directions[0];
    point3d y, z;

    if (!isRoot) { // try to use the same directions as mother for a better edge
                   // flow
      y = motherQuad.a - motherQuad.d;
      z = motherQuad.a - motherQuad.b;
    } else if (fabs(x.x()) > 0.01 ||
               fabs(x.y()) > 0.01) { // not colinear to 0,0,1
      y = point3<float>::cross(x, point3d(0, 0, 1));
      z = point3<float>::cross(x, y);
    } else {
      y = point3<float>::cross(x, point3d(0, 1, 0));
      z = point3<float>::cross(x, y);
    }
    x.normalize();
    y.normalize();
    z.normalize();

    point3d a, b, c, d;     // quadrangle facing the other sphere
    point3d ap, bp, cp, dp; // quadrangle opposite to it
    a = sphere.center + x * r + y * r + z * r;
    b = sphere.center + x * r + y * r - z * r;
    c = sphere.center + x * r - y * r - z * r;
    d = sphere.center + x * r - y * r + z * r;
    ap = a - 2 * x * r;
    bp = b - 2 * x * r;
    cp = c - 2 * x * r;
    dp = d - 2 * x * r;

    hull.push_back(Quadrangle(dp, cp, bp, ap));
    hull.push_back(Quadrangle(a, ap, bp, b));
    hull.push_back(Quadrangle(b, bp, cp, c));
    hull.push_back(Quadrangle(c, cp, dp, d));
    hull.push_back(Quadrangle(d, dp, ap, a));
    // facingMom = Quadrangle(a, b, c, d);
    facingSons.push_back(Quadrangle(a, b, c, d));
  }

  else { // multiple directions to consider

    // Let's find the minimum angle between two directions
    double theta = 360;
    for (int i = 0; i < directions.size(); i++) {
      for (int j = i + 1; j < directions.size(); j++) {
        double angle = acos(point3d::dot(directions[i], directions[j]) /
                            (directions[i].norm() * directions[j].norm()));
        if (angle < theta)
          theta = angle;
      }
    }
    double maxSize = r * sin(theta / 2) *
                     safetyFactor; // size allowed for a neighboring square
    vector<point3d> points;

    for (int i = 0; i < directions.size(); i++) {
      point3d milieu = sphere.center + directions[i] * sphere.radius;
      point3d a, b, c, d, x, y, z;
      x = directions[i];
      if (!isRoot && i == 0) {
        y = motherQuad.a - motherQuad.d;
        z = motherQuad.a - motherQuad.b;
      } else if (fabs(x.x()) > 0.01 ||
                 fabs(x.y()) > 0.01) { // not colinear to 0,0,1
        y = point3<float>::cross(x, point3d(0, 0, 1));
        z = point3<float>::cross(x, y);
      } else {
        y = point3<float>::cross(x, point3d(0, 1, 0));
        z = point3<float>::cross(x, y);
      }
      x.normalize();
      y.normalize();
      z.normalize();

      a = milieu + z * maxSize + y * maxSize;
      b = milieu - z * maxSize + y * maxSize;
      c = milieu - z * maxSize - y * maxSize;
      d = milieu + z * maxSize - y * maxSize;

      if (!isRoot && i == 0) { // this one is facing the mother
        facingSons.push_back(Quadrangle(a, b, c, d));

      } else { // facing a child
        facingSons.push_back(Quadrangle(a, b, c, d));
      }

      // TODO dont draw useless faces that correspond to facingSons
      points.push_back(a);
      points.push_back(b);
      points.push_back(c);
      points.push_back(d);
    }
    vector<Triangle> tri = convexHull(points);
    for (int i = 0; i < tri.size(); i++) {
      hull.push_back(Quadrangle(tri[i].a, tri[i].b, tri[i].c, tri[i].a));
      // TODO merge triangles instead of displaying them as quadrangles
    }
  }

  if (!isRoot) {            // dessiner le hull entre lui et sa mère
    point3d a, b, c, d;     // quadrangle facing the other sphere
    point3d ap, bp, cp, dp; // quadrangle opposite to it
    Quadrangle facingMom = facingSons[0];
    a = facingMom.a;
    b = facingMom.b;
    c = facingMom.c;
    d = facingMom.d;
    ap = motherQuad.a;
    bp = motherQuad.b;
    cp = motherQuad.c;
    dp = motherQuad.d;
    hull.push_back(Quadrangle(ap, a, b, bp));
    hull.push_back(Quadrangle(bp, b, c, cp));
    hull.push_back(Quadrangle(cp, c, d, dp));
    hull.push_back(Quadrangle(dp, d, a, ap));
  }

  int n = 1;
  for (auto child : node->getChildren()) {
    stitching(child, facingSons[n]);
    n++;
  }
}

vector<Triangle> Skeleton::convexHull(vector<point3d> points) {

  const int n = points.size();
  qh_vertex_t vertices[n];
  vector<Triangle> output;

  for (int i = 0; i < n; ++i) {
    vertices[i].z = points[i].z();
    vertices[i].x = points[i].x();
    vertices[i].y = points[i].y();
  }

  qh_mesh_t mesh = qh_quickhull3d(vertices, n);

  // QuickHull
  // https://stackoverflow.com/questions/18416861/how-to-find-convex-hull-in-a-3-dimensional-space
  // First, find 3 extremum.
  // Add the furthest point from that plane.
  // Assignment (optional): remove inside points, and assign each left v to
  // its closest face on the current solution
  //

  // note : this implementation crashes if "vertices" is n times the same vertex

  for (int i = 0; i < mesh.nindices; i += 3) {
    point3d a =
        point3d(mesh.vertices[i].x, mesh.vertices[i].y, mesh.vertices[i].z);
    point3d b = point3d(mesh.vertices[i + 1].x, mesh.vertices[i + 1].y,
                        mesh.vertices[i + 1].z);
    point3d c = point3d(mesh.vertices[i + 2].x, mesh.vertices[i + 2].y,
                        mesh.vertices[i + 2].z);
    output.push_back(Triangle(a, b, c));
  }

  qh_free_mesh(mesh);

  return output;
}

Mesh Skeleton::toMesh(vector<Quadrangle> hull, float threshold) {

  // On crée un vector idVec de taille 4*hull.size()
  // idVec[i] donne l'id attribuée au vertex i dans le Mesh en output
  //
  // Pour chaque Quadriplet,
  //   Pour les 4 sommets,
  //     Regarder s'il a déjà un id.
  //     S'il n'en a pas :
  //       Lui en donner un
  //       Ajouter cette position dans la liste de vertices
  //       Donner le même à tous ceux qui sont assez proches
  // Parcourir de nouveau les quadriplet, et repérer les triangles/quadrangles

  vector<int> idVec;
  vector<Vertex> vertices;
  idVec.resize(4 * hull.size(), -1);
  for (int quadNumber = 0; quadNumber < hull.size(); quadNumber++) {
    Quadrangle quad = hull[quadNumber];
    vector<point3d> q = {quad.a, quad.b, quad.c, quad.d};
    for (int i = 0; i < 4; i++) {
      int vertexId = 4 * quadNumber + i;
      if (idVec[vertexId] == -1) {
        int verticesCount = vertices.size(); // next available Id
        Vertex v;
        v.p = q[i];
        vertices.push_back(v);
        idVec[vertexId] = verticesCount;
        // let's search all the following Quadriplets for the same vertex
        for (int quadNumber2 = quadNumber; quadNumber2 < hull.size();
             quadNumber2++) {
          Quadrangle quad2 = hull[quadNumber2];
          vector<point3d> q2 = {quad2.a, quad2.b, quad2.c, quad2.d};
          for (int i2 = 0; i2 < 4; i2++) {
            point3d dist = q2[i2] - q[i];
            if (dist.norm() < threshold) { // the two vertices are identical
              if (idVec[quadNumber2 * 4 + i2] != -1 &&
                  quadNumber2 != quadNumber)
                cout << "Error : vertex already has an Id" << endl;
              idVec[quadNumber2 * 4 + i2] = idVec[vertexId];
            }
          }
        }
      }
    }
  }

  // Identifying the triangles and quadrangles
  vector<Triplet> triangles;
  vector<Quadruplet> quadrangles;
  for (int quadNumber = 0; quadNumber < hull.size(); quadNumber++) {
    // Quadrangle quad = hull[quadNumber];
    // vector<point3d> q = {quad.a, quad.b, quad.c, quad.d};
    bool foundTri = false;
    for (int i = 0; i < 4; i++) {

      for (int j = i + 1; j < 4; j++) {
        if (idVec[quadNumber * 4 + i] == idVec[quadNumber * 4 + j]) {
          // let's make a triangle with every vertex but i
          Triplet tr = {idVec[quadNumber * 4 + ((i + 1) % 4)],
                        idVec[quadNumber * 4 + ((i + 2) % 4)],
                        idVec[quadNumber * 4 + ((i + 3) % 4)]};
          foundTri = true;
          triangles.push_back(tr);
        }
      }

      if (!foundTri) { // congratulations, it's a quadrangle !
        Quadruplet qu = {idVec[quadNumber * 4], idVec[quadNumber * 4 + 1],
                         idVec[quadNumber * 4 + 2], idVec[quadNumber * 4 + 3]};
        quadrangles.push_back(qu);
      }
    }
  }

  Mesh m;
  m.triangles = triangles;
  m.quadrangles = quadrangles;
  m.vertices = vertices;
  return m;
}

ValGrad Skeleton::getScalarField(point3d pt, float T, float alpha) {
  // T : threshold controlling the proximity between the mesh and the scalar
  // field

  ValGrad I;

  // compute fi for every node sphere
  I = getScalarFieldComponent(root, pt, I, alpha);

  // compute fi for every intersphere
  for (auto sphere : interSpheres) {
    I = calcValGradI(I, pt, sphere, alpha);
  }

  // don't forget to lessen T
  I.val -= T;

  return I;
}

ValGrad Skeleton::calcValGradI(ValGrad I, point3d pt, Sphere sphere, float alpha) {

    double r = (pt - sphere.center).sqrnorm();
    double Ri = alpha * sphere.radius;
    double fi = (r > Ri) ? 0 : pow(1 - pow(r / Ri, 2), 2);
    double dfi = (r > Ri) ? 0 : 4/pow(sphere.radius, 2)*(1 - pow(r / Ri, 2));
    I.val += fi;
    I.grad += dfi*(pt - sphere.center);

    return I;
}

ValGrad Skeleton::getScalarFieldComponent(Node *node, point3d pt,
                                          ValGrad I, float alpha) {

  const Sphere *sphere = node->getValue();

  I = calcValGradI(I, pt, *sphere, alpha);

  for (auto child : node->getChildren()) {
    I = getScalarFieldComponent(child, pt, I, alpha);
  }

  return I;
}

point3d Skeleton::evolve(point3d xt, double Itarget, float T, float alpha) {
  ValGrad v = getScalarField(xt, T, alpha);
  double I = v.val;
  point3d deltaI = v.grad;
  double k1 = 1; // TODO
  double k2 = 1; // TODO
  double f = 1 / (1 + abs(k1) + abs(k2));
  double F = (I - Itarget) * f;
  double Fmax = F; // TODO
  double step =
      1; // TODO : min{r_i}/pow(2, k) où k est le niveau de subdivision
  double deltaT = step / Fmax;

  deltaI.normalize();
  return xt - deltaI * F * deltaT;
}

// merge
// norme =
// angles = 90°
// grande taille

// TODO stop displaying triangles as quadrangles !
// TODO convert vector<Quadrangle> to an actual mesh
