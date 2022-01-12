#include "plane.h"
#include "mat.h"

Plane::Plane() {
    this->normalv = vector(0, 1, 0);
}

Plane::~Plane() {

}

std::list<Intersection* > Plane::intersect(Ray* r) {
    std::list<Intersection* > intersections;
    Ray *r_transf = r->transform(this->inverseTransform); 
    float absoluto = r_transf->direction.y > 0 ? r_transf->direction.y : -r_transf->direction.y;
    if (absoluto < 0.0001)
        return intersections;

    float t = -r_transf->origin.y / r_transf->direction.y;

    intersections.push_back(new Intersection(t, this));
    return intersections;
}

Vec4 Plane::normal_at(const Vec4& p) const {
    return this->normalv;
}

void Plane::set_transform(float** m) {
    this->transform = m;
    this->inverseTransform = inverse(m);
    this->inverseTransposed = transpose(this->inverseTransform);
    this->normalv = inverse(m) * normalv;
}
