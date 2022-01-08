#include "computations.h"

Computations::Computations(Intersection *i, Ray *r) {
    this->t = i->t;
    this->object = i->object;
    
    this->point = r->get_position(i->t);
    this->eyev = -r->direction;
    this->normalv = this->object->normal_at(this->point);
    this->inside = dot(normalv, eyev) < 0 ? true : false;
    if(this->inside) this->normalv = -this->normalv;
    this->over_point = this->point + this->normalv * EPSILON;
}

Computations::~Computations(){
    // this->object = nullptr;
}