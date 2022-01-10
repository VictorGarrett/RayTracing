#include "object_builder.h"

ObjectBuilder::ObjectBuilder(): objMaterial(nullptr), objShape(nullptr){

}

ObjectBuilder::~ObjectBuilder(){
    if(objMaterial)
        delete objMaterial;

    if(objShape)
        delete objShape;
}

void ObjectBuilder::setPrimitiveSphere(point position, float radius){
    if(objShape)
        delete objShape;

    objShape = new Sphere(position, radius);
}

void ObjectBuilder::setPrimitivePlane(point position, vec3f normal){
    if(objShape)
        delete objShape;

    objShape = new Plane(position, normal);
}

void ObjectBuilder::setMaterial(color matColor, float specular, float diffuse, float shininess){
    if(objMaterial)
        delete objMaterial;

    objMaterial = new Material(matColor, specular, diffuse, shininess);
}

Object* ObjectBuilder::getObject(){

    if(objMaterial && objShape){
        Object* obj = new Object(objShape, objMaterial);
        objMaterial = nullptr;
        objShape = nullptr;
        return obj;
    }
    if(objMaterial){
        delete objMaterial;
        objMaterial = nullptr;
    }
    if(objShape){
        delete objShape;
        objShape = nullptr;
    }

    return nullptr;
}