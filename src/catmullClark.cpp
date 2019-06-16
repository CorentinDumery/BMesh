#include "catmullClark.h"

Mesh CatmullClark::subdivision(const Mesh &mesh) {
  unordered_map<string, pair<point3d, uint>> EP; // edge points

  for (auto &face : mesh.quadrangles) {
    // FP
    point3d fp = getFacePoint(mesh, face);

    // EP
    point3d intialEdge =
        (mesh.vertices[face[face.size() - 1]].p + mesh.vertices[face[0]].p) / 2;
    insertEdge(EP, getEdgeKey(face[face.size() - 1], face[0]), intialEdge, fp);

    for (uint i = 0; i < face.size() - 1; i++) {
      point3d edge =
          (mesh.vertices[face[i + 1]].p + mesh.vertices[face[i]].p) / 2;
      insertEdge(EP, getEdgeKey(face[i + 1], face[i]), edge, fp);
    }
  }

  // Finish to calculate edge points position
  for (auto &ep : EP)
    ep.second.first /= ep.second.second;

  vector<pair<point3d, uint>> barycentersF;
  barycentersF.resize(mesh.vertices.size(), {point3d(0, 0, 0), 0});

  vector<pair<point3d, uint>> barycentersR;
  barycentersR.resize(mesh.vertices.size(), {point3d(0, 0, 0), 0});

  for (auto &face : mesh.quadrangles) {
    point3d fp = getFacePoint(mesh, face);

    // Calculates FP barycenters
    for (uint i = 0; i < face.size(); i++) {
      barycentersF[face[i]].first += fp;
      barycentersF[face[i]].second++;
    }
  }

  // Calculates EP barycenters
  for (auto &ep : EP) {
    pair<uint, uint> edge = extractEdgeFromKey(ep.first);
    barycentersR[edge.first].first += ep.second.first;
    barycentersR[edge.first].second++;
    barycentersR[edge.second].first += ep.second.first;
    barycentersR[edge.second].second++;
  }
  // Calculate new positions of orginal points
  vector<point3d> newPoints(mesh.vertices.size());

  for (uint i = 0; i < mesh.vertices.size(); i++) {
    barycentersF[i].first /= barycentersF[i].second;
    barycentersR[i].first /= barycentersR[i].second;

    point3d P = mesh.vertices[i].p;
    point3d F = barycentersF[i].first;
    point3d R = barycentersR[i].first;
    int k = barycentersF[i].second;

    point3d newP = F + (2 * R) + (k - 3) * P;
    newP /= k;

    newPoints[i] = newP;
  }

  // Generate the new Mesh
  Mesh subdividedMesh;

  for (auto &face : mesh.quadrangles) {
    point3d fp = getFacePoint(mesh, face);

    // initial phase
    point3d aInit = fp;
    point3d bInit = newPoints[face[0]];
    point3d cInit = EP[getEdgeKey(face[0], face[face.size() - 1])].first;
    point3d dInit = newPoints[face[face.size() - 1]];
    insertNewFace(subdividedMesh, aInit, bInit, cInit, dInit);

    for (uint i = 0; i < face.size() - 1; i++) {
      point3d a = fp;
      point3d b = newPoints[face[i]];
      point3d c = EP[getEdgeKey(face[i], face[i + 1])].first;
      point3d d = newPoints[face[i + 1]];
      insertNewFace(subdividedMesh, a, d, c, b);
    }
  }

  return subdividedMesh;
}

// TODO : templetize quadruplet and triplet
point3d CatmullClark::getFacePoint(const Mesh &mesh, const Quadruplet &face) {
  point3d center;

  for (uint i = 0; i < face.size(); i++)
    center += mesh.vertices[face[i]].p;

  center /= face.size();
  return center;
}

string CatmullClark::combineNumbers(uint a, uint b) {
  return to_string(a) + "-" + to_string(b);
}

string CatmullClark::getEdgeKey(uint a, uint b) {
  return a < b ? combineNumbers(a, b) : combineNumbers(b, a);
}

void CatmullClark::insertEdge(unordered_map<string, pair<point3d, uint>> &EP,
                              string key, const point3d &ep,
                              const point3d &fp) {
  auto epSearch = EP.find(key);
  if (epSearch != EP.end()) {
    EP[key].second++;
    EP[key].first += fp;
  } else {
    EP.insert({key, {ep + fp, 2}});
  }
}

pair<uint, uint> CatmullClark::extractEdgeFromKey(const string &key) {
  string s = key;
  string delimiter = "-";

  size_t pos = 0;
  string token[2];

  while ((pos = s.find(delimiter)) != string::npos) {
    token[0] = s.substr(0, pos);
    s.erase(0, pos + delimiter.length());
  }
  token[1] = s;

  return make_pair(stoul(token[0]), stoul(token[1]));
}

void CatmullClark::insertNewFace(Mesh &mesh, point3d a, point3d b, point3d c,
                                 point3d d) {
  Quadruplet quadInit;

  // TODO : Carreful this is unefficient (I'm checking all vertice before adding
  // one to avoid duplicate point)
  int indexA = -1;
  int indexB = -1;
  int indexC = -1;
  int indexD = -1;
  Vertex newVertexA(a);
  Vertex newVertexB(b);
  Vertex newVertexC(c);
  Vertex newVertexD(d);
  for (uint i = 0; i < mesh.vertices.size(); i++) {
    if (newVertexA == mesh.vertices[i])
      indexA = i;
    if (newVertexB == mesh.vertices[i])
      indexB = i;
    if (newVertexC == mesh.vertices[i])
      indexC = i;
    if (newVertexD == mesh.vertices[i])
      indexD = i;
  }

  if (indexA == -1) {
    quadInit[0] = mesh.vertices.size();
    mesh.vertices.push_back(newVertexA);
  } else
    quadInit[0] = indexA;

  if (indexB == -1) {
    quadInit[1] = mesh.vertices.size();
    mesh.vertices.push_back(newVertexB);
  } else
    quadInit[1] = indexB;

  if (indexC == -1) {
    quadInit[2] = mesh.vertices.size();
    mesh.vertices.push_back(newVertexC);
  } else
    quadInit[2] = indexC;

  if (indexD == -1) {
    quadInit[3] = mesh.vertices.size();
    mesh.vertices.push_back(newVertexD);
  } else
    quadInit[3] = indexD;

  mesh.quadrangles.push_back(quadInit);
}
