#include "camera.h"

Camera::Camera(const unsigned int width, const unsigned height, const float fov)
{
    this->hsize = width;
    this->vsize = height;
    this->field_of_view = fov;
    this->transform = get_idt_4x4();

    //pixel size
    float half_view = tan(this->field_of_view / 2);
    float aspect = width / (height * 1.0);

    if (aspect >= 1) {
        this->half_width = half_view;
        this->half_height = half_view / aspect;
    }
    else {
        this->half_width = half_view * aspect;
        this->half_height = half_view;
    }

    this->pixel_size = (2 * this->half_width) / this->hsize;
}

Camera::~Camera() {
    free_mat4x4(this->transform);
}

Ray* Camera::ray_for_pixel(const unsigned int px, const unsigned int py) {
    // offset from the edge of the canvas to the pixel center
    float xoffset = (px + 0.5) * this->pixel_size;
    float yoffset = (py + 0.5) * this->pixel_size;

    // camera left is +x
    float world_x = this->half_width - xoffset;
    float world_y = this->half_height - yoffset;


    // canvas is always a unit square centered at z=-1
    Vec4 pixel_pos = this->inverseTransform * point(world_x, world_y, -1);
    Vec4 origin = this->inverseTransform * point(0, 0, 0);
    Vec4 direction = (pixel_pos - origin).normalize();

    return new Ray(origin, direction);
}

void Camera::set_transform(float** m) {
    this->transform = m;
    this->inverseTransform = inverse(m);
}
