#pragma once

#include "vec3f.h"

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
};