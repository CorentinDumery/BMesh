#ifndef CATMULLCLARK_H
#define CATMULLCLARK_H

#include "Mesh.h"
#include <unordered_map>

namespace CatmullClark {
Mesh subdivision(const Mesh &mesh);
point3d getFacePoint(const Mesh &mesh, const Quadruplet &face);
string combineNumbers(uint a, uint b);
string getEdgeKey(uint a, uint b);
pair<uint, uint> extractEdgeFromKey(const string &key);
void insertEdge(unordered_map<string, pair<point3d, uint>> &EP, string key,
                const point3d &ep, const point3d &fp);
void insertNewFace(Mesh &mesh, point3d a, point3d b, point3d c, point3d d);
} // namespace CatmullClark

#endif // UTILITY_H
