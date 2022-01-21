#include "camera.h"
#include "canvas.h"
#include "computations.h"
#include "cone.h"
#include "cube.h"
#include "cylinder.h"
#include "group.h"
#include "intersection.h"
#include "objParser.h"
#include "plane.h"
#include "shape.h"
#include "sphere.h"
#include "triangle.h"
#include "world.h"

Canvas render(Camera &camera, World &world);

void render_sample_scene();

void render_cube_scene();

int main() {
  render_cube_scene();
  return 0;
}

Canvas render(Camera &camera, World &world) {
  Canvas image = Canvas(camera.hsize, camera.vsize);

  for (unsigned int y = 0; y < camera.vsize; y++) {
    std::cout << (y * 100.0) / camera.vsize << '%' << '\n';
    for (unsigned int x = 0; x < camera.hsize; x++) {
      Ray *ray = camera.ray_for_pixel(x, y);
      Color color = color_at(world, ray, MAX_REFLECTIONS);

      image.write_pixel(x, y, color);
    }
  }

  return image;
}

void render_sample_scene() {
  World world = World();
  PointLight light_source = PointLight(point(-8, 8, -9), Color(1, 1, 1));

  // CUBES
  Cube *c = new Cube();
  float **cubetransform =
      multiply4x4(translation(0, 2.5, 0), scaling(0.25, 0.4, 0.25));
  c->set_transform(cubetransform);
  c->material.set_color(Color(1, 1, 1));
  c->material.reflective = 1;
  c->material.transparency = 1;
  c->material.refractive_index = 1.52;
  c->material.diffuse = 0.7;
  c->material.specular = 0.3;

  // SPHERES
  Sphere *middle = new Sphere();
  middle->set_transform(translation(-0.5, 1, 0.5));
  middle->material.set_color(Color(0, 0, 0));
  middle->material.reflective = 1;
  middle->material.transparency = 1;
  middle->material.refractive_index = 1.52;
  middle->material.diffuse = 0.7;
  middle->material.specular = 0.3;

  Sphere *right = new Sphere();
  float **right_wall_transf =
      multiply4x4(translation(1.5, 0.5, -0.5), scaling(0.8, 0.8, 0.8));
  right->set_transform(right_wall_transf);
  right->material.set_color(Color(0, 0, 0));
  right->material.diffuse = 0.7;
  right->material.specular = 0.3;
  right->material.reflective = 1;

  // right->material.reflective = 0.9;

  Sphere *left = new Sphere();
  float **leftwall_transf =
      multiply4x4(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
  left->set_transform(leftwall_transf);
  left->material.set_color(Color(0.8, 1, 1));
  left->material.diffuse = 0.7;
  left->material.specular = 0.3;

  // WALLSS
  Plane *floor = new Plane();
  floor->material.set_pattern(new Pattern(WHITE, Color(0.2, 0.2, 0.2)));
  floor->material.set_patternFn(&checker_pattern);
  floor->material.reflective = 0.3;

  Plane *wallRight = new Plane();
  wallRight->material.set_color(Color(1, 0.8, 0.8));
  float **wrt = multiply4x4(translation(3, 0, 0), rotation_z(PI / 2));
  wallRight->set_transform(wrt);

  Plane *wallback = new Plane();
  wallback->material.set_color(Color(0.8, 1, 0.8));
  float **wrt2 = multiply4x4(translation(-11, 0, 0), rotation_z(PI / 2));
  wallback->set_transform(wrt2);

  Plane *ceil = new Plane();
  ceil->material.set_color(Color(1, 1, 1));
  ceil->set_transform(translation(0, 11, 0));

  Plane *wallLeft = new Plane();
  wallLeft->material.set_color(Color(0.8, 1, 0.8));
  wallLeft->material.specular = 0;
  float **wlet = multiply4x4(translation(0, 0, -11), rotation_x(PI / 2));
  wallLeft->set_transform(wlet);

  Plane *wallLast = new Plane();
  wallLast->material.set_color(Color(0.8, 1, 0.8));
  wallLast->material.specular = 0;
  float **wlt = multiply4x4(translation(0, 0, 4), rotation_x(PI / 2));
  wallLast->set_transform(wlt);

  // CAMERA
  Camera camera = Camera(640, 360, PI / 3);
  Vec4 from = point(0, 2, -4);
  Vec4 to = point(0, 1, 0);
  Vec4 up = vector(0, 1, 0);
  camera.set_transform(view_transform(from, to, up));

  // ADD OBJECTS TO WORLD
  world.light = light_source;
  world.objects.push_back(static_cast<Shape *>(floor));
  world.objects.push_back(static_cast<Shape *>(wallRight));
  world.objects.push_back(static_cast<Shape *>(wallLeft));
  world.objects.push_back(static_cast<Shape *>(ceil));
  world.objects.push_back(static_cast<Shape *>(wallLast));
  world.objects.push_back(static_cast<Shape *>(wallback));
  world.objects.push_back(middle);
  world.objects.push_back(right);
  world.objects.push_back(left);
  // world.objects.push_back(c);

  // RENDER
  Canvas image = render(camera, world);
  canvas_to_ppm(image);
}

void render_cube_scene() {
  World w = World();
  PointLight light_source = PointLight(point(-8, 8, -9), Color(1, 1, 1));
  w.light = light_source;

  // CAMERA
  Camera camera = Camera(640, 360, PI / 3);
  Vec4 from = point(0, 3.5, -11);
  Vec4 to = point(1, -0.3, 0);
  Vec4 up = vector(0, 1, 0);
  camera.set_transform(view_transform(from, to, up));

  Vec4 p1 = point(0, 1, 0);
  Vec4 p2 = point(-1, 0, 0);
  Vec4 p3 = point(1, 0, 0);

  ObjParser parser = ObjParser();
  Group *g = parser.parse_obj_file("cow.obj");
  w.objects.push_back(g);

  Canvas img = render(camera, w);
  canvas_to_ppm(img);
}
