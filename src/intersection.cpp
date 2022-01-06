#include "intersection.h"

Intersection::Intersection() {}

Intersection::Intersection(const float t, Shape* obj) {
    this->t = t;
    this->object = obj;
}

Intersection::~Intersection() {
}


struct comp {
    bool operator()(Intersection* i1, Intersection* i2) {
        return i1->t < i2->t;
    }
};

Intersection* hit(std::list<Intersection* > intList) {
    intList.sort(comp());

    for(auto const& intersection : intList)
        if(intersection->t >= 0) return intersection;
    
    return nullptr;
}