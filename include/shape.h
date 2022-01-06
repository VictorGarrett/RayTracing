#pragma once
#include <list>
#include "vec4.h"
#include "material.h"

class Shape {
public:
    float **transform;
    Material material;

    Shape();
    ~Shape();

    void set_transform(float **m);
    virtual Vec4 normal_at(const Vec4& p) const = 0;
};
