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

Ray* Ray::transform(float **m) {
    Vec4 ori =  m * this->origin;
    Vec4 dir =  m * this->direction;
    return new Ray(ori, dir);
}
