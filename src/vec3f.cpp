#include "vec3f.h"

vec3f::vec3f(){
    
}

vec3f::vec3f(const vec3f& other):x(other.x), y(other.y), z(other.z){

}

vec3f::vec3f(float x, float y, float z):x(x), y(y), z(z){
    
}

vec3f::~vec3f(){

}

float vec3f::length() const{
    return sqrt(x*x+y*y+z*z);
}

float vec3f::length2() const{
    return x*x+y*y+z*z;
}

void vec3f::normalize(){
    float len = length();
    x /= len;
    y /= len;
    z /= len;
}

void vec3f::operator=(const vec3f& attrib){
    x = attrib.x;
    y = attrib.y;
    z = attrib.z;
}

void vec3f::operator+=(const vec3f& attrib){
    x += attrib.x;
    y += attrib.y;
    z += attrib.z;
}

void vec3f::operator-=(const vec3f& attrib){
    x -= attrib.x;
    y -= attrib.y;
    z -= attrib.z;
}

const vec3f vec3f::operator*(float scalar) const{
    return vec3f(x*scalar, y*scalar, z*scalar);
}

const vec3f vec3f::operator/(float scalar) const{
    return vec3f(x/scalar, y/scalar, z/scalar);
}

void vec3f::operator*=(float scalar){
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

const vec3f operator+(const vec3f& first, const vec3f& second){
    vec3f sum(first.x+second.x, first.y+second.y, first.z+second.z);
    return sum;
}

const vec3f operator-(const vec3f& first, const vec3f& second){
    vec3f sub(first.x-second.x, first.y-second.y, first.z-second.z);
    return sub;
}

const vec3f operator*(float scalar, const vec3f& vec){
    return vec3f(vec.x*scalar, vec.y*scalar, vec.z*scalar);
}

const vec3f operator/(float scalar, const vec3f& vec){
    return vec3f(vec.x/scalar, vec.y/scalar, vec.z/scalar);
}

const float dot(const vec3f& first, const vec3f& second){
    return first.x*second.x + first.y*second.y + first.z*second.z;
}

const vec3f cross(const vec3f& first, const vec3f& second){
    return {(first.y*second.z - first.z*second.y), -(first.x*second.z - first.z*second.x), (first.x*second.y - first.y*second.x)};
}