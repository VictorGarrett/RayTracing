#include "light.h"

LightSource::LightSource(vec3f center, color sourceColor): Primitive(center), sourceColor(sourceColor){
    
}

LightSource::~LightSource(){

}

const vec3f LightSource::intersectRay(Ray r){
    return {0.0f, 0.0f, 0.0f};
}

const color LightSource::getColor() const{
    return sourceColor;
}