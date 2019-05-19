#include "skeleton.h"

Skeleton::Skeleton(const Sphere &sphere) : root(new Node<Sphere>(sphere)) {
  // TODO: attention hardoceded
  root->addChild(Sphere(point3d(0, 6, 0), 2.5));
}

Skeleton::~Skeleton() { delete root; }

void Skeleton::draw() const {
  // TODO : draw the full tree not only root and its children
  root->getValue().draw();
  for (auto child : root->getChildren())
    child->getValue().draw();
}

void Skeleton::interpolate(bool constantDistance, int spheresPerEdge, float spheresPerUnit) {
    //TODO: not only root's children

    // When it comes to interpolation, we have different options.
    //  1) Constant number of new spheres between every linked spheres
    //  2) Constant number of new spheres on a given distance, i.e. number
    //     based on the distance between two given spheres

    int newspheres = 0;
    point3d p1 = root->getValue().center;
    for (auto child : root->getChildren()){
      point3d p2 = child->getValue().center;
      int spheresToAdd;
      if (constantDistance){ //Mode 2)
        float distance = (p2-p1).norm();
        spheresToAdd = (int) (distance/spheresPerUnit);
      }
      else spheresToAdd = spheresPerEdge; //Mode 1)
      for (int i=1;i<spheresToAdd+1;i++){
        float lambda = (float) i / (spheresToAdd+1);
        point3d newp = lambda*p1+(1-lambda)*p2;
        double newr = lambda*root->getValue().radius+(1-lambda)*child->getValue().radius;
        root->addChild(Sphere(newp,newr));
        newspheres++;
      }
    }
    cout << "Interpolation added "<<newspheres<<" new sphere(s)."<<endl;
}
