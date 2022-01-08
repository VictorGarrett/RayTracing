#pragma once
#include "shape.h"

class Plane : public Shape {
public:
    Vec4 normalv;

    Plane();
    virtual ~Plane();

    void set_transform(float** m);
    std::list<Intersection* > intersect(Ray* r);
    Vec4 normal_at(const Vec4& p) const;
};