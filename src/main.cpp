#include "canvas.h"
#include "sphere.h"
#include "intersection.h"
#include "transformations.h"
#include "pointLight.h"

int main() {
    Vec4 ray_origin = point(0, 0, -5);
    float wall_z = 10.0;
    float wall_size = 7.0;
    int canvas_pixels = 200;
    float pixel_size = wall_size / canvas_pixels;
    float half = wall_size / 2;

    Canvas c = Canvas(canvas_pixels, canvas_pixels);
    Color color = Color(1,0,0);
    Sphere *shape = new Sphere();
    shape->material.color = Color(1, 0.2, 1);
    PointLight light = PointLight(point(-10, 10, -10), Color(1, 1, 1));

    for(int y = 0; y < canvas_pixels; y++){
        float world_y = half - pixel_size * y;
        for(int x = 0; x < canvas_pixels; x++) {
            float world_x = -half + pixel_size * x;
            Vec4 position = point(world_x, world_y, wall_z);

            Ray *ray = new Ray(ray_origin, (position - ray_origin).normalize());

            std::list<Intersection* > xs = shape->intersect(ray);
            Intersection* collision = hit(xs);
            if(collision){
                Vec4 point = ray->get_position(collision->t);
                Vec4 normal = collision->object->normal_at(point);
                Vec4 eye = -ray->direction;
                color = lighting(collision->object->material, light, point, eye, normal);
                c.write_pixel(x, y, color);
            }

        }
    }

    canvas_to_ppm(c);

    return 0;
}

