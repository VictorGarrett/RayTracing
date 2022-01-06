#pragma once
#include "vec4.h"

class Ray {
public:
    Vec4 origin;
    Vec4 direction;

    Ray();
    Ray(const Vec4& ori, const Vec4& dir);
    ~Ray();

    const Vec4 get_position(const float t) const;
    Ray* transform(float **m);
};

