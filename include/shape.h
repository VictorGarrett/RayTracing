#pragma once
#include "material.h"
#include "ray.h"
#include "vec4.h"
#include <list>

class Group;

class Shape {
public:
  /*====================================================================*/
  /*================================WARNING=============================*/
  /*====================================================================*/
  // THINGS BROKE IF YOU MESS WITH THE DECLARATION ORDER (DONT ASK ME WHY)
  float **transform;
  Material material;
  float **inverseTransform;
  float **inverseTransposed;
  // END OF DANGER ZONE. FROM NOW ON ITS SAFE.

  Group *parent;

  Shape();
  virtual ~Shape();

  virtual void set_transform(float **m);
  virtual std::list<Intersection *> intersect(Ray *r) = 0;
  virtual Vec4 normal_at(const Vec4 &p) const = 0;
};
