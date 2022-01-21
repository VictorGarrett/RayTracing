#include "group.h"

Group::Group() : Shape() {}

Group::~Group() {}

void Group::add_child(Shape *s) {
  if (s != NULL) {
    this->childs.push_back(s);
    s->parent = this;
  }
}

std::list<Intersection *> Group::intersect(Ray *r) {
  std::list<Intersection *> xs;
  Ray *r_transf = r->transform(this->inverseTransform);

  for (auto &shape : this->childs) {
    xs.merge(shape->intersect(r_transf));
  }

  return xs;
}

Vec4 Group::normal_at(const Vec4 &p) const {
  std::cerr << "trying to get the normal of a group" << '\n';
  return vector(0, 0, 0);
}

Vec4 world_to_object(Shape *s, const Vec4 &p) {
  Vec4 point = p;
  if (s->parent)
    point = world_to_object(s->parent, p);

  return s->inverseTransform * point;
}

Vec4 normal_to_world(Shape *s, const Vec4 &n) {
  Vec4 normal = s->inverseTransposed * n;
  normal.w = 0;
  normal = normal.normalize();

  if (s->parent)
    normal = normal_to_world(s->parent, normal);

  return normal;
}

Vec4 normal_at(Shape *s, const Vec4 &p) {
  Vec4 local_point = world_to_object(s, p);
  Vec4 local_normal = s->normal_at(local_point);
  return normal_to_world(s, local_normal);
}

Sphere *hexagon_corner() {
  Sphere *corner = new Sphere();
  corner->set_transform(
      multiply4x4(translation(0, 0, -1), scaling(0.25, 0.25, 0.25)));
  return corner;
}

Cylinder *hexagon_edge() {
  Cylinder *edge = new Cylinder();
  edge->minimum = 0;
  edge->maximum = 1;
  float **trf = multiply4x4(translation(0, 0, -1), rotation_y(-PI / 6));
  trf = multiply4x4(multiply4x4(trf, rotation_z(-PI / 2)),
                    scaling(0.25, 1, 0.25));
  edge->set_transform(trf);

  return edge;
}

Group *hexagon_side() {
  Group *side = new Group();
  side->add_child(hexagon_corner());
  side->add_child(hexagon_edge());

  return side;
}

Group *hexagon() {
  Group *hex = new Group();

  for (int n = 0; n < 5; n++) {
    Group *side = hexagon_side();
    side->set_transform(rotation_y(n * PI / 3));
    hex->add_child(side);
  }
  return hex;
}