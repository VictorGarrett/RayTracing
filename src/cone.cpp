#include "cone.h"
#include "mat.h"

Cone::Cone() {
  this->minimum = -99999;
  this->maximum = 99999;
  this->closed = false;
}

Cone::~Cone() {}

std::list<Intersection *> Cone::intersect(Ray *r) {
  std::list<Intersection *> intersections;
  Ray *r_transf = r->transform(this->inverseTransform);
  intersections = this->intersect_caps(r_transf, intersections);

  Vec4 o = r_transf->origin;
  Vec4 d = r_transf->direction;

  float a = d.x * d.x - d.y * d.y + d.z * d.z;
  float b = 2 * (o.x * d.x - o.y * d.y + o.z * d.z);
  float c = o.x * o.x - o.y * o.y + o.z * o.z;

  if (std::abs(a) < EPSILON) {
    if (std::abs(b) < EPSILON)
      return intersections;

    intersections.push_back(new Intersection(-c / (2 * b), this));
    intersections.push_back(new Intersection(-c / (2 * b), this));
    return intersections;
  }

  float disc = b * b - 4 * a * c;
  if (disc < 0) {
    if (disc > -EPSILON)
      disc = 0;
    else
      return intersections;
  }

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

std::list<Intersection *> Cone::intersect_caps(Ray *r,
                                               std::list<Intersection *> xs) {
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

bool Cone::check_cap(Ray *r, float t) {
  Vec4 p = r->get_position(t);

  if (sqrt(p.x * p.x + p.z * p.z) <= p.y)
    return true;

  return false;
}

Vec4 Cone::normal_at(const Vec4 &p) const {
  Vec4 object_point = this->inverseTransform * p;
  float dist =
      sqrt(object_point.x * object_point.x + object_point.z * object_point.z);

  Vec4 object_normal;
  if (dist < object_point.y - EPSILON) {
    if (object_point.y >= this->maximum - EPSILON)
      object_normal = vector(0, 1, 0);
    else if (object_point.y <= this->minimum + EPSILON)
      object_normal = vector(0, -1, 0);
  } else {
    float y = dist;
    if (std::abs(y) < EPSILON)
      return vector(0, 0, 0);
    if (object_point.y > 0)
      y = -y;
    object_normal = vector(object_point.x, y, object_point.z);
  }

  Vec4 world_normal = this->inverseTransposed * object_normal;
  world_normal.w = 0;

  return world_normal.normalize();
}

void Cone::set_transform(float **m) {
  this->transform = m;
  this->inverseTransform = inverse(m);
  this->inverseTransposed = transpose(this->inverseTransform);
}
