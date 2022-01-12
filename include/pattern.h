#pragma once
#include "color.h"
#include "vec4.h"
;
class Pattern {
public:
    Color a;
    Color b;
    float **transform;
    Color (*Fn)(Pattern *p, const Vec4& point);

    Pattern();
    Pattern(const Color& a, const Color& b);
    ~Pattern();
};

Color stripe_pattern(Pattern *p, const Vec4& point);

Color gradient_pattern(Pattern *p, const Vec4&point);

Color ring_pattern(Pattern *p, const Vec4& point);

Color checker_pattern(Pattern *p, const Vec4& point);