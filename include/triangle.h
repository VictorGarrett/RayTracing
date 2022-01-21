#pragma once
#include "shape.h"

class Triangle : public Shape {
public:
  Vec4 p1;
  Vec4 p2;
  Vec4 p3;
  Vec4 e1;
  Vec4 e2;
  Vec4 normal;

  Triangle();
  Triangle(Vec4 p1, Vec4 p2, Vec4 p3);
  ~Triangle();

  std::list<Intersection *> intersect(Ray *r);
  Vec4 normal_at(const Vec4 &p) const;
};