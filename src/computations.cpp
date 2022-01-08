#include "computations.h"

Computations::Computations(Intersection* i, Ray* r) {
    this->t = i->t;
    this->object = i->object;

    this->point = r->get_position(i->t);
    this->over_point = point;
    this->eyev = -r->direction;
    this->normalv = this->object->normal_at(this->point);
    this->inside = dot(normalv, eyev) < 0 ? true : false;
    if (this->inside) this->normalv = -this->normalv;
}

Computations::~Computations() {
    // this->object = nullptr;
}