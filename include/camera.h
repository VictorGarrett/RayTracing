#pragma once
#include "ray.h"

class Camera{
    private:
        vec3f position;
        vec3f forward;
        float fov;
        int targetWidth, targetHeight;
        vec3f verticalDisp;
        vec3f horizontalDisp;

    public:
        Camera(vec3f position = {0.0f, 0.0f, 0.0f},
               vec3f forward = {0.0f, 0.0f, 0.0f},
               vec3f upHint = {0.0f, 0.0f, 0.0f},
               int targetWidth = 0, int targetHeight = 0,
               float fov = 0.0f);
        ~Camera();

        void setFov(float fov);
        void setPosition(vec3f position);
        void setForward(vec3f forward);

        const Ray getRay(int i, int j);

};