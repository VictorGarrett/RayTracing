#pragma once

#include "vec3f.h"

class Material{

    color baseColor;

    public:
        Material(color baseColor);
        ~Material();

        const color getColor();
};