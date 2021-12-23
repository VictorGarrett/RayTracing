#include "camera.h"

Camera::Camera(vec3f position, vec3f forward, vec3f upHint, int targetWidth, int targetHeight, float fov):
position(position),
forward(forward)
{
    this->targetWidth = targetWidth;
    this->targetHeight = targetHeight;
    this->fov = fov;

    forward.normalize();

    horizontalDisp = cross(forward, upHint);
    horizontalDisp.normalize();

    verticalDisp = cross(horizontalDisp, forward);

    horizontalDisp *= 2*tanf(fov)/(targetWidth);
    verticalDisp *= 2*tanf(fov)/(targetWidth);
    
}

Camera::~Camera(){

}

void Camera::setFov(float fov){
    this->fov = fov;
}

void Camera::setPosition(vec3f position){
    this->position = position;
}

void Camera::setForward(vec3f forward){
    this->forward = forward;
}

const Ray Camera::getRay(int x, int y){
    return Ray(position, forward + (x-targetWidth/2.0f)*horizontalDisp + -1*(y-targetHeight/2.0f)*verticalDisp);
}