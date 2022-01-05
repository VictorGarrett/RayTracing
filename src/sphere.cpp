#include "sphere.h"

Sphere::Sphere():Shape() {
    this->center = point(0, 0, 0);
    this->radius = 1;
}
Sphere::~Sphere() {}

const void Sphere::intersect(const Ray& r) {
    Vec4 sphere_to_ray = r.origin - this->center;

    float a = dot(r.direction, r.direction);
    float b = 2 * dot(r.direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - 1;

    float discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        this->add_intersection((-b - sqrt(discriminant)) / (2 * a), this);
        this->add_intersection((-b + sqrt(discriminant)) / (2 * a), this);
    }
}
