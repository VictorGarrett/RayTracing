#pragma once

#include <math.h>

class vec3f{

    public:
        float x;
        float y;
        float z;

        vec3f();
        vec3f(float x, float y, float z);
        ~vec3f();

        float length() const;
        float length2() const;
        void normalize();
        void operator=(const vec3f& attrib);
        void operator+=(const vec3f& attrib);
        void operator-=(const vec3f& attrib);
        const vec3f operator*(float scalar) const;
        const vec3f operator/(float scalar) const;

};

const vec3f operator+(const vec3f& first, const vec3f& second);

const vec3f operator-(const vec3f& first, const vec3f& second);

const vec3f operator*(float scalar, const vec3f& vec);

const vec3f operator/(float scalar, const vec3f& vec);

const float dot(const vec3f& first, const vec3f& second);

typedef vec3f point;