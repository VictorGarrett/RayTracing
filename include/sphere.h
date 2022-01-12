#pragma once
#include "shape.h"

class Sphere : public Shape {
public:

    Sphere();
    virtual ~Sphere();

    std::list<Intersection* > intersect(Ray* r);
    Vec4 normal_at(const Vec4& p) const;
};

Sphere* glass_sphere();