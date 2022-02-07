#include "objects/material.h"

Material::Material(color baseColor, color emissiveColor): baseColor(baseColor), emissiveColor(emissiveColor){

}

Material::~Material(){

}

color Material::brdf(float theta_i, float phi_i, float theta_r, float phi_r){
    return baseColor/3.141592;
}