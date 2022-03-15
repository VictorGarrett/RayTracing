#include "objects/object.h"
#include <stdio.h>

Object::Object(Primitive* shape, Material* baseMaterial, bool isLightSource): shape(shape), mat(baseMaterial), isLightSource(isLightSource){
    if(!shape)
        printf("WARNING: object shape not set\n");
        
    if(!baseMaterial)
        printf("WARNING: object material not set\n");

}

Object::~Object(){
    delete shape;
    delete mat;
}
