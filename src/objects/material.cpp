#include "objects/material.h"

Material::Material(color baseColor, float specular, float diffuse, float shininess): baseColor(baseColor), specularCoef(specular), diffuseCoef(diffuse), shininess(shininess){

}

Material::~Material(){

}