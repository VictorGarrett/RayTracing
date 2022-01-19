#include "cylinder.h"
#include "mat.h"

Cylinder::Cylinder() {
  this->minimum = -99999;
  this->maximum = 99999;
  this->closed = false;
}

Cylinder::~Cylinder() {}

std::list<Intersection *> Cylinder::intersect(Ray *r) {
  std::list<Intersection *> intersections;

  Ray *r_transf = r->transform(this->inverseTransform);
  intersections = this->intersect_caps(r_transf, intersections);

  float a = pow(r_transf->direction.x, 2) + pow(r_transf->direction.z, 2);

  // ray is paralel to the y axys
  if (std::abs(a) < EPSILON)
    return intersections;

  float b = 2 * r_transf->origin.x * r_transf->direction.x +
            2 * r_transf->origin.z * r_transf->direction.z;
  float c = pow(r_transf->origin.x, 2) + pow(r_transf->origin.z, 2) - 1;
  float disc = b * b - 4 * a * c;

  // ray does not intersect the cylinder
  if (disc < 0)
    return intersections;

  float t0 = (-b - sqrt(disc)) / (2 * a);
  float t1 = (-b + sqrt(disc)) / (2 * a);

  float y0 = r_transf->origin.y + t0 * r_transf->direction.y;
  if (this->minimum < y0 && y0 < this->maximum)
    intersections.push_back(new Intersection(t0, this));

  float y1 = r_transf->origin.y + t1 * r_transf->direction.y;
  if (this->minimum < y1 && y1 < this->maximum)
    intersections.push_back(new Intersection(t1, this));

  return intersections;
}

std::list<Intersection *>
Cylinder::intersect_caps(Ray *r, std::list<Intersection *> xs) {
  if (!this->closed)
    return xs;

  float t = (this->minimum - r->origin.y) / r->direction.y;
  if (this->check_cap(r, t)) {
    xs.push_back(new Intersection(t, this));
  }

  t = (this->maximum - r->origin.y) / r->direction.y;
  if (this->check_cap(r, t)) {
    xs.push_back(new Intersection(t, this));
  }

  return xs;
}

bool Cylinder::check_cap(Ray *r, float t) {
  float x = r->origin.x + t * r->direction.x;
  float z = r->origin.z + t * r->direction.z;

  if (x * x + z * z <= 1)
    return true;

  return false;
}

Vec4 Cylinder::normal_at(const Vec4 &p) const {
  Vec4 object_point = this->inverseTransform * p;
  float dist =
      object_point.x * object_point.x + object_point.z * object_point.z;

  bool elsesta = false;
  Vec4 object_normal;
  if (dist < 1 - EPSILON) {
    if (object_point.y >= this->maximum - EPSILON)
      object_normal = vector(0, 1, 0);
    else if (object_point.y <= this->minimum + EPSILON)
      object_normal = vector(0, -1, 0);
  } else {
    elsesta = true;
    object_normal = vector(object_point.x, 0, object_point.z);
  }

  Vec4 world_normal = this->inverseTransposed * object_normal;
  world_normal.w = 0;

  return world_normal.normalize();
}

void Cylinder::set_transform(float **m) {
  this->transform = m;
  this->inverseTransform = inverse(m);
  this->inverseTransposed = transpose(this->inverseTransform);
}
