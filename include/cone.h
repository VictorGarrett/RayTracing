#pragma once
#include "shape.h"

class Cone : public Shape {
public:
  float minimum;
  float maximum;
  bool closed;

  Cone();
  virtual ~Cone();

  void set_transform(float **m);
  std::list<Intersection *> intersect(Ray *r);
  std::list<Intersection *> intersect_caps(Ray *r,
                                           std::list<Intersection *> xs);
  bool check_cap(Ray *r, float t);
  Vec4 normal_at(const Vec4 &p) const;
};