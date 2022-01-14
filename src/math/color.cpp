#include "math/color.h"

color::color(){
    
}

color::color(const color& other):r(other.r), g(other.g), b(other.b){

}

color::color(float r, float g, float b):r(r), g(g), b(b){
    
}

color::~color(){

}


void color::normalize(){
    float len = sqrt(r*r+g*g+b*b);
    r /= len;
    g /= len;
    b /= len;
}

void color::operator=(const color& attrib){
    r = attrib.r;
    g = attrib.g;
    b = attrib.b;
}

void color::operator+=(const color& attrib){
    r += attrib.r;
    g += attrib.g;
    b += attrib.b;
}

void color::operator-=(const color& attrib){
    r -= attrib.r;
    g -= attrib.g;
    b -= attrib.b;
}

const color color::operator*(float scalar) const{
    return color(r*scalar, g*scalar, b*scalar);
}

const color color::operator/(float scalar) const{
    return color(r/scalar, g/scalar, b/scalar);
}

void color::operator*=(float scalar){
    r *= scalar;
    g *= scalar;
    b *= scalar;
}

void color::operator*=(const color& col){
    r *= col.r;
    g *= col.g;
    b *= col.b;
}

const color operator+(const color& first, const color& second){
    color sum(first.r+second.r, first.g+second.g, first.b+second.b);
    return sum;
}

const color operator-(const color& first, const color& second){
    color sub(first.r-second.r, first.g-second.g, first.b-second.b);
    return sub;
}

const color operator*(float scalar, const color& col){
    return color(col.r*scalar, col.g*scalar, col.b*scalar);
}

const color operator*(const color& first, const color& second){
    return color(first.r*second.r, first.g*second.g, first.b*second.b);
}

const color operator/(float scalar, const color& col){
    return color(col.r/scalar, col.g/scalar, col.b/scalar);
}

const float dot(const color& first, const color& second){
    return first.r*second.r + first.g*second.g + first.b*second.b;
}
