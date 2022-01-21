#include "cylinder.h"
#include "mat.h"
#include "shape.h"
#include "sphere.h"
#include "transformations.h"

class Group : public Shape {
public:
  std::list<Shape *> childs;

  Group();
  ~Group();

  void add_child(Shape *s);
  std::list<Intersection *> intersect(Ray *r);
  Vec4 normal_at(const Vec4 &p) const;
};

Vec4 world_to_object(Shape *s, const Vec4 &p);

Vec4 normal_to_world(Shape *s, const Vec4 &n);

Vec4 normal_at(Shape *s, const Vec4 &p);

Sphere *hexagon_corner();

Cylinder *hexagon_edge();

Group *hexagon_side();

Group *hexagon();