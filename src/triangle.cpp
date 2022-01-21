#include "triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(Vec4 p1, Vec4 p2, Vec4 p3) {
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;

  this->e1 = p2 - p1;
  this->e2 = p3 - p1;

  this->normal = cross(e2, e1).normalize();
}

Triangle::~Triangle() {}

std::list<Intersection *> Triangle::intersect(Ray *r) {
  std::list<Intersection *> xs;
  Vec4 dir_cross_e2 = cross(r->direction, this->e2);
  float det = dot(this->e1, dir_cross_e2);

  if (std::abs(det) < EPSILON)
    return xs;

  float f = 1 / det;
  Vec4 p1_to_origin = r->origin - this->p1;
  float u = f * dot(p1_to_origin, dir_cross_e2);

  if (u < 0 || u > 1)
    return xs;

  Vec4 origin_cross_e1 = cross(p1_to_origin, this->e1);
  float v = f * dot(r->direction, origin_cross_e1);

  if (v < 0 || (u + v) > 1)
    return xs;

  float t = f * dot(this->e2, origin_cross_e1);
  xs.push_back(new Intersection(t, this));

  return xs;
}

Vec4 Triangle::normal_at(const Vec4 &p) const { return this->normal; }
