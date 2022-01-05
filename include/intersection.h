#pragma once
#include "shape.h"

class Intersection {
public:
    float t;
    Shape* object;

    Intersection();
    Intersection(const float t, Shape* obj);
    ~Intersection();
};
