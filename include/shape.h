#pragma once
#include <list>
#include "vec4.h"

class Intersection;

class Shape {
public:
    std::list<Intersection* > intersections;

    Shape();
    ~Shape();

    const void add_intersection(const float t, Shape* obj);
};