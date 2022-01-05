#include "shape.h"
#include "intersection.h"

Shape::Shape(){
}

Shape::~Shape(){}

const void Shape::add_intersection(const float t, Shape* obj) {
    this->intersections.push_back(new Intersection(t, obj));
}
