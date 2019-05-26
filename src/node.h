#ifndef NODE_H
#define NODE_H

#include "Mesh.h"
#include <vector>

using namespace std;

class Node {

public:
  Node();
  Node(Sphere *sphere) : sphere(sphere) {}
  ~Node() {
    delete sphere;

    // TODO : This is not something we really want, specialy when we want to
    // remove one specific node (let's see when it will be implemented). Don't
    // forget to adapt descructor skeleton tree in consequence.
    for (auto node : children)
      delete node;

    children.clear();
  }
  void addChild(Node *child) { children.push_back(child); }
  void addChild(Sphere *value) {
    Node *child = new Node(value);
    children.push_back(child);
  }
  bool isLeaf() const { return children.empty(); }
  const Sphere *getValue() const { return sphere; }
  const vector<Node *> &getChildren() const { return children; }
  void editSphere(point3d center, double radius) {
    sphere->center = center;
    sphere->radius = radius;
  };

private:
  Sphere *sphere;
  vector<Node *> children;
};

#endif // NODE_H
