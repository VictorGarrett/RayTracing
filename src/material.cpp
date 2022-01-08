#include "material.h"

Material::Material() {
    this->color = Color(1, 1, 1);
    this->ambient = AMBIENT;
    this->diffuse = DIFFUSE;
    this->specular = SPECULAR;
    this->shininess = SHININESS;
}

Material::~Material() {}