#pragma once

#include "color.h"

class Material{

    color baseColor;//diffuse color
    float specularCoef;
    float diffuseCoef;
    float shininess;

    public:
        Material(color baseColor = {0.0f, 0.0f, 0.0f}, float specular = 0.0f, float diffuse = 0.0f, float shininess = 0.0f);
        ~Material();

        inline color getColor() const{
            return baseColor;
        }
        inline float getSpecular() const{
            return specularCoef;
        }
        inline float getDiffuse() const{
            return diffuseCoef;
        }
        inline float getShininess() const{
            return shininess;
        }
};