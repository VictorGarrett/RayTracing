#pragma once

#include <math.h>

class vec3f{

    public:
        float x;
        float y;
        float z;

        vec3f();
        vec3f(const vec3f& other);
        vec3f(float x, float y, float z);
        ~vec3f();

        float length() const;

        inline float length2() const{
            return x*x+y*y+z*z;
        }

        inline vec3f normalize(){
            float len = length();
            x /= len;
            y /= len;
            z /= len;

            return *this;
        }

        inline void operator=(const vec3f& attrib){
            x = attrib.x;
            y = attrib.y;
            z = attrib.z;
        }

        void operator+=(const vec3f& attrib);
        void operator-=(const vec3f& attrib);
        inline const vec3f operator*(float scalar) const{
            return vec3f(x*scalar, y*scalar, z*scalar);
        }
        const vec3f operator/(float scalar) const;

        void operator*=(float scalar);

};

inline bool operator==(const vec3f& first, const vec3f& second) {
    return first.x == second.x && first.y == second.y && first.z == second.z;
}

inline bool operator!=(const vec3f& first, const vec3f& second) {
    return first.x != second.x || first.y != second.y || first.z != second.z; 
}

inline const vec3f operator+(const vec3f& first, const vec3f& second){
    vec3f sum(first.x+second.x, first.y+second.y, first.z+second.z);
    return sum;
}

const vec3f operator-(const vec3f& first, const vec3f& second);

inline const vec3f operator*(float scalar, const vec3f& vec){
    return vec3f(vec.x*scalar, vec.y*scalar, vec.z*scalar);
}

const vec3f operator/(float scalar, const vec3f& vec);

inline const float dot(const vec3f& first, const vec3f& second){
    return first.x*second.x + first.y*second.y + first.z*second.z;
}

vec3f cross(const vec3f& first, const vec3f& second);

typedef vec3f point;