#pragma once
#include <list>
#include "vec4.h"
#include "material.h"
#include "ray.h"

class Shape {
public:
    float **transform;
    Material material;

    Shape();
    virtual ~Shape();

    void set_transform(float **m);
    virtual std::list<Intersection* > intersect(Ray* r) = 0;
    virtual Vec4 normal_at(const Vec4& p) const = 0;
};
