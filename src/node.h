#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

template <class T> class Node {

public:
  Node();
  Node(T value) : value(value) {}
  ~Node() {
    for (auto node : children)
      delete node;

    children.clear();
  }
  void addChild(Node<T> *child) { children.push_back(child); }
  void addChild(const T &value) {
    Node<T> *child = new Node<T>(value);
    children.push_back(child);
  }
  bool isLeaf() const { return children.empty(); }
  const T &getValue() const { return value; }
  const vector<Node<T> *> &getChildren() const { return children; }

private:
  T value;
  vector<Node<T> *> children;
};

#endif // NODE_H
