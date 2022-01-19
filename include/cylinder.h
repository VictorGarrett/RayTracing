#pragma once
#include "shape.h"

class Cylinder : public Shape {
public:
  float minimum;
  float maximum;
  bool closed;

  Cylinder();
  virtual ~Cylinder();

  void set_transform(float **m);
  std::list<Intersection *> intersect(Ray *r);
  std::list<Intersection *> intersect_caps(Ray *r,
                                           std::list<Intersection *> xs);
  bool check_cap(Ray *r, float t);
  Vec4 normal_at(const Vec4 &p) const;
};