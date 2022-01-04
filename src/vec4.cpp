#include "vec4.h"

Vec4::Vec4() {}

Vec4::Vec4(float x, float y, float z, float w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vec4::~Vec4(){ }

const bool Vec4::is_point() const { return this->w; }

const bool Vec4::is_vector() const { return !this->w; }