#pragma once
#include "color.h"
#include "vec4.h"

class Material;
class World;
class Computations; 
class Ray;

class PointLight {
public:
    Vec4 position;
    Color intensity;

    PointLight();
    PointLight(const Vec4& pos, const Color& col);
    ~PointLight();

};

Color lighting(const Material& material, const PointLight& light, const Vec4& point, const Vec4& eyev, const Vec4& normalv);

Color shade_hit(const World& world, const Computations& comps);

Color color_at(World& world, Ray *r);