#pragma once

#include "math/color.h"

class Material{

    color baseColor;
    color emissiveColor;


    public:
        Material(color baseColor = {0.0f, 0.0f, 0.0f}, color emissiveColor = {0.0f, 0.0f, 0.0f});
        ~Material();

        inline color getColor() const{
            return baseColor;
        }

        inline color getEmissiveColor() const{
            return emissiveColor;
        }

        color brdf(float theta_i, float phi_i, float theta_r, float phi_r);

};