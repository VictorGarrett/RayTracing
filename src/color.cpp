#include "color.h"

Color::Color() {}
Color::Color(const float r, const float g, const float b){
    // this->red = r > 1 ? 1 : r < 0 ? 0 : r;
    // this->green = g > 1 ? 1 : g < 0 ? 0 : g;
    // this->blue = b > 1 ? 1 : b < 0 ? 0 : b;
    this->red = r;
    this->green = g;
    this->blue = b;
}

Color::~Color() {
}