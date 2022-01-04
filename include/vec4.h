#pragma once
#define EPSILON 0.00001

// helper functions
inline const float abs(float n) { return n > 0.f ? n : -n; }
inline const bool equal(float a, float b) { return abs(a-b) < EPSILON; }

// w=1 is a point, w=0 is a vector
class Vec4 {
public:
    float x, y, z, w;
    Vec4();
    Vec4(const float x, const float y, const float z, const float w);
    ~Vec4();

    const bool is_point() const;
    const bool is_vector() const;
};


// builder functions
inline Vec4 point(const int x, const int y, const int z) {
    return Vec4(x, y, z, 1.0);
}

inline Vec4 vector(const int x, const int y, const int z) {
    return Vec4(x, y, z, 0.0);
}