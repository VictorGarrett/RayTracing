#pragma once
#include "ray.h"
#include "shape.h"

class Sphere: public Shape {
public:
    Vec4 center;
    float radius;

    Sphere();
    ~Sphere();

    std::list<Intersection* > intersect(Ray* r);
};