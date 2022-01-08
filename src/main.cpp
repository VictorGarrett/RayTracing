#include "canvas.h"
#include "sphere.h"
#include "intersection.h"
#include "world.h"
#include "computations.h"
#include "camera.h"

Canvas render(Camera& camera, World& world) {
    Canvas image = Canvas(camera.hsize, camera.vsize);

    for(unsigned int y = 0; y < camera.vsize; y++) {
        for(unsigned int x = 0; x < camera.hsize; x++) {
            Ray *ray = camera.ray_for_pixel(x, y);

            Color color = color_at(world, ray);
            image.write_pixel(x, y, color); 
        }
    }

    return image;
}

int main() {
    World w = default_world();

    // OBJECTS
    Shape* s1 = w.objects.front();
    s1->set_transform(translation(-0.5, 1, 0.5));
    Shape* s2 = w.objects.back();
    s2->set_transform(multiply4x4(translation(0.1, 0, 0.5),scaling(10, 0.02, 10)));


    // CAMERA
    Camera c = Camera(640, 480, PI/ 3);
    Vec4 from = point(0, 1.5, -5);
    Vec4 to = point(0, 1, 0);
    Vec4 up = vector(0, 1, 0);
    c.set_transform(view_transform(from, to, up));

    Canvas image = render(c, w);
    canvas_to_ppm(image);

    return 0;
}
