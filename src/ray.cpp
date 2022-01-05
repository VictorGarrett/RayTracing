#include "ray.h"

Ray::Ray() {}

Ray::Ray(const Vec4& ori, const Vec4& dir){
    this->origin = ori;
    this->direction = dir;
}

Ray::~Ray() {}

const Vec4 Ray::get_position(const float t) const {
    return origin + t * direction;
}