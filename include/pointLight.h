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

Color lighting(
    Material& material,
    float **transform,
    const PointLight& light,
    const Vec4& point,
    const Vec4& eyev,
    const Vec4& normalv,
    const bool in_shadow
);

Color shade_hit(World& world, Computations& comps, int remaining);

const bool is_shadowed(World& world, const Vec4& point);

Color color_at(World& world, Ray* r, int remaining = 4);

Color reflected_color(World& world, Computations comps, int remaining);

Color refracted_color(World& world, Computations comps, int remaining);

float schlick(Computations& comps);