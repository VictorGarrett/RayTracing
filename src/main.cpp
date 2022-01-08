#include "canvas.h"
#include "sphere.h"
#include "intersection.h"
#include "world.h"
#include "computations.h"
#include "camera.h"
#include "plane.h"

Canvas render(Camera& camera, World& world);

void render_sample_scene();

int main() {
    render_sample_scene();

    return 0;
}

Canvas render(Camera& camera, World& world) {
    Canvas image = Canvas(camera.hsize, camera.vsize);

    for (unsigned int y = 0; y < camera.vsize; y++) {
        for (unsigned int x = 0; x < camera.hsize; x++) {
            Ray* ray = camera.ray_for_pixel(x, y);
            Color color = color_at(world, ray);
            image.write_pixel(x, y, color);
        }
    }

    return image;
}

void render_sample_scene() {
    World world = World();
    PointLight light_source = PointLight(point(-10, 10, -10), Color(1, 1, 1));

    // SPHERES
    Sphere* middle = new Sphere();
    middle->set_transform(translation(-0.5, 1, 0.5));
    middle->material.color = Color(0.1, 1, 0.5);
    middle->material.diffuse = 0.7;
    middle->material.specular = 0.3;

    Sphere* right = new Sphere();
    float** right_wall_transf = multiply4x4(
        translation(1.5, 0.5, -0.5),
        scaling(0.5, 0.5, 0.5)
    );
    right->set_transform(right_wall_transf);
    right->material.color = Color(0.5, 1, 0.1);
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;

    Sphere* left = new Sphere();
    float** leftwall_transf = multiply4x4(
        translation(-1.5, 0.33, -0.75),
        scaling(0.33, 0.33, 0.33)
    );
    left->set_transform(leftwall_transf);
    left->material.color = Color(1, 0.8, 0.1);
    left->material.diffuse = 0.7;
    left->material.specular = 0.3;

    // WALLSS
    Plane* floor = new Plane();

    // CAMERA
    Camera camera = Camera(640, 480, PI / 3);
    Vec4 from = point(0, 1.5, -5);
    Vec4 to = point(0, 1, 0);
    Vec4 up = vector(0, 1, 0);
    camera.set_transform(view_transform(from, to, up));

    // ADD OBJECTS TO WORLD
    world.light = light_source;
    world.objects.push_back( static_cast<Shape* >(floor));

    world.objects.push_back(middle);
    world.objects.push_back(right);
    world.objects.push_back(left);

    // RENDER
    Canvas image = render(camera, world);
    canvas_to_ppm(image);
}
