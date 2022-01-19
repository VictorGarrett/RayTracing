#include "cube.h"
#include "mat.h"

Cube::Cube() {}

Cube::~Cube() {}

std::list<Intersection *> Cube::intersect(Ray *r) {
  std::list<Intersection *> intersections;

  Ray *r_transf = r->transform(this->inverseTransform);

  // index 0 is min; index 1 is max
  float *x = check_axis(r_transf->origin.x, r_transf->direction.x);
  float *y = check_axis(r_transf->origin.y, r_transf->direction.y);
  float *z = check_axis(r_transf->origin.z, r_transf->direction.z);

  float temp1[3] = {x[0], y[0], z[0]};
  float temp2[3] = {x[1], y[1], z[1]};

  float tmin = *std::max_element(temp1, temp1 + 3);
  float tmax = *std::min_element(temp2, temp2 + 3);

  delete x;
  delete y;
  delete z;

  if (tmin > tmax)
    return intersections;

  intersections.push_back(new Intersection(tmin, this));
  intersections.push_back(new Intersection(tmax, this));
  return intersections;
}

Vec4 Cube::normal_at(const Vec4 &p) const {
  Vec4 op = this->inverseTransform * p;

  float v[3] = {std::abs(op.x), std::abs(op.y), std::abs(op.z)};
  float maxc = *std::max_element(v, v + 3);

  Vec4 obj_normal;
  if (maxc == v[0])
    obj_normal = vector(op.x, 0, 0);
  else if (maxc == v[1])
    obj_normal = vector(0, op.y, 0);
  else
    obj_normal = vector(0, 0, op.z);

  Vec4 world_normal = this->inverseTransposed * obj_normal;
  world_normal.w = 0;
  return world_normal.normalize();
}

void Cube::set_transform(float **m) {
  this->transform = m;
  this->inverseTransform = inverse(m);
  this->inverseTransposed = transpose(this->inverseTransform);
}

float *Cube::check_axis(const float origin, const float direction) {
  float *t = new float[2];

  float tmin_numerator = (-1 - origin);
  float tmax_numerator = (1 - origin);

  if (std::abs(direction) >= EPSILON) {
    t[0] = tmin_numerator / direction;
    t[1] = tmax_numerator / direction;
  } else {
    t[0] = tmin_numerator * INFINITY;
    t[1] = tmax_numerator * INFINITY;
  }

  if (t[0] > t[1])
    std::swap(t[0], t[1]);

  return t;
}
