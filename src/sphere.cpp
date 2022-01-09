#include "sphere.h"
#include "mat.h"

Sphere::Sphere() :Shape() {

}
Sphere::~Sphere() {}

std::list<Intersection* > Sphere::intersect(Ray* r) {
    std::list <Intersection* > intList;
    Ray* r_transf = r->transform(this->inverseTransform);
    Vec4 sphere_to_ray = r_transf->origin - point(0, 0, 0);
    float a = dot(r_transf->direction, r_transf->direction);
    float b = 2 * dot(r_transf->direction, sphere_to_ray);
    float c = dot(sphere_to_ray, sphere_to_ray) - 1;

    float discriminant = b * b - 4 * a * c;



    if (discriminant >= 0) {
        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float t2 = (-b + sqrt(discriminant)) / (2 * a);
        intList.push_back(new Intersection(t1, this));
        intList.push_back(new Intersection(t2, this));
    }

    return intList;
}

Vec4 Sphere::normal_at(const Vec4& p) const {
    Vec4 object_point = this->inverseTransform * p;
    Vec4 object_normal = object_point - point(0, 0, 0);
    Vec4 world_normal = this->inverseTransposed * object_normal;
    world_normal.w = 0;
    return world_normal.normalize();

}