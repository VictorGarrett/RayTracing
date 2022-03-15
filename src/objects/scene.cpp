#include "objects/scene.h"

Scene::Scene(){

}

Scene::~Scene(){
    for(auto i = objects.begin(); i != objects.end(); i++)
        delete *i;  
}

void Scene::addObject(Object* obj){
    objects.push_back(obj);
}

void Scene::removeObject(Object* obj){
    for(auto i = objects.begin(); i != objects.end(); i++)
        if(*i == obj){
            delete *i;
            objects.erase(i);
        }
}

void Scene::addLight(Object* obj){
    lights.push_back(obj);
}

void Scene::removeLight(Object* obj){
    for(auto i = lights.begin(); i != lights.end(); i++)
        if(*i == obj){
            delete *i;
            lights.erase(i);
        }
}

Object* Scene::operator[](int i){
    return objects[i];
}