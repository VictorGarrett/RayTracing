#pragma once
#include "color.h"
#include "constants.h"

class Material {
public:
    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;

    Material();
    ~Material();

};
