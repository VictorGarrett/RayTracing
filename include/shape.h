#pragma once
#include <list>
#include "vec4.h"
#include "ray.h"
#include "material.h"

class Shape {
public:
    /*====================================================================*/
    /*================================WARNING=============================*/
    /*====================================================================*/
    // THINGS BROKE IF YOU MESS WITH THE DECLARATION ORDER (DONT ASK ME WHY)
    float **transform;
    Material material;
    float **inverseTransform;
    float **inverseTransposed;
    // END OF DANGER ZONE. FROM NOW ON ITS SAFE.

    Shape();
    virtual ~Shape();

    void set_transform(float **m);
    virtual std::list<Intersection* > intersect(Ray* r) = 0;
    virtual Vec4 normal_at(const Vec4& p) const = 0;
};
