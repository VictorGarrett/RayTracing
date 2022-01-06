#include "material.h"

Material::Material(){
    this->color = Color(1, 1, 1);
    this->ambient = 0.1f;
    this->diffuse = 0.9f;
    this->specular = 0.9f;
    this->shininess = 200.0f;
}

Material::~Material(){}