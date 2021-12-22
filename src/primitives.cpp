#include "primitives.h"
#include <stdio.h>

Primitive::Primitive(point center){
    this->center = center;
}

Primitive::~Primitive(){

}

void Primitive::move(vec3f delta){
    center += delta;
}


Plane::Plane(point center, vec3f normal): Primitive(center){
    this->normal = normal;
}

Plane::~Plane(){

}

const bool Plane::intersectRay(Ray r){
    if(dot(r.getDir(), normal)){
        //float t = dot(center - r.getPoint(0), normal)/dot(r.getDir(), normal);
        return true;//r.getPoint(t);
    }
    else
        return false;//{0.0f, 0.0f, 0.0f};
}


Sphere::Sphere(point center, float radius): Primitive(center){
    this->radius = radius;
}

Sphere::~Sphere(){

}

const bool Sphere::intersectRay(Ray r){
    float a = r.getDir().length2();
    float b = 2*dot(r.getPoint(0) - center, r.getDir());
    float c = (r.getPoint(0) - center).length2() - radius*radius;

    if(a == 1.0f)
        printf("%f, %f, %f\n", a, b, c);

    if(b*b-4*a*c >= 0){
        if(a == 1.0f)
            printf("%f, %f, %f\n", a, b, c);
        return true;
    }
    else
        return false;

    /* float t1 = -b + sqrt(b*b-4*a*c)/(2*a);
    float t2 = -b - sqrt(b*b-4*a*c)/(2*a);

    return fabs(t1) < fabs(t2) ? r.getPoint(t1) : r.getPoint(t2); */
}