#include "vec4.h"

Vec4::Vec4() {}

Vec4::Vec4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vec4::~Vec4() { }

const Vec4 Vec4::normalize() const {
    return Vec4(this->x, this->y, this->z, this->w) / this->magnitude();
}

const float Vec4::magnitude() const {
    return sqrt(
        this->x * this->x +
        this->y * this->y +
        this->z * this->z +
        this->w * this->w
    );
}

const bool Vec4::is_point() const { return this->w; }

const bool Vec4::is_vector() const { return !this->w; }

Vec4 reflect(const Vec4& in, const Vec4& normal) {
    return in - normal * 2 * dot(in, normal);
}
