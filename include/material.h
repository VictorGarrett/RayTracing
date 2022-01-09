#pragma once
#include "color.h"
#include "constants.h"
#include "pattern.h"
#include "functional"

class Material {
private:
    Color color;

public:
    Pattern *pattern;
    float ambient;
    float diffuse;
    float specular;
    float shininess;

    Material();
    ~Material();

    void set_color(const Color& c);
    void set_pattern(Pattern *p);
    void set_patternFn(Color (*patternFn)(Pattern *p, const Vec4& point));
    void set_patternTransf(float **m);

    Color get_color(const Vec4& point, float **m);
    Color get_color();
};
