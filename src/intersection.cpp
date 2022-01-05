#include "intersection.h"

Intersection::Intersection() {}

Intersection::Intersection(const float t, Shape* obj) {
    this->t = t;
    this->object = obj;
}

Intersection::~Intersection() {
}
