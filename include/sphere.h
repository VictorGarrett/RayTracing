#pragma once
#include "ray.h"
#include "shape.h"

class Sphere: public Shape {
public:
    Vec4 center;
    float radius;

    Sphere();
    ~Sphere();

    const void intersect(const Ray& r);
};