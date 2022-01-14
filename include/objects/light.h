#pragma once

#include "objects/primitives.h"
#include "math/color.h"

class LightSource{

    private:
        point position;
        color sourceColor;

    public:
        LightSource(const point& position = {0.0f, 0.0f, 0.0f}, const color& sourceColor = {0.0f, 0.0f, 0.0f});
        ~LightSource();

        const point getPosition() const;
        const color getColor() const;

};