#pragma once
#include <list>

class Shape;

class Intersection {
public:
    float t;
    Shape* object;

    Intersection();
    Intersection(const float t, Shape* obj);
    ~Intersection();
};

Intersection* hit(std::list<Intersection* > intList);
