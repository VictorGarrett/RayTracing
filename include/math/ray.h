#pragma once

#include "math/vec3f.h"

class Ray{

    private:
        point p;
        vec3f dir;

    public:
        Ray(point p = {0.0f, 0.0f, 0.0f}, vec3f dir = {0.0f, 0.0f, 0.0f});
        ~Ray();

        const point getPoint(float t) const;
        inline const vec3f getDir() const{
            return dir;
        }

        //returns a ray which is the reflection of this along a normal on a point 
        inline Ray reflection(point origin, vec3f normal){ 
            return Ray(origin, dir - 2*dot(dir, normal)*normal);
        }
};