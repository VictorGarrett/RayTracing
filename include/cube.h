#pragma once
#include "shape.h"

class Cube : public Shape {
public:
  Cube();
  virtual ~Cube();

  void set_transform(float **m);
  float *check_axis(const float origin, const float direction);
  std::list<Intersection *> intersect(Ray *r);
  Vec4 normal_at(const Vec4 &p) const;
};