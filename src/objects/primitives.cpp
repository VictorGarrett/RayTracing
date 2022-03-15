#include "objects/primitives.h"
#include <stdio.h>

Primitive::Primitive(point center){
    this->center = center;
}

Primitive::~Primitive(){

}

void Primitive::move(vec3f& delta){
    center += delta;
}

const vec3f Primitive::getCenter() const{
    return center;
}


Plane::Plane(point center, vec3f normal): Primitive(center){
    this->normal = normal;
}

Plane::~Plane(){

}

const vec3f Plane::intersectRay(Ray& r) const{
    if(dot(r.getDir(), normal)){
        float t = dot(center - r.getPoint(0), normal)/dot(r.getDir(), normal);
        
        if(t > 0.001f){
            //printf("interc %f\n", t);
            return r.getPoint(t);
        }
    }
    return {0.0f, 0.0f, 0.0f};
}

const vec3f Plane::getNormal(point& surfacePoint) const{
    return normal;
}

const float Plane::getSize() const{
    return 0.0f;
}

Sphere::Sphere(point center, float radius): Primitive(center){
    this->radius = radius;
}

Sphere::~Sphere(){

}

const vec3f Sphere::intersectRay(Ray& r) const{
    //float a = r.getDir().length2(); =1
    float b = 2*dot(r.getPoint(0) - center, r.getDir());
    float c = (r.getPoint(0) - center).length2() - radius*radius;

    float delta = b*b-4*c;
    

    if(delta >= 0){
        float t1 = (-b + sqrt(delta))/2;
        float t2 = (-b - sqrt(delta))/2;
        if(t1 > t2 && t2 > 0.01f){
            return r.getPoint(t2);
        }
        else if(t1 > 0.01f){
            return r.getPoint(t1);
        }
    }
    return vec3f(0, 0, 0);


}

const vec3f Sphere::getNormal(point& surfacePoint) const{
    vec3f normal = (surfacePoint - center);
    normal.normalize();
    return normal;
}

const float Sphere::getSize() const{
    return radius;
}