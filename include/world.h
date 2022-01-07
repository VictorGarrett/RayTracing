#pragma once
#include <list>
#include "sphere.h"
#include "pointLight.h"
#include "transformations.h"
#include "helper.h"

class World {
public:
    std::list<Shape* > objects;
    PointLight light;

    World();
    ~World();

    std::list<Intersection* > intersect(Ray* r);

};

World default_world();

