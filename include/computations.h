#pragma once
#include "sphere.h"

class Computations
{ 
public: 
    Shape* object;
    float t;
    Vec4 point;
    Vec4 eyev;
    Vec4 normalv;
    bool inside;

    Computations(Intersection *i, Ray *r);
    ~Computations();
};


