#pragma once
#include <list>
#include "vec4.h"

class Intersection;

class Shape {
public:
    float **transform;

    Shape();
    ~Shape();

    void set_transform(float **m);
};
