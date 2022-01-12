#pragma once
#include "sphere.h"

class Computations
{
public:
    Shape* object;
    float t;
    Vec4 point;
    Vec4 over_point;
    Vec4 under_point;
    Vec4 eyev;
    Vec4 normalv;
    Vec4 reflectv;
    bool inside;
    float n1;
    float n2;

    Computations(Intersection* i, Ray* r, std::list<Intersection* > xs = {});
    ~Computations();

    void init_points(Intersection* i, Ray* r);
    void init_refraction_index(Intersection* i, std::list<Intersection* > xs);
};


