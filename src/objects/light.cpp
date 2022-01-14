#include "objects/light.h"

LightSource::LightSource(const point& position, const color& sourceColor): position(position), sourceColor(sourceColor){
    
}

LightSource::~LightSource(){

}

const point LightSource::getPosition() const{
    return position;
}

const color LightSource::getColor() const{
    return sourceColor;
}