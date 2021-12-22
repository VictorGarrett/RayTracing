#pragma once

#include "ray.h"

class Primitive{
    protected:
        point center;

    public:
        Primitive(point center = {0.0f, 0.0f, 0.0f});
        virtual ~Primitive();
        
        void move(vec3f delta);

        virtual const bool intersectRay(Ray r) = 0;

};

class Plane: public Primitive{

    private:
        vec3f normal;
    
    public:
        Plane(point center = {0.0f, 0.0f, 0.0f}, vec3f normal = {0.0f, 0.0f, 0.0f});
        virtual ~Plane();

        virtual const bool intersectRay(Ray r) override;

};

class Sphere: public Primitive{

    private:
        float radius;
    
    public:
        Sphere(point center = {0.0f, 0.0f, 0.0f}, float radius = 0.0f);
        virtual ~Sphere();

        virtual const bool intersectRay(Ray r) override;

};