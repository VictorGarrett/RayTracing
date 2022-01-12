#include "world.h"
#include "plane.h"
#include "computations.h"

World::World() {}

World::~World() {

}

// sort intersect
struct sortIntersect {
    bool operator()(Intersection* i1, Intersection* i2) {
        return i1->t < i2->t;
    }
};

std::list<Intersection* > World::intersect(Ray* r) {
    std::list<Intersection* > intersections;
    for (auto const& obj : this->objects) {
        std::list<Intersection* > obj_its = obj->intersect(r);
         for (auto const& iscts : obj_its) {
             intersections.push_back(iscts);
         }
    }

    intersections.sort(sortIntersect());
    return intersections;
}

World default_world() {
    PointLight light_source = PointLight(point(-10, 10, -10), Color(1, 1, 1));

    Sphere* s1 = new Sphere();
    s1->material.set_color(Color(0.8, 1.0, 0.6));
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;

    Sphere* s2 = new Sphere();
    s2->set_transform(scaling(0.5, 0.5, 0.5));

    World w = World();
    w.light = light_source;
    w.objects.push_back(static_cast<Shape*>(s1));
    w.objects.push_back(static_cast<Shape*>(s2));

    return w;
}