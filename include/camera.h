#pragma once
#include "transformations.h"
#include "ray.h"


class Camera
{
public:
    unsigned int hsize;
    unsigned int vsize;
    float field_of_view;
    float **transform;

    float pixel_size;
    float half_width;
    float half_height;

    Camera(const unsigned int width, const unsigned height, const float fov);
    ~Camera();

    Ray* ray_for_pixel(const unsigned int px, const unsigned int py);
};

