#include "material.h"
#include "mat.h"

Material::Material() {
    this->color = Color(1, 1, 1);
    this->ambient = AMBIENT;
    this->diffuse = DIFFUSE;
    this->specular = SPECULAR;
    this->shininess = SHININESS;
    this->reflective = REFLECTIVE;
    this->transparency = TRANSPARENCY;
    this->refractive_index = REFRACTIVE_INDEX;
    this->pattern = NULL;
}

Material::~Material() {
    delete pattern;
}

void Material::set_color(const Color& c){
    this->color = c;
}

void Material::set_pattern(Pattern *p){
    this->pattern = p;
}

void Material::set_patternFn(Color (*patternFn)(Pattern *p, const Vec4& point)){
    this->pattern->Fn = patternFn;
}

void Material::set_patternTransf(float **m){
    this->pattern->transform = inverse(m);
}

Color Material::get_color(const Vec4& point, float **m){
    if(this->pattern && this->pattern->Fn){
        Vec4 object_point = point;
        Vec4 pattern_point = this->pattern->transform * object_point;
        return this->pattern->Fn(this->pattern, pattern_point);
    }
    return this->color;
}

Color Material::get_color(){
    return this->color;
}

