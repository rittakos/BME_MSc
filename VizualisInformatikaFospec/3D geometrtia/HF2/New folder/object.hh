#pragma once

#include "base-mesh.hh"
#include "visualization.hh"

class Object {
public:
  explicit Object(std::string filename);
  virtual ~Object();
  const BaseMesh &baseMesh() const;
  virtual void draw(const Visualization &vis) const;
  virtual void drawWithNames(const Visualization &vis) const = 0;
  virtual Vector postSelection(int selected) = 0;
  virtual void movement(int selected, const Vector &pos) = 0;
  virtual void updateBaseMesh();
  virtual bool reload() = 0;
  bool valid() const;
protected:
  void updateBaseMesh(bool own_normal, bool own_mean);
  virtual Vector normal(BaseMesh::VertexHandle vh) const;
  virtual double meanCurvature(BaseMesh::VertexHandle vh) const;

  BaseMesh mesh;
  std::string filename;
};
