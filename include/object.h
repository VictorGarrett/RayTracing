#pragma once

#include "primitives.h"
#include "material.h"

class Object{

    private:
        Primitive* shape;
        Material* mat;

    public:
        Object(Primitive* shape = nullptr, Material* baseMaterial = nullptr);
        ~Object();

        inline point intersectRay(Ray r){
            return shape->intersectRay(r);
        }

        inline vec3f getNormal(point surfacePoint){
            return shape->getNormal(surfacePoint);
        }

        inline color getColor(){
            return mat->getColor();
        }



};