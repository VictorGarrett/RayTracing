#pragma once
#include "helper.h"

inline const bool eps_equal(float a, float b) { return abs(a-b) < EPSILON; }

// w=1 is a point, w=0 is a vector
class Vec4 {
public:
    float x, y, z, w;
    Vec4();
    Vec4(const float x, const float y, const float z, const float w);
    ~Vec4();

    inline Vec4 operator-() const { return Vec4(-x, -y, -z, w); }
    
    const Vec4 normalize() const;
    const float magnitude() const;
    const bool is_point() const;
    const bool is_vector() const;
};

Vec4 reflect(const Vec4& in, const Vec4& normal);

// overload operators
inline bool operator==(const Vec4 &v1, const Vec4 &v2){
    return (
        eps_equal(v1.x, v2.x) &&
        eps_equal(v1.y, v2.y) &&
        eps_equal(v1.z, v2.z) &&
        eps_equal(v1.w, v2.w)
    );
}

inline Vec4 operator+(const Vec4 &v1, const Vec4 &v2){
    return Vec4(
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z,
        v1.w + v2.w
    );
}


inline Vec4 operator*(const float s, const Vec4& v) { 
    return Vec4(s * v.x, s * v.y, s * v.z, v.w);
}

inline Vec4 operator*(const Vec4& v, const float s) { 
    return Vec4(s * v.x, s * v.y, s * v.z, v.w);
}

inline Vec4 operator*(float m[4][4], const Vec4& v) { 
    float vec[4];

    for(int row = 0; row < 4; row++){
        vec[row] =  m[row][0] * v.x +
                    m[row][1] * v.y +
                    m[row][2] * v.z +
                    m[row][3] * v.w;
    }

    return Vec4(vec[0], vec[1], vec[2], vec[3]);
}

inline Vec4 operator*(float **m, const Vec4& v) { 
    float vec[4];

    for(int row = 0; row < 4; row++){
        vec[row] =  m[row][0] * v.x +
                    m[row][1] * v.y +
                    m[row][2] * v.z +
                    m[row][3] * v.w;
    }

    return Vec4(vec[0], vec[1], vec[2], vec[3]);
}

inline Vec4 operator/(const Vec4& v, const float s) { 
    return Vec4(v.x/s, v.y/s, v.z/s, v.w);
}


inline Vec4 operator-(const Vec4 &v1, const Vec4 &v2){
    return Vec4(
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z,
        v1.w - v2.w
    );
}

// linear algebra
inline const float dot(const Vec4& v1, const Vec4& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline Vec4 cross(const Vec4& v1, const Vec4& v2) {
    return Vec4(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x,
        0
    );
}

// builder functions
inline Vec4 point(const float x, const float y, const float z) {
    return Vec4(x, y, z, 1.0);
}

inline Vec4 vector(const float x, const float y, const float z) {
    return Vec4(x, y, z, 0.0);
}
