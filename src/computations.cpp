#include "computations.h"

Computations::Computations(Intersection* i, Ray* r, std::list<Intersection* > xs) {
    this->init_points(i, r);
    if(xs.size() > 0)
        this->init_refraction_index(i, xs);
}

Computations::~Computations() {
    this->object = nullptr;
}

void Computations::init_points(Intersection* i, Ray* r){
    this->t = i->t;
    this->object = i->object;
    
    this->point = r->get_position(i->t);
    this->eyev = -r->direction;
    this->normalv = this->object->normal_at(this->point);
    this->inside = dot(normalv, eyev) < 0 ? true : false;
    
    if (this->inside) this->normalv = -this->normalv;
    this->reflectv = reflect(r->direction, this->normalv);
    this->over_point = point + normalv * EPSILON;
    this->under_point = point - normalv * EPSILON;
}

void Computations::init_refraction_index(Intersection* i, std::list<Intersection* > xs){
    std::list<Shape* > containers;
    for(auto intersec: xs){
        if(intersec == i){
            if(containers.size() == 0)
                this->n1 = 1.0;
            else
                this->n1 = containers.back()->material.refractive_index;
        }
        bool contains = false;
        for(auto c: containers){
            if(c == intersec->object) contains = true;
        }

        if(contains)
            containers.remove(intersec->object);
        else
            containers.push_back(intersec->object);
        
        if(intersec == i){
            if(containers.size() == 0)
                this->n2 = 1.0;
            else
                this->n2 = containers.back()->material.refractive_index;
        }
    }
}
