#pragma once

#include "color.h"

class Material{

    color baseColor; //for now, material is just difuse color

    public:
        Material(color baseColor = {0.0f, 0.0f, 0.0f});
        ~Material();

        inline color getColor() const{
            return baseColor;
        }
};