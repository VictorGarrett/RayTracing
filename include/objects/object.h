#pragma once

#include "objects/primitives.h"
#include "objects/material.h"
#include <stdio.h>

class Object{

    private:
        Primitive* shape;
        Material* mat;

    public:
        Object(Primitive* shape = nullptr, Material* baseMaterial = nullptr);
        ~Object();

        inline point intersectRay(Ray& r){
            return shape->intersectRay(r);
        }

        inline vec3f getNormal(point& surfacePoint){
            return shape->getNormal(surfacePoint);
        }

        inline color getColor(){
            return mat->getColor();
        }

        inline color getEmissiveColor(){
            return mat->getEmissiveColor();
        }

        inline color brdf(float theta_i, float phi_i, float theta_r, float phi_r){
            return mat->brdf(theta_i, phi_i, theta_r, phi_r);
        }

};