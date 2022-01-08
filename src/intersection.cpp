#include "intersection.h"
#include <iostream>

Intersection::Intersection() {}

Intersection::Intersection(const float t, Shape* obj) {
    this->t = t;
    this->object = obj;
}

Intersection::~Intersection() {
    // this->object = nullptr;
}

// sort
struct sortIntersect {
    bool operator()(Intersection* i1, Intersection* i2) {
        return i1->t < i2->t;
    }
};

Intersection* hit(std::list<Intersection* > intList) {

    intList.sort(sortIntersect());
    for(auto const& intersection : intList)
        if(intersection->t >= 0) {
            return intersection;
        }


    return nullptr;
}