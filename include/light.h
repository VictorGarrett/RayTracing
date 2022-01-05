#pragma once

#include "primitives.h"

class LightSource: public Primitive{

    private:
        color sourceColor;

    public:
        LightSource(vec3f center = {0.0f, 0.0f, 0.0f}, color sourceColor = {0.0f, 0.0f, 0.0f});
        ~LightSource();

        const vec3f intersectRay(Ray r) override;

        const color getColor() const;

};